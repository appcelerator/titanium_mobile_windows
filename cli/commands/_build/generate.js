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
	defaultsdeep = require('lodash.defaultsdeep'),
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
	WindowsBuilder.prototype.generateCapabilities = generateCapabilities;
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

	this.i18nVSResources = [];

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

		data[locale].app     = data[locale].app || {};
		data[locale].strings = data[locale].strings || {};

		// process default app_name
		if (!data[locale].strings.app_name) {
			data[locale].strings.app_name = data[locale].app.appname ? data[locale].app.appname : data.en.app.appname;
		}
		// process default app_description
		if (!data[locale].strings.app_description) {
			data[locale].strings.app_description = data[locale].strings.app_name;
		}

		Object.keys(data[locale].strings).forEach(function (name) {
			addString(name, data[locale].strings[name]);
		});

		this.i18nVSResources.push({file:dest.replace(/\\/g, '/'), locale:locale});

		this.logger.debug(__('Writing %s strings => %s', locale.cyan, dest.cyan));
		fs.existsSync(destDir) || wrench.mkdirSyncRecursive(destDir);
		fs.writeFileSync(dest, '<?xml version="1.0" encoding="UTF-8"?>\n' + dom.documentElement.toString());
	}, this);

	next();
};

/**
 * Updates the Visual Studio project to add the generated Resources.resw file
 *
 * @param {Function} next - A function to call after resources have been generated.
 */
function addI18nVSResources(next) {
	var cmakeProjectName = this.sanitizeProjectName(this.cli.tiapp.name),
		vcxproj = path.resolve(this.cmakeTargetDir, cmakeProjectName + '.vcxproj');

	var modified = fs.readFileSync(vcxproj, 'utf8');
	fs.existsSync(vcxproj) && fs.renameSync(vcxproj, vcxproj + '.bak');

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
			i18nVSResources: this.i18nVSResources,
			native_modules: native_modules
		}
	), next);
};

/**
 * Generates capabilities based on API usage
 *
 * @param {String} target - Build target to determine platform specific capabilities
 * @param {Object} capabilities - Capabilities array
 * @param {Object} deviceCapabilities - Device capabilities array
 */
function generateCapabilities(target, capabilities, deviceCapabilities) {
	var apis = {
			// Titanium.Contacts
			'Contacts': {
				uapCapability: ['contacts']
			},
			// Titanium.Filesystem
			'Filesystem.externalStorageDirectory': {
				uapCapability: ['removableStorage']
			},
			// Titanium.Geolocation.*
			'Geolocation': {
				deviceCapability: ['location']
			},
			// Titanium.Media
			'Media.openPhotoGallery': {
				uapCapability: ['picturesLibrary']
			},
			'Media.startVideoCapture': {
				uapCapability: ['videosLibrary']
			},
			'Media.takeScreenshotToFile': {
				uapCapability: ['picturesLibrary']
			},
			'Media.showCamera': {
				deviceCapability: ['microphone', 'webcam']
			},
			'Media.takePicture': {
				uapCapability: ['picturesLibrary', 'videosLibrary']
			},
			// Titanium.Media.AudioRecorder.*
			'Media.AudioRecorder': {
				uapCapability: ['musicLibrary'],
				deviceCapability: ['microphone', 'webcam']
			},
			// Titanium.Network.*
			'Network': {
				capability: ['internetClient']
			},
			// Titanium.App.proximityDetection
			'App.proximityDetection': {
				deviceCapability: ['proximity']
			},
			'App.setProximityDetection': {
				deviceCapability: ['proximity']
			}
		},
		uapCapabilities = [],
		hasCapability = function (capabilities, capability) {
			for (var i = 0; i < capabilities.length; i++) {
				var name = /Name\=\"(.*)\"/.exec(capabilities[i])[1];
				if (name == capability) {
					return true;
				}
			}
			return false;
		}.bind(this);

	Object.keys(this.jsFiles).forEach(function (id) {
		var js = fs.readFileSync(this.jsFiles[id], {encoding: 'utf8'});

		// always include internetClient for analytics
		if (!hasCapability(capabilities, 'internetClient')) {
			capabilities.push('<Capability Name=\"internetClient\" />');
		}
		for (api in apis) {
			var reg = new RegExp('(Ti|Titanium)\\.(' + api.replace('.', '\\.') +')', 'g');
			if (reg.test(js)) {
				apis[api].capability && apis[api].capability.forEach(function(name) {
					var entry = '<Capability Name="' + name + '" />';
					if (!hasCapability(capabilities, name)) {
						capabilities.push(entry);
					}
				});
				apis[api].uapCapability && apis[api].uapCapability.forEach(function(name) {
					var tag = target == 'win10' ? 'uap:' : (name == 'contacts' ? 'm3:' : ''),
						entry = '<' + tag + 'Capability Name="' + name + '" />';

					// skip Windows 8.1 phone specific capabilities when targeting store
					if (tag == 'm3:' && target == 'store') {
						return;
					}
					if (!hasCapability(uapCapabilities, name) && !hasCapability(capabilities, name)) {
						uapCapabilities.push(entry);
					}
				});
				apis[api].deviceCapability && apis[api].deviceCapability.forEach(function(name) {
					var entry = '<DeviceCapability Name="' + name + '" />';
					if (!hasCapability(deviceCapabilities, name)) {
						deviceCapabilities.push(entry);
					}
				});
			}
		}
	}.bind(this));

	return capabilities.concat(uapCapabilities).concat(deviceCapabilities);
};

