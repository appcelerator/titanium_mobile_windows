/**
 * Generates native API wrapper classes and headers from API metadata.
 *
 * @module lib/stub
 *
 * @copyright
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 *
 * @license
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var fs = require('fs'),
	ejs = require('ejs'),
	path = require('path'),
	wrench = require('wrench'),
	async = require('async'),
	metadata = JSON.parse(fs.readFileSync(path.join(__dirname, 'hyperloop_windows_metabase.json.gz'))),
	all_classes = metadata['classes'],
	// The Metadata doesn't contain info on what APIs are specific to phone or store
	// So for now, let's hard-code the ones we know
	store_only_enums = [
		'Windows.Storage.FileAttributes.LocallyIncomplete'
	],
	store_only_methods = {
		'Windows.Storage.Search.StorageFileQueryResult': ['GetMatchingPropertiesWithRanges'],
		'Windows.Storage.FileProperties.StorageItemThumbnail': ['Close'],
		'Windows.Storage.StorageStreamTransaction': ['Close'],
		'Windows.Storage.StreamedFileDataRequest': ['Close'],
		'Windows.Storage.StorageFile': ['IsEqual', 'GetParentAsync'],
		'Windows.Storage.StorageFolder': ['IsEqual', 'GetParentAsync', 'TryGetItemAsync']
	},
	store_only_properties = {
		'Windows.Storage.Search.QueryOptions': ['StorageProviderIdFilter'],
		'Windows.Storage.StorageFolder': ['Provider'],
		'Windows.Storage.StorageFile': ['Provider', 'IsAvailable']
	},
	// We need to skip/map a number of collections to JSArray and JSObject
	// We handle these types specially in our conversions
	blacklist = [
		"object",
		"Windows.Foundation.Collections.IIterable`1<T>",
		"Windows.Foundation.Collections.IIterator`1<T>",
		"Windows.Foundation.Collections.IVectorView`1<T>",
		"Windows.Foundation.Collections.IVector`1<T>",
		"Windows.Foundation.Collections.IKeyValuePair`2<K,V>",
		"Windows.Foundation.Collections.IMap`2<K,V>",
		"Windows.Foundation.Collections.IMapView`2<K,V>",
		"Windows.Foundation.Collections.VectorChangedEventHandler`1<T>",
		"Windows.Foundation.Collections.IObservableVector`1<T>",
		"Windows.Foundation.Collections.IMapChangedEventArgs`1<K>",
		"Windows.Foundation.Collections.MapChangedEventHandler`2<K,V>",
		"Windows.Foundation.Collections.IObservableMap`2<K,V>",
		"Windows.Foundation.IAsyncAction",
		"Windows.Foundation.AsyncActionCompletedHandler",
		"Windows.Foundation.AsyncOperationWithProgressCompletedHandler`2<K,V>",
		"Windows.Foundation.IAsyncOperationWithProgress`2<K,V>",
		"Windows.Foundation.AsyncOperationCompletedHandler`1<T>",
		"Windows.Foundation.IAsyncOperation`1<T>",
		"Windows.Foundation.AsyncActionWithProgressCompletedHandler`1<T>",
		"Windows.Foundation.IAsyncActionWithProgress`1<T>",
		"Windows.Foundation.AsyncOperationProgressHandler`2<K,V>",
		"Windows.Foundation.AsyncActionProgressHandler`1<T>",
		"Windows.Foundation.IReference`1<T>",
		"Windows.Foundation.IReferenceArray`1<T>",
		"Windows.Foundation.TypedEventHandler`2<K,V>",
		"Windows.Foundation.EventHandler`1<T>"
	];

var logger;
exports.setLogger = function(_logger) {
	logger = _logger;
};

/**
 * Takes a type name string and tries to return just the basic type name,
 * handling common metadata issues, primtive arrays, prefixes, reference suffixes, etc.
 * @param {string} typeName - the full name of the type from the metadata, expects non-templated type strings
 * @return {string}
 */
