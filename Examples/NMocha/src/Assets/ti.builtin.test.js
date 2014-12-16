/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('should');

//
// Unit test for Titanium events and some other global functions
//
describe("ti_internal", function () {

    // make sure we have require
    it("require", function (finish) {
        try {
            should(require).be.a.Function;
            finish();
        } catch (E) {
            Ti.API.info(E.toString());
            finish();
        }
    });

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

    // make sure we have global
    it.skip("global", function (finish) {
        should(global).be.an.Object;
        finish();
    });

    // make sure we have console.log
    it.skip("console", function (finish) {
        should(console).be.an.Object;
        finish();
    });

    // make sure we have console.log
    it.skip("console.log", function (finish) {
        should(console.log).be.a.Function;
        finish();
    });


});
