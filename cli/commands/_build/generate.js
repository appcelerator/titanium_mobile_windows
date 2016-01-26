var appc = require('node-appc'),
	nativeTypeGenerator = require('../../lib/stub'),
	DOMParser = require('xmldom').DOMParser,
	fs = require('fs'),
	i18n = require('titanium-sdk/lib/i18n'),
	os = require('os'),
	ejs = require('ejs'),
	path = require('path'),
	ti = require('titanium-sdk'),
	wrench = require('wrench'),
	__ = appc.i18n(__dirname).__;

/*
 Public API.
 */
exports.mixin = mixin;

/*
 Implementation.
 */
function mixin(WindowsBuilder) {
	WindowsBuilder.prototype.generateI18N = generateI18N;
	WindowsBuilder.prototype.generateNativeWrappers = generateNativeWrappers;
	WindowsBuilder.prototype.generateModuleFinder = generateModuleFinder;
	WindowsBuilder.prototype.generateCmakeList = generateCmakeList;
	WindowsBuilder.prototype.generateAppxManifestForPlatform = generateAppxManifestForPlatform;
	WindowsBuilder.prototype.generateAppxManifest = generateAppxManifest;
	WindowsBuilder.prototype.addI18nVSResources = addI18nVSResources;
}

/**
 * Generates the i18n string resource files and adds them to the Visual Studio project.
 *
 * @param {Function} next - A function to call after the i18n files have been generated.
 */
function generateI18N(next) {
	this.logger.info(__('Generating i18n files'));

	var data = i18n.load(this.projectDir, this.logger, {
			ignoreDirs: this.ignoreDirs,
			ignoreFiles: this.ignoreFiles
		}),
		template = fs.readFileSync(path.join(this.platformPath, 'templates', 'build', 'Resources.resw')).toString();

	data.en || (data.en = {});
	data.en.app || (data.en.app = {});
	data.en.app.appname || (data.en.app.appname = this.tiapp.name);

	Object.keys(data).forEach(function (locale) {
		var destDir = path.join(this.buildTargetStringsDir, locale),
			dest = path.join(destDir, 'Resources.resw'),
			dom = new DOMParser().parseFromString(template, 'text/xml'),
			root = dom.documentElement;

		function addString(name, value) {
			var dataNode = dom.createElement('data');
			dataNode.setAttribute('name', name);
			dataNode.setAttribute('xml:space', 'preserve');

			var valueNode = dom.createElement('value');
			valueNode.appendChild(dom.createTextNode(value));

			dataNode.appendChild(valueNode);
			root.appendChild(dataNode);
		}

		// process app_name first
		addString('app_name', data[locale].app && data[locale].app.appname || this.tiapp.name);

		data[locale].strings && Object.keys(data[locale].strings).forEach(function (name) {
			if (name !== 'appname') {
				addString(name, data[locale].strings[name]);
			}
		});

		this.logger.debug(__('Writing %s strings => %s', locale.cyan, dest.cyan));
		fs.existsSync(destDir) || wrench.mkdirSyncRecursive(destDir);
		fs.writeFileSync(dest, '<?xml version="1.0" encoding="UTF-8"?>\n' + dom.documentElement.toString());

		// save the destination files to update the Visual Studio project later at addI18nVSItemGroup
		this.i18nVSResources = this.i18nVSResources || [];
		this.i18nVSResources.push(dest);
	}, this);

	next();
};

/**
 * Updates the Visual Studio project to add the generated Resources.resw file
 *
 * @param {Function} next - A function to call after resources have been generated.
 */
function addI18nVSResources(next) {
	if (!this.i18nVSResources) {
		next();
		return;
	}

	var cmakeProjectName = this.sanitizeProjectName(this.cli.tiapp.name),
		slnFile = path.resolve(this.cmakeTargetDir, cmakeProjectName + '.sln'),
		vcxproj = path.resolve(this.cmakeTargetDir, cmakeProjectName + '.vcxproj');

	var modified = fs.readFileSync(vcxproj, 'utf8');
	fs.existsSync(vcxproj) && fs.renameSync(vcxproj, vcxproj + '.bak');

	var itemGroupContent = ['</ItemGroup>', '<ItemGroup>'];
	for (var i = 0; i < this.i18nVSResources.length; i++) {
		itemGroupContent.push('  <PRIResource Include="' + this.i18nVSResources[i]  + '" />');
	}
	itemGroupContent.push('</ItemGroup>');

	// add it after the first occurrence of </ItemGroup>
	modified = modified.replace(/<\/ItemGroup>/, itemGroupContent.join('\r\n  '));

	// DefaultLanguage (forcing to "en" for now)
	modified = modified.replace(/<DefaultLanguage>[a-zA-Z]{2}(-[a-zA-Z]{2})*<\/DefaultLanguage>/, '<DefaultLanguage>en</DefaultLanguage>');

	fs.writeFileSync(vcxproj, modified);

	next();
}

