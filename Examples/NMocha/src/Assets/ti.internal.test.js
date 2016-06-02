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

	// make sure we have console.log
	// TODO: Is this a public API?
	it("console.log", function (finish) {
		should(console.log).be.a.Function;
		finish();
	});

});
