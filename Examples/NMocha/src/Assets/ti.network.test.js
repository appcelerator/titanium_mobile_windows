/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.Network', function () {

	it('apiName', function (finish) {
		should(Ti.Network.apiName).be.eql('Ti.Network');
		finish();
	});

	it('encodeURIComponent', function (finish) {
		should(Ti.Network.encodeURIComponent).not.be.null;
		should(Ti.Network.encodeURIComponent).be.a.Function;
		var text = Ti.Network.encodeURIComponent('Look what I found! I like this:');
		text.should.eql('Look%20what%20I%20found!%20I%20like%20this%3A');
		finish();
	});

	it('decodeURIComponent', function (finish) {
		should(Ti.Network.decodeURIComponent).not.be.null;
		should(Ti.Network.decodeURIComponent).be.a.Function;
		var text = Ti.Network.decodeURIComponent('Look%20what%20I%20found!%20I%20like%20this%3A');
		text.should.eql('Look what I found! I like this:');
		finish();
	});

	it('createHTTPClient', function (finish) {
		should(Ti.Network.createHTTPClient).not.be.null;
		should(Ti.Network.createHTTPClient).be.a.Function;
		finish();
	});
});
