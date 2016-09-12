/**
 * Detects Windows development environment and displays it in the "titanium info" command.
 *
 * @module lib/info
 *
 * @copyright
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 *
 * @license
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var appc = require('node-appc'),
	fs = require('fs'),
	windowslib = require('windowslib'),
	path = require('path'),
	windowsPackageJson = appc.pkginfo.package(module),
	__ = appc.i18n(__dirname).__;

exports.name = 'windows';

exports.title = 'Windows';

exports.detect = function (types, config, next) {
	// For backward compatibility reasons windowslib could return empty device
	function isPlaceHolderDevice(d) {
		return (d.name == 'Device' && d.udid == 0 && d.index == 0 && d.wpsdk == null);
	}
	windowslib.detect({
		powershell:                       config.get('windows.executables.powershell'),
		preferredWindowsPhoneSDK:         config.get('windows.wpsdk.selectedVersion'),
		preferredVisualStudio:            config.get('windows.visualstudio.selectedVersion'),
		supportedMSBuildVersions:         windowsPackageJson.vendorDependencies['msbuild'],
		supportedVisualStudioVersions:    windowsPackageJson.vendorDependencies['visual studio'],
		supportedWindowsPhoneSDKVersions: windowsPackageJson.vendorDependencies['windows phone sdk'],
		tasklist:                         config.get('windows.executables.tasklist')
	}, function (err, results) {
		if (err) {
			return next(err);
		}

		// TIMOB-19076: Windows Phone 8.0 is not supported
		results.windowsphone && delete results.windowsphone['8.0'];
		results.windows && delete results.windows['8.0'];
		results.emulators && delete results.emulators['8.0'];

		// TIMOB-23371: Remove placeholder device
		if (results.devices && results.devices[0] && isPlaceHolderDevice(results.devices[0])) {
			results.devices.shift();
		}

		results.tisdk = path.basename((function scan(dir) {
			var file = path.join(dir, 'manifest.json');
			if (fs.existsSync(file)) {
				return dir;
			}
			dir = path.dirname(dir);
			return dir != '/' && scan(dir);
		}(__dirname)));

		if (results.issues.length) {
			this.issues = this.issues.concat(results.issues);
		}

		// improve error messages
		this.issues.forEach(function (issue) {
			switch (issue.id) {
				case 'WINDOWS_VISUAL_STUDIO_NOT_INSTALLED':
					issue.message += '\n' + __('You can install it from %s.', '__http://appcelerator.com/visualstudio__');
					break;
				case 'WINDOWS_PHONE_SDK_NOT_INSTALLED':
				case 'WINDOWS_PHONE_SDK_MISSING_DEPLOY_CMD':
					issue.message += '\n' + __('You can install it from %s.', '__http://appcelerator.com/windowsphone__');
					break;
			}
		});

		this.data = results;
		next(null, { windows: results });
	}.bind(this));
};

exports.render = function (logger, config, rpad, styleHeading, styleValue, styleBad) {
	var data = this.data;
	if (!data) return;

	if (process.platform === 'win32') {
						
		// Visual Studio
		logger.log(styleHeading(__('Microsoft (R) Visual Studio')));
		if (data.visualstudio && Object.keys(data.visualstudio).length) {
			Object.keys(data.visualstudio).sort().forEach(function (ver) {
				var supported = data.visualstudio[ver].supported ? '' : styleBad(' **' + __('Not supported by Titanium SDK %s', data.tisdk) + '**');
				logger.log(
					'  ' + String(ver).cyan + (data.visualstudio[ver].selected ? ' (' + __('selected') + ')' : '').grey + supported + '\n' +
					'  ' + rpad('  ' + __('Path')) + ' = ' + styleValue(data.visualstudio[ver].path) + '\n' +
					'  ' + rpad('  ' + __('CLR Version')) + ' = ' + styleValue(data.visualstudio[ver].clrVersion) + '\n' +
					'  ' + rpad('  ' + __('MSBuild Version')) + ' = ' + styleValue('v' + data.visualstudio[ver].msbuildVersion) + '\n' +
					'  ' + rpad('  ' + __('Windows Phone SDKs')) + ' = ' + styleValue(data.visualstudio[ver].wpsdk ? Object.keys(data.visualstudio[ver].wpsdk).join(', ') : __('not installed'))
				);
			});
			logger.log();
		} else {
			logger.log('  ' + __('No versions found').grey + '\n');
		}

		logger.log(styleHeading(__('Microsoft (R) Windows Phone SDK')));
		if (data.windowsphone && Object.keys(data.windowsphone).length) {
			Object.keys(data.windowsphone).sort().forEach(function (ver) {
				var supported = data.windowsphone[ver].supported ? '' : styleBad(' **' + __('Not supported by Titanium SDK %s', data.tisdk) + '**');
				logger.log(
					'  ' + String(ver).cyan + (data.windowsphone[ver].selected ? ' (' + __('selected') + ')' : '').grey + supported + '\n' +
					'  ' + rpad('  ' + __('Path')) + ' = ' + styleValue(data.windowsphone[ver].path)
				);
			});
			logger.log();
		} else {
			logger.log('  ' + __('No versions found').grey + '\n');
		}

		logger.log(styleHeading(__('Windows PowerShell')));
		logger.log('  ' + rpad('  ' + __('Enabled')) + ' = ' + styleValue(data.powershell && data.powershell.enabled ? __('yes') : __('no')) + '\n');

		logger.log(styleHeading(__('Windows Phone Emulators')));
		if (data.emulators) {
			Object.keys(data.emulators).forEach(function (ver) {
				logger.log(String(ver).grey);
				data.emulators[ver].forEach(function (emu) {
					logger.log('  ' + emu.name.cyan);
					logger.log('  ' + rpad('  ' + __('UDID')) + ' ' + emu.udid.magenta);
				});
			});
			logger.log();
		} else {
			logger.log('  ' + __('None').grey + '\n');
		}

		logger.log(styleHeading(__('Windows Phone Devices')));
		if (data.devices) {
			data.devices.forEach(function (dev) {
				logger.log('  ' + dev.name.cyan);
				logger.log('  ' + rpad('  ' + __('UDID')) + ' ' + String(dev.udid).magenta);
			});
			logger.log();
		} else {
			logger.log('  ' + __('None').grey + '\n');
		}
	}
};
