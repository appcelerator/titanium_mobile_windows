/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe("platform", function () {
    it("Ti.Platform.createUUID", function (finish) {
        should(Ti.Platform.createUUID).be.a.Function;
        should(Ti.Platform.createUUID()).be.a.String;
        finish();
    });
    it("Ti.Platform.openURL", function (finish) {
        should(Ti.Platform.openURL).be.a.Function;
        finish();
    });
    it("Ti.Platform.canOpenURL", function (finish) {
        should(Ti.Platform.canOpenURL).be.a.Function;
        should(Ti.Platform.canOpenURL('http://www.appcelerator.com/')).be.a.Boolean;
        finish();
    });
    it.skip("Ti.Platform.is24HourTimeFormat", function (finish) {
        should(Ti.Platform.is24HourTimeFormat).be.a.Function;
        should(Ti.Platform.is24HourTimeFormat()).be.Boolean;
        finish();
    });
    it("Ti.Platform.BATTERY_STATE", function (finish) {
        should(Ti.Platform.BATTERY_STATE_CHARGING).be.a.Number;
        should(Ti.Platform.BATTERY_STATE_FULL).be.a.Number;
        should(Ti.Platform.BATTERY_STATE_UNKNOWN).be.a.Number;
        should(Ti.Platform.BATTERY_STATE_UNPLUGGED).be.a.Number;
        finish();
    });
    it("Ti.Platform.address", function (finish) {
        should(Ti.Platform.address).be.a.String;
        finish();
    });
    it("Ti.Platform.architecture", function (finish) {
        should(Ti.Platform.architecture).be.a.String;
        finish();
    });
    it.skip("Ti.Platform.availableMemory", function (finish) {
        should(Ti.Platform.availableMemory).be.a.Number;
        finish();
    });
    it("Ti.Platform.batteryLevel", function (finish) {
        if (Ti.Platform.osname == 'windowsphone') {
            should(Ti.Platform.batteryLevel).be.a.Number;
        } else {
            should(Ti.Platform.batteryLevel === undefined).be.eql(true);
        }
        finish();
    });
    it("Ti.Platform.batteryMonitoring", function (finish) {
        should(Ti.Platform.batteryMonitoring).be.Boolean;
        if (Ti.Platform.osname == 'windowsphone') {
            should(Ti.Platform.batteryMonitoring).be.eql(true);
        } else if (Ti.Platform.osname == 'windowsstore') {
            should(Ti.Platform.batteryMonitoring).be.eql(false);
        }
        finish();
    });
    it("Ti.Platform.batteryState", function (finish) {
        should(Ti.Platform.batteryState).be.a.Number;
        finish();
    });
    it("Ti.Platform.displayCaps", function (finish) {
        should(Ti.Platform.displayCaps).be.an.Object;
        should(Ti.Platform.displayCaps).not.be.null;
        should(Ti.Platform.displayCaps.platformHeight).be.a.Number;
        should(Ti.Platform.displayCaps.platformWidth).be.a.Number;
        should(Ti.Platform.displayCaps.platformHeight > 0).be.eql(true);
        should(Ti.Platform.displayCaps.platformWidth  > 0).be.eql(true);
        finish();
    });
    it.skip("Ti.Platform.displayCaps.density", function (finish) {
        should(Ti.Platform.displayCaps.density).be.a.String;
        finish();
    });
    it("Ti.Platform.displayCaps.dpi", function (finish) {
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
    it("Ti.Platform.id", function (finish) {
        should(Ti.Platform.id).be.a.String;
        finish();
    });
    it.skip("Ti.Platform.locale", function (finish) {
        should(Ti.Platform.locale).be.a.String;
        finish();
    });
    it.skip("Ti.Platform.macaddress", function (finish) {
        should(Ti.Platform.macaddress).be.a.String;
        finish();
    });
    it("Ti.Platform.model", function (finish) {
        should(Ti.Platform.model).be.a.String;
        finish();
    });
    it("Ti.Platform.name", function (finish) {
        should(Ti.Platform.name).be.a.String;
        finish();
    });
    it.skip("Ti.Platform.netmask", function (finish) {
        should(Ti.Platform.netmask).be.a.String;
        finish();
    });
    it("Ti.Platform.osname", function (finish) {
        should(Ti.Platform.osname).be.a.String;
        finish();
    });
    it.skip("Ti.Platform.ostype", function (finish) {
        should(Ti.Platform.ostype).be.a.String;
        finish();
    });
    it.skip("Ti.Platform.processorCount", function (finish) {
        should(Ti.Platform.processorCount).be.a.Number;
        finish();
    });
    it("Ti.Platform.version", function (finish) {
        should(Ti.Platform.version).be.a.String;
        finish();
    });
    it("Ti.Platform.runtime", function (finish) {
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
});