function normalizeType(typeName) {
	var type = typeName.trim();
	if (type.indexOf('class ') == 0) {
		type = type.substring(6);
	}
	if (type.indexOf('valuetype ') == 0) {
		type = type.substring(10);
	}
	if (type.indexOf('>') == (type.length - 1)) {
		type = type.substring(0, type.length - 1);
	}
	// must drop & before []
	if (type.indexOf('&') == (type.length - 1)) {
		type = type.substring(0, type.length - 1);
	}
	if (type.indexOf('[]') == (type.length - 2)) {
		type = type.substring(0, type.length - 2);
	}
	if (type == 'object') {
		type = 'Platform.Object';
	}
	return type;
}

/*
 * Given a complex/full type name from metadata, tries to expand to all component types.
 * In most cases it juts normalized the simple type name.
 * For templated types it will return all types involved.
 * @param {string} typeName - the full name of the type from the metadata
 * @return {Array[string]}
 */
function expandTypes(typeName) {
	var types = [],
		type = typeName.trim(),
		index = type.indexOf('`'), // index used to hold indexOf results
		count = "", // number of templated args!
		collectionName;

	if (index != -1) {
		count = type.substring(index + 1, index + 2); // are there 1 or 2 templated args?
		if (count == '1') {
			collectionName = normalizeType(type.substring(0, index)); // grab the original type
			types.unshift(collectionName + '`1<T>');
			types = types.concat(expandTypes(type.substring(index + 3, type.length - 1))); // recurse into template arg
		} else if (count == '2') {
			collectionName = normalizeType(type.substring(0, index)); // grab the original type
			types.unshift(collectionName + '`2<K,V>');
			type = type.substring(index + 3, type.length - 1); // take the segment inside the template <>
			// split on ','
			index = type.indexOf(',');
			types = types.concat(expandTypes(type.substring(0, index))); // recurse into first template arg
			types = types.concat(expandTypes(type.substring(index + 1))); // recurse into second template arg
		}
	} else {
		types.unshift(normalizeType(typeName));
	}
	return types;
}

/*
 * Given a complex/full type name from metadata, expands out all types involved and adds any new types to the passed in array.
 * @param {string} rawTypeName - the full name of the type from the metadata
 * @param {Array[string]} existingTypes - the Array of existing known types
 * @return {void}
 */
function addNewTypes(rawTypeName, existingTypes) {
	var types = [];
	if (rawTypeName.indexOf('class ') == 0 || rawTypeName.indexOf('Windows.') == 0
		|| rawTypeName.indexOf('valuetype ') == 0) {
		types = expandTypes(rawTypeName);
		for (var i = 0; i < types.length; i++) {
			// skip template names, primitives
			if (types[i].indexOf("!") == 0 ||
				// primitives
				types[i] == 'bool' ||
				types[i] == 'char' ||
				types[i] == 'int64' ||
				types[i] == 'int32' ||
				types[i] == 'int16' ||
				types[i] == 'int' ||
				types[i] == 'uint64' ||
				types[i] == 'uint32' ||
				types[i] == 'uint16' ||
				types[i] == 'uint8' ||
				types[i] == 'float64' ||
				types[i] == 'float32' ||
				types[i] == 'double' ||
				types[i] == 'string' ||
				types[i] == 'Windows.Storage.StorageProvider') { // FIXME A Windows Store-only API!
				continue;
			}
			if (existingTypes.indexOf(types[i]) == -1) {
				existingTypes.unshift(types[i]);
			}
		}
	}
}

/*
 */
