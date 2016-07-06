/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities');

describe('Titanium.UI.ScrollView', function () {
	it('apiName', function () {
		var scrollView = Ti.UI.createScrollView({});
		should(scrollView).have.readOnlyProperty('apiName').which.is.a.String;
		should(scrollView.apiName).be.eql('Ti.UI.ScrollView');
	});

	// FIXME Fails on Android, should default to true, but is undefined
	(utilities.isAndroid() ? it.skip : it)('canCancelEvents', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.canCancelEvents).be.a.Boolean; // TODO should default to true
	});

	((utilities.isAndroid() || utilities.isIOS()) ? it.skip : it)('contentHeight', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.contentHeight).be.a.String; // defaults to undefined on Android and iOS
	});

	it('contentOffset', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.contentOffset).be.an.Object;
		should(bar.contentOffset.x).be.a.Number;
		should(bar.contentOffset.y).be.a.Number;
	});

	((utilities.isAndroid() || utilities.isIOS()) ? it.skip : it)('contentWidth', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.contentWidth).be.a.String; // defaults to undefined on Android and iOS
	});

	// Intentionally skip on Android, not supported
	// FIXME Get working on iOS. Defaults to undefined. Is that OK?
	((utilities.isAndroid() || utilities.isIOS()) ? it.skip : it)('decelerationRate', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.decelerationRate).be.a.Number; // defaults to undefined on iOS
	});

	// FIXME Get working on IOS
	// Intentionally skip on Android, property not supported
	((utilities.isIOS() || utilities.isAndroid()) ? it.skip : it)('disableBounce', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.disableBounce).be.a.Boolean; // iOS returns undefined, default should be false
	});

	// FIXME Get working on IOS
	// Intentionally skip on Android, property not supported
	((utilities.isIOS() || utilities.isAndroid()) ? it.skip : it)('horizontalBounce', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.horizontalBounce).be.a.Boolean; // iOS returns undefined, default should be false
	});

	// iOS-only property
	(!utilities.isIOS() ? it.skip : it)('maxZoomScale', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.maxZoomScale).be.a.Number;
	});

	// iOS-only property
	(!utilities.isIOS() ? it.skip : it)('minZoomScale', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.minZoomScale).be.a.Number;
	});

	// Android-only property
	(!utilities.isAndroid() ? it.skip : it)('overScrollMode', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.overScrollMode).be.a.Number;
	});

	// Intentionally skip on Android, not supported
	// FIXME Get working on iOS. Defaults to undefined, is that OK?
	((utilities.isAndroid() || utilities.isIOS()) ? it.skip : it)('scrollIndicatorStyle', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.scrollIndicatorStyle).be.a.Number; // defaults to undefined on iOS
	});

	it('scrollingEnabled', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.scrollingEnabled).be.a.Boolean;
	});

	// Android-only property
	(!utilities.isAndroid() ? it.skip : it)('scrollType', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.scrollType).not.exist; // undefined by default
	});

	// FIXME Fix on Android and iOS
	((utilities.isAndroid() || utilities.isIOS()) ? it.skip : it)('showHorizontalScrollIndicator', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.showHorizontalScrollIndicator).be.a.Boolean; // defaults to undefined on Android, docs say default to false
	});

	// FIXME Fix on Android and iOS
	((utilities.isAndroid() || utilities.isIOS()) ? it.skip : it)('showVerticalScrollIndicator', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.showVerticalScrollIndicator).be.a.Boolean; // defaults to undefined on Android, docs say default to false
	});

	// FIXME Get working on IOS
	// Intentionally skip on Android, property not supported
	((utilities.isIOS() || utilities.isAndroid()) ? it.skip : it)('verticalBounce', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.verticalBounce).be.a.Boolean; // iOS returns undefined, default should be false
	});

	// Intentionally skip on Android, not supported
	(utilities.isAndroid() ? it.skip : it)('zoomScale', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.zoomScale).be.a.Number;
	});

	it('#scrollTo()', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.scrollTo).be.a.Function;
	});

	it('#scrollToBottom()', function () {
		var bar = Ti.UI.createScrollView({});
		should(bar.scrollToBottom).be.a.Function;
	});
});
