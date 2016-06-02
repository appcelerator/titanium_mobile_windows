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
describe('Global', function () {

	// make sure we have require
	it('require', function (finish) {
		should(require).be.a.Function;
		finish();
	});

	// make sure we have setTimeout
	it('setTimeout', function (finish) {
		should(setTimeout).be.a.Function;
		finish();
	});

	// make sure we have setInterval
	it('setInterval', function (finish) {
		should(setInterval).be.a.Function;
		finish();
	});

	// make sure we have clearTimeout
	it('clearTimeout', function (finish) {
		should(clearTimeout).be.a.Function;
		finish();
	});

	// make sure we have clearInterval
	it('clearInterval', function (finish) {
		should(clearInterval).be.a.Function;
		finish();
	});

	// make sure we have global
	it.skip('global', function (finish) {
		should(global).be.an.Object;
		finish();
	});

	// make sure we have console.log
	it('console', function (finish) {
		should(console).be.an.Object;
		finish();
	});

	// make sure we have console.log
	it('console.log', function (finish) {
		should(console.log).be.a.Function;
		finish();
	});

	// make sure we have console.info
	it('console.info', function (finish) {
		should(console.info).be.a.Function;
		finish();
	});
	// make sure we have console.error
	it('console.error', function (finish) {
		should(console.error).be.a.Function;
		finish();
	});
	// make sure we have console.warn
	it('console.warn', function (finish) {
		should(console.warn).be.a.Function;
		finish();
	});

});

describe('Titanium.API', function () {
	// make sure we have Ti.API.info
	it('info', function (finish) {
		should(Ti.API.info).be.a.Function;
		finish();
	});

	// make sure we have Ti.API.debug
	it('debug', function (finish) {
		should(Ti.API.debug).be.a.Function;
		finish();
	});

	// make sure we have Ti.API.error
	it('error', function (finish) {
		should(Ti.API.error).be.a.Function;
		finish();
	});

	// make sure we have Ti.API.log
	it('log', function (finish) {
		should(Ti.API.log).be.a.Function;
		finish();
	});
	// make sure we have Ti.API.trace
	it('trace', function (finish) {
		should(Ti.API.trace).be.a.Function;
		finish();
	});
	// make sure we have Ti.API.warn
	it('warn', function (finish) {
		should(Ti.API.warn).be.a.Function;
		finish();
	});

	// make sure Ti.API.info accepts string
	it('info accepts String', function (finish) {
		Ti.API.info('Hello');
		finish();
	});
	// make sure Ti.API.info accepts object
	it('info accepts Object', function (finish) {
		Ti.API.info({});
		finish();
	});
	// make sure Ti.API.info accepts null
	it('info accepts null', function (finish) {
		Ti.API.info(null);
		finish();
	});
	// make sure Ti.API.info accepts undefined
	it('info accepts undefined', function (finish) {
		Ti.API.info(undefined);
		finish();
	});
	// make sure Ti.API.info accepts array
	it('info accepts Array', function (finish) {
		Ti.API.info([]);
		finish();
	});
	// make sure Ti.API.info accepts number
	it('info accepts Number', function (finish) {
		Ti.API.info(101);
		finish();
	});
});

describe('Global.String', function () {
	it('format', function (finish) {
		should(String.format).not.be.undefined;
		should(String.format).be.a.Function;
		should(String.format('formatString', 'value')).be.a.String;
		finish();
	});
	it('formatCurrency', function (finish) {
		should(String.formatCurrency).not.be.undefined;
		should(String.formatCurrency).be.a.Function;
		should(String.formatCurrency(123)).be.a.String;
		finish();
	});
	it('formatDate', function (finish) {
		should(String.formatDate).not.be.undefined;
		should(String.formatDate).be.a.Function;
		should(String.formatDate(new Date())).be.a.String;
		finish();
	});
	it('formatDecimal', function (finish) {
		should(String.formatDecimal).not.be.undefined;
		should(String.formatDecimal).be.a.Function;
		should(String.formatDecimal(123)).be.a.String;
		finish();
	});
	it('formatTime', function (finish) {
		should(String.formatTime).not.be.undefined;
		should(String.formatTime).be.a.Function;
		should(String.formatTime(new Date())).be.a.String;
		finish();
	});

});
