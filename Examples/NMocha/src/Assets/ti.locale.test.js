/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities');

describe('Titanium.Locale', function () {
	it('apiName', function () {
		should(Ti.Locale).have.a.readOnlyProperty('apiName').which.is.a.String;
		should(Ti.Locale.apiName).be.eql('Ti.Locale');
	});

	it('Ti.Locale', function () {
		should(Ti.Locale).not.be.undefined;
		should(Ti.Locale).not.be.null;
		should(Ti.Locale).be.an.Object;
	});

	it('Ti.Locale.getString', function () {
		should(Ti.Locale.getString).be.a.Function;
	});

	it('L', function () {
		should(L).be.a.Function;
		// should(L).eql(Ti.Locale.getString);
	});

	it('Ti.Locale.getCurrentCountry', function () {
		should(Ti.Locale.getCurrentCountry).be.a.Function;
		should(Ti.Locale.getCurrentCountry()).eql('US');
	});

	it('Ti.Locale.getCurrentLanguage', function () {
		should(Ti.Locale.getCurrentLanguage).be.a.Function;
		should(Ti.Locale.getCurrentLanguage()).eql('en');
	});

	it('Ti.Locale.getLocaleCurrencySymbol', function () {
		should(Ti.Locale.getLocaleCurrencySymbol).be.a.Function;
		should(Ti.Locale.getLocaleCurrencySymbol('en-US')).eql('$');
	});

	// FIXME Get working on iOS
	// FIXME Get working properly cross-platform. JPY gives us ¥ on Windows and Android, JP¥ on iOS. CNY gives us ¥ on Windows, CN¥ on Android
	((utilities.isIOS() || utilities.isAndroid()) ? it.skip : it)('Ti.Locale.getCurrencySymbol', function () {
		should(Ti.Locale.getCurrencySymbol).be.a.Function;
		should(Ti.Locale.getCurrencySymbol('USD')).eql('$');
		should(Ti.Locale.getCurrencySymbol('JPY')).eql('¥'); // 'JP¥' on iOS
		should(Ti.Locale.getCurrencySymbol('CNY')).eql('¥'); // 'CN¥' on Android
		should(Ti.Locale.getCurrencySymbol('TWD')).eql('NT$');
	});

	it('Ti.Locale.getCurrencyCode', function () {
		should(Ti.Locale.getCurrencyCode).be.a.Function;
		should(Ti.Locale.getCurrencyCode('en-US')).eql('USD');
		should(Ti.Locale.getCurrencyCode('ja-JP')).eql('JPY');
		should(Ti.Locale.getCurrencyCode('zh-CN')).eql('CNY');
		should(Ti.Locale.getCurrencyCode('zh-TW')).eql('TWD');
	});

	// Intentionally skipping, as available only on Android
	(utilities.isIOS() ? it.skip : it)('Ti.Locale.formatTelephoneNumber', function () {
		should(Ti.Locale.formatTelephoneNumber).be.a.Function;
	});

	it('Ti.Locale.currentCountry', function () {
		should(Ti.Locale.currentCountry).be.a.String;
		should(Ti.Locale.currentCountry).eql('US');
	});

	it('Ti.Locale.currentLanguage', function () {
		should(Ti.Locale.currentLanguage).be.a.String;
		should(Ti.Locale.currentLanguage).eql('en');
	});

	it('Ti.Locale.currentLocale', function () {
		should(Ti.Locale.currentLocale).be.a.String;
		should(Ti.Locale.currentLocale).eql('en-US');
	});

	it.skip('Ti.Locale.getString_format', function () {
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
	});

	// FIXME Get working on iOS, setLangauge doesn't seem to affect currentLocale
	(utilities.isIOS() ? it.skip : it)('Ti.Locale.setLanguage', function () {
		should(Ti.Locale.setLanguage).be.a.Function;
		Ti.Locale.setLanguage('en-GB');
		should(Ti.Locale.currentLocale).eql('en-GB'); // iOS returns 'en-US'
		should(Ti.Locale.currentLanguage).eql('en');
		// TODO Should the currentCountry become 'GB'? Or stay 'US'?
		Ti.Locale.setLanguage('fr');
		should(Ti.Locale.currentLocale).eql('fr');
		should(Ti.Locale.currentLanguage).eql('fr');
	});
});
