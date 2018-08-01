/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-Present by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
/* eslint-env mocha */
/* global Ti */
/* eslint no-unused-expressions: "off" */
'use strict';
var should = require('./utilities/assertions');

describe('Titanium.Network.Cookie', function () {
	it('apiName', function () {
		var cookie = Ti.Network.createCookie();
		should(cookie).have.a.readOnlyProperty('apiName').which.is.a.String;
		should(cookie.apiName).be.eql('Ti.Network.Cookie');
	});

	it('#isValid()', function () {
		var cookie1 = Ti.Network.createCookie({
			domain: 'example.com',
			name: 'test_cookie',
			value: '12',
			path: '/'
		});

		var cookie2 = Ti.Network.createCookie({
			name: 'test_cookie',
			value: '12',
			path: '/'
		});

		should(cookie1.isValid()).be.true;
		should(cookie2.isValid()).be.false;
	});

	it('Add and Remove Cookie', function() {
		should(Ti.Network.addHTTPCookie).be.a.Function;

		var cookie1 = Ti.Network.createCookie({
			domain: 'example.com',
			name: 'test_cookie',
			value: '123',
			path: '/'
		});
		Ti.Network.addHTTPCookie(cookie1);

		var cookies = Ti.Network.getHTTPCookies(cookie1.domain, cookie1.path, cookie1.name);
		should(cookies).be.an.Array;
		should(cookies.length).eql(1);

		Ti.Network.removeHTTPCookie(cookie1.domain, cookie1.path, cookie1.name);

		cookies = Ti.Network.getHTTPCookies(cookie1.domain, cookie1.path, cookie1.name);
		should(cookies).be.an.Array;
		should(cookies.length).eql(0);
	});

});
