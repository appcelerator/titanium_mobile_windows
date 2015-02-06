
/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe("ui_emaildialog", function () {
    it("emaildialog_subject", function (finish) {
        // EmailDialog does not support Windows Store app
        if (Ti.Platform.osname == 'windowsstore') {
            return finish();
        }
        var email = Ti.UI.createEmailDialog({
            subject: "this is some text"
        });
        should(email.subject).be.a.String;
        should(email.getSubject).be.a.Function;
        should(email.subject).eql('this is some text');
        should(email.getSubject()).eql('this is some text');
        email.subject = 'other text';
        should(email.subject).eql('other text');
        should(email.getSubject()).eql('other text');
        finish();
    });

    it("emaildialog_messageBody", function (finish) {
        // EmailDialog does not support Windows Store app
        if (Ti.Platform.osname == 'windowsstore') {
            return finish();
        }
        var email = Ti.UI.createEmailDialog({
            messageBody: "this is some text"
        });
        should(email.messageBody).be.a.String;
        should(email.getMessageBody).be.a.Function;
        should(email.messageBody).eql('this is some text');
        should(email.getMessageBody()).eql('this is some text');
        email.messageBody = 'other text';
        should(email.messageBody).eql('other text');
        should(email.getMessageBody()).eql('other text');
        finish();
    });

    it("emaildialog_toRecipients", function (finish) {
        // EmailDialog does not support Windows Store app
        if (Ti.Platform.osname == 'windowsstore') {
            return finish();
        }
        var email = Ti.UI.createEmailDialog({
            toRecipients: ["me@example.com"]
        });
        should(email.toRecipients).be.a.Array;
        should(email.getToRecipients).be.a.Function;
        should(email.toRecipients).eql(["me@example.com"]);
        should(email.getToRecipients()).eql(["me@example.com"]);
        email.toRecipients = ['other@example.com'];
        should(email.toRecipients).eql(['other@example.com']);
        should(email.getToRecipients()).eql(['other@example.com']);
        finish();
    });

    it("emaildialog_ccRecipients", function (finish) {
        // EmailDialog does not support Windows Store app
        if (Ti.Platform.osname == 'windowsstore') {
            return finish();
        }
        var email = Ti.UI.createEmailDialog({
            ccRecipients: ["me@example.com"]
        });
        should(email.ccRecipients).be.a.Array;
        should(email.getCcRecipients).be.a.Function;
        should(email.ccRecipients).eql(["me@example.com"]);
        should(email.getCcRecipients()).eql(["me@example.com"]);
        email.ccRecipients = ['other@example.com'];
        should(email.ccRecipients).eql(['other@example.com']);
        should(email.getCcRecipients()).eql(['other@example.com']);
        finish();
    });

    it("emaildialog_bccRecipients", function (finish) {
        // EmailDialog does not support Windows Store app
        if (Ti.Platform.osname == 'windowsstore') {
            return finish();
        }
        var email = Ti.UI.createEmailDialog({
            bccRecipients: ["me@example.com"]
        });
        should(email.bccRecipients).be.a.Array;
        should(email.getBccRecipients).be.a.Function;
        should(email.bccRecipients).eql(["me@example.com"]);
        should(email.getBccRecipients()).eql(["me@example.com"]);
        email.bccRecipients = ['other@example.com'];
        should(email.bccRecipients).eql(['other@example.com']);
        should(email.getBccRecipients()).eql(['other@example.com']);
        finish();
    });
});
