/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.Accelerometer', function () {
	it('apiName', function (finish) {
		should(Ti.Accelerometer.apiName).be.eql('Ti.Accelerometer');
		finish();
	});

	it('exists', function (finish) {
		should(Ti.Accelerometer).not.be.undefined;
		should(Ti.Accelerometer).not.be.null;
		should(Ti.Accelerometer.addEventListener).be.a.Function;
		should(Ti.Accelerometer.removeEventListener).be.a.Function;
		finish();
	});
});
