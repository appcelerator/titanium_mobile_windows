/**
 * Windows build command.
 *
 * @module cli/_build
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
	Builder = require('titanium-sdk/lib/builder'),
	nativeTypeGenerator = require('../lib/stub'),
	cleanCSS = require('clean-css'),
	DOMParser = require('xmldom').DOMParser,
	fields = require('fields'),
	fs = require('fs'),
	i18n = require('titanium-sdk/lib/i18n'),
	jsanalyze = require('titanium-sdk/lib/jsanalyze'),
	os = require('os'),
	path = require('path'),
	spawn = require('child_process').spawn,
	ti = require('titanium-sdk'),
	util = require('util'),
	windowslib = require('windowslib'),
	windowsPackageJson = appc.pkginfo.package(module),
	wrench = require('wrench'),
	__ = appc.i18n(__dirname).__;

/*
TODO:
	- figure out how to support different cpu architectures
	  - command line option?
	  - tiapp.xml property?
	  - always build for all architectures?

	- figure out signing windows phone apps
	  - we have a --ws-cert option, but maybe that should become just --cert?
	  - signing the app is done in the hooks\[wp|ws]-run.js hooks

	- depending on how tiapp.xml values (desc, publisher, name, id, version, etc)
	  are embedded the app, you may be able to reduce the number of checks that
	  trigger a full rebuild

	- many other TODOs sprinkled through this file and the hooks
*/

/**
 * Creates the Windows build object.
 *
 * @class
 * @classdesc Windows build logic and state.
 * @constructor
 */
function WindowsBuilder() {
	Builder.apply(this, arguments);

	this.deployTypes = {
		// windows phone targets
		'wp-emulator': 'development',
		'wp-device': 'test',
		'dist-phonestore': 'production',

		// windows store targets
		// 'ws-simulator': 'development',
		'ws-local': 'development',
		// 'ws-remote': 'test',
		'dist-winstore': 'production'
	};

	this.targets = Object.keys(this.deployTypes);

	this.defaultTarget = 'wp-emulator';

	this.tiSymbols = {};
}

util.inherits(WindowsBuilder, Builder);

/**
 * Returns the available target Windows Phone devices and emulators. It will
 * cache the results so subsequent calls don't have to requery.
 *
 * This function must be called after the CLI has called config() and after
 * the --ws-sdk option has been processed.
 *
 * @returns {Array}
 */
WindowsBuilder.prototype.getTargetDevices = function getTargetDevices() {
	if (this.deviceCache) {
		return this.deviceCache;
	}

	var target = this.cli.argv.target,
		wpsdk = this.cli.argv['wp-sdk'];

	if (target === 'wp-emulator' && this.windowsInfo.emulators && Array.isArray(this.windowsInfo.emulators[wpsdk])) {
		return this.deviceCache = this.windowsInfo.emulators[wpsdk];

	} else if (target === 'wp-device' && Array.isArray(this.windowsInfo.devices)) {
		return this.deviceCache = this.windowsInfo.devices;
	}

	return [];
};

/**
 * Defines the command line options for the build command.
 *
 * @param {Object} logger - The logger instance.
 * @param {Object} config - The Titanium CLI config instance.
 * @param {Object} cli - The Titanium CLI instance.
 *
 * @returns {Function} A function to be called async which returns the actual configuration.
 */
WindowsBuilder.prototype.config = function config(logger, config, cli) {
	Builder.prototype.config.apply(this, arguments);

	this.windowslibOptions = {
		powershell: config.get('windows.executables.powershell'),
		pvk2pfx: config.get('windows.executables.pvk2pfx'),
		preferredWindowsPhoneSDK: config.get('windows.wpsdk.selectedVersion'),
		preferredVisualStudio: config.get('windows.visualstudio.selectedVersion'),
		supportedMSBuildVersions: windowsPackageJson.vendorDependencies['msbuild'],
		supportedVisualStudioVersions: windowsPackageJson.vendorDependencies['visual studio'],
		supportedWindowsPhoneSDKVersions: windowsPackageJson.vendorDependencies['windows phone sdk'],
		tasklist: config.get('windows.executables.tasklist')
	};

	this.ignoreDirs = new RegExp(config.get('cli.ignoreDirs'));
	this.ignoreFiles = new RegExp(config.get('cli.ignoreFiles'));

	function assertIssue(issues, name) {
		var i = 0,
			len = issues.length;
		for (; i < len; i++) {
			if ((typeof name === 'string' && issues[i].id === name) || (typeof name === 'object' && name.test(issues[i].id))) {
				issues[i].message.split('\n').forEach(function (line) {
					logger.error(line.replace(/(__(.+?)__)/g, '$2'.bold));
				});
				logger.log();
				process.exit(1);
			}
		}
	}

	// we hook into the pre-validate event so that we can stop the build before
	// prompting if we know the build is going to fail.
	//
	// this is also where we can detect the Windows environments before
	// prompting occurs. because detection is expensive we also do it here instead
	// of during config() because there's no sense detecting if config() is being
	// called because of the help command.
	cli.on('cli:pre-validate', function (obj, callback) {
		if (cli.argv.platform && cli.argv.platform !== 'windows') {
			return callback();
		}

		// make sure we have a sane environment for the specified target
		assertIssue(this.windowsInfo.issues, 'WINDOWS_VISUAL_STUDIO_NOT_INSTALLED');
		assertIssue(this.windowsInfo.issues, 'WINDOWS_MSBUILD_ERROR');
		assertIssue(this.windowsInfo.issues, 'WINDOWS_MSBUILD_TOO_OLD');

		callback();
	}.bind(this));

	return function (finished) {
		windowslib.detect(this.windowslibOptions, function (err, windowsInfo) {
			this.windowsInfo = windowsInfo;

			cli.createHook('build.windows.config', this, function (callback) {
				callback(null, this.conf = {
					options: {
						'build-type': {
							hidden: true
						},
						'debug-host': {
							hidden: true
						},
						'deploy-type': this.configOptionDeployType(100),
						'device-id': this.configOptionDeviceID(500),
						'output-dir': this.configOptionOutputDir(400),
						'profiler-host': {
							hidden: true
						},
						'target': this.configOptionTarget(110),
						'wp-publisher-guid': this.configOptionWPPublisherGUID(210),
						'wp-sdk': this.configOptionWPSDK(200),
						'ws-cert': this.configOptionWSCert(300)
					}
				});
			})(function (err, result) {
				finished(result);
			});
		}.bind(this));
	}.bind(this);
};

/**
 * Defines the --deploy-type option.
 *
 * @param {Integer} order - The order to apply to this option.
 *
 * @returns {Object}
 */
WindowsBuilder.prototype.configOptionDeployType = function configOptionDeployType(order) {
	return {
		abbr: 'D',
		desc: __('the type of deployment; only applicable when target is %s, %s, or %s', 'wp-emulator'.cyan, 'wp-device'.cyan, 'ws-local'.cyan), // or ws-simulator or ws-remote
		hint: __('type'),
		order: order,
		values: ['test', 'development', 'production']
	};
};

/**
 * Defines the --device-id option.
 *
 * @param {Integer} order - The order to apply to this option.
 *
 * @returns {Object}
 */
