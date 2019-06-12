/**
 * Generates the Windows Native Module Visual Studio project files
 *
 * @copyright
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 *
 * @license
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
'use strict';

const fs = require('fs-extra');
const path = require('path');
const appc = require('node-appc');
const async = require('async');
const spawn = require('child_process').spawn; // eslint-disable-line security/detect-child-process
const windowslib = require('windowslib');
const __ = appc.i18n(__dirname).__;

exports.cliVersion = '>=3.2';

//
// Choose CMake generator based on selected Visual Studio
//
function chooseCMakeVSgenerator(logger, callback) {
	const generators = {
		'12.0': 'Visual Studio 12 2013',
		'14.0': 'Visual Studio 14 2015',
		'15.0': 'Visual Studio 15 2017'
	};

	windowslib.detect(function (err, results) {
		if (err) {
			logger.err(err);
		}
		var generator = generators['12.0'],
			sdks = {
				windows: results.windows,
				windowsphone: results.windowsphone
			};
		if (results.selectedVisualStudio) {
			if (/^Visual Studio \w+ 2017/.test(results.selectedVisualStudio.version)) {
				generator = generators['15.0'];
			} else {
				generator = generators[results.selectedVisualStudio.version];
			}
		}
		callback(generator, sdks);
	});
}

exports.init = function (logger, config, cli) {
	cli.on('create.post.module.platform.windows', {
		post: function (data, callback) {
			var cmakeDir = path.resolve(data.sdk.path, 'windows', 'cli', 'vendor', 'cmake'),
				cmake = path.join(cmakeDir, 'bin', 'cmake.exe'),
				projectDir = path.join(data.projectDir, 'windows'),
				cmakeFinds = [ 'HAL', 'JavascriptCore', 'TitaniumKit', 'TitaniumWindows_Utility' ],
				cmakeFindDirSrc = path.join(data.sdk.path, 'windows', 'templates', 'build', 'cmake'),
				cmakeFindDirDst = path.join(projectDir, 'cmake');

			chooseCMakeVSgenerator(logger, function (generator, sdks) {
				async.series([
					function (next) {
						logger.info('Copying CMake package finders');
						fs.ensureDirSync(path.join(cmakeFindDirDst));
						cmakeFinds.forEach(function (pkg) {
							fs.writeFileSync(path.join(cmakeFindDirDst, 'Find' + pkg + '.cmake'), fs.readFileSync(path.join(cmakeFindDirSrc, 'Find' + pkg + '.cmake')));
						});
						next();
					},
					function (next) {
						if (sdks.windows.hasOwnProperty('10.0')) {
							logger.info('Generating Windows 10 Win32 project');
							runCMake(logger, cmake, projectDir, 'Windows10', 'Win32', generator, next);
						} else {
							logger.info('Skipping Windows 10 Win32 project as Windows 10.0 SDK is not installed');
							next();
						}
					},
					function (next) {
						if (sdks.windowsphone.hasOwnProperty('10.0')) {
							logger.info('Generating Windows 10 ARM project');
							runCMake(logger, cmake, projectDir, 'Windows10', 'ARM', generator, next);
						} else {
							logger.info('Skipping Windows 10 ARM project as Windows 10.0 SDK is not installed');
							next();
						}
					}
				], function (err, result) {
					if (err) {
						logger.error(err);
					}
					callback();
				});
			});
		}
	});
};

function runCMake(logger, cmake, projectDir, targetEnv, targetArch, targetGenerator, callback) {
	var targetDir = path.join(projectDir, targetEnv + '.' + targetArch),
		generatorName =  targetGenerator + (targetArch === 'ARM' ? ' ARM' : ''),
		p,
		originalTargetDir,
		targetPlatform = (targetEnv === 'Windows10') ? 'WindowsStore' : targetEnv;
	const targetVersion  = (targetEnv === 'Windows10') ? '10.0' : '8.1';

	// check that the build directory is writeable
	// try to build under temp if the path is shorter and we have write access
	var home = process.env.HOME || process.env.USERPROFILE || process.env.APPDATA;
	var ti_home = path.join(home, '.titanium');
	var tempBuildDir = path.join(ti_home, 'vsbuild');
	if (appc.fs.isDirWritable(home)) {
		if (!fs.existsSync(ti_home)) {
			fs.mkdirSync(ti_home);
		}
		if (!fs.existsSync(tempBuildDir)) {
			fs.mkdirSync(tempBuildDir);
		}
	}
	if (appc.fs.isDirWritable(tempBuildDir)) {
		originalTargetDir = targetDir;
		targetDir = path.join(tempBuildDir, path.basename(path.dirname(projectDir)), path.basename(targetDir));
		logger.info(__('Generating solution under vsbuild directory to avoid path length issues...'));
		// if already exists, wipe it
		fs.emptyDirSync(targetDir);
	} else {
		originalTargetDir = null;
	}

	p = spawn(cmake,
		[
			'-G', generatorName,
			'-DCMAKE_SYSTEM_NAME=' + targetPlatform,
			'-DCMAKE_SYSTEM_VERSION=' + targetVersion,
			'-DHAL_RENAME_AXWAYHAL=ON',
			path.join(projectDir)
		],
		{
			cwd: targetDir
		});

	p.stdout.on('data', function (data) {
		logger.info(data.toString().trim());
	});
	p.stderr.on('data', function (data) {
		logger.warn(data.toString().trim());
	});
	p.on('close', function (code) {
		if (code !== 0) {
			process.exit(1);
		}
		if (originalTargetDir) {
			// Copy stuff back to original dir!
			logger.info(__('Copying solution back to module from temp directory...'));
			// if already exists, wipe it -make sure destination exists
			fs.emptyDirSync(originalTargetDir);
			// Now copy back to original location
			fs.copySync(targetDir, originalTargetDir, {
				overwrite: true
			});
		}
		callback();
	});
}
