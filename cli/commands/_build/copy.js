'use strict';

const appc = require('node-appc');
const async = require('async');
const cleanCSS = require('clean-css');
const fs = require('fs-extra');
const crypto = require('crypto');
const jsanalyze = require('node-titanium-sdk/lib/jsanalyze');
const path = require('path');
const ti = require('node-titanium-sdk');
const __ = appc.i18n(__dirname).__;

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
		// if already exists, wipe it. ensure it exists
		fs.emptyDirSync(this.originalBuildDir);
		// Now copy this.buildDir into this.originalBuildDir
		fs.copySync(this.buildDir, this.originalBuildDir, {
			overwrite: true
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
		jsBootstrapFiles = [],
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
		fs.ensureDirSync(d);

		if (fs.existsSync(to)) {
			// Don't overwrite C++ source files because it causes unnecessary recompile
			if (/\.(cpp|hpp|h)$/.test(to)) {
				_t.logger.debug(__('Skipping %s', to.cyan));
				if (next) {
					next();
				}
				return;
			}
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
				fs.ensureDirSync(destDir);

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

				// Square310x310Logo
				{
					description: 'Square310x310Logo.png - Used for logo',
					file: path.join(appIconSetDir, 'Square310x310Logo.png'),
					width: 310,
					height: 310,
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
			],
			md5 = function (file) {
				return crypto
					.createHash('md5')
					.update(fs.readFileSync(file), 'binary')
					.digest('hex');
			};

		/*
		 * Look for basename.png, if it does not exist then look for .scale-100.png because it should have same dimension
		 */
		function windowsScaledPNGAssetSelect(filename) {
			var extname = path.extname(filename),
				basename = filename.substr(0, filename.length - extname.length),
				scaledname = basename + '.scale-100' + extname;
			if (fs.existsSync(scaledname)) {
				return scaledname;
			}
			return filename;
		}

		// if the app icon does not exist then check if it exists in the project root
		// if it does not exist in project root then generate the missing icon
		for (var i = missingIcons.length - 1; i >= 0; i--) {

			// if file does not exist then look for .scale-100.png
			// because it should have same dimension
			missingIcons[i].file = windowsScaledPNGAssetSelect(missingIcons[i].file);

			var icon = missingIcons[i],
				platformResourceIcon = path.join(this.projectDir, 'Resources', 'Windows', path.basename(icon.file)),
				alloyPlatformResourceIcon = path.join(this.projectDir, 'app', 'assets', 'windows', path.basename(icon.file)),
				resourceIcon = path.join(this.projectDir, 'Resources', path.basename(icon.file));
			if (fs.existsSync(platformResourceIcon)) {
				if (fs.existsSync(icon.file) && md5(icon.file) === md5(platformResourceIcon)) {
					this.logger.debug(__('%s already exists, skipping...', icon.file));
				} else {
					copyFile.call(this, platformResourceIcon, icon.file);
				}
				missingIcons.splice(i, 1);
			} else if (fs.existsSync(alloyPlatformResourceIcon)) {
				if (fs.existsSync(icon.file) && md5(icon.file) === md5(alloyPlatformResourceIcon)) {
					this.logger.debug(__('%s already exists, skipping...', icon.file));
				} else {
					copyFile.call(this, alloyPlatformResourceIcon, icon.file);
				}
				missingIcons.splice(i, 1);
			} else if (fs.existsSync(resourceIcon)) {
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

		// Copy all of the Titanium SDK's core JS files shared by all platforms.
		function (cb) {
			const src = path.join(this.titaniumSdkPath, 'common', 'Resources');
			_t.logger.debug(__('Copying %s', src.cyan));
			copyDir.call(this, {
				src: src,
				dest: this.buildTargetAssetsDir,
				ignoreRootDirs: ti.availablePlatformsNames
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
			var src = path.join(this.platformPath, 'lib', 'HAL', this.cmakePlatformAbbrev, this.arch, 'AXWAYHAL.dll');
			copyFile.call(this,
				src,
				path.join(this.buildDir, 'lib', 'AXWAYHAL.dll'),
				cb);
		},

		createAppIconSet,

		// Remove SplashScreen.png if scaled assets (.scale-100.png) exists.
		function (cb) {
			var basename    = 'SplashScreen.scale-100.png',
				candidates = [
					path.join(this.projectDir, 'Resources', 'Windows', basename),
					path.join(this.projectDir, 'app', 'assets', 'windows', basename),
					path.join(this.projectDir, 'Resources', basename)
				],
				splashAsset = path.join(this.buildDir, 'Assets', 'SplashScreen.png');

			for (var i = 0; i < candidates.length; i++) {
				if (fs.existsSync(candidates[i]) && fs.existsSync(splashAsset)) {
					this.logger.debug('Removing SplashScreen.png as scaled-100 asset found.');
					fs.unlinkSync(splashAsset);
					break;
				}
			}
			cb();
		}
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

	this.modules.forEach(function (module) {
		// copy any module specific resources here
		tasks.push(function (cb) {
			copyDir.call(this, {
				src: path.join(module.modulePath, 'platform', 'Assets'),
				dest: path.join(this.buildTargetAssetsDir)
			}, cb);
		});
	}, this);

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

		// copy js files into assets directory and minify if needed
		this.logger.info(__('Processing JavaScript files'));
		appc.async.series(this, Object.keys(jsFiles).map(function (id) {
			return function (done) {
				var from = jsFiles[id],
					to = path.join(this.buildTargetAssetsDir, id),
					t_ = this;

				if (htmlJsFiles[id]) {
					// this js file is referenced from an html file, so don't minify or encrypt
					return copyFile.call(this, from, to, done);
				}

				// A JS file ending with "*.bootstrap.js" is to be loaded before the "app.js".
				// Add it as a require() compatible string to bootstrap array if it's a match.
				const bootstrapPath = id.substr(0, id.length - 3);  // Remove the ".js" extension.
				if (bootstrapPath.endsWith('.bootstrap')) {
					jsBootstrapFiles.push(bootstrapPath);
				}

				// we have a js file that may be minified or encrypted

				// if we're encrypting the JavaScript, copy the files to the assets dir
				// for processing later
				if (this.encryptJS) {
					to = path.join(this.buildTargetAssetsDir, id);
					jsFilesToEncrypt.push(id);
				}

				try {
					this.cli.createHook('build.windows.analyzeJsFile', this, function (from, to, cb) {
						this.cli.createHook('build.windows.copyResource', this, function (from, to, cb) {
							// parse the AST
							const originalContents = fs.readFileSync(from).toString();
							const r = jsanalyze.analyzeJs(originalContents, {
								filename: from,
								minify: this.minifyJS,
								transpile: this.transpile,
								sourceMap: this.sourceMaps || this.deployType === 'development',
								targets: {
									safari: this.packageJson.safari // use equivalent version of safari that we declare in package.json
								},
								resourcesDir: this.buildTargetAssetsDir,
								logger: t_.logger
							});
							const newContents = r.contents;

							// we want to sort by the "to" filename so that we correctly handle file overwriting
							this.tiSymbols[to] = r.symbols;

							this.cli.createHook('build.windows.compileJsFile', this, function (r, from, to, cb2) {
								const dir = path.dirname(to);
								fs.ensureDirSync(dir);

								if (newContents === originalContents) {
									copyFile.call(this, from, to, cb2);
								} else {
									// we've already read in the file, so just write the original contents
									this.logger.debug(__('Copying %s => %s', from.cyan, to.cyan));
									fs.writeFile(to, newContents, cb2);
								}
							})(r, from, to, cb);
						})(from, to, cb);
					})(from, to, done);
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
				appInfo
				= {
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

			// Write the "bootstrap.json" file, even if the bootstrap array is empty.
			// Note: An empty array indicates the app has no bootstrap files.
			const bootstrapJsonRelativePath = path.join('ti.internal', 'bootstrap.json'),
				bootstrapJsonAbsolutePath = path.join(this.buildTargetAssetsDir, bootstrapJsonRelativePath);
			fs.ensureDirSync(path.dirname(bootstrapJsonAbsolutePath));
			fs.writeFileSync(bootstrapJsonAbsolutePath, JSON.stringify({ scripts: jsBootstrapFiles }));
			this.encryptJS && jsFilesToEncrypt.push(bootstrapJsonRelativePath);

			if (!jsFilesToEncrypt.length) {
				// nothing to encrypt, continue
				return next();
			}

			this.processEncryption(next);
		});
	});
}
