'use strict';

const appc = require('node-appc');
const nativeModuleGenerator = require('../../lib/stub');
const DOMParser = require('xmldom').DOMParser;
const fs = require('fs-extra');
const i18n = require('node-titanium-sdk/lib/i18n');
const ejs = require('ejs');
const path = require('path');
const defaultsdeep = require('lodash.defaultsdeep');
const spawn = require('child_process').spawn; // eslint-disable-line security/detect-child-process
const walkSync = require('klaw-sync');
const __ = appc.i18n(__dirname).__;

/*
 Public API.
 */
exports.mixin = mixin;

/*
 Implementation.
 */
function mixin(WindowsBuilder) {
	WindowsBuilder.prototype.generateBuildVersion = generateBuildVersion;
	WindowsBuilder.prototype.generateI18N = generateI18N;
	WindowsBuilder.prototype.generateNativeTypes = generateNativeTypes;
	WindowsBuilder.prototype.generateModuleFinder = generateModuleFinder;
	WindowsBuilder.prototype.generateCmakeList = generateCmakeList;
	WindowsBuilder.prototype.generateCapabilities = generateCapabilities;
	WindowsBuilder.prototype.generateAppxManifestForPlatform = generateAppxManifestForPlatform;
	WindowsBuilder.prototype.mergeAppxManifestForModule = mergeAppxManifestForModule;
	WindowsBuilder.prototype.generateAppxManifest = generateAppxManifest;
	WindowsBuilder.prototype.fixCSharpConfiguration = fixCSharpConfiguration;
	WindowsBuilder.prototype.copyModuleOverride = copyModuleOverride;
}

/**
 * Generates new build number based on tiapp.version
 *
 * @param {Function} next - A function to call after new version number have been generated.
 */
function generateBuildVersion(next) {
	// Generates new build number based on tiapp.version
	var version = appc.version.format(this.tiapp.version, 3, 4, true);
	// If revision number is omitted, we generate it. Only available on development/test build.
	// Can be disabled when 'use-auto-versioning' set false in <windows> section.
	var disabled = this.tiapp.windows && this.tiapp.windows['use-auto-versioning'] === false;

	if (!disabled && !/^dist-/.test(this.target) && version.split('.').length <= 3) {
		var buildNumber = 0;
		if (this.buildManifest.buildNumber) {
			var number = parseInt(this.buildManifest.buildNumber, 10);
			if (isNaN(number)) {
				number = 0;
			}
			buildNumber = number;
		}
		buildNumber++;
		this.buildVersion = appc.version.format(version + '.' + buildNumber, 4, 4, true);
		this.buildNumber = buildNumber;
	} else {
		this.buildVersion = appc.version.format(version, 4, 4, true);
		this.buildNumber  = 0;
	}
	next();
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

	data['en-US'] || (data['en-US'] = {});
	data['en-US'].app || (data['en-US'].app = {});
	data['en-US'].app.appname || (data['en-US'].app.appname = this.tiapp.name);

	this.i18nVSResources = [];
	this.defaultLanguage = 'en-US'; // default language needs to be qualified (TIMOB-25183)

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
			data[locale].strings.app_name = data[locale].app.appname ? data[locale].app.appname : data['en-US'].app.appname;
		}
		// process default app_description
		if (!data[locale].strings.app_description) {
			data[locale].strings.app_description = data[locale].strings.app_name;
		}

		Object.keys(data[locale].strings).forEach(function (name) {
			addString(name, data[locale].strings[name]);
		});

		this.i18nVSResources.push({ file: dest.replace(/\\/g, '/'), locale: locale });

		this.logger.debug(__('Writing %s strings => %s', locale.cyan, dest.cyan));
		fs.ensureDirSync(destDir);
		fs.writeFileSync(dest, '<?xml version="1.0" encoding="UTF-8"?>\n' + dom.documentElement.toString());
	}, this);

	next();
}

/**
 * Generates the native type wrappers and adds them to the Visual Studio project.
 *
 * @param {Function} next - A function to call after the native types have been generated.
 */