/**
 * Generates the native type wrappers and adds them to the Visual Studio project.
 *
 * @param {Function} next - A function to call after the native types have been generated.
 */
function generateNativeWrappers(next) {
	this.logger.info(__('Generating Native Type Wrappers'));

	nativeTypeGenerator.setLogger(this.logger);
	nativeTypeGenerator.generate(path.join(this.buildDir, 'Native'), this.seeds, this.modules, next);
};

/**
 * Generates finders for cmake to find a native module DLL/winmd.
 *
 * @param {Function} next - A function to call after generating the cmake finders
 */
function generateModuleFinder(next) {
	var template = fs.readFileSync(path.join(this.cmakeFinderDir, 'FindNativeModule.cmake.ejs'), 'utf8');

	for (var i = 0; i < this.modules.length; i++) {
		var module = this.modules[i],
			projectname = module.manifest.moduleIdAsIdentifier;

		module.path = module.modulePath.replace(/\\/g, '/').replace(' ', '\\ ');

		if (module.manifest.platform == 'windows') {
			var dest = path.join(this.cmakeFinderDir, 'Find' + projectname + '.cmake');
			this.logger.info(__('Writing CMake module finder %s', dest));
			fs.writeFileSync(dest, ejs.render(template, {module: module}, {}));
		}
	}

	next();
};

/**
 * Generates a cmakelist to define what cmake is doing to generate the VS project.
 *
 * @param {Function} next - A function to call after generating the cmakelist.txt file.
 */
function generateCmakeList(next) {
	var assetList = [],
		sourceGroups = {},
		native_modules = [];

	this.logger.info(__('Writing CMakeLists.txt: %s', this.cmakeListFile.cyan));

	// TODO If forceBuild is false AND no assets have changed, then we can skip this and the cmake step, I think!
	function getFilesRecursive(folder) {
		var fileContents = fs.readdirSync(folder),
			fileTree = [],
			stats;

		fileContents.forEach(function (fileName) {
			var child = path.join(folder, fileName);
			stats = fs.lstatSync(child);

			if (stats.isDirectory()) {
				getFilesRecursive(child).forEach(function (file) {
					fileTree.push(fileName + '/' + file);  // cmake likes unix separators
				});
			} else {
				fileTree.push(fileName);
			}
		});

		return fileTree;
	}

	// Recursively read all files under Assets and populate the cmake listing with it.
	assetList = getFilesRecursive(this.buildTargetAssetsDir);
	assetList = assetList.map(function (filename) {
		return 'Assets/' + filename;  // cmake likes unix separators
	});

	var isBuildForWindowsStore = (this.cmakePlatform == 'WindowsStore');

	// Generate source groups!
	// go through the asset list, and basically generate a group for each folder
	assetList.forEach(function (filepath) {
		// Skip scale-xx.png assets because WindowsStore doesn't need it
		// TODO: we don't even need to copy these resources for WindowsStore
		if (isBuildForWindowsStore && /.scale-\d+.png$/.test(filepath)) {
			return;
		}
		// lop off Assets/
		var truncatedPath = filepath.substring(7);
		// drop the file basename?
		var folderName = path.dirname(truncatedPath);
		// now stick it in the mapping!
		var listing = sourceGroups[folderName] || [];
		listing.push(filepath);
		sourceGroups[folderName] = listing;
	});

	// Native modules
	for (var i = 0; i < this.modules.length; i++) {
		var module = this.modules[i],
			projectname = module.manifest.moduleIdAsIdentifier;
		if (module.manifest.platform == 'windows') {
			native_modules.push({
				projectname: projectname,
				path: module.modulePath.replace(/\\/g, '/').replace(' ', '\\ ')
			});
		}
	}

	this.cli.createHook('build.windows.writeCMakeLists', this, function (manifest, cb) {
		fs.existsSync(this.buildDir) || wrench.mkdirSyncRecursive(this.buildDir)

		if (fs.existsSync(this.cmakeListFile)) {
			if (manifest == fs.readFileSync(this.cmakeListFile).toString()) {
				this.logger.info("CmakeLists.txt contents unchanged, retaining existing file.");
				cb();
				return;
			}
			fs.unlinkSync(this.cmakeListFile);
		}
		fs.writeFile(this.cmakeListFile, manifest, cb);
	})(ejs.render(
		fs.readFileSync(
			path.resolve(this.platformPath, 'templates', 'build', 'CMakeLists.txt.ejs')
		).toString(),
		{
			projectName: this.sanitizeProjectName(this.cli.tiapp.name),
			windowsSrcDir: path.resolve(__dirname, '..', '..', '..').replace(/\\/g, '/').replace(' ', '\\ '), // cmake likes unix separators
			version: appc.version.format(this.tiapp.version, 4, 4, true),
			assets: assetList.join('\n'),
			publisherDisplayName: this.cli.tiapp.publisher,
			publisherId: this.publisherId,
			appId: this.cli.tiapp.windows.id || this.cli.tiapp.id,
			phonePublisherId: this.phonePublisherId,
			phoneProductId: this.phoneProductId,
			sourceGroups: sourceGroups,
			native_modules: native_modules
		}
	), next);
};

