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
	logger, windowsInfo;

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

function generateNativeProject(dest, platform, builder, options, callback) {
	var template = path.join(dest, platform, 'TitaniumWindows_Hyperloop.csproj.ejs'),
		csproj   = path.join(dest, platform, 'TitaniumWindows_Hyperloop.csproj'),
		externalReferences = [];
		thirdpartyLibraries = builder.hyperloopConfig.windows.thirdparty && Object.keys(builder.hyperloopConfig.windows.thirdparty) || [];

	for (var i = 0; i < thirdpartyLibraries.length; i++) {
		externalReferences.push({
			Include: thirdpartyLibraries[i],
			HintPath: path.join('..', '..', 'lib', platform, builder.arch, thirdpartyLibraries[i] + '.winmd')
		});
	}

	fs.readFile(template, 'utf8', function (err, data) {
		if (err) throw err;
		data = ejs.render(data, { 
			externalReferences:          externalReferences,
			targetPlatformSdkVersion:    options.sdkVersion,
			targetPlatformSdkMinVersion: options.sdkMinVersion
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
	var p = spawn((process.env.comspec || 'cmd.exe'), ['/S', '/C', '"', vsInfo.vsDevCmd.replace(/[ \(\)\&]/g, '^$&') +
		' &&' + ' MSBuild' + ' /p:Platform=\"Any CPU\"' + ' /p:Configuration=' + buildConfiguration + ' ' + slnFile, '"'
	], {windowsVerbatimArguments: true});

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
 * @param {Object} builder - Builder
 * @param {Function} finished - Callback when detection is finished
 */
exports.generate = function generate(builder, finished) {

	var dest = builder.buildDir,
		modules = builder.modules,
		native_types   = builder.native_types || {},
		native_events  = builder.native_events || {},	
		dest_Native    = path.join(dest, 'Native'),
		dest_Hyperloop = path.join(dest, 'TitaniumWindows_Hyperloop');

	logger = builder.logger;
	windowsInfo = builder.windowsInfo;

	var sdkVersion = builder.targetPlatformSdkVersion === '10.0' ? windowsInfo.windows['10.0'].sdks[0] : builder.targetPlatformSdkVersion,
	 	sdkMinVersion = builder.targetPlatformSdkMinVersion === '10.0' ? sdkVersion : builder.targetPlatformSdkMinVersion;

	var platform = 'win10';
	if (sdkVersion === '8.1') {
		if (builder.cmakePlatform === 'WindowsStore') {
			platform = 'store';
		} else if (builder.cmakePlatform === 'WindowsPhone') {
			platform = 'phone';
		}
	}

	if (builder.useHyperloopBuilder) {
		//
		// Let Hyperloop module generate code (>= Hyperloop 2.2.0)
		//
		builder.cli.createHook('build.windows.stub.generate', builder, function (builder, done) {
			async.parallel([
				function(cb) {
					builder.cli.createHook('build.windows.stub.generateCmakeList', builder, function (builder, cb) {
						generateCmakeList(dest_Native, builder.modules, cb);
					})(builder, cb);
				},
				function(cb) {
					builder.cli.createHook('build.windows.stub.generateRequireHook', builder, function (builder, cb) {
						generateRequireHook(dest_Native, builder.modules, builder.native_types, cb);
					})(builder, cb);
				}
			], function() {
				done();
			});
		})(builder, finished);
	} else {
		//
		// Compatibility Mode
		// Use 'built-in' code generation for older version of Hyperloop module (< Hyperloop 2.2.0)
		//
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
						generateNativeProject(dest_Hyperloop, platform, builder, 
							{
								sdkVersion: sdkVersion,
								sdkMinVersion: sdkMinVersion
							}, next);
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
	}
};
