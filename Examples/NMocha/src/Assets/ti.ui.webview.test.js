/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('should'),
	utilities = require('./utilities/utilities');

describe('Titanium.UI.WebView', function () {
	this.timeout(6e4);

	// Skip this on Windows 10 apps because internal network is unstable.
	(utilities.isWindows10() ? it.skip : it)('url', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var webview = Ti.UI.createWebView();

		w.addEventListener('open', function () {
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
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue'
		});
		var webview = Ti.UI.createWebView();
		webview.addEventListener('load', function () {
		    w.close();
		    finish();
		});
		w.addEventListener('open', function () {
			should(function () {
				webview.url = 'ti.ui.webview.test.html';
			}).not.throw();
		});

		w.add(webview);
		w.open();
	});

	(utilities.isWindows() ? it : it.skip)('url (ms-appx)', function (finish) {
	    var w = Ti.UI.createWindow({
	        backgroundColor: 'blue'
	    });
	    var webview = Ti.UI.createWebView();

	    webview.addEventListener('load', function () {
	        w.close();
	        finish();
	    });
	    w.addEventListener('open', function () {
	        should(function () {
	            webview.url = 'ms-appx:///ti.ui.webview.test.html';
	        }).not.throw();
	    });

	    w.add(webview);
	    w.open();
	});

	(utilities.isWindows() ? it : it.skip)('url (ms-appx-web)', function (finish) {
	    var w = Ti.UI.createWindow({
	        backgroundColor: 'blue'
	    });
	    var webview = Ti.UI.createWebView();

	    webview.addEventListener('load', function () {
	        w.close();
	        finish();
	    });
	    w.addEventListener('open', function () {
	        should(function () {
	            webview.url = 'ms-appx-web:///ti.ui.webview.test.html';
	        }).not.throw();
	    });

	    w.add(webview);
	    w.open();
	});

	(utilities.isWindows() ? it : it.skip)('url (ms-appx-data)', function (finish) {
	    function prepare(files) {
	        var webroot = Ti.Filesystem.applicationDataDirectory + 'webroot';
	        var webroot_file = Ti.Filesystem.getFile(webroot);
	        if (!webroot_file.exists()) {
	            webroot_file.createDirectory();
	        }
	        for (var i = 0; i < files.length; i++) {
	            var file = files[i];
	            var from = Ti.Filesystem.getFile(Ti.Filesystem.resourcesDirectory, file);
	            var to = webroot + Ti.Filesystem.separator + file;
	            from.copy(to)
	        }
	    }
	    var w = Ti.UI.createWindow({
	        backgroundColor: 'blue'
	    });
	    var webview = Ti.UI.createWebView();
	    webview.addEventListener('load', function () {
	        w.close();
	        finish();
	    });
	    w.addEventListener('open', function () {
	        prepare(['ti.ui.webview.test.html'])
	        should(function () {
	            webview.url = 'ms-appdata:///local/webroot/ti.ui.webview.test.html';
	        }).not.throw();
	    });

	    w.add(webview);
	    w.open();
	});

	// Skip this on desktop Windows apps because it crashes the app now.
	((utilities.isWindows10() && utilities.isWindowsDesktop()) ? it.skip : it)('evalJS', function (finish) {
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
		w.addEventListener('open', function () {
			should(function () {
				webview.url = 'ti.ui.webview.test.html';
			}).not.throw();
		});

		w.add(webview);
		w.open();
	});

});
