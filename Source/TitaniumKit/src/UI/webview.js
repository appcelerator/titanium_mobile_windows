(function () {
	function log(level, str) {
		Ti.App.notifyEvent('Ti.API.log' + ',' + level + ',' + JSON.stringify(str));
	}
	Ti = {
		API: {
			info: function (str) {
				log('INFO', str);
			},
			debug: function (str) {
				log('DEBUG', str);
			},
			error: function (str) {
				log('ERROR', str);
			},
			warn: function (str) {
				log('WARN', str);
			},
			log: function (level, str) {
				log(level, str);
			},
		},
		App: {
			_event_listeners: [],
			addEventListener: function (name, callback) {
				Ti.App._event_listeners[name] = Ti.App._event_listeners[name] || [];
				Ti.App._event_listeners[name].push(callback);
				Ti.App.notifyEvent('Ti.App.addEventListener,' + name + ',');
			},
			removeEventListener: function (name, callback) {
				var listeners = Ti.App._event_listeners[name];
				if (Array.isArray(listeners)) {
					var index = listeners.indexOf(callback);
					if (index !== -1) {
						listeners.splice(index, 1);
						Ti.App.notifyEvent('Ti.App.removeEventListener,' + name + ',');
					}
				}
			},
			fireEvent: function (name, data) {
				Ti.App.notifyEvent('Ti.App.fireEvent,' + name + ',' + JSON.stringify(data || {}));
			},
			executeListeners: function (name, data) {
				var listeners = Ti.App._event_listeners[name];
				if (Array.isArray(listeners)) {
					for (var i = 0; i < listeners.length; i++) {
						listeners[i].call(listeners[i], data);
					}	
				}
			}
		},
	};
	Titanium = Ti;
})();