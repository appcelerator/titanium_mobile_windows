/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
// modules
var path = require('path'),
	fs = require('fs'),
	async = require('async'),
	colors = require('colors'),
	wrench = require('wrench'),
	exec = require('child_process').exec,
	spawn = require('child_process').spawn,
	// Constants
	WIN_8_1 = '8.1',
	WIN_10 = '10.0',
	MSBUILD_12 = '12.0',
	MSBUILD_14 = '14.0',
	MSBUILD_15 = '15.0',
	VS_2013_GENERATOR = 'Visual Studio 12 2013',
	VS_2015_GENERATOR = 'Visual Studio 14 2015',
	VS_2017_GENERATOR = 'Visual Studio 15 2017',
	// paths
	rootDir = path.join(__dirname, '..', '..', '..'),
	cmakeLocation = path.join(rootDir, 'cli', 'vendor', 'cmake', 'bin', 'cmake.exe'),
	titaniumWindowsSrc = path.join(rootDir, 'Source', 'Titanium'),
	buildRoot = path.join(rootDir, 'build'),
	distRoot = path.join(rootDir, 'dist', 'windows'),
	distLib = path.join(distRoot, 'lib');

/**
 * @param sourceDir {String} The original source directory (in Source/)
 * @param buildDir {String} Where to build the modules temporarily
 * @param destDir {String} The top-level destination directory where we copy the built libraries
 * @param buildType {String} 'Release' || 'Debug'
 * @param sdkVersion {String} '8.1' || '10.0'
 * @param msBuildVersion {String} '12.0' || '14.0' || '15.0'
 * @param platform {String} 'WindowsPhone' || 'WindowsStore'
 * @param arch {String} 'x86' || 'ARM'
 * @param parallel {Boolean} should we run MSBuild in parallel?
 * @param quiet {Boolean} log stdout of processes?
 * @param callback {Function} what to invoke when done/errored
 */
function buildAndPackage(sourceDir, buildDir, destDir, buildType, sdkVersion, msBuildVersion, platform, arch, parallel, quiet, callback) {
	var platformAbbrev = "win10";
	if (sdkVersion == "8.1") {
		platformAbbrev = (platform == 'WindowsPhone') ? 'phone' : 'store';
	}

	console.log('Building ' + platform + ' ' + sdkVersion + ' ' + arch + ': ' + buildType);
	async.series([
		function (next) {
			runCMake(sourceDir, path.join(buildDir, platformAbbrev, arch), buildType, sdkVersion, msBuildVersion, platform, arch, quiet, next);
		},
		function(next) {
			runNuGet(path.join(buildDir, platformAbbrev, arch, 'TitaniumWindows.sln'), quiet, next);
		},
		function (next) {
			runMSBuild(msBuildVersion, path.join(buildDir, platformAbbrev, arch, 'TitaniumWindows.sln'), buildType, arch, parallel, quiet, next);
		},
		function (next) {
			copyToDistribution(buildDir, destDir, buildType, platformAbbrev, arch, next);
		}
	], function (err, results) {
		if (err) {
			callback(err);
		} else {
			// Wipe the build dir if everything went well. Don't remove top-level build root, because previous build steps may have added results we care about there (i.e. CTest)
			wrench.rmdirSyncRecursive(path.join(buildDir, platformAbbrev, arch));
			callback();
		}
	});
}

/**
 * @param githash SHA1 to use for Ti.buildHash, computed if not supplied
 * @param tiModuleCPP the file to update
 * @param callback what to invoke when done/errored
 */
