/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.App', function () {

	// Check if EVENT_ACCESSIBILITY_ANNOUNCEMENT exists and make sure it does not throw exception
	it('EVENT_ACCESSIBILITY_ANNOUNCEMENT', function () {
		should(function () {
			should(Ti.App.EVENT_ACCESSIBILITY_ANNOUNCEMENT).not.be.undefined;
			should(Ti.App.EVENT_ACCESSIBILITY_ANNOUNCEMENT).be.a.String;
			// make sure it is read-only value
			var value = Ti.App.EVENT_ACCESSIBILITY_ANNOUNCEMENT;
			Ti.App.EVENT_ACCESSIBILITY_ANNOUNCEMENT = 'try_to_overwrite_READONLY_value';
			should(Ti.App.EVENT_ACCESSIBILITY_ANNOUNCEMENT).be.eql(value);
		}).not.throw();
	});
	// Check if EVENT_ACCESSIBILITY_CHANGED exists and make sure it does not throw exception
	it('EVENT_ACCESSIBILITY_CHANGED', function () {
		should(function () {
			should(Ti.App.EVENT_ACCESSIBILITY_CHANGED).not.be.undefined;
			should(Ti.App.EVENT_ACCESSIBILITY_CHANGED).be.a.String;
			// make sure it is read-only value
			var value = Ti.App.EVENT_ACCESSIBILITY_CHANGED;
			Ti.App.EVENT_ACCESSIBILITY_CHANGED = 'try_to_overwrite_READONLY_value';
			should(Ti.App.EVENT_ACCESSIBILITY_CHANGED).be.eql(value);
		}).not.throw();
	});

	it('apiName', function () {
		should(Ti.App.apiName).be.eql('Ti.App');
	});

	it('deployType', function () {
		should(Ti.App.deployType).be.a.String;
		should(Ti.App.getDeployType).be.a.Function;
		should(Ti.App.getDeployType()).be.a.String;
	});

	it('id', function () {
		should(Ti.App.id).be.a.String;
		should(Ti.App.getId).be.a.Function;
		should(Ti.App.getId()).be.a.String;
	});

	it('publisher', function () {
		should(Ti.App.publisher).be.a.String;
		should(Ti.App.getPublisher).be.a.Function;
		should(Ti.App.getPublisher()).be.a.String;
	});

	it('url', function () {
		should(Ti.App.url).be.a.String;
		should(Ti.App.getUrl).be.a.Function;
		should(Ti.App.getUrl()).be.a.String;
	});

	it('name', function () {
		should(Ti.App.name).be.a.String;
		should(Ti.App.getName).be.a.Function;
		should(Ti.App.getName()).be.a.String;
	});

	it('version', function () {
		should(Ti.App.version).be.a.String;
		should(Ti.App.getVersion).be.a.Function;
		should(Ti.App.getVersion()).be.a.String;
	});

	it('description', function () {
		should(Ti.App.description).be.a.String;
		should(Ti.App.getDescription).be.a.Function;
		should(Ti.App.getDescription()).be.a.String;
	});

	it('copyright', function () {
		should(Ti.App.copyright).be.a.String;
		should(Ti.App.getCopyright).be.a.Function;
		should(Ti.App.getCopyright()).be.a.String;
	});

	it('guid', function () {
		should(Ti.App.guid).be.a.String;
		should(Ti.App.getGuid).be.a.Function;
		should(Ti.App.getGuid()).be.a.String;
	});

	it('analytics', function () {
		should(Ti.App.analytics).be.a.Boolean;
		should(Ti.App.getAnalytics).be.a.Function;
		should(Ti.App.getAnalytics()).be.a.Boolean;
	});

	it('accessibilityEnabled', function () {
		should(Ti.App.accessibilityEnabled).be.a.Boolean;
		should(Ti.App.getAccessibilityEnabled).be.a.Function;
		should(Ti.App.getAccessibilityEnabled()).be.a.Boolean;
	});

	it('disableNetworkActivityIndicator', function () {
		should(Ti.App.disableNetworkActivityIndicator).be.a.Boolean;
		should(Ti.App.getDisableNetworkActivityIndicator).be.a.Function;
		should(Ti.App.getDisableNetworkActivityIndicator()).be.a.Boolean;
	});

	it('forceSplashAsSnapshot', function () {
		should(Ti.App.forceSplashAsSnapshot).be.a.Boolean;
		should(Ti.App.getForceSplashAsSnapshot).be.a.Function;
		should(Ti.App.getForceSplashAsSnapshot()).be.a.Boolean;
	});

	it('idleTimerDisabled', function () {
		should(Ti.App.idleTimerDisabled).be.a.Boolean;
		should(Ti.App.getIdleTimerDisabled).be.a.Function;
		should(Ti.App.getIdleTimerDisabled()).be.a.Boolean;
	});

	it('installId', function () {
		should(Ti.App.installId).be.a.String;
		should(Ti.App.getInstallId).be.a.Function;
		should(Ti.App.getInstallId()).be.a.String;
	});

	it('keyboardVisible', function () {
		should(Ti.App.keyboardVisible).be.a.Boolean;
		should(Ti.App.getKeyboardVisible).be.a.Function;
		should(Ti.App.getKeyboardVisible()).be.a.Boolean;
	});

	it('proximityDetection', function () {
		should(Ti.App.proximityDetection).be.a.Boolean;
		should(Ti.App.getProximityDetection).be.a.Function;
		should(Ti.App.getProximityDetection()).be.a.Boolean;
	});

	it('proximityState', function () {
		should(Ti.App.proximityState).be.a.Boolean;
		should(Ti.App.getProximityState).be.a.Function;
		should(Ti.App.getProximityState()).be.a.Boolean;
	});

	it('sessionId', function () {
		should(Ti.App.sessionId).be.a.String;
		should(Ti.App.getSessionId).be.a.Function;
		should(Ti.App.getSessionId()).be.a.String;
		should(Ti.App.getSessionId()).not.eql('__SESSION_ID__');
	});
});
