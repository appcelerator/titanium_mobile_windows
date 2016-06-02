/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.Map', function () {
	it('apiName', function (finish) {
		should(Ti.Map.apiName).be.eql('Ti.Map');
		finish();
	});

	it('ANNOTATION_AZURE', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_AZURE).not.be.undefined;
			should(Ti.Map.ANNOTATION_AZURE).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_AZURE;
			Ti.Map.ANNOTATION_AZURE = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_AZURE).be.eql(value);
		}).not.throw();
		finish();
	});
	it('ANNOTATION_BLUE', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_BLUE).not.be.undefined;
			should(Ti.Map.ANNOTATION_BLUE).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_BLUE;
			Ti.Map.ANNOTATION_BLUE = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_BLUE).be.eql(value);
		}).not.throw();
		finish();
	});
	it('ANNOTATION_CYAN', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_CYAN).not.be.undefined;
			should(Ti.Map.ANNOTATION_CYAN).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_CYAN;
			Ti.Map.ANNOTATION_CYAN = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_CYAN).be.eql(value);
		}).not.throw();
		finish();
	});
	it('ANNOTATION_GREEN', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_GREEN).not.be.undefined;
			should(Ti.Map.ANNOTATION_GREEN).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_GREEN;
			Ti.Map.ANNOTATION_GREEN = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_GREEN).be.eql(value);
		}).not.throw();
		finish();
	});
	it('ANNOTATION_MAGENTA', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_MAGENTA).not.be.undefined;
			should(Ti.Map.ANNOTATION_MAGENTA).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_MAGENTA;
			Ti.Map.ANNOTATION_MAGENTA = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_MAGENTA).be.eql(value);
		}).not.throw();
		finish();
	});
	it('ANNOTATION_ORANGE', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_ORANGE).not.be.undefined;
			should(Ti.Map.ANNOTATION_ORANGE).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_ORANGE;
			Ti.Map.ANNOTATION_ORANGE = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_ORANGE).be.eql(value);
		}).not.throw();
		finish();
	});
	it('ANNOTATION_PURPLE', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_PURPLE).not.be.undefined;
			should(Ti.Map.ANNOTATION_PURPLE).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_PURPLE;
			Ti.Map.ANNOTATION_PURPLE = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_PURPLE).be.eql(value);
		}).not.throw();
		finish();
	});
	it('ANNOTATION_RED', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_RED).not.be.undefined;
			should(Ti.Map.ANNOTATION_RED).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_RED;
			Ti.Map.ANNOTATION_RED = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_RED).be.eql(value);
		}).not.throw();
		finish();
	});
	it('ANNOTATION_ROSE', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_ROSE).not.be.undefined;
			should(Ti.Map.ANNOTATION_ROSE).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_ROSE;
			Ti.Map.ANNOTATION_ROSE = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_ROSE).be.eql(value);
		}).not.throw();
		finish();
	});
	it('ANNOTATION_VIOLET', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_VIOLET).not.be.undefined;
			should(Ti.Map.ANNOTATION_VIOLET).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_VIOLET;
			Ti.Map.ANNOTATION_VIOLET = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_VIOLET).be.eql(value);
		}).not.throw();
		finish();
	});
	it('ANNOTATION_YELLOW', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_YELLOW).not.be.undefined;
			should(Ti.Map.ANNOTATION_YELLOW).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_YELLOW;
			Ti.Map.ANNOTATION_YELLOW = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_YELLOW).be.eql(value);
		}).not.throw();
		finish();
	});
	it('ANNOTATION_DRAG_STATE_END', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_DRAG_STATE_END).not.be.undefined;
			should(Ti.Map.ANNOTATION_DRAG_STATE_END).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_DRAG_STATE_END;
			Ti.Map.ANNOTATION_DRAG_STATE_END = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_DRAG_STATE_END).be.eql(value);
		}).not.throw();
		finish();
	});
	it('ANNOTATION_DRAG_STATE_START', function (finish) {
		should(function () {
			should(Ti.Map.ANNOTATION_DRAG_STATE_START).not.be.undefined;
			should(Ti.Map.ANNOTATION_DRAG_STATE_START).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.ANNOTATION_DRAG_STATE_START;
			Ti.Map.ANNOTATION_DRAG_STATE_START = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.ANNOTATION_DRAG_STATE_START).be.eql(value);
		}).not.throw();
		finish();
	});
	it('OVERLAY_LEVEL_ABOVE_LABELS', function (finish) {
		should(function () {
			should(Ti.Map.OVERLAY_LEVEL_ABOVE_LABELS).not.be.undefined;
			should(Ti.Map.OVERLAY_LEVEL_ABOVE_LABELS).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.OVERLAY_LEVEL_ABOVE_LABELS;
			Ti.Map.OVERLAY_LEVEL_ABOVE_LABELS = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.OVERLAY_LEVEL_ABOVE_LABELS).be.eql(value);
		}).not.throw();
		finish();
	});
	it('OVERLAY_LEVEL_ABOVE_ROADS', function (finish) {
		should(function () {
			should(Ti.Map.OVERLAY_LEVEL_ABOVE_ROADS).not.be.undefined;
			should(Ti.Map.OVERLAY_LEVEL_ABOVE_ROADS).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.OVERLAY_LEVEL_ABOVE_ROADS;
			Ti.Map.OVERLAY_LEVEL_ABOVE_ROADS = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.OVERLAY_LEVEL_ABOVE_ROADS).be.eql(value);
		}).not.throw();
		finish();
	});
	it('SERVICE_DISABLED', function (finish) {
		should(function () {
			should(Ti.Map.SERVICE_DISABLED).not.be.undefined;
			should(Ti.Map.SERVICE_DISABLED).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.SERVICE_DISABLED;
			Ti.Map.SERVICE_DISABLED = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.SERVICE_DISABLED).be.eql(value);
		}).not.throw();
		finish();
	});
	it('SERVICE_INVALID', function (finish) {
		should(function () {
			should(Ti.Map.SERVICE_INVALID).not.be.undefined;
			should(Ti.Map.SERVICE_INVALID).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.SERVICE_INVALID;
			Ti.Map.SERVICE_INVALID = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.SERVICE_INVALID).be.eql(value);
		}).not.throw();
		finish();
	});
	it('SERVICE_MISSING', function (finish) {
		should(function () {
			should(Ti.Map.SERVICE_MISSING).not.be.undefined;
			should(Ti.Map.SERVICE_MISSING).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.SERVICE_MISSING;
			Ti.Map.SERVICE_MISSING = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.SERVICE_MISSING).be.eql(value);
		}).not.throw();
		finish();
	});
	it('SERVICE_VERSION_UPDATE_REQUIRED', function (finish) {
		should(function () {
			should(Ti.Map.SERVICE_VERSION_UPDATE_REQUIRED).not.be.undefined;
			should(Ti.Map.SERVICE_VERSION_UPDATE_REQUIRED).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.SERVICE_VERSION_UPDATE_REQUIRED;
			Ti.Map.SERVICE_VERSION_UPDATE_REQUIRED = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.SERVICE_VERSION_UPDATE_REQUIRED).be.eql(value);
		}).not.throw();
		finish();
	});
	it('SUCCESS', function (finish) {
		should(function () {
			should(Ti.Map.SUCCESS).not.be.undefined;
			should(Ti.Map.SUCCESS).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Map.SUCCESS;
			Ti.Map.SUCCESS = 'try_to_overwrite_READONLY_value';
			should(Ti.Map.SUCCESS).be.eql(value);
		}).not.throw();
		finish();
	});
	it("NORMAL_TYPE", function (finish) {
		should(Ti.Map.NORMAL_TYPE).be.a.Number;
		finish();
	});
	it("SATELLITE_TYPE", function (finish) {
		should(Ti.Map.SATELLITE_TYPE).be.a.Number;
		finish();
	});
	it("HYBRID_TYPE", function (finish) {
		should(Ti.Map.HYBRID_TYPE).be.a.Number;
		finish();
	});
	it("TERRAIN_TYPE", function (finish) {
		should(Ti.Map.TERRAIN_TYPE).be.a.Number;
		finish();
	});
	it('createAnnotation', function (finish) {
		should(Ti.Map.createAnnotation).not.be.undefined;
		should(Ti.Map.createAnnotation).be.a.Function;

		finish();
	});

	it('createCamera', function (finish) {
		should(Ti.Map.createCamera).not.be.undefined;
		should(Ti.Map.createCamera).be.a.Function;

		finish();
	});

	it('createRoute', function (finish) {
		should(Ti.Map.createRoute).not.be.undefined;
		should(Ti.Map.createRoute).be.a.Function;

		finish();
	});

	it('createView', function (finish) {
		should(Ti.Map.createView).not.be.undefined;
		should(Ti.Map.createView).be.a.Function;

		//var view = Ti.Map.createView({mapType: Ti.Map.NORMAL_TYPE});

		// Confirm 'view' is an object
		//should(view).be.a.Object;
		// TODO Confirm that it has certain properties, etc.

		finish();
	});

	it('isGooglePlayServicesAvailable', function (finish) {
		should(Ti.Map.isGooglePlayServicesAvailable).not.be.undefined;
		should(Ti.Map.isGooglePlayServicesAvailable).be.a.Function;

		var value = Ti.Map.isGooglePlayServicesAvailable();
		should(value).be.a.Number;

		finish();
	});
});
