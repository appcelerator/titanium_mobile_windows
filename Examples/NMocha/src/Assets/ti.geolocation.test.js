/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.Geolocation', function () {
	it('apiName', function (finish) {
		should(Ti.Geolocation.apiName).be.eql('Ti.Geolocation');
		finish();
	});

	// Check if ACCURACY_BEST exists and make sure it does not throw exception
	it('ACCURACY_BEST', function (finish) {
		should(function () {
			should(Ti.Geolocation.ACCURACY_BEST).not.be.undefined;
			should(Ti.Geolocation.ACCURACY_BEST).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Geolocation.ACCURACY_BEST;
			Ti.Geolocation.ACCURACY_BEST = 'try_to_overwrite_READONLY_value';
			should(Ti.Geolocation.ACCURACY_BEST).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if ACCURACY_BEST_FOR_NAVIGATION exists and make sure it does not throw exception
	it('ACCURACY_BEST_FOR_NAVIGATION', function (finish) {
		should(function () {
			should(Ti.Geolocation.ACCURACY_BEST_FOR_NAVIGATION).not.be.undefined;
			should(Ti.Geolocation.ACCURACY_BEST_FOR_NAVIGATION).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Geolocation.ACCURACY_BEST_FOR_NAVIGATION;
			Ti.Geolocation.ACCURACY_BEST_FOR_NAVIGATION = 'try_to_overwrite_READONLY_value';
			should(Ti.Geolocation.ACCURACY_BEST_FOR_NAVIGATION).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if ACCURACY_HIGH exists and make sure it does not throw exception
	it('ACCURACY_HIGH', function (finish) {
		should(function () {
			should(Ti.Geolocation.ACCURACY_HIGH).not.be.undefined;
			should(Ti.Geolocation.ACCURACY_HIGH).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Geolocation.ACCURACY_HIGH;
			Ti.Geolocation.ACCURACY_HIGH = 'try_to_overwrite_READONLY_value';
			should(Ti.Geolocation.ACCURACY_HIGH).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if ACCURACY_HUNDRED_METERS exists and make sure it does not throw exception
	it('ACCURACY_HUNDRED_METERS', function (finish) {
		should(function () {
			should(Ti.Geolocation.ACCURACY_HUNDRED_METERS).not.be.undefined;
			should(Ti.Geolocation.ACCURACY_HUNDRED_METERS).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Geolocation.ACCURACY_HUNDRED_METERS;
			Ti.Geolocation.ACCURACY_HUNDRED_METERS = 'try_to_overwrite_READONLY_value';
			should(Ti.Geolocation.ACCURACY_HUNDRED_METERS).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if ACCURACY_KILOMETER exists and make sure it does not throw exception
	it('ACCURACY_KILOMETER', function (finish) {
		should(function () {
			should(Ti.Geolocation.ACCURACY_KILOMETER).not.be.undefined;
			should(Ti.Geolocation.ACCURACY_KILOMETER).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Geolocation.ACCURACY_KILOMETER;
			Ti.Geolocation.ACCURACY_KILOMETER = 'try_to_overwrite_READONLY_value';
			should(Ti.Geolocation.ACCURACY_KILOMETER).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if ACCURACY_LOW exists and make sure it does not throw exception
	it('ACCURACY_LOW', function (finish) {
		should(function () {
			should(Ti.Geolocation.ACCURACY_LOW).not.be.undefined;
			should(Ti.Geolocation.ACCURACY_LOW).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Geolocation.ACCURACY_LOW;
			Ti.Geolocation.ACCURACY_LOW = 'try_to_overwrite_READONLY_value';
			should(Ti.Geolocation.ACCURACY_LOW).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if ACCURACY_NEAREST_TEN_METERS exists and make sure it does not throw exception
	it('ACCURACY_NEAREST_TEN_METERS', function (finish) {
		should(function () {
			should(Ti.Geolocation.ACCURACY_NEAREST_TEN_METERS).not.be.undefined;
			should(Ti.Geolocation.ACCURACY_NEAREST_TEN_METERS).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Geolocation.ACCURACY_NEAREST_TEN_METERS;
			Ti.Geolocation.ACCURACY_NEAREST_TEN_METERS = 'try_to_overwrite_READONLY_value';
			should(Ti.Geolocation.ACCURACY_NEAREST_TEN_METERS).be.eql(value);
		}).not.throw();
		finish();
	});

	// Check if ACCURACY_THREE_KILOMETERS exists and make sure it does not throw exception
	it('ACCURACY_THREE_KILOMETERS', function (finish) {
		should(function () {
			should(Ti.Geolocation.ACCURACY_THREE_KILOMETERS).not.be.undefined;
			should(Ti.Geolocation.ACCURACY_THREE_KILOMETERS).be.a.Number;
			// make sure it is read-only value
			var value = Ti.Geolocation.ACCURACY_THREE_KILOMETERS;
			Ti.Geolocation.ACCURACY_THREE_KILOMETERS = 'try_to_overwrite_READONLY_value';
			should(Ti.Geolocation.ACCURACY_THREE_KILOMETERS).be.eql(value);
		}).not.throw();
		finish();
	});

	it('accuracy', function (finish) {
		should(Ti.Geolocation.getAccuracy()).be.a.Number;
		should(Ti.Geolocation.getAccuracy).be.a.Function;
		should(Ti.Geolocation.setAccuracy).be.a.Function;
		Ti.Geolocation.setAccuracy(Ti.Geolocation.ACCURACY_BEST);
		should(Ti.Geolocation.getAccuracy()).be.eql(Ti.Geolocation.ACCURACY_BEST);
		finish();
	});

	it('distanceFilter', function (finish) {
		should(Ti.Geolocation.getDistanceFilter()).be.a.Number;
		should(Ti.Geolocation.getDistanceFilter).be.a.Function;
		should(Ti.Geolocation.setDistanceFilter).be.a.Function;
		Ti.Geolocation.setDistanceFilter(1000);
		should(Ti.Geolocation.getDistanceFilter()).be.eql(1000);
		finish();
	});

	it('headingFilter', function (finish) {
		should(Ti.Geolocation.getHeadingFilter()).be.a.Number;
		should(Ti.Geolocation.getHeadingFilter).be.a.Function;
		should(Ti.Geolocation.setHeadingFilter).be.a.Function;
		Ti.Geolocation.setHeadingFilter(90);
		should(Ti.Geolocation.getHeadingFilter()).be.eql(90);
		finish();
	});

	it('lastGeolocation', function (finish) {
		should(Ti.Geolocation.getLastGeolocation()).be.a.Object;
		should(Ti.Geolocation.getLastGeolocation).be.a.Function;
		finish();
	});

	it('locationServicesEnabled', function (finish) {
		should(Ti.Geolocation.getLocationServicesEnabled()).be.a.Boolean;
		should(Ti.Geolocation.getLocationServicesEnabled).be.a.Function;
		finish();
	});

	// skip it for now, it may be blocking other tests due to permission dialog
	it.skip('forwardGeocoder', function (finish) {
		this.timeout(6e4);
		should(Ti.Geolocation.forwardGeocoder).be.a.Function;
		Ti.Geolocation.forwardGeocoder('440 N Bernardo Ave, Mountain View', function (data) {
		    try {
		        should(data).have.property('success').which.is.a.Boolean;
		        should(data.success).be.eql(true);
		        should(data).have.property('code').which.is.a.Number;
		        should(data.code).be.eql(0);
		        should(data.latitude).be.approximately(37.387, 0.002);
		        should(data.longitude).be.approximately(-122.065, 0.02);
		        finish();
		    } catch (err) {
		        finish(err);
		    }
		});
	});

	// skip it for now, it may be blocking other tests due to permission dialog
	it.skip('reverseGeocoder', function (finish) {
		this.timeout(6e4);
		should(Ti.Geolocation.reverseGeocoder).be.a.Function;
		Ti.Geolocation.reverseGeocoder(37.3883645, -122.0512682, function (data) {
			try {
				should(data).have.property('success').which.is.a.Boolean;
				should(data.success).be.eql(true);
				should(data).have.property('code').which.is.a.Number;
				should(data.code).be.eql(0);
				should(data).have.property('places').which.is.an.Array;
				should(data.places[0].zipcode).be.eql('94043');
				should(data.places[0].country).be.eql('United States of America');
				should(data.places[0].state).be.eql('California');
				should(data.places[0].country_code).be.eql('US');
				should(data.places[0]).have.property('city').which.is.a.String;
				should(data.places[0]).have.property('address').which.is.a.String;
				should(data.places[0]).have.property('latitude').which.is.a.Number;
				should(data.places[0]).have.property('longitude').which.is.a.Number;
				finish();
			} catch (err) {
				finish(err);
			}
		});
	});

	it('currentPosition', function (finish) {
		should(Ti.Geolocation.getCurrentPosition).be.a.Function;
		finish();
	});

	it('currentHeading', function (finish) {
		should(Ti.Geolocation.getCurrentHeading).be.a.Function;
		finish();
	});
});
