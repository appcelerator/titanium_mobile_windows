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

const
	fs = require('fs'),
	path = require('path'),
	appc = require('node-appc'),
	os = require('os'),
	wrench = require('wrench'),
	async = require('async'),
	ejs = require('ejs'),
	spawn = require('child_process').spawn,
	__ = appc.i18n(__dirname).__;

exports.cliVersion = '>=3.2';

exports.init = function (logger, config, cli) {
	cli.on('create.post.module.platform.windows', {
		post: function (data, callback) {
			var cmakeDir = path.resolve(data.sdk.path, 'windows', 'cli', 'vendor', 'cmake'),
				cmake = path.join(cmakeDir, 'bin', 'cmake.exe'),
				projectDir = path.join(data.projectDir, 'windows'),
				cmakeFinds = ['HAL', 'JavascriptCore', 'TitaniumKit', 'TitaniumWindows_Utility'],
				cmakeFindDirSrc = path.join(data.sdk.path, 'windows', 'templates', 'build', 'cmake'),
				cmakeFindDirDst = path.join(projectDir, 'cmake');

			async.series([
				function(next) {
					logger.info('Copying CMake package finders');
					wrench.mkdirSyncRecursive(path.join(cmakeFindDirDst));
					cmakeFinds.forEach(function(pkg) {
						fs.writeFileSync(path.join(cmakeFindDirDst, 'Find'+pkg+'.cmake'), fs.readFileSync(path.join(cmakeFindDirSrc, 'Find'+pkg+'.cmake')));
					});
					next();
				},
				function(next) {
					logger.info('Generating WindowsPhone ARM project');
					runCMake(logger, cmake, projectDir, 'WindowsPhone', 'ARM', next);
				},
				//function(next) {
				//	logger.info('Generating WindowsStore ARM project');
				//	runCMake(logger, cmake, projectDir, 'WindowsStore', 'ARM', next);
				//},
				function(next) {
					logger.info('Generating WindowsPhone Win32 project');
					runCMake(logger, cmake, projectDir, 'WindowsPhone', 'Win32', next);
				},
				function(next) {
					logger.info('Generating WindowsStore Win32 project');
					runCMake(logger, cmake, projectDir, 'WindowsStore', 'Win32', next);
				}
			], function(err, result) {
				if (err) {
					logger.error(err);
				}
				callback();
			});
		}
	});
};

function runCMake(logger, cmake, projectDir, targetEnv, targetArch, callback){
	var targetDir = path.join(projectDir, targetEnv+'.'+targetArch),
		generatorName = 'Visual Studio 12 2013'+(targetArch === 'ARM' ? ' ARM' : ''),
		p,
		originalTargetDir,
		tempBuildDir;

	// try to build under temp if the path is shorter and we have write access
	tempBuildDir = path.join(os.tmpdir(), path.basename(path.dirname(projectDir)), path.basename(targetDir));
	if ((tempBuildDir.length < targetDir.length) && appc.fs.isDirWritable(os.tmpdir())) {
		originalTargetDir = targetDir;
		targetDir = tempBuildDir; // build under temp!
		logger.info(__('Generating solution under temp directory to avoid path length issues...'));
		// if already exists, wipe it
		fs.existsSync(targetDir) && wrench.rmdirSyncRecursive(targetDir);
	} else {
		originalTargetDir = null;
	}

	if (!fs.existsSync(targetDir)) {
		wrench.mkdirSyncRecursive(targetDir);
	}

	p = spawn(cmake,
		[
			'-G', generatorName,
			'-DCMAKE_SYSTEM_NAME=' + targetEnv,
			'-DCMAKE_SYSTEM_VERSION=' + '8.1',
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
		if (code != 0) {
			process.exit(1);
		}
		if (originalTargetDir) {
			// Copy stuff back to original dir!
			logger.info(__('Copying solution back to module from temp directory...'));
			// if already exists, wipe it
			fs.existsSync(originalTargetDir) && wrench.rmdirSyncRecursive(originalTargetDir);
			// make sure destination exists
			fs.existsSync(originalTargetDir) || wrench.mkdirSyncRecursive(originalTargetDir);
			// Now copy back to original location
			wrench.copyDirSyncRecursive(targetDir, originalTargetDir, {
				forceDelete: true
			});
		}
		callback();
	});
}
