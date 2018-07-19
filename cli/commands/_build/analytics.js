var appc = require('node-appc'),
	os = require('os'),
	path = require('path'),
	ti = require('node-titanium-sdk'),
	__ = appc.i18n(__dirname).__;

/*
 Public API.
 */
exports.mixin = mixin;

/*
 Implementation.
 */
function mixin(WindowsBuilder) {
	WindowsBuilder.prototype.doAnalytics = doAnalytics;
}

/**
 * Creates the Titanium CLI analytics event for the build. The sending of this
 * event is done by the Titanium CLI after the build has finished.
 *
 * @param {Function} next - A function to call after the analytics event has been created.
 */
function doAnalytics(next) {
	var eventName = 'windows.' + this.target,
		tiapp = this.cli.tiapp;

	if (this.target === 'dist-phonestore') {
		eventName = "windows.distribute.phonestore";
	} else if (this.target === 'dist-winstore') {
		eventName = "windows.distribute.winstore";
	} else if (this.allowDebugging && this.cli.argv['debug-host']) {
		eventName += '.debug';
	} else if (this.allowProfiling && this.cli.argv['profiler-host']) {
		eventName += '.profile';
	} else {
		eventName += '.run';
	}

	this.cli.addAnalyticsEvent(eventName, {
		name: tiapp.name,
		publisher: tiapp.publisher,
		url: tiapp.url,
		image: tiapp.icon,
		appid: tiapp.id,
		description: tiapp.description,
		type: this.cli.argv.type, // app or module
		guid: tiapp.guid,
		version: tiapp.version,
		copyright: tiapp.copyright,
		date: (new Date()).toDateString()
	});

	next();
}
