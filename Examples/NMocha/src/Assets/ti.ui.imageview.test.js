/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.UI.ImageView', function () {
	this.timeout(5000);

	it('apiName', function (finish) {
		should(Ti.UI.ImageView.apiName).be.eql('Ti.UI.ImageView');
		finish();
	});


	it('image (URL)', function (finish) {
		var imageView = Ti.UI.createImageView({
			image: 'https://www.google.com/images/srpr/logo11w.png'
		});
		should(imageView.image).be.a.String;
		should(imageView.getImage).be.a.Function;
		should(imageView.image).eql('https://www.google.com/images/srpr/logo11w.png');
		should(imageView.getImage()).eql('https://www.google.com/images/srpr/logo11w.png');
		imageView.image = 'path/to/logo.png';
		should(imageView.image).eql('path/to/logo.png');
		should(imageView.getImage()).eql('path/to/logo.png');
		finish();
	});

	(utilities.isWindows() ? it : it.skip)('image (local path)', function (finish) {
		var imageView = Ti.UI.createImageView();
		imageView.addEventListener('load', function() {
			should(imageView.image).be.a.String;
			should(imageView.image).eql(Ti.Filesystem.resourcesDirectory + 'Logo.png');
			finish();
		});
		imageView.image = Ti.Filesystem.resourcesDirectory + 'Logo.png';
	});

	(utilities.isWindows() ? it : it.skip)('image (local path with separator)', function (finish) {
		var imageView = Ti.UI.createImageView();
		imageView.addEventListener('load', function() {
			should(imageView.image).be.a.String;
			should(imageView.image).eql(Ti.Filesystem.resourcesDirectory + Ti.Filesystem.separator + 'Logo.png');
			finish();
		});
		// Try appending separator
		// It's not quite clear if we needs separator, but people often do this
		imageView.image = Ti.Filesystem.resourcesDirectory + Ti.Filesystem.separator + 'Logo.png';
	});

	(utilities.isWindows() ? it : it.skip)('image (local path with /)', function (finish) {
		var imageView = Ti.UI.createImageView();
		imageView.addEventListener('load', function() {
			should(imageView.image).be.a.String;
			should(imageView.image).eql(Ti.Filesystem.resourcesDirectory + '/' + 'Logo.png');
			finish();
		});
		// Try appending '/' for the separator
		// Technically this is not right on Windows, but people often do this
		imageView.image = Ti.Filesystem.resourcesDirectory + '/' + 'Logo.png';
	});

	(utilities.isWindows() ? it : it.skip)('image (nativePath)', function (finish) {
		var fromFile = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory, 'Logo.png');
		var imageView = Ti.UI.createImageView();
		imageView.addEventListener('load', function() {
			should(imageView.image).be.a.String;
			should(imageView.image).eql(Ti.Filesystem.resourcesDirectory + 'Logo.png');
			finish();
		});
		imageView.image = fromFile.nativePath;
	});

	(utilities.isWindows() ? it : it.skip)('image (ms-appx)', function (finish) {
		var imageView = Ti.UI.createImageView();
		imageView.addEventListener('load', function() {
			should(imageView.image).be.a.String;
			should(imageView.image).eql('ms-appx:///Logo.png');

			finish();
		});
		imageView.image = 'ms-appx:///Logo.png';
	});

	(utilities.isWindows() ? it : it.skip)('image (ms-appdata)', function (finish) {
		var fromFile = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory, 'Logo.png');
		var toFile = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory + 'TIMOB-20609.png');
		toFile.write(fromFile.read());

		var imageView = Ti.UI.createImageView();
		imageView.addEventListener('load', function() {
			should(imageView.image).be.a.String;
			should(imageView.image).eql('ms-appdata:///local/TIMOB-20609.png');
			toFile.deleteFile();
			finish();
		});

		imageView.image = 'ms-appdata:///local/TIMOB-20609.png';
	});

	(utilities.isWindows() ? it : it.skip)('image (File)', function (finish) {
		var fromFile = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory, 'Logo.png');

		var imageView = Ti.UI.createImageView();
		imageView.addEventListener('load', function() {
			should(imageView.image).be.an.Object;
			should(imageView.image).eql(fromFile);
			finish();
		});

		imageView.image = fromFile;
	});

	(utilities.isWindows() ? it : it.skip)('image (Blob)', function (finish) {
		var fromFile = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory, 'Logo.png'),
			blob = fromFile.read();
		var imageView = Ti.UI.createImageView();
		imageView.addEventListener('load', function() {
			should(imageView.image).be.an.Object;
			should(imageView.toBlob()).eql(blob);
			finish();
		});

		imageView.image = blob;
	});

	(utilities.isWindows() ? it : it.skip)('images', function (finish) {
		this.timeout(6e4);
		var win = Ti.UI.createWindow();
		var imageView = Ti.UI.createImageView({
			width: Ti.UI.FILL, height: Ti.UI.FILL
		});
		imageView.addEventListener('start', function(){
			should(imageView.animating).be.true;
			win.close();
			finish();
		});
		imageView.addEventListener('load', function() {
			should(imageView.animating).be.false;
			imageView.start();
		});
		win.addEventListener('open', function() {
			imageView.images = [
				'ms-appx:///Logo.png',
				'ms-appx:///Logo.png',
				'ms-appx:///Logo.png'
			];
		});
		win.add(imageView);
		win.open();
	});

	(utilities.isWindows() ? it : it.skip)('images (File)', function (finish) {
		this.timeout(6e4);
		var win = Ti.UI.createWindow();
		var imageView = Ti.UI.createImageView({
			width: Ti.UI.FILL, height: Ti.UI.FILL
		});
		imageView.addEventListener('start', function(){
			should(imageView.animating).be.true;
			win.close();
			finish();
		});
		imageView.addEventListener('load', function() {
			should(imageView.animating).be.false;
			imageView.start();
		});
		win.addEventListener('open', function() {
			var fromFile = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory, 'Logo.png');
			imageView.images = [ fromFile, fromFile, fromFile ];
		});

		win.add(imageView);
		win.open();
	});

	(utilities.isWindows() ? it : it.skip)('images (Blob)', function (finish) {
		this.timeout(6e4);
		var win = Ti.UI.createWindow();
		var imageView = Ti.UI.createImageView({
			width: Ti.UI.FILL, height: Ti.UI.FILL
		});

		imageView.addEventListener('start', function(){
			should(imageView.animating).be.true;
			win.close();
			finish();
		});
		imageView.addEventListener('load', function() {
			should(imageView.animating).be.false;
			imageView.start();
		});
		win.addEventListener('open', function() {
			var fromFile = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory, 'Logo.png');
			imageView.images = [ fromFile.read(), fromFile.read(), fromFile.read() ];
		});

		win.add(imageView);
		win.open();
	});

	// TIMOB-18684
	it('layoutWithSIZE_and_fixed', function (finish) {
		var win = Ti.UI.createWindow();
		var view = Ti.UI.createView({
			backgroundColor: 'green',
			width: 100,
			height: Ti.UI.SIZE
		});
		var innerView = Ti.UI.createImageView({
			image: 'http://api.randomuser.me/portraits/women/0.jpg',
			width: 100,
			height: Ti.UI.SIZE,
			top: 0,
			left: 0
		});
		view.add(innerView);
		innerView.addEventListener('load', function (e) {
			setTimeout(function () {
				should(innerView.size.height).eql(100);
				should(view.size.height).eql(innerView.size.height);
				should(view.size.width).eql(innerView.size.width);
				win.close();
				finish();
			}, 1000);
		});
		win.add(view);
		win.open();
	});
});
