/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.Utils', function () {
	it('Ti.Utils', function (finish) {
		should(Ti.Utils).not.be.undefined;
		finish();
	});

	it('apiName', function (finish) {
		should(Ti.Utils.apiName).be.eql('Ti.Utils');
		finish();
	});

	it('base64decode()', function (finish) {
		should(Ti.Utils.base64decode).not.be.undefined;
		should(Ti.Utils.base64decode).be.a.Function;
		var test = Ti.Utils.base64decode('dGVzdA==');
		should(test).be.a.Object;
		should(test.getText()).be.eql('test');
		finish();
	});

	it('base64encode()', function (finish) {
		should(Ti.Utils.base64encode).not.be.undefined;
		should(Ti.Utils.base64encode).be.a.Function;
		var test = Ti.Utils.base64encode('test');
		should(test).be.a.Object;
		should(test.getText()).be.eql('dGVzdA==');
		finish();
	});

	it('md5HexDigest()', function (finish) {
		should(Ti.Utils.md5HexDigest).not.be.undefined;
		should(Ti.Utils.md5HexDigest).be.a.Function;
		var test = Ti.Utils.md5HexDigest('test');
		should(test).be.a.String;
		should(test).be.eql('098f6bcd4621d373cade4e832627b4f6');
		finish();
	});

	it('sha1()', function (finish) {
		should(Ti.Utils.sha1).not.be.undefined;
		should(Ti.Utils.sha1).be.a.Function;
		var test = Ti.Utils.sha1('test');
		should(test).be.a.String;
		should(test).be.eql('a94a8fe5ccb19ba61c4c0873d391e987982fbbd3');
		finish();
	});

	it('sha256()', function (finish) {
		should(Ti.Utils.sha256).not.be.undefined;
		should(Ti.Utils.sha256).be.a.Function;
		var test = Ti.Utils.sha256('test');
		should(test).be.a.String;
		should(test).be.eql('9f86d081884c7d659a2feaa0c55ad015a3bf4f1b2b0b822cd15d6c15b0f00a08');
		finish();
	});
});
