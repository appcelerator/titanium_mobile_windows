/**
 * Analytics
 *
 * @module analytics
 *
 * @copyright
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 *
 * @license
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var ANALYTICS_URL = 'https://api.appcelerator.com/p/v3/mobile-track/',
	ANALYTICS_FILE = 'analytics.json',
	SESSION_TIME_SEPARATION = 30,
	RETRY_TIMEOUT = 3,
	RETRY_COUNT = 3,
	TIMEOUT = 3,
	EVENT_APP_FEATURE = 'app.feature',
	EVENT_APP_NAV = 'app.nav',
	EVENT_APP_ENROLL = 'ti.enroll',
	EVENT_APP_FOREGROUND = 'ti.foreground',
	EVENT_APP_BACKGROUND = 'ti.background',
	FEATURE_MAX_LEVELS = 5,
	FEATURE_MAX_SIZE = 1000,
	FEATURE_MAX_KEYS = 35,
	FEATURE_MAX_KEY_LENGTH = 50,
	OPTED_OUT_KEY = 'Ti.Analytics.optedOut';

/**
 * Creates the analytics object
 * @class
 * @classdesc Analytics object
 * @constructor
 */
function Analytics() {
	this.sessionId = Ti.Platform.createUUID();
	this.eventQueue = [];
	if (!this.analyticsFile) {
		this.analyticsFile = Ti.Filesystem.getFile(Ti.Filesystem.applicationDataDirectory + Ti.Filesystem.separator + ANALYTICS_FILE);
	}
	this.loadEventQueue();
	this.sequence = 0;
	this.http = null;
	this.timestamp = null;
	this.lastEvent = {};
	this.receivedResponse = false;
	this.optedOut = Ti.App.Properties.getBool(OPTED_OUT_KEY, false);
}

Analytics.prototype.loadEventQueue = function loadEventQueue() {
	if (this.analyticsFile && this.analyticsFile.exists()) {
		this.eventQueue = JSON.parse(this.analyticsFile.read().text) || [];
	}
};

Analytics.prototype.saveEventQueue = function saveEventQueue() {
	this.analyticsFile && this.analyticsFile.write(JSON.stringify(this.eventQueue));
};

/**
 * Convert an ISO date string into a SimpleDateFormat string
 * @param  {String} ISO format date string
 * @return {String} SimpleDateFormat string
 */
function toSimpleDateFormat(isoDateString) {
	return isoDateString.replace('Z', '+0000');
}

/**
 * Validate feature event data object meets limitations
 * @param  {Object} Feature event data object
 * @param {Number} Number of levels nested
 * @return {Boolean} Boolean result of validation
 */
function validateFeatureEvent(obj, level) {
	if (level > FEATURE_MAX_LEVELS) {
		Ti.API.warn('Feature event exceeds ' + FEATURE_MAX_LEVELS + ' level limit.');
		return false;
	}
	if (level == 0 && JSON.stringify(obj).length > FEATURE_MAX_SIZE) {
		Ti.API.warn('Feature event data object exceeds ' + FEATURE_MAX_SIZE + ' size limit.');
		return false;
	}
	if (Object.keys(obj).length > FEATURE_MAX_KEYS) {
		Ti.API.warn('Feature event data object exceeds ' + FEATURE_MAX_KEYS + ' key limit.');
		return false;
	}
	for (var k in obj) {
		if (k.length > FEATURE_MAX_KEY_LENGTH) {
			Ti.API.warn('Feature event data object key \'' + k + '\' exceeds ' + FEATURE_MAX_KEY_LENGTH + ' key length limit.');
			return false;
		}
		if (typeof obj[k] == 'object' && !validateFeatureEvent(obj[k], level + 1)) {
			return false;
		}
	}
	return true;
}

/**
 * Creates an event and adds it to the event queue
 * @param {String} eventType - event type (e.g: 'app.feature')
 * @param {Object} data - JSON event data
 * @private
 */
Analytics.prototype.createEvent = function createEvent(eventType, data) {
	data = data || {}; // ensure we always send a "data" property, empty object if null/undefined TIMOB-23402
	var event = {
		id: Ti.Platform.createUUID() + ':' + Ti.Platform.id,
		sid: this.sessionId,
		ts: toSimpleDateFormat(new Date().toISOString()),
		event: eventType,
		seq: this.sequence++,
		mid: Ti.Platform.id,
		ver: '3',
		aguid: Ti.App.guid,
		data: data
	};
	this.eventQueue.push(event);
	this.lastEvent = event;
};

function trimVersionQualifier(version) {
	var parts = [];
	// keep first three segments of the version number.
	if (version && version.indexOf('.') != -1) {
		parts = version.split('.');
		return parts.slice(0, 3).join('.');
	}
	return version;
}

/**
 * Creates a 'ti.enroll' event and adds it to the event queue
 * @private
 */
Analytics.prototype.createEnrollEvent = function createAppEnrollEvent() {
	this.createEvent(EVENT_APP_ENROLL, {
		platform: Ti.Platform.name,
		osarch: Ti.Platform.architecture,
		model: Ti.Platform.model,
		oscpu: Ti.Platform.processorCount,
		ostype: Ti.Platform.ostype,
		deploytype: Ti.App.deployType,
		app_id: Ti.App.id,
		app_name: Ti.App.name,
		os: Ti.Platform.osname,
		tz: - new Date().getTimezoneOffset(),
		nettype: Ti.Network.networkTypeName,
		app_version: Ti.App.version,
		osver: Ti.Platform.version,
		sdkver: "ti." + trimVersionQualifier(Ti.version)
	});
};

/**
 * Creates a 'ti.foreground' event and adds it to the event queue
 * @private
 */
