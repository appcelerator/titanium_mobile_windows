/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.Filesystem', function () {
	it('apiName', function (finish) {
		should(Ti.Filesystem.apiName).be.eql('Ti.Filesystem');
		finish();
	});

	// Check if applicationDirectory exists and make sure it does not throw exception
	// Android doesn't support Ti.Filesystem.applicationDirectory
	(utilities.isAndroid() ? it.skip : it)('applicationDirectory', function (finish) {
		should(function () {
			should(Ti.Filesystem.applicationDirectory).not.be.undefined;
			should(Ti.Filesystem.applicationDirectory).be.a.String;
			// make sure it is read-only value
			var value = Ti.Filesystem.applicationDirectory;
			Ti.Filesystem.applicationDirectory = 'try_to_overwrite_READONLY_value';
			should(Ti.Filesystem.applicationDirectory).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if applicationDataDirectory exists and make sure it does not throw exception
	it('applicationDataDirectory', function (finish) {
		should(function () {
			should(Ti.Filesystem.applicationDataDirectory).not.be.undefined;
			should(Ti.Filesystem.applicationDataDirectory).be.a.String;
			// make sure it is read-only value
			var value = Ti.Filesystem.applicationDataDirectory;
			Ti.Filesystem.applicationDataDirectory = 'try_to_overwrite_READONLY_value';
			should(Ti.Filesystem.applicationDataDirectory).be.eql(value);
		}).not.throw();
		finish();
	});
	// Check if resourcesDirectory exists and make sure it does not throw exception
	it('resourcesDirectory', function (finish) {
		should(function () {
			should(Ti.Filesystem.resourcesDirectory).not.be.undefined;
			should(Ti.Filesystem.resourcesDirectory).be.a.String;
			// make sure it is read-only value
			var value = Ti.Filesystem.resourcesDirectory;
			Ti.Filesystem.resourcesDirectory = 'try_to_overwrite_READONLY_value';
			should(Ti.Filesystem.resourcesDirectory).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if resRawDirectory exists and make sure it does not throw exception
	it('resRawDirectory', function (finish) {
		if (utilities.isAndroid()) {
			should(function () {
				should(Ti.Filesystem.resRawDirectory).not.be.undefined;
				should(Ti.Filesystem.resRawDirectory).be.a.String;
				// make sure it is read-only value
				var value = Ti.Filesystem.resRawDirectory;
				Ti.Filesystem.resRawDirectory = 'try_to_overwrite_READONLY_value';
				should(Ti.Filesystem.resRawDirectory).be.eql(value);
			}).not.throw();
		} else {
			should(Ti.Filesystem.resRawDirectory).be.undefined;
		}
		finish();
	});
	// On Windows Runtime, applicationSupportDirectory may return null if app doesn't have permission
	// although it should not throw exception
	it('applicationSupportDirectory', function (finish) {
		if (!utilities.isAndroid()) {
			should(function () {
				should(Ti.Filesystem.applicationSupportDirectory).not.be.undefined;
				if (Ti.Filesystem.applicationSupportDirectory != null) {
					should(Ti.Filesystem.applicationSupportDirectory).be.a.String;
				}
				// make sure it is read-only value
				var value = Ti.Filesystem.applicationSupportDirectory;
				Ti.Filesystem.applicationSupportDirectory = 'try_to_overwrite_READONLY_value';
				should(Ti.Filesystem.applicationSupportDirectory).be.eql(value);
			}).not.throw();
			finish();
		}
	});

	// On Windows Runtime, externalStorageDirectory may return null if app doesn't have permission
	// although it should not throw exception
	it('externalStorageDirectory', function (finish) {
		if (!utilities.isIOS()) {
			should(function () {
				should(Ti.Filesystem.externalStorageDirectory).not.be.undefined;
				if (Ti.Filesystem.externalStorageDirectory != null) {
					should(Ti.Filesystem.externalStorageDirectory).be.a.String;
				}
				// make sure it is read-only value
				var value = Ti.Filesystem.externalStorageDirectory;
				Ti.Filesystem.externalStorageDirectory = 'try_to_overwrite_READONLY_value';
				should(Ti.Filesystem.externalStorageDirectory).be.eql(value);
			}).not.throw();
			finish();
		}
	});

	// Check if applicationCacheDirectory exists and make sure it does not throw exception
	it('applicationCacheDirectory', function (finish) {
		should(function () {
			// Windows Store app doesn't support cache directory
			if (utilities.isWindowsDesktop()) {
				should(Ti.Filesystem.applicationCacheDirectory).be.undefined;
			} else {
				should(Ti.Filesystem.applicationCacheDirectory).not.be.undefined;
				should(Ti.Filesystem.applicationCacheDirectory).be.a.String;
				// make sure it is read-only value
				var value = Ti.Filesystem.applicationCacheDirectory;
				Ti.Filesystem.applicationCacheDirectory = 'try_to_overwrite_READONLY_value';
				should(Ti.Filesystem.applicationCacheDirectory).be.eql(value);
			}
		}).not.throw();
		finish();
	});

	// Check if tempDirectory exists and make sure it does not throw exception
	it('tempDirectory', function (finish) {
		should(function () {
			should(Ti.Filesystem.tempDirectory).not.be.undefined;
			should(Ti.Filesystem.tempDirectory).be.a.String;
			// make sure it is read-only value
			var value = Ti.Filesystem.tempDirectory;
			Ti.Filesystem.tempDirectory = 'try_to_overwrite_READONLY_value';
			should(Ti.Filesystem.tempDirectory).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if separator exists and make sure it does not throw exception
	it('separator', function (finish) {
		should(function () {
			should(Ti.Filesystem.separator).not.be.undefined;
			should(Ti.Filesystem.separator).be.a.String;
			if (utilities.isWindows()) {
				should(Ti.Filesystem.separator).be.eql('\\');
			} else {
				should(Ti.Filesystem.separator).be.eql('/');
			}
			// make sure it is read-only value
			var value = Ti.Filesystem.separator;
			Ti.Filesystem.separator = 'try_to_overwrite_READONLY_value';
			should(Ti.Filesystem.separator).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if lineEnding exists and make sure it does not throw exception
	it('lineEnding', function (finish) {
		should(function () {
			should(Ti.Filesystem.lineEnding).not.be.undefined;
			should(Ti.Filesystem.lineEnding).be.a.String;
			if (utilities.isWindows()) {
				should(Ti.Filesystem.lineEnding).be.eql('\r\n');
			} else {
				should(Ti.Filesystem.lineEnding).be.eql('\n');
			}
			// make sure it is read-only value
			var value = Ti.Filesystem.lineEnding;
			Ti.Filesystem.lineEnding = 'try_to_overwrite_READONLY_value';
			should(Ti.Filesystem.lineEnding).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if MODE_APPEND exists and make sure it does not throw exception
	it('MODE_APPEND', function (finish) {
		should(function () {
			should(Ti.Filesystem.MODE_APPEND).not.be.undefined;
			should(Ti.Filesystem.MODE_APPEND).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Filesystem.MODE_APPEND;
			Ti.Filesystem.MODE_APPEND = 'try_to_overwrite_READONLY_value';
			should(Ti.Filesystem.MODE_APPEND).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if MODE_READ exists and make sure it does not throw exception
	it('MODE_READ', function (finish) {
		should(function () {
			should(Ti.Filesystem.MODE_READ).not.be.undefined;
			should(Ti.Filesystem.MODE_READ).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Filesystem.MODE_READ;
			Ti.Filesystem.MODE_READ = 'try_to_overwrite_READONLY_value';
			should(Ti.Filesystem.MODE_READ).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if MODE_WRITE exists and make sure it does not throw exception
	it('MODE_WRITE', function (finish) {
		should(function () {
			should(Ti.Filesystem.MODE_WRITE).not.be.undefined;
			should(Ti.Filesystem.MODE_WRITE).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Filesystem.MODE_WRITE;
			Ti.Filesystem.MODE_WRITE = 'try_to_overwrite_READONLY_value';
			should(Ti.Filesystem.MODE_WRITE).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if getFile exists and make sure it does not throw exception
	it('getFile', function (finish) {
		should(Ti.Filesystem.getFile).not.be.undefined;
		should(Ti.Filesystem.getFile).be.a.Function;
		var file = Ti.Filesystem.getFile('app.js');
		should(file).be.ok; // not null or undefined. should(file).not.be.null causes a stack overflow somehow.
		finish();
	});

	// Check if openStream exists
	it('openStream', function (finish) {
		should(Ti.Filesystem.openStream).not.be.undefined;
		should(Ti.Filesystem.openStream).be.a.Function;
		var stream = Ti.Filesystem.openStream(Ti.Filesystem.MODE_READ, 'app.js');
		should(stream).be.ok; // not null or undefined. should(stream).not.be.null causes a stack overflow somehow.
		stream.close();
		finish();
	});

	// Check if createTempDirectory exists and make sure it does not throw exception
	it('createTempDirectory', function (finish) {
		should(Ti.Filesystem.createTempDirectory).not.be.undefined;
		should(Ti.Filesystem.createTempDirectory).be.a.Function;
		var dir = Ti.Filesystem.createTempDirectory();
		should.exist(dir);
		should.exist(dir.name);
		should(dir.exists()).be.true;
		should(dir.deleteDirectory()).be.true;
		should(dir.exists()).be.false;
		finish();
	});

	// Check if createTempFile exists and make sure it does not throw exception
	it('createTempFile', function (finish) {
		should(Ti.Filesystem.createTempFile).not.be.undefined;
		should(Ti.Filesystem.createTempFile).be.a.Function;
		var file = Ti.Filesystem.createTempFile();
		should(file).be.ok; // not null or undefined. should(file).not.; causes a stack overflow somehow.
		should(file.name).be.a.String;
		should(file.exists()).be.true;
		should(file.deleteFile()).be.true;
		should(file.exists()).be.false;
		finish();
	});

	// TIMOB-10107
	it.skip('multiLingualFilename', function(finish) {
		var msg = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, '網上廣東話輸入法.txt');
		should(msg.write('Appcelerator', true)).be.true;
		should(msg.exists()).be.true;
		should(msg.deleteFile()).be.true;
		should(msg.exists()).be.false;
		finish();
	});

	// TIMOB-14364
	(utilities.isIOS() ? it : it.skip)('setRemoteBackup', function (finish) {
		should(function () {
			Titanium.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory).setRemoteBackup(false);
		}).not.throw();
		finish();
	});
});