function updateBuildValuesInTitaniumModule(githash, tiModuleCPP, callback) {
	async.series([
		function getGitHash(next) {
			if (githash) {
				return next();
			}
			exec('git rev-parse --short --no-color HEAD', {cwd: path.dirname(tiModuleCPP)}, function (error, stdout, stderr) {
				if (error) {
					return next('Failed to get Git HASH: ' + error);
				}

				githash = stdout.trim(); // drop leading 'commit ', just take 7-character sha
				return next();
			});
		},
		function updateTiModule(next) {
			fs.readFile(tiModuleCPP, function (err, data) {
				var contents,
					timestamp,
					date;
				if (err) {
					return callback('Failed to get contents of TiModule.cpp to replace hard-coded values: ' + error);
				}
				date = new Date();
				timestamp = (date.getMonth() + 1) + "/" + date.getDate() + "/" + date.getFullYear() + " " + date.getHours() + ":" + date.getMinutes();

				contents = data.toString();
				// FIXME How can we set the version? It doesn't get set until later _after_ we've built! We'll need to pull it in from some file!
				contents = contents.replace(/__TITANIUM_BUILD_DATE__/, timestamp).replace(/__TITANIUM_BUILD_HASH__/, githash);
				fs.writeFile(tiModuleCPP, contents, callback);
			});
		}
	], callback);
}

/**
 * @param sourceDir {String} Where the source is
 * @param buildDir {String} Where to build the project
 * @param buildType {String} 'Release' || 'Debug'
 * @param platform {String} 'WindowsPhone' || 'WindowsStore'
 * @param arch {String} 'x86' || 'ARM'
 * @param quiet {Boolean} log stdout of process?
 * @param callback {Function} what to invoke when done/errored
 */
function runCMake(sourceDir, buildDir, buildType, sdkVersion, msBuildVersion, platform, arch, quiet, callback) {
	var generator = VS_2013_GENERATOR;

	if (msBuildVersion == MSBUILD_14) {
		generator = VS_2015_GENERATOR;
	} else if (msBuildVersion == MSBUILD_15) {
		generator = VS_2017_GENERATOR;
	}

	// If the buildDir already exists, wipe it
	if (fs.existsSync(buildDir)) {
		wrench.rmdirSyncRecursive(buildDir);
	}
	wrench.mkdirSyncRecursive(buildDir);

	if ('ARM' == arch) {
		generator += ' ARM';
	}

	var args = [
		'-G', generator,
		'-DCMAKE_SYSTEM_NAME=' + platform,
		'-DCMAKE_BUILD_TYPE=' + buildType,
		'-DCMAKE_SYSTEM_VERSION=' + sdkVersion,
		'-DTitaniumWindows_DISABLE_TESTS=ON',
		'-DTitaniumWindows_Ti_DISABLE_TESTS=ON',
		'-DTitaniumWindows_Global_DISABLE_TESTS=ON',
		'-DTitaniumWindows_Sensors_DISABLE_TESTS=ON',
		'-DTitaniumWindows_UI_DISABLE_TESTS=ON',
		'-DTitaniumWindows_Utility_DISABLE_TESTS=ON',
		'-DTitaniumWindows_Map_DISABLE_TESTS=ON',
		'-DTitaniumWindows_Media_DISABLE_TESTS=ON',
		'-DHAL_DISABLE_TESTS=ON',
		'-DTitaniumKit_DISABLE_TESTS=ON',
		'-DHAL_RENAME_AXWAYHAL=ON',
		'-Wno-dev',
		sourceDir
	];

	var options = {cwd: buildDir};
	spawnWithArgs('CMake', cmakeLocation, args, options, quiet, callback);
}

/**
 * @param slnFile {String} The VS solution file to build.
 * @param quiet {Boolean} log stdout of process?
 * @param callback {Function} what to invoke when done/errored
 */
function runNuGet(slnFile, quiet, callback) {
	spawnWithArgs('NuGet', path.join(__dirname,'..','..','..','cli','vendor','nuget','nuget.exe'), ['restore',slnFile], {}, quiet, callback);
}

/**
 * @param msBuildVersion {String} The version of MSBuild to run: '12.0' or '14.0'
 * @param slnFile {String} The VS solution file to build.
 * @param buildType {String} 'Release' || 'Debug'
 * @param arch {String} 'x86' || 'ARM'
 * @param parallel {Boolean} Run msbuild in parallel? (/m option)
 * @param quiet {Boolean} log stdout of process?
 * @param callback {Function} what to invoke when done/errored
 */
