/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

require('ti-mocha');
var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities'),
	didFocus = false;

describe('Titanium.UI.Button', function () {

	this.timeout(5000);

	beforeEach(function() {
		didFocus = false;
	});

	it('apiName', function () {
		var button = Ti.UI.createButton({
			title: 'this is some text'
		});
		should(button).have.readOnlyProperty('apiName').which.is.a.String;
		should(button.apiName).be.eql('Ti.UI.Button');
	});

	it('title', function () {
		var bar = Ti.UI.createButton({
			title: 'this is some text'
		});
		should(bar.title).be.a.String;
		should(bar.getTitle).be.a.Function;
		should(bar.title).eql('this is some text');
		should(bar.getTitle()).eql('this is some text');
		bar.title = 'other text';
		should(bar.title).eql('other text');
		should(bar.getTitle()).eql('other text');
	});

	// FIXME Parity issue - iOS and Android retains old title if titleid can't be found, Windows uses key
	it('titleid', function () {
		var bar = Ti.UI.createButton({
			titleid: 'this_is_my_key'
		});
		should(bar.titleid).be.a.String;
		should(bar.getTitleid).be.a.Function;
		should(bar.titleid).eql('this_is_my_key');
		should(bar.getTitleid()).eql('this_is_my_key');
		should(bar.title).eql('this is my value');
		bar.titleid = 'other text'; // key won't get found!
		should(bar.titleid).eql('other text');
		should(bar.getTitleid()).eql('other text');
		should(bar.title).eql('this is my value'); // should retain old value if can't find key! https://jira.appcelerator.org/browse/TIMOB-23498
	});

	it('image(String)', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('focus', function () {
			var error;

			if (didFocus) return;
			didFocus = true;

			try {
				view.image = 'Logo.png';
				should(view.image).be.eql('Logo.png');
			} catch (err) {
				error = err;
			}

			setTimeout(function () {
				w.close();
				finish(error);
			}, 1000);
		});
		w.open();
	});

	// Skip on Windows 10 and 8.1 desktop for now, it hangs
	// FIXME iOS getFile().read() returns null for Logo.png
	(utilities.isWindows10() || (utilities.isWindows8_1() && utilities.isWindowsDesktop() || utilities.isIOS()) ? it.skip : it)('image(Blob)', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('focus', function () {
			var error;

			if (didFocus) return;
			didFocus = true;

			try {
				view.image = Ti.Filesystem.getFile('Logo.png').read();
				should(view.image).be.an.Object; // ios gives null
			} catch (err) {
				error = err;
			}
			setTimeout(function () {
				w.close();
				finish(error);
			}, 1000);
		});
		w.open();
	});

	// FIXME Get working on iOS and Android. borderColor defaults to undefined there, we're verifying it's a String
	((utilities.isWindowsDesktop() || utilities.isIOS() || utilities.isAndroid()) ? it.skip : it)('backgroundColor/Image', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('focus', function () {
			var error;

			if (didFocus) return;
			didFocus = true;

			try {
				should(view.backgroundColor).be.a.String; // undefined on iOS and Android
				should(view.backgroundImage).be.a.String;
				view.backgroundColor = 'white';
				view.backgroundImage = 'Logo.png';
				should(view.backgroundColor).be.eql('white');
				should(view.backgroundImage).be.eql('Logo.png');
			} catch (err) {
				error = err;
			}

			setTimeout(function () {
				w.close();
				finish(error);
			}, 1000);
		});
		w.open();
	});

	// FIXME Get working on iOS and Android. borderColor defaults to undefined there, we're verifying it's a String
	(((utilities.isWindows8_1() && utilities.isWindowsDesktop()) || utilities.isIOS() || utilities.isAndroid()) ? it.skip : it)('backgroundFocusedColor/Image', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('focus', function () {
			var error;

			if (didFocus) return;
			didFocus = true;

			try {
				should(view.backgroundFocusedColor).be.a.String; // undefined on iOS and Android
				should(view.backgroundFocusedImage).be.a.String;
				view.backgroundFocusedColor = 'white';
				view.backgroundFocusedImage = 'Logo.png'
				should(view.backgroundFocusedColor).be.eql('white');
				should(view.backgroundFocusedImage).be.eql('Logo.png');
			} catch (err) {
				error = err;
			}

			setTimeout(function () {
				w.close();
				finish(error);
			}, 1000);
		});
		w.open();
	});

	// FIXME Get working on iOS and Android. borderColor defaults to undefined there, we're verifying it's a String
	(((utilities.isWindows8_1() && utilities.isWindowsDesktop()) || utilities.isIOS() || utilities.isAndroid()) ? it.skip : it)('backgroundSelectedColor/Image', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('focus', function () {
			var error;

			if (didFocus) return;
			didFocus = true;

			try {
				should(view.backgroundSelectedColor).be.a.String; // undefined on iOS and Android
				should(view.backgroundSelectedImage).be.a.String;
				view.backgroundSelectedColor = 'white';
				view.backgroundSelectedImage = 'Logo.png';
				should(view.backgroundSelectedColor).be.eql('white');
				should(view.backgroundSelectedImage).be.eql('Logo.png');
			} catch (err) {
				error = err;
			}

			setTimeout(function () {
				w.close();
				finish(error);
			}, 1000);
		});
		w.open();
	});

	// FIXME Get working on iOS and Android. borderColor defaults to undefined there, we're verifying it's a String
	(((utilities.isWindows8_1() && utilities.isWindowsDesktop()) || utilities.isIOS() || utilities.isAndroid()) ? it.skip : it)('backgroundDisabledColor/Image', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('focus', function () {
			var error;

			if (didFocus) return;
			didFocus = true;

			try {
				should(view.backgroundDisabledColor).be.a.String; // undefined on iOS and Android
				should(view.backgroundDisabledImage).be.a.String;
				view.backgroundDisabledColor = 'white';
				view.backgroundDisabledImage = 'Logo.png';
				should(view.backgroundDisabledColor).be.eql('white');
				should(view.backgroundDisabledImage).be.eql('Logo.png');
			} catch (err) {
				error = err;
			}

			setTimeout(function () {
				w.close();
				finish(error);
			}, 1000);
		});
		w.open();
	});

	// FIXME Get working on iOS
	(((utilities.isWindows8_1() && utilities.isWindowsDesktop()) || utilities.isIOS()) ? it.skip : it)('backgroundGradient', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		view.backgroundGradient = {
			type: 'linear',
			startPoint: { x: '0%', y: '50%' },
			endPoint: { x: '100%', y: '100%' },
			colors: [{ color: 'red', offset: 0.0 }, { color: 'blue', offset: 0.25 }, { color: 'red', offset: 1.0 }],
		};
		w.add(view);
		w.addEventListener('focus', function () {
			var error;

			if (didFocus) return;
			didFocus = true;

			try {
				should(view.backgroundGradient.type).be.eql('linear');
				should(view.backgroundGradient.startPoint).be.an.Object;
				should(view.backgroundGradient.endPoint).be.an.Object;
				should(view.backgroundGradient.colors).be.an.Array; // undefined on iOS
			} catch (err) {
				error = err;
			}

			setTimeout(function () {
				w.close();
				finish(error);
			}, 1000);
		});
		w.open();
	});

	// FIXME Get working on iOS and Android. borderColor defaults to undefined there, we're verifying it's a String
	(((utilities.isWindows8_1() && utilities.isWindowsDesktop()) || utilities.isIOS() || utilities.isAndroid()) ? it.skip : it)('border', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('focus', function () {
			var error;

			if (didFocus) return;
			didFocus = true;

			try {
				should(view.borderColor).be.a.String; // undefined on iOS and Android
				should(view.borderWidth).be.a.Number;
				view.borderColor = 'blue';
				view.borderWidth = 2;
				should(view.borderColor).be.eql('blue');
				should(view.borderWidth).be.eql(2);
			} catch (err) {
				error = err;
			}

			setTimeout(function () {
				w.close();
				finish(error);
			}, 1000);
		});
		w.open();
	});

	// FIXME Intermittently failing on Android build machine - I think due to test timeout!
	(((utilities.isWindows8_1() && utilities.isWindowsDesktop()) || utilities.isAndroid()) ? it.skip : it)('rect and size', function (finish) {
		var w = Ti.UI.createWindow({
				backgroundColor: 'blue'
			}),
			view = Ti.UI.createButton({ title: 'push button' }),
			error;
		w.add(view);

		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;

			setTimeout(function () {
				w.close();
				finish(error);
			}, 3000);
		});

		view.addEventListener('postlayout', function () {
			try {
				Ti.API.info('Got postlayout event');
				Ti.API.info(JSON.stringify(view.rect));
				Ti.API.info(JSON.stringify(view.size));
				should(view.rect).be.an.Object;
				should(view.rect.width).be.above(0);
				should(view.rect.height).be.above(0);
				should(view.rect.x).be.a.Number;
				should(view.rect.y).be.a.Number;
				should(view.size.width).be.above(0);
				should(view.size.height).be.above(0);
			} catch (err) {
				error = err;
			}
		});
		w.open();
	});
});
