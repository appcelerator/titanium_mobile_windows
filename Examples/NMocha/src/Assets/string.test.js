/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2018-Present by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
/* eslint-env mocha */
/* global Ti */
/* eslint no-unused-expressions: "off" */
'use strict';
var should = require('./utilities/assertions'); // eslint-disable-line no-unused-vars

describe('String', function () {
	it('#format', function () {
		should(String.format).not.be.undefined;
		should(String.format).be.a.Function;
		should(String.format('formatString', 'value')).be.a.String;
	});

	it('#formatCurrency', function () {
		should(String.formatCurrency).not.be.undefined;
		should(String.formatCurrency).be.a.Function;
		should(String.formatCurrency(123)).be.a.String;
	});

	it('#formatDate', function () {
		should(String.formatDate).not.be.undefined;
		should(String.formatDate).be.a.Function;
		should(String.formatDate(new Date())).be.a.String;
	});

	it('#formatDecimal', function () {
		should(String.formatDecimal).not.be.undefined;
		should(String.formatDecimal).be.a.Function;
		should(String.formatDecimal(123)).be.a.String;
	});

	it('#formatTime', function () {
		should(String.formatTime).not.be.undefined;
		should(String.formatTime).be.a.Function;
		should(String.formatTime(new Date())).be.a.String;
	});
});