function runMSBuild(msBuildVersion, slnFile, buildType, arch, parallel, quiet, callback) {
	var args = ['/p:Configuration=' + buildType];
	if ('ARM' == arch) {
		args.unshift('/p:Platform=ARM');
	}
	args.unshift(slnFile);
	parallel && args.push('/m');
	args.push('/nr:false');
	spawnWithArgs('MSBuild', 'C:/Program Files (x86)/MSBuild/' + msBuildVersion + '/Bin/MSBuild.exe', args, {}, quiet, callback);
}

/**
 * @param sourceDir The top-level folder containing all the built libraries from the sln
 * @param destDir The top-level destination directory where we copy the built libraries
 * @param buildType 'Release' || 'Debug'
 * @param platformAbbrev 'phone' || 'store' || 'win10'
 * @param arch 'x86' || 'ARM'
 * @param callback what to invoke when done/errored
 */
function copyToDistribution(sourceDir, destDir, buildType, platformAbbrev, arch, callback) {
	var libs = {
			// Library full name : output location
			'TitaniumWindows_Sensors': 'Sensors',
			'TitaniumWindows_Filesystem': 'Filesystem',
			'TitaniumWindows_Global': 'Global',
			'HAL': 'Filesystem\\TitaniumKit\\HAL',
			'LayoutEngine': 'LayoutEngine',
			'TitaniumWindows_Map': 'Map',
			'TitaniumWindows_Media': 'Media',
			'TitaniumWindows_Network': 'Network',
			'TitaniumWindows_Ti': 'Ti',
			'TitaniumWindows': '',
			'TitaniumKit': 'Filesystem\\TitaniumKit',
			'TitaniumWindows_UI': 'Map\\UI',
			'TitaniumWindows_Utility': 'Filesystem\\Utility',
		},
		libDestDir,
		libSrcDir,
		suffix,
		lib,
		header;

	// For each lib, copy the output files!
	for (var key in libs) {
		if (!libs.hasOwnProperty(key)) {
			continue;
		}
		lib = key; // full name of the built lib files
		suffix = libs[key]; // relative path of built libs in build folder

		libSrcDir = path.join(sourceDir, platformAbbrev, arch, suffix, buildType);
		libDestDir = path.join(destDir, lib, platformAbbrev, arch);

		// Make the destination folder
		if (fs.existsSync(libDestDir)) {
			wrench.rmdirSyncRecursive(libDestDir);
		}
		wrench.mkdirSyncRecursive(libDestDir);

		// Copy the build artifacts
		// TODO Only copy dll/winmd/lib? Do we need anything else? pri?
		wrench.copyDirSyncRecursive(libSrcDir, libDestDir, {
			forceDelete: true, // Whether to overwrite existing directory or not
			preserveTimestamps: true, // Preserve the mtime and atime when copying files
			// FIXME This seems to be copying over everything for TitaniumWindows artifacts, but not sub-libraries
			include: new RegExp(lib + '\.*') // Include the library's artifacts regardless of file extension
		});
		// Copy the export header!
		header = lib.toLowerCase() + '_export.h';
		wrench.mkdirSyncRecursive(path.join(destDir, lib, 'include'));
		fs.writeFileSync(path.join(destDir, lib, 'include', header), fs.readFileSync(path.join(sourceDir, platformAbbrev, arch, suffix, header)));
	}
	callback();
}

/*
 Utility methods (not used elsewhere).
 */

/**
 * Spawns the specified file with its args, logging its output, and executing the callback when it has finished.
 * @param name {String} Name to use for log messages
 * @param file {String} Filepath to execute
 * @param args {Array} args to pass to spawn
 * @param options {Object} options ot pass to spawn
 * @param quiet {Boolean} Should we log stdout?
 * @param callback {Function} callback function when finished
 */
function spawnWithArgs(name, file, args, options, quiet, callback) {
	var child = spawn(file, args, options);
	child.stdout.on('data', function (data) {
		quiet || console.log(data.toString().trim());
	});
	child.stderr.on('data', function (data) {
		console.log(data.toString().trim().red);
	});
	child.on('close', function (code) {
		if (code != 0) {
			callback('Failed to run ' + name);
		} else {
			callback();
		}
	});
}

