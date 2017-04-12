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
	async = require('async'),
	spawn = require('child_process').spawn,
	logger, windowsInfo,
	targetPlatformSdkVersion, targetPlatformSdkMinVersion,
	cmakePlatform;

exports.init = function(thiz) {
	logger = thiz.logger;
	windowsInfo = thiz.windowsInfo;
	targetPlatformSdkVersion    = thiz.targetPlatformSdkVersion === '10.0' ? windowsInfo.windows['10.0'].sdks[0] : thiz.targetPlatformSdkVersion;
	targetPlatformSdkMinVersion = thiz.targetPlatformSdkMinVersion === '10.0' ? targetPlatformSdkVersion : thiz.targetPlatformSdkMinVersion;
	cmakePlatform = thiz.cmakePlatform;
};

function generateCmakeList(dest, modules, next) {
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
 * Generates the code in TypeHelper.cs to handle building up the list of native types registered.
 * @param {String} dest - 
 * @param {Array[map]} native_types - 
 * @param {Array[map]} native_events - 
 * @param {Function} next - 
 */
function generateNativeTypeHelper(dest, native_types, native_events, next) {
	var helper_cs = path.join(dest, 'src', 'TypeHelper.cs'),
		template = path.join(dest, 'src', 'TypeHelper.cs.ejs');
	// Now we'll add all the types we know about as includes into our TypeHelper class
	// This let's us load these types by name using C# Reflection
	logger.trace("Adding native API type listing to TypeHelper.cs...");
	fs.readFile(template, 'utf8', function (err, data) {
		if (err) throw err;

		data = ejs.render(data, { 
			native_types:native_types,
			native_events:native_events
		}, {});

		// if contents haven't changed, don't overwrite so we don't recompile the file
		if (fs.existsSync(helper_cs) && fs.readFileSync(helper_cs, 'utf8').toString() == data) {
			logger.debug("TypeHelper.cs contents unchanged, retaining existing file.");
			next();
			return;
		}

		fs.writeFile(helper_cs, data, function(err) {
			next(err);
		});
	});
}


/**
 * Generates the code in RequireHook.cpp to handle building up the list of native modules registered.
 * @param {String} dest - 
 * @param {Array[map]} modules - 
 * @param {Function} next - 
 */
function generateRequireHook(dest, modules, native_types, next) {
	var require_hook = path.join(dest, 'src', 'RequireHook.cpp'),
		template = path.join(dest, 'src', 'RequireHook.cpp.ejs');
	// Now we'll add all the types we know about as includes into our require hook class
	// This let's us load these types by name using require!
	logger.trace("Adding native module listing to RequireHook.cpp...");
	fs.readFile(template, 'utf8', function (err, data) {
		if (err) throw err;

		var native_module_includes = [], // built up includes
			native_modules = []; // built up code for appending list of native types

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

		data = ejs.render(data, { 
			native_module_includes:native_module_includes,
			native_modules:native_modules,
			native_types:native_types
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

function buildNativeTypeHelper(dest, platform, buildConfiguration, callback) {
	var slnFile = path.join(dest, platform, 'TitaniumWindows_Hyperloop.sln');
	runNuGet(slnFile, function(err) {
		if (err) return callback(err);
		runMSBuild(slnFile, buildConfiguration, callback);
	});
}

function generateTargetVersion(dest, platform, callback) {
	var template = path.join(dest, platform, 'TitaniumWindows_Hyperloop.csproj.ejs'),
		csproj   = path.join(dest, platform, 'TitaniumWindows_Hyperloop.csproj');

	logger.trace("Updating target version for " + platform);

	fs.readFile(template, 'utf8', function (err, data) {
		if (err) throw err;
		data = ejs.render(data, { 
			targetPlatformSdkVersion:    targetPlatformSdkVersion,
			targetPlatformSdkMinVersion: targetPlatformSdkMinVersion
		}, {});

		fs.writeFile(csproj, data, function(err) {
			callback(err);
		});
	});
}

function runNuGet(slnFile, callback) {
	logger.debug('nuget restore ' + slnFile);
	// Make sure project dependencies are installed via NuGet
	var nuget = path.resolve(__dirname, '..', 'vendor', 'nuget', 'nuget.exe');
		p = spawn(nuget, ['restore', slnFile]);
	p.stdout.on('data', function (data) {
		var line = data.toString().trim();
		if (line.indexOf('error ') >= 0) {
			logger.error(line);
		} else if (line.indexOf('warning ') >= 0) {
			logger.warn(line);
		} else if (line.indexOf(':\\') === -1) {
			logger.debug(line);
		} else {
			logger.trace(line);
		}
	});
	p.stderr.on('data', function (data) {
		logger.warn(data.toString().trim());
	});
	p.on('close', function (code) {
		if (code != 0) {
			process.exit(1); // Exit with code from nuget?
		}
		callback();
	});
}

function runMSBuild(slnFile, buildConfiguration, callback) {
	var vsInfo = windowsInfo.selectedVisualStudio;

	if (!vsInfo) {
		logger.error('Unable to find a supported Visual Studio installation');
		process.exit(1);
	}

	logger.debug('Running MSBuild on solution: ' + slnFile + ' for ' + buildConfiguration);

	// Use spawn directly so we can pipe output as we go
	var p = spawn(vsInfo.vcvarsall, [
		'&&', 'MSBuild', '/p:Platform=Any CPU', '/p:Configuration=' + buildConfiguration, slnFile
	]);
	p.stdout.on('data', function (data) {
		var line = data.toString().trim();
		if (line.indexOf('error ') >= 0) {
			logger.error(line);
		}
		else if (line.indexOf('warning ') >= 0) {
			logger.warn(line);
		}
		else if (line.indexOf(':\\') === -1) {
			logger.debug(line);
		}
		else {
			logger.trace(line);
		}
	});
	p.stderr.on('data', function (data) {
		logger.warn(data.toString().trim());
	});
	p.on('close', function (code) {

		if (code != 0) {
			logger.error('MSBuild fails with code ' + code);
			process.exit(1); // Exit with code from msbuild?
		}

		callback();
	});
}

/**
 * Generates the set of native type wrappers.
 * @param {String} dest - the location on disk where to place the generate types.
 * @param {Array[map]} modules - List of native modules
 * @param {Array[map]} native_types - List of native types
 * @param {Array[map]} native_events - List of native events
 * @param {Function} finished - Callback when detection is finished
 */
exports.generate = function generate(dest, modules, native_types, native_events, finished) {
	var dest_Native    = path.join(dest, 'Native'),
		dest_Hyperloop = path.join(dest, 'TitaniumWindows_Hyperloop');

	native_types  = native_types  || {};
	native_events = native_events || {};

	var platform = 'win10';
	if (targetPlatformSdkVersion === '8.1') {
		if (cmakePlatform === 'WindowsStore') {
			platform = 'store';
		} else if (cmakePlatform === 'WindowsPhone') {
			platform = 'phone';
		}
	}

	async.parallel([
		function(callback) {
			// generate native types only when hyperloop is used
			if (Object.keys(native_types).length === 0) {
				return callback();
			}
			async.series([
				function(next) {
					generateNativeTypeHelper(dest_Hyperloop, native_types, native_events, next);
				},
				function(next) {
					generateTargetVersion(dest_Hyperloop, 'win10', next);
				},
				function(next) {
					buildNativeTypeHelper(dest_Hyperloop, platform, 'Debug', next);
				},
				function(next) {
					buildNativeTypeHelper(dest_Hyperloop, platform, 'Release', next);
				}
			], callback);
		},
		function(callback) {
			generateCmakeList(dest_Native, modules, callback);
		},
		function(callback) {
			generateRequireHook(dest_Native, modules, native_types, callback);
		}
	], finished);
};
