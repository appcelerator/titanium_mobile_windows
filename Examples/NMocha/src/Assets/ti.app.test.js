/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities');

describe('Titanium.App', function () {

	it('EVENT_ACCESSIBILITY_ANNOUNCEMENT', function () {
		should(Ti.App).have.constant('EVENT_ACCESSIBILITY_ANNOUNCEMENT').which.is.eql('accessibilityannouncement');
	});

	it('EVENT_ACCESSIBILITY_CHANGED', function () {
		should(Ti.App).have.constant('EVENT_ACCESSIBILITY_CHANGED').which.is.eql('accessibilitychanged');
	});

	// TODO Add tests for set* methods!

	it('apiName', function () {
		should(Ti.App.apiName).be.eql('Ti.App');
		should(Ti.App).have.readOnlyProperty('apiName').which.is.a.String;
	});

	it('accessibilityEnabled', function () {
		should(Ti.App).have.readOnlyProperty('accessibilityEnabled').which.is.a.Boolean;
	});

	it('getAccessibilityEnabled()', function () {
		should(Ti.App.getAccessibilityEnabled).be.a.Function;
		should(Ti.App.getAccessibilityEnabled()).be.a.Boolean;
	});

	it('analytics', function () {
		should(Ti.App).have.readOnlyProperty('analytics').which.is.a.Boolean;
	});

	it('getAnalytics()', function () {
		should(Ti.App.getAnalytics).be.a.Function;
		should(Ti.App.getAnalytics()).be.a.Boolean;
	});

	it('copyright', function () {
		should(Ti.App).have.readOnlyProperty('copyright').which.is.a.String;
	});

	it('getCopyright()', function () {
		should(Ti.App.getCopyright).be.a.Function;
		should(Ti.App.getCopyright()).be.a.String;
	});

	it('deployType', function () {
		should(Ti.App).have.readOnlyProperty('deployType').which.is.a.String;
	});

	it('getDeployType()', function () {
		should(Ti.App.getDeployType).be.a.Function;
		should(Ti.App.getDeployType()).be.a.String;
	});

	it('description', function () {
		should(Ti.App).have.readOnlyProperty('description').which.is.a.String;
	});

	it('getDescription()', function () {
		should(Ti.App.getDescription).be.a.Function;
		should(Ti.App.getDescription()).be.a.String;
	});

	(utilities.isIOS() ? it : it.skip)('disableNetworkActivityIndicator', function () {
		should(Ti.App.disableNetworkActivityIndicator).be.a.Boolean;
	});

	(utilities.isIOS() ? it : it.skip)('getDisableNetworkActivityIndicator()', function () {
		should(Ti.App.getDisableNetworkActivityIndicator).be.a.Function;
		should(Ti.App.getDisableNetworkActivityIndicator()).be.a.Boolean;
	});

	// FIXME Enable on iOS only once fixed. we get undefined
	it.skip('forceSplashAsSnapshot', function () {
		should(Ti.App.forceSplashAsSnapshot).be.a.Boolean;
	});

	// FIXME Enable on iOS only once fixed. we get undefined
	it.skip('getForceSplashAsSnapshot()', function () {
		should(Ti.App.getForceSplashAsSnapshot).be.a.Function;
		should(Ti.App.getForceSplashAsSnapshot()).be.a.Boolean;
	});

	it('guid', function () {
		should(Ti.App).have.readOnlyProperty('guid').which.is.a.String;
	});

	it('getGuid()', function () {
		should(Ti.App.getGuid).be.a.Function;
		should(Ti.App.getGuid()).be.a.String;
	});

	it('id', function () {
		should(Ti.App).have.readOnlyProperty('id').which.is.a.String;
	});

	it('getId()', function () {
		should(Ti.App.getId).be.a.Function;
		should(Ti.App.getId()).be.a.String;
	});

	(utilities.isAndroid() ? it.skip : it)('idleTimerDisabled', function () {
		should(Ti.App.idleTimerDisabled).be.a.Boolean;
	});

	(utilities.isAndroid() ? it.skip : it)('getIdleTimerDisabled()', function () {
		should(Ti.App.getIdleTimerDisabled).be.a.Function;
		should(Ti.App.getIdleTimerDisabled()).be.a.Boolean;
	});

	(utilities.isAndroid() ? it.skip : it)('installId', function () {
		should(Ti.App).have.readOnlyProperty('installId').which.is.a.String;
	});

	(utilities.isAndroid() ? it.skip : it)('getInstallId()', function () {
		should(Ti.App.getInstallId).be.a.Function;
		should(Ti.App.getInstallId()).be.a.String;
	});

	(utilities.isAndroid() ? it.skip : it)('keyboardVisible', function () {
		should(Ti.App).have.readOnlyProperty('keyboardVisible').which.is.a.Boolean;
	});

	(utilities.isAndroid() ? it.skip : it)('getKeyboardVisible()', function () {
		should(Ti.App.getKeyboardVisible).be.a.Function;
		should(Ti.App.getKeyboardVisible()).be.a.Boolean;
	});

	it('name', function () {
		should(Ti.App).have.readOnlyProperty('name').which.is.a.String;
	});

	it('getName()', function () {
		should(Ti.App.getName).be.a.Function;
		should(Ti.App.getName()).be.a.String;
	});

	(utilities.isWindows() ? it.skip : it)('proximityDetection', function () {
		should(Ti.App.proximityDetection).be.a.Boolean;
	});

	(utilities.isWindows() ? it.skip : it)('getProximityDetection()', function () {
		should(Ti.App.getProximityDetection).be.a.Function;
		should(Ti.App.getProximityDetection()).be.a.Boolean;
	});

	(utilities.isWindows() ? it.skip : it)('proximityState', function () {
		should(Ti.App.proximityState).be.a.Boolean;
	});

	(utilities.isWindows() ? it.skip : it)('getProximityState()', function () {
		should(Ti.App.getProximityState).be.a.Function;
		should(Ti.App.getProximityState()).be.a.Boolean;
	});

	it('publisher', function () {
		should(Ti.App).have.readOnlyProperty('publisher').which.is.a.String;
	});

	it('getPublisher()', function () {
		should(Ti.App.getPublisher).be.a.Function;
		should(Ti.App.getPublisher()).be.a.String;
	});

	it('sessionId', function () {
		should(Ti.App).have.readOnlyProperty('sessionId').which.is.a.String;
	});

	it('getSessionId()', function () {
		should(Ti.App.getSessionId).be.a.Function;
		should(Ti.App.getSessionId()).be.a.String;
	});

	it('url', function () {
		should(Ti.App).have.readOnlyProperty('url').which.is.a.String;
	});

	it('getUrl()', function () {
		should(Ti.App.getUrl).be.a.Function;
		should(Ti.App.getUrl()).be.a.String;
	});

	it('version', function () {
		should(Ti.App).have.readOnlyProperty('version').which.is.a.String;
	});

	it('getVersion()', function () {
		should(Ti.App.getVersion).be.a.Function;
		should(Ti.App.getVersion()).be.a.String;
	});
});
