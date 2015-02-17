/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

Array.prototype.contains = function (obj) {
    var i = this.length;
    while (i--) if (this[i] === obj) return true;
    return false;
}

describe('ti.app', function () {

    // Check if EVENT_ACCESSIBILITY_ANNOUNCEMENT exists and make sure it does not throw exception
    it('EVENT_ACCESSIBILITY_ANNOUNCEMENT', function (finish) {
        should(function () {
            should(Ti.App.EVENT_ACCESSIBILITY_ANNOUNCEMENT).not.be.undefined;
            should(Ti.App.EVENT_ACCESSIBILITY_ANNOUNCEMENT).be.a.String;
            // make sure it is read-only value
            var value = Ti.App.EVENT_ACCESSIBILITY_ANNOUNCEMENT;
            Ti.App.EVENT_ACCESSIBILITY_ANNOUNCEMENT = 'try_to_overwrite_READONLY_value';
            should(Ti.App.EVENT_ACCESSIBILITY_ANNOUNCEMENT).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if EVENT_ACCESSIBILITY_CHANGED exists and make sure it does not throw exception
    it('EVENT_ACCESSIBILITY_CHANGED', function (finish) {
        should(function () {
            should(Ti.App.EVENT_ACCESSIBILITY_CHANGED).not.be.undefined;
            should(Ti.App.EVENT_ACCESSIBILITY_CHANGED).be.a.String;
            // make sure it is read-only value
            var value = Ti.App.EVENT_ACCESSIBILITY_CHANGED;
            Ti.App.EVENT_ACCESSIBILITY_CHANGED = 'try_to_overwrite_READONLY_value';
            should(Ti.App.EVENT_ACCESSIBILITY_CHANGED).be.eql(value);
        }).not.throw();
        finish();
    });

    it('deployType', function (finish) {
        should(Ti.App.deployType).be.a.String;
        should(Ti.App.getDeployType).be.a.Function;
        should(Ti.App.getDeployType()).be.a.String;
        finish();
    });

    it('id', function (finish) {
        should(Ti.App.id).be.a.String;
        should(Ti.App.getId).be.a.Function;
        should(Ti.App.getId()).be.a.String;
        finish();
    });

    it('publisher', function (finish) {
        should(Ti.App.publisher).be.a.String;
        should(Ti.App.getPublisher).be.a.Function;
        should(Ti.App.getPublisher()).be.a.String;
        finish();
    });

    it('url', function (finish) {
        should(Ti.App.url).be.a.String;
        should(Ti.App.getUrl).be.a.Function;
        should(Ti.App.getUrl()).be.a.String;
        finish();
    });

    it('name', function (finish) {
        should(Ti.App.name).be.a.String;
        should(Ti.App.getName).be.a.Function;
        should(Ti.App.getName()).be.a.String;
        finish();
    });

    it('version', function (finish) {
        should(Ti.App.version).be.a.String;
        should(Ti.App.getVersion).be.a.Function;
        should(Ti.App.getVersion()).be.a.String;
        finish();
    });

    it('description', function (finish) {
        should(Ti.App.description).be.a.String;
        should(Ti.App.getDescription).be.a.Function;
        should(Ti.App.getDescription()).be.a.String;
        finish();
    });

    it('copyright', function (finish) {
        should(Ti.App.copyright).be.a.String;
        should(Ti.App.getCopyright).be.a.Function;
        should(Ti.App.getCopyright()).be.a.String;
        finish();
    });

    it('guid', function (finish) {
        should(Ti.App.guid).be.a.String;
        should(Ti.App.getGuid).be.a.Function;
        should(Ti.App.getGuid()).be.a.String;
        finish();
    });

    it('analytics', function (finish) {
        should(Ti.App.analytics).be.a.Boolean;
        should(Ti.App.getAnalytics).be.a.Function;
        should(Ti.App.getAnalytics()).be.a.Boolean;
        finish();
    });

    it('accessibilityEnabled', function (finish) {
        should(Ti.App.accessibilityEnabled).be.a.Boolean;
        should(Ti.App.getAccessibilityEnabled).be.a.Function;
        should(Ti.App.getAccessibilityEnabled()).be.a.Boolean;
        finish();
    });

    it('disableNetworkActivityIndicator', function (finish) {
        should(Ti.App.disableNetworkActivityIndicator).be.a.Boolean;
        should(Ti.App.getDisableNetworkActivityIndicator).be.a.Function;
        should(Ti.App.getDisableNetworkActivityIndicator()).be.a.Boolean;
        finish();
    });
  
    it('forceSplashAsSnapshot', function (finish) {
        should(Ti.App.forceSplashAsSnapshot).be.a.Boolean;
        should(Ti.App.getForceSplashAsSnapshot).be.a.Function;
        should(Ti.App.getForceSplashAsSnapshot()).be.a.Boolean;
        finish();
    });

    it('idleTimerDisabled', function (finish) {
        should(Ti.App.idleTimerDisabled).be.a.Boolean;
        should(Ti.App.getIdleTimerDisabled).be.a.Function;
        should(Ti.App.getIdleTimerDisabled()).be.a.Boolean;
        finish();
    });

    it('installId', function (finish) {
        should(Ti.App.installId).be.a.String;
        should(Ti.App.getInstallId).be.a.Function;
        should(Ti.App.getInstallId()).be.a.String;
        finish();
    });

    it('keyboardVisible', function (finish) {
        should(Ti.App.keyboardVisible).be.a.Boolean;
        should(Ti.App.getKeyboardVisible).be.a.Function;
        should(Ti.App.getKeyboardVisible()).be.a.Boolean;
        finish();
    });

    it('proximityDetection', function (finish) {
        should(Ti.App.proximityDetection).be.a.Boolean;
        should(Ti.App.getProximityDetection).be.a.Function;
        should(Ti.App.getProximityDetection()).be.a.Boolean;
        finish();
    });

    it('proximityState', function (finish) {
        should(Ti.App.proximityState).be.a.Boolean;
        should(Ti.App.getProximityState).be.a.Function;
        should(Ti.App.getProximityState()).be.a.Boolean;
        finish();
    });

    it('sessionId', function (finish) {
        should(Ti.App.sessionId).be.a.String;
        should(Ti.App.getSessionId).be.a.Function;
        should(Ti.App.getSessionId()).be.a.String;
        finish();
    });
});

describe('ti.app.properties', function () {

    it('Bool', function (finish) {
        Ti.App.Properties.setBool('test_bool', true);
        should(Ti.App.Properties.getBool('test_bool')).be.eql(true);
        finish();
    });

    it('Double', function (finish) {
        Ti.App.Properties.setDouble('test_double', 1.321);
        should(Ti.App.Properties.getDouble('test_double')).be.eql(1.321);
        finish();
    });

    it('Int', function (finish) {
        Ti.App.Properties.setInt('test_int', 123);
        should(Ti.App.Properties.getInt('test_int')).be.eql(123);
        finish();
    });

    it('List', function (finish) {
        var test_list = ['item1', 'item2', 'item3'];
        Ti.App.Properties.setList('test_list', test_list);
        should(Ti.App.Properties.getList('test_list')).be.eql(test_list);
        finish();
    });

    it('Object', function (finish) {
        var test_object = {item : 'item1'};
        Ti.App.Properties.setObject('test_object', test_object);
        should(Ti.App.Properties.getObject('test_object')).be.eql(test_object);
        finish();
    });

    it('String', function (finish) {
        var test_string = 'some test string.';
        Ti.App.Properties.setString('test_string', test_string);
        should(Ti.App.Properties.getString('test_string')).be.eql(test_string);
        finish();
    });

    it('listProperties', function (finish) {
        Ti.App.Properties.setBool('test_property', true);
        var properties = Ti.App.Properties.listProperties();
        should(properties).be.a.Object;
        properties.contains('test_property');
        finish();
    });

    it('removeProperty', function (finish) {
        Ti.App.Properties.setBool('test_property', true);
        var properties = Ti.App.Properties.listProperties();
        should(properties).be.a.Object;
        should(properties.contains('test_property')).be.eql(true);
        Ti.App.Properties.removeProperty('test_property');
        properties = Ti.App.Properties.listProperties();
        should(properties.contains('test_property')).be.eql(false);
        finish();
    });

    it('hasProperty', function (finish) {
        Ti.App.Properties.removeProperty('test_has_property');
        should(Ti.App.Properties.hasProperty('test_has_property')).be.eql(false);
        Ti.App.Properties.setBool('test_has_property', true);
        should(Ti.App.Properties.hasProperty('test_has_property')).be.eql(true);
        finish();
    });

});
