'use strict';

/**
 * clean.js: Titanium Mobile CLI clean command for Windows
 *
 * @copyright
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 *
 * @license
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

const
	appc = require('node-appc'),
	fs = require('fs'),
	path = require('path'),
	wrench = require('wrench'),
	__ = appc.i18n(__dirname).__;

exports.cliVersion = '>=3.2';

exports.init = function (logger, config, cli) {
	cli.on('clean.post', {
		priority: 10000,
		post: function (builder, finished) {
			var home = process.env.HOME || process.env.USERPROFILE || process.env.APPDATA,
				tempBuildDir = path.join(home, '.titanium', 'vsbuild', path.basename(cli.argv['project-dir']));

			logger.debug(__('Deleting %s', tempBuildDir.cyan));
			if (fs.existsSync(tempBuildDir) && fs.lstatSync(tempBuildDir).isDirectory()) {
				wrench.rmdirSyncRecursive(tempBuildDir);
			}
			finished();
		}
	});
};
