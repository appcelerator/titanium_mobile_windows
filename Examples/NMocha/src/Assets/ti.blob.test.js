/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.Blob', function () {
	it('apiName', function (finish) {
		should(Ti.Blob.apiName).be.eql('Ti.Blob');
		finish();
	});

	it.skip('constructed from File.read()', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob).be.an.Object;
		should(blob).be.an.instanceof(Ti.Blob);
		finish();
	});

	it.skip('constructed from image', function (finish) {
		var window = Ti.UI.createWindow();
		var label = Ti.UI.createLabel({ text: 'test' });
		window.add(label);
		window.addEventListener('focus', function () {
			var blob = label.toImage(function (blob) {
				should(blob).be.an.Object;
				should(blob).be.an.instanceof(Ti.Blob);
				should(blob.getText() === null).be.eql(true);
				should(blob.width).be.a.Number;
				should(blob.width > 0).be.true;
				should(blob.height).be.a.Number;
				should(blob.height > 0).be.true;
				should(blob.length).be.a.Number;
				should(blob.size).be.a.Number;
				should(blob.size == (blob.width * blob.height));
				window.close();
				finish();
			});
		});
		window.open();
	});

	it('text', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.text).be.a.String;
		should(blob.text.length > 0).be.true;
		should(blob.text == blob.toString());
		finish();
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

	it('nativePath', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.nativePath).be.a.String;
		should(blob.nativePath.length > 0).be.true;
		finish();
	});

	it('mimeType', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.mimeType).be.a.String;
		should(blob.mimeType.length > 0).be.true;
		should(blob.mimeType).be.eql('text/javascript');
		finish();
	});

	it('length', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.length).be.a.Number;
		should(blob.length > 0).be.true;
		finish();
	});

	it('size', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.size).be.a.Number;
		should(blob.size > 0).be.true;
		finish();
	});

	it('width', function (finish) {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.width).be.a.Number;
		should(blob.width).be.eql(150);
		finish();
	});

	it('height', function (finish) {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.height).be.a.Number;
		should(blob.height).be.eql(150);
		finish();
	});

	it('width of non-image', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.width).be.a.Number;
		should(blob.width).be.eql(0);
		finish();
	});

	it('height of non-image', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.height).be.a.Number;
		should(blob.height).be.eql(0);
		finish();
	});

	it('file', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		var file = blob.file;
		should(file.toString()).be.a.String;
		should(file.nativePath).be.eql(blob.nativePath);
		finish();
	});

	it('imageAsCropped', function (finish) {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageAsCropped({ width: 50, height: 60, x: 0, y: 0 });
			should(b).be.an.Object;
			should(b.width).be.eql(50);
			should(b.height).be.eql(60);
		}).not.throw();
		finish();
	});

	it('imageAsResized', function (finish) {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.imageAsResized).be.a.Function;
		should(function () {
			var b = blob.imageAsResized(50, 60);
			should(b).be.an.Object;
			should(b.width).be.eql(50);
			should(b.height).be.eql(60);
		}).not.throw();
		finish();
	});

	it('imageAsThumbnail', function (finish) {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.imageAsThumbnail).be.a.Function;
		should(function () {
			var b = blob.imageAsThumbnail(50);
			should(b).be.an.Object;
			should(b.width).eql(50);
			should(b.height).eql(50);
		}).not.throw();
		finish();
	});

	it('imageWithAlpha', function (finish) {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.imageWithAlpha).be.a.Function;
		should(function () {
			blob.imageWithAlpha();
		}).not.throw();
		finish();
	});

	it('imageWithRoundedCorner', function (finish) {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.imageWithRoundedCorner).be.a.Function;
		should(function () {
			blob.imageWithRoundedCorner(1);
		}).not.throw();
		finish();
	});

	it('imageWithTransparentBorder', function (finish) {
		var blob = Ti.Filesystem.getFile('Logo.png').read();
		should(blob.imageWithTransparentBorder).be.a.Function;
		should(function () {
			blob.imageWithTransparentBorder(1);
		}).not.throw();
		finish();
	});

	it('imageAsCropped of non-image', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageAsCropped({ width: 50, height: 60, x: 0, y: 0 });
			should(b).be.null;
		}).not.throw();
		finish();
	});

	it('imageAsResized of non-image', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageAsResized(50, 60);
			should(b).be.null;
		}).not.throw();
		finish();
	});

	it('imageAsThumbnail of non-image', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageAsThumbnail(50);
			should(b).be.null;
		}).not.throw();
		finish();
	});

	it('imageWithAlpha of non-image', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageWithAlpha();
			should(b).be.null;
		}).not.throw();
		finish();
	});

	it('imageWithRoundedCorner of non-image', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageWithRoundedCorner(1);
			should(b).be.null;
		}).not.throw();
		finish();
	});

	it('imageWithTransparentBorder of non-image', function (finish) {
		var blob = Ti.Filesystem.getFile('app.js').read();
		should(blob.imageAsCropped).be.a.Function;
		should(function () {
			var b = blob.imageWithTransparentBorder(1);
			should(b).be.null;
		}).not.throw();
		finish();
	});
});
