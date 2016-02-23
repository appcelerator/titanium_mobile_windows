/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should'),
	didFocus = false;

describe("Titanium.UI.Picker", function() {
	this.timeout(5000);

	beforeEach(function() {
		didFocus = false;
		didPostlayout = false;
	});

	it("DatePicker", function(finish) {
		var date = new Date();
		var win = Ti.UI.createWindow({
			backgroundColor: "#000"
		});
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_DATE,
			value: date
		});
		win.add(picker);
		win.addEventListener('focus', function() {
			if (didFocus) return;
			didFocus = true;
			should(function() {
				should(picker.getValue()).be.eql(date);
			}).not.throw();
			setTimeout(function() {
				win.close();
				finish();
			}, 1000);
		});
		win.open();
	});
	it("TimePicker", function(finish) {
		var date = new Date();
		var win = Ti.UI.createWindow({
			backgroundColor: "#000"
		});
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_TIME,
			value: date
		});
		win.add(picker);
		win.addEventListener('focus', function() {
			if (didFocus) return;
			didFocus = true;
			should(function() {
				should(picker.getValue()).be.eql(date);
			}).not.throw();
			setTimeout(function() {
				win.close();
				finish();
			}, 1000);
		});
		win.open();
	});
	it("PlainPicker", function(finish) {
		var win = Ti.UI.createWindow({
			backgroundColor: "#000"
		});
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_PLAIN
		});
		win.add(picker);
		win.addEventListener('focus', function() {
			if (didFocus) return;
			didFocus = true;
			should(function() {
				should(picker).be.an.Object;
				picker.getValue();
			}).not.throw();
			setTimeout(function() {
				win.close();
				finish();
			}, 1000);
		});
		win.open();
	});

});
