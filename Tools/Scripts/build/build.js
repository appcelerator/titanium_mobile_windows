/**
 * Copyright (c) 2015-Present by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
'use strict';

// modules
const path = require('path');
const fs = require('fs-extra');
const colors = require('colors'); // eslint-disable-line no-unused-vars
const exec = require('child_process').exec; // eslint-disable-line security/detect-child-process
const spawn = require('child_process').spawn; // eslint-disable-line security/detect-child-process
const windowslib = require('windowslib');

// Constants
const WIN_10_0_14393 = '10.0.14393.0';
const MSBUILD_14 = '14.0';
const MSBUILD_15 = '15.0';
const VS_2015_GENERATOR = 'Visual Studio 14 2015';
const VS_2017_GENERATOR = 'Visual Studio 15 2017';
// paths

const ROOT_DIR = path.join(__dirname, '..', '..', '..');
const CMAKE_BINARY = path.join(ROOT_DIR, 'cli', 'vendor', 'cmake', 'bin', 'cmake.exe');
const SOURCE_TITANIUM_DIR = path.join(ROOT_DIR, 'Source', 'Titanium');
const BUILD_DIR = path.join(ROOT_DIR, 'build');
const DIST_DIR = path.join(ROOT_DIR, 'dist', 'windows');
const DIST_LIB_DIR = path.join(DIST_DIR, 'lib');

/**
 * @param {String} sourceDir The original source directory (in Source/)
 * @param {String} buildDir Where to build the modules temporarily
 * @param {String} destDir The top-level destination directory where we copy the built libraries
 * @param {String} buildType 'Release' || 'Debug'
 * @param {String} msBuildVersion '14.0' || '15.0'
 * @param {String} platform 'WindowsPhone' || 'WindowsStore'
 * @param {String} arch 'x86' || 'ARM'
 * @param {Boolean} parallel should we run MSBuild in parallel?
 * @param {Boolean} quiet log stdout of processes?
 * @return {Promise}
 */
async function buildAndPackage(sourceDir, buildDir, destDir, buildType, msBuildVersion, platform, arch, parallel, quiet) {
	const platformAbbrev = 'win10';

	console.log(`Building ${platform} 10.0 ${arch}: ${buildType}`);
	const archDir = path.join(buildDir, platformAbbrev, arch);
	const slnFile = path.join(archDir, 'TitaniumWindows.sln');

	await runCMake(sourceDir, archDir, buildType, msBuildVersion, platform, arch, quiet);
	await runNuGet(slnFile, quiet);
	await runMSBuild(msBuildVersion, slnFile, buildType, arch, parallel, quiet);
	await copyToDistribution(buildDir, destDir, buildType, platformAbbrev, arch);

	// Wipe the build dir if everything went well. Don't remove top-level build root, because previous build steps may have added results we care about there (i.e. CTest)
	await fs.remove(archDir);
}

/**
 * [getGitHash description]
 * @param {String} dir cwd to run in
 * @return {Promise<string>} [description]
 */
function getGitHash(dir) {
	return new Promise((resolve, reject) => {
		exec('git rev-parse --short --no-color HEAD', { cwd: dir }, (error, stdout) => {
			if (error) {
				return reject(`Failed to get Git HASH: ${error}`);
			}

			resolve(stdout.trim());
		});
	});
}

/**
 * @param {String} githash SHA1 to use for Ti.buildHash, computed if not supplied
 * @param {String} tiModuleCPP the file to update
 * @return {Promise}
 */
async function updateBuildValuesInTitaniumModule(githash, tiModuleCPP) {
	if (!githash) {
		githash = await getGitHash(path.dirname(tiModuleCPP));
	}
	const contents = await fs.readFile(tiModuleCPP, 'utf8');
	const date = new Date();
	const timestamp = (date.getMonth() + 1) + '/' + date.getDate() + '/' + date.getFullYear() + ' ' + date.getHours() + ':' + date.getMinutes();

	// FIXME How can we set the version? It doesn't get set until later _after_ we've built! We'll need to pull it in from some file!
	const modified = contents.replace(/__TITANIUM_BUILD_DATE__/, timestamp).replace(/__TITANIUM_BUILD_HASH__/, githash);
	await fs.writeFile(tiModuleCPP, modified);
}

/**
 * @param {String} sourceDir Where the source is
 * @param {String} buildDir Where to build the project
 * @param {String} buildType 'Release' || 'Debug'
 * @param {String} msBuildVersion '14.0' || '15.0'
 * @param {String} platform  'WindowsPhone' || 'WindowsStore'
 * @param {String} arch 'x86' || 'ARM'
 * @param {Boolean} quiet log stdout of process?
 * @return {Promise}
 */
