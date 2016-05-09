/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./should');

describe('Titanium.Locale', function () {
    it('Ti.Locale', function (finish) {
        should(Ti.Locale).not.be.undefined;
        should(Ti.Locale).not.be.null;
        should(Ti.Locale).be.an.Object;
        should(Ti.Locale.apiName).be.eql("Titanium.Locale");
        finish();
    });

    it('Ti.Locale.getString', function (finish) {
        should(Ti.Locale.getString).be.a.Function;
        finish();
    });

    it('L', function (finish) {
        should(L).be.a.Function;
        should(L).eql(Ti.Locale.getString);
        finish();
    });

    it('Ti.Locale.getCurrentCountry', function (finish) {
        should(Ti.Locale.getCurrentCountry).be.a.Function;
        should(Ti.Locale.getCurrentCountry()).eql('US');
        finish();
    });

    it('Ti.Locale.getCurrentLanguage', function (finish) {
        should(Ti.Locale.getCurrentLanguage).be.a.Function;
        should(Ti.Locale.getCurrentLanguage()).eql('en');
        finish();
    });

    it('Ti.Locale.getLocaleCurrencySymbol', function (finish) {
        should(Ti.Locale.getLocaleCurrencySymbol).be.a.Function;
        should(Ti.Locale.getLocaleCurrencySymbol('en-US')).eql('$');
        finish();
    });

    it('Ti.Locale.getCurrencySymbol', function (finish) {
        should(Ti.Locale.getCurrencySymbol).be.a.Function;
        should(Ti.Locale.getCurrencySymbol('USD')).eql('$');
        should(Ti.Locale.getCurrencySymbol('JPY')).eql('¥');
        should(Ti.Locale.getCurrencySymbol('CNY')).eql('¥');
        should(Ti.Locale.getCurrencySymbol('TWD')).eql('NT$');
        finish();
    });

    it('Ti.Locale.getCurrencyCode', function (finish) {
        should(Ti.Locale.getCurrencyCode).be.a.Function;
        should(Ti.Locale.getCurrencyCode('en-US')).eql('USD');
        should(Ti.Locale.getCurrencyCode('ja-JP')).eql('JPY');
        should(Ti.Locale.getCurrencyCode('zh-CN')).eql('CNY');
        should(Ti.Locale.getCurrencyCode('zh-TW')).eql('TWD');

        finish();
    });

    it('Ti.Locale.formatTelephoneNumber', function (finish) {
        should(Ti.Locale.formatTelephoneNumber).be.a.Function;
        finish();
    });

    it('Ti.Locale.currentCountry', function (finish) {
        should(Ti.Locale.currentCountry).be.a.String;
        should(Ti.Locale.currentCountry).eql('US');
        finish();
    });

    it('Ti.Locale.currentLanguage', function (finish) {
        should(Ti.Locale.currentLanguage).be.a.String;
        should(Ti.Locale.currentLanguage).eql('en');
        finish();
    });

    it('Ti.Locale.currentLocale', function (finish) {
        should(Ti.Locale.currentLocale).be.a.String;
        should(Ti.Locale.currentLocale).eql('en-US');
        finish();
    });

    it.skip('Ti.Locale.getString_format', function (finish) {
        var i18nMissingMsg = '<no translation available>';
        var string1 = 'You say ' + Ti.Locale.getString('signoff', i18nMissingMsg) + ' and I say ' + Ti.Locale.getString('greeting', i18nMissingMsg) + '!';
        var string2 = String.format(L('phrase'), L('greeting', i18nMissingMsg), L('signoff', i18nMissingMsg));

        if (Ti.Locale.currentLanguage == 'en') {
            should(string1).eql('You say goodbye and I say hello!');
            should(string2).eql('You say goodbye and I say hello!');
        } else if (Ti.Locale.currentLanguage == 'ja') {
            should(string1).eql('You say さようなら and I say こんにちは!');
            should(string2).eql('You say さようなら and I say こんにちは!');
        }

        finish();
    });

	it('Ti.Locale.setLanguage', function (finish) {
        should(Ti.Locale.setLanguage).be.a.Function;
        Ti.Locale.setLanguage('en-GB');
        should(Ti.Locale.currentLocale).eql('en-GB');
        should(Ti.Locale.currentLanguage).eql('en');
        // TODO Should the currentCountry become 'GB'? Or stay 'US'?
        Ti.Locale.setLanguage('fr');
        should(Ti.Locale.currentLocale).eql('fr');
        should(Ti.Locale.currentLanguage).eql('fr');
        finish();
    });
});
