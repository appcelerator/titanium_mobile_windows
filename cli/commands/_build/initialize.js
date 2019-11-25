var appc = require('node-appc'),
	fs = require('fs'),
	os = require('os'),
	path = require('path'),
	ti = require('node-titanium-sdk'),
	__ = appc.i18n(__dirname).__;

/*
 Public API.
 */
exports.mixin = mixin;

/*
 Implementation.
 */
function mixin(WindowsBuilder) {
	WindowsBuilder.prototype.initialize = initialize;
}

/**
 * Initializes common build settings that will be available to build hooks.
 *
 * @param {Function} next - A function to call after the builder object has been initialized.
 */
function initialize(next) {
	var argv = this.cli.argv;

	this.buildOnly = argv['build-only'];
	this.debugHost = this.allowDebugging && argv['debug-host'];
	this.profilerHost = this.allowProfiling && argv['profiler-host'];
	this.deviceId = argv['device-id'];

	// cmake
	this.cmakeDir = path.resolve(__dirname, '..', '..', 'vendor', 'cmake');
	this.cmake = path.join(this.cmakeDir, 'bin', 'cmake.exe');
	if (this.target == 'wp-emulator' || this.target == 'wp-device' || this.target == 'dist-phonestore') {
		if (this.target == 'wp-device' || this.target == 'dist-phonestore') {
			this.cmakeArch = 'ARM';
		} else {
			this.cmakeArch = 'Win32';
		}
		this.cmakePlatform = 'WindowsPhone';
		this.cmakePlatformAbbrev = 'phone';
	} else {
		this.cmakeArch = 'Win32';
		this.cmakePlatform = 'WindowsStore';
		this.cmakePlatformAbbrev = 'store';
	}
	if (this.wpsdk == '10.0') {
		this.cmakePlatform = 'WindowsStore';
		this.cmakePlatformAbbrev = 'win10';
	}
	this.arch = this.cmakeArch == 'Win32' ? 'x86' : this.cmakeArch;
	this.cmakeTarget = this.cmakePlatformAbbrev + '.' + this.arch;

	// Detect CMake generator name: e.g. 12.0 -> Visual Studio 12 2013
	// because there's no specific way to auto-detect "year" component
	var supportedCMakeGenerators = {
		'12.0': 'Visual Studio 12 2013',
		'14.0': 'Visual Studio 14 2015',
		'15.0': 'Visual Studio 15 2017',
	};

	var vstarget = argv['vs-target'];

	// As of Visual Studio 2017, multiple editions can coexist.
	if (/^Visual Studio \w+ 2017/.test(vstarget)) {
		vstarget = '15.0';
	}

	this.cmakeGeneratorName = supportedCMakeGenerators[vstarget];

	// directories
	this.outputDir = argv['output-dir'] ? appc.fs.resolvePath(argv['output-dir']) : null;
	this.wsCert = argv['win-cert'] ? argv['win-cert'] : (argv['ws-cert'] ? argv['ws-cert'] : null);
	this.pfxPassword = argv['pfx-password'] ? argv['pfx-password'] : null;

	// Publisher id may be a GUID, or they may have copied it verbatim from dev account with CN= prefix
	this.publisherId = argv['win-publisher-id'];
	if (this.publisherId.indexOf('CN=') != 0) {
		// We need to prepend CN= prefix for appxmanifest and cert generation
		this.publisherId = "CN=" + this.publisherId;
	}
	this.phonePublisherId = argv['wp-publisher-guid'] ? argv['wp-publisher-guid'] : "00000000-0000-0000-0000-000000000000";
	this.phoneProductId = argv['win-product-guid'] ? argv['win-product-guid'] : (argv['wp-product-guid'] ? argv['wp-product-guid'] : "f0473be1-c557-4f98-a103-4ba9f453b5b0");

	this.buildSrcDir = path.join(this.buildDir, 'src'); // Where the src files go
	this.cmakeTargetDir = path.join(this.buildDir, this.cmakeTarget); // where cmake generates the VS solution
	this.buildTargetAssetsDir = path.join(this.buildDir, 'Assets');
	this.buildAssetsDir = this.buildTargetAssetsDir; // This property is used by the ProcessJSTask so just alias it to the one Windows CLI uses
	this.buildTargetStringsDir = path.join(this.buildDir, 'Strings');

	// files
	this.buildManifestFile = path.join(this.buildDir, 'build-manifest.json');
	this.cmakeListFile = path.join(this.buildDir, 'CMakeLists.txt'); // lives above the buildSrcDir
	this.cmakeFinderDir = path.join(this.buildDir, 'cmake');

	// Generate appxbundle only for dist-* because it is not actually required for other targets.
	this.useAppxBundle = (/^dist-(phone|win)store$/.test(this.target));

	// Hyperloop configuration
	var hyperloopAppcJs = path.join(this.projectDir, 'appc.windows.js');
	this.hyperloopConfig = fs.existsSync(hyperloopAppcJs) && require(hyperloopAppcJs).hyperloop || {};
	this.hyperloopConfig.windows || (this.hyperloopConfig.windows = {});

	next();
}
