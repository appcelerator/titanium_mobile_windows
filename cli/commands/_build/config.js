var appc = require('node-appc'),
	Builder = require('titanium-sdk/lib/builder'),
	windowslib = require('windowslib'),
	windowsPackageJson = appc.pkginfo.package(module);

var configOptions = require('./config/_index');

/*
 Public API.
 */
exports.mixin = mixin;

/*
 Implementation.
 */
function mixin(WindowsBuilder) {
	WindowsBuilder.prototype.config = config;
	for (var key in configOptions) {
		if (configOptions.hasOwnProperty(key)) {
			WindowsBuilder.prototype[key] = configOptions[key];
		}
	}
}

/**
 * Defines the command line options for the build command.
 *
 * @param {Object} logger - The logger instance.
 * @param {Object} config - The Titanium CLI config instance.
 * @param {Object} cli - The Titanium CLI instance.
 *
 * @returns {Function} A function to be called async which returns the actual configuration.
 */
function config(logger, config, cli) {
	Builder.prototype.config.apply(this, arguments);

	var target = (cli.argv['target'] || cli.argv['T']);

	this.windowslibOptions = {
		powershell: config.get('windows.executables.powershell'),
		pvk2pfx: config.get('windows.executables.pvk2pfx'),
		preferredWindowsPhoneSDK: config.get('windows.wpsdk.selectedVersion'),
		preferredWindowsSDK: config.get('windows.sdk.selectedVersion'),
		preferredVisualStudio: config.get('windows.visualstudio.selectedVersion'),
		supportedMSBuildVersions: windowsPackageJson.vendorDependencies['msbuild'],
		supportedVisualStudioVersions: windowsPackageJson.vendorDependencies['visual studio'],
		supportedWindowsPhoneSDKVersions: windowsPackageJson.vendorDependencies['windows phone sdk'],
		tasklist: config.get('windows.executables.tasklist'),
		skipWpTool: cli.argv['build-only'] || (target !== 'wp-device' && target !== 'wp-emulator' && target !== undefined)
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

	function shouldForceProduction(argv) {
		return (argv['target'] === 'dist-phonestore' || argv['target'] === 'dist-winstore');
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

		// force production build when you package the app
		if (shouldForceProduction(cli.argv)) {
			cli.argv['deploy-type'] = 'production';
		}
	
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
						'pfx-password': this.configOptionPFXPassword(450),
						'profiler-host': {
							hidden: true
						},
						'target': this.configOptionTarget(110),
						'vs-target': this.configOptionVisualStudioTarget(120),
						'win-publisher-id': this.configOptionWindowsPublisherID(210),
						'wp-publisher-guid': this.configOptionWPPublisherGUID(220),
						'wp-product-guid': this.configOptionProductID(230),
						'win-product-guid': this.configOptionProductID(240),
						'win-sdk': this.configOptionSDK(300),
						'wp-sdk': this.configOptionSDK(310),
						'win-cert': this.configOptionCert(400),
						'ws-cert': this.configOptionCert(410)
					}
				});
			})(function (err, result) {
				finished(result);
			});
		}.bind(this));
	}.bind(this);
}