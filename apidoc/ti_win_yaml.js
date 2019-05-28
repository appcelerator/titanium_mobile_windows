/**
 * Copyright (c) 2015-Present by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
'use strict';

const path = require('path');
const fs = require('fs-extra');
const walkSync = require('klaw-sync');
const union = require('lodash.union');
const difference = require('lodash.difference');
const LineReader = require('line-by-line');
const titaniumKit = {};
const windowsTitaniumKit = {};         // Stores what's implemented in Titanium Windows
const windowsTitaniumKit_Missing = []; // Stores missing module names

// FIXME: We could populate this while reading in the files, but it would
// require changes to how we read in, his isnt the nicest, but works for now
const APIS = [
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

String.prototype.capitalize = function () {
	return this.charAt(0).toUpperCase() + this.slice(1);
};

/**
 * Extract TitaniumKit API and find Windows implementation
 * @return {Promise}            [description]
 */
function extract() {
	const filterFn = item => item.path.endsWith('.cpp');
	const cppFiles = walkSync(path.join(__dirname, '../Source/TitaniumKit/src'), { filter: filterFn });
	const allPromises = Promise.all(cppFiles.map(file => extractTitaniumKit(file.path)));
	return allPromises.then(() => extractWhiteList());
}

/**
 * Extract TitaniumKit API from cpp source
 * @param  {string}   itemPath [description]
 * @return {Promise}
 */
function extractTitaniumKit(itemPath) {
	return new Promise((resolve, reject) => {
		const reader = new LineReader(itemPath);
		let module_name;
		const properties = [];
		const methods = [];
		const events = [];
		reader.on('line', line => {
			const namespace_match = line.match(/\s*:\s*\w+\(js_context,\s*"([\w.]+)"\)/);
			const unknown_match   = line.match(/\s*:\s*Module\(js_context,\s*apiName\)/);

			if (namespace_match) {
				module_name = namespace_match[1];
				// convert Ti.* to Titanium.*
				if (module_name.indexOf('Ti.') === 0) {
					module_name = 'Titanium.' + module_name.slice(3);
				} else if (module_name === 'Ti') {
					module_name = 'Titanium';
				}
			} else if (unknown_match) {
			// Some modules are using special pattern for now...
				if (itemPath.endsWith('IOStream.cpp')) {
					module_name = 'Titanium.IOStream';
				} else if (itemPath.endsWith('View.cpp')) {
					module_name = 'Titanium.UI.View';
				}
			}

			// Don't expose internal property/function which starts with "_"
			const property_match = line.match(/TITANIUM_ADD_PROPERTY\w*\((\w+),\s*(\w+)\);/);
			if (property_match && property_match[2][0] !== '_') {
				properties.push(property_match[2]);
			}

			const function_match = line.match(/TITANIUM_ADD_FUNCTION\((\w+),\s*(\w+)\);/);
			if (function_match && function_match[2][0] !== '_') {
				methods.push(function_match[2]);
			}

			const constant_match = line.match(/TITANIUM_ADD_CONSTANT_PROPERTY\w*\((\w+),\s*(\w+)\);/);
			if (constant_match && APIS.indexOf(constant_match[2]) === -1) {
				properties.push(constant_match[2]);
			}
		});
		reader.on('error', err => reject(err));
		reader.on('end', () => {
			if (module_name) {
				titaniumKit[module_name] = {
					module_name: module_name,
					properties: properties,
					methods: methods,
					events: events
				};
			}
			resolve();
		});
	});
}

/**
 * Load API from whitelist, because some API are implemented in JavaScript
 * @return {Promise} [description]
 */
function extractWhiteList() {
	return new Promise((resolve, reject) => {
		const titaniumKit_whitelist = {};
		const reader = new LineReader(path.join(__dirname, 'whitelist.txt'));
		let module_name;
		let properties = [];
		let methods = [];
		let events = [];
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
			properties = [];
			methods = [];
			events = [];
		}
		reader.on('line', line => {
			const element = line.split(' ');
			const type = element[0];

			if (type === 'C') {
				module_name = element[1];
			} else if (type === 'P') {
				properties.push(element[1]);
			} else if (type === 'M') {
				methods.push(element[1]);
			} else if (type === 'E') {
				events.push(element[1]);
			} else if (line.trim() === '') {
				// new whitelist entry
				addWhitelistEntry();
			}
		});
		reader.on('error', err => reject(err));
		reader.on('end', () => {
			// include last entry into whitelist
			addWhitelistEntry();

			// merge the result
			for (const name in titaniumKit_whitelist) {
				if (titaniumKit[name]) {
					titaniumKit[name].properties = union(titaniumKit[name].properties, titaniumKit_whitelist[name].properties);
					titaniumKit[name].methods    = union(titaniumKit[name].methods, titaniumKit_whitelist[name].methods);
					titaniumKit[name].events     = union(titaniumKit[name].events, titaniumKit_whitelist[name].events);
				} else {
					titaniumKit[name] = titaniumKit_whitelist[name];
				}
			}

			resolve();
		});
	}).then(() => extractWindowsKit());
}

