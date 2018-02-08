var appc = require('node-appc'),
	async = require('async'),
	cleanCSS = require('clean-css'),
	fs = require('fs'),
	crypto = require('crypto'),
	jsanalyze = require('node-titanium-sdk/lib/jsanalyze'),
	path = require('path'),
	ti = require('node-titanium-sdk'),
	wrench = require('wrench'),
	babylon = require('babylon'),
	types = require('babel-types'),
	traverse = require('babel-traverse').default,
	__ = appc.i18n(__dirname).__;

/*
 Public API.
 */
exports.mixin = mixin;

/*
 Implementation.
 */
function mixin(WindowsBuilder) {
	WindowsBuilder.prototype.copyResultsToProject = copyResultsToProject;
	WindowsBuilder.prototype.copyResources = copyResources;
}

// Copy to original location!
/**
 * Copies the build directory back to the project's build directory if we compiled in temp.
 *
 * @param {Function} next - A function to call after the build manifest has been written.
 */
function copyResultsToProject(next) {
	if (this.originalBuildDir) {
		this.logger.info(__('Copying results back to project build directory'));
		// if already exists, wipe it
		fs.existsSync(this.originalBuildDir) && wrench.rmdirSyncRecursive(this.originalBuildDir);
		// make sure destination exists
		fs.existsSync(this.originalBuildDir) || wrench.mkdirSyncRecursive(this.originalBuildDir);
		// Now copy this.buildDir into this.originalBuildDir
		wrench.copyDirSyncRecursive(this.buildDir, this.originalBuildDir, {
			forceDelete: true
		});
	}
	next();
}

/**
 * Copies files from the project's "Resources", "Resources\windows", and "platform\windows"
 * directories into the generated Visual Studio project.
 *
 * @param {Function} next - A function to call after the files have been copied.
 */