function generateNativeTypes(next) {
	this.logger.info(__('Generating Native Types'));

	var defaultTargetPlatformVersion,
		defaultTargetPlatformMinVersion;

	if (this.wpsdk.startsWith('10.0')
		&& this.windowsInfo.windowsphone['10.0']
		&& this.windowsInfo.windowsphone['10.0'].sdks
		&& this.windowsInfo.windowsphone['10.0'].sdks.length > 0) {

		var supportedSdkVersions = this.windowslibOptions.supportedWindows10SDKVersions.replace(/(\d+\.\d+\.\d+)\.\d+/g, '$1'),
			sdks = this.windowsInfo.windowsphone['10.0'].sdks;

		// TIMOB-24908: Visual studio 2015 cannout build with newer SDKs
		if (this.windowsInfo.selectedVisualStudio.version === '14.0') {
			supportedSdkVersions = '>=10.0.10240 <=10.0.14393';
		}

		// obtain highest compatible target version
		for (var i = sdks.length - 1; i >= 0; i--) {
			var sdk = sdks[i];
			if (appc.version.satisfies(sdk, supportedSdkVersions, false)) {
				defaultTargetPlatformVersion = sdk;
				break;
			}
		}
		// obtain lowest compatible target version
		for (var i = 0; i < sdks.length; i++) {
			var sdk = sdks[i];
			if (appc.version.satisfies(sdk, supportedSdkVersions, false)) {
				defaultTargetPlatformMinVersion = sdk;
				break;
			}
		}
	}
	this.targetPlatformSdkVersion = this.targetPlatformSdkVersion || this.tiapp.windows['TargetPlatformVersion'] || defaultTargetPlatformVersion || this.wpsdk;
	this.targetPlatformSdkMinVersion = this.targetPlatformSdkMinVersion || this.tiapp.windows['TargetPlatformMinVersion'] || defaultTargetPlatformMinVersion || this.targetPlatformSdkVersion;

	this.logger.debug(__('targetPlatformSdkVersion: %s', this.targetPlatformSdkVersion));
	this.logger.debug(__('targetPlatformSdkMinVersion: %s', this.targetPlatformSdkMinVersion));

	nativeModuleGenerator.generate(this, next);
}

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
			fs.writeFileSync(dest, ejs.render(template, { module: module }, {}));
		}
	}

	next();
}

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

	// Generate source groups!
	// go through the asset list, and basically generate a group for each folder
	assetList.forEach(function (filepath) {
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

	// '10.0' is not valid for MinVersion because it requires build number
	if (this.targetPlatformSdkMinVersion.match(/^[0-9]{1,2}\.[0-9]$/)) {
		this.targetPlatformSdkMinVersion = '';
	}

	this.cli.createHook('build.windows.writeCMakeLists', this, function (manifest, cb) {
		fs.ensureDirSync(this.buildDir);

		if (fs.existsSync(this.cmakeListFile)) {
			if (manifest == fs.readFileSync(this.cmakeListFile).toString()) {
				this.logger.info('CmakeLists.txt contents unchanged, retaining existing file.');
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
			version: this.buildVersion,
			assets: assetList.join('\n'),
			publisherDisplayName: this.cli.tiapp.publisher,
			publisherId: this.publisherId,
			appId: this.cli.tiapp.windows.id || this.cli.tiapp.id,
			phonePublisherId: this.phonePublisherId,
			phoneProductId: this.phoneProductId,
			sourceGroups: sourceGroups,
			i18nVSResources: this.i18nVSResources,
			defaultLanguage: this.defaultLanguage,
			native_modules: native_modules,
			targetPlatformSdkMinVersion: this.targetPlatformSdkMinVersion,
			thirdPartyReferences: this.hyperloopConfig.windows.thirdPartyReferences || [],
			vsSdkReferences: this.vsSdkReferences || []
		}
	), next);
}

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
			Contacts: {
				uapCapability: [ 'contacts' ]
			},
			// Titanium.Filesystem
			'Filesystem.externalStorageDirectory': {
				uapCapability: [ 'removableStorage' ]
			},
			// Titanium.Geolocation.*
			Geolocation: {
				deviceCapability: [ 'location' ]
			},
			// Titanium.Media
			'Media.openPhotoGallery': {
				uapCapability: [ 'picturesLibrary' ]
			},
			'Media.startVideoCapture': {
				uapCapability: [ 'videosLibrary' ]
			},
			'Media.takeScreenshotToFile': {
				uapCapability: [ 'picturesLibrary' ]
			},
			'Media.showCamera': {
				deviceCapability: [ 'microphone', 'webcam' ]
			},
			'Media.takePicture': {
				uapCapability: [ 'picturesLibrary', 'videosLibrary' ]
			},
			// Titanium.Media.AudioRecorder.*
			'Media.AudioRecorder': {
				uapCapability: [ 'musicLibrary' ],
				deviceCapability: [ 'microphone', 'webcam' ]
			},
			// Titanium.Network.*
			Network: {
				capability: [ 'internetClient' ]
			},
			// Titanium.App.proximityDetection
			'App.proximityDetection': {
				deviceCapability: [ 'proximity' ]
			},
			'App.setProximityDetection': {
				deviceCapability: [ 'proximity' ]
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
		};

	Object.keys(this.jsFiles).forEach(function (id) {
		var js = fs.readFileSync(this.jsFiles[id], { encoding: 'utf8' });

		// always include internetClient for analytics
		if (!hasCapability(capabilities, 'internetClient')) {
			capabilities.push('<Capability Name="internetClient" />');
		}
		for (const api in apis) {
			var reg = new RegExp('(Ti|Titanium)\\.(' + api.replace('.', '\\.') + ')', 'g');
			if (reg.test(js)) {
				apis[api].capability && apis[api].capability.forEach(function (name) {
					var entry = '<Capability Name="' + name + '" />';
					if (!hasCapability(capabilities, name)) {
						capabilities.push(entry);
					}
				});
				apis[api].uapCapability && apis[api].uapCapability.forEach(function (name) {
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
				apis[api].deviceCapability && apis[api].deviceCapability.forEach(function (name) {
					var entry = '<DeviceCapability Name="' + name + '" />';
					if (!hasCapability(deviceCapabilities, name)) {
						deviceCapabilities.push(entry);
					}
				});
			}
		}
	}.bind(this));

	return capabilities.concat(uapCapabilities).concat(deviceCapabilities);
}

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
		capabilities = [],
		deviceCapabilities = [],
		_t = this;

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
				name = appc.xml.getAttr(node, 'Name');
				if (target == 'win10') { // Windows 10 universal
					if (win10UAPCapabilities.indexOf(name) !== -1) {
						var cap = '<uap:Capability Name="' + name + '" />';
						if (capabilities.indexOf(cap) === -1) {
							capabilities.push(cap);
						}
					} else if (win10BaseCapabilities.indexOf(name) !== -1) {
						var cap = '<Capability Name="' + name + '" />';
						if (capabilities.indexOf(cap) === -1) {
							capabilities.push(cap);
						}
					}
				} else if (win81BaseCapabilities.indexOf(name) != -1) {
						var cap = '<Capability Name="' + name + '" />';
						if (capabilities.indexOf(cap) == -1) {
							capabilities.push(cap);
						}
					} else if (target == 'phone' && win81M3Capabilities.indexOf(name) != -1) {
						var cap = '<m3:Capability Name="' + name + '" />';
						if (capabilities.indexOf(cap) == -1) {
							capabilities.push(cap);
						}
					}
			} else {
				// Just write the XML out as is
				// TODO Do some validation of DeviceCapability name?
				if (node.tagName == 'DeviceCapability') {
					// Capability should have Name property only
					var cap = '<' + node.tagName + ' Name="' +  appc.xml.getAttr(node, 'Name') + '" />';
					if (deviceCapabilities.indexOf(cap) == -1) {
						deviceCapabilities.push(cap);
					}
				} else {
					// Capability should have Name property only
					var cap = '<' + node.tagName + ' Name="' +  appc.xml.getAttr(node, 'Name') + '" />';
					if (capabilities.indexOf(cap) == -1) {
						capabilities.push(cap);
					}
				}
			}
		});
	}

	properties.Capabilities = this.generateCapabilities(target, capabilities, deviceCapabilities);

	properties.Prerequisites = properties.Prerequisites || [];
	properties.Resources = properties.Resources || [];
	properties.Extensions = properties.Extensions || [];
	properties.PackageExtensions = properties.PackageExtensions || [];
	properties.Dependencies = properties.Dependencies || [];
	properties.SDKReferences = properties.SDKReferences || [];

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
		}
		applications['Application'] = xmlToObject(properties.Applications[0]);
	}
	// now merge with our default colors
	var defaultApplications = {
		Application: {
			VisualElements: {
				Square150x150Logo: 'Square150x150Logo.png',
				Square44x44Logo:   'Square44x44Logo.png',
				BackgroundColor: 'transparent',
				DefaultTile: {
					Square71x71Logo: 'Square71x71Logo.png',
					Square310x310Logo: 'Square310x310Logo.png',
				},
				SplashScreen: {
					BackgroundColor: '#b41100',
					Image: 'SplashScreen.png'
				}
			}
		}
	};

	/*
	 * Look for basename.png, if it does not exist then look for .scale-100.png because it should have same dimension
	 */
	function windowsScaledPNGAssetExists(basename) {
		if (fs.existsSync(basename + '.png')) {
			return true;
		} else if (fs.existsSync(basename + '.scale-100.png')) {
			return true;
		}
		return false;
	}

	// Enable Wide310x150Logo only when file exists
	if (windowsScaledPNGAssetExists(path.join(this.buildTargetAssetsDir, 'Wide310x150Logo'))) {
		defaultApplications.Application.VisualElements.DefaultTile.Wide310x150Logo = 'Wide310x150Logo.png';
	}

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
	if (requiresBadgeLogo) {
		defaultApplications.Application.VisualElements.LockScreen
		= {
			Notification: 'badge',
			BadgeLogo: 'Square24x24Logo.png'
		};
	}

	properties.Applications = defaultsdeep(applications, defaultApplications);

	this.vsSdkReferences = [];
	properties.SDKReferences.forEach(function (node) {
		if (node.tagName == 'SDKReference') {
			_t.vsSdkReferences.push(appc.xml.getAttr(node, 'Include'));
		}
	});

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
function mergeAppxManifestForModule() {
	var _t = this;
	this.tiapp.windows.manifests = this.tiapp.windows.manifests || [];
	var domParser = new DOMParser();
	for (var i = 0; i < this.modules.length; i++) {
		var timodule = path.join(this.modules[i].modulePath, 'timodule.xml');
		if (fs.existsSync(timodule)) {
			var content  = fs.readFileSync(timodule, 'utf8'),
				dom = domParser.parseFromString(content, 'text/xml'),
				root = dom.documentElement;
			appc.xml.forEachElement(root, function (node) {
				if (node.tagName == 'windows') {
					appc.xml.forEachElement(node, function (node) {
						if (node.tagName == 'manifest') {
							_t.tiapp.windows.manifests.push(node.toString());
						}
					});
				}
			});
		}
	}
}

