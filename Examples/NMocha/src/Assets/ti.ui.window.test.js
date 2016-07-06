/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

require('ti-mocha');
var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities'),
	didFocus = false;

describe('Titanium.UI.Window', function () {
	this.timeout(5000);
	beforeEach(function() {
		didFocus = false;
	});

	it('title', function () {
		var bar = Ti.UI.createWindow({
			title: 'this is some text'
		});
		should(bar.title).be.a.String;
		should(bar.getTitle).be.a.Function;
		should(bar.title).eql('this is some text');
		should(bar.getTitle()).eql('this is some text');
		bar.title = 'other text';
		should(bar.title).eql('other text');
		should(bar.getTitle()).eql('other text');
	});

	it('titleid', function () {
		var bar = Ti.UI.createWindow({
			titleid: 'this_is_my_key'
		});
		should(bar.titleid).be.a.String;
		should(bar.getTitleid).be.a.Function;
		should(bar.titleid).eql('this_is_my_key');
		should(bar.getTitleid()).eql('this_is_my_key');
		should(bar.title).eql('this is my value');
		bar.titleid = 'other text';
		should(bar.titleid).eql('other text');
		should(bar.getTitleid()).eql('other text');
		should(bar.title).eql('this is my value'); // FIXME Windows: https://jira.appcelerator.org/browse/TIMOB-23498
	});

	// FIXME Get working on iOS. iOS reports size of 100, which seems right...
	// FIXME Get working on Android. Also reports size of 100...
	(((utilities.isWindows10() && utilities.isWindowsDesktop()) || utilities.isIOS() || utilities.isAndroid()) ? it.skip : it)('window_size_is_read_only', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'blue',
			width: 100,
			height: 100
		});
		w.addEventListener('focus', function () {
			var error;
			if (didFocus) return;
			didFocus = true;
			try {
				should(w.size.width).not.be.eql(100); // iOS fails here
				should(w.size.height).not.be.eql(100);
			} catch (err) {
				error = err;
			}
			setTimeout(function () {
				w.close();
				finish(error);
			}, 1000);
		});
		w.open();
	});

	// FIXME Get working on iOS. reports left of 100, which seems right!
	(((utilities.isWindows10() && utilities.isWindowsDesktop()) || utilities.isIOS()) ? it.skip : it)('window_position_is_read_only', function (finish) {
		var w = Ti.UI.createWindow({
			backgroundColor: 'green',
			left: 100,
			right: 100
		});
		w.addEventListener('focus', function () {
			var error;
			if (didFocus) return;
			didFocus = true;
			try {
				should(w.rect.left).not.be.eql(100); // ios reports 100
				should(w.rect.right).not.be.eql(100);
			} catch (err) {
				error = err;
			}
			setTimeout(function () {
				w.close();
				finish(error);
			}, 1000);
		});
		w.open();
	});

	((utilities.isWindows10() && utilities.isWindowsDesktop()) ? it.skip : it)('window_post_layout', function (finish) {
		var win = Ti.UI.createWindow({
				backgroundColor: 'yellow'
			}),
			winEvent = 0;
		win.addEventListener('postlayout', function (e) {
			winEvent += 1;
		});
		setTimeout(function () {
			var error;
			try {
				should(winEvent).be.above(0);
			} catch (err) {
				error = err;
			}
			win.close();
			finish(error);
		}, 3000);
		win.open();
	});

	it('remove_children', function (finish) {
		var win = Ti.UI.createWindow({
			backgroundColor: 'gray'
		});
		var view = Ti.UI.createView();
		win.addEventListener('focus', function() {
			var error;
			if (didFocus) return;
			didFocus = true;
			try {
				should(win.children.length).be.eql(1);
				win.remove(win.children[0]);
				should(win.children.length).be.eql(0);
			} catch (err) {
				error = err;
			}
			setTimeout(function () {
				win.close();
				finish(error);
			}, 3000);
		});
		win.add(view);
		win.open();
	});

	it('windows_events', function (finish) {
		var win = Ti.UI.createWindow({
			backgroundColor: 'pink'
		});
		var focusEventFired = 0;
		var blurEventFired = 0;
		var openEventFired = 0;
		var closeEventFired = 0;

		win.addEventListener('focus', function () { focusEventFired++; });
		win.addEventListener('blur', function () { blurEventFired++; });
		win.addEventListener('open', function () { openEventFired++; });
		win.addEventListener('close', function () { closeEventFired++; });
		win.open();
		setTimeout(function () {
			win.close();
			setTimeout(function () {
				try {
					should(focusEventFired).be.eql(1);
					should(blurEventFired).be.eql(1);
					should(openEventFired).be.eql(1);
					should(closeEventFired).be.eql(1);
					finish();
				} catch (err) {
					finish(err);
				}
			}, 1000);
		}, 3000);
	});

	// For this test, you should see errors in the console, it is expected.
	// What you should not see is a crash
	it('should_not_crash', function (finish) {
		var win1 = Ti.UI.createWindow();
		win1.open();
		win1.close();
		var win2 = Ti.UI.createWindow();
		win2.close();
		win1.open();
		win2.close();
		setTimeout(function () {
			win1.close();
			setTimeout(function () {
				win1.close();
				finish();
			}, 1000);
		}, 1000);
	});

	it('window_close_order_1', function (finish) {
		var win1 = Ti.UI.createWindow({backgroundColor:'green'}),
			win2 = Ti.UI.createWindow({backgroundColor:'blue' }),
			win3 = Ti.UI.createWindow({backgroundColor:'gray' });

		win1.addEventListener('focus', function(e) {
			if (didFocus) return;
			didFocus = true;

			win2.open();
			setTimeout(function () {
				win3.open();
				setTimeout(function () {
					win3.close();
					setTimeout(function () {
						win2.close();
						setTimeout(function () {
							win1.close();
							finish();
						}, 500);
					}, 500);
				}, 500);
			}, 500);
		});

		win1.open();
	});

	it('window_close_order_2', function (finish) {
		var win1 = Ti.UI.createWindow({backgroundColor:'green'}),
			win2 = Ti.UI.createWindow({backgroundColor:'blue' }),
			win3 = Ti.UI.createWindow({backgroundColor:'gray' });

		win1.addEventListener('focus', function(e) {
			if (didFocus) return;
			didFocus = true;

			win2.open();
			setTimeout(function () {
				win3.open();
				win2.close();
				setTimeout(function () {
					win3.close();
					setTimeout(function () {
						win1.close();
						finish();
					}, 500);
				}, 500);
			}, 500);
		});

		win1.open();
	});

	// TIMOB-20600
	it('TIMOB-20600', function (finish) {
		var win1 = Ti.UI.createWindow({backgroundColor:'green'}),
			win2 = Ti.UI.createWindow({backgroundColor:'blue' }),
			win3 = Ti.UI.createWindow({backgroundColor:'gray' });

		win1.addEventListener('focus', function(e) {
			if (didFocus) return;
			didFocus = true;

			win2.open();
			setTimeout(function () {
				win3.open();
				setTimeout(function () {
					win2.close();
					setTimeout(function () {
						win3.close();
						setTimeout(function () {
							win1.close();
							finish();
						}, 500);
					}, 500);
				}, 500);
			}, 500);
		});

		win1.open();
	});

	it.skip('window_to_string', function () {
		var win = Ti.UI.createWindow();
		should(win.toString()).be.eql('[object Window]');
		should(win.apiName).be.a.String;
		should(win.apiName).be.eql('Ti.UI.Window');
	});

	// FIXME Get working on iOS
	// FIXME Get working on Android - Ti.UI.currentWindow is null
	// Supposedly this property should only exist when using Ti.UI.Window.url to load JS files into own context! But we support elsewhere for Windows
	((utilities.isIOS() || utilities.isAndroid()) ? it.skip : it)('window_currentWindow', function (finish) {
		var win = Ti.UI.createWindow({
			backgroundColor: 'yellow'
		});
		win.addEventListener('focus', function (e) {
			var error;

			if (didFocus) return;
			didFocus = true;

			try {
				should(Ti.UI.currentWindow).exist; // Android gives null
				should(Ti.UI.currentWindow).be.eql(win); // iOS fails here
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

	it.skip('window_navigation', function (finish) {
		var rootWindowFocus = 0;
		var rootWindowBlur = 0;
		var rootWindowOpen = 0;
		var rootWindowClose = 0;
		var secondWindowFocus = 0;
		var secondWindowBlur = 0;
		var secondWindowOpen = 0;
		var secondWindowClose = 0;
		var thridWindowFocus = 0;
		var thridWindowBlur = 0;
		var thridWindowOpen = 0;
		var thridWindowClose = 0;

		var rootWindow = Ti.UI.createWindow({
			backgroundColor: 'navy'
		});

		rootWindow.addEventListener('focus', function () { rootWindowFocus++ });
		rootWindow.addEventListener('blur', function () { rootWindowBlur++ });
		rootWindow.addEventListener('open', function () { rootWindowOpen++ });
		rootWindow.addEventListener('close', function () { rootWindowClose++ });
		rootWindow.open();

		setTimeout(function () {
			var secondWindow = Ti.UI.createWindow({
				backgroundColor: 'pink'
			});
			secondWindow.addEventListener('focus', function () { secondWindowFocus++ });
			secondWindow.addEventListener('blur', function () { secondWindowBlur++ });
			secondWindow.addEventListener('open', function () { secondWindowOpen++ });
			secondWindow.addEventListener('close', function () { secondWindowClose++ });
			secondWindow.open();

			setTimeout(function () {
				var thirdWindow = Ti.UI.createWindow({
					backgroundColor: 'green'
				});
				thirdWindow.addEventListener('focus', function () { thridWindowFocus++ });
				thirdWindow.addEventListener('blur', function () { thridWindowBlur++ });
				thirdWindow.addEventListener('open', function () { thridWindowOpen++ });
				thirdWindow.addEventListener('close', function () { thridWindowClose++ });
				thirdWindow.open();

				setTimeout(function () {
					thirdWindow.close();
					setTimeout(function () {
						secondWindow.close();
						setTimeout(function () {
							rootWindow.close();
							try {
								should(rootWindowFocus).be.eql(2);
								should(rootWindowBlur).be.eql(2);
								should(rootWindowOpen).be.eql(1);
								should(rootWindowClose).be.eql(1);

								should(secondWindowFocus).be.eql(2);
								should(secondWindowBlur).be.eql(2);
								should(secondWindowOpen).be.eql(1);
								should(secondWindowClose).be.eql(1);

								should(thridWindowFocus).be.eql(1);
								should(thridWindowBlur).be.eql(1);
								should(thridWindowOpen).be.eql(1);
								should(thridWindowClose).be.eql(1);
								finish();
							} catch(err) {
								finish(err);
							}
						}, 500);
					}, 500);
				}, 500);
			}, 500);
		}, 500);
	});
});
