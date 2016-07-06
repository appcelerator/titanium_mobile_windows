/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var should = require('./utilities/assertions'),
	utilities = require('./utilities/utilities');

describe('Titanium.UI.Switch', function () {
	it('Ti.UI.Switch', function () {
		should(Ti.UI.Switch).not.be.undefined;
	});

	it('apiName', function () {
		var switch_ctrl = Ti.UI.createSwitch();
		should(switch_ctrl).have.readOnlyProperty('apiName').which.is.a.String;
		should(switch_ctrl.apiName).be.eql('Ti.UI.Switch');
	});

	it('createSwitch', function () {
		should(Ti.UI.createSwitch).not.be.undefined;
		should(Ti.UI.createSwitch).be.a.Function;

		// Create switch
		var switch_ctrl = Ti.UI.createSwitch({value : true});
		should(switch_ctrl).be.a.Object;
		should(switch_ctrl.apiName).be.a.String;
		should(switch_ctrl.apiName).be.eql('Ti.UI.Switch');

		// Validate switch value
		Ti.API.info('Switch value : '+switch_ctrl.value);
		should(switch_ctrl.value).be.eql(true);
		switch_ctrl.value = false;
		should(switch_ctrl.value).be.eql(false);
	});

});
