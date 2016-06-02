/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe('requireJS', function () {
	// require should be a function
	it('requireJS.Function', function (finish) {
		should(require).be.a.Function;
		finish();
	});

	// require should return object
	it('requireJS.Object', function (finish) {
		var object = require('ti.require.test_test');
		should(object).be.an.Object;
		finish();
	});

	// require for invalid file should throw error
	it('requireJS.NonObject', function (finish) {
		(function () {
			var object = require('requireJS_test_notfound');
			should(object).not.be.an.Object;
		}).should.throw();
		finish();
	});

	// require should cache object
	it('requireJS.ObjectCache', function (finish) {
		var object1 = require('ti.require.test_test');
		var object2 = require('ti.require.test_test');
		should(object1).be.an.Object;
		should(object2).be.an.Object;
		should((object1 ==  object2)).be.true;
		should((object1 === object2)).be.true;
		finish();
	});

	// local function and variable should not be exposed
	it('requireJS.LocalFunc', function (finish) {
		var object = require('ti.require.test_test');
		should(object).be.an.Object;
		should(object.localVariable).be.undefined;
		should(object.localFunction).be.undefined;
		finish();
	});

	// public function with 0 argument
	it('requireJS.PublicFunc0', function (finish) {
		var object = require('ti.require.test_test');
		should(object).be.an.Object;
		should(object.testFunc0).a.Function;
		var result = object.testFunc0();
		should(result).be.a.String;
		should(result).be.eql('testFunc0');
		finish();
	});

	// public function with 1 argument
	it('requireJS.PublicFunc1', function (finish) {
		var object = require('ti.require.test_test');
		should(object).be.an.Object;
		should(object.testFunc1).be.a.Function;
		var result = object.testFunc1('A');
		should(result).be.a.String;
		should(result).be.eql('testFunc1 A');
		finish();
	});

	// public function with 2 arguments
	it('requireJS.PublicFunc2', function (finish) {
		var object = require('ti.require.test_test');
		should(object).be.an.Object;
		should(object.testFunc2).be.a.Function;
		var result = object.testFunc2('A', 'B');
		should(result).be.a.String;
		should(result).be.eql('testFunc2 A B');
		finish();
	});

	// public string variable
	it('requireJS.PulbicStrVar', function (finish) {
		var object = require('ti.require.test_test');
		should(object).be.an.Object;
		should(object.testStrVar).be.a.String;
		should(object.testStrVar).be.eql('testVar0');
		finish();
	});

	// public number variable
	it('requireJS.PulbicNumVar', function (finish) {
		var object = require('ti.require.test_test');
		should(object).be.an.Object;
		should(object.testNumVar).be.a.Number;
		should(object.testNumVar).be.eql(101);
		finish();
	});

	// public boolean variable
	it('requireJS.PulbicBoolVar', function (finish) {
		var object = require('ti.require.test_test');
		should(object).be.an.Object;
		should(object.testBoolVar).be.a.Boolean;
		should(object.testBoolVar).be.true;
		finish();
	});

	// public null variable
	it('requireJS.PulbicNullVar', function (finish) {
		var object = require('ti.require.test_test');
		should(object).be.an.Object;
		should(object.testNullVar).be.null;
		finish();
	});

	// internal __filename
	it('requireJS.__filename', function (finish) {
		var object = require('ti.require.test_test');
		should(object).be.an.Object;
		should(object.filename).be.a.String;
		should(object.filename).be.eql('ti.require.test_test');
		finish();
	});

	it('loads package.json main property when requiring directory', function (finish) {
		var with_package = require('./with_package');
		should(with_package).have.property('name');
		should(with_package.name).be.eql('main.js');
		finish();
	});

	it('falls back to index.js when requiring directory with no package.json', function (finish) {
		var with_index_js = require('./with_index_js');
		should(with_index_js).have.property('name');
		should(with_index_js.name).be.eql('index.js');
		finish();
	});

	it('falls back to index.json when requiring directory with no package.json or index.js', function (finish) {
		var with_index_json = require('./with_index_json');
		should(with_index_json).have.property('name');
		should(with_index_json.name).be.eql('index.json');
		finish();
	});

	it('loads exact match JS file', function (finish) {
		var exact_js = require('./with_package/index.js');
		should(exact_js).have.property('name');
		should(exact_js.name).be.eql('index.js');
		finish();
	});

	it('loads exact match JSON file', function (finish) {
		var package_json = require('./with_package/package.json');
		should(package_json).have.property('main');
		should(package_json.main).be.eql('./main.js');
		finish();
	});

	it('loads .js with matching file basename if no exact match', function (finish) {
		var with_index_js = require('./with_index_js/index');
		should(with_index_js).have.property('name');
		should(with_index_js.name).be.eql('index.js');
		finish();
	});

	it('loads .json with matching file basename if no exact or .js match', function (finish) {
		var with_index_json = require('./with_index_json/index');
		should(with_index_json).have.property('name');
		should(with_index_json.name).be.eql('index.json');
		finish();
	});

	it('loads file under Titanium CommonJS module containing moduleid.js file', function (finish) {
		var object = require('commonjs.legacy.package/main');
		should(object).have.property('name');
		should(object.name).be.eql('commonjs.legacy.package/main.js');
		finish();
	});
});
