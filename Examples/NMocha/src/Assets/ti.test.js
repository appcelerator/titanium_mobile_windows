/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium', function () {

	it('apiName', function (finish) {
		should(Ti.apiName).be.eql('Ti');
		finish();
	});

	it('version', function (finish) {
		should(Ti.version).be.a.String;
		should(Ti.getVersion).be.a.Function;
		should(Ti.getVersion()).be.a.String;
		should(Ti.version).not.eql('__TITANIUM_VERSION__');
		finish();
	});
	it('buildDate', function (finish) {
		should(Ti.buildDate).be.a.String;
		should(Ti.getBuildDate).be.a.Function;
		should(Ti.getBuildDate()).be.a.String;
		should(Ti.buildDate).not.eql('__TITANIUM_BUILD_DATE__');
		finish();
	});
	it('buildHash', function (finish) {
		should(Ti.buildHash).be.a.String;
		should(Ti.getBuildHash).be.a.Function;
		should(Ti.getBuildHash()).be.a.String;
		should(Ti.buildHash).not.eql('__TITANIUM_BUILD_HASH__');
		finish();
	});
	it('userAgent', function (finish) {
		should(Ti.userAgent).be.a.String;
		should(Ti.getUserAgent).be.a.Function;
		should(Ti.getUserAgent()).be.a.String;
		should(Ti.setUserAgent).be.a.Function;
		var save = Ti.getUserAgent();
		Ti.setUserAgent('Titanium_Mocha_Test');
		should(Ti.getUserAgent()).be.eql('Titanium_Mocha_Test');
		Ti.setUserAgent(save);
		should(Ti.getUserAgent()).be.eql(save);
		finish();
	});
	it('addEventListener', function (finish) {
		should(Ti.addEventListener).be.a.Function;
		finish();
	});
	it('removeEventListener', function (finish) {
		should(Ti.removeEventListener).be.a.Function;
		finish();
	});
	it('applyProperties', function (finish) {
		should(Ti.applyProperties).be.a.Function;
		Ti.mocha_test = undefined;
		should(Ti.applyProperties({ mocha_test: 'mocha_test_value' }))
		should(Ti.mocha_test !== undefined);
		should(Ti.mocha_test).be.eql('mocha_test_value');
		Ti.mocha_test = undefined;
		finish();
	});
	it('createBuffer', function (finish) {
		should(Ti.createBuffer).be.a.Function;
		finish();
	});
	it('fireEvent', function (finish) {
		should(Ti.fireEvent).be.a.Function;
		finish();
	});
});
