/**
 * Copyright (c) 2015-Present by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
'use strict';

const fs = require('fs-extra');
const path = require('path');
const spawn = require('child_process').spawn; // eslint-disable-line security/detect-child-process
const os = require('os');

const colors = require('colors'); // eslint-disable-line no-unused-vars

// Constants
const MSBUILD_14 = '14.0';
const MSBUILD_15 = '15.0';
const VS_2015_GENERATOR = 'Visual Studio 14 2015';
const VS_2017_GENERATOR = 'Visual Studio 15 2017';
const WINDOWS_STORE = 'WindowsStore';
const symbols = {
	ok: '✓',
	err: '✖',
	dot: '․'
};
// With node.js on Windows: use symbols available in terminal default fonts
if (os.platform() === 'win32') {
	symbols.ok = '\u221A';
	symbols.err = '\u00D7';
	symbols.dot = '.';
}

/**
 * Generates a VS solution and project to run/debug our Example apps manually.
 *
 * @param {String} example_name Name of the example app to generate from (See Examples folder)
 * @param {String} dest output location/folder
 * @param {String} platform 'WindowsStore'|'WindowsPhone'
 * @param {String} sdkVersion '8.1'|'10.0'
 * @param {String} msdev '12.0'|'14.0' MSBuild version to use
 * @param {String} arch 'ARM'|'Win32'
 * @return {Promise}
 **/
function generateProject(example_name, dest, platform, sdkVersion, msdev, arch) {
	return new Promise((resolve, reject) => {
		// cmake generator name
		let generator = (msdev === MSBUILD_14) ? VS_2015_GENERATOR : VS_2017_GENERATOR;
		if (arch === 'ARM') {
			generator += ' ARM';
		}

		// Make sure our intended output dir exists!
		if (!fs.existsSync(dest)) {
			// Make the directory structure!
			fs.ensureDirSync(dest);
		}
		// Now let's generate the solution
		const prc = spawn('cmake', [
			'-G', generator,
			'-DCMAKE_SYSTEM_NAME=' + platform,
			'-DCMAKE_SYSTEM_VERSION=' + sdkVersion,
			'-DTitaniumWindows_DISABLE_TESTS=ON',
			'-DTitaniumWindows_Global_DISABLE_TESTS=ON',
			'-DTitaniumWindows_Ti_DISABLE_TESTS=ON',
			'-DTitaniumWindows_UI_DISABLE_TESTS=ON',
			'-DTitaniumKit_DISABLE_TESTS=ON',
			'-DHAL_DISABLE_TESTS=ON',
			'-DHAL_RENAME_AXWAYHAL=ON',
			path.join(__dirname, '..', '..', 'Examples', example_name)
		], {
			cwd: dest
		});
		prc.stdout.on('data', data => console.log(data.toString()));
		prc.stderr.on('data', data => console.log(data.toString()));
		prc.on('close', function (code) {
			if (code !== 0) {
				return reject('Failed to generate project!');
			}

			resolve();
		});
	});
}

// API
exports.generateProject = generateProject;

// //////////////////////////////////
// //////// MAIN EXECUTION //////////
// //////////////////////////////////
if (module.id === '.') {
	(function () {
		// Process command line input
		const program = require('commander');
		program
			.description('Titanium Windows VS Solution Generator')
			.usage('COMMAND [ARGS] [OPTIONS]')
			.option('-a, --arch <arch>', '"ARM" (device) or "Win32" (emulator)', /^(ARM|Win32)$/, 'Win32')
			.option('-o, --outputPath <outputPath>', 'Output path for generated code');
		// FIXME: Add back MSBuild/VS version selection!

		program.command('new'.blue + ' <example_name>'.white)
			.description('	create a new project from the packaged examples'.grey);

		program.parse(process.argv);

		Error.stackTraceLimit = Infinity;

		if (program.args.length === 0) {
			let help = program.helpInformation();
			help = help.replace('Usage: generate_project COMMAND [ARGS] [OPTIONS]', 'Usage: ' + 'generate_project'.blue + ' COMMAND'.white + ' [ARGS] [OPTIONS]'.grey);
			console.log(help);
			process.exit(1);
		}

		// TODO USe command built-in API for new command!
		// Validate the given command, only can be 'new' right now
		const command = program.args[0];
		if (command !== 'new') {
			console.log('Unknown command: ' + command.red);
			process.exit(1);
		}

		const example_name = program.args[1] || 'NG'; // The example from Examples dir to turn into a project

		// output location
		const dest = program.outputPath || path.join('.', example_name + '.Windows10.' + program.arch);
		generateProject(example_name, dest, WINDOWS_STORE, program.sdkVersion, MSBUILD_15, program.arch)
			.then(() => {
				console.log((symbols.ok + ' Generated VS solution. Open ' + dest + '\\' + example_name + '.sln to begin development.').green);
				process.exit(0);
			})
			.catch(err => {
				console.error(err.toString().red);
				process.exit(1);
			});
	}());
}
