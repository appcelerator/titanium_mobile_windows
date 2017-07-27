/**
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
var path = require('path'),
	fs   = require('fs.extra'),
	_    = require('underscore'),
	LineReader = require('line-by-line'),
	path = require('path'),
	titaniumKit = {},
	windowsTitaniumKit = {},         // Stores what's implemented in Titanium Windows
	windowsTitaniumKit_Missing = []; // Stores missing module names


// FIXME: We could populate this while reading in the files, but it would
// require changes to how we read in, his isnt the nicest, but works for now
var APIS = [
	'2DMatrix',
	'API',
	'Accelerometer',
	'ActivityIndicator',
	'ActivityIndicatorStyle',
	'AlertDialog',
	'Analytics',
	'Animation',
	'Annotation',
	'App',
	'AttributedString',
	'AudioPlayer',
	'AudioRecorder',
	'Blob',
	'BlobStream',
	'Buffer',
	'BufferStream',
	'Button',
	'Camera',
	'Clipboard',
	'Codec',
	'Contacts',
	'Cookie',
	'Database',
	'EmailDialog',
	'File',
	'FileStream',
	'Filesystem',
	'Geolocation',
	'Gesture',
	'Group',
	'HTTPClient',
	'IOStream',
	'ImageView',
	'Item',
	'Label',
	'ListSection',
	'ListView',
	'Locale',
	'Map',
	'Media',
	'MusicPlayer',
	'Network',
	'Notification',
	'OptionDialog',
	'Person',
	'Picker',
	'PickerColumn',
	'PickerRow',
	'Platform',
	'ProgressBar',
	'Properties',
	'Route',
	'ScrollView',
	'ScrollableView',
	'SearchBar',
	'Slider',
	'Sound',
	'Stream',
	'Switch',
	'TCP',
	'Tab',
	'TabGroup',
	'TableView',
	'TableViewRow',
	'TableViewSection',
	'TextArea',
	'TextField',
	'UDP',
	'UI',
	'Utils',
	'VideoPlayer',
	'View',
	'View',
	'WebView',
	'Window',
	'XML'
];

String.prototype.capitalize = function() {
    return this.charAt(0).toUpperCase() + this.slice(1);
};

//
// Extract TitaniumKit API and find Windows implementation
//
function extract(callback) {
	var walker = fs.walk(path.join(__dirname, '../Source/TitaniumKit/src'));
	walker.on('file',
		function (root, stat, next) {
			if (/\.cpp$/.test(stat.name)) {
			    extractTitaniumKit(root, stat.name, next);
			} else {
				next();
			}
		}
	);
	walker.on('end', function() {
		extractWhiteList(callback);
	});
}

//
// Extract TitaniumKit API from cpp source
//
function extractTitaniumKit(root, file, next) {
	var reader = new LineReader(path.join(root, file)),
		module_name, properties = [] , methods = [], events = [];
	reader.on('line', function(line) {
		var namespace_match = line.match(/\s*\:\s*\w+\(js_context,\s*\"([\w\.]+)\"\)/);
		var unknown_match   = line.match(/\s*\:\s*Module\(js_context,\s*apiName\)/);
		var property_match  = line.match(/TITANIUM_ADD_PROPERTY\w*\((\w+),\s*(\w+)\);/);
		var function_match  = line.match(/TITANIUM_ADD_FUNCTION\((\w+),\s*(\w+)\);/);
		var constant_match  = line.match(/TITANIUM_ADD_CONSTANT_PROPERTY\w*\((\w+),\s*(\w+)\);/)

		if (namespace_match) {
			module_name = namespace_match[1];
			// convert Ti.* to Titanium.*
			if (module_name.indexOf('Ti.') == 0) {
				module_name = 'Titanium.' + module_name.slice(3);
			} else if (module_name === 'Ti') {
				module_name = 'Titanium';
			}
		} else if (unknown_match) {
			//
			// Some modules are using special pattern for now...
			//
			if (file == 'IOStream.cpp') {
				module_name = 'Titanium.IOStream';
			} else if (file == 'View.cpp') {
				module_name = 'Titanium.UI.View';
			}
		}

		// Don't expose internal property/function which starts with "_"
		if (property_match && property_match[2][0] != '_') {
			properties.push(property_match[2]);
		}
		if (function_match && function_match[2][0] != '_') {
			methods.push(function_match[2]);
		}
		if (constant_match && APIS.indexOf(constant_match[2]) === -1) {
			properties.push(constant_match[2]);
		}
	});
	reader.on('error', function(err) {
		console.error(err);
		process.exit(1);
	});
	reader.on('end', function() {
		if (module_name) {
			titaniumKit[module_name] = {
				module_name: module_name,
				properties: properties,
				methods: methods,
				events: events
			};
		}
		next();
	});
}

//
// Load API from whitelist, because some API are implemented in JavaScript
//
function extractWhiteList(callback) {
	var titaniumKit_whitelist = {};
	var reader = new LineReader(path.join(__dirname, 'whitelist.txt')),
		module_name, properties = [], methods = [], events = [];
	function addWhitelistEntry() {
		if (module_name) {
			titaniumKit_whitelist[module_name] = {
				module_name: module_name,
				properties: properties,
				methods: methods,
				events: events
			};
		}
		module_name = null;
		properties = [], methods = [], events = [];
	}
	reader.on('line', function(line) {
		var element = line.split(' '),
			type = element[0];
		if (type === 'C') {
			module_name = element[1];
		} else if (type === 'P') {
			properties.push(element[1]);
		} else if (type === 'M') {
			methods.push(element[1]);
		} else if (type === 'E') {
			events.push(element[1]);
		} else if (line.trim() == "") {
			// new whitelist entry
			addWhitelistEntry();
		}
	});
	reader.on('error', function(err) {
		console.error(err);
		process.exit(1);
	});
	reader.on('end', function() {
		// include last entry into whitelist
		addWhitelistEntry();

		// merge the result
		for (name in titaniumKit_whitelist) {
			if (titaniumKit[name]) {
				titaniumKit[name].properties = _.union(titaniumKit[name].properties, titaniumKit_whitelist[name].properties);
				titaniumKit[name].methods    = _.union(titaniumKit[name].methods, titaniumKit_whitelist[name].methods);
				titaniumKit[name].events     = _.union(titaniumKit[name].events, titaniumKit_whitelist[name].events);
			} else {
				titaniumKit[name] = titaniumKit_whitelist[name];
			}
		}

		extractWindowsKit(callback);
	});
}

//
// Search for platform implementation and find what's implemented
//
function extractWindowsKit(callback) {
	var walker = fs.walk(path.join(__dirname, '../Source/'));
	walker.on('file',
		function (root, stat, next) {
			if (/\.hpp$/.test(stat.name)) {
				var reader = new LineReader(path.join(root, stat.name)),
					module_name,
					properties = [], methods = [], events = [],
					un_properties = [], un_methods = [], un_events = [];
				reader.on('line', function(line) {
					var module_match = line.match(/\s*TITANIUM_MODULE_UNIMPLEMENTED\(\"*(\w[\w.]*)\"*\)/);
					if (module_match) {
						windowsTitaniumKit_Missing.push(module_match[1]);
					}

					// C++ header should contain @ingroup to represent Titanium proxy name
					var class_match = line.match(/@ingroup\s+([\w.]+)/);
					if (class_match) {
						module_name = class_match[1];
					}
					// Unimplemented Ti method be marked with TITANIUM_FUNCTION_UNIMPLEMENTED
					var method_match = line.match(/\s*TITANIUM_FUNCTION_UNIMPLEMENTED\(\"*(\w+)\"*\)/);
					if (method_match) {
						un_methods.push(method_match[1]);
					}
					// Unimplemented Ti property be marked with TITANIUM_PROPERTY_UNIMPLEMENTED
					var property_match = line.match(/\s*TITANIUM_PROPERTY_UNIMPLEMENTED\(\"*(\w+)\"*\)/);
					if (property_match) {
						var property_name   = property_match[1];
						var property_name_C = property_name.capitalize();
						un_properties.push(property_name);
						// Disable property getter/setter too
						un_methods.push('get' + property_name_C);
						un_methods.push('set' + property_name_C);
					}

				});
				reader.on('error', function(err) {
					console.error(err);
					process.exit(1);
				});
				reader.on('end', function() {
					if (module_name && titaniumKit[module_name]) {
						windowsTitaniumKit[module_name] = {
							module_name: module_name,
							properties: _.difference(titaniumKit[module_name].properties, un_properties),
							methods: _.difference(titaniumKit[module_name].methods, un_methods),
							events: _.difference(titaniumKit[module_name].events, un_events)
						};
					}
					next();
				});
			} else {
				next();
			}
		}
	);
	walker.on('end', callback);
}
//
// Export API document to YAML
//
function exportYAML() {
	for (module_name in titaniumKit) {
		var lines = [];
		lines.push('name: ' + module_name);
		lines.push('platforms: [windowsphone]');

		// dump properties
		titaniumKit[module_name].properties.length > 0 && lines.push('properties:');
		for (var i = 0; i < titaniumKit[module_name].properties.length; i++) {
			var property  = titaniumKit[module_name].properties[i];
			lines.push('  - name: ' + property);
			lines.push('    platforms: [windowsphone]');
		}

		// dump methods
		titaniumKit[module_name].methods.length > 0 && lines.push('methods:');
		for (var i = 0; i < titaniumKit[module_name].methods.length; i++) {
			var method    = titaniumKit[module_name].methods[i];
			lines.push('  - name: ' + method);
			lines.push('    platforms: [windowsphone]');
		}

		// dump events
		titaniumKit[module_name].events.length > 0 && lines.push('events:');
		for (var i = 0; i < titaniumKit[module_name].events.length; i++) {
			var eventname = titaniumKit[module_name].events[i];
			lines.push('  - name: ' + eventname);
			lines.push('    platforms: [windowsphone]');
		}

		// newline at end of file
		lines.push('\n');

		// dump to file
		var modulepath = module_name.split('.');
		var classname  = modulepath[modulepath.length-1];

		modulepath.pop();
		// everything should be go to Titanium directory
		if (modulepath[0] != 'Titanium') {
			modulepath[0] = 'Titanium';
		}
		var outdir = path.join(modulepath.join(path.sep));
		var outfile = path.join(outdir, classname + '.yml');
		console.log('Generating ' + outfile);
		fs.mkdirpSync(path.join(__dirname, outdir));
		fs.writeFileSync(path.join(__dirname, outfile), lines.join('\n'));
	}
}

function isEmpty(prop) {
	return prop.properties.length == 0 && prop.methods.length == 0 && prop.events.length == 0;
}
//
// Extract API from source & export to YAML
//
extract(function() {
	// remove unimplemented API
	for (var i = 0; i < windowsTitaniumKit_Missing.length; i++) {
		delete titaniumKit[windowsTitaniumKit_Missing[i]];
	}

	// now merge the supported API
	for (name in titaniumKit) {
		var winprop = windowsTitaniumKit[name];
		if (winprop) {
			titaniumKit[name] = winprop;
		}
		if (isEmpty(titaniumKit[name])) {
			delete titaniumKit[name];
		}
	}

	exportYAML();
});
