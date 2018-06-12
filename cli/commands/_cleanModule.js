/**
* Windows module clean command.
*
* @module cli/_cleanModule
*
* @copyright
* Copyright (c) 2018 by Appcelerator, Inc. All Rights Reserved.
*
* @license
* Licensed under the terms of the Apache Public License
* Please see the LICENSE included with this distribution for details.
*/

'use strict';
const path = require('path');
const fs = require('fs-extra');
const appc = require('node-appc');
const __ = appc.i18n(__dirname).__;

exports.run = function run(logger, config, cli, finished) {
	const projectDir = cli.argv['project-dir'];

	// Guess the generated zipfile name!
	// TODO: Use a glob and delete any version zipfile generated?
	const moduleId = cli.manifest.moduleid;
	const moduleVersion = cli.manifest.version;
	const moduleZipName = [ moduleId, '-windows-', moduleVersion, '.zip' ].join('');

	const moduleBuildDir = path.join('build', moduleId);
	const toDelete = [
		moduleBuildDir, 'dist', 'Windows10.ARM', 'Windows10.Win32', 'WindowsPhone.ARM/',
		'WindowsPhone.Win32', 'WindowsStore.Win32', 'CMakeLists.txt', moduleZipName
	];
	toDelete.forEach((f) => {
		const target = path.join(projectDir, f);
		if (appc.fs.exists(target)) {
			logger.debug(__('Deleting %s', target.cyan));
			fs.removeSync(target);
		} else {
			logger.debug(__('File does not exist %s', target.cyan));
		}
	});

	finished();
};