function generateAppxManifest(next) {

	this.tiapp.windows = this.tiapp.windows || {};
	this.readTiAppManifest();

	this.mergeAppxManifestForModule();

	var xprops = {
			phone: { 8.1: {}, '10.0': {} },
			store: { 8.1: {}, '10.0': {} }
		},
		domParser = new DOMParser();

	if (this.tiapp.windows.manifests) {

		// Construct manifest properties
		for (var i = 0; i < this.tiapp.windows.manifests.length; i++) {
			var manifest = this.tiapp.windows.manifests[i];

			var dom = domParser.parseFromString(manifest, 'text/xml'),
				root = dom.documentElement,
				target = appc.xml.getAttr(root, 'target'),
				version = appc.xml.getAttr(root, 'version');

			appc.xml.forEachElement(root, function (node) {
				var key = node.tagName,
					elements = [];
				// gather all the child tags
				appc.xml.forEachElement(node, function (elm) {
					elements.push(elm);
				});

				xprops.phone['8.1'][key]  = xprops.phone['8.1'][key]  || [];
				xprops.store['8.1'][key]  = xprops.store['8.1'][key]  || [];
				xprops.store['10.0'][key] = xprops.store['10.0'][key] || [];

				// If version is 10.0 or not specified, add it to store['10.0']
				if (version == '10.0' || !version) {
					xprops.store['10.0'][key] = xprops.store['10.0'][key].concat(xprops.store['10.0'][key].concat(elements));
				}

				// If version is 8.1 or not defined, check target to determine phone[8.1] and/or store[8.1]
				if (version == '8.1' || !version) {
					if (target == 'phone') {
						xprops.phone['8.1'][key] = xprops.phone['8.1'][key].concat(xprops.phone['8.1'][key].concat(elements));
					} else if (target == 'store') {
						xprops.store['8.1'][key] = xprops.store['8.1'][key].concat(xprops.store['8.1'][key].concat(elements));
					} else {
						xprops.phone['8.1'][key] = xprops.phone['8.1'][key].concat(xprops.phone['8.1'][key].concat(elements));
						xprops.store['8.1'][key] = xprops.store['8.1'][key].concat(xprops.store['8.1'][key].concat(elements));
					}
				}
			});
		}
	}

	// TODO Only generate the manifest for the target we're building for!
	// TODO Write them out in parallel
	this.generateAppxManifestForPlatform('store', xprops.store['8.1']);
	this.generateAppxManifestForPlatform('phone', xprops.phone['8.1']);
	this.generateAppxManifestForPlatform('win10', xprops.store['10.0']);

	next();
}

