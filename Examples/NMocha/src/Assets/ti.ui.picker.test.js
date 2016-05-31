/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should'),
	utilities = require('./utilities/utilities'),
	didFocus = false;

describe('Titanium.UI.Picker', function() {
	this.timeout(5000);

	var fruit = ['Bananas', 'Strawberries', 'Mangos', 'Grapes'];
	var color = ['red', 'green', 'blue', 'orange', 'red', 'green', 'blue', 'orange'];

	beforeEach(function() {
		didFocus = false;
		didPostlayout = false;
	});

	it('DatePicker', function(finish) {
		var date = new Date();
		var win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_DATE,
			value: date
		});
		win.add(picker);
		win.addEventListener('open', function() {
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
	it('TimePicker', function(finish) {
		var date = new Date();
		var win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_TIME,
			value: date
		});
		win.add(picker);
		win.addEventListener('open', function() {
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
	it('PlainPicker', function(finish) {
		var win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_PLAIN
		});
		win.add(picker);
		win.addEventListener('open', function() {
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

	it('PlainPicker.add (PickerColumn)', function(finish) {
		var win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_PLAIN
		});

		win.add(picker);
		win.addEventListener('open', function() {
			var column = Ti.UI.createPickerColumn();
			for (var i = 0, ilen = fruit.length; i < ilen; i++) {
				var row = Ti.UI.createPickerRow({
					title: fruit[i], color: color[i], font: { fontSize: 24 },
				});
				column.addRow(row);
			}
			picker.add(column);

			should(picker.columns.length).be.eql(1);
			should(picker.columns[0]).be.an.Object;
			should(picker.columns[0].rows).be.an.Array;
			should(picker.columns[0].rows.length).be.eql(fruit.length);

			setTimeout(function() {
				win.close();
				finish();
			}, 1000);
		});
		win.open();
	});

	it('PlainPicker.add (multiple PickerColumn)', function(finish) {
		var win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_PLAIN
		});

		win.add(picker);
		win.addEventListener('open', function() {
			var column1 = Ti.UI.createPickerColumn();
			for (var i = 0, ilen = fruit.length; i < ilen; i++) {
				var row = Ti.UI.createPickerRow({
					title: fruit[i], color: color[i], font: { fontSize: 24 },
				});
				column1.addRow(row);
			}

			var column2 = Ti.UI.createPickerColumn();
			for (var i = 0, ilen = color.length; i < ilen; i++) {
				var row = Ti.UI.createPickerRow({
					title: color[i]
				});
				column2.addRow(row);
			}

			picker.add([column1, column2]);

			should(picker.columns.length).be.eql(2);
			should(picker.columns[0]).be.an.Object;
			should(picker.columns[0].rows).be.an.Array;
			should(picker.columns[0].rows.length).be.eql(fruit.length);

			should(picker.columns[1]).be.an.Object;
			should(picker.columns[1].rows).be.an.Array;
			should(picker.columns[1].rows.length).be.eql(color.length);

			setTimeout(function() {
				win.close();
				finish();
			}, 1000);
		});
		win.open();
	});
	it('PlainPicker.add (PickerRow)', function(finish) {
		var win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_PLAIN
		});

		win.add(picker);
		win.addEventListener('open', function() {
			var rows = [];
			for (var i = 0, ilen = fruit.length; i < ilen; i++) {
				rows.push(Ti.UI.createPickerRow({
					title: fruit[i], color: color[i], font: { fontSize: 24 },
				}));
			}
			picker.add(rows);
			setTimeout(function() {
				win.close();
				finish();
			}, 1000);
		});
		win.open();
	});

	it('PlainPicker.removeRow', function(finish) {
		var win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_PLAIN
		});

		var column = Ti.UI.createPickerColumn();
		for (var i = 0, ilen = fruit.length; i < ilen; i++) {
			var row = Ti.UI.createPickerRow({
				title: fruit[i], color: color[i], font: { fontSize: 24 },
			});
			column.addRow(row);
		}
		picker.add(column);

		win.add(picker);
		win.addEventListener('open', function() {

			should(picker.columns.length).be.eql(1);
			should(picker.columns[0]).be.an.Object;
			should(picker.columns[0].rows).be.an.Array;
			should(picker.columns[0].rows.length).be.eql(fruit.length);

			picker.columns[0].removeRow(picker.columns[0].rows[0]);

			should(picker.columns.length).be.eql(1);
			should(picker.columns[0]).be.an.Object;
			should(picker.columns[0].rows).be.an.Array;
			should(picker.columns[0].rows.length).be.eql(fruit.length - 1);

			setTimeout(function() {
				win.close();
				finish();
			}, 1000);
		});
		win.open();
	});
});
