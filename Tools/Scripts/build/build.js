/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
var path = require('path'),
	fs = require('fs'),
	async = require('async'),
	colors = require('colors'),
	wrench = require('wrench'),
	spawn = require('child_process').spawn,
	cmakeLocation = path.join(__dirname, '..', '..', '..', 'cli', 'vendor', 'cmake', 'bin', 'cmake.exe'),
	MSBuildLocation = "C:/Program Files (x86)/MSBuild/12.0/Bin/MSBuild.exe";

/**
 * @param sourceDir Where the source is
 * @param buildDir Where to build the project
 * @param buildType 'Release' || 'Debug'
 * @param platform 'WindowsPhone' || 'WindowsStore'
 * @param arch 'x86' || 'ARM'
 * @param callback what to invoke when done/errored 
 */
function runCMake(sourceDir, buildDir, buildType, platform, arch, callback) {
	var prc,
		generator = 'Visual Studio 12 2013';
	
	// If the buildDir already exists, wipe it
	if (fs.existsSync(buildDir)) {
		wrench.rmdirSyncRecursive(buildDir);
	}
	wrench.mkdirSyncRecursive(buildDir);

	if ('ARM' == arch) {
		generator += ' ARM';
	}

	prc = spawn(cmakeLocation, [
			'-G', generator,
			'-DCMAKE_SYSTEM_NAME=' + platform,
			'-DCMAKE_BUILD_TYPE=' + buildType,
			'-DCMAKE_SYSTEM_VERSION=8.1', 
			'-DTitaniumWindows_DISABLE_TESTS=ON',
			'-DTitaniumWindows_Ti_DISABLE_TESTS=ON',
			'-DTitaniumWindows_Global_DISABLE_TESTS=ON',
			'-DTitaniumWindows_Sensors_DISABLE_TESTS=ON',
			'-DTitaniumWindows_UI_DISABLE_TESTS=ON',
			'-DTitaniumWindows_Utility_DISABLE_TESTS=ON',
			'-DTitaniumWindows_Media_DISABLE_TESTS=ON',
			'-DHAL_DISABLE_TESTS=ON',
			'-DTitaniumKit_DISABLE_TESTS=ON',
			'-Wno-dev',
			sourceDir
		],
		{
			cwd: buildDir
	});
	prc.stdout.on('data', function (data) {
	   console.log(data.toString().trim());
	});
	prc.stderr.on('data', function (data) {
	   console.log(data.toString().trim().red);
	});

	prc.on('close', function (code) {
		if (code != 0) {
			callback("Failed to run CMake");
		} else {
			callback();
		}
	});
}

/**
 * @param slnFile The VS solution file to build.
 * @param buildType 'Release' || 'Debug'
 * @param arch 'x86' || 'ARM'
 * @param callback what to invoke when done/errored 
 */
function runMSBuild(slnFile, buildType, arch, callback) {
	var prc,
		args = ['/p:Configuration=' + buildType, '/m'];
		if ('ARM' == arch) {
			args.unshift('/p:Platform=ARM');
		}
		args.unshift(slnFile);
	prc = spawn(MSBuildLocation, args);
	prc.stdout.on('data', function (data) {
	   console.log(data.toString().trim());
	});
	prc.stderr.on('data', function (data) {
	   console.log(data.toString().trim().red);
	});

	prc.on('close', function (code) {
		if (code != 0) {
			callback("Failed to run MSBuild");
		} else {
			callback();
		}
	});
}

/**
 * @param sourceDir The top-level folder containing all the built libraries from the sln
 * @param destDir The top-level destination directory where we copy the built libraries
 * @param buildType 'Release' || 'Debug'
 * @param platform 'WindowsPhone' || 'WindowsStore'
 * @param arch 'x86' || 'ARM'
 * @param callback what to invoke when done/errored 
 */
function copyToDistribution(sourceDir, destDir, buildType, platform, arch, callback) {
	var platformAbbrev = (platform == 'WindowsPhone') ? 'phone' : 'store',
		libs = {
			// Library full name : output location
			'TitaniumWindows_Sensors': 'Sensors',
			'TitaniumWindows_Filesystem': 'Filesystem',
			'TitaniumWindows_Global': 'Global',
			'HAL': 'Filesystem\\TitaniumKit\\HAL',
			'LayoutEngine': 'LayoutEngine',
			'TitaniumWindows_Media': 'Media',
			'TitaniumWindows_Network': 'Network',
			'TitaniumWindows_Ti': 'Ti',
			'TitaniumWindows': '',
			'TitaniumKit': 'Filesystem\\TitaniumKit',
			'TitaniumWindows_UI': 'UI',
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
			include: new RegExp(lib + "\.*") // Include the library's artifacts regardless of file extension
		});
		// Copy the export header!
		header = lib.toLowerCase() + '_export.h';
		wrench.mkdirSyncRecursive(path.join(destDir, lib, 'include'));
		fs.writeFileSync(path.join(destDir, lib, 'include', header), fs.readFileSync(path.join(sourceDir, platformAbbrev, arch, suffix, header)));
	}
	callback();
}

/**
 * @param sourceDir The original source directory (in Source/)
 * @param buildDir Where to build the modules temporarily
 * @param destDir The top-level destination directory where we copy the built libraries
 * @param buildType 'Release' || 'Debug'
 * @param platform 'WindowsPhone' || 'WindowsStore'
 * @param arch 'x86' || 'ARM'
 * @param callback what to invoke when done/errored 
 */