function copyResources(next) {
	/*
	 TODO: This function is supposed to copy the files from the "Resources", "Resources\windows",
	 and "platform\windows" directories into the generated Visual Studio project.

	 Files should be copied into the this.buildTargetAssetsDir directory.

	 This is commented out because it actually does more than just copies files.

	 It also:

	 * makes sure an app icon exists or copies the default one from the Titanium SDK
	 * makes sure a splash screen exists or copies the default one from the Titanium SDK
	 - this may not be necessary on Windows Phone
	 * when copying an HTML file, scan it for all .js files and exclude them from being
	 encrypted
	 - this may not be necessary if you can override the WebView's resource loader and
	 return the correct .js file
	 * css files are minified with the clean-css Node.js module
	 * all JavaScript files discovered, but not copied. we later iterate over this distinct
	 list of js files and call jsanalyze.analyzeJsFile() to be scan for Titanium
	 namespaces (so we can determine which modules we need to compile in) and minify the
	 js code
	 - when encrypting js is enabled (test or production build), then we call titanium_prep

	 Titanium Windows may support encrypting more than just JavaScript files. If that is
	 the case, scan the Resources diretory for files to be encrypted and build a list. Only
	 copy files you are not going to encrypt. Then you'll need to perform the actual
	 encryption at the end of the last callback in this function.
	 */

	var ignoreDirs = this.ignoreDirs,
		ignoreFiles = this.ignoreFiles,
		extRegExp = /\.(\w+)$/,
		jsFiles = this.jsFiles = {},
		jsFilesToEncrypt = this.jsFilesToEncrypt = [],
		htmlJsFiles = this.htmlJsFiles = {},
		_t = this;

	function copyDir(opts, callback) {
		if (opts && opts.src && fs.existsSync(opts.src) && opts.dest) {
			opts.origSrc = opts.src;
			opts.origDest = opts.dest;
			recursivelyCopy(opts.src, opts.dest, opts.ignoreRootDirs, opts, callback);
		} else {
			callback();
		}
	}

	function copyFile(from, to, next) {
		var d = path.dirname(to);
		fs.existsSync(d) || wrench.mkdirSyncRecursive(d);

		if (fs.existsSync(to)) {
			_t.logger.debug(__('Overwriting file %s', to.cyan));
		}

		this.logger.debug(__('Copying %s => %s', from.cyan, to.cyan));
		if (next) {
			fs.readFile(from, function (err, data) {
				if (err) {
					throw err;
				}
				fs.writeFile(to, data, next);
			});
		} else {
			fs.writeFileSync(to, fs.readFileSync(from));
		}
	}

	/*
	 * Check JS syntax and report errors. Mostly copied from jsanalyze
	 */
	function reportJSErrors(filename, contents, ex) {
		var errmsg = [__('Failed to parse %s', filename)];
		if (ex.line) {
			errmsg.push(__('%s [line %s, column %s]', ex.message, ex.line, ex.col));
		} else {
			errmsg.push(ex.message);
		}
		try {
			contents = contents.split('\n');
			if (ex.line && ex.line <= contents.length) {
				errmsg.push('');
				errmsg.push('    ' + contents[ex.line - 1].replace(/\t/g, ' '));
				if (ex.col) {
					var i = 0,
						len = ex.col,
						buffer = '    ';
					for (; i < len; i++) {
						buffer += '-';
					}
					errmsg.push(buffer + '^');
				}
				errmsg.push('');
			}
		} catch (ex2) {}
		return errmsg.join('\n');
	}

	function recursivelyCopy(src, dest, ignoreRootDirs, opts, done) {
		var files;
		if (fs.statSync(src).isDirectory()) {
			files = fs.readdirSync(src);
		} else {
			// we have a file, so fake a directory listing
			files = [path.basename(src)];
			src = path.dirname(src);
		}

		async.whilst(
			function () {
				return files.length;
			},

			function (next) {
				var filename = files.shift(),
					destDir = dest,
					from = path.join(src, filename),
					to = path.join(destDir, filename);

				// check that the file actually exists
				if (!fs.existsSync(from)) {
					return next();
				}

				var isDir = fs.statSync(from).isDirectory();

				// check if we are ignoring this file
				if ((isDir && ignoreRootDirs && ignoreRootDirs.indexOf(filename) !== -1) || (isDir ? ignoreDirs : ignoreFiles).test(filename)) {
					_t.logger.debug(__('Ignoring %s', from.cyan));
					return next();
				}

				// if this is a directory, recurse
				if (isDir) {
					return recursivelyCopy.call(_t, from, path.join(destDir, filename), null, opts, next);
				}

				// we have a file, now we need to see what sort of file

				// if the destination directory does not exists, create it
				fs.existsSync(destDir) || wrench.mkdirSyncRecursive(destDir);

				var ext = filename.match(extRegExp);

				switch (ext && ext[1]) {
					case 'css':
						// if we encounter a css file, check if we should minify it
						if (_t.minifyCSS) {
							_t.logger.debug(__('Copying and minifying %s => %s', from.cyan, to.cyan));
							fs.readFile(from, function (err, data) {
								if (err) {
									throw err;
								}
								fs.writeFile(to, cleanCSS.process(data.toString()), next);
							});
						} else {
							copyFile.call(_t, from, to, next);
						}
						break;

					case 'html':
						// find all js files referenced in this html file
						var relPath = from.replace(opts.origSrc, '').replace(/\\/g, '/').replace(/^\//, '').split('/');
						relPath.pop(); // remove the filename
						relPath = relPath.join('/');
						jsanalyze.analyzeHtmlFile(from, relPath).forEach(function (file) {
							htmlJsFiles[file] = 1;
						});

						_t.cli.createHook('build.windows.copyResource', _t, function (from, to, cb) {
							copyFile.call(_t, from, to, cb);
						})(from, to, next);
						break;

					case 'js':
						if (opts && opts.trackJS === false) {
							_t.cli.createHook('build.windows.copyResource', _t, function (from, to, cb) {
								copyFile.call(_t, from, to, cb);
							})(from, to, next);
							break;
						}

						// track each js file so we can copy/minify later

						// we use the destination file name minus the path to the assets dir as the id
						// which will eliminate dupes
						var id = to.replace(opts.origDest, '').replace(/\\/g, '/').replace(/^\//, '');

						if (!jsFiles[id] || !opts || !opts.onJsConflict || opts.onJsConflict(from, to, id)) {
							jsFiles[id] = from;
						}

						next();
						break;

					default:
						// normal file, just copy it into the build/windows/Assets directory
						_t.cli.createHook('build.windows.copyResource', _t, function (from, to, cb) {
							copyFile.call(_t, from, to, cb);
						})(from, to, next);
				}
			},

			done
		);
	}

	function createAppIconSet(next) {
		var appIconSetDir = path.join(this.buildDir, 'Assets'),
			missingIcons = [

			// Square24x24Logo
			{
				description: 'Square24x24Logo.png - Used for badge',
				file: path.join(appIconSetDir, 'Square24x24Logo.png'),
				width: 24,
				height: 24,
				required: true
			},

			// Square44x44Logo
			{
				description: 'Square44x44Logo.png - Used for logo',
				file: path.join(appIconSetDir, 'Square44x44Logo.png'),
				width: 44,
				height: 44,
				required: true
			},

			// Square71x71Logo
			{
				description: 'Square71x71Logo.png - Used for logo',
				file: path.join(appIconSetDir, 'Square71x71Logo.png'),
				width: 71,
				height: 71,
				required: true
			},

			// Square150x150Logo
			{
				description: 'Square150x150Logo.png - Used for logo',
				file: path.join(appIconSetDir, 'Square150x150Logo.png'),
				width: 150,
				height: 150,
				required: true
			},

			// Logo.png
			{
				description: 'Logo.png - Used for logo',
				file: path.join(appIconSetDir, 'Logo.png'),
				width: 150,
				height: 150,
				required: true
			},

			// StoreLogo.png
			{
				description: 'StoreLogo.png - Used for logo',
				file: path.join(appIconSetDir, 'StoreLogo.png'),
				width: 50,
				height: 50,
				required: true
			},

			// SmallLogo.png
			{
				description: 'SmallLogo.png - Used for logo',
				file: path.join(appIconSetDir, 'SmallLogo.png'),
				width: 30,
				height: 30,
				required: true
			}

			// TODO: Generate SplashScreen.scale-100.png?
		],
		md5 = function (file) {
			return crypto
				.createHash('md5')
				.update(fs.readFileSync(file), 'binary')
				.digest('hex')
		};

		// if the app icon does not exist then check if it exists in the project root
		// if it does not exist in project root then generate the missing icon
		for (var i = missingIcons.length - 1; i >= 0; i--) {
			var icon = missingIcons[i],
				platformResourceIcon = path.join(this.projectDir, 'Resources', 'Windows', path.basename(icon.file)),
				resourceIcon = path.join(this.projectDir, 'Resources', path.basename(icon.file));
			if (fs.existsSync(platformResourceIcon)) {
				if (fs.existsSync(icon.file) && md5(icon.file) === md5(platformResourceIcon)) {
					this.logger.debug(__('%s already exists, skipping...', icon.file));
				} else {
					copyFile.call(this, platformResourceIcon, icon.file);
				}
				missingIcons.splice(i, 1);
			} else {
				if (fs.existsSync(resourceIcon)) {
					if (fs.existsSync(icon.file) && md5(icon.file) === md5(resourceIcon)) {
						this.logger.debug(__('%s already exists, skipping...', icon.file));
					} else {
						copyFile.call(this, resourceIcon, icon.file);
					}
					missingIcons.splice(i, 1);
				} else {
					this.logger.debug(__('%s missing, generating...', icon.file));
				}
			}
		}

		this.generateAppIcons(missingIcons, next);
	}

	var tasks = [
		// First, copy template files for CMake/MSBuild FIXME Move these into subdir so we copy only ones we need!
		function (cb) {
			var src = path.join(this.platformPath, 'templates', 'build');
			copyDir.call(this, {
				src: src,
				dest: this.buildDir // throw into top-level build dir
			}, cb);
		},

		// Copy cmake folder over, with our helper scripts to find the bundled dependency libs
		function (cb) {
			var src = path.join(this.platformPath, 'templates', 'build', 'cmake');
			copyDir.call(this, {
				src: src,
				dest: path.join(this.buildDir, 'cmake')
			}, cb);
		},

		// Next task is to copy all files in the Resources directory, but ignore
		// any directory that is the name of a known platform
		function (cb) {
			var src = path.join(this.projectDir, 'Resources');
			copyDir.call(this, {
				src: src,
				dest: this.buildTargetAssetsDir,
				ignoreRootDirs: ti.availablePlatformsNames
			}, cb);
		},

		// next copy all files from the Windows specific Resources directory
		function (cb) {
			var src = path.join(this.projectDir, 'Resources', 'windows');
			copyDir.call(this, {
				src: src,
				dest: this.buildTargetAssetsDir
			}, cb);
		},

		// Copy all external libraries into lib folder
		function (cb) {
			var src = path.join(this.projectDir, 'lib', 'windows');
			copyDir.call(this, {
				src: src,
				dest: path.join(this.buildDir, 'lib')
			}, cb);
		},

		// Copy TitaniumKit and HAL dlls over into src folder
		function (cb) {
			var src = path.join(this.platformPath, 'lib', 'TitaniumKit', this.cmakePlatformAbbrev, this.arch, 'TitaniumKit.dll');
			copyFile.call(this,
				src,
				path.join(this.buildDir, 'lib', 'TitaniumKit.dll'),
				cb);
		},

		function (cb) {
			var src = path.join(this.platformPath, 'lib', 'HAL', this.cmakePlatformAbbrev, this.arch, 'HAL.dll');
			copyFile.call(this,
				src,
				path.join(this.buildDir, 'lib', 'HAL.dll'),
				cb);
		},

		createAppIconSet
	];

	// copy all commonjs modules
	this.commonJsModules.forEach(function (module) {
		// copy the main module
		tasks.push(function (cb) {
			copyDir.call(this, {
				trackJS: false,
				src: module.modulePath,
				dest: path.join(this.buildTargetAssetsDir, 'node_modules', module.id),
				onJsConflict: function (src, dest, id) {
					this.logger.error(__('There is a project resource "%s" that conflicts with a CommonJS module', id));
					this.logger.error(__('Please rename the file, then rebuild') + '\n');
					process.exit(1);
				}.bind(this)
			}, cb);
		});

		// copy the assets
		tasks.push(function (cb) {
			copyDir.call(this, {
				trackJS: false,
				src: path.join(module.modulePath, 'assets'),
				dest: path.join(this.buildTargetAssetsDir, 'node_modules', module.id, 'assets')
			}, cb);
		});
	});

	// this.modules.forEach(function (module) {
		// TODO: copy any module specific resources here
	// }, this);

	var platformPaths = [];
	// WARNING! This is pretty dangerous, but yes, we're intentionally copying
	// every file from platform/windows and all modules into the build dir
	this.modules.forEach(function (module) {
		platformPaths.push(path.join(module.modulePath, 'platform', 'windows'));
	});
	platformPaths.push(path.join(this.projectDir, this.cli.argv['platform-directory'] || 'platform', 'windows'));
	platformPaths.forEach(function (dir) {
		if (fs.existsSync(dir)) {
			tasks.push(function (cb) {
				copyDir.call(this, {
					src: dir,
					dest: this.buildDir
				}, cb);
			});
		}
	}, this);

	tasks.push(function (cb) {
		// fire a hook event so that hooks can copy additional resources
		this.cli.emit('build.windows.copyResources', this, cb);
	}.bind(this));

	appc.async.series(this, tasks, function (err, results) {

		if (err) {
			return next(err);
		}

		var templateDir = path.join(this.platformPath, 'templates', 'app', 'default', 'template', 'Resources', 'windows');

		// if an app icon hasn't been copied, copy the default one
		var destIcon = path.join(this.buildTargetAssetsDir, this.tiapp.icon);
		if (!fs.existsSync(destIcon)) {
			copyFile.call(this, path.join(templateDir, 'appicon.png'), destIcon);
		}

		var thirdpartyLibraries = this.hyperloopConfig.windows.thirdparty && Object.keys(this.hyperloopConfig.windows.thirdparty) || [];
		function hasWindowsAPI(node_value) {
			for (var i = 0; i < thirdpartyLibraries.length; i++) {
				if (node_value.indexOf(thirdpartyLibraries[i] + '.') === 0) {
					return true;
				}
			}
			return (node_value.indexOf('Windows.') === 0 || node_value.indexOf('System.') === 0);
		}

		// copy js files into assets directory and minify if needed
		this.logger.info(__('Processing JavaScript files'));
		appc.async.series(this, Object.keys(jsFiles).map(function (id) {
			return function (done) {
				var from = jsFiles[id],
					to = path.join(this.buildTargetAssetsDir, id),
					t_ = this;
				t_.native_types  = t_.native_types  || {};
				t_.native_events = t_.native_events || {};

				// Look for native requires here
				var fromContent = fs.readFileSync(from, {encoding: 'utf8'}),
					ast;
				try {
					ast = babylon.parse(fromContent, { filename: from, sourceType: 'module' });
				} catch (E) {
					t_.logger.error(reportJSErrors(from, fromContent, E));
					return next('Failed to parse JavaScript files.');
				}

				//
				// Compatibility Mode
				// Use 'built-in' type detection for older version of Hyperloop module (< 2.2.0)
				//
				if (!t_.useHyperloopBuilder) {
					traverse(ast, {
						CallExpression: {
							enter: function(path) {

								// if we're calling require with one string literal argument...
								// FIXME What if it is a requires, but not a string? What if it is a dynamically built string?
								if (types.isIdentifier(path.node.callee, { name: 'require' }) &&
										path.node.arguments && path.node.arguments.length == 1 &&
										types.isStringLiteral(path.node.arguments[0])) {
									// check if the required type is "native"
									var node_value = path.node.arguments[0].value;
									if (hasWindowsAPI(node_value)) {
										t_.logger.info("Detected native API reference: " + node_value);
										t_.native_types[node_value] = {name: node_value};
									}
								} else if (types.isMemberExpression(path.node.callee) && // are we calling 'addEventListener'?
										types.isIdentifier(path.node.callee.property, { name: 'addEventListener' }) &&
										path.node.arguments && path.node.arguments.length > 0 && // with at least one argument
										types.isStringLiteral(path.node.arguments[0]) && // first argument is a string literal
										types.isIdentifier(path.node.callee.object) // on some variable
										) {
									var event_name = path.node.arguments[0].value,  // record the event name
										binding = path.scope.getBinding(path.node.callee.object.name); // get binding for the receiver variable
									if (binding && // if we got the initial binding for the variable
											types.isVariableDeclarator(binding.path.node) && // and it declares the variable
											types.isNewExpression(binding.path.node.init) && // and it's assigned from a 'new' expression
											types.isIdentifier(binding.path.node.init.callee) // and the type is an identifier
											) {
										var ctor = path.scope.getBinding(binding.path.node.init.callee.name); // and it's the constructor variable
										if (ctor && ctor.path.node.init && ctor.path.node.init.arguments && ctor.path.node.init.arguments.length > 0) {
											var detectedConstructorType = ctor.path.node.init.arguments[0].value; // record the type of the constructor
											if (hasWindowsAPI(detectedConstructorType)) {
												var native_event = {
													name: event_name,
													type: detectedConstructorType,
													signature: event_name + '_' + detectedConstructorType.replace(/\./g, '_')
												};
												t_.native_events[native_event.signature] = native_event;
												t_.logger.info('Detected native API event: ' + native_event.name + ' for ' + detectedConstructorType);
											}
										}
									}
								}
							}
						}
					});
				}

				if (htmlJsFiles[id]) {
					// this js file is referenced from an html file, so don't minify or encrypt
					return copyFile.call(this, from, to, done);
				}

				// we have a js file that may be minified or encrypted

				// if we're encrypting the JavaScript, copy the files to the assets dir
				// for processing later
				if (this.encryptJS) {
					to = path.join(this.buildTargetAssetsDir, id);
					jsFilesToEncrypt.push(id);
				}

				try {
					this.cli.createHook('build.windows.analyzeJsFile', this, function (from, to, ast, traverse, types, cb) {
						this.cli.createHook('build.windows.copyResource', this, function (from, to, cb) {
							// parse the AST
							const originalContents = fs.readFileSync(from).toString();
							const r = jsanalyze.analyzeJs(originalContents, {
								filename: from,
								minify: this.minifyJS,
								transpile: this.transpile,
								targets: {
									safari: '10' // matches the version of jscore we use
								}
							});
							const newContents = r.contents;

							// we want to sort by the "to" filename so that we correctly handle file overwriting
							this.tiSymbols[to] = r.symbols;

							this.cli.createHook('build.windows.compileJsFile', this, function (r, from, to, cb2) {
								const dir = path.dirname(to);
								fs.existsSync(dir) || wrench.mkdirSyncRecursive(dir);

								if (newContents === originalContents) {
									copyFile.call(this, from, to, cb2);
								} else {
									// we've already read in the file, so just write the original contents
									this.logger.debug(__('Copying %s => %s', from.cyan, to.cyan));
									fs.writeFile(to, newContents, cb2);
								}
							})(r, from, to, cb);
						})(from, to, cb);
					})(from, to, ast, traverse, types, done);
				} catch (ex) {
					ex.message.split('\n').forEach(this.logger.error);
					this.logger.log();
					process.exit(1);
				}
			};
		}), function () {

			// write the properties file
			var appPropsFile = path.join(this.buildTargetAssetsDir, '_app_props_.json'),
				props = {};
			Object.keys(this.tiapp.properties).forEach(function (prop) {
				props[prop] = this.tiapp.properties[prop].value;
			}, this);
			this.tiapp.windows && Object.keys(this.tiapp.windows).forEach(function (prop) {
				// ignore appxmanifest
				if (prop !== 'manifest') {
					props[prop] = this.tiapp.windows[prop];
				}
			}, this);
			fs.writeFileSync(
				appPropsFile,
				JSON.stringify(props)
			);
			this.encryptJS && jsFilesToEncrypt.push('_app_props_.json');

			// write the app info file
			var appInfoFile = path.join(this.buildTargetAssetsDir, '_app_info_.json'),
				appInfo =
				{
					deployType: this.deployType,
					name: this.tiapp.name,
					id: this.tiapp.id,
					analytics: this.tiapp.analytics,
					publisher: this.tiapp.publisher,
					url: this.tiapp.url,
					version: this.buildVersion,
					description: this.tiapp.description,
					copyright: this.tiapp.copyright,
					guid: this.tiapp.guid,
					sdkVersion: this.cli && this.cli.sdk && this.cli.sdk.name
				};
			fs.writeFileSync(
				appInfoFile,
				JSON.stringify(appInfo)
			);
			this.encryptJS && jsFilesToEncrypt.push('_app_info_.json');

			if (!jsFilesToEncrypt.length) {
				// nothing to encrypt, continue
				return next();
			}

			this.processEncryption(next);
		});
	});
}