/**
 * Recursively copies a directory.
 * @param from
 * @param to
 */
function copyDir(from, to) {
	return function (next) {
		wrench.copyDirRecursive(from, to, {forceDelete: true}, function (err) {
			if (err) {
				next(err);
			}
			else {
				next();
			}
		});
	};
}

/**
 * Copies a file.
 * @param from
 * @param to
 */
function copyFile(from, to) {
	return function (next) {
		fs.createReadStream(from).pipe(fs.createWriteStream(to)).on('finish', function (err) {
			if (err) {
				next(err);
			}
			else {
				next();
			}
		});
	};
}

/**
 * @param sdkVersion {String} '8.1' || '10.0'
 * @param sha {String} sha1 to use for Ti.buildHash, computed if not provided
 * @param msBuildVersion {String} '12.0' || '14.0'
 * @param buildType {String} 'Release' || 'Debug'
 * @param targets {Array[String]}
 * @param options {Object}
 * @param options.parallel {Boolean} Run builds in parallel?
 * @param options.quiet {Boolean} Log stdout of processes?
 * @param finished {Function} callback
 **/
function build(sdkVersion, sha, msBuildVersion, buildType, targets, options, finished) {
	var overallTimer = process.hrtime(),
		timer = process.hrtime(),
		options = options || {};

	async.series([
		function updateBuildValues(next) {
			updateBuildValuesInTitaniumModule(sha, path.join(rootDir, 'Source', 'Ti', 'src', 'TiModule.cpp'), next);
		},
		function buildAndPackageAll(next) {
			(options.parallel ? async.each : async.eachSeries)(targets, function (configuration, next) {
				var parts = configuration.split('-'); // target platform(WindowsStore|WindowsPhone)-arch(ARM|x86)
				buildAndPackage(titaniumWindowsSrc, buildRoot, distLib, buildType, sdkVersion, msBuildVersion, parts[0], parts[1], options.parallel, options.quiet, next);
			}, next);
		},
		function measureTimeElapsed(next) {
			var elapsed = process.hrtime(timer);
			console.info('Build and Package Time: %ds %dms', elapsed[0], elapsed[1] / 1000000);
			timer = process.hrtime();
			next();
		},
		function copyJavaScriptCore(next) {
			async.eachSeries(targets, function (configuration, next) {
				var parts = configuration.split('-'); // target platform(WindowsStore|WindowsPhone)-arch(ARM|x86)
				console.log('Copying JavaScriptCore for ' + parts[1] + '...');
				var newDir = path.join(distLib, 'JavaScriptCore', 'win10', parts[1]);
				var fromDir = path.join(process.env.JavaScriptCore_HOME, parts[1]);
				wrench.mkdirSyncRecursive(newDir);
				wrench.copyDirSyncRecursive(path.join(fromDir, 'Release'), newDir, {forceDelete: true});
				fs.createReadStream(path.join(fromDir, 'JavaScriptCore-Release.lib')).pipe(fs.createWriteStream(path.join(newDir, 'JavaScriptCore.lib'))).on('finish', next);
			}, next);
		},
		function copyIncludedHeaders(next) {
			console.log('Copying over include headers...');
			var newDir = path.join(distLib, 'TitaniumKit', 'include', 'Titanium');
			wrench.mkdirSyncRecursive(newDir);

			var tasks = [
				copyDir(path.join(rootDir, 'Source', 'HAL', 'include', 'HAL'), path.join(distLib, 'HAL', 'include', 'HAL')),
				copyDir(path.join(rootDir, 'Source', 'TitaniumKit', 'include', 'Titanium'), path.join(distLib, 'TitaniumKit', 'include', 'Titanium')),
				copyDir(path.join(process.env.JavaScriptCore_HOME, 'includes', 'JavaScriptCore'), path.join(distLib, 'HAL', 'include', 'JavaScriptCore')),

				copyDir(path.join(rootDir, 'Source', 'Utility', 'include', 'TitaniumWindows'), path.join(distLib, 'TitaniumWindows_Utility', 'include', 'TitaniumWindows')),
				copyDir(path.join(rootDir, 'Source', 'LayoutEngine', 'include', 'LayoutEngine'), path.join(distLib, 'LayoutEngine', 'include', 'LayoutEngine')),
				copyDir(path.join(rootDir, 'Source', 'Titanium', 'include', 'TitaniumWindows'), path.join(distLib, 'TitaniumWindows', 'include', 'TitaniumWindows')),

				copyFile(path.join(rootDir, 'titanium_prep.win64.exe'), path.join(distRoot, 'titanium_prep.win64.exe')),
				copyFile(path.join(rootDir, 'titanium_prep.win32.exe'), path.join(distRoot, 'titanium_prep.win32.exe')),
				copyFile(path.join(rootDir, 'package.json'), path.join(distRoot, 'package.json')),
				copyDir(path.join(rootDir, 'templates'), path.join(distRoot, 'templates')),
				// FIXME For some reason, locally this isn't copying all of cli/vendor/cmake/share (specifically cmake-3.1 subfolder)
				copyDir(path.join(rootDir, 'cli'), path.join(distRoot, 'cli'))
			];

			var include_TitaniumWindows = ['Filesystem', 'Global', 'Map', 'Media', 'Network', 'Sensors', 'Ti', 'UI'];
			for (var i = 0; i < include_TitaniumWindows.length; i++) {
				tasks.push(copyDir(path.join(rootDir, 'Source', include_TitaniumWindows[i], 'include', 'TitaniumWindows'), path.join(distLib, 'TitaniumWindows_' + include_TitaniumWindows[i], 'include', 'TitaniumWindows')));
			}

			async.parallel(tasks, next);
		},
		function measureTimeElapsed(next) {
			var elapsed = process.hrtime(timer);
			console.info('Header Copy Time: %ds %dms', elapsed[0], elapsed[1] / 1000000);
			elapsed = process.hrtime(overallTimer);
			console.info('Total Time: %ds %dms', elapsed[0], elapsed[1] / 1000000);
			next();
		}
		// TODO Generate docs and copy them over! We should start integrating together all these disparate node scripts into a cohesive set!
	], finished);
}