function addEventPropertyTypes(addEventMethod, existingTypes) {
	var handler_type_name = addEventMethod.args[0].type, // first arg type, should only be one arg
		handler_type,
		invoke_method,
		event_type_name = "",
		event_type;
	// handle special common handler types:
	if (handler_type_name.indexOf("Windows.Foundation.EventHandler`1") != -1) {
		event_type_name = expandTypes(handler_type_name)[1];
	} else if (handler_type_name.indexOf("Windows.Foundation.TypedEventHandler`2") != -1) {
		event_type_name = expandTypes(handler_type_name)[2];
	} else {
		// Dedicated event handler delegate type
		handler_type_name = normalizeType(handler_type_name);
		handler_type = all_classes[handler_type_name]; // grab handler type from metadata
		if (!handler_type) {
			// Make this an error?
			console.log("Unable to find metadata for: " + handler_type_name);
			return;
		}

		// Find the Invoke method in handler_type.methods!
		// FIXME Use nicer JS to find it!
		for (var i = 0; i < handler_type.methods.length; i++) {
			var method = handler_type.methods[i];
			if (method.name == "Invoke") {
				invoke_method = method;
				break;
			}
		}
		// event is last argument
		event_type_name = normalizeType(invoke_method.args[invoke_method.args.length - 1].type);
	}

	logger.trace("Determined event type to be: " + event_type_name);
	// Pull the metadata for the actual event object
	event_type = all_classes[event_type_name];
	if (!event_type) {
		// Make this an error?
		logger.warn("Unable to find metadata for: " + event_type_name);
		return;
	}

	// We need types for all the properties of the event! We don't need the event types because we flatten the event to attach all it's
	// properties to our own event object
	for (property_name in event_type.properties) {
		addNewTypes(event_type.properties[property_name].returnType, existingTypes);
	}
}

/**
 * Given a type name, look up all the types it references. Returns an array of strings (type names)
 * @param {string} classname - the full name of the type from the metadata
 * @return {Array[string]} - the full set of dependencies for this type
 */
function getDependencies(classname) {
	var classDefinition = all_classes[classname],
		types = [];
	if (!classDefinition) {
		logger.warn("Something went wrong. No metadata for type: " + classname);
		return types;
	}

	// skip system types
	if (classname.indexOf("[mscorlib]") == 0) {
		return types;
	}

	// Add parent
	if (classDefinition['extends']) {
		addNewTypes(classDefinition['extends'], types);
	}

	// gather all the types referenced in this file!
	var prop,
		method;
	// check property types
	for (property_name in classDefinition.properties) {
		// FIXME StorageProvider is a Windows Store only API, but we don't have anything in the metadata to let us know, nor have I figured out how to guard it to store apps only for now.
		if (property_name == 'Provider' && classname.indexOf('StorageFile') != -1) {
			continue;
		}

		prop = classDefinition.properties[property_name];
		addNewTypes(prop.returnType, types);
	}
	// Check method args and return types!
	if (classDefinition.methods) {
		for (var i = 0; i < classDefinition.methods.length; i++) {
			method = classDefinition.methods[i];

			// Skip if method starts with get_, put_ (properties), remove_ (events)
			if (method.name.indexOf('get_') == 0 || method.name.indexOf('put_') == 0 ||
				method.name.indexOf('remove_') == 0 || method.name == '.ctor') {
					continue;
			}

			// Skip non-public methods
			if (method.attributes.indexOf("public") == -1) {
				continue;
			}

			// Handle event handlers specially!
			if (method.name.indexOf('add_') == 0) {
				addEventPropertyTypes(method, types);
				continue;
			}

			// return type
			addNewTypes(method.returnType, types);
			// Check method args!
			for (var j = 0; j < method.args.length; j++) {
				addNewTypes(method.args[j].type, types);
			}
		}
	}
	classDefinition.dependencies = types;
	classDefinition.dependencies.unshift(classname);
	return types;
}

/*
 * Returns an array of fully qualified enum value names.
 * @param {string} type_name - the name of the type as it should appear in the metadata
 * @param {Object} metadata - the metadata loaded from disk
 * @return {Array[string]} - the fully qualified names of any enum dependencies of the given type
 */