WindowsBuilder.prototype.configOptionDeviceID = function configOptionDeviceID(order) {
	var cli = this.cli;

	function validate(value, callback) {
		if (!value && value !== 0) {
			return callback(new Error(__('Invalid device id')));
		}

		var devices = this.getTargetDevices();

		if (cli.argv.target === 'wp-emulator' && value === 'xd' && devices[0]) {
			// pick first emulator
			return callback(null, devices[0].udid);
		}

		if (cli.argv.target === 'wp-device' && value === 'de' && devices[0]) {
			// pick first device
			return callback(null, devices[0].udid);
		}

		var dev;

		if (!devices.some(function (d) {
			if (d.udid == value || d.name === value) {
				dev = d;
				value = d.udid;
				return true;
			}
			return false;
		})) {
			return callback(new Error(__('Invalid device id "%s"', value)));
		}

		// check the device
		if (cli.argv.target === 'wp-device') {
			// try connecting to the device to detect no device or more than 1 device
			windowslib.device.connect(dev.udid, this.windowslibOptions)
				.on('connected', function () {
					callback(null, value);
				})
				.on('error', function (err) {
					this.logger.log();
					this.logger.error(err.message || err.toString());
					this.logger.log();
					process.exit(1);
				}.bind(this));
		} else {
			// must be emulator then
			callback(null, value);
		}
	}

	return {
		abbr: 'C',
		desc: __('the Windows Phone device or emulator udid to launch the app on; only applicable when target is %s or %s', 'wp-emulator'.cyan, 'wp-device'.cyan),
		hint: 'udid',
		order: order,
		prompt: function (callback) {
			var devices = this.getTargetDevices(),
				maxLen = devices.reduce(function (a, b) { return Math.max(a, b.name.length); }, 0);

			if (!devices.length) {
				// this shouldn't happen
				throw new Error(
					cli.argv.target === 'wp-emulator'
						? __('No Windows Phone emulators found')
						: __('No Windows Phone devices found')
				);
			}

			callback(fields.select({
				title: cli.argv.target === 'wp-emulator'
					? __("Which emulator do you want to install your app on?")
					: __("Which device do you want to install your app on?"),
				promptLabel: __('Select by number or name'),
				default: devices.length && devices[0].name,
				formatters: {
					option: function (opt, idx, num) {
						return '  ' + num + appc.string.rpad(opt.name, maxLen).cyan + '  ' + __('(udid: %s)', opt.udid).grey;
					}
				},
				margin: '',
				autoSelectOne: true,
				numbered: true,
				relistOnError: true,
				complete: ['name', 'udid'],
				completeIgnoreCase: true,
				ignoreCase: true,
				suggest: false,
				optionLabel: 'name',
				optionValue: 'udid',
				options: devices,
				validate: validate.bind(this)
			}));
		}.bind(this),
		validate: validate.bind(this),
		verifyIfRequired: function (callback) {
			callback(!this.cli.argv['build-only']);
		}.bind(this)
	};
};

/**
 * Defines the --output-dir option.
 *
 * @param {Integer} order - The order to apply to this option.
 *
 * @returns {Object}
 */
WindowsBuilder.prototype.configOptionOutputDir = function configOptionOutputDir(order) {
	function validate(outputDir, callback) {
		callback(outputDir || !this.conf.options['output-dir'].required ? null : new Error(__('Invalid output directory')), outputDir);
	}

	return {
		abbr: 'O',
		desc: __('the output directory to copy the built app; only applicable when target is %s or %s', 'dist-phonestore'.cyan, 'dist-phonestore'.cyan),
		hint: 'dir',
		order: order,
		prompt: function (callback) {
			callback(fields.file({
				promptLabel: __('Where would you like the output XAP file saved?'),
				default: this.cli.argv['project-dir'] && path.join(this.cli.argv['project-dir'], 'dist'),
				complete: true,
				showHidden: true,
				ignoreDirs: this.ignoreDirs,
				ignoreFiles: /.*/,
				validate: validate.bind(this)
			}));
		}.bind(this),
		validate: validate.bind(this)
	};
};

/**
 * Defines the --target option.
 *
 * @param {Integer} order - The order to apply to this option.
 *
 * @returns {Object}
 */
WindowsBuilder.prototype.configOptionTarget = function configOptionTarget(order) {
	return {
		abbr: 'T',
		callback: function (value) {
			// as soon as we know the target, toggle required options for validation

			if (value === 'wp-emulator' || value === 'wp-device') {
				this.conf.options['device-id'].required = true;
			}

			if (value === 'wp-emulator' || value === 'wp-device' || value === 'dist-phonestore') {
				this.conf.options['wp-publisher-guid'].required = true;
				this.conf.options['wp-sdk'].required = true;
			}

			if (value === 'dist-phonestore' || value === 'dist-winstore') {
				this.conf.options['output-dir'].required = true;
			}

			if (value === 'dist-winstore') {
				this.conf.options['ws-cert'].required = true;
			}
		}.bind(this),
		default: this.defaultTarget,
		desc: __('the target to build for'),
		order: order,
		required: true,
		values: this.targets
	};
};

/**
 * Defines the --wp-publisher-guid option.
 *
 * @param {Integer} order - The order to apply to this option.
 *
 * @returns {Object}
 */
