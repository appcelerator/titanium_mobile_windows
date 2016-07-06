/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities');

describe('Titanium.Filesystem', function () {
	it('apiName', function () {
		should(Ti.Filesystem.apiName).be.eql('Ti.Filesystem');
		should(Ti.Filesystem).have.readOnlyProperty('apiName').which.is.a.String;
	});

	it('MODE_APPEND', function () {
		should(Ti.Filesystem).have.constant('MODE_APPEND').which.is.a.Number;
	});

	it('MODE_READ', function () {
		should(Ti.Filesystem).have.constant('MODE_READ').which.is.a.Number;
	});

	it('MODE_WRITE', function () {
		should(Ti.Filesystem).have.constant('MODE_WRITE').which.is.a.Number;
	});

	// Android doesn't support Ti.Filesystem.applicationDirectory
	(utilities.isAndroid() ? it.skip : it)('applicationDirectory', function () {
		should(Ti.Filesystem).have.readOnlyProperty('applicationDirectory').which.is.a.String;
	});

	it('applicationDataDirectory', function () {
		should(Ti.Filesystem).have.readOnlyProperty('applicationDataDirectory').which.is.a.String;
	});

	it('resourcesDirectory', function () {
		should(Ti.Filesystem).have.readOnlyProperty('resourcesDirectory').which.is.a.String;
	});

	it('resRawDirectory', function () {
		if (utilities.isAndroid()) {
			should(Ti.Filesystem).have.readOnlyProperty('resRawDirectory').which.is.a.String;
		} else {
			should(Ti.Filesystem.resRawDirectory).be.undefined;
		}
	});

	// On Windows Runtime, applicationSupportDirectory may return null if app doesn't have permission
	// although it should not throw exception
	it('applicationSupportDirectory', function () {
		if (!utilities.isAndroid()) {
			should(Ti.Filesystem.applicationSupportDirectory).not.be.undefined;
			should(Ti.Filesystem).have.a.readOnlyProperty('applicationSupportDirectory').which.is.a.String;
		}
	});

	// On Windows Runtime, externalStorageDirectory may return null if app doesn't have permission
	// although it should not throw exception
	it('externalStorageDirectory', function () {
		if (!utilities.isIOS()) {
			should(Ti.Filesystem.externalStorageDirectory).not.be.undefined;
			should(Ti.Filesystem).have.a.readOnlyProperty('externalStorageDirectory').which.is.a.String;
		}
	});

	it('applicationCacheDirectory', function () {
		// Windows Store app doesn't support cache directory
		if (utilities.isWindowsDesktop()) {
			should(Ti.Filesystem.applicationCacheDirectory).be.undefined;
		} else {
			should(Ti.Filesystem).have.readOnlyProperty('applicationCacheDirectory').which.is.a.String;
		}
	});

	it('tempDirectory', function () {
		should(Ti.Filesystem).have.readOnlyProperty('tempDirectory').which.is.a.String;
	});

	it('separator', function () {
		should(Ti.Filesystem).have.a.readOnlyProperty('separator').which.is.a.String;
		if (utilities.isWindows()) {
			should(Ti.Filesystem.separator).be.eql('\\');
		} else {
			should(Ti.Filesystem.separator).be.eql('/');
		}
	});

	it('lineEnding', function () {
		should(Ti.Filesystem).have.a.readOnlyProperty('lineEnding').which.is.a.String;
		if (utilities.isWindows()) {
			should(Ti.Filesystem.lineEnding).be.eql('\r\n');
		} else {
			should(Ti.Filesystem.lineEnding).be.eql('\n');
		}
	});

	it('getFile()', function () {
		should(Ti.Filesystem.getFile).be.a.Function;
		var file = Ti.Filesystem.getFile('app.js');
		should(file).be.ok; // not null or undefined. should(file).not.be.null causes a stack overflow somehow.
	});

	it('openStream()', function () {
		should(Ti.Filesystem.openStream).not.be.undefined;
		should(Ti.Filesystem.openStream).be.a.Function;
		var stream = Ti.Filesystem.openStream(Ti.Filesystem.MODE_READ, 'app.js');
		should(stream).be.ok; // not null or undefined. should(stream).not.be.null causes a stack overflow somehow.
		stream.close();
	});

	// FIXME Get working on Android. Either exists() or deleteDirectory() is returning false
	(utilities.isAndroid() ? it.skip : it)('createTempDirectory()', function () {
		should(Ti.Filesystem.createTempDirectory).not.be.undefined;
		should(Ti.Filesystem.createTempDirectory).be.a.Function;
		var dir = Ti.Filesystem.createTempDirectory();
		should.exist(dir);
		should.exist(dir.name);
		should(dir.exists()).be.true;
		should(dir.deleteDirectory()).be.true;
		should(dir.exists()).be.false;
	});

	// Check if createTempFile exists and make sure it does not throw exception
	it('createTempFile()', function () {
		should(Ti.Filesystem.createTempFile).not.be.undefined;
		should(Ti.Filesystem.createTempFile).be.a.Function;
		var file = Ti.Filesystem.createTempFile();
		should(file).be.ok; // not null or undefined. should(file).not.; causes a stack overflow somehow.
		should(file.name).be.a.String;
		should(file.exists()).be.true;
		should(file.deleteFile()).be.true;
		should(file.exists()).be.false;
	});

	// TIMOB-10107
	it.skip('multiLingualFilename', function() {
		var msg = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory, '網上廣東話輸入法.txt');
		should(msg.write('Appcelerator', true)).be.true;
		should(msg.exists()).be.true;
		should(msg.deleteFile()).be.true;
		should(msg.exists()).be.false;
	});
});