// public API
exports.build = build;

// When run as script
if (module.id === ".") {
	(function () {
		var program = require('commander'),
			// default platform/arch targets
			arches = [
				'WindowsPhone-x86',
				'WindowsPhone-ARM',
				'WindowsStore-x86'
			];

		function collectArches(val, memo) {
			var m = /^Windows(Store|Phone)\-(x86|ARM)$/.exec(val);
			if (m) {
				memo.push(val);
			}
			return memo;
		}

		program
			.version('0.0.1')
			.option('-o, --only [arch]', 'Limit to specific architectures (i.e. WindowsPhone-x86)', collectArches, [])
			.option('-c, --configuration [config]', 'Specify configuration to build (i.e. Release or Debug)', /^(Release|Debug)$/, 'Release')
			.option('-q, --quiet', 'Be quiet')
			.option('-p, --parallel', 'Run builds in parallel')
			.option('-m, --msbuild [version]', 'Use a specific version of MSBuild', /^(12\.0|14\.0|15\.0)$/, MSBUILD_12)
			.option('-s, --sdk-version [version]', 'Target a specific Windows SDK version [version]', /^(8\.1|10\.0)$/, WIN_8_1)
			.option('--sha [sha1]', 'sha1 to use for Ti.buildHash, computed if not provided')
			.parse(process.argv);

		// When doing win 10, it has to use msbuild 14
		if (program.sdkVersion == WIN_10 && program.msbuild == MSBUILD_12) {
			// TODO Log warning if they used msbuild 12!
			program.msbuild = MSBUILD_14;
		}

		build(program.sdkVersion, program.sha, program.msbuild, program.configuration, (program.only && program.only.length > 0) ? program.only : arches,
			{
				parallel: program.parallel,
				quiet: program.quiet
			},
			function (err, results) {
				if (err) {
					console.error(err.toString().red);
					process.exit(1);
				}
				process.exit(0);
		});
	})();
}
