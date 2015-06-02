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
	// We need to skip/map a number of collections to JSArray and JSObject
	// We handle these types specially
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
		"Windows.Foundation.AsyncOperationWithProgressCompletedHandler`2<TResult,TProgress>",
		"Windows.Foundation.IAsyncOperationWithProgress`2<TResult,TProgress>",
		"Windows.Foundation.AsyncOperationCompletedHandler`1<TResult>",
		"Windows.Foundation.IAsyncOperation`1<TResult>",
		"Windows.Foundation.AsyncActionWithProgressCompletedHandler`1<TProgress>",
		"Windows.Foundation.IAsyncActionWithProgress`1<TProgress>",
		"Windows.Foundation.AsyncOperationProgressHandler`2<TResult,TProgress>",
		"Windows.Foundation.AsyncActionProgressHandler`1<TProgress>",
		"Windows.Foundation.IReference`1<T>",
		"Windows.Foundation.IReferenceArray`1<T>",
		"Windows.Foundation.TypedEventHandler`2<TSender,TResult>",
		"Windows.Foundation.EventHandler`1<T>"
	];

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
		collectionName;
	if (type.indexOf('`1<') != -1) {
		collectionName = normalizeType(type.substring(0, type.indexOf('`1<')));
		types.unshift(collectionName + '`1<T>');
		types = types.concat(expandTypes(type.substring(type.indexOf('`1<') + 3, type.length - 1)));
	} else if (type.indexOf('`2<') != -1) {
		collectionName = normalizeType(type.substring(0, type.indexOf('`2<')));
		types.unshift(collectionName + '`2<K,V>');
		type = type.substring(type.indexOf('`2<') + 3, type.length - 1);
		// split on ,!
		types = types.concat(expandTypes(type.substring(0, type.indexOf(','))));
		types = types.concat(expandTypes(type.substring(type.indexOf(',') + 1)));
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
			// skip template names
			if (types[i].indexOf("!") == 0) {
				continue;
			}
			if (existingTypes.indexOf(types[i]) == -1) {
				existingTypes.unshift(types[i]);
			}
		}
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
		console.log("Something went wrong. No metadata for type: " + classname);
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
		prop = classDefinition.properties[property_name];
		addNewTypes(prop.returnType, types);
	}
	// Check method args and return types!
	if (classDefinition.methods) {
		for (var i = 0; i < classDefinition.methods.length; i++) {
			method = classDefinition.methods[i];
			// Skip if method starts with get_, put_ (properties), add_ or remove_ (events)
			if (method.name.indexOf('get_') == 0 || method.name.indexOf('put_') == 0 ||
				method.name.indexOf('add_') == 0 || method.name.indexOf('remove_') == 0 ||
				method.name == '.ctor') {
					continue;
			}
			// Skip non-public methods
			if (method.attributes.indexOf("public") == -1) {
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
	// If we have no seeds, assume we want everything!
	if (seeds.length == 0) {
		for (classname in all_classes) {
			var classDefinition = all_classes[classname];
			// skip structs and enums
			if (classDefinition['extends'] && 
				(classDefinition['extends'].indexOf("[mscorlib]System.Enum") == 0 ||
				classDefinition['extends'].indexOf("[mscorlib]System.ValueType") == 0)) {
				continue;
			}

			seeds.unshift(classname);
		}
	}

	// Sort seeds by name and remove duplicates
	seeds = seeds.sort();
	seeds = seeds.filter(function(elem, pos) {
		return seeds.indexOf(elem) == pos;
	});

	// Using the seeds, generate the list of types we need to stub!
	// We've specified seed types, use those to gather the full list of types we'll need to generate
	var todo = [];
	for (var i = 0; i < seeds.length; i++) {
		todo.unshift(seeds[i]);
	}
	while (todo.length > 0) {
		var classname = todo.shift();
		console.log("Gathering dependencies of: " + classname);
		var dependencies = getDependencies(classname);
		// are there any new types here?
		for (var j = 0; j < dependencies.length; j++) {
			var the_dependency = dependencies[j];
			if (seeds.indexOf(the_dependency) == -1) {
				// new type. Add it to our seed listing and our queue to gather it's dependencies
				console.log("Adding type to list: " + the_dependency);
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
		console.log('Generating stubs for: ' + classname);

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
		//console.log("Stubbing header for " + classname);
		var hpp_file = path.join(__dirname, 'templates', 'Proxy.hpp');
		fs.readFile(hpp_file, 'utf8', function (err, data) {
			if (err) callback(err);

			var generated_proxy_header = ejs.render(data, {properties: classDefinition.properties, methods: classDefinition.methods, name: classDefinition.name, metadata: all_classes, parent: classDefinition['extends']}, {filename: hpp_file});
			// TODO Only write new contents if they differ from existing!
			fs.writeFile(path.join(dest, 'include', classname + '.hpp'), generated_proxy_header, {flags : 'w'}, function(err) {
				if (err) callback(err);
			});
		});

		// Stub the implementation
		//console.log("Stubbing implementation for " + classname);
		var cpp_file = path.join(__dirname, 'templates', 'Proxy.cpp');
		fs.readFile(cpp_file, 'utf8', function (err, data) {
			if (err) callback(err);

			var generated_proxy_impl = ejs.render(data, {properties: classDefinition.properties, methods: classDefinition.methods, name: classDefinition.name, metadata: all_classes, parent: classDefinition['extends'], dependencies: classDefinition.dependencies}, {filename: cpp_file});
			
			// TODO Only write new contents if they differ from existing!
			fs.writeFile(path.join(dest, 'src', classname + '.cpp'), generated_proxy_impl, {flags : 'w'}, function(err) {
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
 * Generates the code in WindowsNativeModuleLoader to handle require calls for native types.
 * This will load up the type in JS, hang it off global under the fully qualified type name,
 * and will also register any enum values in the appropriate namespace for any enum dependencies of the type.
 * @param {String} dest - 
 * @param {Array[string]} seeds - 
 * @param {Function} next - 
 */
function generateWindowsNativeModuleLoader(dest, seeds, next) {
	var native_loader = path.join(dest, 'src', 'WindowsNativeModuleLoader.cpp');
	// Now we'll add all the types we know about as includes into our require hook class
	// This let's us load these types by name using require!
	console.log("Adding require hook implementation in WindowsNativeModuleLoader.cpp...");
	fs.readFile(native_loader, 'utf8', function (err, data) {
		if (err) throw err;

		var classes = "", // built up includes
			loader_switch = "", // built up type instantiation/loading code
			enum_loader = "", // built up block for loading enum dependencies of a type
			classname = "", // name of current type in outer loop
			classDefinition, // definition of current type in outer loop
			dependency, // current enum dependency
			enum_dependencies = []; // list of all enum dependencies for this type

		// Add our includes
		for (var i = 0; i < seeds.length; i++) {
			classname = seeds[i];
			// Skip blacklisted types
			if (blacklist.indexOf(classname) != -1) {
				continue;
			}
			classDefinition = all_classes[classname];
			if (!classDefinition) {
				console.log("Unable to find metadata for: " + classname);
				continue;
			}
			// skip enums and structs
			if (classDefinition['extends'] && 
				(classDefinition['extends'].indexOf("[mscorlib]System.Enum") == 0 ||
				classDefinition['extends'].indexOf("[mscorlib]System.ValueType") == 0)) {
				continue;	
			}

			classes += "#include \"" + classname + ".hpp\"\r\n";
			loader_switch += "\t\telse if (path == \"" + classname + "\") {\r\n\t\t\tinstantiated = context.CreateObject(JSExport<::Titanium::" + classname.replace(/\./g, '::') + ">::Class());\r\n";
			
			// Load up enum dependencies!
			// Add dependencies of current type
			enum_dependencies = getEnumDependencies(classname, all_classes);
			if (enum_dependencies && enum_dependencies.length > 0) {
				enum_loader += "\t\telse if (type_name == \"" + classname + "\") {\r\n";
				// Call registerEnums for parent type too
				if (classDefinition['extends'] &&
					classDefinition['extends'].indexOf('[mscorlib]') == -1) {
					enum_loader += "\t\t\tregisterEnums(context, \"" + classDefinition['extends'] + "\");\r\n";
				}
				for (var j = 0; j < enum_dependencies.length; j++) {
					dependency = enum_dependencies[j];
				
					// hook the value up
					// TODO make use of native_to_js.cpp ejs template for this?
					enum_loader += "\t\t\tregisterValue(context, \"" + dependency + "\", context.CreateNumber(static_cast<int32_t>(static_cast<int>(::" + dependency.replace(/\./g, '::') + "))));\r\n";		
				}
				enum_loader += "\t\t}\r\n";
				loader_switch += "\t\t\tregisterEnums(context, path);\r\n";
			}
			loader_switch += "\t\t}\r\n";
		}
		loader_switch += "\t\telse {\r\n\t\t\treturn context.CreateUndefined();\r\n\t\t}\r\n\t\t// END_SWITCH";
		loader_switch = "// INSERT_SWITCH\r\n\t\t" + loader_switch.substring(7); // drop first "\t\telse "
		enum_loader = "// INSERT_ENUMS\r\n\t\t" + enum_loader.substring(7) + "\t\t// END_ENUMS"; // drop first "\t\telse "
		classes = "// INSERT_INCLUDES\r\n" + classes + "// END_INCLUDES";

		data = data.substring(0, data.indexOf('// INSERT_INCLUDES')) + classes + data.substring(data.indexOf('// END_INCLUDES') + 15);
		data = data.substring(0, data.indexOf('// INSERT_SWITCH')) + loader_switch + data.substring(data.indexOf('// END_SWITCH') + 13);
		data = data.substring(0, data.indexOf('// INSERT_ENUMS')) + enum_loader + data.substring(data.indexOf('// END_ENUMS') + 12);

		fs.writeFile(native_loader, data, function(err) {
			next(err);
		});
	});
}

/**
 * Generates the code in RequireHook.cpp to handle building up the list of native types registered.
 * @param {String} dest - 
 * @param {Array[string]} seeds - 
 * @param {Function} next - 
 */
function generateRequireHook(dest, seeds, next) {
	var require_hook = path.join(dest, 'src', 'RequireHook.cpp');
	// Now we'll add all the types we know about as includes into our require hook class
	// This let's us load these types by name using require!
	console.log("Adding native API type listing to RequireHook.cpp...");
	fs.readFile(require_hook, 'utf8', function (err, data) {
		if (err) throw err;

		var native_module_includes = [], // built up includes
			native_modules = [], // built up code for appending list of native types
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
				console.log("Unable to find metadata for: " + classname);
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

		fs.writeFile(require_hook, data, function(err) {
			next(err);
		});
	});
}

/*
 * This adds the real cast implementation to Platform::Object native wrapper allowing us to unwrap,
 * wrap the object in the more specific type wrapper and return that new wrapper.
 * @param {String} dest - 
 * @param {Array[string]} seeds -
 * @param {Function} callback -  
 */
function generateCasting(dest, seeds, next) {
	// where do we stick our wrappers?
	var platform_object_cpp = path.join(dest, 'src', 'Platform.Object.cpp');
	console.log("Adding casting method to Platform.Object implementation...");
	fs.readFile(platform_object_cpp, 'utf8', function (err, data) {
		if (err) throw err;

		var classes = "", // built up #includes
			cast_block = "",
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
				console.log("Unable to find metadata for: " + classname);
				continue;
			}
			// skip enums and structs
			if (classDefinition['extends'] && 
				(classDefinition['extends'].indexOf("[mscorlib]System.Enum") == 0 ||
				classDefinition['extends'].indexOf("[mscorlib]System.ValueType") == 0)) {
				continue;	
			}
			classes += "#include \"" + classname + ".hpp\"\r\n";
			cast_block += "\t\t\t\telse if (to_cast == \"" + classname + "\") {\r\n" +
				"\t\t\t\t\tauto result = context.CreateObject(JSExport<Titanium::" + classname.replace(/\./g, '::') + ">::Class());\r\n" + 
				"\t\t\t\t\tauto result_wrapper = result.GetPrivate<Titanium::" + classname.replace(/\./g, '::') + ">();\r\n" +
				"\t\t\t\t\tresult_wrapper->wrap(dynamic_cast<::" + classname.replace(/\./g, '::') + "^>(unwrap()));\r\n" +
				"\t\t\t\t\treturn result;\r\n" +
				"\t\t\t\t}\r\n";
		}
		cast_block = "auto to_cast = static_cast<std::string>(_0);\r\n\t\t\t\t" + cast_block.substring(9); // drop first "\t\telse "
		classes = "// INSERT_INCLUDES\r\n" + classes + "// END_INCLUDES";

		var include_index = data.indexOf('#include "Platform.Object.hpp"');
		data = data.substring(0, include_index) + classes + data.substring(include_index + 31);

		// Insert cast block
		data = data.substring(0, data.indexOf('auto to_cast =')) + cast_block + data.substring(data.indexOf('return result;') + 14);
		// Replace #include "Platform.Object.hpp" with same includes as native module loader!
		
		fs.writeFile(platform_object_cpp, data, function(err) {
			next(err);
		});
	});
}

/**
 * Generates the set of native type wrappers.
 * @param {String} dest - the location on disk where to place the generate types.
 * @param {Array{string}} seeds - The list of types needed
 * @param {Function} finished - Callback when detection is finished
 */
exports.generate = function generate(dest, seeds, finished) {
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
				        generateWindowsNativeModuleLoader(dest, all_types, callback);
				    },
				    function(callback) {
				        generateRequireHook(dest, all_types, callback);
				    },
				    function(callback) {
				        generateCasting(dest, all_types, callback);
				    }
				], callback);
			}
		], finished);
	});
};
