/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities');

describe('Titanium.API', function () {

	// FIXME Get working on Android, not sure why it doesn't!
	((utilities.isAndroid()) ? it.skip : it)('apiName', function () {
		should(Ti.API).have.readOnlyProperty('apiName').which.is.a.String;
		should(Ti.API.apiName).be.eql('Ti.API');
	});

	it('debug()', function () {
		should(Ti.API.debug).be.a.Function;
		// return value is void/undefined
		// TODO How can we verify behavior, accepting array of string args, or accepting/rejecting non string args?
		should(Ti.API.debug('debug')).be.undefined;
	});

	it('error()', function () {
		should(Ti.API.error).be.a.Function;
		should(Ti.API.debug('error')).be.undefined;
	});

	it('info()', function () {
		should(Ti.API.info).be.a.Function;
		should(Ti.API.debug('info')).be.undefined;
	});

	it('log()', function () {
		should(Ti.API.log).be.a.Function;
		should(Ti.API.debug('log')).be.undefined;
	});

	(utilities.isIOS() ? it : it.skip)('timestamp()', function () {
		should(Ti.API.timestamp).be.a.Function;
		should(Ti.API.debug('timestamp')).be.undefined;
	});

	it('trace()', function () {
		should(Ti.API.trace).be.a.Function;
		should(Ti.API.trace('trace')).be.undefined;
	});

	it('warn()', function () {
		should(Ti.API.warn).be.a.Function;
		should(Ti.API.warn('warn')).be.undefined;
	});
});
