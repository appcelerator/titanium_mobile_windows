/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./utilities/assertions');

//
// Unit test for Titanium events and some other global functions
//
describe('Global', function () {

	// make sure we have require
	it('require', function () {
		should(require).be.a.Function;
	});

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

	// make sure we have global
	it.skip('global', function () {
		should(global).be.an.Object;
	});

	// make sure we have console.log
	it('console', function () {
		should(console).be.an.Object;
	});

	// make sure we have console.log
	it('console.log', function () {
		should(console.log).be.a.Function;
	});

	// make sure we have console.info
	it('console.info', function () {
		should(console.info).be.a.Function;
	});

	// make sure we have console.error
	it('console.error', function () {
		should(console.error).be.a.Function;
	});
	// make sure we have console.warn
	it('console.warn', function () {
		should(console.warn).be.a.Function;
	});

});

// FIXME Combine with ti.api.test.js
describe('Titanium.API', function () {
	// make sure we have Ti.API.info
	it('info', function () {
		should(Ti.API.info).be.a.Function;
	});

	// make sure we have Ti.API.debug
	it('debug', function () {
		should(Ti.API.debug).be.a.Function;
	});

	// make sure we have Ti.API.error
	it('error', function () {
		should(Ti.API.error).be.a.Function;
	});

	// make sure we have Ti.API.log
	it('log', function () {
		should(Ti.API.log).be.a.Function;
	});

	// make sure we have Ti.API.trace
	it('trace', function (finish) {
		should(Ti.API.trace).be.a.Function;
		finish();
	});

	// make sure we have Ti.API.warn
	it('warn', function () {
		should(Ti.API.warn).be.a.Function;
	});

	// make sure Ti.API.info accepts string
	it('info accepts String', function () {
		Ti.API.info('Hello');
	});

	// make sure Ti.API.info accepts object
	it('info accepts Object', function () {
		Ti.API.info({});
	});

	// make sure Ti.API.info accepts null
	it('info accepts null', function () {
		Ti.API.info(null);
	});
	// make sure Ti.API.info accepts undefined
	it('info accepts undefined', function () {
		Ti.API.info(undefined);
	});

	// make sure Ti.API.info accepts array
	it('info accepts Array', function () {
		Ti.API.info([]);
	});

	// make sure Ti.API.info accepts number
	it('info accepts Number', function () {
		Ti.API.info(101);
	});
});

describe('Global.String', function () {
	it('format', function () {
		should(String.format).not.be.undefined;
		should(String.format).be.a.Function;
		should(String.format('formatString', 'value')).be.a.String;
	});

	it('formatCurrency', function () {
		should(String.formatCurrency).not.be.undefined;
		should(String.formatCurrency).be.a.Function;
		should(String.formatCurrency(123)).be.a.String;
	});

	it('formatDate', function () {
		should(String.formatDate).not.be.undefined;
		should(String.formatDate).be.a.Function;
		should(String.formatDate(new Date())).be.a.String;
	});

	it('formatDecimal', function () {
		should(String.formatDecimal).not.be.undefined;
		should(String.formatDecimal).be.a.Function;
		should(String.formatDecimal(123)).be.a.String;
	});

	it('formatTime', function () {
		should(String.formatTime).not.be.undefined;
		should(String.formatTime).be.a.Function;
		should(String.formatTime(new Date())).be.a.String;
	});

});
