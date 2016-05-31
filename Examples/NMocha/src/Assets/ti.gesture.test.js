/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.Gesture', function () {
	it('apiName', function (finish) {
		should(Ti.Gesture.apiName).be.eql('Ti.Gesture');
		finish();
	});

	it('Ti.Gesture', function (finish) {
		should(Ti.Gesture).not.be.undefined;
		should(Ti.Gesture.addEventListener).be.a.Function;
		should(Ti.Gesture.removeEventListener).be.a.Function;
		finish();
	});

	it('landscape', function (finish) {
		should(Ti.Gesture.landscape).not.be.undefined;
		should(Ti.Gesture.landscape).be.a.Boolean;
		finish();
	});

	it('portrait', function (finish) {
		should(Ti.Gesture.portrait).not.be.undefined;
		should(Ti.Gesture.portrait).be.a.Boolean;
		finish();
	});

	it('orientation', function (finish) {
		should(Ti.Gesture.orientation).not.be.undefined;
		should(Ti.Gesture.orientation).be.a.Number;
		finish();
	});

	it('getLandscape()', function (finish) {
		should(Ti.Gesture.getLandscape).not.be.undefined;
		should(Ti.Gesture.getLandscape).be.a.Function;
		should(Ti.Gesture.getLandscape()).be.a.Boolean;
		finish();
	});

	it('getPortrait()', function (finish) {
		should(Ti.Gesture.getPortrait).not.be.undefined;
		should(Ti.Gesture.getPortrait).be.a.Function;
		should(Ti.Gesture.getPortrait()).be.a.Boolean;
		finish();
	});

	it('isLandscape()', function (finish) {
		should(Ti.Gesture.isLandscape).not.be.undefined;
		should(Ti.Gesture.isLandscape).be.a.Function;
		should(Ti.Gesture.isLandscape()).be.a.Boolean;
		finish();
	});

	it('isPortrait()', function (finish) {
		should(Ti.Gesture.isPortrait).not.be.undefined;
		should(Ti.Gesture.isPortrait).be.a.Function;
		should(Ti.Gesture.isPortrait()).be.a.Boolean;
		finish();
	});

	it('isFaceDown()', function (finish) {
		should(Ti.Gesture.isFaceDown).not.be.undefined;
		should(Ti.Gesture.isFaceDown).be.a.Function;
		should(Ti.Gesture.isFaceDown()).be.a.Boolean;
		finish();
	});

	it('isFaceUp()', function (finish) {
		should(Ti.Gesture.isFaceUp).not.be.undefined;
		should(Ti.Gesture.isFaceUp).be.a.Function;
		should(Ti.Gesture.isFaceUp()).be.a.Boolean;
		finish();
	});

	it('getOrientation()', function (finish) {
		should(Ti.Gesture.getOrientation).not.be.undefined;
		should(Ti.Gesture.getOrientation).be.a.Function;
		should(Ti.Gesture.getOrientation()).be.a.Number;
		finish();
	});
});