/**
 * Write appxmanifest.in according to manifest properties
 */
function generateAppxManifestForPlatform(target, properties) {
	var template = fs.readFileSync(path.resolve(this.platformPath,
			'templates', 'build', 'Package.' + target + '.appxmanifest.in.ejs'), 'utf8'),
		dest = path.join(this.buildDir, 'Package.' + target + '.appxmanifest.in');

	// Supported properties
	properties.Properties = properties.Properties || [];
	properties.Capabilities = properties.Capabilities || ['<Capability Name=\"internetClient\" />'];
	properties.Prerequisites = properties.Prerequisites || [];
	properties.Resources = properties.Resources || [];
	properties.Extensions = properties.Extensions || [];

	this.logger.info(__('Writing appxmanifest %s', dest));
	fs.writeFileSync(dest, ejs.render(template, {
		manifest: properties
	}, {}));
}

/**
 * Generate appx manifest properties
 *
 * <manifest>:
 *   . May appear multiple times (target="phone" or target="store")
 *   . When it doesn't have "target" that means common properties across phone & store
 *
 *  Example:
 *    <windows>
 *        <manifest target="phone">
 *            <Capabilities>
 *                <Capability Name="location" />
 *            </Capabilities>
 *        </manifest>
 *        <manifest target="store">
 *            <Capabilities>
 *                <Capability Name="optical" />
 *            </Capabilities>
 *        </manifest>
 *        <manifest>
 *            <Capabilities>
 *                <Capability Name="internetClient" />
 *            </Capabilities>
 *        </manifest>
 *    </windows>
 */
function generateAppxManifest(next) {

	this.tiapp.windows = this.tiapp.windows || {};
	this.readTiAppManifest();

	var xprops = {phone: {}, store: {}},
		domParser = new DOMParser();

	if (this.tiapp.windows.manifests) {
		// Construct manifest properties
		for (var i = 0; i < this.tiapp.windows.manifests.length; i++) {
			var manifest = this.tiapp.windows.manifests[i];

			var dom = domParser.parseFromString(manifest, 'text/xml'),
				root = dom.documentElement, properties = {},
				target = appc.xml.getAttr(root, "target");

			appc.xml.forEachElement(root, function (node) {
				var key = node.tagName,
					elements = [];
				appc.xml.forEachElement(node, function (elm) {
					elements.push(elm.toString());
				});
				properties[key] = elements;

				xprops.phone[key] = xprops.phone[key] || [];
				xprops.store[key] = xprops.store[key] || [];

				if (target == "phone") {
					xprops.phone[key] = xprops.phone[key].concat(elements);
				} else if (target == "store") {
					xprops.store[key] = xprops.store[key].concat(elements);
				} else {
					xprops.phone[key] = xprops.phone[key].concat(elements);
					xprops.store[key] = xprops.store[key].concat(elements);
				}
			});
		}
	}

	// TODO Only generate the manifest for the target we're building for!
	// TODO Write them out in parallel
	this.generateAppxManifestForPlatform("store", xprops.store);
	this.generateAppxManifestForPlatform("phone", xprops.phone);
	this.generateAppxManifestForPlatform("win10", xprops.store);

	next();
};
