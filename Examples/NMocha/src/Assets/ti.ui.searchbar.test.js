/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe('Ti.UI.SearchBar', function () {
	this.timeout(10000);
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
		var fruitSection = Ti.UI.createListSection({ headerTitle: 'Fruits ' });
		listview.sections = [fruitSection];
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

	it('Should be able to set/set hintText', function (finish) {
	    var search = Ti.UI.createSearchBar({
	        hintText: 'Search'
	    });
	    should(search.hintText).eql('Search');
	    should(search.getHintText()).eql('Search');
	    should(function () {
	        search.setHintText('Updated search');
	    }).not.throw();
	    should(search.hintText).eql('Updated search');
	    should(search.getHintText()).eql('Updated search');
	    finish();
	});

	it("hinttextid", function (finish) {
	    var search = Ti.UI.createSearchBar({
	        hinttextid: "this is my key"
	    });
	    should(search.hinttextid).be.a.String;
	    should(search.getHinttextid).be.a.Function;
	    should(search.hinttextid).eql('this is my key');
	    should(search.getHinttextid()).eql('this is my key');
	    should(search.hintText).eql('this is my value');
	    search.hinttextid = 'other text';
	    should(search.hinttextid).eql('other text');
	    should(search.getHinttextid()).eql('other text');
	    should(search.hintText).eql('this is my value'); // should retain old value if can't find key
	    finish();
	});
});
