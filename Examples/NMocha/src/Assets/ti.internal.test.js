/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./utilities/assertions');

//
// Unit test for Titanium events and some other global functions
// TODO Combine with ti.builtin.test.js, this is all pretty much Global functions
describe('ti_internal', function () {

	// make sure we have setTimeout
	it('setTimeout', function () {
		should(setTimeout).be.a.Function;
	});

	// make sure we have setInterval
	it('setInterval', function () {
		should(setInterval).be.a.Function;
	});

	// make sure we have clearTimeout
	it('clearTimeout', function () {
		should(clearTimeout).be.a.Function;
	});

	// make sure we have clearInterval
	it('clearInterval', function () {
		should(clearInterval).be.a.Function;
	});

	// make sure we have console.log
	it('console.log', function () {
		should(console.log).be.a.Function;
	});

});