function getEnumDependencies(type_name, metadata) {
	var fields = [],
		classDefinition = metadata[type_name],
		dependency = "",
		dependency_definition;

	if (classDefinition && classDefinition.dependencies) {
		for (var j = 0; j < classDefinition.dependencies.length; j++) {
			dependency = classDefinition.dependencies[j];
			dependency_definition = metadata[dependency];
			// for any enum dependencies...
			if (dependency_definition && dependency_definition['extends'] && 
				dependency_definition['extends'].indexOf("[mscorlib]System.Enum") == 0) {
				for (field_name in dependency_definition.fields) {
					// only register public fields
					if (dependency_definition.fields[field_name].attributes.indexOf('public') == -1) {
						continue;
					}
					fields.unshift(dependency +'.' + field_name);
				}
			}
		}
	}
	return fields;
}

/*
 * Given the list of seeds let's traverse the metadata to get dependency info,
 * sort and remove dupes from the seeds, add custom info to the metadata, etc.
 * @param {Array[string]} seeds - the list of types we need to generate.
 * @param {Function} next - 
 */
function initialize(seeds, next) {
	// Sort seeds by name and remove duplicates
	seeds = seeds.sort();
	seeds = seeds.filter(function(elem, pos) {
		return seeds.indexOf(elem) == pos;
	});

	// Adjust the metadata to mark certain methods and properties as store-only! 
	for (class_name in store_only_methods) {
		var methods = all_classes[class_name].methods;
		var store_methods = store_only_methods[class_name];
		for (var i = 0; i < methods.length; i++) {
			if (store_methods.indexOf(methods[i].name) != -1) {
				methods[i]['api'] = 'store';
			}
		}
	}
	for (class_name in store_only_properties) {
		var props = store_only_properties[class_name];
		for (var i = 0; i < props.length; i++) {
			all_classes[class_name].properties[props[i]]['api'] = 'store';
		}
	}

	// Using the seeds, generate the list of types we need to stub!
	// We've specified seed types, use those to gather the full list of types we'll need to generate
	var todo = [];
	for (var i = 0; i < seeds.length; i++) {
		todo.unshift(seeds[i]);
	}
	while (todo.length > 0) {
		var classname = todo.shift();
		logger.trace("Gathering dependencies of: " + classname);
		var dependencies = getDependencies(classname);
		// are there any new types here?
		for (var j = 0; j < dependencies.length; j++) {
			var the_dependency = dependencies[j];
			if (seeds.indexOf(the_dependency) == -1) {
				// new type. Add it to our seed listing and our queue to gather it's dependencies
				logger.trace("Adding type to list: " + the_dependency);
				seeds.unshift(the_dependency);
				todo.unshift(the_dependency);
			}
		}
	}


	// Generate a base class that everything can extend where we can hang a single unwrap method to get back an Object!
	all_classes['Platform.Object'] = {
		"name": 'Platform.Object',
		properties: {},
		methods: [
			{
				"attributes": [
					"public",
					"hidebysig",
					"newslot",
					"abstract",
					"virtual",
					"instance",
					"cil",
					"managed"
				],
				"returnType": "class Platform.Object",
				"name": "cast",
				"args": [
					{
					  "inout": "in",
					  "type": "string",
					  "name": "to_cast"
					}
				]
			}
		],
		attributes: [
			"public",
			"auto",
			"ansi",
			"windowsruntime"
		],
		'extends': 'Module'
	};
	seeds.unshift('Platform.Object');

	// sort again and de-dupe
	seeds = seeds.sort();
	seeds = seeds.filter(function(elem, pos) {
		return seeds.indexOf(elem) == pos;
	});
	next(null, seeds);
}

/*
 * Generates the native wrappers for the list of classes in seeds.
 * @param {String} dest -
 * @param {Array[string]} seeds - 
 * @param {Function} next - 
 */
