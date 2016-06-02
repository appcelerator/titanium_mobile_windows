/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.UI.ScrollableView', function () {

	it('apiName', function (finish) {
		should(Ti.UI.ScrollableView.apiName).be.eql('Ti.UI.ScrollableView');
		finish();
	});

	it('views', function (finish) {
		var bar = Ti.UI.createScrollableView({

		});
		should(bar.views).be.an.Array;
		should(bar.getViews).be.a.Function;
		should(bar.views).be.empty;
		should(bar.getViews()).be.empty;
		bar.views = [Ti.UI.createView(), Ti.UI.createView()];
		should(bar.views.length).eql(2);
		should(bar.getViews().length).eql(2);
		finish();
	});
	it('currentPage', function (finish) {
		var bar = Ti.UI.createScrollableView({

		});
		should(bar.currentPage).be.a.Number;
		should(bar.getCurrentPage).be.a.Function;
		should(bar.currentPage).eql(0);
		should(bar.getCurrentPage()).eql(0);
		bar.views = [Ti.UI.createView(), Ti.UI.createView()];
		bar.currentPage = 1;
		should(bar.currentPage).eql(1);
		should(bar.getCurrentPage()).eql(1);
		finish();
	});
	it('moveNext', function (finish) {
		var bar = Ti.UI.createScrollableView({

		});
		should(bar.moveNext).be.a.Function;
		bar.views = [Ti.UI.createView(), Ti.UI.createView()];
		bar.moveNext();
		should(bar.currentPage).eql(1);
		should(bar.getCurrentPage()).eql(1);
		finish();
	});
	it('movePrevious', function (finish) {
		var bar = Ti.UI.createScrollableView({

		});
		should(bar.movePrevious).be.a.Function;
		bar.views = [Ti.UI.createView(), Ti.UI.createView()];
		bar.moveNext();
		should(bar.currentPage).eql(1);
		should(bar.getCurrentPage()).eql(1);
		bar.movePrevious();
		should(bar.currentPage).eql(0);
		should(bar.getCurrentPage()).eql(0);
		finish();
	});
});
