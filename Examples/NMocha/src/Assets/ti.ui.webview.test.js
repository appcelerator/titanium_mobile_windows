/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('should'),
	utilities = require('./utilities/utilities'),
	didFocus = false;

describe('Titanium.UI.WebView', function () {

	beforeEach(function() {
		didFocus = false;
	});

	// Skip this on desktop Windows 10 apps because it crashes the app now.
	((utilities.isWindows10() && utilities.isWindowsDesktop()) ? it.skip : it)('url', function (finish) {
		this.timeout(10000);
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var webview = Ti.UI.createWebView();

		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
			should(function () {
				webview.url = 'http://www.appcelerator.com/';
			}).not.throw();
			setTimeout(function () {
				w.close();
				finish();
			}, 1000);
		});

		w.add(webview);
		w.open();
	});

	it('url(local)', function (finish) {
		this.timeout(10000);
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var webview = Ti.UI.createWebView();

		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
			should(function () {
				webview.url = 'ti.ui.webview.test.html';
			}).not.throw();
			setTimeout(function () {
				w.close();
				finish();
			}, 1000);
		});

		w.add(webview);
		w.open();
	});

	// Skip this on desktop Windows apps because it crashes the app now.
	((utilities.isWindows10() && utilities.isWindowsDesktop()) ? it.skip : it)('evalJS', function (finish) {
		this.timeout(10000);
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var webview = Ti.UI.createWebView();
		webview.addEventListener('load', function () {
			webview.evalJS('Ti.API.info("Hello, World!");"WebView.evalJS.TEST";', function (result) {
				should(result).be.eql('WebView.evalJS.TEST');
				setTimeout(function () {
					w.close();
					finish();
				}, 1000);
			});
		});
		w.addEventListener('focus', function () {
			if (didFocus) return;
			didFocus = true;
			should(function () {
				webview.url = 'ti.ui.webview.test.html';
			}).not.throw();
		});

		w.add(webview);
		w.open();
	});

});
