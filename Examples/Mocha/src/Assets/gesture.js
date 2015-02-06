/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe('gesture', function () {
    it('Ti.Gesture', function (finish) {
        should(Ti.Gesture).not.be.undefined;
        should(Ti.Gesture).be.an.Object;
        should(Ti.Gesture.addEventListener).be.a.Function;
        should(Ti.Gesture.removeEventListener).be.a.Function;
        finish();
    });
    it('Ti.Gesture.landscape', function (finish) {
        should(Ti.Gesture.landscape).not.be.undefined;
        should(Ti.Gesture.landscape).be.a.Boolean;
        finish();
    });
    it('Ti.Gesture.portrait', function (finish) {
        should(Ti.Gesture.portrait).not.be.undefined;
        should(Ti.Gesture.portrait).be.a.Boolean;
        finish();
    });
    it('Ti.Gesture.orientation', function (finish) {
        should(Ti.Gesture.orientation).not.be.undefined;
        should(Ti.Gesture.orientation).be.a.Number;
        finish();
    });
    it('Ti.UI.PORTRAIT', function (finish) {
        should(Ti.UI.PORTRAIT).not.be.undefined;
        should(Ti.UI.PORTRAIT).be.a.Number;
        finish();
    });
    it('Ti.UI.UPSIDE_PORTRAIT', function (finish) {
        should(Ti.UI.UPSIDE_PORTRAIT).not.be.undefined;
        should(Ti.UI.UPSIDE_PORTRAIT).be.a.Number;
        finish();
    });
    it('Ti.UI.LANDSCAPE_LEFT', function (finish) {
        should(Ti.UI.LANDSCAPE_LEFT).not.be.undefined;
        should(Ti.UI.LANDSCAPE_LEFT).be.a.Number;
        finish();
    });
    it('Ti.UI.LANDSCAPE_RIGHT', function (finish) {
        should(Ti.UI.LANDSCAPE_RIGHT).not.be.undefined;
        should(Ti.UI.LANDSCAPE_RIGHT).be.a.Number;
        finish();
    });
    it('Ti.UI.FACE_UP', function (finish) {
        should(Ti.UI.FACE_UP).not.be.undefined;
        should(Ti.UI.FACE_UP).be.a.Number;
        finish();
    });
    it('Ti.UI.UNKNOWN', function (finish) {
        should(Ti.UI.UNKNOWN).not.be.undefined;
        should(Ti.UI.UNKNOWN).be.a.Number;
        finish();
    });
    it('Ti.Gesture.getLandscape', function (finish) {
        should(Ti.Gesture.getLandscape).not.be.undefined;
        should(Ti.Gesture.getLandscape).be.a.Function;
        should(Ti.Gesture.getLandscape()).be.a.Boolean;
        finish();
    });
    it('Ti.Gesture.getPortrait', function (finish) {
        should(Ti.Gesture.getPortrait).not.be.undefined;
        should(Ti.Gesture.getPortrait).be.a.Function;
        should(Ti.Gesture.getPortrait()).be.a.Boolean;
        finish();
    });
    it('Ti.Gesture.isLandscape', function (finish) {
        should(Ti.Gesture.isLandscape).not.be.undefined;
        should(Ti.Gesture.isLandscape).be.a.Function;
        should(Ti.Gesture.isLandscape()).be.a.Boolean;
        finish();
    });
    it('Ti.Gesture.isPortrait', function (finish) {
        should(Ti.Gesture.isPortrait).not.be.undefined;
        should(Ti.Gesture.isPortrait).be.a.Function;
        should(Ti.Gesture.isPortrait()).be.a.Boolean;
        finish();
    });
    it('Ti.Gesture.isFaceDown', function (finish) {
        should(Ti.Gesture.isFaceDown).not.be.undefined;
        should(Ti.Gesture.isFaceDown).be.a.Function;
        should(Ti.Gesture.isFaceDown()).be.a.Boolean;
        finish();
    });
    it('Ti.Gesture.isFaceUp', function (finish) {
        should(Ti.Gesture.isFaceUp).not.be.undefined;
        should(Ti.Gesture.isFaceUp).be.a.Function;
        should(Ti.Gesture.isFaceUp()).be.a.Boolean;
        finish();
    });
    it('Ti.Gesture.getOrientation', function (finish) {
        should(Ti.Gesture.getOrientation).not.be.undefined;
        should(Ti.Gesture.getOrientation).be.a.Function;
        should(Ti.Gesture.getOrientation()).be.a.Number;
        finish();
    });
});
