var appc = require('node-appc'),
	Builder = require('node-titanium-sdk/lib/builder'),
	fs = require('fs'),
	os = require('os'),
	path = require('path'),
	version = appc.version,
	__ = appc.i18n(__dirname).__;

/*
 Public API.
 */
exports.mixin = mixin;

/*
 Implementation.
 */
function mixin(WindowsBuilder) {
	WindowsBuilder.prototype.validate = validate;
}

/**
 * Escapes a value in a relative distinguished name. Used to generate the distinguished name for the windows cert string from tiapp publisher value.
 **/
function restrictToManifestSTPublisher(value) {
	return value.trim().replace(/[, ="<>#;]/g, '');
}

/**
 * Validates the Windows build-specific arguments, tiapp.xml settings, and environment.
 *
 * @param {Object} logger - The logger instance.
 * @param {Object} config - The Titanium CLI config instance.
 * @param {Object} cli - The Titanium CLI instance.
 *
 * @returns {Function} A function to be called async which returns the actual configuration.
 */
function validate(logger, config, cli) {
	Builder.prototype.validate.apply(this, arguments);

	this.target = cli.argv.target;
	this.wpsdk  = this.getWindowsSDKTarget();
	this.deployType = !/^dist-$/.test(this.target) && cli.argv['deploy-type'] ? cli.argv['deploy-type'] : this.deployTypes[this.target];
	this.buildType = cli.argv['build-type'] || '';

	if (this.wpsdk == '8.1') {
		logger.warn(__('Support for Windows 8.1 and Windows Phone 8.1 SDKs has been dropped as of Titanium SDK 6.3.0.GA, and will be removed in Titanium SDK 7.0.0.GA'));
	}

	// ti.deploytype is deprecated and so we force the real deploy type
	if (cli.tiapp.properties['ti.deploytype']) {
		logger.warn(__('The %s tiapp.xml property has been deprecated, please use the %s option', 'ti.deploytype'.cyan, '--deploy-type'.cyan));
	}
	cli.tiapp.properties['ti.deploytype'] = {type: 'string', value: this.deployType};

	// manually inject the build profile settings into the tiapp.xml
	switch (this.deployType) {
		case 'production':
			this.minifyJS = true;
			this.encryptJS = true;
			this.allowDebugging = false;
			this.allowProfiling = false;
			this.includeAllTiModules = false;
			this.enableLogging = false;
			this.buildConfiguration = 'Release';
			break;

		case 'test':
			this.minifyJS = true;
			this.encryptJS = true;
			this.allowDebugging = true;
			this.allowProfiling = true;
			this.includeAllTiModules = false;
			this.enableLogging = true;
			this.buildConfiguration = 'Debug';
			break;

		case 'development':
		default:
			this.minifyJS = false;
			this.encryptJS = false;
			this.allowDebugging = true;
			this.allowProfiling = true;
			this.includeAllTiModules = true;
			this.enableLogging = true;
			this.buildConfiguration = 'Release';
	}

	this.transpile = this.cli.tiapp.transpile === true;

	if (cli.argv['skip-js-minify']) {
		this.minifyJS = false;
	}

	// check the default unit
	cli.tiapp.properties || (cli.tiapp.properties = {});
	cli.tiapp.properties['ti.ui.defaultunit'] || (cli.tiapp.properties['ti.ui.defaultunit'] = {
		type: 'string',
		value: 'system'
	});
	if (!/^system|px|dp|dip|mm|cm|in$/.test(cli.tiapp.properties['ti.ui.defaultunit'].value)) {
		logger.error(__('Invalid "ti.ui.defaultunit" property value "%s"', cli.tiapp.properties['ti.ui.defaultunit'].value) + '\n');
		logger.log(__('Valid units:'));
		'system,px,dp,dip,mm,cm,in'.split(',').forEach(function (unit) {
			logger.log('  ' + unit.cyan);
		});
		logger.log();
		process.exit(1);
	}

	// check that the build directory is writeable
	// try to build under temp if the path is shorter and we have write access
	var home = process.env.HOME || process.env.USERPROFILE || process.env.APPDATA;
	var ti_home = path.join(home, '.titanium');
	var tempBuildDir = path.join(ti_home, 'vsbuild');
	if (appc.fs.isDirWritable(home)) {
		if (!fs.existsSync(ti_home)) {
			fs.mkdirSync(ti_home);
		}
		if (!fs.existsSync(tempBuildDir)) {
			fs.mkdirSync(tempBuildDir);
		}
	}
	if ((tempBuildDir.length < this.buildDir.length) && appc.fs.isDirWritable(tempBuildDir)) {
		this.originalBuildDir = this.buildDir;
		this.buildDir = path.join(tempBuildDir, path.basename(this.projectDir)); // build under temp!
	} else {
		this.originalBuildDir = null;
	}
	var buildDir = path.join(cli.argv['project-dir'], 'build');
	if (fs.existsSync(buildDir)) {
		if (!appc.fs.isDirWritable(buildDir)) {
			logger.error(__('The build directory is not writeable: %s', buildDir) + '\n');
			logger.log(__('Make sure the build directory is writeable and that you have sufficient free disk space.') + '\n');
			process.exit(1);
		}
	} else if (!appc.fs.isDirWritable(cli.argv['project-dir'])) {
		logger.error(__('The project directory is not writeable: %s', cli.argv['project-dir']) + '\n');
		logger.log(__('Make sure the project directory is writeable and that you have sufficient free disk space.') + '\n');
		process.exit(1);
	}

	// make sure we have an icon
	if (!cli.tiapp.icon || !['Resources', 'Resources/windows'].some(function (p) {
			return fs.existsSync(cli.argv['project-dir'], p, cli.tiapp.icon);
		})) {
		cli.tiapp.icon = 'appicon.png';
	}

	this.jdkInfo = null;

	return function (callback) {
		this.validateTiModules('windows', this.deployType, function (err, modules) {
			this.modules = modules.found;
			this.commonJsModules = [];

			// TODO: Windows specific module stuff, if needed

			modules.found.forEach(function (module) {
				if (module.platform.indexOf('commonjs') != -1) {
					this.commonJsModules.push(module);
				}

				// TODO: more Windows specific module stuff, if needed

				// scan the module for any CLI hooks
				cli.scanHooks(path.join(module.modulePath, 'hooks'));
			}.bind(this));

			// Are we not encrypting JS? Then we don't need to detect the JDK.
			if (!this.encryptJS) {
				return callback();
			}
			// detect java development kit.
			appc.jdk.detect(config, null, function (jdkInfo) {
				if (!jdkInfo.version) {
					this.logger.error(__('Unable to locate the Java Development Kit') + '\n');
					this.logger.log(__('You can specify the location by setting the %s environment variable.', 'JAVA_HOME'.cyan) + '\n');
					process.exit(1);
				}

				if (!version.satisfies(jdkInfo.version, this.packageJson.vendorDependencies.java)) {
					this.logger.error(__('JDK version %s detected, but only version %s is supported', jdkInfo.version, this.packageJson.vendorDependencies.java) + '\n');
					process.exit(1);
				}

				this.jdkInfo = jdkInfo;
				callback();

			}.bind(this));
		}.bind(this));
	}.bind(this);
}