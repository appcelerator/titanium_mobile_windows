/**
 * Runs an app on a Windows Store emulator.
 *
 * @copyright
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 *
 * @license
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

const
	appc = require('node-appc'),
	async = require('async'),
	ejs = require('ejs'),
	fields = require('fields'),
	fs = require('fs'),
	os = require('os'),
	path = require('path'),
	uuid = require('node-uuid'),
	windowslib = require('windowslib'),
	__ = appc.i18n(__dirname).__;

exports.cliVersion = '>=3.2.1';

exports.init = function (logger, config, cli) {
	var emuHandle,
		emuInstall,
		logRelay;

	cli.on('build.pre.compile', {
		priority: 8000,
		post: function (builder, finished) {
			if (builder.buildOnly || !/^ws-local$/.test(builder.target)) return finished();

			async.series([
				function (next) {
					if (!builder.enableLogging) return next();

					// create the log relay instance so we can get a token to embed in our app
					var session = appc.auth.status(),
						userToken = session.loggedIn && session.email || uuid.v4(),
						appToken = builder.tiapp.id,
						machineToken = os.hostname(),
						deviceToken = cli.argv['device-id'],
						targetToken = builder.target,
						levels = logger.getLevels(),
						logLevelRE = /^(\u001b\[\d+m)?\[(.+)\]\s*(\u001b\[\d+m)?(.*)/i,
						lastLogger = 'debug';

					logRelay = new windowslib.LogRelay({
						includeInternalIPAddresses: builder.target !== 'ws-remote',
						serverToken: builder.hash(userToken + '/' + appToken + '/' + machineToken + '/' + targetToken + '/' + deviceToken),
						tcpPort: config.get('windows.log.tcpPort', config.get('windows.log.tcpPort'))
					});

					logRelay.on('message', function (msg) {
						var m = msg.match(logLevelRE);
						if (m) {
							lastLogger = m[2].toLowerCase();
							if (levels.indexOf(lastLogger) == -1) {
								logger.log(msg.grey);
							} else {
								logger[lastLogger](m[4].trim());
							}
						} else {
							(logger[lastLogger] || logger.info)(msg);
						}
					});

					logRelay.on('log-debug', function (msg) {
						logger.debug(msg);
					});

					logRelay.on('disconnect', function () {
						logger.info("Disconnected from app");
					});

					logRelay.on('connection', function () {
						logger.info("Connected to app");
					});

					logRelay.on('started', function () {
						finished();
					});

					logRelay.start();
				}
			], function () {
				finished();
			});
		}
	});

	cli.on('build.windows.copyResources', {
		pre: function (builder, finished) {
			if (!/^ws-local$/.test(builder.target)) return finished();
			// write the titanium settings file
			fs.writeFileSync(
				path.join(builder.buildTargetAssetsDir, 'titanium_settings.ini'),
				ejs.render(
					fs.readFileSync(
						path.resolve(builder.platformPath, 'templates', 'build', 'titanium_settings.ini.ejs')
					).toString(),
					{
						ipAddressList: logRelay && logRelay.ipAddressList.join(',') || '',
						logConnectionTimeout: config.get('windows.log.connectionTimeout', 2000),
						serverToken: logRelay && logRelay.serverToken || '',
						tcpPort: logRelay && logRelay.tcpPort || ''
					}
				)
			);

			finished();
		}
	});

	cli.on('build.post.compile', {
		priority: 8000,
		post: function (builder, finished) {
			if (builder.buildOnly || !/^ws-local$/.test(builder.target)) return finished();

			var delta = appc.time.prettyDiff(cli.startTime, Date.now());
			logger.info(__('Finished building the application in %s', delta.cyan));

			function install() {
				if (logRelay) {
					// start the log relay server
					var started = false;

					function endLog() {
						if (started) {
							var endLogTxt = __('End application log');
							logger.log('\r' + ('-- ' + endLogTxt + ' ' + (new Array(75 - endLogTxt.length)).join('-')).grey + '\n');
							started = false;
						}
					}

					logRelay.on('connection', function () {
						endLog();
						var startLogTxt = __('Start application log');
						logger.log(('-- ' + startLogTxt + ' ' + (new Array(75 - startLogTxt.length)).join('-')).grey);
						started = true;
					});

					logRelay.on('disconnect', endLog);

					logRelay.on('stopped', endLog);

					process.on('SIGINT', function () {
						logRelay.stop();
						process.exit(0);
					});
				}

				var tiapp = builder.tiapp,
					appId = tiapp.windows.id || tiapp.id,
					sanitizedName = builder.sanitizeProjectName(tiapp.name),
					// name of the directory holding appx and dependencies subfolder
					dirName = sanitizedName + '_' + builder.buildVersion + ((builder.buildConfiguration == 'Debug') ? '_Debug_Test' : '_Test'),
					projectDir = path.resolve(builder.cmakeTargetDir, 'AppPackages', sanitizedName, dirName),
					// Options for installing and launching app
					opts = appc.util.mix({
						killIfRunning: false,
						timeout: config.get('windows.log.timeout', 60000),
						wpsdk: builder.wpsdk
					}, builder.windowslibOptions);

				async.series([function(next) {
					if (cli.argv.hasOwnProperty('forceUnInstall')) {
						logger.info(__('Uninstalling old versions of the application'));
						windowslib.winstore.uninstall(appId, opts, next);
					} else {
						next();
					}
				}, function(next) {
					logger.info(__('Installing the application'));
					windowslib.winstore.install(projectDir, opts, next);
				}, function (next) {
					logger.info(__('Making the application exempt from loopback IP restrictions for logging'));
					windowslib.winstore.loopbackExempt(appId, opts, next);
				}, function(next) {
					logger.info(__('Launching the application'));
					windowslib.winstore.launch(appId, opts, function (err, pid) {
						if (err) {
							return next(err);
						}
						logger.info(__('Finished launching the application'));

						// Poll on pid for when the app closes like we do for the emulator!
						var pollInterval = config.get('windows.emulator.pollInterval', 1000);
						if (pollInterval > 0) {
							(function watchForAppQuit() {
								setTimeout(function () {
									windowslib.process.find(pid, opts, function (err, proc) {
										if (!err && !proc) { // no error, but no process by pid
											logRelay && logRelay.stop();
											process.exit(0);
										} else {
											watchForAppQuit();
										}
									});
								}, pollInterval);
							}());
						}

						if (logRelay) {
							logger.info(__('Waiting for app to connect to log relay'));
						} else {
							// no reason to stick around, let the build command finish
							next(null);
						}
					});
				}], function (err, results) {
					if (err) {
						logger.error(err);
						process.exit(1);
					}
				});

				finished();
			}

			install();
		}
	});
};
