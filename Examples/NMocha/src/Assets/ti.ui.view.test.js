/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

require('ti-mocha');
var should = require('should'),
	utilities = require('./utilities/utilities'),
	didFocus = false,
	didPostLayout = false;

describe('Titanium.UI.View', function () {
	this.timeout(5000);

	beforeEach(function() {
		didFocus = false;
		didPostLayout = false;
	});

	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('backgroundColor/Image', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createView({ width:Ti.UI.FILL, height:Ti.UI.FILL });
		w.add(view);
		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
			should(view.backgroundColor).be.a.String;
			should(view.backgroundImage).be.a.String;
			view.backgroundColor = 'white';
			view.backgroundImage = 'Logo.png';
			should(view.backgroundColor).be.eql('white');
			should(view.backgroundImage).be.eql('Logo.png');
			setTimeout(function () {
				w.close();
				finish();
			}, 1000);
		});
		w.open();
	});

	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('backgroundFocusedColor/Image', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createView({ width:Ti.UI.FILL, height:Ti.UI.FILL });
		w.add(view);
		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
			should(view.backgroundFocusedColor).be.a.String;
			should(view.backgroundFocusedImage).be.a.String;
			view.backgroundFocusedColor = 'white';
			view.backgroundFocusedImage = 'Logo.png'
			should(view.backgroundFocusedColor).be.eql('white');
			should(view.backgroundFocusedImage).be.eql('Logo.png');
			setTimeout(function () {
				w.close();
				finish();
			}, 1000);
		});
		w.open();
	});

	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('backgroundSelectedColor/Image', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createView({ width:Ti.UI.FILL, height:Ti.UI.FILL });
		w.add(view);
		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
			should(view.backgroundSelectedColor).be.a.String;
			should(view.backgroundSelectedImage).be.a.String;
			view.backgroundSelectedColor = 'white';
			view.backgroundSelectedImage = 'Logo.png';
			should(view.backgroundSelectedColor).be.eql('white');
			should(view.backgroundSelectedImage).be.eql('Logo.png');
			setTimeout(function () {
				w.close();
				finish();
			}, 1000);
		});
		w.open();
	});

	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('backgroundDisabledColor/Image', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createView({ width:Ti.UI.FILL, height:Ti.UI.FILL });
		w.add(view);
		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
			should(view.backgroundDisabledColor).be.a.String;
			should(view.backgroundDisabledImage).be.a.String;
			view.backgroundDisabledColor = 'white';
			view.backgroundDisabledImage = 'Logo.png';
			should(view.backgroundDisabledColor).be.eql('white');
			should(view.backgroundDisabledImage).be.eql('Logo.png');
			setTimeout(function () {
				w.close();
				finish();
			}, 1000);
		});
		w.open();
	});

	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('backgroundGradient', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createView({ width:Ti.UI.FILL, height:Ti.UI.FILL });
		view.backgroundGradient = {
			type: 'linear',
			startPoint: { x: '0%', y: '50%' },
			endPoint: { x: '100%', y: '100%' },
			colors: [{ color: 'red', offset: 0.0 }, { color: 'blue', offset: 0.25 }, { color: 'red', offset: 1.0 }],
		};
		w.add(view);
		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
			should(view.backgroundGradient.type).be.eql('linear');
			should(view.backgroundGradient.startPoint).be.an.Object;
			should(view.backgroundGradient.endPoint).be.an.Object;
			should(view.backgroundGradient.colors).be.an.Array;
			setTimeout(function () {
				w.close();
				finish();
			}, 1000);
		});
		w.open();
	});

	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('border', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createView({ width:Ti.UI.FILL, height:Ti.UI.FILL });
		w.add(view);
		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
			should(view.borderColor).be.a.String;
			should(view.borderWidth).be.a.Number;
			view.borderColor = 'blue';
			view.borderWidth = 2;
			should(view.borderColor).be.eql('blue');
			should(view.borderWidth).be.eql(2);
			setTimeout(function () {
				w.close();
				finish();
			}, 1000);
		});
		w.open();
	});

	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('rect and size', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createView({ width:Ti.UI.FILL, height:Ti.UI.FILL });
		w.add(view);

		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
			setTimeout(function () {
				w.close();
				finish();
			}, 3000);
		});

		view.addEventListener('postlayout', function () {
			if (didPostLayout) return;
			didPostLayout = true;
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
		});
		w.open();
	});

	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('hide() and show() change visible property value', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});

		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
			Ti.API.info('Got focus event');
			should(w.visible).be.true;
			w.hide();
			should(w.visible).be.false;
			w.show();
			should(w.visible).be.true;
			setTimeout(function () {
				w.close();
				finish();
			}, 1000);
		});
		w.open();
	});

	// FIXME: Windows 10 Store app fails for this...need to figure out why.
	((utilities.isWindows10() && utilities.isWindowsDesktop()) ? it.skip : it)('animate (top)', function (finish) {
		var win = Ti.UI.createWindow(),
			view = Ti.UI.createView({
				backgroundColor:'red',
				width: 100, height: 100,
				left: 100,  top: 100
			});

		win.addEventListener('open', function() {
			var animation = Ti.UI.createAnimation({
				top: 150,
				duration: 1000,
			});

			animation.addEventListener('complete', function() {
				// make sure to give it a time to layout
				setTimeout(function(){
					should(view.rect.x).be.eql(100);
					should(view.rect.y).be.eql(150);
					should(view.left).be.eql(100);
					should(view.top).be.eql(100);
					win.close();
					finish();
				}, 500);
			});

			view.animate(animation);

		});
		win.add(view);
		win.open();
	});

	// FIXME: Windows 10 Store app fails for this...need to figure out why.
	((utilities.isWindows10() && utilities.isWindowsDesktop()) ? it.skip : it)('animate (left)', function (finish) {
		var win = Ti.UI.createWindow(),
			view = Ti.UI.createView({
				backgroundColor:'red',
				width: 100, height: 100,
				left: 100,  top: 100
			});

		win.addEventListener('open', function() {
			var animation = Ti.UI.createAnimation({
				left: 150,
				duration: 1000,
			});

			animation.addEventListener('complete', function() {
				// make sure to give it a time to layout
				setTimeout(function(){
					should(view.rect.x).be.eql(150);
					should(view.rect.y).be.eql(100);
					should(view.left).be.eql(100);
					should(view.top).be.eql(100);
					win.close();
					finish();
				}, 500);
			});

			view.animate(animation);

		});
		win.add(view);
		win.open();
	});

	// FIXME: Windows 10 Store app fails for this...need to figure out why.
	((utilities.isWindows10() && utilities.isWindowsDesktop()) ? it.skip : it)('TIMOB-20598', function (finish) {
		var win = Ti.UI.createWindow(),
			view = Ti.UI.createView({
				backgroundColor:'red',
				width: 100, height: 100,
				left: 100,  top: 100
			}),
			pos = 100, count = 0;

		function start() {
			var animation = Ti.UI.createAnimation({
				left: pos,
				duration: 1000,
			});
			animation.addEventListener('complete', function() {
				setTimeout(function(){
					should(view.rect.x).be.eql(pos);
					should(view.rect.y).be.eql(100);
					should(view.left).be.eql(100);
					should(view.top).be.eql(100);
					if (count > 1) {
						win.close();
						finish();
					} else {
						pos += 50;
						count++;
						start();
					}
				}, 500);
			});

			view.animate(animation);
		}

		win.addEventListener('open', function() {
			start();
		});
		win.add(view);
		win.open();
	});

	it('convertPointToView', function (finish) {
		var w = Ti.UI.createWindow(),
		a = Ti.UI.createView({backgroundColor:'red'}),
		b = Ti.UI.createView({ top: '100', backgroundColor: 'blue' });

		a.add(b);
		w.add(a);

		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
			setTimeout(function () {
				w.close();
				finish();
			}, 3000);
		});

		b.addEventListener('postlayout', function () {
			if (didPostLayout) return;
			didPostLayout = true;
			Ti.API.info('Got postlayout event');
			var result = b.convertPointToView({ x: 123, y: 23 }, a);
			should(result).be.an.Object;
			should(result.x).be.a.Number;
			should(result.y).be.a.Number;
			should(result.x).eql(123);
			should(result.y).eql(123);
		});
		w.open();
	});

	it('parent', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createView({ width:Ti.UI.FILL, height:Ti.UI.FILL });
		w.add(view);

		w.addEventListener('open', function () {

			should(view.parent).be.an.Object;
			should(view.parent).eql(w);
			should(view.getParent).be.a.Function;
			should(view.setParent).be.a.Function;
			should(view.getParent()).eql(w);

			// parent is not read-only
			view.setParent(null);
			should(view.parent).be.null;

			setTimeout(function () {
				w.close();
				finish();
			}, 1000);
		});

		w.open();
	});

});