function generateWrappers(dest, seeds, next) {
	// Now that we have the full list of types, let's stub them
	async.eachLimit(seeds, 25, function(classname, callback) {
		var classDefinition = all_classes[classname];
		logger.debug('Generating stubs for: ' + classname);

		// Skip blacklisted types
		if (blacklist.indexOf(classname) != -1) {
			callback();
			return;
		}
		
		if (!classDefinition) {
			callback("Something went wrong. No metadata for type: " + classname);
			return;
		}

		// skip structs and enums
		if (classDefinition['extends'] && 
			(classDefinition['extends'].indexOf("[mscorlib]System.Enum") == 0 ||
			classDefinition['extends'].indexOf("[mscorlib]System.ValueType") == 0)) {
			callback();
			return;
		}

		// Stub the header
		var hpp_file = path.join(__dirname, 'templates', 'Proxy.hpp');
		fs.readFile(hpp_file, 'utf8', function (err, data) {
			if (err) callback(err);

			var destFile = path.join(dest, 'include', classname + '.hpp'),
				rewrite = true,
			    generated_proxy_header = ejs.render(data, {properties: classDefinition.properties, methods: classDefinition.methods, name: classDefinition.name, metadata: all_classes, parent: classDefinition['extends']}, {filename: hpp_file});
			// Only write new contents if they differ from existing!
			if (fs.existsSync(destFile) && fs.readFileSync(destFile).toString() == generated_proxy_header) {
				logger.debug("Native wrapper header for " + classname + " unchanged, retaining existing file.");
				rewrite = false;
			}
			if (rewrite) {
				fs.writeFile(destFile, generated_proxy_header, {flags : 'w'}, function(err) {
					if (err) callback(err);
				});
			}
		});

		// Stub the implementation
		// TODO Trim the includes to avoid including parents of types we've already included! See trimTypes
		var cpp_file = path.join(__dirname, 'templates', 'Proxy.cpp');
		fs.readFile(cpp_file, 'utf8', function (err, data) {
			if (err) callback(err);

			var destFile = path.join(dest, 'src', classname + '.cpp'),
				generated_proxy_impl = ejs.render(data, {properties: classDefinition.properties, methods: classDefinition.methods, name: classDefinition.name, metadata: all_classes, parent: classDefinition['extends'], dependencies: classDefinition.dependencies}, {filename: cpp_file});
			
			if (classname == 'Platform.Object') {
				// Treat specially, by hacking in the cast method
				generated_proxy_impl = generateCasting(generated_proxy_impl, seeds);
			}

			if (fs.existsSync(destFile) && fs.readFileSync(destFile).toString() == generated_proxy_impl) {
				logger.debug("Native wrapper implementation for " + classname + " unchanged, retaining existing file.");
				callback();
				return;
			}
			fs.writeFile(destFile, generated_proxy_impl, {flags : 'w'}, function(err) {
				if (err) {
					callback(err);
				}
				else {
					callback();
				}
			});
		});
	}, next);
}

/**
 * Generates CMakeLists.txt to handle building up the list of native modules
 * @param {String} dest - 
 * @param {Array[string]} seeds - 
 * @param {Array[map]} modules - 
 * @param {Function} next - 
 */
function generateCmakeList(dest, seeds, modules, next) {
	var cmakelist_template = path.join(dest, 'CMakeLists.txt.ejs'),
		cmakelist = path.join(dest, 'CMakeLists.txt');
	logger.info("Setting up native modules for CMakeLists.txt...");
	fs.readFile(cmakelist_template, 'utf8', function (err, data) {
		if (err) throw err;

		var native_modules = [],
			contents = "";

		for (var i = 0; i < modules.length; i++) {
			var module = modules[i],
				projectname = module.manifest.moduleIdAsIdentifier;
			if (module.manifest.platform == "windows") {
				native_modules.push({
					projectname:projectname,
					path:module.modulePath.replace(/\\/g, '/').replace(' ', '\\ ')
				});
			}
		}

		data = ejs.render(data, {native_modules:native_modules }, {});
		if (fs.existsSync(cmakelist)) {
			contents = fs.readFileSync(cmakelist).toString();
			if (contents == data) {
				logger.debug("CMakeLists.txt contents unchanged, retaining existing file.");
				next();
				return;
			}
		}
		
		fs.writeFile(cmakelist, data, function(err) {
			next(err);
		});
	});
}