Analytics.prototype.createForegroundEvent = function foregroundEvent() {
	this.createEvent(EVENT_APP_FOREGROUND, {
		platform: Ti.Platform.name,
		osarch: Ti.Platform.architecture,
		model: Ti.Platform.model,
		oscpu: Ti.Platform.processorCount,
		ostype: Ti.Platform.ostype,
		deploytype: Ti.App.deployType,
		app_id: Ti.App.id,
		app_name: Ti.App.name,
		os: Ti.Platform.osname,
		tz: - new Date().getTimezoneOffset(),
		nettype: Ti.Network.networkTypeName,
		app_version: Ti.App.version,
		osver: Ti.Platform.version,
		sdkver: "ti." + trimVersionQualifier(Ti.version)
	});
};

/**
 * Creates a 'ti.background' event and adds it to the event queue
 * @private
 */
Analytics.prototype.createBackgroundEvent = function backgroundEvent() {
	this.createEvent(EVENT_APP_BACKGROUND, null);
};

/**
 * Creates a 'app.feature' event and adds it to the event queue
 * @param {String} name - feature event name
 * @param {Object} data - JSON event data
 * @private
 */
Analytics.prototype.createFeatureEvent = function featureEvent(name, data) {
	data = data || {};
	if (validateFeatureEvent(data, 0)) {
		data['eventName'] = name;
		this.createEvent(EVENT_APP_FEATURE, data);
	} else {
	    Ti.API.error('Feature event \'' + name + '\' not conforming to recommended usage.');
	    return -1;
	}
	return 0;
};

/**
 * Creates a 'app.nav' event and adds it to the event queue
 * @param {String} from - navigation from
 * @param {String} to - navigation to
 * @param {String} name - feature event name
 * @param {Object} data - JSON event data
 * @private
 */
Analytics.prototype.createNavEvent = function navEvent(from, to, name, data) {
	data = data || {};
	data['eventName'] = name;
	data['from'] = from;
	data['to'] = to;
	this.createEvent(EVENT_APP_NAV, data);
};

/**
 * Send all events in the event queue
 * @private
 */
Analytics.prototype.postEvents = function postEvents() {
	if (this.optedOut) {
		// Clear all pending events
		this.eventQueue = [];
		this.saveEventQueue();
		this.receivedResponse = true;
		Ti.API.debug('Skipping Ti.Analytics.postEvents because of opted-out');
		return;
	}
	if (Ti.Network.online) {
		var _t = this,
			retry = 0;
		function post() {
			if (_t.http == null) {
				_t.http = Ti.Network.createHTTPClient({
					onload: function (e) {
						_t.eventQueue = [];
						_t.saveEventQueue();
						_t.receivedResponse = true;
					},
					onerror: function (e) {
						retry++;
						if (retry <= RETRY_COUNT) {
							setTimeout(post(), RETRY_TIMEOUT * 1000);
							Ti.API.debug('Failed to send analytics events. Retrying in ' + RETRY_TIMEOUT + ' seconds. Attempt #' + retry + '.');
						} else {
							Ti.API.error('Failed to send analytics events after ' + RETRY_COUNT + ' attempts.');
							_t.saveEventQueue();
						}
					},
					timeout: TIMEOUT * 1000
				});
				_t.http.open('POST', ANALYTICS_URL);
			}
			_t.receivedResponse = false;
			_t.http.setRequestHeader('Content-Type', 'application/json');
			_t.http.send(JSON.stringify(_t.eventQueue));
		}
		post();
	} else {
		this.saveEventQueue();

		// offline so dont wait for a response
		this.receivedResponse = true;
	}
};

// create analytics
var analytics = new Analytics();
// listen for 'resume' and 'pause' events
Ti.App.addEventListener('resume', function resume(e) {
	// generate a new sessionId if we have been suspeneded for over 30 seconds
	if (analytics.timestamp && (new Date().getTime() - analytics.timestamp)/1000 > SESSION_TIME_SEPARATION) {
		analytics.sessionId = Ti.Platform.createUUID();
	}
	// queue ti.foreground event
	analytics.createForegroundEvent();
	// send events
	analytics.postEvents();
});
Ti.App.addEventListener('pause', function pause(e) {
	// save suspend timestamp
	analytics.timestamp = new Date().getTime();
	//queue ti.background event
	analytics.createBackgroundEvent();
	// send events
	analytics.postEvents();
});

// set exports
this.exports = {
	featureEvent: function (name, data) {
		var r = analytics.createFeatureEvent(name, data);
		analytics.postEvents();
		return r;
	},
	navEvent: function (from, to, name, data) {
		analytics.createNavEvent(from, to, name, data);
		analytics.postEvents();
	},
	lastEvent: function () {
		return analytics.lastEvent;
	},
	getReceivedResponse: function () {
		return analytics.receivedResponse;
	},
	setReceivedResponse: function (value) {
		analytics.receivedResponse = value;
	},
	startPostingEvents: function() {
		Ti.API.debug('Start posting initial Ti.Analytics events');
		// enroll on our first launch
		if (!Ti.App.Properties.getBool('_firstLaunch', false)) {
			Ti.App.Properties.setBool('_firstLaunch', true);
			analytics.createEnrollEvent();
		}
		// queue ti.foreground event
		analytics.createForegroundEvent();
		// send events
		analytics.postEvents();
	},
	getOptedOut: function() {
		return analytics.optedOut;
	},
	setOptedOut: function(value) {
		analytics.optedOut = value;
		Ti.App.Properties.setBool(OPTED_OUT_KEY, value);
		Ti.API.debug('Saving Ti.Analytics.optedOut=' + value);
	}
};
