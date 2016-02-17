/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

require('ti-mocha');
var should = require('should'),
	didFocus = false,
	didPostLayout = false;

describe("Titanium.UI.View", function () {
	this.timeout(5000);

	beforeEach(function() {
		didFocus = false;
		didPostLayout = false;
	});

    ((Ti.Platform.version.indexOf('6.3.9600') == 0 && Ti.Platform.osname === 'windowsstore') ? it.skip : it)("backgroundColor/Image", function (finish) {
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
            view.backgroundColor = "white";
            view.backgroundImage = "Logo.png";
            should(view.backgroundColor).be.eql("white");
            should(view.backgroundImage).be.eql("Logo.png");
            setTimeout(function () {
                w.close();
                finish();
            }, 1000);
        });
        w.open();
    });

    ((Ti.Platform.version.indexOf('6.3.9600') == 0 && Ti.Platform.osname === 'windowsstore') ? it.skip : it)("backgroundFocusedColor/Image", function (finish) {
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
            view.backgroundFocusedColor = "white";
            view.backgroundFocusedImage = "Logo.png"
            should(view.backgroundFocusedColor).be.eql("white");
            should(view.backgroundFocusedImage).be.eql("Logo.png");
            setTimeout(function () {
                w.close();
                finish();
            }, 1000);
        });
        w.open();
    });

    ((Ti.Platform.version.indexOf('6.3.9600') == 0 && Ti.Platform.osname === 'windowsstore') ? it.skip : it)("backgroundSelectedColor/Image", function (finish) {
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
            view.backgroundSelectedColor = "white";
            view.backgroundSelectedImage = "Logo.png";
            should(view.backgroundSelectedColor).be.eql("white");
            should(view.backgroundSelectedImage).be.eql("Logo.png");
            setTimeout(function () {
                w.close();
                finish();
            }, 1000);
        });
        w.open();
    });

    ((Ti.Platform.version.indexOf('6.3.9600') == 0 && Ti.Platform.osname === 'windowsstore') ? it.skip : it)("backgroundDisabledColor/Image", function (finish) {
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
            view.backgroundDisabledColor = "white";
            view.backgroundDisabledImage = "Logo.png";
            should(view.backgroundDisabledColor).be.eql("white");
            should(view.backgroundDisabledImage).be.eql("Logo.png");
            setTimeout(function () {
                w.close();
                finish();
            }, 1000);
        });
        w.open();
    });

    ((Ti.Platform.version.indexOf('6.3.9600') == 0 && Ti.Platform.osname === 'windowsstore') ? it.skip : it)("backgroundGradient", function (finish) {
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
            should(view.backgroundGradient.type).be.eql("linear");
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

    ((Ti.Platform.version.indexOf('6.3.9600') == 0 && Ti.Platform.osname === 'windowsstore') ? it.skip : it)("border", function (finish) {
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
            view.borderColor = "blue";
            view.borderWidth = 2;
            should(view.borderColor).be.eql("blue");
            should(view.borderWidth).be.eql(2);
            setTimeout(function () {
                w.close();
                finish();
            }, 1000);
        });
        w.open();
    });

    ((Ti.Platform.version.indexOf('6.3.9600') == 0 && Ti.Platform.osname === 'windowsstore') ? it.skip : it)("rect and size", function (finish) {
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
            Ti.API.info("Got postlayout event");
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

    ((Ti.Platform.version.indexOf('6.3.9600') == 0 && Ti.Platform.osname === 'windowsstore') ? it.skip : it)("hide() and show() change visible property value", function (finish) {
        var w = Ti.UI.createWindow({
            backgroundColor: 'blue'
        });

        w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
            Ti.API.info("Got focus event");
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

	it("convertPointToView", function (finish) {
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
			Ti.API.info("Got postlayout event");
			var result = b.convertPointToView({ x: 123, y: 23 }, a);
			should(result).be.an.Object;
			should(result.x).be.a.Number;
			should(result.y).be.a.Number;
			should(result.x).eql(123);
			should(result.y).eql(123);
		});
		w.open();
	});
});
