/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities'),
	didFocus = false,
	didPostlayout = false;

function createWindow(_args, finish) {
	_args = _args || {};
	_args.backgroundColor = _args.backgroundColor || 'red';
	var win = Ti.UI.createWindow(_args);
	win.addEventListener('open', function () {
		Ti.API.info('Got open event');
		setTimeout(function () {
			closeAndFinish(win, finish);
		}, 3000);
	});
	return win;
}

function closeAndFinish(win, finish) {
	Ti.API.info('Closing window');
	win.close();
	Ti.API.info('Finishing test');
	finish();
}

describe('Titanium.UI.Layout', function () {
	this.timeout(5000);

	beforeEach(function() {
		didFocus = false;
		didPostlayout = false;
	});

	// functional test cases #1010, #1011, #1025, #1025a
	//rect and size properties should not be undefined
	it('viewSizeAndRectPx', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView();
		var label = Ti.UI.createLabel({
			text: 'a',
			font: {
				fontSize: 14,
				fontFamily: 'monospace'
			}
		});
		win.add(view);
		win.add(label);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			Ti.API.info('Got postlayout');
			should(view.size).not.be.undefined;
			should(view.size.width).not.be.undefined;
			should(view.size.height).not.be.undefined;
			should(view.size.x).not.be.undefined;
			should(view.size.y).not.be.undefined;
			should(view.rect).not.be.undefined;
			should(view.rect.width).not.be.undefined;
			should(view.rect.height).not.be.undefined;
			should(view.rect.x).not.be.undefined;
			should(view.rect.y).not.be.undefined;
			//size and rect properties return the same width and height
			should(view.size.width).eql(view.rect.width);
			should(view.size.height).eql(view.rect.height);
			//size property returns 0 for x and y
			should(view.size.x).eql(0);
			should(view.size.y).eql(0);
			//Functonal test case 1025
			should(view.top).be.undefined;
			should(view.bottom).be.undefined;
			should(view.left).be.undefined;
			should(view.right).be.undefined;
			should(view.center).be.undefined;
			should(view.zIndex).be.undefined;
			//Functonal test case 1025a
			should(label.top).be.undefined;
			should(label.bottom).be.undefined;
			should(label.left).be.undefined;
			should(label.right).be.undefined;
			should(label.center).be.undefined;
			should(label.zIndex).be.undefined;
			//FILL behavior
			should(view.rect.x).eql(0);
			should(view.rect.y).eql(0);
			should(win.size.height / view.size.height).eql(1);
			should(win.size.width / view.size.width).eql(1);
		});
		win.open();
	});

	// functional test cases #1012, #1014:
	// ViewLeft and ViewRight
	it('viewLeft', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			left: 10,
			width: 10
		});
		var view2 = Ti.UI.createView({
			right: 10,
			width: 10
		});
		win.add(view);
		win.add(view2);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.left).eql(10);
			should(view.rect.x).eql(10);
			should(view.rect.width).eql(10);
			should(view.right).be.undefined;
			should(view2.right).eql(10);
			should(view2.rect.x).eql(win.size.width - 20);
			should(view2.rect.width).eql(10);
			should(view2.left).be.undefined;
		});
		win.open();
	});

	// functional test case #1016, #1018
	// ViewTop and ViewBottom
	it('viewTop', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			top: 10,
			height: 10
		});
		var view2 = Ti.UI.createView({
			bottom: 10,
			height: 10
		});
		win.add(view);
		win.add(view2);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.top).eql(10);
			should(view.rect.y).eql(10);
			should(view.rect.height).eql(10);
			should(view.bottom).be.undefined;
			should(view2.bottom).eql(10);
			should(view2.rect.y).eql(win.size.height - 20);
			should(view2.rect.height).eql(10);
			should(view2.top).be.undefined;
		});
		win.open();
	});

	// functional test case #1020: ViewCenter
	it.skip('viewCenter', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			center: {
				x: 50,
				y: 50
			},
			height: 40,
			width: 40
		});
		win.add(view);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.center.x).eql(50);
			should(view.center.y).eql(50);
			should(view.rect.x).eql(30);
			should(view.rect.y).eql(30);
		});
		win.open();
	});

	// functional test case #1022, #1024
	// ViewWidth, ViewHeight
	((utilities.isWindows10() && utilities.isWindowsDesktop()) ? it.skip : it)('viewWidth', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			width: 10,
			height: 10
		});
		win.add(view);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.width).eql(10);
			should(view.size.width).eql(10);
			should(view.height).eql(10);
			should(view.size.height).eql(10);
			should(view.left).be.undefined;
			should(view.right).be.undefined;
			should(view.top).be.undefined;
			should(view.bottom).be.undefined;
			//Centered View with width and height defined
			// FIXME There's nothing to indicate that x/y should be integers, but this test assumed they were, so I had to rewrite to wrap them in Math.floor
			should(view.rect.x).eql(Math.floor((win.size.width - view.size.width) / 2));
			should(view.rect.y).eql(Math.floor((win.size.height - view.size.height) / 2));
			//should(Math.floor(view.rect.x)).eql(Math.floor((win.size.width - view.size.width) / 2));
			//should(Math.floor(view.rect.y)).eql(Math.floor((win.size.height - view.size.height) / 2));
		});
		win.open();
	});

	// functional test #1026 ViewError
	it.skip('viewError', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			backgroundColor: 'green',
			left: 'leftString',
			right: 'rightString',
			top: 'topString',
			bottom: 'bottomString',
			width: 'widthString',
			height: 'heightString',
			center: {
				x: 'centerXString',
				y: 'centerYString'
			}
		});
		win.add(view);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.left).eql('leftString');
			should(view.right).eql('rightString');
			should(view.top).eql('topString');
			should(view.bottom).eql('bottomString');
			should(view.center.y).eql('centerYString');
			should(view.center.x).eql('centerXString');
			should(view.width).eql('widthString');
			should(view.height).eql('heightString');
		});
		win.open();
	});

	// functional test #1033, 1033a, 1033b
	// UndefinedWidth Implicit calculations
	it('undefinedWidth', function (finish) {
		var win = createWindow({}, finish);
		var parentView = Ti.UI.createView({
			width: 100,
			height: 100
		});
		var view1 = Ti.UI.createView({
			left: 5,
			right: 10
		});
		var view2 = Ti.UI.createView({
			left: 5,
			center: {
				x: 10
			}
		});
		var view3 = Ti.UI.createView({
			center: {
				x: 75
			},
			right: 10
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view1.width).be.undefined;
			should(view2.width).be.undefined;
			should(view3.width).be.undefined;
			should(view1.rect.width).eql(85);
			/*
			// This is wrong... i think
			should(view2.rect.width).eql(10);
			should(view3.rect.width).eql(30);
			*/
		});
		parentView.add(view1);
		parentView.add(view2);
		parentView.add(view3);
		win.add(parentView);
		win.open();
	});

	// functional test #1034/1034a/1034b UndefinedLeft
	it('undefinedLeft', function (finish) {
		var win = createWindow({}, finish);
		var view1 = Ti.UI.createView({
			width: 120,
			center: {
				x: 80
			}
		});
		var view2 = Ti.UI.createView({
			right: 120,
			center: {
				x: 80
			}
		});
		var view3 = Ti.UI.createView({
			right: 80,
			width: 120
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view1.left).be.undefined;
			should(view2.left).be.undefined;
			should(view3.left).be.undefined;
			should(view1.rect.x).not.be.undefined;
			should(view2.rect.x).not.be.undefined;
			should(view3.rect.x).not.be.undefined;
			should(view1.rect.y).not.be.undefined;
			should(view2.rect.y).not.be.undefined;
			should(view3.rect.y).not.be.undefined;
			should(view1.rect.width).not.be.undefined;
			should(view2.rect.width).not.be.undefined;
			should(view3.rect.width).not.be.undefined;
			should(view1.rect.height).not.be.undefined;
			should(view2.rect.height).not.be.undefined;
			should(view3.rect.height).not.be.undefined;
		});
		win.add(view1);
		win.add(view2);
		win.add(view3);
		win.open();
	});

	// functional test #1035 & #1039 UndefinedCenter
	it('undefinedCenter', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.center).be.undefined;
			//Dynamic center can be calculated from view.rect
			should(view.rect).not.be.undefined;
		});
		win.add(view);
		win.open();
	});

	// functional test #1036 UndefinedRight
	// FIXME Open a JIRA to fix this on iOS, because it causes a crash!
	(utilities.isIOS() ? it.skip : it)('undefinedRight', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			backgroundColor: 'yellow',
			center: {
				x: 50
			},
			left: 10
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.right).be.undefined;
			// this is wrong
			// should(view.rect.width).eql(80);
			should(view.rect.x).eql(10);
		});
		win.add(view);
		win.open();
	});

	// functional test #1037, #1037a, #1037b
	// UndefinedHeight Implicit calculations
	it('undefinedHeight', function (finish) {
		var win = createWindow({}, finish);
		var parentView = Ti.UI.createView({
			width: 100,
			height: 100
		});
		var view1 = Ti.UI.createView({
			top: 5,
			bottom: 10
		});
		var view2 = Ti.UI.createView({
			top: 5,
			center: {
				y: 10
			}
		});
		var view3 = Ti.UI.createView({
			center: {
				y: 75
			},
			bottom: 10
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view1.height).be.undefined;
			should(view2.height).be.undefined;
			should(view3.height).be.undefined;
			should(view1.rect.height).eql(85);
			// should(view2.rect.height).eql(10);
			// should(view3.rect.height).eql(30);
		});
		parentView.add(view1);
		parentView.add(view2);
		parentView.add(view3);
		win.add(parentView);
		win.open();
	});

	// functional test #1038, 1038a, 1038b
	// UndefinedTop. Dynamic top calculation
	it.skip('undefinedTop', function (finish) {
		var win = createWindow({}, finish);
		var view1 = Ti.UI.createView({
			height: 50,
			center: {
				y: 200
			}
		});
		var view2 = Ti.UI.createView({
			center: {
				y: 50
			},
			bottom: 200
		});
		var view3 = Ti.UI.createView({
			bottom: 200,
			height: 100
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			//Static Tops
			should(view1.top).be.undefined;
			should(view2.top).be.undefined;
			should(view3.top).be.undefined;
			//Dynamic Tops
			should(view1.rect.y).eql(175);
			if (win.size.height <= 250) {//View Height of 0 positioned at center
				should(view2.rect.y).eql(50);
			} else {//View height = 2x(wh - bottom - center)
				//View top = center - height/2 = 2c + b - wh
				should(view2.rect.y).eql(300 - win.size.height);
			}
			should(view3.rect.y).eql(win.size.height - 300);
		});
		win.add(view1);
		win.add(view2);
		win.add(view3);
		win.open();
	});
	// functional test #1040 UndefinedBottom
	it('undefinedBottom', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			backgroundColor: 'yellow',
			center: {
				y: 50
			},
			top: 10
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.bottom).be.undefined;
			//Dynamic bottom is rect.y + rect.height
			should(view.rect.height).not.be.undefined;
		});
		win.add(view);
		win.open();
	});
	// functional test #1042 WidthPrecedence
	it('widthPrecedence', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			backgroundColor: 'yellow',
			left: 10,
			right: 15,
			width: 10
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.size.width).eql(10);
		});
		win.add(view);
		win.open();
	});
	// functional test #1043 LeftPrecedence
	// Chris W: Skipping because we don't have any precedence set up yet for the properties, as far as I know...
	it.skip('leftPrecedence', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			backgroundColor: 'yellow',
			left: 10,
			right: 100,
			center: {
				x: 30
			}
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.size.width).eql(40);
		});
		win.add(view);
		win.open();
	});
	// functional test #1044 CenterXPrecedence
	it.skip('centerXPrecedence', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			height: 200,
			width: 200,
			backgroundColor: 'yellow'
		});
		var viewChild = Ti.UI.createView({
			backgroundColor: 'red',
			center: {
				x: 100
			},
			right: 50
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(viewChild.size.width).eql(100);
		});
		view.add(viewChild);
		win.add(view);
		win.open();
	});
	// functional test #1046 HeightPrecedence
	it('heightPrecedence', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			backgroundColor: 'yellow',
			top: 10,
			bottom: 15,
			height: 10
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.size.height).eql(10);
		});
		win.add(view);
		win.open();
	});
	// functional test #1047 TopPrecedence
	// Chris W: Skipping because we don't have any precedence set up yet for the properties, as far as I know...
	it.skip('topPrecedence', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			backgroundColor: 'yellow',
			top: 10,
			bottom: 100,
			center: {
				y: 30
			}
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.size.height).eql(40);
		});
		win.add(view);
		win.open();
	});

	// functional test #1048 CenterYPrecedence
	it.skip('centerYPrecedence', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			height: 200,
			width: 200,
			backgroundColor: 'yellow'
		});
		var viewChild = Ti.UI.createView({
			backgroundColor: 'red',
			center: {
				y: 100
			},
			bottom: 50
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(viewChild.size.height).eql(100);
		});
		view.add(viewChild);
		win.add(view);
		win.open();
	});

	// functional test #1053 ScrollViewSize
	// This is completely wrong. Adding a scrollview to a label?
	// Really? Skipping
	it.skip('scrollViewSize', function (finish) {
		var win = createWindow({}, finish);
		var label = Ti.UI.createLabel({
			color: 'red'
		});
		var label2 = Ti.UI.createLabel({
			text: 'View Size is: ',
			top: 20,
			left: 10,
			height: 200,
			color: 'black'
		});
		var scrollView = Titanium.UI.createScrollView({
			contentHeight: 'auto',
			contentWidth: 'auto',
			showVerticalScrollIndicator: true,
			showHorizontalScrollIndicator: true,
			width: Ti.UI.SIZE,
			height: Ti.UI.SIZE
		});
		var scrollView2 = Titanium.UI.createScrollView({
			contentHeight: 'auto',
			contentWidth: 'auto',
			showVerticalScrollIndicator: true,
			showHorizontalScrollIndicator: true
		});
		label.add(scrollView);
		label2.add(scrollView2);
		var view = Ti.UI.createView({
			backgroundColor: 'green',
			borderRadius: 10,
			width: 200,
			height: 200
		});
		//var scrollView3 = Titanium.UI.createScrollView({
		//	contentHeight: 'auto',
		//	contentWidth: 'auto',
		//	showVerticalScrollIndicator: true,
		//	showHorizontalScrollIndicator: true
		//});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			//LABEL HAS SIZE AUTO BEHAVIOR.
			//SCROLLVIEW HAS FILL BEHAVIOR
			//LABEL will have 0 size (no text)
			//LABEL2 will have non 0 size (has text/pins)
			should(label.size).not.be.undefined;
			should(label2.size).not.be.undefined;
			should(scrollView.size).not.be.undefined;
			should(scrollView2.size).not.be.undefined;
			if (utilities.isIPhone()) {
				//Android does not return 0 height even when there is no text
				should(label.size.width).eql(0);
				should(label.size.height).eql(0);
				// Adding a scroll view to a label does not work in android: TIMOB-7817
				should(scrollView.size.width).eql(0);
				should(scrollView.size.height).eql(0);
				should(label2.size.height).not.be.eql(0);
				should(label2.size.width).not.be.eql(0);
				should(scrollView2.size.height).not.be.eql(0);
				should(scrollView2.size.width).not.be.eql(0);
				should(label2.size.width).eql(scrollView2.size.width);
				should(label2.size.height).eql(scrollView2.size.height);
			}
			// This is not working yet due to TIMOB-5303
			// valueOf(testRun, scrollView3.size.height).shouldNotBe(0);
			// valueOf(testRun, scrollView3.size.width).shouldNotBe(0);
			//
			// valueOf(testRun, view.size.width).shouldBe(scrollView3.size.width);
			// valueOf(testRun, view.size.height).shouldBe(scrollView3.size.height);
		});
		view.add(scrollView);
		win.add(view);
		win.add(scrollView2);
		win.add(label);
		win.open();
	});

	// functional test #1106 ZIndexMultiple
	it('zIndexMultiple', function (finish) {
		var win = createWindow({}, finish);
		var view1 = Ti.UI.createView({
			backgroundColor: 'red',
			zIndex: 0,
			height: 50,
			width: 50,
			top: 10
		});
		var view2 = Ti.UI.createView({
			backgroundColor: 'orange',
			zIndex: 1,
			height: 50,
			width: 50,
			top: 20
		});
		var view3 = Ti.UI.createView({
			backgroundColor: 'yellow',
			zIndex: 2,
			height: 50,
			width: 50,
			top: 30
		});
		var view4 = Ti.UI.createView({
			backgroundColor: 'green',
			zIndex: 3,
			height: 50,
			width: 50,
			top: 40
		});
		var view5 = Ti.UI.createView({
			backgroundColor: 'blue',
			zIndex: 4,
			height: 50,
			width: 50,
			top: 50
		});
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view1.zIndex).eql(0);
			should(view2.zIndex).eql(1);
			should(view3.zIndex).eql(2);
			should(view4.zIndex).eql(3);
			should(view5.zIndex).eql(4);
		});
		win.add(view5);
		win.add(view4);
		win.add(view3);
		win.add(view2);
		win.add(view1);
		win.open();
	});

	it('fillInVerticalLayout', function (finish) {
		var win = createWindow({}, finish);
		var parent = Ti.UI.createView({
			height: 50,
			width: 40,
			layout: 'vertical'
		});
		var child = Ti.UI.createView({});
		parent.add(child);
		win.add(parent);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(parent.size.width).eql(40);
			should(parent.size.height).eql(50);
			should(child.size.width).eql(40);
			should(child.size.height).eql(50);
		});
		win.open();
	});

	it('sizeFillConflict', function (finish) {
		var win = createWindow({}, finish);
		var grandParent = Ti.UI.createView({
			height: 300,
			width: 200
		});
		var parent = Ti.UI.createView({
			height: Ti.UI.SIZE
		});
		var child1 = Ti.UI.createView({
			height: Ti.UI.SIZE
		});
		var child2 = Ti.UI.createView({
			height: 50
		});
		var child3 = Ti.UI.createView({
			width: 30
		});
		child1.add(child2);
		child1.add(child3);
		parent.add(child1);
		grandParent.add(parent);
		win.add(grandParent);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(grandParent.size.width).eql(200);
			should(grandParent.size.height).eql(300);
			should(parent.size.width).eql(200);
			// should(parent.size.height).eql(300); // TIMOB-18684?
			should(child1.size.width).eql(200);
			// should(child1.size.height).eql(300); // TIMOB-18684?
			should(child2.size.width).eql(200);
			should(child2.size.height).eql(50);
			should(child3.size.width).eql(30);
			should(child3.size.height).eql(300);
		});
		win.open();
	});
	// Functional Test #1000 SystemMeasurement
	it('systemMeasurement', function (finish) {
		var win = createWindow({}, finish);
		var parent = Ti.UI.createView({
			height: '50dip',
			width: '40px',
			layout: 'vertical'
		});
		var child = Ti.UI.createView({});
		parent.add(child);
		win.add(parent);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			if (utilities.isAndroid()) {
				should(parent.size.width).eql(40);
			}
			else if (utilities.isIOS()) {
				should(parent.size.height).eql(50);
			} else {
				should(parent.size.width).eql(40);
			}
		});
		win.open();
	});

	// Functional Test #1001 #1002 #1003 #1004 #1005 #1006
	// Skip on Windows 10 Desktop for now, it hangs
	((utilities.isWindows10() && utilities.isWindowsDesktop()) ? it.skip : it)('unitMeasurements', function (finish) {
		var win = createWindow({}, finish);
		var child = Ti.UI.createView({
			height: '50mm',
			width: '40cm'
		});
		var child1 = Ti.UI.createView({
			height: '1in',
			width: '100px'
		});
		var child2 = Ti.UI.createView({
			height: '50dip',
			width: '40dp'
		});
		var child3 = Ti.UI.createView({
			//inavlid measurement
			height: 'invalid',
			width: 'inavlid'
		});
		win.add(child);
		win.add(child1);
		win.add(child2);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(child.size.width).not.be.eql(0);
			should(child.size.height).not.be.eql(0);
			should(child1.size.width).not.be.eql(0);
			should(child1.size.height).not.be.eql(0);
			should(child2.size.width).not.be.eql(0);
			should(child2.size.height).not.be.eql(0);
			should(child3.size.width).eql(0);
			should(child3.size.height).eql(0);
		});
		win.open();
	});

	// Scrollview
	/*
	it('scrollViewAutoContentHeight', function (finish) {
		var win = Ti.UI.createWindow({}, finish);
		var scrollView = Titanium.UI.createScrollView({
			contentHeight: 'auto',
			contentWidth: 'auto',
			showVerticalScrollIndicator: true,
			showHorizontalScrollIndicator: true
		});
		var view2 = Ti.UI.createView({});
		scrollView.add(view2);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view2.size.width).eql(scrollView.size.width);
			should(view2.size.height).eql(scrollView.size.height);

		});
		win.add(scrollView);
		win.open();
	});

	it('scrollViewLargeContentHeight', function (finish) {
		var win = Ti.UI.createWindow({}, finish);
		var scrollView = Titanium.UI.createScrollView({
			contentHeight: '2000',
			contentWidth: 'auto',
			showVerticalScrollIndicator: true,
			showHorizontalScrollIndicator: true
		});
		var view2 = Ti.UI.createView({});
		scrollView.add(view2);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view2.size.width).eql(scrollView.size.width);
			should(view2.size.height).eql(2e3);

		});
		win.add(scrollView);
		win.open();
	});

	it('scrollViewMinimumContentHeight', function (finish) {
		var win = Ti.UI.createWindow({}, finish);
		var scrollView = Titanium.UI.createScrollView({
			contentHeight: '50',
			contentWidth: 'auto',
			showVerticalScrollIndicator: true,
			showHorizontalScrollIndicator: true
		});
		var view2 = Ti.UI.createView({});
		scrollView.add(view2);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view2.size.width).eql(scrollView.size.width);
			should(view2.size.height).eql(scrollView.size.height);

		});
		win.add(scrollView);
		win.open();
	});

	it('horizontalScrollViewMinimumContentHeight', function (finish) {
		var win = Ti.UI.createWindow({}, finish);
		var scrollView = Titanium.UI.createScrollView({
			contentHeight: 'auto',
			contentWidth: '50',
			showVerticalScrollIndicator: true,
			showHorizontalScrollIndicator: true,
			scrollType: 'horizontal'
		});
		var view2 = Ti.UI.createView({});
		scrollView.add(view2);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view2.size.width).eql(scrollView.size.width);
			should(view2.size.height).eql(scrollView.size.height);

		});
		win.add(scrollView);
		win.open();
	});
	it('horizontalScrollViewLargeContentHeight', function (finish) {
		var win = Ti.UI.createWindow({}, finish);
		var scrollView = Titanium.UI.createScrollView({
			contentHeight: 'auto',
			contentWidth: '50',
			showVerticalScrollIndicator: true,
			showHorizontalScrollIndicator: true,
			scrollType: 'horizontal'
		});
		var view2 = Ti.UI.createView({});
		scrollView.add(view2);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view2.size.width).eql(scrollView.size.width);
			should(view2.size.height).eql(scrollView.size.height);

		});
		win.add(scrollView);
		win.open();
	});
	*/
	//TIMOB-8362
	it('scrollViewWithSIZE', function (finish) {
		var win = createWindow({
			backgroundColor: '#7B6700',
			layout: 'vertical'
		}, finish);
		var NavBarView = Ti.UI.createView({
			height: '25',
			top: 0,
			backgroundColor: 'green',
			width: '100%'
		});
		var scrollView = Ti.UI.createScrollView({
			height: Ti.UI.SIZE,
			width: Ti.UI.SIZE,
			scrollType: 'vertical',
			layout: 'vertical',
			backgroundColor: 'red'
		});
		var button = Ti.UI.createButton({
			title: 'Click',
			width: '100',
			height: '50'
		});
		scrollView.add(button);
		win.add(NavBarView);
		win.add(scrollView);
		scrollView.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(scrollView.size.height).eql(50);
			should(scrollView.size.width).eql(100);
		});
		win.open();
	});

	//TIMOB-20385
	it('scrollViewWithTop', function (finish) {
		var win = createWindow({
			backgroundColor: '#7B6700',
			layout: 'vertical'
		}, finish);
		var NavBarView = Ti.UI.createView({
			height: '25',
			top: 0,
			backgroundColor: 'green',
			width: '100%'
		});
		var scrollView = Ti.UI.createScrollView({
			height: 300,
			width: Ti.UI.FILL,
			scrollType: 'vertical',
			layout: 'vertical',
			backgroundColor: 'red'
		});
		var button = Ti.UI.createButton({
			title: 'Click',
			width: '100',
			height: '50',
			top: 20, left: 40
		});
		scrollView.add(button);
		win.add(NavBarView);
		win.add(scrollView);
		scrollView.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(scrollView.size.height).eql(300);
			should(button.top).eql(20);
			should(button.left).eql(40);
		});
		win.open();
	});

	//TIMOB-8891
	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('scrollViewWithLargeVerticalLayoutChild', function (finish) {
		var win = createWindow({}, finish);
		var scrollView = Ti.UI.createScrollView({
			contentHeight: 'auto',
			backgroundColor: 'green'
		});
		win.add(scrollView);
		var innerView = Ti.UI.createView({
			height: Ti.UI.SIZE,
			// works if set to 1000
			layout: 'vertical',
			left: 0,
			top: 0,
			right: 0
		});
		scrollView.add(innerView);
		var colors = ['red', 'blue', 'pink', 'white', 'black'];
		var max = 10;
		for (var i = 0; max > i; i++) innerView.add(Ti.UI.createView({
			backgroundColor: colors[i % colors.length],
			height: 100,
			top: 20
		}));
		scrollView.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(innerView.size.height).eql(1200);
			should(innerView.size.width).eql(scrollView.size.width);
		});
		win.open();
	});
	/*
	// Functional Test #1087-#1097
	it('convertUnits', function (finish) {
		// android
		var dpi = Ti.Platform.displayCaps.dpi;
		if (utilities.isAndroid()) {
			// 1087
			should(Ti.UI.convertUnits('1in', Ti.UI.UNIT_PX)).eql(dpi);
			should(Ti.UI.convertUnits('100', Ti.UI.UNIT_PX)).eql(100);
			// 1092
			should(Ti.UI.convertUnits('25.4mm', Ti.UI.UNIT_PX)).eql(dpi);
		} else if (utilities.isIOS()) {
			// 1091
			// TODO: This needs to support retina
			should(Ti.UI.convertUnits('1in', Ti.UI.UNIT_DIP)).eql(dpi);
			should(Ti.UI.convertUnits('100', Ti.UI.UNIT_DIP)).eql(100);
			should(Ti.UI.convertUnits('25.4mm', Ti.UI.UNIT_DIP)).eql(dpi);
		}
		// 1088
		should(Math.round(Ti.UI.convertUnits(dpi.toString(), Ti.UI.UNIT_MM))).eql(25);
		// 1089
		should(Math.round(Ti.UI.convertUnits(dpi.toString(), Ti.UI.UNIT_CM))).eql(3);
		// 1088
		should(Math.round(Ti.UI.convertUnits(dpi.toString(), Ti.UI.UNIT_MM))).eql(25);
		// 1089
		should(Math.round(Ti.UI.convertUnits(dpi.toString(), Ti.UI.UNIT_CM))).eql(3);
		// 1090
		should(Math.round(Ti.UI.convertUnits(dpi.toString(), Ti.UI.UNIT_IN))).eql(1);
		// 1093
		should(Ti.UI.convertUnits('100cm', Ti.UI.UNIT_MM)).eql(1e3);
		// 1094
		should(Ti.UI.convertUnits('100in', Ti.UI.UNIT_CM)).eql(254);
		// 1097
		should(Ti.UI.convertUnits('abc', Ti.UI.UNIT_PX)).eql(0);

	});
	*/

	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('twoPins', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			width: 100,
			height: 100
		});
		var inner_view = Ti.UI.createView({
			left: 10,
			right: 10
		});
		view.add(inner_view);
		win.add(view);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(inner_view.size.width).eql(80);
			should(inner_view.rect.width).eql(80);
		});
		win.open();
	});

	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('fourPins', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			width: 100,
			height: 100
		});
		var inner_view = Ti.UI.createView({
			left: 10,
			right: 10,
			top: 10,
			bottom: 10
		});
		view.add(inner_view);
		win.add(view);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(inner_view.size.width).eql(80);
			should(inner_view.size.height).eql(80);
			should(inner_view.left).eql(10);
			should(inner_view.right).eql(10);
			should(inner_view.top).eql(10);
			should(inner_view.bottom).eql(10);
			should(inner_view.rect.x).eql(10);
			should(inner_view.rect.width).eql(80);
			should(inner_view.rect.y).eql(10);
			should(inner_view.rect.height).eql(80);
		});
		win.open();
	});

	// TIMOB-18684
	((utilities.isWindows8_1() && utilities.isWindowsDesktop()) ? it.skip : it)('layoutWithSIZE_and_fixed', function (finish) {
		var win = createWindow({}, finish);
		var view = Ti.UI.createView({
			backgroundColor: 'green',
			width: 100,
			height: Ti.UI.SIZE
		});
		var innerView = Ti.UI.createView({
			backgroundColor: 'blue',
			width: 100,
			height: 50
		});
		view.add(innerView);
		win.addEventListener('postlayout', function (e) {
			if (didPostlayout) return;
			didPostlayout = true;
			should(view.size.height).eql(innerView.size.height);
			should(view.size.width).eql(innerView.size.width);
		});
		win.add(view);
		win.open();
	});

	// TIMOB-23372 #1
	//
	// left/right/top/bottom should just work for child view
	// when both left/right/top/bottom are specified to parent
	//
	it('TIMOB-23372 #1', function (finish) {
		var a = Ti.UI.createView({
			backgroundColor: 'orange',
			top: 10,
			left: 10,
			right: 10,
			bottom: 10,
		}),
		b = Ti.UI.createView({
			backgroundColor: 'yellow',
			top: 10,
			left: 10,
			right: 10,
			bottom: 10,
		});
		var win = createWindow({}, function() {
			var err;
			try {
				should(a.rect.x).eql(10);
				should(a.rect.y).eql(10);
				should(b.rect.x).eql(10);
				should(b.rect.y).eql(10);
				should(b.rect.width).eql(a.rect.width - 20);
				should(b.rect.height).eql(a.rect.height - 20);
			} catch (e) {
				err = e;
			}
			finish(err);
		});
		a.add(b);
		win.add(a);
		win.open();
	});

	// TIMOB-23372 #2
	//
	// left & right should just work for child view (vertical)
	// when both left & right are specified to parent
	//
	(utilities.isWindows10() ? it.skip : it)('TIMOB-23372 #2', function (finish) {
		var view = Ti.UI.createView({
			backgroundColor: 'orange',
			layout: 'vertical',
			top: 10,
			left: 10,
			right: 10,
			height: Ti.UI.SIZE,
			width: Ti.UI.SIZE,
		}),
		label = Ti.UI.createLabel({
			left: 10,
			right: 10,
			color: 'green',
			backgroundColor: 'yellow',
			text: 'this is test text'
		});
		var win = createWindow({}, function() {
			var err;
			try {
				should(view.rect.x).eql(10);
				should(view.rect.y).eql(10);
				should(label.rect.x).eql(10);
				should(label.rect.y).eql(0);
				should(label.rect.width).eql(view.rect.width - 20);
			} catch (e) {
				err = e;
			}
			finish(err);
		});
		view.add(label);
		win.add(view);
		win.open();
	});

	// TIMOB-23372 #3
	//
	// left & right should just work for child view (composite)
	// when both left & right are specified to parent
	//
	(utilities.isWindows10() ? it.skip : it)('TIMOB-23372 #3', function (finish) {
		var view = Ti.UI.createView({
			backgroundColor: 'yellow',
			layout: 'composite',
			top: 10,
			left: 10,
			right: 10,
			height: Ti.UI.SIZE,
			width: Ti.UI.SIZE
		}),
		label = Ti.UI.createLabel({
			left: 10,
			right: 10,
			color: 'blue',
			text: 'this is test text'
		});
		view.add(label);
		var win = createWindow({}, function () {
			var err;
			try {
				should(view.rect.x).eql(10);
				should(view.rect.y).eql(10);
				should(label.rect.x).eql(10);
				should(label.rect.y).eql(0);
				should(label.rect.width).eql(view.rect.width - 20);
			} catch (e) {
				err = e;
			}
			finish(err);
		});
		win.add(view);
		win.open();
	});

	// TIMOB-23372 #4
	//
	// left & right should just work for child view (horizontal)
	// when both left & right are specified to parent
	//
	(utilities.isWindows10() ? it.skip : it)('TIMOB-23372 #4', function (finish) {
		var view = Ti.UI.createView({
			backgroundColor: 'yellow',
			layout: 'horizontal',
			top: 10,
			left: 10,
			right: 10,
			height: Ti.UI.SIZE,
			width: Ti.UI.SIZE
		}),
		label = Ti.UI.createLabel({
			left: 10,
			right: 10,
			color: 'blue',
			text: 'this is test text'
		});
		view.add(label);
		var win = createWindow({}, function() {
			var err;
			try {
				should(view.rect.x).eql(10);
				should(view.rect.y).eql(10);
				should(label.rect.x).eql(10);
				should(label.rect.y).eql(0);
				should(label.rect.width).eql(view.rect.width - 20);
			} catch (e) {
				err = e;
			}
			finish(err);
		});
		win.add(view);
		win.open();
	});

	// TIMOB-23372 #5
	//
	// left & right should just work for label (horizontal)
	// even when parent view doesn't have right value.
	// parent view should fit the size of the child, not Window
	//
	it('TIMOB-23372 #5', function (finish) {
		var view = Ti.UI.createView({
			backgroundColor: 'orange',
			layout: 'horizontal',
			top: 10,
			left: 10,
			height: Ti.UI.SIZE,
			width: Ti.UI.SIZE,
		}),
		label = Ti.UI.createLabel({
			left: 10,
			right: 10,
			color: 'green',
			backgroundColor: 'yellow',
			text: 'this is test text'
		});
		var win = createWindow({}, function() {
			var err;
			try {
				should(view.rect.x).eql(10);
				should(view.rect.y).eql(10);
				should(label.rect.x).eql(10);
				should(label.rect.y).eql(0);
				should(label.rect.width).eql(view.rect.width - 20);
				should(view.rect.width).not.eql(win.rect.width - 20);
			} catch (e) {
				err = e;
			}
			finish(err);
		});
		view.add(label);
		win.add(view);
		win.open();
	});

	// TIMOB-23372 #6
	//
	// left & right should just work for label (vertical)
	// even when parent view doesn't have right value.
	// parent view should fit the size of the child, not Window
	//
	it('TIMOB-23372 #6', function (finish) {
		var view = Ti.UI.createView({
			backgroundColor: 'orange',
			layout: 'vertical',
			top: 10,
			left: 10,
			height: Ti.UI.SIZE,
			width: Ti.UI.SIZE,
		}),
		label = Ti.UI.createLabel({
			left: 10,
			right: 10,
			color: 'green',
			backgroundColor: 'yellow',
			text: 'this is test text'
		});
		var win = createWindow({}, function() {
			var err;
			try {
				should(view.rect.x).eql(10);
				should(view.rect.y).eql(10);
				should(label.rect.x).eql(10);
				should(label.rect.y).eql(0);
				should(label.rect.width).eql(view.rect.width - 20);
				should(view.rect.width).not.eql(win.rect.width - 20);
			} catch (e) {
				err = e;
			}
			finish(err);
		});
		view.add(label);
		win.add(view);
		win.open();
	});

	// TIMOB-23372 #7
	//
	// left & right should just work for label (composite)
	// even when parent view doesn't have right value.
	// parent view should fit the size of the child, not Window
	//
	it('TIMOB-23372 #7', function (finish) {
		var view = Ti.UI.createView({
			backgroundColor: 'orange',
			layout: 'composite',
			top: 10,
			left: 10,
			height: Ti.UI.SIZE,
			width: Ti.UI.SIZE,
		}),
		label = Ti.UI.createLabel({
			left: 10,
			right: 10,
			color: 'green',
			backgroundColor: 'yellow',
			text: 'this is test text'
		});
		var win = createWindow({}, function() {
			var err;
			try {
				should(view.rect.x).eql(10);
				should(view.rect.y).eql(10);
				should(label.rect.x).eql(10);
				should(label.rect.y).eql(0);
				should(label.rect.width).eql(view.rect.width - 20);
				should(view.rect.width).not.eql(win.rect.width - 20);
			} catch (e) {
				err = e;
			}
			finish(err);
		});
		view.add(label);
		win.add(view);
		win.open();
	});

	// TIMOB-23372 #8
	//
	// left & right should just work for child view when parent is Window (composite)
	//
	(utilities.isWindows10() ? it.skip : it)('TIMOB-23372 #8', function (finish) {
		var label = Ti.UI.createLabel({
			left: 10,
			right: 10,
			backgroundColor:'yellow',
			color: 'green',
			text: 'this is test text'
		});
		var win = createWindow({layout:'composite'}, function() {
			var err;
			try {
				should(label.rect.x).eql(10);
				should(label.rect.width).eql(win.rect.width - 20);
			} catch (e) {
				err = e;
			}
			finish(err);
		});
		win.add(label);
		win.open();
	});

	// TIMOB-23372 #9
	//
	// left & right should just work for child view when parent is Window (horizontal)
	//
	(utilities.isWindows10() ? it.skip : it)('TIMOB-23372 #9', function (finish) {
		var label = Ti.UI.createLabel({
			left: 10,
			right: 10,
			backgroundColor:'yellow',
			color: 'green',
			text: 'this is test text'
		});
		var win = createWindow({layout:'horizontal'}, function() {
			var err;
			try {
				should(label.rect.x).eql(10);
				should(label.rect.width).eql(win.rect.width - 20);
			} catch (e) {
				err = e;
			}
			finish(err);
		});
		win.add(label);
		win.open();
	});

	// TIMOB-23372 #10
	//
	// left & right should just work for child view when parent is Window (vertical)
	//
	(utilities.isWindows10() ? it.skip : it)('TIMOB-23372 #10', function (finish) {
		var label = Ti.UI.createLabel({
			left: 10,
			right: 10,
			backgroundColor:'yellow',
			color: 'green',
			text: 'this is test text'
		});
		var win = createWindow({layout:'vertical'}, function() {
			var err;
			try {
				should(label.rect.x).eql(10);
				should(label.rect.width).eql(win.rect.width - 20);
			} catch (e) {
				err = e;
			}
			finish(err);
		});
		win.add(label);
		win.open();
	});

	// TIMOB-23305
	//
	// Label width should be updated when setting new text
	it('TIMOB-23305', function (finish) {
		var label = Ti.UI.createLabel({
			text: 'Lorem ipsum dolor sit amet',
			backgroundColor: 'orange',
		});
		var savedRect = {};
		var err;
		var win = createWindow({}, function () {
			try {
				should(label.rect.width).not.eql(0);
				should(label.rect.height).not.eql(0);
				should(label.rect.width).greaterThan(savedRect.width);
				if (utilities.isWindowsPhone()) {
					should(label.rect.height).greaterThan(savedRect.height);
				}
			} catch (e) {
				err = e;
			}
			finish(err);
		});
		label.addEventListener('postlayout', function () {
			if (didPostlayout) return;
			didPostlayout = true;
			try {
				savedRect = label.rect;
				should(label.rect.width).not.eql(0);
				should(label.rect.height).not.eql(0);
				label.text = 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut mollis rutrum dignissim.';
			} catch (e) {
				err = e;
			}
		});
		win.add(label);
		win.open();
	});

		// TIMOB-23225
	it('TIMOB-23225', function (finish) {
			var parent = Ti.UI.createView({
					height: Ti.UI.SIZE,
					width: Ti.UI.SIZE,
					backgroundColor: 'orange'
			});

			var v1 = Ti.UI.createView({
					height: 100, width: Ti.UI.FILL,
					backgroundColor: 'gray',
			});
			var v2 = Ti.UI.createImageView({
					height: 50, width: 50,
					top: 0, right: 0,
					backgroundColor: 'red',
			});
			var win = createWindow({}, finish);
			win.addEventListener('open', function () {
					setTimeout(function () {
						var err;
						try {
							should(v1.rect.x).eql(0);
							should(v1.rect.y).eql(0);
							should(v1.rect.width).eql(parent.rect.width);
							should(v1.rect.height).eql(parent.rect.height);
							should(v2.rect.x).eql(parent.rect.width - v2.rect.width);
							should(v2.rect.y).eql(0);
							should(v2.rect.width).eql(50);
							should(v2.rect.width).eql(50);
						} catch (e) {
							err = e;
						}
						finish(err);
					}, 2000);
			});
			parent.add(v1);
			parent.add(v2);
			win.add(parent);
			win.open();
	});

	it('TIMOB-24825', function (finish) {
	    var main = Ti.UI.createView({
	        top: 0,
	        left: 0,
	        width: 200,
	        height: 200
	    });
	    var view = Ti.UI.createView({
	        width: 20, height: 20
	    });

	    view.center = { x:'50%', y:'50%' };

	    var win = createWindow({}, function () {
	        var err;
	        try {
	            should(view.rect.x).eql((main.rect.width / 2.0)  - (view.rect.width / 2.0));
	            should(view.rect.y).eql((main.rect.height / 2.0) - (view.rect.height / 2.0));
            } catch (e) {
	            err = e;
	        }
	        finish(err);
	    });
	    main.add(view);
	    win.add(main);
	    win.open();
	});


});
