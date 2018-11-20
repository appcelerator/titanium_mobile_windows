/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-Present by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
/* eslint-env mocha */
/* global Ti */
/* eslint no-unused-expressions: "off" */
'use strict';
var should = require('./utilities/assertions'); // eslint-disable-line no-unused-vars

describe('Titanium.UI.TabGroup', function () {
	var tabGroup,
		tab;

	afterEach(function () {
		if (tab && tabGroup) {
			tabGroup.removeTab(tab);
		}
		tab = null;
	});

	it.windowsBroken('add Map.View to TabGroup', function (finish) {
		var win,
			map,
			mapView;
		this.timeout(10000);

		win = Ti.UI.createWindow();
		map = require('ti.map');
		mapView = map.createView({ top: 0, height: '80%' });

		mapView.addEventListener('complete', function () {
			tabGroup.close();
			finish();
		});

		win.add(mapView);

		tabGroup = Ti.UI.createTabGroup();
		tab = Ti.UI.createTab({
			title: 'Tab',
			window: win
		});

		tabGroup.addTab(tab);
		tabGroup.open();
	});

	it.ios('tabs', function () {
		var win = Ti.UI.createWindow();
		tabGroup = Ti.UI.createTabGroup();
		tab = Ti.UI.createTab({
			title: 'Tab',
			window: win
		});

		tabGroup.addTab(tab);
		should(tabGroup.tabs.length).eql(1);
		tabGroup.removeTab(tab);
		should(tabGroup.tabs.length).eql(0);
	});

	it.ios('allowUserCustomization', function () {
		var win = Ti.UI.createWindow();
		tabGroup = Ti.UI.createTabGroup({
			allowUserCustomization: true
		});
		tab = Ti.UI.createTab({
			title: 'Tab',
			window: win
		});

		tabGroup.addTab(tab);
		should(tabGroup.allowUserCustomization).eql(true);
		tabGroup.setAllowUserCustomization(false);
		should(tabGroup.allowUserCustomization).eql(false);
	});

	it.ios('tabsTranslucent', function () {
		var win = Ti.UI.createWindow();
		tabGroup = Ti.UI.createTabGroup({
			tabsTranslucent: true
		});
		tab = Ti.UI.createTab({
			title: 'Tab',
			window: win
		});

		tabGroup.addTab(tab);
		should(tabGroup.tabsTranslucent).eql(true);
		tabGroup.setTabsTranslucent(false);
		should(tabGroup.tabsTranslucent).eql(false);
	});

	// FIXME Windows doesn't fire open/close events
	it.windowsMissing('close event', function (finish) {
		var win;
		this.timeout(10000);

		win = Ti.UI.createWindow();
		tabGroup = Ti.UI.createTabGroup();

		tabGroup.addEventListener('open', function () {
			tabGroup.close();
		});

		tabGroup.addEventListener('close', function () {
			finish();
		});

		tab = Ti.UI.createTab({
			title: 'Tab',
			window: win
		});
		tabGroup.addTab(tab);

		tabGroup.open();
	});
});