/**
 * When we include types in WindowsNativeModuleLoader, we used to include _every_ type.
 * But we know a type will include it's parent in it's own header
 * so we can eliminate including the parent if we include the child.
 * This method filters down to the Array of unique types we'll need to include.
 *
 * @param {Array[string]} seeds - The full set of seeds, including enums/structs and blacklisted types 
 * @return {Array[string]} - the filtered set of types to include - excludes blacklisted, structs, enums, and transitive types (parents of types already included here)
 */
 // TODO We should do the same sort of trimming for includes in the Proxy.cpp (line 470)!
function trimTypes(seeds) {
	var unique_classes = {},
		classname = '',
		classDefinition = {},
		filtered_classes = [];

	// Go through the list of seeds and copy them.
	// Skip all the blacklisted types, any types we have no metadata for, and any that are enums/structs
	for (var i = 0; i < seeds.length; i++) {
		classname = seeds[i];
		// Skip blacklisted types
		if (blacklist.indexOf(classname) != -1) {
			continue;
		}

		classDefinition = all_classes[classname];
		if (!classDefinition) {
			continue;
		}
		// skip enums and structs
		if (classDefinition['extends'] && 
			(classDefinition['extends'].indexOf("[mscorlib]System.Enum") == 0 ||
			classDefinition['extends'].indexOf("[mscorlib]System.ValueType") == 0)) {
			continue;
		}

		// OK it's not blacklisted, we have metadata, and it's not a struct/enum
		filtered_classes.unshift(classname);
		unique_classes[classname] = 1;
	}

	// Now we need to go through the list of classes and recursively remove parents
	for (var i = 0; i < filtered_classes.length; i++) {
		classname = filtered_classes[i];
		classDefinition = all_classes[classname];

		// if it has a parent and it's parent isn't a struct or enum, remove the parent
		if (classDefinition['extends'] && classDefinition['extends'].indexOf('[mscorlib]') == -1) {
			// Remove the parent from our listing
			// We also need to remove the parent's parent. But I think that should already happen since parent will still be in filtered_classes array
			logger.debug("Trimming include of parent: " + classDefinition['extends']);
			delete unique_classes[classDefinition['extends']];
		}
	}

	return Object.keys(unique_classes);
}


/**
 * Generates the code in WindowsNativeModuleLoader to handle require calls for native types.
 * This will load up the type in JS, hang it off global under the fully qualified type name,
 * and will also register any enum values in the appropriate namespace for any enum dependencies of the type.
 * @param {String} dest - 
 * @param {Array[string]} seeds - 
 * @param {Function} next - 
 */
