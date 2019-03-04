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
const ANALYTICS_URL = 'https://api.appcelerator.com/p/v4/mobile-track/',
	  ANALYTICS_FILE = 'analytics.json',
	  SESSION_TIME_SEPARATION = 1,
	  RETRY_TIMEOUT = 3,
	  RETRY_COUNT = 3,
	  TIMEOUT = 3,
	  EVENT_APP_FEATURE = 'app.feature',
	  EVENT_APP_NAV = 'app.nav',
	  EVENT_APP_INSTALL = 'app.install',
	  EVENT_SESSION_START = 'session.start',
	  EVENT_SESSION_END = 'session.end',
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

/**
 * Load queued events from local JSON
 */
Analytics.prototype.loadEventQueue = function () {
	if (this.analyticsFile && this.analyticsFile.exists()) {
		this.eventQueue = JSON.parse(this.analyticsFile.read().text) || [];
	}
};

/**
 * Save queued events from local JSON
 */
Analytics.prototype.saveEventQueue = function () {
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
 * Obtain first three segments of version string
 * @param  {String} version Full version string
 * @return {String} Trimmed version string
 */
function trimVersionQualifier(version) {
	let parts = [];
	// keep first three segments of the version number.
	if (version && version.indexOf('.') != -1) {
		parts = version.split('.');
		return parts.slice(0, 3).join('.');
	}
	return version;
}

/**
 * Construct comprehensive default event payload
 * @return {Object} Payload JSON object
 */
function getDefaultPayload() {
	return {
		distribution: {
			version: Ti.App.version,
			environment: Ti.App.deployType
		},
		hardware: {
			id: Ti.Platform.id,
			arch: Ti.Platform.architecture,
			name: Ti.Platform.model
		},
		os: {
			name: Ti.Platform.name,
			version: Ti.Platform.version
		}
	};
}

/**
 * Merge source JSON object into destination JSON object
 * @param  {Object} source JSON object
 * @param  {Object} destination JSON object
 */
function mergeJSON(source, destination) {
	for (let key in source) {
		if (source[key] instanceof Object && destination[key]) {
			mergeJSON(source[key], destination[key]);
			continue;
		}
		destination[key] = source[key];
	}
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
	for (let k in obj) {
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
 * @param {String} name - event name (e.g: 'app.feature')
 * @param {Object} data - JSON event data
 * @param {Object} payload - JSON event payload
 * @private
 */
Analytics.prototype.createEvent = function (name, data, payload) {
	let event = {
		id: Ti.Platform.createUUID(),
		timestamp: new Date().getTime(),
		event: name,
		version: '4',
		app: Ti.App.guid,
		session: {
			id: this.sessionId
		},
		data: {
			app_id: Ti.App.id,
			app_name: Ti.App.name,
			timezone: -(new Date().getTimezoneOffset()),
			sdk_version: Ti.version
		}
	};
	if (payload) {
		mergeJSON(payload, event);
	}
	if (data) {
		mergeJSON(data, event.data);
	}

	this.eventQueue.push(event);
	this.lastEvent = event;
};

/**
 * Creates a 'app.install' event and adds it to the event queue
 * @private
 */
Analytics.prototype.createEnrollEvent = function () {
	this.createEvent(EVENT_APP_INSTALL, {
		app_id: Ti.App.id,
		app_name: Ti.App.name,
		timezone: - new Date().getTimezoneOffset(),
		sdk_version: trimVersionQualifier(Ti.version)
	}, getDefaultPayload());
};

/**
 * Creates a 'session.start' event and adds it to the event queue
 * @private
 */
Analytics.prototype.createForegroundEvent = function () {
	this.createEvent(EVENT_SESSION_START, {
		app_id: Ti.App.id,
		app_name: Ti.App.name,
		timezone: - new Date().getTimezoneOffset(),
		sdk_version: trimVersionQualifier(Ti.version)
	}, getDefaultPayload());
};

/**
 * Creates a 'session.end' event and adds it to the event queue
 * @private
 */
Analytics.prototype.createBackgroundEvent = function () {
	this.createEvent(EVENT_SESSION_END, null, getDefaultPayload());
};

/**
 * Creates a 'app.feature' event and adds it to the event queue
 * @param {String} name - feature event name
 * @param {Object} data - JSON event data
 * @private
 */
Analytics.prototype.createFeatureEvent = function (name, data) {
	data = data || {};
	if (validateFeatureEvent(data, 0)) {
		this.createEvent(name, data, getDefaultPayload());
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
Analytics.prototype.createNavEvent = function (from, to, name, data) {
	data = data || {};
	data['eventName'] = name;
	data['from'] = from;
	data['to'] = to;
	this.createEvent(EVENT_APP_NAV, data, getDefaultPayload());
};

/**
 * Send all events in the event queue
 * @private
 */
Analytics.prototype.postEvents = function () {
	if (this.optedOut) {
		// Clear all pending events
		this.eventQueue = [];
		this.saveEventQueue();
		this.receivedResponse = true;
		Ti.API.debug('Skipping Ti.Analytics.postEvents because of opted-out');
		return;
	}
	if (Ti.Network.online) {
		let _t = this,
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
const analytics = new Analytics();
// listen for 'resume' and 'pause' events
Ti.App.addEventListener('resume', function (e) {
	// generate a new sessionId if we have been suspeneded for over 30 seconds
	if (analytics.timestamp && (new Date().getTime() - analytics.timestamp)/1000 > SESSION_TIME_SEPARATION) {
		analytics.sessionId = Ti.Platform.createUUID();
	}
	// queue ti.foreground event
	analytics.createForegroundEvent();
	// send events
	analytics.postEvents();
});
Ti.App.addEventListener('pause', function (e) {
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
		const r = analytics.createFeatureEvent(name, data);
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
	startPostingEvents: function () {
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
