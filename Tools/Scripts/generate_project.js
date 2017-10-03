'use strict';

/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
const fs = require('fs'),
	colors = require('colors'), // eslint-disable-line no-unused-vars
	path = require('path'),
	spawn = require('child_process').spawn,  // eslint-disable-line security/detect-child-process
	os = require('os'),
	program = require('commander'),
	wrench = require('wrench'),
	symbols = {
		ok: '✓',
		err: '✖',
		dot: '․'
	},
	// Constants
	WIN_8_1 = '8.1',
	WIN_10 = '10.0',
	MSBUILD_12 = '12.0',
	MSBUILD_14 = '14.0',
	VS_2013_GENERATOR = 'Visual Studio 12 2013',
	VS_2015_GENERATOR = 'Visual Studio 14 2015',
	WINDOWS_STORE = 'WindowsStore';
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
 * @param {Function} next callback function
 **/
function generateProject(example_name, dest, platform, sdkVersion, msdev, arch, next) {
	var example_folder = path.join(__dirname, '..', '..', 'Examples', example_name),
		generator,
		prc;

	// cmake generator name
	generator = (msdev === MSBUILD_14) ? VS_2015_GENERATOR : VS_2013_GENERATOR;
	if (arch === 'ARM') {
		generator += ' ARM';
	}

	// Make sure our intended output dir exists!
	if (!fs.existsSync(dest)) {
		// Make the directory structure!
		wrench.mkdirSyncRecursive(dest);
	}
	// Now let's generate the solution
	prc = spawn('cmake', [ '-G', generator,
		'-DCMAKE_SYSTEM_NAME=' + platform,
		'-DCMAKE_SYSTEM_VERSION=' + sdkVersion,
		'-DTitaniumWindows_DISABLE_TESTS=ON',
		'-DTitaniumWindows_Global_DISABLE_TESTS=ON',
		'-DTitaniumWindows_Ti_DISABLE_TESTS=ON',
		'-DTitaniumWindows_UI_DISABLE_TESTS=ON',
		'-DTitaniumKit_DISABLE_TESTS=ON',
		'-DHAL_DISABLE_TESTS=ON',
		example_folder
	], {
		cwd: dest
	});
	prc.stdout.on('data', function (data) {
		console.log(data.toString());
	});
	prc.stderr.on('data', function (data) {
		console.log(data.toString());
	});
	prc.on('close', function (code) {
		if (code !== 0) {
			next('Failed to generate project!');
		} else {
			next();
		}
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
		program
			.description('Titanium Windows VS Solution Generator')
			.usage('COMMAND [ARGS] [OPTIONS]')
			.option('-a, --arch <arch>', '"ARM" (device) or "Win32" (emulator)', /^(ARM|Win32)$/, 'Win32')
			.option('-o, --outputPath <outputPath>', 'Output path for generated code')
			.option('-p, --platform <platform>', '"WindowsPhone" or "WindowsStore"', /^Windows(Phone|Store)$/, 'WindowsPhone')
			.option('-s, --sdk-version <version>', 'Target a specific Windows SDK version [version]', /^(8\.1|10\.0)$/, WIN_8_1)
			.option('-m, --msbuild <msbuild>', '"12.0" (VS 2013) or "14.0" (VS 2015)', /^(12\.0|14\.0)$/, MSBUILD_12);

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
		let abbrev = program.platform; // part of folder name for generated project

		// Win 10 must be 'WindowsStore', VS 2015 and MSBuild 14.0
		if (program.sdkVersion === WIN_10) {
			program.msbuild = MSBUILD_14;
			program.platform = WINDOWS_STORE;
			abbrev = 'Windows10';
		}

		// output location
		const dest = program.outputPath || path.join('.', example_name + '.' + abbrev + '.' + program.arch);

		generateProject(example_name, dest, program.platform, program.sdkVersion, program.msbuild, program.arch, function (err) {
			if (err) {
				console.error(err.toString().red);
				process.exit(1);
			}
			console.log((symbols.ok + ' Generated VS solution. Open ' + dest + '\\' + example_name + '.sln to begin development.').green);
		});
	}());
}
