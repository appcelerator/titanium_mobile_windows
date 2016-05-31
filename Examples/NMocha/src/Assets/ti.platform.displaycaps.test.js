/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.Platform.DisplayCaps', function () {
	it('apiName', function (finish) {
		should(Ti.Platform.DisplayCaps.apiName).be.eql('Ti.Platform.DisplayCaps');
		finish();
	});

	it.skip('platformHeight', function (finish) {
		should(Ti.Platform.displayCaps.platformHeight).be.a.Number;
		should(Ti.Platform.displayCaps.platformHeight > 0).be.eql(true);
		finish();
	});

	it.skip('platformWidth', function (finish) {
		should(Ti.Platform.displayCaps.platformWidth).be.a.Number;
		should(Ti.Platform.displayCaps.platformWidth  > 0).be.eql(true);
		finish();
	});

	it.skip('density', function (finish) {
		should(Ti.Platform.displayCaps.density).be.a.String;
		finish();
	});

	it.skip('dpi', function (finish) {
		should(Ti.Platform.displayCaps.dpi).be.a.Number;
		should(Ti.Platform.displayCaps.xdpi).be.a.Number;
		should(Ti.Platform.displayCaps.ydpi).be.a.Number;
		should(Ti.Platform.displayCaps.logicalDensityFactor).be.a.Number;

		should(Ti.Platform.displayCaps.dpi  > 0).be.eql(true);
		should(Ti.Platform.displayCaps.xdpi > 0).be.eql(true);
		should(Ti.Platform.displayCaps.ydpi > 0).be.eql(true);
		should(Ti.Platform.displayCaps.logicalDensityFactor > 0).be.eql(true);
		finish();
	});
});
