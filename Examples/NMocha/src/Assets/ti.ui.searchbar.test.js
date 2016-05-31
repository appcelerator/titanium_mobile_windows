/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe('Ti.UI.SearchBar', function () {
	it('TableView', function (finish) {
		var win = Ti.UI.createWindow();
		var sb = Titanium.UI.createSearchBar({
			barColor: 'blue',
			height: 44
		});
		var table = Ti.UI.createTableView({
			height: 600,
			width: '100%',
			top: 75,
			left: 0
		});
		win.addEventListener('open', function () {
			table.search = sb;
			setTimeout(function () {
				win.close();
				finish();
			}, 1000);
		});
		win.add(table);
		win.open();
	});
	it('ListView', function (finish) {
		var win = Ti.UI.createWindow();
		var sb = Titanium.UI.createSearchBar({
			barColor: 'blue',
			height: 44
		});
		var listview = Ti.UI.createListView({
			height: 600,
			width: '100%',
			top: 75,
			left: 0
		});
		win.addEventListener('open', function () {
			listview.searchView = sb;
			setTimeout(function () {
				win.close();
				finish();
			}, 1000);
		});
		win.add(listview);
		win.open();
	});

	it('TIMOB-9745,TIMOB-7020', function (finish) {
		var win = Ti.UI.createWindow();
		var data = [ {
			title: 'Row 1',
			color: 'red'
		}, {
			title: 'Row 2',
			color: 'green'
		} ];
		var sb = Titanium.UI.createSearchBar({
			barColor: 'blue',
			showCancel: false,
			height: 44
		});
		var table = Ti.UI.createTableView({
			height: 600,
			width: '100%',
			search: sb,
			top: 75,
			left: 0,
			data: data
		});
		win.addEventListener('open', function() {
			should(function() {
				win.add(table);
			}).not.throw();
			should(function() {
				win.remove(table);
			}).not.throw();
			should(function() {
				win.add(table);
			}).not.throw();
			should(sb.getHeight()).eql(44);
			should(sb.getShowCancel()).be.false;
			should(sb.getBarColor()).eql('blue');
			setTimeout(function () {
				win.close();
				finish();
			}, 1000);
		});
		win.open();
	});
});