async function runCMake(sourceDir, buildDir, buildType, msBuildVersion, platform, arch, quiet) {
	let generator = VS_2015_GENERATOR;
	if (msBuildVersion === MSBUILD_15) {
		generator = VS_2017_GENERATOR;
	}

	// If the buildDir already exists, wipe it
	const exists = await fs.pathExists(buildDir);
	if (exists) {
		await fs.remove(buildDir);
	}
	await fs.ensureDir(buildDir);

	if (arch === 'ARM') {
		generator += ' ARM';
	}

	const args = [
		'-G', generator,
		'-DCMAKE_SYSTEM_NAME=' + platform,
		'-DCMAKE_BUILD_TYPE=' + buildType,
		'-DCMAKE_SYSTEM_VERSION=' + WIN_10_0_14393,
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

	await spawnWithArgs('CMake', CMAKE_BINARY, args, { cwd: buildDir }, quiet);
}

/**
 * @param {String} slnFile The VS solution file to build.
 * @param {Boolean} quiet log stdout of process?
 * @return {Promise}
 */
function runNuGet(slnFile, quiet) {
	return spawnWithArgs('NuGet', path.join(__dirname, '..', '..', '..', 'cli', 'vendor', 'nuget', 'nuget.exe'), [ 'restore', slnFile ], {}, quiet);
}

/**
 * @param {String} msBuildVersion The version of MSBuild to run: '14.0' || '15.0'
 * @param {String} slnFile The VS solution file to build.
 * @param {String} buildType 'Release' || 'Debug'
 * @param {String} arch 'x86' || 'ARM'
 * @param {Boolean} parallel Run msbuild in parallel? (/m option)
 * @param {Boolean} quiet log stdout of process?
 * @return {Promise}
 */
function runMSBuild(msBuildVersion, slnFile, buildType, arch, parallel, quiet) {
	return new Promise((resolve, reject) => {
		windowslib.detect({}, (err, results) => {

			let vsInfo = results.visualstudio[msBuildVersion];
			if (vsInfo === undefined && msBuildVersion === '15.0') {
				for (var key in results.visualstudio) {
					// If you can't decide which VS2017 to select, use first one
					if (key.endsWith(' 2017')) {
						vsInfo = results.visualstudio[key];
						break;
					}
				}
			}

			if (!vsInfo) {
				return reject('Unable to find a supported Visual Studio installation');
			}

			// Use spawn directly so we can pipe output as we go
			const p = spawn((process.env.comspec || 'cmd.exe'), [ '/S', '/C', '"', vsInfo.vsDevCmd.replace(/[ ()&]/g, '^$&')
				+ ' && MSBuild' + (arch === 'ARM' ? ' /p:Platform=' + arch : '') + (parallel ? ' /m' : '') + ' /nr:false /p:Configuration=Release ' + slnFile, '"'
			], { windowsVerbatimArguments: true });

			p.stdout.on('data', data => {
				const line = data.toString().trim();
				if (line.indexOf('error ') >= 0) {
					console.log(line);
				} else if (line.indexOf('warning ') >= 0) {
					console.log(line);
				} else {
					quiet || console.log(line);
				}
			});
			p.stderr.on('data', data => console.log(data.toString().trim()));
			p.on('close', code => {
				if (code !== 0) {
					return reject('MSBuild return non-zero exit code');
				}
				resolve();
			});
		});
	});
}

/**
 * @param {String} sourceDir The top-level folder containing all the built libraries from the sln
 * @param {String} destDir The top-level destination directory where we copy the built libraries
 * @param {String} buildType 'Release' || 'Debug'
 * @param {String} platformAbbrev 'phone' || 'store' || 'win10'
 * @param {String} arch 'x86' || 'ARM'
 */
async function copyToDistribution(sourceDir, destDir, buildType, platformAbbrev, arch) {
	const libs = {
		// Library full name : output location
		TitaniumWindows_Sensors: 'Sensors',
		TitaniumWindows_Filesystem: 'Filesystem',
		TitaniumWindows_Global: 'Global',
		HAL: 'Filesystem\\TitaniumKit\\HAL',
		LayoutEngine: 'LayoutEngine',
		TitaniumWindows_Map: 'Map',
		TitaniumWindows_Media: 'Media',
		TitaniumWindows_Network: 'Network',
		TitaniumWindows_Ti: 'Ti',
		TitaniumWindows: '',
		TitaniumKit: 'Filesystem\\TitaniumKit',
		TitaniumWindows_UI: 'Map\\UI',
		TitaniumWindows_Utility: 'Filesystem\\Utility',
	};

	// For each lib, copy the output files!
	for (const key in libs) {
		if (!libs.hasOwnProperty(key)) {
			continue;
		}
		const lib = key; // full name of the built lib files
		const suffix = libs[key]; // relative path of built libs in build folder

		const libSrcDir = path.join(sourceDir, platformAbbrev, arch, suffix, buildType);
		const libDestDir = path.join(destDir, lib, platformAbbrev, arch);

		// Make the destination folder
		const exists = await fs.pathExists(libDestDir);
		if (exists) {
			await fs.remove(libDestDir);
		}
		await fs.ensureDir(libDestDir);

		// Copy the build artifacts
		// TODO Only copy dll/winmd/lib? Do we need anything else? pri?
		await fs.copy(libSrcDir, libDestDir, {
			preserveTimestamps: true, // Preserve the mtime and atime when copying files
		});
		// Copy the export header!
		const header = lib.toLowerCase() + '_export.h';
		await fs.ensureDir(path.join(destDir, lib, 'include'));
		await fs.copy(path.join(sourceDir, platformAbbrev, arch, suffix, header), path.join(destDir, lib, 'include', header));
	}
}

/*
 Utility methods (not used elsewhere).
 */

/**
 * Spawns the specified file with its args, logging its output, and executing the callback when it has finished.
 * @param {String} name Name to use for log messages
 * @param {String} file Filepath to execute
 * @param {String} args args to pass to spawn
 * @param {Object} options options ot pass to spawn
 * @param {Boolean} quiet Should we log stdout?
 * @return {Promise}
 */
function spawnWithArgs(name, file, args, options, quiet) {
	return new Promise((resolve, reject) => {
		const child = spawn(file, args, options);
		child.stdout.on('data', data => quiet || console.log(data.toString().trim()));
		child.stderr.on('data', data => console.log(data.toString().trim().red));
		child.on('close', code => {
			if (code !== 0) {
				return reject(`Failed to run ${name}`);
			}

			resolve();
		});
	});
}

/**
 * @param {String} sha sha1 to use for Ti.buildHash, computed if not provided
 * @param {String} msBuildVersion '14.0' || '15.0'
 * @param {String} buildType 'Release' || 'Debug'
 * @param {string[]} targets (WindowsStore|WindowsPhone)-(ARM|x86)
 * @param {Object} [options] options
 * @param {Boolean} [options.parallel] Run builds in parallel?
 * @param {Boolean} [options.quiet] Log stdout of processes?
 * @return {Promise}
 **/
async function build(sha, msBuildVersion, buildType, targets, options = {}) {
	const overallTimer = process.hrtime();
	let timer = process.hrtime();

	await updateBuildValuesInTitaniumModule(sha, path.join(ROOT_DIR, 'Source', 'Ti', 'src', 'TiModule.cpp'));

	if (options.parallel) {
		await Promise.all(targets.map(configuration => {
			const parts = configuration.split('-'); // target platform(WindowsStore|WindowsPhone)-arch(ARM|x86)
			return buildAndPackage(SOURCE_TITANIUM_DIR, BUILD_DIR, DIST_LIB_DIR, buildType, msBuildVersion, parts[0], parts[1], options.parallel, options.quiet);
		}));
	} else {
		for (const configuration of targets) {
			const parts = configuration.split('-'); // target platform(WindowsStore|WindowsPhone)-arch(ARM|x86)
			await buildAndPackage(SOURCE_TITANIUM_DIR, BUILD_DIR, DIST_LIB_DIR, buildType, msBuildVersion, parts[0], parts[1], options.parallel, options.quiet);
		}
	}

	// measureTimeElapsed
	let elapsed = process.hrtime(timer);
	console.info('Build and Package Time: %ds %dms', elapsed[0], elapsed[1] / 1000000);
	timer = process.hrtime();

	// copy JavaScriptCore
	for (const configuration of targets) {
		const parts = configuration.split('-'); // target platform(WindowsStore|WindowsPhone)-arch(ARM|x86)
		console.log(`Copying JavaScriptCore for ${parts[1]}...`);
		const newDir = path.join(DIST_LIB_DIR, 'JavaScriptCore', 'win10', parts[1]);
		const fromDir = path.join(process.env.JavaScriptCore_HOME, parts[1]);
		await fs.ensureDir(newDir);
		await fs.copy(path.join(fromDir, 'Release'), newDir);
		await fs.copy(path.join(fromDir, 'JavaScriptCore-Release.lib'), path.join(newDir, 'JavaScriptCore.lib'));
	}

	// copyIncludedHeaders
	console.log('Copying over include headers...');
	const newDir = path.join(DIST_LIB_DIR, 'TitaniumKit', 'include', 'Titanium');
	await fs.ensureDir(newDir);

	const tasks = [
		fs.copy(path.join(ROOT_DIR, 'Source', 'HAL', 'include', 'HAL'), path.join(DIST_LIB_DIR, 'HAL', 'include', 'HAL')),
		fs.copy(path.join(ROOT_DIR, 'Source', 'TitaniumKit', 'include', 'Titanium'), path.join(DIST_LIB_DIR, 'TitaniumKit', 'include', 'Titanium')),
		fs.copy(path.join(process.env.JavaScriptCore_HOME, 'includes', 'JavaScriptCore'), path.join(DIST_LIB_DIR, 'HAL', 'include', 'JavaScriptCore')),

		fs.copy(path.join(ROOT_DIR, 'Source', 'Utility', 'include', 'TitaniumWindows'), path.join(DIST_LIB_DIR, 'TitaniumWindows_Utility', 'include', 'TitaniumWindows')),
		fs.copy(path.join(ROOT_DIR, 'Source', 'LayoutEngine', 'include', 'LayoutEngine'), path.join(DIST_LIB_DIR, 'LayoutEngine', 'include', 'LayoutEngine')),
		fs.copy(path.join(ROOT_DIR, 'Source', 'Titanium', 'include', 'TitaniumWindows'), path.join(DIST_LIB_DIR, 'TitaniumWindows', 'include', 'TitaniumWindows')),

		fs.copy(path.join(ROOT_DIR, 'titanium_prep.win64.exe'), path.join(DIST_DIR, 'titanium_prep.win64.exe')),
		fs.copy(path.join(ROOT_DIR, 'titanium_prep.win32.exe'), path.join(DIST_DIR, 'titanium_prep.win32.exe')),
		fs.copy(path.join(ROOT_DIR, 'package.json'), path.join(DIST_DIR, 'package.json')),
		fs.copy(path.join(ROOT_DIR, 'templates'), path.join(DIST_DIR, 'templates')),
		// FIXME For some reason, locally this isn't copying all of cli/vendor/cmake/share (specifically cmake-3.1 subfolder)
		fs.copy(path.join(ROOT_DIR, 'cli'), path.join(DIST_DIR, 'cli'))
	];

	// TODO: map and concat?
	const include_TitaniumWindows = [ 'Filesystem', 'Global', 'Map', 'Media', 'Network', 'Sensors', 'Ti', 'UI' ];
	for (const name of include_TitaniumWindows) {
		tasks.push(fs.copy(path.join(ROOT_DIR, 'Source', name, 'include', 'TitaniumWindows'), path.join(DIST_LIB_DIR, 'TitaniumWindows_' + name, 'include', 'TitaniumWindows')));
	}
	await Promise.all(tasks);

	// measureTimeElapsed
	elapsed = process.hrtime(timer);
	console.info('Header Copy Time: %ds %dms', elapsed[0], elapsed[1] / 1000000);
	elapsed = process.hrtime(overallTimer);
	console.info('Total Time: %ds %dms', elapsed[0], elapsed[1] / 1000000);

	// TODO Generate docs and copy them over! We should start integrating together all these disparate node scripts into a cohesive set!
}

// public API
exports.build = build;

// When run as script
if (module.id === '.') {
	(function () {
		const program = require('commander');
		// default platform/arch targets
		const arches = [ 'WindowsPhone-x86', 'WindowsPhone-ARM', 'WindowsStore-x86' ];

		function collectArches(val, memo) {
			const m = /^Windows(Store|Phone)-(x86|ARM)$/.exec(val);
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
			.option('-m, --msbuild [version]', 'Use a specific version of MSBuild', /^(14\.0|15\.0)$/, MSBUILD_14)
			.option('--sha [sha1]', 'sha1 to use for Ti.buildHash, computed if not provided')
			.parse(process.argv);

		build(program.sha, program.msbuild, program.configuration, (program.only && program.only.length > 0) ? program.only : arches,
			{
				parallel: program.parallel,
				quiet: program.quiet
			})
			.then(() => process.exit(0))
			.catch(err => {
				console.error(err.toString().red);
				process.exit(1);
			});
	}());
}
