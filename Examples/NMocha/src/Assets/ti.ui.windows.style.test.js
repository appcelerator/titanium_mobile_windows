/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2017 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

if (utilities.isWindows()) {
	describe('Titanium.UI.Windows.Style', function () {
		it('constructor', function (finish) {
			should(Ti.UI.Windows).not.be.undefined;
			should(Ti.UI.Windows.createStyle).be.a.Function;

			finish();
		});

		it('Style', function (finish) {
			var style = Ti.UI.Windows.createStyle();
			should(style).be.an.Object;
			should(style.apiName).be.eql('Ti.UI.Windows.Style');
			should(style.apply).be.a.Function;

			finish();
		});

		it('Style(source)', function (finish) {
			var source = 'ms-appx:///Styles.xaml';
			var style = Ti.UI.Windows.createStyle({source:source});
			should(style).be.an.Object;
			should(style.source).eql(source);

			finish();
		});

		it('apply(component)', function (finish) {
			var style  = Ti.UI.Windows.createStyle();
			var button = Ti.UI.createButton();

			style.apply(button);

			finish();
		});

		it('apply(component, style)', function (finish) {
			var style  = Ti.UI.Windows.createStyle();
			var button = Ti.UI.createButton();

			style.apply(button, 'ButtonStyle');

			finish();
		});

	});
}
