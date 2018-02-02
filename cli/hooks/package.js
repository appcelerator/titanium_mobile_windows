/**
 * Copies the result to the specified output directory.
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

function sanitizeProjectName(str) {
	return str.replace(/[^a-zA-Z0-9_]/g, '_').replace(/_+/g, '_').split(/[\W_]/).map(function (s) { return appc.string.capitalize(s); }).join('');
}

exports.init = function (logger, config, cli) {
	cli.on('build.post.compile', {
		priority: 10000,
		post: function (builder, finished) {
			if (builder.buildOnly || !/^dist-(phone|win)store$/.test(builder.target)) {
				return finished();
			}

			var outputDir = builder.outputDir,
				tiapp = builder.tiapp,
				sanitizedName = sanitizeProjectName(tiapp.name),
				// name of the directory holding appx and dependencies subfolder
				dirName = sanitizedName + '_' + builder.buildVersion + ((builder.buildConfiguration == 'Debug') ? '_Debug_Test' : '_Test');
				// path to folder holding appx
				appxDir = path.resolve(builder.cmakeTargetDir, 'AppPackages', sanitizedName, dirName),
				appxExtensions = ['.appx', '.appxbundle'],
				appx = path.join(appxDir, fs.readdirSync(appxDir).filter(function (f) {
					return appxExtensions.indexOf(path.extname(f)) !== -1;
				})[0]),
				dest = path.join(outputDir, path.basename(appx));

			if (outputDir && outputDir != path.dirname(appx)) {
				fs.existsSync(outputDir) || wrench.mkdirSyncRecursive(outputDir);
				fs.existsSync(dest) && fs.unlinkSync(dest);
				appc.fs.copyFileSync(appx, dest, {logger: logger.debug});
			}

			logger.info(__('Packaging complete'));
			logger.info(__('Package location: %s', dest.cyan));
			finished();
		}
	});
};