function buildAndPackage(sourceDir, buildDir, destDir, buildType, platform, arch, callback) {
	var platformAbbrev = (platform == 'WindowsPhone') ? 'phone' : 'store';
	console.log("Building " + platform + " 8.1 " + arch + ": " + buildType);
	async.series([
		function (next) {
			runCMake(sourceDir, path.join(buildDir, platformAbbrev, arch), buildType, platform, arch, next);
		},
		function (next) {
			runMSBuild(path.join(buildDir, platformAbbrev, arch, 'TitaniumWindows.sln'), buildType, arch, next);
		},
		function (next) {
			copyToDistribution(buildDir, destDir, buildType, platform, arch, next);
		}
	], function (err, results) {
		if (err) {
			callback(err);
		} else {
			// Wipe the build dir if everything went well. Don't remove top-level build root, because previous build steps may have added results we care about there (i.e. CTest)
			//wrench.rmdirSyncRecursive(path.join(buildDir, platformAbbrev, arch));
			callback();
		}
	});
}

// Now do the builds
var rootDir = path.join(__dirname, '..', '..', '..'),
	titaniumWindowsSrc = path.join(rootDir, 'Source', 'Titanium'),
	buildRoot = path.join(rootDir, 'build'),
	distRoot = path.join(rootDir, 'dist', 'windows'),
	distLib = path.join(distRoot, 'lib');

async.series([
	function (next) {
		buildAndPackage(titaniumWindowsSrc, buildRoot, distLib, 'Release', 'WindowsPhone', 'x86', next);
	},
	// TODO Maybe we can be more efficient by running the mocha tests here after we have enough of the libs to run the emulator.		
	// If they pass, keep building, otherwise exit early?		
	function (next) {		
		buildAndPackage(titaniumWindowsSrc, buildRoot, distLib, 'Release', 'WindowsPhone', 'ARM', next);		
	},		
	function (next) {		
		buildAndPackage(titaniumWindowsSrc, buildRoot, distLib, 'Release', 'WindowsStore', 'x86', next);		
	},
	// TODO Do all these others async. Use async.parallel, and use non-sync versions of file ops!
	function (next) {
		console.log("Copying over include headers...");
		wrench.copyDirSyncRecursive(path.join(rootDir, 'Source', 'HAL', 'include', 'HAL'), path.join(distLib, 'HAL', 'include', 'HAL'));
		//wrench.mkdirSyncRecursive(path.join(distLib, 'TitaniumKit', 'include', 'Titanium'));
		wrench.copyDirSyncRecursive(path.join(rootDir, 'Source', 'Utility', 'include', 'TitaniumWindows'), path.join(distLib, 'TitaniumWindows_Utility', 'include', 'TitaniumWindows'));
		wrench.copyDirSyncRecursive(path.join(rootDir, 'Source', 'TitaniumKit', 'include', 'Titanium'), path.join(distLib, 'TitaniumKit', 'include', 'Titanium'));	
		wrench.copyDirSyncRecursive(path.join(rootDir, 'Source', 'UI', 'include', 'TitaniumWindows'), path.join(distLib, 'TitaniumWindows_UI', 'include', 'TitaniumWindows'));
		wrench.copyDirSyncRecursive(path.join(rootDir, 'Source', 'LayoutEngine', 'include', 'LayoutEngine'), path.join(distLib, 'LayoutEngine', 'include', 'LayoutEngine'));
		// Copy over the JSC headers to HAL!
		wrench.copyDirSyncRecursive(path.join(process.env.JavaScriptCore_HOME, 'includes', 'JavaScriptCore'), path.join(distLib, 'HAL', 'include', 'JavaScriptCore'));
		// Copy over TitaniumKit's Titanium/Module.hpp until we fix the wrappers to not use it!
		fs.writeFileSync(path.join(distLib, 'TitaniumKit', 'include', 'Titanium', 'Module.hpp'), fs.readFileSync(path.join(rootDir, 'Source', 'TitaniumKit', 'include', 'Titanium', 'Module.hpp')));
		// Copy over TitaniumKit's sqlite3.h and stdafx.h
		fs.writeFileSync(path.join(distLib, 'TitaniumKit', 'include', 'sqlite3.h'), fs.readFileSync(path.join(rootDir, 'Source', 'TitaniumKit', 'include', 'sqlite3.h')));
		fs.writeFileSync(path.join(distLib, 'TitaniumKit', 'include', 'stdafx.h'), fs.readFileSync(path.join(rootDir, 'Source', 'TitaniumKit', 'include', 'stdafx.h')));
		next();
	},
	function (next) {
		console.log("Copying over package.json...");
		fs.writeFileSync(path.join(distRoot, 'package.json'), fs.readFileSync(path.join(rootDir, 'package.json')));
		next();
	},
	function (next) {
		console.log("Copying over templates...");
		if (fs.existsSync(path.join(distRoot, 'templates'))) {
			wrench.rmdirSyncRecursive(path.join(distRoot, 'templates'));
		}
		wrench.copyDirSyncRecursive(path.join(rootDir, 'templates'), path.join(distRoot, 'templates'));
		next();
	},
	function (next) {
		console.log("Copying over CLI...");
		if (fs.existsSync(path.join(distRoot, 'cli'))) {
			wrench.rmdirSyncRecursive(path.join(distRoot, 'cli'));
		}
		// FIXME For some reason, locally this isn't copying all of cli/vendor/cmake/share (specifically cmake-3.1 subfolder)
		wrench.copyDirSyncRecursive(path.join(rootDir, 'cli'), path.join(distRoot, 'cli'));
		next();
	},
	// TODO Generate docs and copy them over! We should start integrating together all these disparate node scripts into a cohesive set!
], function (err, results) {
	if (err) {
		console.error(err.toString().red);
		process.exit(1);
	} else {
		process.exit(0);
	}
});