/**
 * Search for platform implementation and find what's implemented
 * @return {Promise} [description]
 */
function extractWindowsKit() {
	const filterFn = item => item.path.endsWith('.hpp');
	const hppFiles = walkSync(path.join(__dirname, '../Source/'), { filter: filterFn });
	return Promise.all(hppFiles.map(file => extractWindowsKitFile(file.path)));
}

function extractWindowsKitFile(itemPath) {
	return new Promise((resolve, reject) => {
		const reader = new LineReader(itemPath);
		let module_name;
		const un_properties = [];
		const un_methods = [];
		const un_events = [];
		reader.on('line', line => {
			const module_match = line.match(/\s*TITANIUM_MODULE_UNIMPLEMENTED\("*(\w[\w.]*)"*\)/);
			if (module_match) {
				windowsTitaniumKit_Missing.push(module_match[1]);
			}

			// C++ header should contain @ingroup to represent Titanium proxy name
			const class_match = line.match(/@ingroup\s+([\w.]+)/);
			if (class_match) {
				module_name = class_match[1];
			}
			// Unimplemented Ti method be marked with TITANIUM_FUNCTION_UNIMPLEMENTED
			const method_match = line.match(/\s*TITANIUM_FUNCTION_UNIMPLEMENTED\("*(\w+)"*\)/);
			if (method_match) {
				un_methods.push(method_match[1]);
			}
			// Unimplemented Ti property be marked with TITANIUM_PROPERTY_UNIMPLEMENTED
			const property_match = line.match(/\s*TITANIUM_PROPERTY_UNIMPLEMENTED\("*(\w+)"*\)/);
			if (property_match) {
				const property_name = property_match[1];
				const propNameCaps = property_name.capitalize();
				un_properties.push(property_name);
				// Disable property getter/setter too
				un_methods.push(`get${propNameCaps}`);
				un_methods.push(`set${propNameCaps}`);
			}

		});
		reader.on('error', err => reject(err));
		reader.on('end', () => {
			if (module_name && titaniumKit[module_name]) {
				windowsTitaniumKit[module_name] = {
					module_name: module_name,
					properties: difference(titaniumKit[module_name].properties, un_properties),
					methods: difference(titaniumKit[module_name].methods, un_methods),
					events: difference(titaniumKit[module_name].events, un_events)
				};
			}
			resolve();
		});
	});
}

/**
 * Export API document to YAML
 * @return {Promise} [description]
 */
function exportYAML() {
	return Promise.all(Object.keys(titaniumKit).map(module_name => exportYAMLFile(module_name)));
}

/**
 * [exportYAMLFile description]
 * @param  {string} module_name [description]
 * @return {[type]}             [description]
 */
function exportYAMLFile(module_name) {
	const entry = titaniumKit[module_name];
	const lines = [];
	lines.push(`name: ${module_name}`);
	lines.push('platforms: [windowsphone]');

	// dump properties
	entry.properties.length > 0 && lines.push('properties:');
	entry.properties.forEach(property => {
		lines.push(`  - name: ${property}`);
		lines.push('    platforms: [windowsphone]');
	});

	// dump methods
	entry.methods.length > 0 && lines.push('methods:');
	entry.methods.forEach(name => {
		lines.push(`  - name: ${name}`);
		lines.push('    platforms: [windowsphone]');
	});

	// dump events
	entry.events.length > 0 && lines.push('events:');
	entry.events.forEach(name => {
		lines.push(`  - name: ${name}`);
		lines.push('    platforms: [windowsphone]');
	});

	// newline at end of file
	lines.push('\n');

	// dump to file
	const modulepath = module_name.split('.');
	const classname  = modulepath[modulepath.length - 1];

	modulepath.pop();
	// everything should be go to Titanium directory
	if (modulepath[0] !== 'Titanium') {
		modulepath[0] = 'Titanium';
	}
	const outdir = path.join(__dirname, modulepath.join(path.sep));
	const outfile = path.join(outdir, classname + '.yml');
	console.log(`Generating ${path.relative(__dirname, outfile)}`);
	return fs.ensureDir(outdir)
		.then(() => fs.writeFile(outfile, lines.join('\n')));
}

function isEmpty(prop) {
	return prop.properties.length === 0 && prop.methods.length === 0 && prop.events.length === 0;
}

// Extract API from source & export to YAML
extract().then(() => {
	// remove unimplemented API
	windowsTitaniumKit_Missing.forEach(entry => {
		delete titaniumKit[entry];
	});

	// now merge the supported API
	for (const name in titaniumKit) {
		const winprop = windowsTitaniumKit[name];
		if (winprop) {
			titaniumKit[name] = winprop;
		}
		if (isEmpty(titaniumKit[name])) {
			delete titaniumKit[name];
		}
	}

	exportYAML();
}).catch(err => {
	console.error(err);
	process.exit(1);
});
