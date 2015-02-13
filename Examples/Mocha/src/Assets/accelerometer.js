/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe('accelerometer', function () {
    it('Ti.Accelerometer', function (finish) {
        should(Ti.Accelerometer).not.be.undefined;
        should(Ti.Accelerometer).be.an.Object;
        should(Ti.Accelerometer.addEventListener).be.a.Function;
        should(Ti.Accelerometer.removeEventListener).be.a.Function;
        finish();
    });
});