/**
 * Updates the Visual Studio project to fix configuration for C# project
 */
function fixCSharpConfiguration(next) {
	var cmakeProjectName = this.sanitizeProjectName(this.cli.tiapp.name),
		sln = path.resolve(this.cmakeTargetDir, cmakeProjectName + '.sln'),
		modified = fs.readFileSync(sln, 'utf8'),
		_t = this;

	modified = modified.replace('{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.Debug|Win32.ActiveCfg = Debug|Win32',     '{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.Debug|Win32.ActiveCfg = Debug|x86');
	modified = modified.replace('{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.Debug|Win32.Build.0 = Debug|Win32',       '{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.Debug|Win32.Build.0 = Debug|x86');
	modified = modified.replace('{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.Release|Win32.ActiveCfg = Release|Win32', '{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.Release|Win32.ActiveCfg = Release|x86');
	modified = modified.replace('{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.Release|Win32.Build.0 = Release|Win32',   '{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.Release|Win32.Build.0 = Release|x86');
	modified = modified.replace('{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.MinSizeRel|Win32.ActiveCfg = MinSizeRel|Win32', '{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.MinSizeRel|Win32.ActiveCfg = MinSizeRel|x86');
	modified = modified.replace('{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.MinSizeRel|Win32.Build.0 = MinSizeRel|Win32',   '{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.MinSizeRel|Win32.Build.0 = MinSizeRel|x86');
	modified = modified.replace('{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.RelWithDebInfo|Win32.ActiveCfg = RelWithDebInfo|Win32', '{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.RelWithDebInfo|Win32.ActiveCfg = RelWithDebInfo|x86');
	modified = modified.replace('{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.RelWithDebInfo|Win32.Build.0 = RelWithDebInfo|Win32',   '{68D742FA-F1E6-487A-A9FA-158A6C8BBCBB}.RelWithDebInfo|Win32.Build.0 = RelWithDebInfo|x86');

	fs.writeFileSync(sln, modified);

	// Make sure project dependencies are installed via NuGet
	var nuget = path.resolve(__dirname, '..', '..', 'vendor', 'nuget', 'nuget.exe');
	var p = spawn(nuget, [ 'restore', sln ]);
	p.stdout.on('data', function (data) {
		var line = data.toString().trim();
		if (line.indexOf('error ') >= 0) {
			_t.logger.error(line);
		} else if (line.indexOf('warning ') >= 0) {
			_t.logger.warn(line);
		} else if (line.indexOf(':\\') === -1) {
			_t.logger.debug(line);
		} else {
			_t.logger.trace(line);
		}
	});
	p.stderr.on('data', function (data) {
		_t.logger.warn(data.toString().trim());
	});
	p.on('close', function (code) {
		if (code !== 0) {
			process.exit(1); // Exit with code from nuget?
		}
		next();
	});
}

/*
 * Each modules have 'platform' folder that is meant to replace existing files under build folder just before the build
 */
function copyModuleOverride(next) {
	var _t = this;
	const windowsModules = this.modules.filter(m => m.manifest.platform == 'windows');
	windowsModules.forEach(module => {
		const moduleSrc = path.join(module.modulePath, 'platform');
		if (!fs.existsSync(moduleSrc)) {
			return;
		}
		walkSync(moduleSrc).forEach(res => {
			const from = path.join(moduleSrc, res);
			if (!fs.statSync(from).isFile()) {
				return;
			}

			_t.logger.info('Module [' + module.manifest.moduleid + '] overrides ' + res);
			const to = path.join(_t.buildDir, res);
			const todir = path.dirname(to);
			fs.ensureDirSync(todir);
			fs.createReadStream(from).pipe(fs.createWriteStream(to));
		});
	});

	next();
}
