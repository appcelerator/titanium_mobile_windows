/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities');

describe('Titanium.Blob', function () {
	it('apiName', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob).have.a.readOnlyProperty('apiName').which.is.a.String;
		should(blob.apiName).be.eql('Ti.Blob');
	});

	it.skip('constructed from File.read()', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob).be.an.Object;
		should(blob).be.an.instanceof(Ti.Blob);
	});

	it.skip('constructed from image', function (finish) {
		var window = Ti.UI.createWindow();
		var label = Ti.UI.createLabel({ text: 'test' });
		window.add(label);
		window.addEventListener('focus', function () {
			var blob = label.toImage(function (blob) {
				should(blob).be.an.Object;
				should(blob).be.an.instanceof(Ti.Blob);
				should(blob.getText()).equal(null);
				should(blob.width).be.a.Number;
				should(blob.width).be.above(0);
				should(blob.height).be.a.Number;
				should(blob.height).be.above(0);
				should(blob.length).be.a.Number;
				should(blob.size).be.a.Number;
				should(blob.size).equal(blob.width * blob.height);
				window.close();
				finish();
			});
		});
		window.open();
	});

	it('text', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.text).be.a.String;
		should(blob.text.length).be.above(0);
		should(blob.text).equal(blob.toString());
	});

	it('append', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		if (utilities.isIOS()) {
			should(blob.append).be.undefined;
		} else {
			should(blob.append).be.a.Function;
		}
		finish();
	});

	it('nativePath', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.nativePath).be.a.String;
		should(blob.nativePath.length).be.above(0);
	});

	it('mimeType', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.mimeType).be.a.String;
		should(blob.mimeType.length).be.above(0);
		should(blob.mimeType).be.eql('text/javascript');
	});

	it('length', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.length).be.a.Number;
		should(blob.length).be.above(0);
	});

	// Intentionally skip for Android, property not available. TODO For parity, add it?
	(utilities.isAndroid() ? it.skip : it)('size', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.size).be.a.Number;
		should(blob.size).be.above(0);
	});

	// FIXME Get working for iOS - I think app thinning is getting rid of Logo.png
	(utilities.isIOS() ? it.skip : it)('width', function () {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.width).be.a.Number;
		should(blob.width).be.eql(150);
	});

	// FIXME Get working for iOS - I think app thinning is getting rid of Logo.png
	(utilities.isIOS() ? it.skip : it)('height', function () {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.height).be.a.Number;
		should(blob.height).be.eql(150);
	});

	it('width of non-image', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.width).be.a.Number;
		should(blob.width).be.eql(0);
	});

	it('height of non-image', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.height).be.a.Number;
		should(blob.height).be.eql(0);
	});

	it('file', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		var file = blob.file;
		should(file.toString()).be.a.String;
		should(file.nativePath).be.eql(blob.nativePath);
	});

	// FIXME Get working for iOS - I think app thinning is getting rid of Logo.png
	(utilities.isIOS() ? it.skip : it)('imageAsCropped', function () {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageAsCropped({ width: 50, height: 60, x: 0, y: 0 });
			should(b).be.an.Object;
			should(b.width).be.eql(50);
			should(b.height).be.eql(60);
		}).not.throw();
	});

	// FIXME Get working for iOS - I think app thinning is getting rid of Logo.png
	(utilities.isIOS() ? it.skip : it)('imageAsResized', function () {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.imageAsResized).be.a.Function;
		should(function () {
			var b = blob.imageAsResized(50, 60);
			should(b).be.an.Object;
			should(b.width).be.eql(50);
			should(b.height).be.eql(60);
		}).not.throw();
	});

	// FIXME Get working for iOS - I think app thinning is getting rid of Logo.png
	(utilities.isIOS() ? it.skip : it)('imageAsThumbnail', function () {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.imageAsThumbnail).be.a.Function;
		should(function () {
			var b = blob.imageAsThumbnail(50);
			should(b).be.an.Object;
			should(b.width).eql(50);
			should(b.height).eql(50);
		}).not.throw();
	});

	// FIXME Get working for iOS - I think app thinning is getting rid of Logo.png
	(utilities.isIOS() ? it.skip : it)('imageWithAlpha', function () {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.imageWithAlpha).be.a.Function;
		should(function () {
			blob.imageWithAlpha();
		}).not.throw();
	});

	// FIXME Get working for iOS - I think app thinning is getting rid of Logo.png
	(utilities.isIOS() ? it.skip : it)('imageWithRoundedCorner', function () {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.imageWithRoundedCorner).be.a.Function;
		should(function () {
			blob.imageWithRoundedCorner(1);
		}).not.throw();
	});

	// FIXME Get working for iOS - I think app thinning is getting rid of Logo.png
	(utilities.isIOS() ? it.skip : it)('imageWithTransparentBorder', function () {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.imageWithTransparentBorder).be.a.Function;
		should(function () {
			blob.imageWithTransparentBorder(1);
		}).not.throw();
	});

	it('imageAsCropped of non-image', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageAsCropped({ width: 50, height: 60, x: 0, y: 0 });
			should(b).not.exist;
		}).not.throw();
	});

	it('imageAsResized of non-image', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageAsResized(50, 60);
			should(b).not.exist;
		}).not.throw();
	});

	it('imageAsThumbnail of non-image', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageAsThumbnail(50);
			should(b).not.exist;
		}).not.throw();
	});

	it('imageWithAlpha of non-image', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageWithAlpha();
			should(b).not.exist;
		}).not.throw();
	});

	it('imageWithRoundedCorner of non-image', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageWithRoundedCorner(1);
			should(b).not.exist;
		}).not.throw();
	});

	it('imageWithTransparentBorder of non-image', function () {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageWithTransparentBorder(1);
			should(b).not.exist;
		}).not.throw();
	});
});
