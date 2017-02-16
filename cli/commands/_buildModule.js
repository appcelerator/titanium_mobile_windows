/**
* Windows module build command.
*
* @module cli/_buildModule
*
* @copyright
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
*
* @license
* Licensed under the terms of the Apache Public License
* Please see the LICENSE included with this distribution for details.
*/

var archiver = require('archiver'),
	async = require('async'),
	appc = require('node-appc'),
	Builder = require('titanium-sdk/lib/builder'),
	DOMParser = require('xmldom').DOMParser,
	fs = require('fs'),
	os = require('os'),
	wrench = require('wrench'),
	path = require('path'),
	windowslib = require('windowslib'),
	util = require('util'),
	spawn = require('child_process').spawn,
	defaultTypes = ['WindowsPhone', 'WindowsStore', 'Windows10'],
	types = defaultTypes.slice(0),
	typesMin = ['phone', 'store', 'win10'],
	configuration = 'Release',
	EventEmitter = require('events').EventEmitter,
	vs_architectures = {ARM:'ARM', x86:'Win32'}; // x86 -> Win32 mapping

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
};

WindowsModuleBuilder.prototype.run = function run(logger, config, cli, finished) {
	Builder.prototype.run.apply(this, arguments);

	this.cli = cli;
	this.logger = logger;

	appc.async.series(this, [
		function(next) {
			cli.scanHooks(path.join(cli.argv['project-dir'], 'plugins', 'hooks'));
			next();
		},
		function (next) {
			cli.emit('build.module.pre.construct', this, next);
		},

		'doAnalytics',
		'initialize',
		'loginfo',

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
		dir: cli.argv['project-dir'],
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

	windowslib.detect(function (err, windowsInfo) {
		assertIssue(windowsInfo.issues, 'WINDOWS_VISUAL_STUDIO_NOT_INSTALLED');
		assertIssue(windowsInfo.issues, 'WINDOWS_MSBUILD_ERROR');
		assertIssue(windowsInfo.issues, 'WINDOWS_MSBUILD_TOO_OLD');

		if (!windowsInfo.selectedVisualStudio) {
			logger.error('Unable to find a supported Visual Studio installation');
			process.exit(1);
		}

		_t.windowsInfo = windowsInfo;

		next();
	});
};

WindowsModuleBuilder.prototype.loginfo = function loginfo(next) {
	console.log('--- WindowsModuleBuilder loginfo');

	this.logger.info('Visual Studio version: ' + this.windowsInfo.selectedVisualStudio.version.cyan);
	this.logger.info('MSBuild version: ' + this.windowsInfo.selectedVisualStudio.msbuildVersion.cyan);
	this.logger.info('Project directory: ' + this.projectDir.cyan);

	next();
};

WindowsModuleBuilder.prototype.compileModule = function compileModule(next) {
	var _t = this;

	function build(sln, config, arch, next) {
		var nativeAssetsDir = path.dirname(sln),
			platformTarget  = path.basename(nativeAssetsDir),
			vcxproj = path.join(nativeAssetsDir, _t.manifest.moduleIdAsIdentifier+'.vcxproj'),
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
			fs.existsSync(buildPath) && wrench.rmdirSyncRecursive(buildPath);
			// make sure destination exists
			fs.existsSync(buildPath) || wrench.mkdirSyncRecursive(buildPath);
			wrench.copyDirSyncRecursive(nativeAssetsDir, buildPath, {
				forceDelete: true
			});
			sln = path.join(buildPath, _t.manifest.moduleIdAsIdentifier+'.vcxproj');
		}

		var p = spawn(_t.windowsInfo.selectedVisualStudio.vcvarsall, [
			'&&', 'MSBuild', '/p:Platform=' + arch, '/p:Configuration=' + config, sln
		]);
		p.stdout.on('data', function (data) {
			var line = data.toString().trim();
			if (line.indexOf('error ') >= 0) {
				_t.logger.warn(line);
			}
			else if (line.indexOf('warning ') >= 0) {
				_t.logger.warn(line);
			}
			else if (line.indexOf(':\\') === -1) {
				_t.logger.debug(line);
			}
			else {
				_t.logger.trace(line);
			}
		});
		p.stderr.on('data', function (data) {
			_t.logger.error(data.toString().trim());
		});
		p.on('close', function (code) {
			if (code != 0) {
				process.exit(code);
			}
			next();
		});
	}

	// TIMOB-23557
	// read timodule.xml and get configuration
	var timodule = path.join(_t.projectDir, 'timodule.xml');
	if (fs.existsSync(timodule)) {
		var ti_dom  = new DOMParser().parseFromString(fs.readFileSync(timodule, 'utf8').toString()),
			ti_root = ti_dom.getElementsByTagName('windows');
		if (ti_root.length > 0) {
			var win_items = ti_root.item(0);
			appc.xml.forEachElement(win_items, function (item) {
				if (item.tagName == 'manifest') {
					appc.xml.forEachElement(item, function(node) {
						if (node.tagName == 'uses-sdk') {
							var sdk_version = appc.xml.getAttr(node, 'targetSdkVersion');
							_t.logger.info('targetSdkVersion: ' + sdk_version);
							// Remove Windows10 target only when it targets to 8.1 explicitly
							if (sdk_version == '8.1') {
								types = defaultTypes.slice(0, 2);
							} else if (sdk_version == '10.0') {
								types    = ['Windows10'];
								typesMin = ['win10'];
							}
						}
					});
				}
			});
		}
	}

	// compile module projects
	var archs = _t.manifest.architectures.split(' ');
	async.eachSeries(types, function(type, next_type) {
		async.eachSeries(archs, function(arch, next_arch) {
			var architecture = vs_architectures[arch],
				sln = path.resolve(_t.projectDir, type+'.'+architecture, _t.manifest.moduleIdAsIdentifier+'.sln');

			build(sln, configuration, architecture, next_arch);
		}, function(err) {
			if (err) {
				throw err;
			}
			next_type();
		});
	}, function(err) {
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
  fs.readdir(dirpath, function(err, list) {
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
      fs.stat(filepath, function(err, stats) {
        results.push({
          path: filepath,
          relative: path.relative(base, filepath).replace(/\\/g, '/'),
          stats: stats
        });
        if (stats && stats.isDirectory()) {
          walkdir(filepath, base, function(err, res) {
            results = results.concat(res);
            next();
          });
        } else {
          next();
        }
      });
    })();
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
	if (fs.existsSync(moduleDir)) {
		wrench.rmdirSyncRecursive(moduleDir);
	}
	wrench.mkdirSyncRecursive(moduleDir);

	// copy necesary folders and files
	var parent_folders = ['documentation', 'example', 'assets'],
		parent_files   = ['LICENSE'];
	parent_folders.forEach(function(folder) {
		var from = path.join(_t.projectDir, '..', folder);
		if (fs.existsSync(from)) {
			wrench.copyDirSyncRecursive(from, path.join(moduleDir, folder));
		}
	});
	parent_files.forEach(function(filename){
		var from = path.join(_t.projectDir, '..', filename),
			to   = path.join(moduleDir, filename);
		if (fs.existsSync(from) && !fs.existsSync(to)) {
			fs.createReadStream(from).pipe(fs.createWriteStream(to));
		}
	});
	wrench.copyDirSyncRecursive(path.join(this.projectDir, 'include'), path.join(moduleDir, 'include'));
	fs.createReadStream(path.join(this.projectDir, 'manifest')).pipe(fs.createWriteStream(path.join(moduleDir, 'manifest')));
	fs.createReadStream(path.join(this.projectDir, 'timodule.xml')).pipe(fs.createWriteStream(path.join(moduleDir, 'timodule.xml')));

	// copy compiled libraries
	types.forEach(function(type, index) {
		_t.manifest.architectures.split(' ').forEach(function(arch) {
			var moduleProjectDir = path.join(_t.projectDir, type+'.'+vs_architectures[arch]);

			if (!fs.existsSync(moduleProjectDir)) {
				_t.logger.debug('Skipping '+moduleProjectDir);
				return;
			}

			var moduleSrc = path.join(moduleProjectDir, configuration, projectname),
				moduleDst = path.join(moduleDir, typesMin[index], arch, projectname);

			// We may have built in temp because of long path issues!
			// Check to see if the dll exists in normal spot, if not, fall back to trying temp location!
			if (!fs.existsSync(moduleSrc + '.dll')) {
				var home = process.env.HOME || process.env.USERPROFILE || process.env.APPDATA,
				    ti_home = path.join(home, '.titanium'),
				    tempBuildDir = path.join(ti_home, 'vsbuild');

				moduleSrc = path.join(tempBuildDir, path.basename(path.dirname(_t.projectDir)), path.basename(moduleProjectDir), configuration, projectname);
			}

			// create module directory
			wrench.mkdirSyncRecursive(path.join(moduleDir, typesMin[index], arch));

			// Dynamic-Link Library
			fs.createReadStream(moduleSrc+'.dll').pipe(fs.createWriteStream(moduleDst+'.dll'));

			// Windows Metadata
			fs.createReadStream(moduleSrc+'.winmd').pipe(fs.createWriteStream(moduleDst+'.winmd'));

			// Library
			fs.createReadStream(moduleSrc+'.lib').pipe(fs.createWriteStream(moduleDst+'.lib'));

			// copy one of export.hpp
			var export_file     = projectname+'_export.h',
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
	_t.logger.info('Writing module zip: '+ destName.cyan);

	archive.on('error', function(err) {
		throw err;
	});
	output.on('close', function() {
		next();
	});

	archive.pipe(output);

	walkdir(moduleDir, function(err, files) {
		if (err) {
			throw err;
		}
		for (var i = 0; i < files.length; i++) {
			var file = files[i];
			var relative_path = path.join('modules', 'windows', _t.manifest.moduleid, _t.manifest.version, file.relative);
			if (file.stats.isFile()) {
				_t.logger.debug('Packing: '+JSON.stringify(relative_path, null, 2));
				archive.append(fs.createReadStream(file.path), {name: relative_path });
			}
		}	
		archive.finalize();
	});

};

(function (windowsModuleBuilder) {
	exports.config   = windowsModuleBuilder.config.bind(windowsModuleBuilder);
	exports.validate = windowsModuleBuilder.validate.bind(windowsModuleBuilder);
	exports.run      = windowsModuleBuilder.run.bind(windowsModuleBuilder);
}(new WindowsModuleBuilder(module)));