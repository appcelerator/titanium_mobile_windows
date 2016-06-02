/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should'),
	utilities = require('./utilities/utilities');

describe('Titanium.UI.EmailDialog', function () {
	it('apiName', function (finish) {
		should(Ti.UI.EmailDialog.apiName).be.eql('Ti.UI.EmailDialog');
		finish();
	});

	// Check if FAILED exists and make sure it does not throw exception
	it('FAILED', function (finish) {
		should(function () {
			should(Ti.UI.EmailDialog.FAILED).not.be.undefined;
			should(Ti.UI.EmailDialog.FAILED).be.a.Number;
			// make sure it is read-only value
			var value = Ti.UI.EmailDialog.FAILED;
			Ti.UI.EmailDialog.FAILED = 'try_to_overwrite_READONLY_value';
			should(Ti.UI.EmailDialog.FAILED).be.eql(value);
		}).not.throw();
		finish();
	});
	// Check if SENT exists and make sure it does not throw exception
	it('SENT', function (finish) {
		should(function () {
			should(Ti.UI.EmailDialog.SENT).not.be.undefined;
			should(Ti.UI.EmailDialog.SENT).be.a.Number;
			// make sure it is read-only value
			var value = Ti.UI.EmailDialog.SENT;
			Ti.UI.EmailDialog.SENT = 'try_to_overwrite_READONLY_value';
			should(Ti.UI.EmailDialog.SENT).be.eql(value);
		}).not.throw();
		finish();
	});
	// Check if SAVED exists and make sure it does not throw exception
	it('SAVED', function (finish) {
		should(function () {
			should(Ti.UI.EmailDialog.SAVED).not.be.undefined;
			should(Ti.UI.EmailDialog.SAVED).be.a.Number;
			// make sure it is read-only value
			var value = Ti.UI.EmailDialog.SAVED;
			Ti.UI.EmailDialog.SAVED = 'try_to_overwrite_READONLY_value';
			should(Ti.UI.EmailDialog.SAVED).be.eql(value);
		}).not.throw();
		finish();
	});
	// Check if CANCELLED exists and make sure it does not throw exception
	it('CANCELLED', function (finish) {
		should(function () {
			should(Ti.UI.EmailDialog.CANCELLED).not.be.undefined;
			should(Ti.UI.EmailDialog.CANCELLED).be.a.Number;
			// make sure it is read-only value
			var value = Ti.UI.EmailDialog.CANCELLED;
			Ti.UI.EmailDialog.CANCELLED = 'try_to_overwrite_READONLY_value';
			should(Ti.UI.EmailDialog.CANCELLED).be.eql(value);
		}).not.throw();
		finish();
	});
	it('subject', function (finish) {
		// EmailDialog does not support Windows Store app
		if (utilities.isWindowsDesktop()) {
			return finish();
		}
		var email = Ti.UI.createEmailDialog({
			subject: 'this is some text'
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

	it('messageBody', function (finish) {
		// EmailDialog does not support Windows Store app
		if (utilities.isWindowsDesktop()) {
			return finish();
		}
		var email = Ti.UI.createEmailDialog({
			messageBody: 'this is some text'
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

	it('toRecipients', function (finish) {
		// EmailDialog does not support Windows Store app
		if (utilities.isWindowsDesktop()) {
			return finish();
		}
		var email = Ti.UI.createEmailDialog({
			toRecipients: ['me@example.com']
		});
		should(email.toRecipients).be.a.Array;
		should(email.getToRecipients).be.a.Function;
		should(email.toRecipients).eql(['me@example.com']);
		should(email.getToRecipients()).eql(['me@example.com']);
		email.toRecipients = ['other@example.com'];
		should(email.toRecipients).eql(['other@example.com']);
		should(email.getToRecipients()).eql(['other@example.com']);
		finish();
	});

	it('ccRecipients', function (finish) {
		// EmailDialog does not support Windows Store app
		if (utilities.isWindowsDesktop()) {
			return finish();
		}
		var email = Ti.UI.createEmailDialog({
			ccRecipients: ['me@example.com']
		});
		should(email.ccRecipients).be.a.Array;
		should(email.getCcRecipients).be.a.Function;
		should(email.ccRecipients).eql(['me@example.com']);
		should(email.getCcRecipients()).eql(['me@example.com']);
		email.ccRecipients = ['other@example.com'];
		should(email.ccRecipients).eql(['other@example.com']);
		should(email.getCcRecipients()).eql(['other@example.com']);
		finish();
	});

	it('bccRecipients', function (finish) {
		// EmailDialog does not support Windows Store app
		if (utilities.isWindowsDesktop()) {
			return finish();
		}
		var email = Ti.UI.createEmailDialog({
			bccRecipients: ['me@example.com']
		});
		should(email.bccRecipients).be.a.Array;
		should(email.getBccRecipients).be.a.Function;
		should(email.bccRecipients).eql(['me@example.com']);
		should(email.getBccRecipients()).eql(['me@example.com']);
		email.bccRecipients = ['other@example.com'];
		should(email.bccRecipients).eql(['other@example.com']);
		should(email.getBccRecipients()).eql(['other@example.com']);
		finish();
	});
});
