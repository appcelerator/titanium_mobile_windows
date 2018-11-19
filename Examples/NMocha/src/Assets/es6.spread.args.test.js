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

describe('ES6 Spread Arguments', function () {

	it('expands array via spread to multiple named arguments', function () {
		var result;
		function f(x, y, z) {
			return x + y + z;
		}
		// Pass each elem of array as argument
		result = f(...[ 1, 2, 3 ]);
		result.should.eql(6);
	});
});
