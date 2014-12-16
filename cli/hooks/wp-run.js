/**
 * Runs an app on a Windows Phone device or emulator.
 *
 * @copyright
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
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
			if (builder.buildOnly || !/^wp-emulator|wp-device$/.test(builder.target)) return finished();

			async.series([
				function (next) {
					if (builder.target !== 'wp-emulator') return next();

					logger.info(__('Launching emulator: %s', builder.deviceId.cyan));

					cli.createHook('build.windows.startEmulator', function (deviceId, opts, cb) {
						windowslib.emulator.launch(deviceId, opts)
							.on('error', function (err) {
								logger.error(__('Failed to start emulator "%s"', deviceId.cyan) + '\n');
								logger.error(err.message || err);
								logger.log();
								process.exit(1);
							}).on('launched', function (_emuHandle) {
								emuHandle = _emuHandle;

								logger.info(__('Windows Phone emulator is ready'));

								// unblock the install if necessary
								if (typeof emuInstall === 'function') {
									setTimeout(function () {
										emuInstall();
									}, 1000);
								}
							}).on('timeout', function (err) {
								logger.error(err);
								logger.log();
								process.exit(1);
							});

						cb();
					})(builder.deviceId, appc.util.mix({
						killIfRunning: false
					}, builder.windowslibOptions), next);
				},

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
						includeInternalIPAddresses: builder.target !== 'wp-device',
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
			if (builder.buildOnly || !/^wp-emulator|wp-device$/.test(builder.target)) return finished();

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
					baseFileName = tiapp.name + '_1.1.0.0_' + builder.cmakeArch + ((builder.buildConfiguration == 'Debug') ? '_Debug' : ''),
					xapFile = path.resolve(builder.cmakeTargetDir, 'AppPackages', tiapp.name, baseFileName + '_Test', baseFileName + '.appx'),
					phoneLibAppx = path.resolve(builder.cmakeTargetDir, 'AppPackages', tiapp.name, baseFileName + '_Test', 'Dependencies', 'x86', 'Microsoft.VCLibs.x86.Debug.12.00.Phone.appx'),
					opts = appc.util.mix({
						killIfRunning: false,
						timeout: config.get('windows.log.timeout', 60000),
						wpsdk: builder.wpsdk
					}, builder.windowslibOptions);

				logger.info(__('Installing and launching the application'));
				// When we do a debug build we need to install a dependency library before we install the actual app for it to work
				// FIXME I don't think we need to do this for Release config, and probably not for actual device installs!
				windowslib.install(builder.deviceId, phoneLibAppx, appc.util.mix({
						skipLaunch: true
					}, opts))
					.on('installed', function (handle) {
						logger.info(__('Finished installing the debug dependency'));

						// Now install the real app
						windowslib.install(builder.deviceId, xapFile, opts)
						.on('installed', function (handle) {
							logger.info(__('Finished launching the application'));

							// watch for when the emulator is quit, if necessary
							if (builder.target == 'wp-emulator') {
								var pollInterval = config.get('windows.emulator.pollInterval', 1000);
								if (pollInterval > 0) {
									(function watchForEmulatorQuit() {
										setTimeout(function () {
											windowslib.emulator.isRunning(builder.deviceId, builder.windowslibOptions, function (err, running) {
												if (!err && !running) {
													logRelay && logRelay.stop();
													process.exit(0);
												} else {
													watchForEmulatorQuit();
												}
											});
										}, pollInterval);
									}());
								}
							}

							if (logRelay) {
								logger.info(__('Waiting for app to connect to log relay'));
							} else {
								// no reason to stick around, let the build command finish
								finished();
							}
						})
						.on('timeout', function (err) {
							logRelay && logRelay.stop();
							finished(err);
						})
						.on('error', function (err) {
							logRelay && logRelay.stop();
							finished(err);
						});
					})
					.on('timeout', function (err) {
						logRelay && logRelay.stop();
						finished(err);
					})
					.on('error', function (err) {
						logRelay && logRelay.stop();
						finished(err);
					});

				finished(); // temp
			}

			if (builder.target === 'wp-device' || emuHandle) {
				install();
			} else {
				// emulator not started yet, queue up the install
				emuInstall = install;
				logger.info(__('Waiting for Windows Phone emulator to finish booting'));
			}
		}
	});
};
