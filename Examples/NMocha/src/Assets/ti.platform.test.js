/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should');

describe("Titanium.Platform", function () {

    it("apiName", function (finish) {
        should(Ti.Platform.apiName).be.eql("Titanium.Platform");
        finish();
    });
    it("createUUID", function (finish) {
        var result;
        should(Ti.Platform.createUUID).be.a.Function;

        result = Ti.Platform.createUUID();
        should(result).be.a.String;
        should(result.length).eql(36);
        // Verify format using regexp!
        should(result.match(/^[0-9a-f]{8}-[0-9a-f]{4}-[1-5][0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i)).not.eql(null);
        should(result.charAt(0)).not.eql("{");
        should(result.charAt(result.length - 1)).not.eql("}");
        finish();
    });
    it("openURL", function (finish) {
        should(Ti.Platform.openURL).be.a.Function;
        finish();
    });
    it("canOpenURL", function (finish) {
        should(Ti.Platform.canOpenURL).be.a.Function;
        should(Ti.Platform.canOpenURL('http://www.appcelerator.com/')).be.a.Boolean;
        finish();
    });
    it.skip("is24HourTimeFormat", function (finish) {
        should(Ti.Platform.is24HourTimeFormat).be.a.Function;
        should(Ti.Platform.is24HourTimeFormat()).be.Boolean;
        finish();
    });
    it("BATTERY_STATE", function (finish) {
        should(Ti.Platform.BATTERY_STATE_CHARGING).be.a.Number;
        should(Ti.Platform.BATTERY_STATE_FULL).be.a.Number;
        should(Ti.Platform.BATTERY_STATE_UNKNOWN).be.a.Number;
        should(Ti.Platform.BATTERY_STATE_UNPLUGGED).be.a.Number;
        finish();
    });
    it("address", function (finish) {
        should(Ti.Platform.address).be.a.String;
        finish();
    });
    it("architecture", function (finish) {
        should(Ti.Platform.architecture).be.a.String;
        finish();
    });
    it("availableMemory", function (finish) {
        should(Ti.Platform.availableMemory).be.a.Number;
        finish();
    });
    it("batteryLevel", function (finish) {
        // batteryLevel should be a number and only accessible from phone
        should(Ti.Platform.batteryLevel).be.a.Number;
        if (Ti.Platform.osname == 'windowsphone') {
            should(Ti.Platform.batteryLevel).be.a.Number;
        }
        finish();
    });
    it("batteryMonitoring", function (finish) {
        should(Ti.Platform.batteryMonitoring).be.Boolean;
        // Note: Windows 10 Mobile doesn't support battery monitoring
        if (Ti.Platform.osname == 'windowsphone' && !/^10\./.test(Ti.Platform.version)) {
            should(Ti.Platform.batteryMonitoring).be.eql(true);
        } else if (Ti.Platform.osname == 'windowsstore') {
            should(Ti.Platform.batteryMonitoring).be.eql(false);
        }
        finish();
    });
    it("batteryState", function (finish) {
        should(Ti.Platform.batteryState).be.a.Number;
        finish();
    });
    it("id", function (finish) {
        should(Ti.Platform.id).be.a.String;
        finish();
    });
    it("locale", function (finish) {
        should(Ti.Platform.locale).be.a.String;
        finish();
    });
    it("macaddress", function (finish) {
        should(Ti.Platform.macaddress).be.a.String;
        finish();
    });
    it("model", function (finish) {
        should(Ti.Platform.model).be.a.String;
        finish();
    });
    it("name", function (finish) {
        should(Ti.Platform.name).be.a.String;
        finish();
    });
    it("netmask", function (finish) {
        should(Ti.Platform.netmask).be.a.String;
        finish();
    });
    it("osname", function (finish) {
        should(Ti.Platform.osname).be.a.String;
        finish();
    });
    it("ostype", function (finish) {
        should(Ti.Platform.ostype).be.a.String;
        finish();
    });
    it("processorCount", function (finish) {
        should(Ti.Platform.processorCount).be.a.Number;
        finish();
    });
    it("version", function (finish) {
        should(Ti.Platform.version).be.a.String;
        finish();
    });
    it("runtime", function (finish) {
        should(Ti.Platform.runtime).be.a.String;
        if ("android" === Ti.Platform.osname) {
            should("rhino" === Ti.Platform.runtime || "v8" === Ti.Platform.runtime).be.true;
        } else if ("iphone" === Ti.Platform.osname || "ipad" === Ti.Platform.osname) {
            should(Ti.Platform.runtime).eql("javascriptcore");
        } else if ("windows" === Ti.Platform.osname || "windowsphone" === Ti.Platform.osname) {
            should(Ti.Platform.runtime).eql("javascriptcore");
        } else {
            should(Ti.Platform.runtime.length).be.greaterThan(0);
        }
        finish();
    });
    it("displayCaps", function (finish) {
        should(Ti.Platform.displayCaps).be.an.Object;
        should(Ti.Platform.displayCaps).not.be.null;
        finish();
    });
});

describe("Titanium.Platform.DisplayCaps", function () {
    it.skip("platformHeight", function (finish) {
        should(Ti.Platform.displayCaps.platformHeight).be.a.Number;
        should(Ti.Platform.displayCaps.platformHeight > 0).be.eql(true);
        finish();
    });
    it.skip("platformWidth", function (finish) {
        should(Ti.Platform.displayCaps.platformWidth).be.a.Number;
        should(Ti.Platform.displayCaps.platformWidth  > 0).be.eql(true);
        finish();
    });
    it.skip("density", function (finish) {
        should(Ti.Platform.displayCaps.density).be.a.String;
        finish();
    });
    it.skip("dpi", function (finish) {
        should(Ti.Platform.displayCaps.dpi).be.a.Number;
        should(Ti.Platform.displayCaps.xdpi).be.a.Number;
        should(Ti.Platform.displayCaps.ydpi).be.a.Number;
        should(Ti.Platform.displayCaps.logicalDensityFactor).be.a.Number;

        should(Ti.Platform.displayCaps.dpi  > 0).be.eql(true);
        should(Ti.Platform.displayCaps.xdpi > 0).be.eql(true);
        should(Ti.Platform.displayCaps.ydpi > 0).be.eql(true);
        should(Ti.Platform.displayCaps.logicalDensityFactor > 0).be.eql(true);
        finish();
    });
});
