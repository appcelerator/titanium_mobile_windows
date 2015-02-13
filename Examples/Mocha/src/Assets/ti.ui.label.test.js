
/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe("ui_label", function () {
    it("label_text", function (finish) {
        var label = Ti.UI.createLabel({
            text: "this is some text"
        });
        should(label.text).be.a.String;
        should(label.getText).be.a.Function;
        should(label.text).eql('this is some text');
        should(label.getText()).eql('this is some text');
        label.text = 'other text';
        should(label.text).eql('other text');
        should(label.getText()).eql('other text');
        finish();
    });

    it("label_text_align", function (finish) {
        var label = Ti.UI.createLabel({
            text: "this is some text",
            textAlign: 'center'
        });
        should(label.textAlign).be.a.String;
        should(label.getTextAlign).be.a.Function;
        should(label.textAlign).eql('center');
        should(label.getTextAlign()).eql('center');
        label.textAlign = 'right';
        should(label.textAlign).eql('right');
        should(label.getTextAlign()).eql('right');
        finish();
    });
    it("label_text_vertical_align", function (finish) {
        var label = Ti.UI.createLabel({
            text: "this is some text",
            verticalAlign: 'bottom'
        });
        should(label.verticalAlign).be.a.String;
        should(label.getVerticalAlign).be.a.Function;
        should(label.verticalAlign).eql('bottom');
        should(label.getVerticalAlign()).eql('bottom');
        label.verticalAlign = 'top';
        should(label.verticalAlign).eql('top');
        should(label.getVerticalAlign()).eql('top');
        finish();
    });

    // Turn on/off the addition of ellipses at the end of the label if the text is too large to fit.
    // Default: false
    it("label_text_ellipsize", function (finish) {
        var label = Ti.UI.createLabel({
            text: "this is some text"
        });
        should(label.ellipsize).be.a.Boolean;
        should(label.getEllipsize).be.a.Function;
        should(label.ellipsize).eql(false);
        should(label.getEllipsize()).eql(false);
        label.ellipsize = true;
        should(label.getEllipsize()).eql(true);
        should(label.ellipsize).eql(true);
        finish();
    });

    // Enable or disable word wrapping in the label.
    // Defaults: true
    it("label_text_word_wrap", function (finish) {
        var label = Ti.UI.createLabel({
            wordWrap: "this is some text"
        });
        should(label.wordWrap).be.a.Boolean;
        should(label.getWordWrap).be.a.Function;
        should(label.wordWrap).eql(true);
        should(label.getWordWrap()).eql(true);
        label.wordWrap = false;
        should(label.getWordWrap()).eql(false);
        should(label.wordWrap).eql(false);
        finish();
    });
    it("label_text_width_size", function (finish) {
        this.timeout(1000);
        var label = Ti.UI.createLabel({
            text: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec nec ullamcorper massa, eget tempor sapien. Phasellus nisi metus, tempus a magna nec, ultricies rutrum lacus. Aliquam sit amet augue suscipit, dignissim tellus eu, consectetur elit. Praesent ligula velit, blandit vel urna sit amet, suscipit euismod nunc.',
            width: Ti.UI.SIZE
        });
        var win = Ti.UI.createWindow({
            backgroundColor: '#ddd'
        });
        win.add(label);
        win.open();
        setTimeout(function () {
            should(win.size.width).be.greaterThan(100);
            should(label.size.width).not.be.greaterThan(win.size.width);
            win.close();
            finish();
        }, 100);
    });
    it("label_text_height_size", function (finish) {
        this.timeout(1000);
        var label = Ti.UI.createLabel({
            text: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec nec ullamcorper massa, eget tempor sapien. Phasellus nisi metus, tempus a magna nec, ultricies rutrum lacus. Aliquam sit amet augue suscipit, dignissim tellus eu, consectetur elit. Praesent ligula velit, blandit vel urna sit amet, suscipit euismod nunc.',
            width: Ti.UI.SIZE,
            height: Ti.UI.SIZE,
            color: 'black'
        });
        var bgView = Ti.UI.createView({
            width: 200, height: 100,
            backgroundColor: 'red'
        });
        var win = Ti.UI.createWindow({
            backgroundColor: '#eee'
        });
        bgView.add(label)
        win.add(bgView);

        setTimeout(function () {
            should(bgView.size.height).be.eql(100);
            should(label.size.height).not.be.greaterThan(100);
            win.close();
            finish();
        },100);
        win.open();
    });

});