WindowsBuilder.prototype.configOptionWPPublisherGUID = function configOptionWPPublisherGUID(order) {
	function validate(value, callback) {
		if (!/^[0-9a-f]{8}-[0-9a-f]{4}-[1-5][0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i.test(value)) {
			return callback(new Error(__('Invalid "%s" value "%s"', '--wp-publisher-guid', value)));
		}
		callback(null, value);
	}

	return {
		abbr: 'G',
		default: this.config.get('windows.phone.publisherGuid'),
		desc: __('your publisher GUID, obtained from %s; only applicable when target is %s, %s, or %s', 'http://appcelerator.com/windowsphone'.cyan, 'wp-emulator'.cyan, 'wp-device'.cyan, 'dist-phonestore'.cyan),
		hint: __('guid'),
		order: order,
		prompt: function (callback) {
			callback(fields.text({
				promptLabel: __('What is your __Windows Phone Publisher GUID__?'),
				validate: validate
			}));
		},
		validate: validate
	};
};

/**
 * Defines the --wp-sdk option.
 *
 * @param {Integer} order - The order to apply to this option.
 *
 * @returns {Object}
 */
WindowsBuilder.prototype.configOptionWPSDK = function configOptionWPSDK(order) {
	return {
		abbr: 'S',
		default: '8.1',
		desc: __('the Windows Phone SDK version; only used when target is %s, %s, or %s', 'wp-emulator'.cyan, 'wp-device'.cyan, 'dist-phonestore'.cyan),
		hint: __('version'),
		order: order,
		values: ['8.1']
	};
};

/**
 * Defines the --ws-cert option.
 *
 * @param {Integer} order - The order to apply to this option.
 *
 * @returns {Object}
 */
WindowsBuilder.prototype.configOptionWSCert = function configOptionWSCert(order) {
	function validate(certFile, callback) {
		if (!certFile) {
			return callback(new Error(__('Please specify the path to your certificate file')));
		}

		certFile = appc.fs.resolvePath(certFile);

		if (!fs.existsSync(certFile) || !fs.statSync(certFile).isFile()) {
			return callback(new Error(__('Invalid cert file')));
		}

		callback(null, certFile);
	}

	return {
		abbr: 'R',
		desc: __('the location of the cert file; only applicable when target is %s or %s', 'ws-local'.cyan, 'dist-winstore'.cyan), // or ws-simulator or ws-remote
		hint: 'path',
		order: order,
		prompt: function (callback) {
			callback(fields.file({
				promptLabel: __('Where is the __keystore file__ used to sign the app?'),
				complete: true,
				showHidden: true,
				ignoreDirs: this.ignoreDirs,
				ignoreFiles: this.ignoreFiles,
				validate: validate
			}));
		},
		validate: validate
	};
};

/**
 * Validates the Windows build-specific arguments, tiapp.xml settings, and environment.
 *
 * @param {Object} logger - The logger instance.
 * @param {Object} config - The Titanium CLI config instance.
 * @param {Object} cli - The Titanium CLI instance.
 *
 * @returns {Function} A function to be called async which returns the actual configuration.
 */
WindowsBuilder.prototype.validate = function validate(logger, config, cli) {
	Builder.prototype.validate.apply(this, arguments);

	this.target = cli.argv.target;
	this.wpsdk = cli.argv['wp-sdk'];
	this.deployType = !/^dist-$/.test(this.target) && cli.argv['deploy-type'] ? cli.argv['deploy-type'] : this.deployTypes[this.target];
	this.buildType = cli.argv['build-type'] || '';

	// ti.deploytype is deprecated and so we force the real deploy type
	if (cli.tiapp.properties['ti.deploytype']) {
		logger.warn(__('The %s tiapp.xml property has been deprecated, please use the %s option', 'ti.deploytype'.cyan, '--deploy-type'.cyan));
	}
	cli.tiapp.properties['ti.deploytype'] = { type: 'string', value: this.deployType };

	// manually inject the build profile settings into the tiapp.xml
	switch (this.deployType) {
		case 'production':
			this.minifyJS = true;
			this.encryptJS = true;
			this.allowDebugging = false;
			this.allowProfiling = false;
			this.includeAllTiModules = false;
			this.enableLogging = false;
			this.buildConfiguration = 'Release';
			break;

		case 'test':
			this.minifyJS = true;
			this.encryptJS = true;
			this.allowDebugging = true;
			this.allowProfiling = true;
			this.includeAllTiModules = false;
			this.enableLogging = true;
			this.buildConfiguration = 'Debug';
			break;

		case 'development':
		default:
			this.minifyJS = false;
			this.encryptJS = false;
			this.allowDebugging = true;
			this.allowProfiling = true;
			this.includeAllTiModules = true;
			this.enableLogging = true;
			this.buildConfiguration = 'Release';
	}

	if (cli.argv['skip-js-minify']) {
		this.minifyJS = false;
	}

	// check the default unit
	cli.tiapp.properties || (cli.tiapp.properties = {});
	cli.tiapp.properties['ti.ui.defaultunit'] || (cli.tiapp.properties['ti.ui.defaultunit'] = { type: 'string', value: 'system' });
	if (!/^system|px|dp|dip|mm|cm|in$/.test(cli.tiapp.properties['ti.ui.defaultunit'].value)) {
		logger.error(__('Invalid "ti.ui.defaultunit" property value "%s"', cli.tiapp.properties['ti.ui.defaultunit'].value) + '\n');
		logger.log(__('Valid units:'));
		'system,px,dp,dip,mm,cm,in'.split(',').forEach(function (unit) {
			logger.log('  ' + unit.cyan);
		});
		logger.log();
		process.exit(1);
	}

	// check that the build directory is writeable
	// try to build under temp if the path is shorter and we have write access
	var tempBuildDir = path.join(os.tmpdir());
	logger.log(tempBuildDir);
	if ((tempBuildDir.length < this.buildDir.length) && appc.fs.isDirWritable(tempBuildDir)) {
		this.originalBuildDir = this.buildDir;
		this.buildDir = path.join(tempBuildDir, path.basename(this.projectDir)); // build under temp!
	} else {
		this.originalBuildDir = null;
	}
	var buildDir = path.join(cli.argv['project-dir'], 'build');
	if (fs.existsSync(buildDir)) {
		if (!appc.fs.isDirWritable(buildDir)) {
			logger.error(__('The build directory is not writeable: %s', buildDir) + '\n');
			logger.log(__('Make sure the build directory is writeable and that you have sufficient free disk space.') + '\n');
			process.exit(1);
		}
	} else if (!appc.fs.isDirWritable(cli.argv['project-dir'])) {
		logger.error(__('The project directory is not writeable: %s', cli.argv['project-dir']) + '\n');
		logger.log(__('Make sure the project directory is writeable and that you have sufficient free disk space.') + '\n');
		process.exit(1);
	}

	// make sure we have an icon
	if (!cli.tiapp.icon || !['Resources', 'Resources/windows'].some(function (p) {
		return fs.existsSync(cli.argv['project-dir'], p, cli.tiapp.icon);
	})) {
		cli.tiapp.icon = 'appicon.png';
	}

	return function (callback) {
		this.validateTiModules('windows', this.deployType, function (err, modules) {
			this.modules = modules.found;
			this.commonJsModules = [];

			// TODO: Windows specific module stuff, if needed

			modules.found.forEach(function (module) {
				if (module.platform.indexOf('commonjs') != -1) {
					this.commonJsModules.push(module);
				}

				// TODO: more Windows specific module stuff, if needed

				// scan the module for any CLI hooks
				cli.scanHooks(path.join(module.modulePath, 'hooks'));
			});

			callback();
		}.bind(this));
	}.bind(this);
};

/**
 * Performs the build operations.
 *
 * @param {Object} logger - The logger instance.
 * @param {Object} config - The Titanium CLI config instance.
 * @param {Object} cli - The Titanium CLI instance.
 * @param {Function} finished - A function to call when the build has finished or errored.
 */
WindowsBuilder.prototype.run = function run(logger, config, cli, finished) {
    Builder.prototype.run.apply(this, arguments);

    appc.async.series(this, [
        function (next) {
            cli.emit('build.pre.construct', this, next);
        },

        'doAnalytics',
        'initialize',
        'loginfo',
        'computeHashes',
        'readBuildManifest',
        'checkIfNeedToRecompile',

        function (next) {
            cli.emit('build.pre.compile', this, next);
        },

        'checkAppJs',
        'copyResources',
        'generateI18N',
		'generateNativeWrappers',
        'generateCmakeList',
        'runCmake',
        'compileApp',
        'writeBuildManifest',
        'copyResultsToProject',

        function (next) {
            // now that the app is built, if we're going to do some logging, then we print how long the app took so far
            if (!this.buildOnly && (this.target === 'wp-device' || this.target === 'wp-emulator')) {
                var delta = appc.time.prettyDiff(this.cli.startTime, Date.now());
                this.logger.info(__('Finished building the application in %s', delta.cyan));
            }

            cli.emit('build.post.compile', this, next);
        },

        function (next) {
            cli.emit('build.finalize', this, next);
        }
    ], finished);
};

/**
 * Creates the Titanium CLI analytics event for the build. The sending of this
 * event is done by the Titanium CLI after the build has finished.
 *
 * @param {Function} next - A function to call after the analytics event has been created.
 */
WindowsBuilder.prototype.doAnalytics = function doAnalytics(next) {
	var eventName = 'windows.' + this.target,
		tiapp = this.cli.tiapp;

	if (this.target === 'dist-phonestore') {
		eventName = "windows.distribute.phonestore";
	} else if (this.target === 'dist-winstore') {
		eventName = "windows.distribute.winstore";
	} else if (this.allowDebugging && this.cli.argv['debug-host']) {
		eventName += '.debug';
	} else if (this.allowProfiling && this.cli.argv['profiler-host']) {
		eventName += '.profile';
	} else {
		eventName += '.run';
	}

	this.cli.addAnalyticsEvent(eventName, {
		dir: this.projectDir,
		name: tiapp.name,
		publisher: tiapp.publisher,
		url: tiapp.url,
		image: tiapp.icon,
		appid: tiapp.id,
		description: tiapp.description,
		type: this.cli.argv.type, // app or module
		guid: tiapp.guid,
		version: tiapp.version,
		copyright: tiapp.copyright,
		date: (new Date()).toDateString()
	});

	next();
};

/**
 * Initializes common build settings that will be available to build hooks.
 *
 * @param {Function} next - A function to call after the builder object has been initialized.
 */
WindowsBuilder.prototype.initialize = function initialize(next) {
	var argv = this.cli.argv;

	this.buildOnly    = argv['build-only'];
	this.debugHost    = this.allowDebugging && argv['debug-host'];
	this.profilerHost = this.allowProfiling && argv['profiler-host'];
	this.deviceId     = argv['device-id'];

	// cmake
	this.cmakeDir     = path.resolve(__dirname, '..', 'vendor', 'cmake');
	this.cmake        = path.join(this.cmakeDir, 'bin', 'cmake.exe');
	if (this.target == 'wp-emulator' || this.target == 'wp-device' || this.target == 'dist-phonestore') {
		if (this.target == 'wp-device' || this.target == 'dist-phonestore') {
			this.cmakeArch = 'ARM';
		} else {
			this.cmakeArch = 'Win32';
		}
		this.cmakePlatform = 'WindowsPhone';
		this.cmakePlatformAbbrev = 'wp';
	} else {
		this.cmakeArch = 'Win32';
		this.cmakePlatform = 'WindowsStore';
		this.cmakePlatformAbbrev = 'ws';
	}
	this.arch = this.cmakeArch == 'Win32' ? 'x86' : this.cmakeArch;
	this.cmakeTarget  = this.cmakePlatformAbbrev +'.' + this.arch;

	// directories
	// FIXME If we're building to temp, we need to copy the build results back over to the original build dir!
	this.outputDir             = argv['output-dir'] ? appc.fs.resolvePath(argv['output-dir']) : null;
	this.buildSrcDir		   = path.join(this.buildDir, 'src'); // Where the src files go
	this.cmakeTargetDir		   = path.join(this.buildDir, this.cmakeTarget); // where cmake generates the VS solution
	this.buildTargetAssetsDir  = path.join(this.buildDir, 'Assets');
	this.buildTargetStringsDir = path.join(this.buildDir, 'Strings');

	// files
	this.buildManifestFile = path.join(this.buildDir, 'build-manifest.json');
	this.cmakeListFile = path.join(this.buildDir, 'CMakeLists.txt'); // lives above the buildSrcDir

	next();
};

/**
 * Displays information about the build settings.
 *
 * @param {Function} next - A function to call after the build settings have been logged.
 */
WindowsBuilder.prototype.loginfo = function loginfo(next) {
	switch (this.target) {
		// windows phone targets
		case 'wp-emulator':
			this.logger.info(this.buildOnly
				? __('Building for Windows Phone emulator')
				: __('Building for Windows Phone emulator: %s', this.deviceId.cyan)
			);
			break;
		case 'wp-device':
			this.logger.info(this.buildOnly
				? __('Building for Windows Phone device: %s', this.deviceId.cyan)
				: __('Building for Windows Phone device: %s', this.deviceId.cyan)
			);
			break;
		case 'dist-phonestore':
			this.logger.info(__('Building for Windows Phone Store'));
			break;

		// windows store targets
		case 'ws-simulator':
			this.logger.info(__('Building Windows Simulator'));
			break;
		case 'ws-local':
			this.logger.info(__('Building local Windows machine'));
			break;
		case 'ws-remote':
			this.logger.info(__('Building remote Windows machine'));
			break;
		case 'dist-winstore':
			this.logger.info(__('Building for Windows App Store'));
			break;
	}

	if (this.buildOnly) {
		this.logger.info(__('Performing build only'));
	}

	this.logger.debug(__('Titanium SDK Windows directory: %s', this.platformPath.cyan));
	this.logger.info(__('Deploy type: %s', this.deployType.cyan));

	if (this.debugHost) {
		this.logger.info(__('Debugging enabled via debug host: %s', String(this.debugHost).cyan));
	} else {
		this.logger.info(__('Debugging disabled'));
	}

	if (this.profilerHost) {
		this.logger.info(__('Profiler enabled via profiler host: %s', String(this.profilerHost).cyan));
	} else {
		this.logger.info(__('Profiler disabled'));
	}

	next();
};

/**
 * Generate hashes of modules and properties from the tiapp.xml so we can detect
 * changes and force a rebuild.
 *
 * @param {Function} next - A function to call when once the hashes have been computed
 */
WindowsBuilder.prototype.computeHashes = function computeHashes(next) {
	// modules
	this.modulesHash = !Array.isArray(this.tiapp.modules) ? '' : this.hash(this.tiapp.modules.filter(function (m) {
		return !m.platform || /^windows|commonjs$/.test(m.platform);
	}).map(function (m) {
		return m.id + ',' + m.platform + ',' + m.version;
	}).join('|'));

	// properties
	this.propertiesHash = this.hash(this.tiapp.properties ? JSON.stringify(this.tiapp.properties) : '');

	next();
};

/**
 * Reads the build manifest, if exists, from the previous build so that we can
 * detect changes and force a rebuild.
 *
 * @param {Function} next - A function to call after the build manifest has been read.
 */
WindowsBuilder.prototype.readBuildManifest = function readBuildManifest(next) {
	// read the build manifest from the last build, if exists, so we
	// can determine if we need to do a full rebuild
	this.buildManifest = {};

	if (fs.existsSync(this.buildManifestFile)) {
		try {
			this.buildManifest = JSON.parse(fs.readFileSync(this.buildManifestFile)) || {};
		} catch (e) {}
	}

	next();
};

/**
 * Runs a series of checks to see if the build state has changed and a rebuild must
 * be performed.
 *
 * @returns {Boolean} Returns true if a rebuild is needed.
 */
WindowsBuilder.prototype.checkIfShouldForceRebuild = function checkIfShouldForceRebuild() {
	var manifest = this.buildManifest;

	if (this.cli.argv.force) {
		this.logger.info(__('Forcing rebuild: %s flag was set', '--force'.cyan));
		return true;
	}

	if (!fs.existsSync(this.buildManifestFile)) {
		this.logger.info(__('Forcing rebuild: %s does not exist', this.buildManifestFile.cyan));
		return true;
	}

	// check if the target changed
	if (this.target !== manifest.target) {
		this.logger.info(__('Forcing rebuild: target changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.target));
		this.logger.info('  ' + __('Now: %s', this.target));
		return true;
	}

	// check if the deploy type changed
	if (this.deployType !== manifest.deployType) {
		this.logger.info(__('Forcing rebuild: deploy type changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.deployType));
		this.logger.info('  ' + __('Now: %s', this.deployType));
		return true;
	}

	// if encryption is enabled, then we must recompile the java files
	if (this.encryptJS) {
		this.logger.info(__('Forcing rebuild: JavaScript files need to be re-encrypted'));
		return true;
	}

	// if encryptJS changed, then we need to recompile the java files
	if (this.encryptJS !== manifest.encryptJS) {
		this.logger.info(__('Forcing rebuild: JavaScript encryption flag changed'));
		this.logger.info('  ' + __('Was: %s', manifest.encryptJS));
		this.logger.info('  ' + __('Now: %s', this.encryptJS));
		return true;
	}

	// check if the titanium sdk paths are different
	if (this.platformPath !== manifest.platformPath) {
		this.logger.info(__('Forcing rebuild: Titanium SDK path changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.platformPath));
		this.logger.info('  ' + __('Now: %s', this.platformPath));
		return true;
	}

	// check the git hashes are different
	if (!manifest.gitHash || manifest.gitHash !== ti.manifest.githash) {
		this.logger.info(__('Forcing rebuild: githash changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.gitHash));
		this.logger.info('  ' + __('Now: %s', ti.manifest.githash));
		return true;
	}

	// check if the modules hashes are different
	if (this.modulesHash !== manifest.modulesHash) {
		this.logger.info(__('Forcing rebuild: modules hash changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.modulesHash));
		this.logger.info('  ' + __('Now: %s', this.modulesHash));
		return true;
	}

	if (this.modulesManifestHash !== manifest.modulesManifestHash) {
		this.logger.info(__('Forcing rebuild: module manifest hash changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.modulesManifestHash));
		this.logger.info('  ' + __('Now: %s', this.modulesManifestHash));
		return true;
	}

	if (this.modulesNativeHash !== manifest.modulesNativeHash) {
		this.logger.info(__('Forcing rebuild: native modules hash changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.modulesNativeHash));
		this.logger.info('  ' + __('Now: %s', this.modulesNativeHash));
		return true;
	}

	if (this.modulesBindingsHash !== manifest.modulesBindingsHash) {
		this.logger.info(__('Forcing rebuild: native modules bindings hash changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.modulesBindingsHash));
		this.logger.info('  ' + __('Now: %s', this.modulesBindingsHash));
		return true;
	}

	// next we check if any tiapp.xml values changed so we know if we need to reconstruct the main.m
	if (this.tiapp.name !== manifest.name) {
		this.logger.info(__('Forcing rebuild: tiapp.xml project name changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.name));
		this.logger.info('  ' + __('Now: %s', this.tiapp.name));
		return true;
	}

	if (this.tiapp.id !== manifest.id) {
		this.logger.info(__('Forcing rebuild: tiapp.xml app id changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.id));
		this.logger.info('  ' + __('Now: %s', this.tiapp.id));
		return true;
	}

	if (!this.tiapp.analytics !== !manifest.analytics) {
		this.logger.info(__('Forcing rebuild: tiapp.xml analytics flag changed since last build'));
		this.logger.info('  ' + __('Was: %s', !!manifest.analytics));
		this.logger.info('  ' + __('Now: %s', !!this.tiapp.analytics));
		return true;
	}
	if (this.tiapp.publisher !== manifest.publisher) {
		this.logger.info(__('Forcing rebuild: tiapp.xml publisher changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.publisher));
		this.logger.info('  ' + __('Now: %s', this.tiapp.publisher));
		return true;
	}

	if (this.tiapp.url !== manifest.url) {
		this.logger.info(__('Forcing rebuild: tiapp.xml url changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.url));
		this.logger.info('  ' + __('Now: %s', this.tiapp.url));
		return true;
	}

	if (this.tiapp.version !== manifest.version) {
		this.logger.info(__('Forcing rebuild: tiapp.xml version changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.version));
		this.logger.info('  ' + __('Now: %s', this.tiapp.version));
		return true;
	}

	if (this.tiapp.description !== manifest.description) {
		this.logger.info(__('Forcing rebuild: tiapp.xml description changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.description));
		this.logger.info('  ' + __('Now: %s', this.tiapp.description));
		return true;
	}

	if (this.tiapp.copyright !== manifest.copyright) {
		this.logger.info(__('Forcing rebuild: tiapp.xml copyright changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.copyright));
		this.logger.info('  ' + __('Now: %s', this.tiapp.copyright));
		return true;
	}

	if (this.tiapp.guid !== manifest.guid) {
		this.logger.info(__('Forcing rebuild: tiapp.xml guid changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.guid));
		this.logger.info('  ' + __('Now: %s', this.tiapp.guid));
		return true;
	}

	if (this.tiapp.icon !== manifest.icon) {
		this.logger.info(__('Forcing rebuild: tiapp.xml icon changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.icon));
		this.logger.info('  ' + __('Now: %s', this.tiapp.icon));
		return true;
	}

	if (this.propertiesHash !== manifest.propertiesHash) {
		this.logger.info(__('Forcing rebuild: tiapp.xml properties changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.propertiesHash));
		this.logger.info('  ' + __('Now: %s', this.propertiesHash));
		return true;
	}

	return false;
};

/**
 * Checks if we need to rebuild the app and if so, deletes the previous build files.
 *
 * @param {Function} next - A function to call after checking if the app needs to be rebuilt.
 */
WindowsBuilder.prototype.checkIfNeedToRecompile = function checkIfNeedToRecompile(next) {
	// check if we need to do a rebuild
	this.forceRebuild = this.checkIfShouldForceRebuild();

	if (this.forceRebuild && fs.existsSync(this.buildDir)) {
		wrench.rmdirSyncRecursive(this.buildDir);
	}

	// now that we've read the build manifest, delete it so if this build
	// becomes incomplete, the next build will be a full rebuild
	fs.existsSync(this.buildManifestFile) && fs.unlinkSync(this.buildManifestFile);

	next();
};

/**
 * Checks that the app.js exists. This has to be done after the "build.pre.compile" event
 * has fired. This gives build hooks such as Alloy the ability to generate an app.js.
 *
 * @param {Function} next - A function to call after the app.js has been verified to exist.
 */
WindowsBuilder.prototype.checkAppJs = function checkAppJs(next) {
	// Make sure we have an app.js. This used to be validated in validate(), but since plugins like
	// Alloy generate an app.js, it may not have existed during validate(), but should exist now
	// that build.pre.compile was fired.
	ti.validateAppJsExists(this.projectDir, this.logger, 'windows');

	next();
};

/**
 * Copies files from the project's "Resources", "Resources\windows", and "platform\windows"
 * directories into the generated Visual Studio project.
 *
 * @param {Function} next - A function to call after the files have been copied.
 */
WindowsBuilder.prototype.copyResources = function copyResources(next) {
	/*
	TODO: This function is supposed to copy the files from the "Resources", "Resources\windows",
	      and "platform\windows" directories into the generated Visual Studio project.

		  Files should be copied into the this.buildTargetAssetsDir directory.

	      This is commented out because it actually does more than just copies files.

	      It also:

	        * makes sure an app icon exists or copies the default one from the Titanium SDK
	        * makes sure a splash screen exists or copies the default one from the Titanium SDK
	          - this may not be necessary on Windows Phone
	        * when copying an HTML file, scan it for all .js files and exclude them from being
	          encrypted
	          - this may not be necessary if you can override the WebView's resource loader and
	            return the correct .js file
	        * css files are minified with the clean-css Node.js module
	        * all JavaScript files discovered, but not copied. we later iterate over this distinct
	          list of js files and call jsanalyze.analyzeJsFile() to be scan for Titanium
	          namespaces (so we can determine which modules we need to compile in) and minify the
	          js code
	          - when encrypting js is enabled (test or production build), then we call titanium_prep

	       Titanium Windows may support encrypting more than just JavaScript files. If that is
	       the case, scan the Resources diretory for files to be encrypted and build a list. Only
	       copy files you are not going to encrypt. Then you'll need to perform the actual
	       encryption at the end of the last callback in this function.
	*/

	var ignoreDirs = this.ignoreDirs,
		ignoreFiles = this.ignoreFiles,
		extRegExp = /\.(\w+)$/,
		jsFiles = {},
		jsFilesToEncrypt = this.jsFilesToEncrypt = [],
		htmlJsFiles = this.htmlJsFiles = {},
		_t = this;

	function copyDir(opts, callback) {
		if (opts && opts.src && fs.existsSync(opts.src) && opts.dest) {
			opts.origSrc = opts.src;
			opts.origDest = opts.dest;
			recursivelyCopy(opts.src, opts.dest, opts.ignoreRootDirs, opts, callback);
		} else {
			callback();
		}
	}

	function copyFile(from, to, next) {
		var d = path.dirname(to);
		fs.existsSync(d) || wrench.mkdirSyncRecursive(d);

		if (fs.existsSync(to)) {
			_t.logger.warn(__('Overwriting file %s', to.cyan));
		}

		this.logger.debug(__('Copying %s => %s', from.cyan, to.cyan));
		if (next) {
			fs.readFile(from, function (err, data) {
				if (err) throw err;
				fs.writeFile(to, data, next);
			});
		} else {
			fs.writeFileSync(to, fs.readFileSync(from));
		}
	}

	function recursivelyCopy(src, dest, ignoreRootDirs, opts, done) {
		var files;
		if (fs.statSync(src).isDirectory()) {
			files = fs.readdirSync(src);
		} else {
			// we have a file, so fake a directory listing
			files = [ path.basename(src) ];
			src = path.dirname(src);
		}

		async.whilst(
			function () {
				return files.length;
			},

			function (next) {
				var filename = files.shift(),
					destDir = dest,
					from = path.join(src, filename),
					to = path.join(destDir, filename);

				// check that the file actually exists
				if (!fs.existsSync(from)) return next();

				var isDir = fs.statSync(from).isDirectory();

				// check if we are ignoring this file
				if ((isDir && ignoreRootDirs && ignoreRootDirs.indexOf(filename) !== -1) || (isDir ? ignoreDirs : ignoreFiles).test(filename)) {
					_t.logger.debug(__('Ignoring %s', from.cyan));
					return next();
				}

				// if this is a directory, recurse
				if (isDir) return recursivelyCopy.call(_t, from, path.join(destDir, filename), null, opts, next);

				// we have a file, now we need to see what sort of file

				// if the destination directory does not exists, create it
				fs.existsSync(destDir) || wrench.mkdirSyncRecursive(destDir);

				var ext = filename.match(extRegExp);

				switch (ext && ext[1]) {
					case 'css':
						// if we encounter a css file, check if we should minify it
						if (_t.minifyCSS) {
							_t.logger.debug(__('Copying and minifying %s => %s', from.cyan, to.cyan));
							fs.readFile(from, function (err, data) {
								if (err) throw err;
								fs.writeFile(to, cleanCSS.process(data.toString()), next);
							});
						} else {
							copyFile.call(_t, from, to, next);
						}
						break;

					case 'html':
						// find all js files referenced in this html file
						var relPath = from.replace(opts.origSrc, '').replace(/\\/g, '/').replace(/^\//, '').split('/');
						relPath.pop(); // remove the filename
						relPath = relPath.join('/');
						jsanalyze.analyzeHtmlFile(from, relPath).forEach(function (file) {
							htmlJsFiles[file] = 1;
						});

						_t.cli.createHook('build.windows.copyResource', _t, function (from, to, cb) {
							copyFile.call(_t, from, to, cb);
						})(from, to, next);
						break;

					case 'js':
						// track each js file so we can copy/minify later

						// we use the destination file name minus the path to the assets dir as the id
						// which will eliminate dupes
						var id = to.replace(opts.origDest, '').replace(/\\/g, '/').replace(/^\//, '');

						if (!jsFiles[id] || !opts || !opts.onJsConflict || opts.onJsConflict(from, to, id)) {
							jsFiles[id] = from;
						}

						next();
						break;

					default:
						// normal file, just copy it into the build/windows/Assets directory
						_t.cli.createHook('build.windows.copyResource', _t, function (from, to, cb) {
							copyFile.call(_t, from, to, cb);
						})(from, to, next);
				}
			},

			done
		);
	}

	var tasks = [
		// first task is to copy all files in the Resources directory, but ignore
		// any directory that is the name of a known platform
		function (cb) {
			var src = path.join(this.projectDir, 'Resources');
			copyDir.call(this, {
				src: src,
				dest: this.buildTargetAssetsDir,
				ignoreRootDirs: ti.availablePlatformsNames
			}, cb);
		},

		// next copy all files from the Windows specific Resources directory
		function (cb) {
			var src = path.join(this.projectDir, 'Resources', 'windows');
			copyDir.call(this, {
				src: src,
				dest: this.buildTargetAssetsDir
			}, cb);
		},

		// next copy template files for CMake/MSBuild FIXME Move these into subdir so we copy only ones we need!
		function (cb) {
			var src = path.join(this.platformPath, 'templates', 'build');
			copyDir.call(this, {
				src: src,
				dest: this.buildDir // throw into top-level build dir
			}, cb);
		},

		// Copy cmake folder over, with our helper scripts to find the bundled dependency libs
		function (cb) {
			var src = path.join(this.platformPath, 'templates', 'build', 'cmake');
			copyDir.call(this, {
				src: src,
				dest: path.join(this.buildDir, 'cmake')
			}, cb);
		},

		// Copy TitaniumKit and HAL dlls over into src folder
		function (cb) {
			var plat = this.target == 'ws-local' ? 'store' : 'phone';
			var src = path.join(this.platformPath, 'lib', 'TitaniumKit', plat, this.arch, 'TitaniumKit.dll');
			copyFile.call(this,
				src,
				path.join(this.buildDir, 'lib', 'TitaniumKit.dll'),
			cb);
		},

		function (cb) {
			var plat = this.target == 'ws-local' ? 'store' : 'phone';
			var src = path.join(this.platformPath, 'lib', 'HAL', plat, this.arch, 'HAL.dll');
			copyFile.call(this,
				src,
				path.join(this.buildDir, 'lib', 'HAL.dll'),
			cb);
		}
	];

	// copy all commonjs modules
	this.commonJsModules.forEach(function (module) {
		// copy the main module
		tasks.push(function (cb) {
			copyDir.call(this, {
				src: module.libFile,
				dest: this.buildTargetAssetsDir,
				onJsConflict: function (src, dest, id) {
					this.logger.error(__('There is a project resource "%s" that conflicts with a CommonJS module', id));
					this.logger.error(__('Please rename the file, then rebuild') + '\n');
					process.exit(1);
				}.bind(this)
			}, cb);
		});

		// copy the assets
		tasks.push(function (cb) {
			copyDir.call(this, {
				src: path.join(module.modulePath, 'assets'),
				dest: path.join(this.buildTargetAssetsDir, 'modules', module.id)
			}, cb);
		});
	});

	this.modules.forEach(function (module) {
		// TODO: copy any module specific resources here
	}, this);

	var platformPaths = [];
	// WARNING! This is pretty dangerous, but yes, we're intentionally copying
	// every file from platform/windows and all modules into the build dir
	this.modules.forEach(function (module) {
		platformPaths.push(path.join(module.modulePath, 'platform', 'windows'));
	});
	platformPaths.push(path.join(this.projectDir, this.cli.argv['platform-directory'] || 'platform', 'windows'));
	platformPaths.forEach(function (dir) {
		if (fs.existsSync(dir)) {
			tasks.push(function (cb) {
				copyDir.call(this, {
					src: dir,
					dest: this.buildDir
				}, cb);
			});
		}
	}, this);

	tasks.push(function (cb) {
		// fire a hook event so that hooks can copy additional resources
		this.cli.emit('build.windows.copyResources', this, cb);
	}.bind(this));

	appc.async.series(this, tasks, function (err, results) {
		var templateDir = path.join(this.platformPath, 'templates', 'app', 'default', 'template', 'Resources', 'windows');

		// if an app icon hasn't been copied, copy the default one
		var destIcon = path.join(this.buildTargetAssetsDir, this.tiapp.icon);
		if (!fs.existsSync(destIcon)) {
			copyFile.call(this, path.join(templateDir, 'appicon.png'), destIcon);
		}

		// copy js files into assets directory and minify if needed
		this.logger.info(__('Processing JavaScript files'));
		appc.async.series(this, Object.keys(jsFiles).map(function (id) {
			return function (done) {
				var from = jsFiles[id],
					to = path.join(this.buildTargetAssetsDir, id);

				if (htmlJsFiles[id]) {
					// this js file is referenced from an html file, so don't minify or encrypt
					return copyFile.call(this, from, to, done);
				}

				// we have a js file that may be minified or encrypted

				// if we're encrypting the JavaScript, copy the files to the assets dir
				// for processing later
				if (this.encryptJS) {
					to = path.join(this.buildTargetAssetsDir, id);
					jsFilesToEncrypt.push(id);
				}

				try {
					this.cli.createHook('build.windows.copyResource', this, function (from, to, cb) {
						// parse the AST
						var r = jsanalyze.analyzeJsFile(from, { minify: this.minifyJS });

						// we want to sort by the "to" filename so that we correctly handle file overwriting
						this.tiSymbols[to] = r.symbols;

						var dir = path.dirname(to);
						fs.existsSync(dir) || wrench.mkdirSyncRecursive(dir);

						if (this.minifyJS) {
							this.logger.debug(__('Copying and minifying %s => %s', from.cyan, to.cyan));

							this.cli.createHook('build.windows.compileJsFile', this, function (r, from, to, cb2) {
								fs.writeFile(to, r.contents, cb2);
							})(r, from, to, cb);
						} else {
							// we've already read in the file, so just write the original contents
							this.logger.debug(__('Copying %s => %s', from.cyan, to.cyan));
							fs.writeFile(to, r.contents, cb);
						}
					})(from, to, done);
				} catch (ex) {
					ex.message.split('\n').forEach(this.logger.error);
					this.logger.log();
					process.exit(1);
				}
			};
		}), function () {

			// write the properties file
			var appPropsFile = path.join(this.buildTargetAssetsDir, '_app_props_.json'),
				props = {};
			Object.keys(this.tiapp.properties).forEach(function (prop) {
				props[prop] = this.tiapp.properties[prop].value;
			}, this);
			fs.writeFileSync(
				appPropsFile,
				JSON.stringify(props)
			);
			this.encryptJS && jsFilesToEncrypt.push('_app_props_.json');

			// write the app info file
			var appInfoFile = path.join(this.buildTargetAssetsDir, '_app_info_.json'),
				appInfo = 
				{
					deployType: this.deployType,
					name: this.tiapp.name,
					id: this.tiapp.id,
					analytics: this.tiapp.analytics,
					publisher: this.tiapp.publisher,
					url: this.tiapp.url,
					version: this.tiapp.version,
					description: this.tiapp.description,
					copyright: this.tiapp.copyright,
					guid: this.tiapp.guid
				};
			fs.writeFileSync(
				appInfoFile,
				JSON.stringify(appInfo)
			);
			this.encryptJS && jsFilesToEncrypt.push('_app_info_.json');

			if (!jsFilesToEncrypt.length) {
				// nothing to encrypt, continue
				return next();
			}

			// TODO: Titanium Windows will probably have a different encryption mechanism... replace the below code with
			//       whatever encryption steps are necessary.

			next();
		});
	});
};

/**
 * Generates the i18n string resource files and adds them to the Visual Studio project.
 *
 * @param {Function} next - A function to call after the i18n files have been generated.
 */
WindowsBuilder.prototype.generateI18N = function generateI18N(next) {
	this.logger.info(__('Generating i18n files'));

	var data = i18n.load(this.projectDir, this.logger, {
			ignoreDirs: this.ignoreDirs,
			ignoreFiles: this.ignoreFiles
		}),
		template = fs.readFileSync(path.join(this.platformPath, 'templates', 'build', 'Resources.resw')).toString();

	data.en || (data.en = {});
	data.en.app || (data.en.app = {});
	data.en.app.appname || (data.en.app.appname = this.tiapp.name);

	Object.keys(data).forEach(function (locale) {
		var destDir = path.join(this.buildTargetStringsDir, locale),
			dest = path.join(destDir, 'Resources.resw'),
			dom = new DOMParser().parseFromString(template, 'text/xml'),
			root = dom.documentElement;

		function addString(name, value) {
			var dataNode = dom.createElement('data');
			dataNode.setAttribute('name', name);
			dataNode.setAttribute('xml:space', 'preserve');

			var valueNode = dom.createElement('value');
			valueNode.appendChild(dom.createTextNode(value));

			dataNode.appendChild(valueNode);
			root.appendChild(dataNode);
		}

		// process app_name first
		addString('app_name', data[locale].app && data[locale].app.appname || this.tiapp.name);

		data[locale].strings && Object.keys(data[locale].strings).forEach(function (name) {
			if (name !== 'appname') {
				addString(name, data[locale].strings[name]);
			}
		});

		this.logger.debug(__('Writing %s strings => %s', locale.cyan, dest.cyan));
		fs.existsSync(destDir) || wrench.mkdirSyncRecursive(destDir);
		fs.writeFileSync(dest, '<?xml version="1.0" encoding="UTF-8"?>\n' + dom.documentElement.toString());

		// TODO: update the Visual Studio project to add the generated Resources.resw file (i.e. "dest")
	}, this);

	next();
};

/**
 * Generates the native type wrappers and adds them to the Visual Studio project.
 *
 * @param {Function} next - A function to call after the native types have been generated.
 */
WindowsBuilder.prototype.generateNativeWrappers = function generateNativeWrappers(next) {
	// FIXME Walk the user's JS files to generate the listing of native types we need!
	var seeds = [
		"Windows.UI.Xaml.Window",
		"Windows.UI.Colors",
		"Windows.UI.Xaml.Media.SolidColorBrush",
		"Windows.UI.Xaml.Controls.Canvas",
		"Windows.UI.Xaml.Controls.TextBlock",
		'Windows.UI.Xaml.Controls.Frame',
		'Windows.UI.Xaml.Controls.Page'
	];
	this.logger.info(__('Generating Native Type Wrappers'));

	nativeTypeGenerator.generate(path.join(this.buildDir, 'Native'), seeds, next);
};

/**
 * Generates a cmakelist to define what cmake is doing to generate the VS project.
 *
 * @param {Function} next - A function to call after generating the cmakelist.txt file.
 */
WindowsBuilder.prototype.generateCmakeList = function generateCmakeList(next) {
	var assetList = [],
		sourceGroups = {};

	this.logger.info(__('Writing CMakeLists.txt: %s', this.cmakeListFile.cyan));
	// TODO If forceBuild is false AND no assets have changed, then we can skip this and the cmake step, I think!
	function getFilesRecursive (folder) {
	    var fileContents = fs.readdirSync(folder),
	        fileTree = [],
	        stats;

	    fileContents.forEach(function (fileName) {
	    	var child = path.join(folder, fileName);
	        stats = fs.lstatSync(child);

	        if (stats.isDirectory()) {
	            getFilesRecursive(child).forEach(function (file) {
	            	fileTree.push(fileName + '/' + file);  // cmake likes unix separators
	            });
	        } else {
	            fileTree.push(fileName);
	        }
	    });

	    return fileTree;
	}
	// Recursively read all files under Assets and populate the cmake listing with it.
	assetList = getFilesRecursive(this.buildTargetAssetsDir);
	assetList = assetList.map(function(filename) {
		return 'Assets/' + filename;  // cmake likes unix separators
	});

	// Generate source groups!
	// go through the asset list, and basically generate a group for each folder
	assetList.forEach(function (filepath) {
		// lop off Assets/
		var truncatedPath = filepath.substring(7);
		// drop the file basename?
		var folderName = path.dirname(truncatedPath);
		// now stick it in the mapping!
		var listing = sourceGroups[folderName] || [];
		listing.push(filepath);
		sourceGroups[folderName] = listing;
	});

	this.cli.createHook('build.windows.writeCMakeLists', this, function (manifest, cb) {
		fs.existsSync(this.buildDir) || wrench.mkdirSyncRecursive(this.buildDir);
		fs.existsSync(this.cmakeListFile) && fs.unlinkSync(this.cmakeListFile);
		fs.writeFile(this.cmakeListFile, manifest, cb);
	})(ejs.render(
		fs.readFileSync(
			path.resolve(this.platformPath, 'templates', 'build', 'CMakeLists.txt.ejs')
		).toString(),
		{
			projectName: this.cli.tiapp.name,
			windowsSrcDir: path.resolve(__dirname, '..', '..').replace(/\\/g, '/'), // cmake likes unix separators
			version: this.tiapp.version,
			assets: assetList.join('\n'),
			appId: this.cli.tiapp.id,
			sourceGroups: sourceGroups
		}
	), next);
};

/**
 * Runs cmake to generate a VS project.
 *
 * @param {Function} next - A function to call after generating the Visual Studio project.
 */
WindowsBuilder.prototype.runCmake = function runCmake(next) {
	this.logger.info(__('Running cmake at %s in directory %s', this.cmake.cyan, this.cmakeTargetDir.cyan));
	var _t = this,
		generatorName = 'Visual Studio 12 2013',
		p;

	if (this.cmakeArch == 'ARM') {
		generatorName += ' ARM';
	}

	fs.existsSync(this.cmakeTargetDir) || wrench.mkdirSyncRecursive(this.cmakeTargetDir);
	// Use spawn directly so we can pipe output as we go
	p = spawn(this.cmake,
		[
			'-G', generatorName,
			'-DCMAKE_SYSTEM_NAME=' + this.cmakePlatform,
			'-DCMAKE_SYSTEM_VERSION=' + this.wpsdk,
			'-DCMAKE_BUILD_TYPE=' + this.buildConfiguration,
			this.buildDir
		],
		{
			cwd: this.cmakeTargetDir
		});
	p.stdout.on('data', function (data) {
  		_t.logger.info(data.toString().trim());
	});
	p.stderr.on('data', function (data) {
  		_t.logger.warn(data.toString().trim());
	});
	p.on('close', function (code) {

		if (code != 0) {
			process.exit(1); // Exit with code from cmake?
		}

		next();
	});
};

/**
 * Compiles the generated Visual Studio project.
 *
 * @param {Function} next - A function to call after the Visual Studio project.
 */
WindowsBuilder.prototype.compileApp = function compileApp(next) {
	var _t = this;
		slnFile = path.resolve(this.cmakeTargetDir, this.cli.tiapp.name + '.sln'),
		vcxproj = path.resolve(this.cmakeTargetDir, this.cli.tiapp.name + '.vcxproj');
	this.logger.info(__('Running MSBuild on solution: %s', slnFile.cyan));

	// Modify the vcxproj to inject some properties, so we always bundle
	var modified = fs.readFileSync(vcxproj, 'utf8');
	fs.existsSync(vcxproj) && fs.renameSync(vcxproj, vcxproj + '.bak');
	// Only modify the one property group we care about!
	modified = modified.replace(/<\/PropertyGroup>\s*<ItemDefinitionGroup/m, '<AppxBundle>Always</AppxBundle><AppxBundlePlatforms>' + this.arch + '</AppxBundlePlatforms>$&');
	fs.writeFileSync(vcxproj, modified);

	// Use spawn directly so we can pipe output as we go
	// FIXME Edit windowslib to allow realtime output
	windowslib.detect(function (err, results) {
		if (err) {
			_t.logger.error(err.message || err.toString());
			_t.logger.log();
			process.exit(1);
		}

		var vsInfo = results.selectedVisualStudio,
			p;

		if (!vsInfo) {
			_t.logger.error(__('Unable to find a supported Visual Studio installation'));
			_t.logger.log();
			process.exit(1);
		}

		// Use spawn directly so we can pipe output as we go
		p = spawn(vsInfo.vcvarsall, [
			'&&', 'MSBuild', '/m', '/t:rebuild', '/p:Platform=' + _t.cmakeArch, '/p:Configuration=' + _t.buildConfiguration, slnFile
		]);
		p.stdout.on('data', function (data) {
  			_t.logger.info(data.toString().trim());
		});
		p.stderr.on('data', function (data) {
  			_t.logger.warn(data.toString().trim());
		});
		p.on('close', function (code) {

			if (code != 0) {
				process.exit(1); // Exit with code from msbuild?
			}

			next();
		});
	});
};

/**
 * Writes the build manifest file so subsequent builds will know if a rebuild is needed.
 *
 * @param {Function} next - A function to call after the build manifest has been written.
 */
WindowsBuilder.prototype.writeBuildManifest = function writeBuildManifest(next) {
	this.logger.info(__('Writing build manifest: %s', this.buildManifestFile.cyan));



	this.cli.createHook('build.windows.writeBuildManifest', this, function (manifest, cb) {
		fs.existsSync(this.buildDir) || wrench.mkdirSyncRecursive(this.buildDir);
		fs.existsSync(this.buildManifestFile) && fs.unlinkSync(this.buildManifestFile);
		fs.writeFile(this.buildManifestFile, JSON.stringify(this.buildManifest = manifest, null, '\t'), cb);
	})({
		target: this.target,
		deployType: this.deployType,
		platformPath: this.platformPath,
		modulesHash: this.modulesHash,
		modulesManifestHash: this.modulesManifestHash,
		modulesNativeHash: this.modulesNativeHash,
		modulesBindingsHash: this.modulesBindingsHash,
		gitHash: ti.manifest.githash,
		outputDir: this.outputDir,
		name: this.tiapp.name,
		id: this.tiapp.id,
		analytics: this.tiapp.analytics,
		publisher: this.tiapp.publisher,
		url: this.tiapp.url,
		version: this.tiapp.version,
		description: this.tiapp.description,
		copyright: this.tiapp.copyright,
		guid: this.tiapp.guid,
		icon: this.tiapp.icon,
		skipJSMinification: !!this.cli.argv['skip-js-minify'],
		encryptJS: this.encryptJS,
		propertiesHash: this.propertiesHash
	}, next);
};

// Copy to original location!
/**
 * Copies the build directory back to the project's build directory if we compiled in temp.
 *
 * @param {Function} next - A function to call after the build manifest has been written.
 */
WindowsBuilder.prototype.copyResultsToProject = function copyResultsToProject(next) {
	if (this.originalBuildDir) {
		this.logger.info(__('Copying results back to project build directory'));
		// if already exists, wipe it
		fs.existsSync(this.originalBuildDir) && wrench.rmdirSyncRecursive(this.originalBuildDir);
		// make sure destination exists
		fs.existsSync(this.originalBuildDir) || wrench.mkdirSyncRecursive(this.originalBuildDir);
		// Now copy this.buildDir into this.originalBuildDir
		wrench.copyDirSyncRecursive(this.buildDir, this.originalBuildDir);
	}
	next();
};

// create the builder instance and expose the public api
(function (WindowsBuilder) {
	exports.config   = WindowsBuilder.config.bind(WindowsBuilder);
	exports.validate = WindowsBuilder.validate.bind(WindowsBuilder);
	exports.run      = WindowsBuilder.run.bind(WindowsBuilder);
}(new WindowsBuilder(module)));
