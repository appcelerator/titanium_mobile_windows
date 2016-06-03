/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.UI.OptionDialog', function () {

	it('apiName', function (finish) {
		should(Ti.UI.OptionDialog.apiName).be.eql('Ti.UI.OptionDialog');
		finish();
	});

	it('title', function (finish) {
		var bar = Ti.UI.createOptionDialog({
			title: 'this is some text'
		});
		should(bar.title).be.a.String;
		should(bar.getTitle).be.a.Function;
		should(bar.title).eql('this is some text');
		should(bar.getTitle()).eql('this is some text');
		bar.title = 'other text';
		should(bar.title).eql('other text');
		should(bar.getTitle()).eql('other text');
		finish();
	});

    it("titleid", function (finish) {
        var bar = Ti.UI.createOptionDialog({
            titleid: "this is my key"
        });
        should(bar.titleid).be.a.String;
        should(bar.getTitleid).be.a.Function;
        should(bar.titleid).eql('this is my key');
        should(bar.getTitleid()).eql('this is my key');
        should(bar.title).eql('this is my value');
        bar.titleid = 'other text';
        should(bar.titleid).eql('other text');
        should(bar.getTitleid()).eql('other text');
        should(bar.title).eql('other text'); // key is used when no resources found
        finish();
    });

	it('buttonNames', function (finish) {
		var bar = Ti.UI.createOptionDialog({
		});
		should(bar.buttonNames).be.an.Array;
		should(bar.getButtonNames).be.a.Function;
		should(bar.buttonNames).be.empty;
		should(bar.getButtonNames()).be.empty;
		bar.buttonNames = ['this','other'];
		should(bar.buttonNames.length).eql(2);
		should(bar.getButtonNames().length).eql(2);
		finish();
	});

	it('options', function (finish) {
		var bar = Ti.UI.createOptionDialog({
		});
		should(bar.options).be.an.Array;
		should(bar.getOptions).be.a.Function;
		should(bar.options).be.empty;
		should(bar.getOptions()).be.empty;
		bar.options = ['this','other'];
		should(bar.options.length).eql(2);
		should(bar.getOptions().length).eql(2);
		finish();
	});

	it('cancel', function (finish) {
		var bar = Ti.UI.createOptionDialog({
		});
		should(bar.cancel).be.a.Number;
		should(bar.getCancel).be.a.Function;
		bar.cancel = 1;
		should(bar.cancel).eql(1);
		should(bar.getCancel()).eql(1);
		finish();
	});


	it('persistent', function (finish) {
		var bar = Ti.UI.createOptionDialog({
		});
		should(bar.persistent).be.a.Boolean;
		should(bar.getPersistent).be.a.Function;
		should(bar.persistent).be.true;
		should(bar.getPersistent()).be.true;
		bar.persistent = false;
		should(bar.persistent).be.false;
		should(bar.getPersistent()).be.false;
		finish();
	});

	it('selectedIndex', function (finish) {
		var bar = Ti.UI.createOptionDialog({
		});
		should(bar.selectedIndex).be.a.Number;
		should(bar.getSelectedIndex).be.a.Function;
		should(bar.selectedIndex).eql(0);
		should(bar.getSelectedIndex()).eql(0);
		bar.selectedIndex = 1;
		should(bar.selectedIndex).eql(1);
		should(bar.getSelectedIndex()).eql(1);
		finish();
	});
});
