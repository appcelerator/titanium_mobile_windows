/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2017-Present by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
/* eslint-env mocha */
/* eslint no-unused-expressions: "off" */
'use strict';
var should = require('./utilities/assertions'); // eslint-disable-line no-unused-vars

describe('ES6 Rest Arguments', function () {

	it('assigns rest arguments', function () {
		var result;
		function f(x, ...y) {
			// y is an Array
			return x * y.length;
		}
		result = f(3, 'hello', true);
		result.should.eql(6);
	});
});
