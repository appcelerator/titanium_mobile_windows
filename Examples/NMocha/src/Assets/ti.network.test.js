/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities');

describe('Titanium.Network', function () {

	// Constants
	var NETWORK_TYPES = ['NETWORK_LAN', 'NETWORK_MOBILE', 'NETWORK_NONE', 'NETWORK_UNKNOWN', 'NETWORK_WIFI'],
		NOTIFICATION_TYPES = ['NOTIFICATION_TYPE_ALERT', 'NOTIFICATION_TYPE_BADGE', 'NOTIFICATION_TYPE_NEWSSTAND', 'NOTIFICATION_TYPE_SOUND'],
		TLS_VERSIONS = ['TLS_VERSION_1_0', 'TLS_VERSION_1_1', 'TLS_VERSION_1_2'],
		i;
	// TODO Test that each group has unique values!
	for (i = 0; i < NETWORK_TYPES.length; i++) {
		it(NETWORK_TYPES[i], function () {
			should(Ti.Network).have.constant(NETWORK_TYPES[i]).which.is.a.Number;
		});
	}
	for (i = 0; i < NOTIFICATION_TYPES.length; i++) {
		// Intentionally skip on Android, iOS-specific property
		(utilities.isAndroid() ? it.skip : it)(NOTIFICATION_TYPES[i], function () {
			should(Ti.Network).have.constant(NOTIFICATION_TYPES[i]).which.is.a.Number;
		});
	}
	for (i = 0; i < TLS_VERSIONS.length; i++) {
		// FIXME Fails on Android and iOS for some reason! They say they're undefined, not Number
		((utilities.isAndroid() || utilities.isIOS()) ? it.skip : it)(TLS_VERSIONS[i], function () {
			should(Ti.Network).have.constant(TLS_VERSIONS[i]).which.is.a.Number;
		});
	}

	it('PROGRESS_UNKNOWN', function () {
		should(Ti.Network).have.constant('PROGRESS_UNKNOWN').which.is.a.Number;
	});

	// Properties
	it('apiName', function () {
		should(Titanium.Network).have.a.readOnlyProperty('apiName').which.is.a.String;
		should(Ti.Network.apiName).be.eql('Ti.Network');
	});

	it('networkType', function () {
		should(Ti.Network).have.a.readOnlyProperty('networkType').which.is.a.Number;
		// Has to be one of the defined constants
		should([Ti.Network.NETWORK_LAN,
			Ti.Network.NETWORK_MOBILE,
			Ti.Network.NETWORK_NONE,
			Ti.Network.NETWORK_UNKNOWN,
			Ti.Network.NETWORK_WIFI].indexOf(Ti.Network.networkType)).not.eql(-1);
	});

	it('networkTypeName', function () {
		should(Ti.Network).have.a.readOnlyProperty('networkTypeName').which.is.a.String;
		if (Ti.Network.networkType == Ti.Network.NETWORK_LAN) {
			Ti.Network.networkTypeName.should.eql('LAN');
		} else if (Ti.Network.networkType == Ti.Network.NETWORK_MOBILE) {
			Ti.Network.networkTypeName.should.eql('MOBILE');
		} else if (Ti.Network.networkType == Ti.Network.NETWORK_NONE) {
			Ti.Network.networkTypeName.should.eql('NONE');
		} else if (Ti.Network.networkType == Ti.Network.NETWORK_UNKNOWN) {
			Ti.Network.networkTypeName.should.eql('UNKNOWN');
		} else if (Ti.Network.networkType == Ti.Network.NETWORK_WIFI) {
			Ti.Network.networkTypeName.should.eql('WIFI');
		}
	});

	it('online', function () {
		should(Ti.Network).have.a.readOnlyProperty('online').which.is.a.Boolean;
	});

	// Methods
	it('encodeURIComponent()', function () {
		should(Ti.Network.encodeURIComponent).be.a.Function;
		var text = Ti.Network.encodeURIComponent('Look what I found! I like this:');
		// TODO Open a JIRA ticket for parity! iOS encodes exclamation points, Windows/Android do not
		if (utilities.isIOS()) {
			text.should.eql('Look%20what%20I%20found%21%20I%20like%20this%3A')
		} else {
			text.should.eql('Look%20what%20I%20found!%20I%20like%20this%3A');
		}
	});

	it('decodeURIComponent()', function () {
		should(Ti.Network.decodeURIComponent).be.a.Function;
		var text = Ti.Network.decodeURIComponent('Look%20what%20I%20found!%20I%20like%20this%3A');
		text.should.eql('Look what I found! I like this:');
	});

	it('createHTTPClient()', function () {
		should(Ti.Network.createHTTPClient).be.a.Function;
	});
});
