/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities'),
	didFocus = false;

describe('Titanium.UI.TextField', function () {

	beforeEach(function() {
		didFocus = false;
	});

	it('apiName', function () {
		var textField = Ti.UI.createTextField({
			value: 'this is some text'
		});
		should(textField).have.readOnlyProperty('apiName').which.is.a.String;
		should(textField.apiName).be.eql('Ti.UI.TextField');
	});

	it('value', function () {
		var textfield = Ti.UI.createTextField({
			value: 'this is some text'
		});
		should(textfield.value).be.a.String;
		should(textfield.getValue).be.a.Function;
		should(textfield.value).eql('this is some text');
		should(textfield.getValue()).eql('this is some text');
		textfield.value = 'other text';
		should(textfield.value).eql('other text');
		should(textfield.getValue()).eql('other text');
	});

	it('textAlign', function () {
		var textfield = Ti.UI.createTextField({
			value: 'this is some text',
			textAlign: Titanium.UI.TEXT_ALIGNMENT_CENTER
		});
		if (utilities.isAndroid()) {
			should(textfield.textAlign).be.a.String;
		} else {
			should(textfield.textAlign).be.a.Number;
		}
		should(textfield.getTextAlign).be.a.Function;
		should(textfield.textAlign).eql(Titanium.UI.TEXT_ALIGNMENT_CENTER);
		should(textfield.getTextAlign()).eql(Titanium.UI.TEXT_ALIGNMENT_CENTER);
		textfield.textAlign = Titanium.UI.TEXT_ALIGNMENT_RIGHT;
		should(textfield.textAlign).eql(Titanium.UI.TEXT_ALIGNMENT_RIGHT);
		should(textfield.getTextAlign()).eql(Titanium.UI.TEXT_ALIGNMENT_RIGHT);
	});

	it('verticalAlign', function () {
		var textfield = Ti.UI.createTextField({
			value: 'this is some text',
			verticalAlign: Titanium.UI.TEXT_VERTICAL_ALIGNMENT_BOTTOM
		});
		if (utilities.isAndroid()) {
			should(textfield.verticalAlign).be.a.String;
		} else {
			should(textfield.verticalAlign).be.a.Number;
		}
		should(textfield.getVerticalAlign).be.a.Function;
		should(textfield.verticalAlign).eql(Titanium.UI.TEXT_VERTICAL_ALIGNMENT_BOTTOM);
		should(textfield.getVerticalAlign()).eql(Titanium.UI.TEXT_VERTICAL_ALIGNMENT_BOTTOM);
		textfield.verticalAlign = Titanium.UI.TEXT_VERTICAL_ALIGNMENT_TOP;
		should(textfield.verticalAlign).eql(Titanium.UI.TEXT_VERTICAL_ALIGNMENT_TOP);
		should(textfield.getVerticalAlign()).eql(Titanium.UI.TEXT_VERTICAL_ALIGNMENT_TOP);
	});

	// FIXME Defaults to undefined on Android. Docs say default is false
	(utilities.isAndroid() ? it.skip : it)('passwordMask', function () {
		var text = 'this is some text',
			textfield = Ti.UI.createTextField({
				value: text
			});
		// passwordMask should default to false
		should(textfield.passwordMask).be.false; // undefined on Android
		textfield.passwordMask = true;
		should(textfield.passwordMask).be.true;
		// it should have same text before
		should(textfield.value).be.eql(text);
	});

	// TODO Add tests for:
	// autocapitalize
	// autocorrect
	// borderStyle
	// clearonEdit
	// color
	// editable
	// enableReturnKey
	// font
	// hintText
	// keyboardType
	// maxLength
	// returnKeyType
	// selection
	// suppressReturn

	it.skip('width', function (finish) {
		this.timeout(5000);
		var textfield = Ti.UI.createTextField({
			value: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec nec ullamcorper massa, eget tempor sapien. Phasellus nisi metus, tempus a magna nec, ultricies rutrum lacus. Aliquam sit amet augue suscipit, dignissim tellus eu, consectetur elit. Praesent ligula velit, blandit vel urna sit amet, suscipit euismod nunc.',
			width: Ti.UI.SIZE
		});
		var win = Ti.UI.createWindow({
			backgroundColor: '#ddd'
		});
		win.add(textfield);
		win.addEventListener('focus', function () {
			var error;

			try {
				should(win.width).be.greaterThan(100);
				should(textfield.width).not.be.greaterThan(win.width);
			} catch (err) {
				error = err;
			}

			setTimeout(function() {
				win.close();
				finish(error);
			}, 3000);
		});
		win.open();
	});

	// FIXME Intermittently failing on Android on build machine, I think due to test timeout
	(utilities.isAndroid() ? it.skip : it)('height', function (finish) {
		this.timeout(5000);
		var textfield = Ti.UI.createTextField({
				value: 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec nec ullamcorper massa, eget tempor sapien. Phasellus nisi metus, tempus a magna nec, ultricies rutrum lacus. Aliquam sit amet augue suscipit, dignissim tellus eu, consectetur elit. Praesent ligula velit, blandit vel urna sit amet, suscipit euismod nunc.',
				width: Ti.UI.SIZE,
				height: Ti.UI.SIZE,
				color: 'black'
			}),
			bgView = Ti.UI.createView({
				width: 200,
				height: 100,
				backgroundColor: 'red'
			}),
			win = Ti.UI.createWindow({
				backgroundColor: '#eee'
			});
		bgView.add(textfield);
		win.add(bgView);

		win.addEventListener('focus', function () {
			var error;

			if (didFocus) return;
			didFocus = true;

			try {
				should(bgView.height).be.eql(100);
				should(textfield.height).not.be.greaterThan(100);
			} catch (err) {
				error = err;
			}

			setTimeout(function() {
				win.close();
				finish(error);
			}, 3000);
		});
		win.open();
	});

});
