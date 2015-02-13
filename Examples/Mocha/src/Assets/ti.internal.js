/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

//
// Unit test for Titanium events and some other global functions
//
describe("ti_internal", function () {

    // make sure we have setTimeout
    it("setTimeout", function (finish) {
        should(setTimeout).be.a.Function;
        finish();
    });

    // make sure we have setInterval
    it("setInterval", function (finish) {
        should(setInterval).be.a.Function;
        finish();
    });

    // make sure we have clearTimeout
    it("clearTimeout", function (finish) {
        should(clearTimeout).be.a.Function;
        finish();
    });

    // make sure we have clearInterval
    it("clearInterval", function (finish) {
        should(clearInterval).be.a.Function;
        finish();
    });

    // make sure we have Ti.API.info
    it("Ti.API.info", function (finish) {
        should(Ti.API.info).be.a.Function;
        finish();
    });

    // make sure we have Ti.API.debug
    it("Ti.API.debug", function (finish) {
        should(Ti.API.debug).be.a.Function;
        finish();
    });

    // make sure we have Ti.API.error
    it("Ti.API.error", function (finish) {
        should(Ti.API.error).be.a.Function;
        finish();
    });

    // make sure we have Ti.API.log
    it("Ti.API.log", function (finish) {
        should(Ti.API.log).be.a.Function;
        finish();
    });
    // make sure we have Ti.API.trace
    it("Ti.API.trace", function (finish) {
        should(Ti.API.trace).be.a.Function;
        finish();
    });
    // make sure we have Ti.API.warn
    it("Ti.API.warn", function (finish) {
        should(Ti.API.warn).be.a.Function;
        finish();
    });

    // make sure we have console.log
    // TODO: Is this a public API?
    it("console.log", function (finish) {
        should(console.log).be.a.Function;
        finish();
    });

    // make sure proxy has applyProperties
    it("tiproxy_applyProperties", function (finish) {
        var view = Ti.UI.createView();
        should(view.applyProperties).be.a.Function;
        finish();
    });

    // make sure applyProperties applies property
    it("tiproxy_applyProperties_add", function (finish) {
        var view = Ti.UI.createView();
        should(view.applyProperties).be.a.Function;
        view.applyProperties({ check: "tiproxy_applyProperties" });
        should(view.check).be.a.String;
        should(view.check).be.eql("tiproxy_applyProperties");
        finish();
    });

    // make sure proxy has addEventListener
    it("tiproxy_addEventListener", function (finish) {
        var view = Ti.UI.createView();
        should(view.addEventListener).be.a.Function;
        finish();
    });

    // make sure proxy has removeEventListener
    it("tiproxy_removeEventListener", function (finish) {
        var view = Ti.UI.createView();
        should(view.removeEventListener).be.a.Function;
        finish();
    });

    // make sure proxy has fireEvent
    it("tiproxy_fireEvent", function (finish) {
        var view = Ti.UI.createView();
        should(view.fireEvent).be.a.Function;
        finish();
    });

    // make sure addEventListener adds listener
    it("tiproxy_add_length", function (finish) {
        var view = Ti.UI.createView();
        view.addEventListener("tiproxy_add_length", function (e) {
            should(e.source).be.an.Object;
        });
        should.exist(view.__ti_private__.events["tiproxy_add_length"]);
        should(view.__ti_private__.events["tiproxy_add_length"].length).not.be.eql(0);

        finish();
    });

    // listener to test removeEventListener
    function tiproxy_remove_fire_listener(e) {
        throw new Error("should not be called");
    }

    // make sure removeEventListener removes listener
    it("tiproxy_remove_length", function (finish) {
        var view = Ti.UI.createView();
        view.addEventListener("tiproxy_remove_length", tiproxy_remove_fire_listener);
        should.exist(view.__ti_private__.events["tiproxy_remove_length"]);

        view.removeEventListener("tiproxy_remove_length", tiproxy_remove_fire_listener);
        should.not.exist(view.__ti_private__.events["tiproxy_remove_length"]);

        finish();
    });

    // make sure fireEvent invokes listener
    it("tiproxy_add_fire", function (finish) {
        var view = Ti.UI.createView();
        view.addEventListener("tiproxy_add_fire", function (e) {
            should(e.source).be.an.Object;
            should(e.source).be.eql(view);
            should(e.check).eql("tiproxy_add_fire_check");
            finish();
        });
        view.fireEvent("tiproxy_add_fire", { check: "tiproxy_add_fire_check" });
    });

    // make sure fireEvent doesn't invoke removed listener
    it("tiproxy_remove_fire", function (finish) {
        var view = Ti.UI.createView();
        view.addEventListener("tiproxy_remove_fire", tiproxy_remove_fire_listener);
        view.removeEventListener("tiproxy_remove_fire", tiproxy_remove_fire_listener);
        view.fireEvent("tiproxy_remove_fire", { check: "tiproxy_remove_fire" });
        finish();
    });

});
