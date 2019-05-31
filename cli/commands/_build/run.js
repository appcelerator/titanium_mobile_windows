'use strict';

const appc = require('node-appc');
const spawn = require('child_process').spawn;
const fs = require('fs-extra');
const Builder = require('node-titanium-sdk/lib/builder');
const __ = appc.i18n(__dirname).__;

/*
 Public API.
 */
exports.mixin = mixin;

/*
 Implementation.
 */
function mixin(WindowsBuilder) {
	WindowsBuilder.prototype.run = run;
	WindowsBuilder.prototype.runCmake = runCmake;
}

/**
 * Performs the build operations.
 *
 * @param {Object} logger - The logger instance.
 * @param {Object} config - The Titanium CLI config instance.
 * @param {Object} cli - The Titanium CLI instance.
 * @param {Function} finished - A function to call when the build has finished or errored.
 */
function run(logger, config, cli, finished) {
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
		'generateBuildVersion',

		function (next) {
			cli.emit('build.pre.compile', this, next);
		},

		'checkAppJs',
		'copyResources',

		function (next) {
			cli.emit('build.pre.build', this, next);
		},

		'generateI18N',
		'generateModuleFinder',
		'generateAppxManifest',
		'generateNativeTypes',
		'generateCmakeList',
		'runCmake',
		'fixCSharpConfiguration',
		'copyModuleOverride',
		'compileApp',

		function (next) {
			cli.emit('build.post.build', this, next);
		},

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
}

/**
 * Runs cmake to generate a VS project.
 *
 * @param {Function} next - A function to call after generating the Visual Studio project.
 */
function runCmake(next) {
	this.logger.info(__('Running cmake at %s in directory %s', this.cmake.cyan, this.cmakeTargetDir.cyan));
	var _t = this,
		generatorName = this.cmakeGeneratorName,
		p;

	if (this.cmakeArch === 'ARM') {
		generatorName += ' ARM';
	}

	this.logger.debug(this.cmake + ' '
		+ JSON.stringify([
			'-G', generatorName,
			'-DCMAKE_SYSTEM_NAME=' + this.cmakePlatform,
			'-DCMAKE_SYSTEM_VERSION=' + this.targetPlatformSdkVersion,
			'-DHAL_RENAME_AXWAYHAL=ON',
			this.buildDir
		], null, 2));
	fs.ensureDirSync(this.cmakeTargetDir);
	// Use spawn directly so we can pipe output as we go
	var cmake = this.cmake;
	p = spawn(cmake,
		[
			'-G', generatorName,
			'-DCMAKE_SYSTEM_NAME=' + this.cmakePlatform,
			'-DCMAKE_SYSTEM_VERSION=' + this.targetPlatformSdkVersion,
			'-DHAL_RENAME_AXWAYHAL=ON',
			this.buildDir
		],
		{
			cwd: this.cmakeTargetDir
		});
	p.on('error', function (err) {
		_t.logger.error(cmake);
		_t.logger.error(err);
	});
	p.stdout.on('data', function (data) {
		_t.logger.debug(data.toString().trim());
	});
	p.stderr.on('data', function (data) {
		_t.logger.warn(data.toString().trim());
	});
	p.on('close', function (code) {
		if (code !== 0) {
			process.exit(1); // Exit with code from cmake?
		}

		next();
	});
}
