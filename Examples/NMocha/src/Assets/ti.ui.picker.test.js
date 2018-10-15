/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2018 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
/* eslint-env mocha */
/* global Ti */
/* eslint no-unused-expressions: "off" */
'use strict';
var should = require('./utilities/assertions');

describe('Titanium.UI.Picker', function () {
	var fruit = [ 'Bananas', 'Strawberries', 'Mangos', 'Grapes' ];
	var color = [ 'red', 'green', 'blue', 'orange', 'red', 'green', 'blue', 'orange' ];
	var win;

	this.timeout(10000);

	afterEach(function () {
		if (win) {
			win.close();
		}
		win = null;
	});

	it('DatePicker', function (finish) {
		var date = new Date();
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_DATE,
			value: date
		});

		win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		win.add(picker);
		win.addEventListener('open', function () {
			try {
				should(picker.getValue()).be.eql(date);
				finish();
			} catch (err) {
				finish(err);
			}
		});
		win.open();
	});

	it('TimePicker', function (finish) {
		var date = new Date();
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_TIME,
			value: date
		});

		win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		win.add(picker);
		win.addEventListener('open', function () {
			try {
				should(picker.getValue().getHours()).be.eql(date.getHours());
				should(picker.getValue().getMinutes()).be.eql(date.getMinutes());
				finish();
			} catch (err) {
				finish(err);
			}
		});
		win.open();
	});

	it('PlainPicker', function (finish) {
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_PLAIN
		});

		win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		win.add(picker);
		win.addEventListener('open', function () {
			try {
				should(picker).be.an.Object;
				picker.getValue();
				finish();
			} catch (err) {
				finish(err);
			}
		});
		win.open();
	});

	it('PlainPicker.add(PickerColumn)', function (finish) {
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_PLAIN
		});

		win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		win.add(picker);
		win.addEventListener('open', function () {
			var column,
				i,
				ilen,
				row;
			try {
				column = Ti.UI.createPickerColumn();
				for (i = 0, ilen = fruit.length; i < ilen; i++) {
					row = Ti.UI.createPickerRow({
						title: fruit[i], color: color[i], font: { fontSize: 24 },
					});
					column.addRow(row);
				}
				picker.add(column);

				should(picker.columns.length).be.eql(1);
				should(picker.columns[0]).be.an.Object;
				should(picker.columns[0].rows).be.an.Array;
				should(picker.columns[0].rows.length).be.eql(fruit.length);

				finish();
			} catch (err) {
				finish(err);
			}
		});
		win.open();
	});

	it('PlainPicker.add(multiple PickerColumn)', function (finish) {
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_PLAIN
		});

		win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		win.add(picker);
		win.addEventListener('open', function () {
			var column1,
				column2,
				i,
				ilen,
				row;
			try {
				column1 = Ti.UI.createPickerColumn();
				for (i = 0, ilen = fruit.length; i < ilen; i++) {
					row = Ti.UI.createPickerRow({
						title: fruit[i], color: color[i], font: { fontSize: 24 },
					});
					column1.addRow(row);
				}

				column2 = Ti.UI.createPickerColumn();
				for (i = 0, ilen = color.length; i < ilen; i++) {
					row = Ti.UI.createPickerRow({
						title: color[i]
					});
					column2.addRow(row);
				}

				picker.add([ column1, column2 ]);

				should(picker.columns.length).be.eql(2);
				should(picker.columns[0]).be.an.Object;
				should(picker.columns[0].rows).be.an.Array;
				should(picker.columns[0].rows.length).be.eql(fruit.length);

				should(picker.columns[1]).be.an.Object;
				should(picker.columns[1].rows).be.an.Array;
				should(picker.columns[1].rows.length).be.eql(color.length);

				finish();
			} catch (err) {
				finish(err);
			}
		});
		win.open();
	});

	it('PlainPicker.add (PickerRow)', function (finish) {
		var picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_PLAIN
		});

		win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		win.add(picker);
		win.addEventListener('open', function () {
			var i,
				ilen,
				rows = [];
			try {
				for (i = 0, ilen = fruit.length; i < ilen; i++) {
					rows.push(Ti.UI.createPickerRow({
						title: fruit[i], color: color[i], font: { fontSize: 24 },
					}));
				}
				picker.add(rows);

				finish();
			} catch (err) {
				finish(err);
			}
		});
		win.open();
	});

	it('PlainPicker.removeRow', function (finish) {
		var picker,
			i,
			ilen,
			column,
			row;

		picker = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_PLAIN
		});
		column = Ti.UI.createPickerColumn();
		for (i = 0, ilen = fruit.length; i < ilen; i++) {
			row = Ti.UI.createPickerRow({
				title: fruit[i], color: color[i], font: { fontSize: 24 },
			});
			column.addRow(row);
		}
		picker.add(column);

		win = Ti.UI.createWindow({
			backgroundColor: '#000'
		});
		win.add(picker);
		win.addEventListener('open', function () {
			try {
				should(picker.columns.length).be.eql(1);
				should(picker.columns[0]).be.an.Object;
				should(picker.columns[0].rows).be.an.Array;
				should(picker.columns[0].rows.length).be.eql(fruit.length);

				picker.columns[0].removeRow(picker.columns[0].rows[0]);

				should(picker.columns.length).be.eql(1);
				should(picker.columns[0]).be.an.Object;
				should(picker.columns[0].rows).be.an.Array;
				should(picker.columns[0].rows.length).be.eql(fruit.length - 1);

				finish();
			} catch (err) {
				finish(err);
			}
		});
		win.open();
	});

	it('PlainPicker change event', function (finish) {
		var type2 = [];
		var pickerType = Ti.UI.createPicker();

		type2[0] = Ti.UI.createPickerRow({ title: 'Row 1' });
		type2[1] = Ti.UI.createPickerRow({ title: 'Row 2' });

		win = Ti.UI.createWindow();
		win.add(pickerType);
		pickerType.addEventListener('postlayout', loadTypes);
		pickerType.selectionIndicator = true;
		pickerType.addEventListener('change', pickerChange);

		function loadTypes() {
			pickerType.removeEventListener('postlayout', loadTypes);
			pickerType.add(type2);
			pickerType.setSelectedRow(0, 1);
		}

		function pickerChange() {
			finish();
		}

		win.open();
	});

	it('DatePicker minDate', function (finish) {
		var dp = Ti.UI.createPicker({
			titleype: Ti.UI.PICKER_TYPE_DATE
		});
		var date = new Date(2018, 1, 1);
		dp.setMinDate(date);

		win = Ti.UI.createWindow({ title: 'Form' });
		win.addEventListener('open', function () {
			try {
				should(dp.minDate).be.eql(date);
				finish();
			} catch (err) {
				finish(err);
			}
		});
		win.add(dp);
		win.open();
	});

	it('DatePicker maxDate', function (finish) {
		var dp = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_DATE
		});
		var date = new Date(2020, 1, 20);
		dp.setMaxDate(date);

		win = Ti.UI.createWindow({ title: 'Form' });
		win.addEventListener('open', function () {
			try {
				should(dp.maxDate).be.eql(date);
				finish();
			} catch (err) {
				finish(err);
			}
		});
		win.add(dp);
		win.open();
	});

	it('DatePicker postlayout event', function (finish) {
		var dp = Ti.UI.createPicker({
			type: Ti.UI.PICKER_TYPE_DATE
		});

		win = Ti.UI.createWindow({ title: 'Form' });
		dp.addEventListener('postlayout', function () {
			finish();
		});
		win.add(dp);
		win.open();
	});

	it.android('Selected index persistance', function (finish) {
		// workaround iOS triggering of 'postlayout' event
		var containerView = Ti.UI.createView();
		var picker = Ti.UI.createPicker({});
		var rows = [];
		var indexToTest = 2;

		for (var index = 0; index < 5; index++) {
			rows.push(Ti.UI.createPickerRow({ title: 'Item ' + (index + 1).toString() }));
		}

		picker.add(rows);

		win = Ti.UI.createWindow();
		win.add(picker);

		picker.addEventListener('change', function () {
			win.remove(picker);
			containerView.addEventListener('postlayout', finishTest);
			containerView.add(picker);
			win.add(containerView);
		});

		picker.addEventListener('postlayout', changeItem);

		win.open();

		function changeItem() {
			picker.removeEventListener('postlayout', changeItem);
			picker.setSelectedRow(0, indexToTest);
		}

		function finishTest() {
			if (rows.indexOf(picker.getSelectedRow(0)) === indexToTest) {
				finish();
			}
		}
	});
});
