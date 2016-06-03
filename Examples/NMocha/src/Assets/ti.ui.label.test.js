/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities'),
	didFocus = false,
	didPostLayout = false;

describe('Titanium.UI.Label', function () {

	beforeEach(function() {
		didFocus = false;
		didPostLayout = false;
	});

	it('apiName', function (finish) {
		should(Ti.UI.Label.apiName).be.eql('Ti.UI.Label');
		finish();
	});

	it('text', function (finish) {
		var label = Ti.UI.createLabel({
			text: 'this is some text'
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

    it("textid", function (finish) {
        var label = Ti.UI.createLabel({
            textid: "this is my key"
        });
        should(label.textid).be.a.String;
        should(label.getTextid).be.a.Function;
        should(label.textid).eql('this is my key');
        should(label.getTextid()).eql('this is my key');
        should(label.text).eql('this is my value');
        label.textid = 'other text';
        should(label.textid).eql('other text');
        should(label.getTextid()).eql('other text');
        should(label.text).eql('other text'); // key is used when no resources found
        finish();
    });

	it('textAlign', function (finish) {
		var label = Ti.UI.createLabel({
			text: 'this is some text',
			textAlign: Titanium.UI.TEXT_ALIGNMENT_CENTER
		});
		should(label.textAlign).be.a.Number; // String on Android
		should(label.getTextAlign).be.a.Function;
		should(label.textAlign).eql(Titanium.UI.TEXT_ALIGNMENT_CENTER);
		should(label.getTextAlign()).eql(Titanium.UI.TEXT_ALIGNMENT_CENTER);
		label.textAlign = Titanium.UI.TEXT_ALIGNMENT_RIGHT;
		should(label.textAlign).eql(Titanium.UI.TEXT_ALIGNMENT_RIGHT);
		should(label.getTextAlign()).eql(Titanium.UI.TEXT_ALIGNMENT_RIGHT);
		finish();
	});

	it('verticalAlign', function (finish) {
		var label = Ti.UI.createLabel({
			text: 'this is some text',
			verticalAlign: Titanium.UI.TEXT_VERTICAL_ALIGNMENT_BOTTOM
		});
		should(label.verticalAlign).be.a.Number; // String on Android
		should(label.getVerticalAlign).be.a.Function;
		should(label.verticalAlign).eql(Titanium.UI.TEXT_VERTICAL_ALIGNMENT_BOTTOM);
		should(label.getVerticalAlign()).eql(Titanium.UI.TEXT_VERTICAL_ALIGNMENT_BOTTOM);
		label.verticalAlign = Titanium.UI.TEXT_VERTICAL_ALIGNMENT_TOP;
		should(label.verticalAlign).eql(Titanium.UI.TEXT_VERTICAL_ALIGNMENT_TOP);
		should(label.getVerticalAlign()).eql(Titanium.UI.TEXT_VERTICAL_ALIGNMENT_TOP);
		finish();
	});

	// Turn on/off the addition of ellipses at the end of the label if the text is too large to fit.
	// Default: false
	it('ellipsize', function (finish) {
		var label = Ti.UI.createLabel({
			text: 'this is some text'
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
	it('wordWrap', function (finish) {
		var label = Ti.UI.createLabel({
			text: 'this is some text'
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

	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('width', function (finish) {
		this.timeout(5000);
		var label = Ti.UI.createLabel({
			text: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec nec ullamcorper massa, eget tempor sapien. Phasellus nisi metus, tempus a magna nec, ultricies rutrum lacus. Aliquam sit amet augue suscipit, dignissim tellus eu, consectetur elit. Praesent ligula velit, blandit vel urna sit amet, suscipit euismod nunc.',
			width: Ti.UI.SIZE
		});
		var win = Ti.UI.createWindow({
			backgroundColor: '#ddd'
		});
		win.add(label);
		win.addEventListener('postlayout', function () {
			if (didPostLayout) return;
			didPostLayout = true;
			should(label.size.width).not.be.greaterThan(win.size.width);
		});
		win.addEventListener('focus', function() {
			if (didFocus) return;
			didFocus = true;
			setTimeout(function() {
				win.close();
				finish();
			}, 3000);
		});
		win.open();
	});
	it('height', function (finish) {
		this.timeout(5000);
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
		bgView.add(label);
		win.add(bgView);

		win.addEventListener('postlayout', function () {
			if (didPostLayout) return;
			didPostLayout = true;
			should(bgView.size.height).be.eql(100);
			// Uncomment below because it should be ok for label to have height greater than parent view
			// parent view should be able to handle which areas should be shown in that case.
			// should(label.size.height).not.be.greaterThan(100);
		});
		win.addEventListener('focus', function() {
			if (didFocus) return;
			didFocus = true;
			setTimeout(function() {
				win.close();
				finish();
			}, 3000);
		});
		win.open();
	});

});