function generateWindowsNativeModuleLoader(dest, seeds, next) {
	var native_loader = path.join(dest, 'src', 'WindowsNativeModuleLoader.cpp'),
		template = path.join(dest, 'src', 'WindowsNativeModuleLoader.cpp.ejs');
	// Now we'll add all the types we know about as includes into our require hook class
	// This let's us load these types by name using require!
	logger.trace("Adding require hook implementation in WindowsNativeModuleLoader.cpp...");
	fs.readFile(template, 'utf8', function (err, data) {
		if (err) throw err;

		var class_descriptions = {}, // the thing we're building up
			classname = "", // name of current type in outer loop
			classDefinition; // definition of current type in outer loop

		// Add our includes
		for (var i = 0; i < seeds.length; i++) {
			classname = seeds[i];
			// Skip blacklisted types
			if (blacklist.indexOf(classname) != -1) {
				continue;
			}

			classDefinition = all_classes[classname];
			if (!classDefinition) {
				logger.warn("Unable to find metadata for: " + classname);
				continue;
			}
			// skip enums and structs
			if (classDefinition['extends'] && 
				(classDefinition['extends'].indexOf("[mscorlib]System.Enum") == 0 ||
				classDefinition['extends'].indexOf("[mscorlib]System.ValueType") == 0)) {
				continue;	
			}

			class_descriptions[classname] = {};

			// Load up enum dependencies!
			// Add dependencies of current type
			class_descriptions[classname].enums = getEnumDependencies(classname, all_classes) || [];

			// Call registerEnums for parent type too
			if (classDefinition['extends'] && classDefinition['extends'].indexOf('[mscorlib]') == -1) {
				class_descriptions[classname].parent = classDefinition['extends'];
			}
		}

		data = ejs.render(data, { classes: class_descriptions, store_only_enums: store_only_enums, unique_classes: trimTypes(seeds) }, {});

		// if contents haven't changed, don't overwrite so we don't recompile the file
		if (fs.existsSync(native_loader) && fs.readFileSync(native_loader).toString() == data) {
			logger.debug("WindowsNativeModuleLoader contents unchanged, retaining existing file.");
			next();
			return;
		}

		fs.writeFile(native_loader, data, function(err) {
			next(err);
		});
	});
}

function capitalize(str) {
	return str.charAt(0).toUpperCase() + str.slice(1);
}

function getCppClassForModule(moduleId) {
	var ids = moduleId.split('.'), names = [];
	for (var i = 0; i < ids.length; i++) {
		names.push(capitalize(ids[i]));
	}
	return names.length > 0 ? names.join('::') : capitalize(moduleId);
}

/**
 * Generates the code in RequireHook.cpp to handle building up the list of native types registered.
 * @param {String} dest - 
 * @param {Array[string]} seeds - 
 * @param {Array[map]} modules - 
 * @param {Function} next - 
 */
function generateRequireHook(dest, seeds, modules, next) {
	var require_hook = path.join(dest, 'src', 'RequireHook.cpp'),
		template = path.join(dest, 'src', 'RequireHook.cpp.ejs');
	// Now we'll add all the types we know about as includes into our require hook class
	// This let's us load these types by name using require!
	logger.trace("Adding native API type listing to RequireHook.cpp...");
	fs.readFile(template, 'utf8', function (err, data) {
		if (err) throw err;

		var native_module_includes = [], // built up includes
			native_modules = [], // built up code for appending list of native types
			classDefinition; // definition of current type in outer loop

		// Add includes for native modules
		for (var i = 0; i < modules.length; i++) {
			var module = modules[i],
				classname = module.manifest.classname ? module.manifest.classname : getCppClassForModule(module.manifest.moduleid);
			if (module.manifest.platform == "windows") {
				native_module_includes.push(module.manifest.moduleIdAsIdentifier + ".hpp");
				native_modules.push({
					name:module.manifest.moduleid,
					className:classname,
					preload: true
				});
			}
		}

		// Add our includes
		for (var i = 0; i < seeds.length; i++) {
			classname = seeds[i];
			// Skip blacklisted types
			if (blacklist.indexOf(classname) != -1) {
				continue;
			}
			classDefinition = all_classes[classname];
			if (!classDefinition) {
				logger.warn("Unable to find metadata for: " + classname);
				continue;
			}
			// skip enums and structs
			if (classDefinition['extends'] && 
				(classDefinition['extends'].indexOf("[mscorlib]System.Enum") == 0 ||
				classDefinition['extends'].indexOf("[mscorlib]System.ValueType") == 0)) {
				continue;	
			}

			native_module_includes.push(classname + ".hpp");
			native_modules.push({name:classname});
		}

		data = ejs.render(data, { 
			native_module_includes:native_module_includes,
			native_modules:native_modules 
			}, {});


		// if contents haven't changed, don't overwrite so we don't recompile the file
		if (fs.existsSync(require_hook) && fs.readFileSync(require_hook).toString() == data) {
			logger.debug("RequireHook contents unchanged, retaining existing file.");
			next();
			return;
		}

		fs.writeFile(require_hook, data, function(err) {
			next(err);
		});
	});
}

