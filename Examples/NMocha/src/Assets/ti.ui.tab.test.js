/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

require('ti-mocha');
var should = require('should'),
    didFocus = false;

describe("Titanium.UI.Tab", function () {

    beforeEach(function() {
        didFocus = false;
    });

    it("apiName", function (finish) {
        var tab = Ti.UI.createTab({
            text: "this is some text"
        });
        should(tab.apiName).be.a.String;
        should(tab.apiName).be.eql("Ti.UI.Tab");
        finish();
    });

    it("title", function (finish) {
        var tab = Ti.UI.createTab({
            title: "this is some text"
        });
        should(tab.title).be.a.String;
        should(tab.getTitle).be.a.Function;
        should(tab.title).eql('this is some text');
        should(tab.getTitle()).eql('this is some text');
        tab.title = 'other text';
        should(tab.title).eql('other text');
        should(tab.getTitle()).eql('other text');
        finish();
    });

    it("titleid", function (finish) {
        var bar = Ti.UI.createTab({
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

});
