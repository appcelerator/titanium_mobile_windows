/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

require('ti-mocha');
var should = require('should'),
	utilities = require('./utilities/utilities'),
	didFocus = false;

describe('Titanium.UI.Button', function () {

	beforeEach(function() {
		didFocus = false;
	});

	it('apiName', function (finish) {
		should(Ti.UI.Button.apiName).be.eql('Ti.UI.Button');
		finish();
	});

    it("title", function (finish) {
        var bar = Ti.UI.createButton({
            title: "this is some text"
        });
        should(bar.title).be.a.String;
        should(bar.getTitle).be.a.Function;
        should(bar.title).eql('this is some text');
        should(bar.getTitle()).eql('this is some text');
        bar.title = 'other text';
        should(bar.title).eql('other text');
        should(bar.getTitle()).eql('other text');
        finish();
    });

    it("titleid", function (finish) {
        var bar = Ti.UI.createButton({
            titleid: "this is my key"
        });
        should(bar.titleid).be.a.String;
        should(bar.getTitleid).be.a.Function;
        should(bar.titleid).eql('this is my key');
        should(bar.getTitleid()).eql('this is my key');
        should(bar.title).eql('this is my value');
        bar.titleid = 'other text';
        should(bar.titleid).eql('other text');
        should(bar.getTitleid()).eql('other text');
        should(bar.title).eql('this is my value'); // should retain old value if can't find key
        finish();
    });

	it('image(String)', function (finish) {
		this.timeout(5000);
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('open', function () {
			view.image = 'Logo.png';
			should(view.image).be.eql('Logo.png');
			setTimeout(function () {
				w.close();
				finish();
			}, 1000);
		});
		w.open();
	});

	it('image(Blob)', function (finish) {
		this.timeout(5000);
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('open', function () {
			view.image = Ti.Filesystem.getFile('Logo.png').read();
			should(view.image).be.an.Object;
			setTimeout(function () {
				w.close();
				finish();
			}, 1000);
		});
		w.open();
	});

	it('backgroundColor/Image', function (finish) {
		this.timeout(5000);
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('open', function () {
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

	it('backgroundFocusedColor/Image', function (finish) {
		this.timeout(5000);
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('open', function () {
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

	it('backgroundSelectedColor/Image', function (finish) {
		this.timeout(5000);
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('open', function () {
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

	it('backgroundDisabledColor/Image', function (finish) {
		this.timeout(5000);
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('open', function () {
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
		this.timeout(5000);
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
		w.addEventListener('open', function () {
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

	(utilities.isWindowsDesktop() ? it.skip : it)('border', function (finish) {
		this.timeout(5000);
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);
		w.addEventListener('open', function () {
			should(view.borderColor).be.a.String;
			should(view.borderWidth).be.a.String;
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

	(utilities.isWindowsDesktop() ? it.skip : it)('rect and size', function (finish) {
		this.timeout(5000);
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var view = Ti.UI.createButton({ title: 'push button' });
		w.add(view);

		w.addEventListener('open', function () {
			setTimeout(function () {
				w.close();
				finish();
			}, 3000);
		});

		view.addEventListener('postlayout', function () {
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
});
