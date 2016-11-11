/**
 * Windows build command.
 *
 * @module cli/_build
 *
 * @copyright
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 *
 * @license
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var Builder = require('titanium-sdk/lib/builder'),
	util = require('util');

/*
 TODO:
 - figure out how to support different cpu architectures
 - command line option?
 - tiapp.xml property?
 - always build for all architectures?

 - depending on how tiapp.xml values (desc, publisher, name, id, version, etc)
 are embedded the app, you may be able to reduce the number of checks that
 trigger a full rebuild

 - many other TODOs sprinkled through this file and the hooks
 */

/**
 * Creates the Windows build object.
 *
 * @class
 * @classdesc Windows build logic and state.
 * @constructor
 */
function WindowsBuilder() {
	Builder.apply(this, arguments);

	this.deployTypes = {
		// windows phone targets
		'wp-emulator': 'development',
		'wp-device': 'test',
		'dist-phonestore': 'production',

		// windows store targets
		// 'ws-simulator': 'development',
		'ws-local': 'development',
		// 'ws-remote': 'test',
		'dist-winstore': 'production'
	};

	this.targets = Object.keys(this.deployTypes);

	this.defaultTarget = 'wp-emulator';

	this.tiSymbols = {};
}

util.inherits(WindowsBuilder, Builder);

var prototypes = require('./_build/_index');
for (var key in prototypes) {
	if (prototypes.hasOwnProperty(key)) {
		prototypes[key].mixin(WindowsBuilder);
	}
}

/*
 Create an instance of WindowsBuilder and bind several of our exports to it.
 */
var windowsBuilder = new WindowsBuilder(module);
exports.config = windowsBuilder.config.bind(windowsBuilder);
exports.validate = windowsBuilder.validate.bind(windowsBuilder);
exports.run = windowsBuilder.run.bind(windowsBuilder);