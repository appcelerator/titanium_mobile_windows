/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015-2017 by Axway, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
/* eslint-env mocha */
/* global Ti */
/* eslint no-unused-expressions: "off" */
'use strict';
var should = require('./utilities/assertions');

describe('Titanium.Calendar', function () {
	it('apiName', function () {
		should(Ti.Calendar).have.a.readOnlyProperty('apiName').which.is.a.String;
		should(Ti.Calendar.apiName).be.eql('Ti.Calendar');
	});

	describe('#allAlerts', function () {
		it('is an Array', function () {
			should(Ti.Calendar).have.a.readOnlyProperty('allAlerts').which.is.an.Array;
		});
	});

	describe('#allCalendars', function () {
		it('is an Array', function () {
			should(Ti.Calendar).have.a.readOnlyProperty('allCalendars').which.is.an.Array;
		});
	});

	describe('#allEditableCalendars', function () {
		it('is an Array', function () {
			should(Ti.Calendar).have.a.readOnlyProperty('allEditableCalendars').which.is.an.Array;
		});
	});

	describe('#calendarAuthorization', function () {
		it('is a Number', function () {
			should(Ti.Calendar).have.a.readOnlyProperty('calendarAuthorization').which.is.a.Number;
		});
	});

	describe('#defaultCalendar', function () {
		it('is an Object', function () {
			should(Ti.Calendar).have.a.readOnlyProperty('defaultCalendar').which.is.an.Object;
		});
	});

	describe('#selectableCalendars', function () {
		it('is an Array', function () {
			should(Ti.Calendar).have.a.readOnlyProperty('selectableCalendars').which.is.an.Array;
		});
	});

	describe('#hasCalendarPermissions()', function () {
		it('is a Function', function () {
			should(Ti.Calendar.hasCalendarPermissions).be.a.Function;
		});
	});

	describe('#requestCalendarPermissions()', function () {
		it('is a Function', function () {
			should(Ti.Calendar.requestCalendarPermissions).be.a.Function;
		});
	});

	describe('#getCalendarById()', function () {
		it('is a Function', function () {
			should(Ti.Calendar.getCalendarById).be.a.Function;
		});
	});
});