/*
 * This adds the real cast implementation to Platform::Object native wrapper allowing us to unwrap,
 * wrap the object in the more specific type wrapper and return that new wrapper.
 * @param {String} contents - Original contents before adding casting 
 * @param {Array[string]} seeds -
 * @return {String} - the new contents with the casting method added 
 */
function generateCasting(contents, seeds) {
	// where do we stick our wrappers?
	logger.trace("Adding casting method to Platform.Object implementation...");

	var data = contents,
		includes = [],
		classes = "", // built up includes source
		cast_block = "",
		classname = "", // name of current type in outer loop
		classDefinition; // definition of current type in outer loop

	// Build up the block of casting
	for (var i = 0; i < seeds.length; i++) {
		classname = seeds[i];
		// Skip blacklisted types
		if (blacklist.indexOf(classname) != -1) {
			continue;
		}
		classDefinition = all_classes[classname];
		if (!classDefinition) {
			logger.warn("Unable to find metadata for: " + classname);
			continue;
		}
		// skip enums and structs
		if (classDefinition['extends'] && 
			(classDefinition['extends'].indexOf("[mscorlib]System.Enum") == 0 ||
			classDefinition['extends'].indexOf("[mscorlib]System.ValueType") == 0)) {
			continue;	
		}
		
		cast_block += "\t\t\t\telse if (to_cast == \"" + classname + "\") {\r\n" +
			"\t\t\t\t\tauto result = context.CreateObject(JSExport<Titanium::" + classname.replace(/\./g, '::') + ">::Class());\r\n" + 
			"\t\t\t\t\tauto result_wrapper = result.GetPrivate<Titanium::" + classname.replace(/\./g, '::') + ">();\r\n" +
			"\t\t\t\t\tresult_wrapper->wrap(dynamic_cast<::" + classname.replace(/\./g, '::') + "^>(unwrap()));\r\n" +
			"\t\t\t\t\treturn result;\r\n" +
			"\t\t\t\t}\r\n";
	}
	cast_block = "auto to_cast = static_cast<std::string>(_0);\r\n\t\t\t\t" + cast_block.substring(9); // drop first "\t\telse "

	// Get the filtered list of types to include
	includes = trimTypes(seeds);
	// Then build up the #includes source
	for (var i = 0; i < includes.length; i++) {
		classname = includes[i];
		classes += "#include \"" + classname + ".hpp\"\r\n";
	}
	classes = "// INSERT_INCLUDES\r\n" + classes + "// END_INCLUDES";

	var include_index = data.indexOf('#include "Platform.Object.hpp"');
	data = data.substring(0, include_index) + classes + data.substring(include_index + 31);

	// Insert cast block
	data = data.substring(0, data.indexOf('auto to_cast =')) + cast_block + data.substring(data.indexOf('return result;') + 14);
	return data;
}

/**
 * Generates the set of native type wrappers.
 * @param {String} dest - the location on disk where to place the generate types.
 * @param {Array{string}} seeds - The list of types needed
 * @param {Function} finished - Callback when detection is finished
 */
exports.generate = function generate(dest, seeds, modules, finished) {
	initialize(seeds, function(err, all_types) {
		if (err) {
			finished(err);
			return;
		}
		async.series([
			function(callback) {
		        generateWrappers(dest, all_types, callback);
		    },
		    function(callback) {
			    async.parallel([
				    function(callback) {
				        generateCmakeList(dest, all_types, modules, callback);
				    },
				    function(callback) {
				        generateWindowsNativeModuleLoader(dest, all_types, callback);
				    },
				    function(callback) {
				        generateRequireHook(dest, all_types, modules, callback);
				    }
				], callback);
			}
		], finished);
	});
};
