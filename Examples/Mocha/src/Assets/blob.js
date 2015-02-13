/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe("blob", function () {
    it("Ti.Blob", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        should(blob).be.an.Object;
        finish();
    });
    it("Ti.Blob from image", function (finish) {
        var window = Ti.UI.createWindow();
        var label = Ti.UI.createLabel({ text: 'test' });
        window.add(label);
        window.addEventListener('focus', function () {
            var blob = label.toImage(function (blob) {
                should(blob).be.an.Object;
                should(blob.getText() === null).be.eql(true);
                should(blob.toString()).be.eql("[object Blob]");
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
    it("Ti.Blob.text", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        should(blob.text).be.a.String;
        should(blob.text.length > 0).be.true;
        should(blob.text == blob.toString());
        finish();
    });
    it("Ti.Blob.append", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        if (Ti.Platform.osname == 'iphone' || Ti.Platform.osname == 'ipad') {
            should(blob.append).be.undefined;
        } else {
            should(blob.append).be.a.Function;
        }
        finish();
    });
    it("Ti.Blob.nativePath", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        should(blob.nativePath).be.a.String;
        should(blob.nativePath.length > 0).be.true;
        finish();
    });
    it("Ti.Blob.mimeType", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        should(blob.mimeType).be.a.String;
        should(blob.mimeType.length > 0).be.true;
        should(blob.mimeType).be.eql("application/octet-stream");
        finish();
    });
    it("Ti.Blob.length", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        should(blob.length).be.a.Number;
        should(blob.length > 0).be.true;
        finish();
    });
    it("Ti.Blob.size", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        should(blob.size).be.a.Number;
        should(blob.size > 0).be.true;
        finish();
    });
    it("Ti.Blob.width", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        should(blob.width).be.a.Number;
        should(blob.width == 0).be.true;
        finish();
    });
    it("Ti.Blob.height", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        should(blob.height).be.a.Number;
        should(blob.height == 0).be.true;
        finish();
    });
    it("Ti.Blob.file", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        var file = blob.file;
        should(file).be.an.Object;
        should(file.toString()).be.eql("[object File]");
        should(file.nativePath).be.eql(blob.nativePath);
        finish();
    });
    it("Ti.Blob.imageAsCropped", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        if (Ti.Platform.osname == "windowsstore" || Ti.Platform.osname == "windowsphone") {
            should(blob.imageAsCropped).be.undefined;
        } else {
            should(blob.imageAsCropped).be.a.Function;
        }
        finish();
    });
    it("Ti.Blob.imageAsResized", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        if (Ti.Platform.osname == "windowsstore" || Ti.Platform.osname == "windowsphone") {
            should(blob.imageAsResized).be.undefined;
        } else {
            should(blob.imageAsResized).be.a.Function;
        }
        finish();
    });
    it("Ti.Blob.imageAsThumbnail", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        if (Ti.Platform.osname == "windowsstore" || Ti.Platform.osname == "windowsphone") {
            should(blob.imageAsThumbnail).be.undefined;
        } else {
            should(blob.imageAsThumbnail).be.a.Function;
        }
        finish();
    });
    it("Ti.Blob.imageWithAlpha", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        if (Ti.Platform.osname == "windowsstore" || Ti.Platform.osname == "windowsphone") {
            should(blob.imageWithAlpha).be.undefined;
        } else {
            should(blob.imageWithAlpha).be.a.Function;
        }
        finish();
    });
    it("Ti.Blob.imageWithRoundedCorner", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        if (Ti.Platform.osname == "windowsstore" || Ti.Platform.osname == "windowsphone") {
            should(blob.imageWithRoundedCorner).be.undefined;
        } else {
            should(blob.imageWithRoundedCorner).be.a.Function;
        }
        finish();
    });
    it("Ti.Blob.imageWithTransparentBorder", function (finish) {
        var blob = Ti.Filesystem.getFile('app.js').read();
        if (Ti.Platform.osname == "windowsstore" || Ti.Platform.osname == "windowsphone") {
            should(blob.imageWithTransparentBorder).be.undefined;
        } else {
            should(blob.imageWithTransparentBorder).be.a.Function;
        }
        finish();
    });
});
