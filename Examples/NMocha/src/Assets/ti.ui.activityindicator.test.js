/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities');

describe('Titanium.UI.ActivityIndicator', function () {
	it('apiName', function () {
		var activityIndicator = Ti.UI.createActivityIndicator();
		should(activityIndicator).have.readOnlyProperty('apiName').which.is.a.String;
		should(activityIndicator.apiName).be.eql('Ti.UI.ActivityIndicator');
	});

	it('color', function () {
		var activityIndicator = Ti.UI.createActivityIndicator({
			color: '#fff'
		});
		should(activityIndicator.color).be.a.String;
		should(activityIndicator.getColor).be.a.Function;
		should(activityIndicator.color).eql('#fff');
		should(activityIndicator.getColor()).eql('#fff');
		activityIndicator.color = '#000';
		should(activityIndicator.color).eql('#000');
		should(activityIndicator.getColor()).eql('#000');
	});

	it('font', function () {
		var activityIndicator = Ti.UI.createActivityIndicator({
			font: {
				fontSize: 24,
				fontFamily: 'Segoe UI'
			}
		});
		should(activityIndicator.font).be.a.Object;
		should(activityIndicator.getFont).be.a.Function;
		should(activityIndicator.font.fontSize).eql(24);
		should(activityIndicator.getFont().fontFamily).eql('Segoe UI');
		activityIndicator.font = {
			fontSize: 11,
			fontFamily: 'Segoe UI Semilight'
		};
		should(activityIndicator.font.fontSize).eql(11);
		should(activityIndicator.getFont().fontFamily).eql('Segoe UI Semilight');
	});

	it('message', function () {
		var activityIndicator = Ti.UI.createActivityIndicator({
			message: 'this is some text'
		});
		should(activityIndicator.message).be.a.String;
		should(activityIndicator.getMessage).be.a.Function;
		should(activityIndicator.message).eql('this is some text');
		should(activityIndicator.getMessage()).eql('this is some text');
		activityIndicator.message = 'other text';
		should(activityIndicator.message).eql('other text');
		should(activityIndicator.getMessage()).eql('other text');
	});

	it('style', function () {
		var activityIndicator = Ti.UI.createActivityIndicator({
			style: Ti.UI.ActivityIndicatorStyle.BIG
		});
		should(activityIndicator.style).be.a.Number;
		should(activityIndicator.getStyle).be.a.Function;
		should(activityIndicator.style).eql(Ti.UI.ActivityIndicatorStyle.BIG);
		should(activityIndicator.getStyle()).eql(Ti.UI.ActivityIndicatorStyle.BIG);
		activityIndicator.style = Ti.UI.ActivityIndicatorStyle.DARK;
		should(activityIndicator.style).eql(Ti.UI.ActivityIndicatorStyle.DARK);
		should(activityIndicator.getStyle()).eql(Ti.UI.ActivityIndicatorStyle.DARK);
	});

	// Not supported on Android: https://jira.appcelerator.org/browse/TIMOB-23497
	(utilities.isAndroid() ? it.skip : it)('indicatorColor', function () {
		var activityIndicator = Ti.UI.createActivityIndicator({
			indicatorColor: '#fff'
		});
		should(activityIndicator.indicatorColor).be.a.String;
		should(activityIndicator.getIndicatorColor).be.a.Function;
		should(activityIndicator.indicatorColor).eql('#fff');
		should(activityIndicator.getIndicatorColor()).eql('#fff');
		activityIndicator.indicatorColor = '#000';
		should(activityIndicator.indicatorColor).eql('#000');
		should(activityIndicator.getIndicatorColor()).eql('#000');
	});

	// Not supported on Android: https://jira.appcelerator.org/browse/TIMOB-23497
	(utilities.isAndroid() ? it.skip : it)('indicatorDiameter', function () {
		var activityIndicator = Ti.UI.createActivityIndicator({
			indicatorDiameter: '36'
		});
		should(activityIndicator.indicatorDiameter).be.a.String;
		should(activityIndicator.getIndicatorDiameter).be.a.Function;
		should(activityIndicator.indicatorDiameter).eql('36');
		should(activityIndicator.getIndicatorDiameter()).eql('36');
		activityIndicator.indicatorDiameter = '12';
		should(activityIndicator.indicatorDiameter).eql('12');
		should(activityIndicator.getIndicatorDiameter()).eql('12');
	});
});
