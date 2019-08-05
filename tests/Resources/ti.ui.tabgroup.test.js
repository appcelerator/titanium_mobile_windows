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
const should = require('./utilities/assertions'); // eslint-disable-line no-unused-vars

// skipping many test on Windows due to lack of event firing, see https://jira.appcelerator.org/browse/TIMOB-26690
describe('Titanium.UI.TabGroup', function () {
	let tabGroup;

	this.timeout(5000);

	afterEach(function (done) {
		if (tabGroup) {
			// If `tabGroup` is already closed, we're done.
			let t = setTimeout(function () {
				if (tabGroup) {
					tabGroup = null;
					done();
				}
			}, 3000);

			tabGroup.addEventListener('close', function listener () {
				clearTimeout(t);

				if (tabGroup) {
					tabGroup.removeEventListener('close', listener);
				}
				tabGroup = null;
				done();
			});
			tabGroup.close();
		} else {
			tabGroup = null;
			done();
		}
	});

	it.windowsBroken('add Map.View to TabGroup', function (finish) {
		this.slow(5000);
		this.timeout(10000);

		const map = require('ti.map');
		const mapView = map.createView({ top: 0, height: '80%' });
		mapView.addEventListener('complete', function listener () {
			mapView.removeEventListener('complete', listener);
			finish();
		});

		const win = Ti.UI.createWindow();
		win.add(mapView);

		tabGroup = Ti.UI.createTabGroup();
		const tab = Ti.UI.createTab({
			title: 'Tab',
			window: win
		});

		tabGroup.addTab(tab);
		tabGroup.open();
	});

	it.ios('.tabs', () => {
		const win = Ti.UI.createWindow();
		tabGroup = Ti.UI.createTabGroup();
		const tab = Ti.UI.createTab({
			title: 'Tab',
			window: win
		});

		tabGroup.addTab(tab);
		should(tabGroup.tabs.length).eql(1);
		tabGroup.removeTab(tab);
		should(tabGroup.tabs.length).eql(0);
	});

	it.ios('.allowUserCustomization', () => {
		const win = Ti.UI.createWindow();
		tabGroup = Ti.UI.createTabGroup({
			allowUserCustomization: true
		});
		const tab = Ti.UI.createTab({
			title: 'Tab',
			window: win
		});

		tabGroup.addTab(tab);
		should(tabGroup.allowUserCustomization).eql(true);
		tabGroup.setAllowUserCustomization(false);
		should(tabGroup.allowUserCustomization).eql(false);
	});

	it.ios('.tabsTranslucent', () => {
		const win = Ti.UI.createWindow();
		tabGroup = Ti.UI.createTabGroup({
			tabsTranslucent: true
		});
		const tab = Ti.UI.createTab({
			title: 'Tab',
			window: win
		});

		tabGroup.addTab(tab);
		should(tabGroup.tabsTranslucent).eql(true);
		tabGroup.setTabsTranslucent(false);
		should(tabGroup.tabsTranslucent).eql(false);
	});

	it.windowsBroken('#setTabs()', () => {
		const winA = Ti.UI.createWindow(),
			tabA = Ti.UI.createTab({
				title: 'Tab A',
				window: winA
			}),
			winB = Ti.UI.createWindow(),
			tabB = Ti.UI.createTab({
				title: 'Tab B',
				window: winB
			});
		tabGroup = Ti.UI.createTabGroup();

		tabGroup.setTabs([ tabA, tabB ]);
		should(tabGroup.getTabs()).eql([ tabA, tabB ]);
	});

	it.windowsBroken('#setActiveTab()', finish => {
		const winA = Ti.UI.createWindow(),
			tabA = Ti.UI.createTab({
				title: 'Tab A',
				window: winA
			}),
			winB = Ti.UI.createWindow(),
			tabB = Ti.UI.createTab({
				title: 'Tab B',
				window: winB
			});
		tabGroup = Ti.UI.createTabGroup();

		// Does windows fire this event?
		// Can we test this without even opening tab group?
		tabGroup.addEventListener('open', () => {
			try {
				tabGroup.setActiveTab(tabB);
				should(tabGroup.getActiveTab().title).be.a.String;
				should(tabGroup.getActiveTab().title).eql('Tab B');
				finish();
			} catch (err) {
				finish(err);
			} finally {
				tabGroup.removeTab(tabA);
				tabGroup.removeTab(tabB);
			}
		});

		tabGroup.addTab(tabA);
		tabGroup.addTab(tabB);
		tabGroup.open();
	});

	it.android('#disableTabNavigation()', function (finish) {
		const winA = Ti.UI.createWindow(),
			tabA = Ti.UI.createTab({
				title: 'Tab A',
				window: winA
			}),
			winB = Ti.UI.createWindow(),
			tabB = Ti.UI.createTab({
				title: 'Tab B',
				window: winB
			});
		this.timeout(5000);
		tabGroup = Ti.UI.createTabGroup();

		// does windows fire this event?
		tabGroup.addEventListener('open', () => {
			try {
				tabGroup.disableTabNavigation(true);
				tabGroup.setActiveTab(tabB);
				should(tabGroup.getActiveTab().title).be.a.String;
				should(tabGroup.getActiveTab().title).eql('Tab A');
				tabGroup.disableTabNavigation(false);
				tabGroup.setActiveTab(tabB);
				should(tabGroup.getActiveTab().title).be.a.String;
				should(tabGroup.getActiveTab().title).eql('Tab B');
				finish();
			} catch (err) {
				finish(err);
			} finally {
				tabGroup.removeTab(tabA);
				tabGroup.removeTab(tabB);
			}
		});

		tabGroup.addTab(tabA);
		tabGroup.addTab(tabB);
		tabGroup.open();
	});

	it('.title', () => {
		tabGroup = Ti.UI.createTabGroup({
			title: 'My title'
		});

		should(tabGroup.getTitle()).be.a.String;
		should(tabGroup.getTitle()).eql('My title');
	});

	describe('events', function () {
		this.timeout(5000);

		// FIXME Windows doesn't fire open/close events
		it.windowsMissing('close', finish => {
			const win = Ti.UI.createWindow();
			tabGroup = Ti.UI.createTabGroup();
			const tab = Ti.UI.createTab({
				title: 'Tab',
				window: win
			});

			tabGroup.addEventListener('open', () => {
				setTimeout(() => tabGroup.close(), 1);
			});
			tabGroup.addEventListener('close', function listener () {
				tabGroup.removeEventListener('close', listener);
				finish();
			});

			tabGroup.addTab(tab);
			tabGroup.open();
		});

		// times out, presumably doesn't fire event?
		// intermittently times out on Android
		it.windowsBroken('focus', finish => {
			const win = Ti.UI.createWindow();
			tabGroup = Ti.UI.createTabGroup();
			const tab = Ti.UI.createTab({
				window: win,
				title: 'Tab'
			});

			tabGroup.addEventListener('focus', function listener () {
				tabGroup.removeEventListener('focus', listener);
				finish();
			});

			tabGroup.addTab(tab);
			tabGroup.open();
		});

		// times out, presumably doesn't fire event?
		it.windowsBroken('blur', finish => {
			const win = Ti.UI.createWindow();
			tabGroup = Ti.UI.createTabGroup();
			const tab = Ti.UI.createTab({
				title: 'Tab',
				window: win
			});

			function done() {
				tabGroup.removeEventListener('blur', done);
				finish();
			}

			tabGroup.addEventListener('blur', done);
			tabGroup.addEventListener('open', () => {
				setTimeout(() => tabGroup.close(), 1);
			});

			tabGroup.addTab(tab);
			tabGroup.open();
		});
	});

	it.windowsBroken('#setActiveTab()', finish => {
		const winA = Ti.UI.createWindow(),
			tabA = Ti.UI.createTab({
				title: 'Tab A',
				window: winA
			}),
			winB = Ti.UI.createWindow(),
			tabB = Ti.UI.createTab({
				title: 'Tab B',
				window: winB
			});
		tabGroup = Ti.UI.createTabGroup();

		// Does windows fire this event?
		// Can we test this without even opening tab group?
		tabGroup.addEventListener('open', () => {
			try {
				tabGroup.setActiveTab(tabB);
				should(tabGroup.getActiveTab().title).be.a.String;
				should(tabGroup.getActiveTab().title).eql('Tab B');
				finish();
			} catch (err) {
				finish(err);
			} finally {
				tabGroup.removeTab(tabA);
				tabGroup.removeTab(tabB);
			}
		});

		tabGroup.addTab(tabA);
		tabGroup.addTab(tabB);
		tabGroup.open();
	});

	it.windowsBroken('#setActiveTab()_before_open', finish => {
		const winA = Ti.UI.createWindow(),
			tabA = Ti.UI.createTab({
				title: 'Tab A',
				window: winA
			}),
			winB = Ti.UI.createWindow(),
			tabB = Ti.UI.createTab({
				title: 'Tab B',
				window: winB
			});
		tabGroup = Ti.UI.createTabGroup();
		tabGroup.setActiveTab(1);
		// Does windows fire this event?
		// Can we test this without even opening tab group?
		tabGroup.addEventListener('open', () => {
			try {
				should(tabGroup.getActiveTab().title).be.a.String;
				should(tabGroup.getActiveTab().title).eql('Tab B');
				finish();
			} catch (err) {
				finish(err);
			} finally {
				tabGroup.removeTab(tabA);
				tabGroup.removeTab(tabB);
			}
		});

		tabGroup.addTab(tabA);
		tabGroup.addTab(tabB);
		tabGroup.open();
	});

	it.windowsBroken('#change_activeTab_property', finish => {
		const winA = Ti.UI.createWindow(),
			tabA = Ti.UI.createTab({
				title: 'Tab A',
				window: winA
			}),
			winB = Ti.UI.createWindow(),
			tabB = Ti.UI.createTab({
				title: 'Tab B',
				window: winB
			});
		tabGroup = Ti.UI.createTabGroup();

		// Does windows fire this event?
		// Can we test this without even opening tab group?
		tabGroup.addEventListener('open', () => {
			try {
				tabGroup.activeTab = tabB;
				should(tabGroup.getActiveTab().title).be.a.String;
				should(tabGroup.getActiveTab().title).eql('Tab B');
				finish();
			} catch (err) {
				finish(err);
			} finally {
				tabGroup.removeTab(tabA);
				tabGroup.removeTab(tabB);
			}
		});

		tabGroup.addTab(tabA);
		tabGroup.addTab(tabB);
		tabGroup.open();
	});

	it.windowsBroken('#change_activeTab_property_before_open', finish => {
		const winA = Ti.UI.createWindow(),
			tabA = Ti.UI.createTab({
				title: 'Tab A',
				window: winA
			}),
			winB = Ti.UI.createWindow(),
			tabB = Ti.UI.createTab({
				title: 'Tab B',
				window: winB
			});
		tabGroup = Ti.UI.createTabGroup();
		tabGroup.activeTab = 1;
		// Does windows fire this event?
		// Can we test this without even opening tab group?
		tabGroup.addEventListener('open', () => {
			try {
				should(tabGroup.getActiveTab().title).be.a.String;
				should(tabGroup.getActiveTab().title).eql('Tab B');
				finish();
			} catch (err) {
				finish(err);
			} finally {
				tabGroup.removeTab(tabA);
				tabGroup.removeTab(tabB);
			}
		});

		tabGroup.addTab(tabA);
		tabGroup.addTab(tabB);
		tabGroup.open();
	});

	it.windowsBroken('#set_activeTab_in_creation_dictionary', finish => {
		const winA = Ti.UI.createWindow(),
			tabA = Ti.UI.createTab({
				title: 'Tab A',
				window: winA
			}),
			winB = Ti.UI.createWindow(),
			tabB = Ti.UI.createTab({
				title: 'Tab B',
				window: winB
			});
		tabGroup = Ti.UI.createTabGroup({
			activeTab: 1
		});
		// Does windows fire this event?
		// Can we test this without even opening tab group?
		tabGroup.addEventListener('open', () => {
			try {
				should(tabGroup.getActiveTab().title).be.a.String;
				should(tabGroup.getActiveTab().title).eql('Tab B');
				finish();
			} catch (err) {
				finish(err);
			} finally {
				tabGroup.removeTab(tabA);
				tabGroup.removeTab(tabB);
			}
		});

		tabGroup.addTab(tabA);
		tabGroup.addTab(tabB);
		tabGroup.open();
	});

	it('title after drawing the TabGroup', () => {
		const winA = Ti.UI.createWindow(),
			winB = Ti.UI.createWindow(),
			tabA = Ti.UI.createTab({ title: 'titleA', window: winA }),
			tabB = Ti.UI.createTab({ title: 'titleB', window: winB }),
			tabGroup = Ti.UI.createTabGroup({ tabs: [ tabA, tabB ] });
		tabGroup.addEventListener('open', () => {
			tabGroup.title = 'newTitle';
			tabGroup.setActiveTab(tabB);
		});
		tabB.addEventListener('selected', () => {
			should(tabGroup.title).be.a.String;
			should(tabGroup.title).eql('newTitle');
		});
	});

	it.windowsBroken('icon-only tabs - default style', (finish) => { // https://jira.appcelerator.org/browse/TIMOB-27264
		this.timeout(5000);
		tabGroup = Ti.UI.createTabGroup({
			tabs: [
				Ti.UI.createTab({
					icon: '/SmallLogo.png',
					window: Ti.UI.createWindow({ title: 'Tab 1' })
				}),
				Ti.UI.createTab({
					icon: '/SmallLogo.png',
					window: Ti.UI.createWindow({ title: 'Tab 2' })
				}),
			]
		});
		tabGroup.addEventListener('open', () => {
			finish();
		});
		tabGroup.open();
	});

	it.android('icon-only tabs - android bottom style', (finish) => {
		this.timeout(5000);
		tabGroup = Ti.UI.createTabGroup({
			style: Ti.UI.Android.TABS_STYLE_BOTTOM_NAVIGATION,
			tabs: [
				Ti.UI.createTab({
					icon: '/SmallLogo.png',
					window: Ti.UI.createWindow({ title: 'Tab 1' })
				}),
				Ti.UI.createTab({
					icon: '/SmallLogo.png',
					window: Ti.UI.createWindow({ title: 'Tab 2' })
				}),
			]
		});
		tabGroup.addEventListener('open', () => {
			finish();
		});
		tabGroup.open();
	});
});
