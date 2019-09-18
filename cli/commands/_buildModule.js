/**
 * Windows module build command.
 *
 * @module cli/_buildModule
 *
 * @copyright
 * Copyright (c) 2015-2018 by Appcelerator, Inc. All Rights Reserved.
 *
 * @license
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
'use strict';

const archiver = require('archiver');
const async = require('async');
const appc = require('node-appc');
const Builder = require('node-titanium-sdk/lib/builder');
const DOMParser = require('xmldom').DOMParser;
const fs = require('fs-extra');
const path = require('path');
const windowslib = require('windowslib');
const util = require('util');
const spawn = require('child_process').spawn; // eslint-disable-line security/detect-child-process
const EventEmitter = require('events').EventEmitter;

const defaultTypes = [ 'WindowsPhone', 'WindowsStore', 'Windows10' ];
const configuration = 'Release';
const vs_architectures = { ARM: 'ARM', x86: 'Win32' }; // x86 -> Win32 mapping
const __ = appc.i18n(__dirname).__;

let types = defaultTypes.slice(0);
let typesMin = [ 'phone', 'store', 'win10' ];

function WindowsModuleBuilder() {
	Builder.apply(this, arguments);
}
util.inherits(WindowsModuleBuilder, Builder);

WindowsModuleBuilder.prototype.config = function config(logger, config, cli) {
	Builder.prototype.config.apply(this, arguments);
};

WindowsModuleBuilder.prototype.validate = function validate(logger, config, cli) {
	if (cli.argv.platform && cli.argv.platform !== 'windows') {
		logger.error('Invalid platform');
		process.exit(1);
	}

	var manifest = cli.manifest;
	var sdkModuleAPIVersion = cli.sdk.manifest && cli.sdk.manifest.moduleAPIVersion && cli.sdk.manifest.moduleAPIVersion['windows'];
	if (manifest.apiversion && sdkModuleAPIVersion && manifest.apiversion !== sdkModuleAPIVersion) {
		logger.error(__('The module manifest apiversion is currently set to %s', manifest.apiversion));
		logger.error(__('Titanium SDK %s Windows module apiversion is at %s', cli.sdk.manifest.version, sdkModuleAPIVersion));
		logger.error(__('Please update module manifest apiversion to match Titanium SDK module apiversion'));
		logger.error(__('and the minsdk to %s',  cli.sdk.manifest.version));
		process.exit(1);
	}
};

WindowsModuleBuilder.prototype.run = function run(logger, config, cli, finished) {
	Builder.prototype.run.apply(this, arguments);

	this.cli = cli;
	this.logger = logger;

	appc.async.series(this, [
		function (next) {
			cli.scanHooks(path.join(cli.argv['project-dir'], 'plugins', 'hooks'));
			next();
		},
		function (next) {
			cli.emit('build.module.pre.construct', this, next);
		},

		'doAnalytics',
		'initialize',
		'checkOldPlugin',
		'loginfo',
		'generateModuleProject',

		function (next) {
			cli.emit('build.module.pre.compile', this, next);
		},

		'compileModule',

		function (next) {
			cli.emit('build.module.post.compile', this, next);
		},

		'copyModule',

		function (next) {
			cli.emit('build.module.pre.package', this, next);
		},

		'packageZip',

		function (next) {
			cli.emit('build.module.post.package', this, next);
		},
	], function (err) {
		cli.emit('build.module.finalize', this, function () {
			finished(err);
		});
	});
};

WindowsModuleBuilder.prototype.doAnalytics = function doAnalytics(next) {
	var cli = this.cli,
		manifest = cli.manifest,
		eventName = 'windows.' + cli.argv.type;

	cli.addAnalyticsEvent(eventName, {
		name: manifest.name,
		publisher: manifest.author,
		appid: manifest.moduleid,
		description: manifest.description,
		type: cli.argv.type,
		guid: manifest.guid,
		version: manifest.version,
		copyright: manifest.copyright,
		date: (new Date()).toDateString()
	});

	next();
};

WindowsModuleBuilder.prototype.initialize = function initialize(next) {
	var _t = this;

	function assertIssue(issues, name) {
		for (var i = 0, l = issues.length; i < l; i++) {
			if ((typeof name === 'string' && issues[i].id === name) || (typeof name === 'object' && name.test(issues[i].id))) {
				issues[i].message.split('\n').forEach(function (line) {
					logger.error(line.replace(/(__(.+?)__)/g, '$2'.bold));
				});
				logger.log();
				process.exit(1);
			}
		}
	}

	this.projectDir = this.cli.argv['project-dir'];
	this.manifest = this.cli.manifest;
	this.buildDir = path.join(this.projectDir, 'build');

	// TIMOB-23557
	// read timodule.xml and get configuration
	var timodule = path.join(this.projectDir, 'timodule.xml');
	if (fs.existsSync(timodule)) {
		var ti_dom  = new DOMParser().parseFromString(fs.readFileSync(timodule, 'utf8').toString()),
			ti_root = ti_dom.getElementsByTagName('windows');
		if (ti_root.length > 0) {
			var win_items = ti_root.item(0);
			appc.xml.forEachElement(win_items, function (item) {
				if (item.tagName == 'manifest') {
					appc.xml.forEachElement(item, function (node) {
						if (node.tagName == 'uses-sdk') {
							var sdk_version = appc.xml.getAttr(node, 'targetSdkVersion');
							if (sdk_version) {
								_t.targetPlatformSdkVersion = sdk_version;
								_t.logger.debug('targetSdkVersion: ' + sdk_version);
								// Remove Windows10 target only when it targets to 8.1 explicitly
								if (sdk_version == '8.1') {
									_t.logger.error('The specified version of the Windows and Windows Phone SDK "%s" is not supported by Titanium %s', sdk_version, _t.titaniumSdkName);
									process.exit(0);
								}
							}
						}
					});
				}
			});
		}
	}

	windowslib.detect(function (err, windowsInfo) {
		assertIssue(windowsInfo.issues, 'WINDOWS_VISUAL_STUDIO_NOT_INSTALLED');
		assertIssue(windowsInfo.issues, 'WINDOWS_MSBUILD_ERROR');
		assertIssue(windowsInfo.issues, 'WINDOWS_MSBUILD_TOO_OLD');

		if (!windowsInfo.selectedVisualStudio) {
			logger.error('Unable to find a supported Visual Studio installation');
			process.exit(1);
		}

		// Visual Studio 2017 doesn't support Windows/Phone 8.1 project anymore
		if (/^Visual Studio \w+ 2017/.test(windowsInfo.selectedVisualStudio.version)) {
			types    = [ 'Windows10' ];
			typesMin = [ 'win10' ];
		}

		_t.windowsInfo = windowsInfo;

		next();
	});
};

WindowsModuleBuilder.prototype.checkOldPlugin = function checkOldPlugin(next) {
	var old_plugin = path.join(this.projectDir, 'plugins', 'hooks', 'windows.js');
	if (fs.existsSync(old_plugin)) {
		this.logger.error('Old plugin detected: ' + old_plugin);
		this.logger.error('plugins/hooks/windows.js is no longer valid, it should be removed.');
		this.logger.error('Please remove plugins/hooks/windows.js in order to continue module build.');
		process.exit(1);
	}
	next();
};

WindowsModuleBuilder.prototype.loginfo = function loginfo(next) {
	console.log('--- WindowsModuleBuilder loginfo');

	this.logger.info('Visual Studio version: ' + this.windowsInfo.selectedVisualStudio.version.cyan);
	this.logger.info('MSBuild version: ' + this.windowsInfo.selectedVisualStudio.msbuildVersion.cyan);
	this.logger.info('Project directory: ' + this.projectDir.cyan);

	next();
};

WindowsModuleBuilder.prototype.generateModuleProject = function generateModuleProject(next) {
	var tasks = [
		function (done) {
			runCmake(this, 'WindowsStore', 'Win32', '10.0', done);
		},
		function (done) {
			runCmake(this, 'WindowsStore', 'ARM', '10.0', done);
		}
	];

	appc.async.series(this, tasks, function (err) {
		next(err);
	});
};

WindowsModuleBuilder.prototype.compileModule = function compileModule(next) {
	var _t = this;

	function build(sln, config, arch, next) {
		var nativeAssetsDir = path.dirname(sln),
			platformTarget  = path.basename(nativeAssetsDir),
			vcxproj = path.join(nativeAssetsDir, _t.manifest.moduleIdAsIdentifier + '.vcxproj'),
			vcxContent,
			buildPath;
		// user may skip specific architecture by using CLI.
		// at least we are skipping WindowsStore.ARM for now
		if (!fs.existsSync(sln)) {
			_t.logger.info('Skipping ' + sln + ' for ' + platformTarget + ' ' + config);
			next();
			return;
		} else {
			_t.logger.info('Building ' + sln + ' for ' + platformTarget + ' ' + config);
		}

		vcxContent = fs.readFileSync(vcxproj, 'utf8');
		// Check the build output dir that the module is set up for.
		// If it doesn't exist, copy our local copy of everything over to it.
		buildPath = path.resolve(vcxContent.match(/<OutDir .+?>(.+?)<\/OutDir>/)[1], '..');
		if (buildPath != nativeAssetsDir) {
			fs.ensureDirSync(buildPath);
			// make sure destination exists
			fs.ensureDirSync(buildPath);
			fs.copySync(nativeAssetsDir, buildPath, {
				overwrite: true
			});
			sln = path.join(buildPath, _t.manifest.moduleIdAsIdentifier + '.vcxproj');
		}

		var p = spawn((process.env.comspec || 'cmd.exe'), [ '/S', '/C', '"', _t.windowsInfo.selectedVisualStudio.vsDevCmd.replace(/[ \(\)\&]/g, '^$&')
			+ ' && MSBuild /p:Platform=' + arch + ' /p:Configuration=' + config + ' ' + sln, '"'
		], { windowsVerbatimArguments: true });

		p.stdout.on('data', function (data) {
			var line = data.toString().trim();
			if (line.indexOf('error ') >= 0) {
				_t.logger.warn(line);
			} else if (line.indexOf('warning ') >= 0) {
				_t.logger.warn(line);
			} else if (line.indexOf(':\\') === -1) {
				_t.logger.debug(line);
			} else {
				_t.logger.trace(line);
			}
		});
		p.stderr.on('data', function (data) {
			_t.logger.error(data.toString().trim());
		});
		p.on('close', function (code) {
			if (code !== 0) {
				process.exit(code);
			}
			next();
		});
	}

	// compile module projects
	var archs = _t.manifest.architectures.split(' ');
	async.eachSeries(types, function (type, next_type) {
		async.eachSeries(archs, function (arch, next_arch) {
			var architecture = vs_architectures[arch],
				sln = path.resolve(_t.projectDir, type + '.' + architecture, _t.manifest.moduleIdAsIdentifier + '.sln');

			build(sln, configuration, architecture, next_arch);
		}, function (err) {
			if (err) {
				throw err;
			}
			next_type();
		});
	}, function (err) {
		if (err) {
			throw err;
		}
		next();
	});
};

function walkdir(dirpath, base, callback) {
	var results = [];
	if (typeof base === 'function') {
		callback = base;
		base = dirpath;
	}
	fs.readdir(dirpath, function (err, list) {
		var i = 0;
		var file;
		var filepath;
		if (err) {
			return callback(err);
		}
		(function next() {
			file = list[i++];
			if (!file) {
				return callback(null, results);
			}
			filepath = path.join(dirpath, file);
			fs.stat(filepath, function (err, stats) {
				results.push({
					path: filepath,
					relative: path.relative(base, filepath).replace(/\\/g, '/'),
					stats: stats
				});
				if (stats && stats.isDirectory()) {
					walkdir(filepath, base, function (err, res) {
						results = results.concat(res);
						next();
					});
				} else {
					next();
				}
			});
		}());
	});
}

WindowsModuleBuilder.prototype.copyModule = function copyModule(next) {

	// Suppress warnings from Stream
	EventEmitter.defaultMaxListeners = 100;

	var buildDir = path.join(this.projectDir, 'build'),
		moduleDir = path.join(buildDir, this.manifest.moduleid, this.manifest.version),
		projectname = this.manifest.moduleIdAsIdentifier,
		_t = this;

	// empty any existing module directory
	fs.emptyDirSync(moduleDir);

	// copy necesary folders and files
	var parent_folders = [ 'documentation', 'example', 'assets' ],
		parent_files   = [ 'LICENSE' ];
	parent_folders.forEach(function (folder) {
		var from = path.join(_t.projectDir, '..', folder);
		if (fs.existsSync(from)) {
			fs.copySync(from, path.join(moduleDir, folder));
		}
	});
	parent_files.forEach(function (filename) {
		var from = path.join(_t.projectDir, '..', filename),
			to   = path.join(moduleDir, filename);
		if (fs.existsSync(from) && !fs.existsSync(to)) {
			fs.createReadStream(from).pipe(fs.createWriteStream(to));
		}
	});
	fs.copySync(path.join(this.projectDir, 'include'), path.join(moduleDir, 'include'));
	fs.createReadStream(path.join(this.projectDir, 'manifest')).pipe(fs.createWriteStream(path.join(moduleDir, 'manifest')));
	fs.createReadStream(path.join(this.projectDir, 'timodule.xml')).pipe(fs.createWriteStream(path.join(moduleDir, 'timodule.xml')));

	// Whatever files in platform directory will be copied into build/windows directory during app build
	var platformOverrideDir = path.join(this.projectDir, 'platform');
	if (fs.existsSync(platformOverrideDir)) {
		fs.copySync(platformOverrideDir, path.join(moduleDir, 'platform'));
		var readme = path.join(moduleDir, 'platform', 'README.md');
		if (fs.existsSync(readme)) {
			fs.unlinkSync(readme); // We don't need README.md
		}
	}

	// copy compiled libraries
	types.forEach(function (type, index) {
		_t.manifest.architectures.split(' ').forEach(function (arch) {
			var moduleProjectDir = path.join(_t.projectDir, type + '.' + vs_architectures[arch]);

			if (!fs.existsSync(moduleProjectDir)) {
				_t.logger.debug('Skipping ' + moduleProjectDir);
				return;
			}

			var moduleSrc = path.join(moduleProjectDir, configuration),
				moduleDst = path.join(moduleDir, typesMin[index], arch);

			// We may have built in temp because of long path issues!
			// Check to see if the dll exists in normal spot, if not, fall back to trying temp location!
			if (!fs.existsSync(path.join(moduleSrc, projectname) + '.dll')) {
				var home = process.env.HOME || process.env.USERPROFILE || process.env.APPDATA,
					ti_home = path.join(home, '.titanium'),
					tempBuildDir = path.join(ti_home, 'vsbuild');

				moduleSrc = path.join(tempBuildDir, path.basename(path.dirname(_t.projectDir)), path.basename(moduleProjectDir), configuration);
			}

			// create module directory
			fs.ensureDirSync(path.join(moduleDir, typesMin[index], arch));

			// Copy all "known" files as we may have more dependencies
			fs.readdirSync(moduleSrc).forEach(function (depfile) {
				var depfileL = depfile.toLowerCase();
				if (depfileL.endsWith('.dll') || depfileL.endsWith('.winmd') || depfileL.endsWith('.lib')) {
					fs.createReadStream(path.join(moduleSrc, depfile)).pipe(fs.createWriteStream(path.join(moduleDst, depfile)));
				}
			});

			// copy one of export.hpp
			var export_file     = projectname + '_export.h',
				export_hpp_from = path.join(moduleProjectDir, export_file),
				export_hpp_to   = path.join(moduleDir, 'include', export_file);
			if (!fs.existsSync(export_hpp_to)) {
				fs.createReadStream(export_hpp_from).pipe(fs.createWriteStream(export_hpp_to));
			}
		});
	});
	next();
};

WindowsModuleBuilder.prototype.packageZip = function packageZip(next) {
	var buildDir = path.join(this.projectDir, 'build'),
		moduleDir = path.join(buildDir, this.manifest.moduleid, this.manifest.version),
		_t = this;

	// create zip
	var zipName = _t.manifest.moduleid + '-windows-' + _t.manifest.version + '.zip',
		destName = path.join(_t.projectDir, zipName),
		output   = fs.createWriteStream(destName),
		archive = archiver('zip');

	_t.logger.info('Creating module zip');
	_t.logger.info('Writing module zip: ' + destName.cyan);

	archive.on('error', function (err) {
		throw err;
	});
	output.on('close', function () {
		next();
	});

	archive.pipe(output);

	walkdir(moduleDir, function (err, files) {
		if (err) {
			throw err;
		}
		for (var i = 0; i < files.length; i++) {
			var file = files[i];
			var relative_path = path.join('modules', 'windows', _t.manifest.moduleid, _t.manifest.version, file.relative);
			if (file.stats.isFile()) {
				_t.logger.debug('Packing: ' + JSON.stringify(relative_path, null, 2));
				archive.append(fs.createReadStream(file.path), { name: relative_path });
			}
		}
		archive.finalize();
	});

};

function selectVisualStudio(data) {
	var version;
	if (data.cli.argv.hasOwnProperty('vs-target')) {
		version = data.cli.argv['vs-target'];
	} else if (data.windowsInfo && data.windowsInfo.selectedVisualStudio) {
		version = data.windowsInfo.selectedVisualStudio.version;
	}

	if (version == '12.0') {
		return 'Visual Studio 12 2013';
	} else if (version == '14.0') {
		return 'Visual Studio 14 2015';
	} else if (/^Visual Studio \w+ 2017/.test(version)) {
		return 'Visual Studio 15 2017';
	} else {
		return 'Visual Studio 14 2015';
	}
}

function rmdir(dirPath, fs, path, logger, removeSelf) {
	var files;
	try {
		files = fs.readdirSync(dirPath);
	} catch (e) {
		return;
	}
	if (files.length > 0) {
		for (var i = 0; i < files.length; i++) {
			var filePath = path.join(dirPath, files[i]);
			if (fs.statSync(filePath).isFile()) {
				fs.unlinkSync(filePath);
			} else {
				rmdir(filePath, fs, path, logger, true);
			}
		}
	}
	if (removeSelf) {
		fs.rmdirSync(dirPath);
	}
}

function runCmake(data, platform, arch, sdkVersion, next) {
	var logger = data.logger,
		generatorName = selectVisualStudio(data) + (arch === 'ARM' ? ' ARM' : ''),
		cmakeProjectName = (sdkVersion === '10.0' ? 'Windows10' : platform) + '.' + arch,
		cmakeWorkDir = path.resolve(data.projectDir, cmakeProjectName);

	if (!data.cli.argv.hasOwnProperty('run-cmake') && fs.existsSync(cmakeWorkDir)) {
		return next();
	}

	logger.debug('Run CMake on ' + cmakeWorkDir);

	if (fs.existsSync(cmakeWorkDir)) {
		rmdir(cmakeWorkDir, fs, path, logger, true);
	}

	fs.mkdirSync(cmakeWorkDir);

	var targetSdkVersion = sdkVersion;
	if (sdkVersion === '10.0' && data.targetPlatformSdkVersion) {
		targetSdkVersion = data.targetPlatformSdkVersion;
	}

	var cmakeArg = [
		'-G', generatorName,
		'-DCMAKE_SYSTEM_NAME=' + platform,
		'-DCMAKE_SYSTEM_VERSION=' + targetSdkVersion,
		'-DCMAKE_BUILD_TYPE=Debug',
		'-DHAL_RENAME_AXWAYHAL=ON',
		path.resolve(data.projectDir)
	];

	logger.debug(JSON.stringify(cmakeArg, null, 2));

	var p = spawn(path.join(data.titaniumSdkPath, 'windows', 'cli', 'vendor', 'cmake', 'bin', 'cmake.exe'),
    	cmakeArg,
		{
			cwd: cmakeWorkDir
		});
	p.on('error', function (err) {
		logger.error(cmake);
		logger.error(err);
	});
	p.stdout.on('data', function (data) {
		logger.info(data.toString().trim());
	});
	p.stderr.on('data', function (data) {
		logger.warn(data.toString().trim());
	});
	p.on('close', function (code) {
		if (code != 0) {
			process.exit(1); // Exit with code from cmake?
		}
		next();
	});
}

(function (windowsModuleBuilder) {
	exports.config   = windowsModuleBuilder.config.bind(windowsModuleBuilder);
	exports.validate = windowsModuleBuilder.validate.bind(windowsModuleBuilder);
	exports.run      = windowsModuleBuilder.run.bind(windowsModuleBuilder);
}(new WindowsModuleBuilder(module)));