/**
 * Write appxmanifest.in according to manifest properties
 */
function generateAppxManifestForPlatform(target, properties) {
	var template = fs.readFileSync(path.resolve(this.platformPath,
			'templates', 'build', 'Package.' + target + '.appxmanifest.in.ejs'), 'utf8'),
		dest = path.join(this.buildDir, 'Package.' + target + '.appxmanifest.in'),
		win10BaseCapabilities = [
			'internetClient',
			'internetClientServer',
			'privateNetworkClientServer',
			'allJoyn',
			'codeGeneration'
		],
		win81BaseCapabilities = [
			'documentsLibrary', // not listed
			'enterpriseAuthentication',
			'internetClient',
			'internetClientServer',
			'musicLibrary',
			'picturesLibrary',
			'privateNetworkClientServer', // store only?
			'removableStorage',
			'sharedUserCertificates',
			'videosLibrary'
		],
		win81M3Capabilities = [ // m3 namespace, phone 8.1 only
			'contacts',
			'appointments'
		],
		win10UAPCapabilities = [
			'documentsLibrary',
			'picturesLibrary',
			'videosLibrary',
			'musicLibrary',
			'enterpriseAuthentication',
			'sharedUserCertificates',
			'userAccountInformation',
			'removableStorage',
			'appointments',
			'contacts',
			'phoneCall',
			'blockedChatMessages',
			'objects3D',
			'voipCall',
			'chat'
		],
		win81DeviceCapabilities = [
			'webcam',
			'proximity',
			'microphone',
			'location'
		],
		capabilities = [],
		deviceCapabilities = [];

	// Supported properties
	properties.Properties = properties.Properties || [];

	// Capabilities (we kept them as xml nodes to make this below easier!)
	if (properties.Capabilities) {
		// Filter capabilities that aren't valid for the SDK version and platform we're targeting
		// Also make sure we use the correct tag namespace for target
		properties.Capabilities.forEach(function (node) {
			var name;
			if (node.tagName == 'Capability') {
				// grab name of capability, determine if we include or filter, which namespace to use for tag
				name = appc.xml.getAttr(node, "Name");
				if (target == 'win10') { // Windows 10 universal
					if (win10UAPCapabilities.indexOf(name) != -1) {
						capabilities.push('<uap:Capability Name="' + name + '" />');
					} else if (win10BaseCapabilities.indexOf(name) != -1) {
						capabilities.push('<Capability Name="' + name + '" />');
					}
				}
				else {
					if (win81BaseCapabilities.indexOf(name) != -1) {
						capabilities.push('<Capability Name="' + name + '" />');
					} else if (target == 'phone' && win81M3Capabilities.indexOf(name) != -1) {
						capabilities.push('<m3:Capability Name="' + name + '" />');
					}
				}
			}
			else {
				// Just write the XML out as is
				// TODO Do some validation of DeviceCapability name?
				if (node.tagName == 'DeviceCapability') {
					deviceCapabilities.push(node.toString());
				} else {
					capabilities.push(node.toString());
				}
			}
		});
	}
	properties.Capabilities = this.generateCapabilities(target, capabilities, deviceCapabilities);

	properties.Prerequisites = properties.Prerequisites || [];
	properties.Resources = properties.Resources || [];
	properties.Extensions = properties.Extensions || [];

	var applications = {};
	if (properties.Applications) {
		// Turn the xml to JSON!
		function xmlToObject(node) {
			var obj = {};
			appc.xml.forEachAttr(node, function (item) {
				obj[item.name] = item.value;
			});
			appc.xml.forEachElement(node, function (elm) {
				obj[elm.tagName] = xmlToObject(elm);
			});
			return obj;
		};
		applications['Application'] = xmlToObject(properties.Applications[0]);
	}
	// now merge with our default colors
	var defaultApplications = {
		Application: {
			VisualElements: {
				BackgroundColor: 'transparent',
				ForegroundText: 'light',
				SplashScreen: {
					BackgroundColor: '#b41100'
				}
			}
		}
	};
	properties.Applications = defaultsdeep(applications, defaultApplications);

	// Enable badge logo only when BackgroundTask Extension is used.
	var requiresBadgeLogo = false;
	properties.Extensions.forEach(function (node) {
		if (node.tagName == 'Extension' && node.childNodes) {
			for (var i = 0; i < node.childNodes.length; i++) {
				var cnode = node.childNodes.item(i);
				if (cnode && cnode.tagName == 'BackgroundTasks') {
					requiresBadgeLogo = true;
					break;
				}
			}
		}
	});
	properties.requiresBadgeLogo = requiresBadgeLogo;

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

	var xprops = {
			phone: { '8.1': {}, '10.0': {} },
			store: { '8.1': {}, '10.0': {} }
		},
		domParser = new DOMParser();

	if (this.tiapp.windows.manifests) {
		// Construct manifest properties
		for (var i = 0; i < this.tiapp.windows.manifests.length; i++) {
			var manifest = this.tiapp.windows.manifests[i];

			var dom = domParser.parseFromString(manifest, 'text/xml'),
				root = dom.documentElement,
				target = appc.xml.getAttr(root, "target"),
				version = appc.xml.getAttr(root, "version");

			appc.xml.forEachElement(root, function (node) {
				var key = node.tagName,
					elements = [];
				// gather all the child tags
				appc.xml.forEachElement(node, function (elm) {
					elements.push(elm);
				});

				xprops.phone['8.1'][key] = xprops.phone['8.1'][key] || [];
				xprops.store['8.1'][key] = xprops.store['8.1'][key] || [];
				xprops.store['10.0'][key] = xprops.store['10.0'][key] || [];

				// If version is 10.0 or not specified, add it to store['10.0']
				if (version == '10.0' || !version) {
					xprops.store['10.0'][key] = xprops.store['10.0'][key].concat(elements);
				}

				// If version is 8.1 or not defined, check target to determine phone[8.1] and/or store[8.1]
				if (version == '8.1' || !version) {
					if (target == "phone") {
						xprops.phone['8.1'][key] = xprops.phone['8.1'][key].concat(elements);
					} else if (target == "store") {
						xprops.store['8.1'][key] = xprops.store['8.1'][key].concat(elements);
					} else {
						xprops.phone['8.1'][key] = xprops.phone['8.1'][key].concat(elements);
						xprops.store['8.1'][key] = xprops.store['8.1'][key].concat(elements);
					}
				}
			});
		}
	}

	// TODO Only generate the manifest for the target we're building for!
	// TODO Write them out in parallel
	this.generateAppxManifestForPlatform("store", xprops.store['8.1']);
	this.generateAppxManifestForPlatform("phone", xprops.phone['8.1']);
	this.generateAppxManifestForPlatform("win10", xprops.store['10.0']);

	next();
};
