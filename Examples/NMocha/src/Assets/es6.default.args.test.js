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

describe('ES6 Default Arguments', function () {

	it('assigns default value to argument not passed explicitly', function () {
		var result;
		function f(x, y = 12) {
			// y is 12 if not passed (or passed as undefined)
			return x + y;
		}
		result = f(3);
		result.should.eql(15);
	});
});
