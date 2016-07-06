/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities');

describe('Titanium.UI.SearchBar', function () {
	// FIXME Intermittently fails on Android?
	(utilities.isAndroid() ? it.skip : it)('TableView', function (finish) {
		var win = Ti.UI.createWindow(),
			sb = Ti.UI.createSearchBar({
				barColor: 'blue',
				height: 44
			}),
			table = Ti.UI.createTableView({
				height: 600,
				width: '100%',
				top: 75,
				left: 0
			});

		win.addEventListener('open', function () {
			var error;

			try {
				table.search = sb;
			} catch (err) {
				error = err;
			}

			setTimeout(function () {
				win.close();
				finish(error);
			}, 1000);
		});
		win.add(table);
		win.open();
	});

	// FIXME this seems to hard-crash Android. No stacktrace, no errors from logcat. File a JIRA?
	(utilities.isAndroid() ? it.skip : it)('ListView', function (finish) {
		var win = Ti.UI.createWindow(),
			sb = Ti.UI.createSearchBar({
				barColor: 'blue',
				height: 44
			}),
			listview = Ti.UI.createListView({
				height: 600,
				width: '100%',
				top: 75,
				left: 0
			});

		win.addEventListener('open', function () {
			var error;

			try {
				listview.searchView = sb;
			} catch (err) {
				error = err;
			}

			setTimeout(function () {
				win.close();
				finish(error);
			}, 1000);
		});
		win.add(listview);
		win.open();
	});

	// FIXME this seems to hard-crash Android. No stacktrace, no errors from logcat. File a JIRA?
	(utilities.isAndroid() ? it.skip : it)('TIMOB-9745,TIMOB-7020', function (finish) {
		var win = Ti.UI.createWindow(),
			data = [{
				title: 'Row 1',
				color: 'red'
			},{
				title: 'Row 2',
				color: 'green'
			}],
			sb = Ti.UI.createSearchBar({
				barColor: 'blue',
				showCancel: false,
				height: 44
			}),
			table = Ti.UI.createTableView({
				height: 600,
				width: '100%',
				search: sb,
				top: 75,
				left: 0,
				data: data
			});

		win.addEventListener('open', function() {
			var error;

			try {
				win.add(table);
				win.remove(table);
				win.add(table);

				should(sb.getHeight()).eql(44);
				should(sb.getShowCancel()).be.false;
				should(sb.getBarColor()).eql('blue');
			} catch (err) {
				error = err;
			}

			setTimeout(function () {
				win.close();
				finish(error);
			}, 1000);
		});
		win.open();
	});
});
