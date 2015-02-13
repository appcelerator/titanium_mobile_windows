
/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe("ui_activityindicator", function () {
    it("activityindicator_text", function (finish) {
        var activityIndicator = Ti.UI.createActivityIndicator({
            message: "this is some text"
        });
        should(activityIndicator.message).be.a.String;
        should(activityIndicator.getMessage).be.a.Function;
        should(activityIndicator.message).eql('this is some text');
        should(activityIndicator.getMessage()).eql('this is some text');
        activityIndicator.message = 'other text';
        should(activityIndicator.message).eql('other text');
        should(activityIndicator.getMessage()).eql('other text');
        finish();
    });
});
