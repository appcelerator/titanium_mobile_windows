'use strict';

const appc = require('node-appc');
const fs = require('fs-extra');
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
	WindowsBuilder.prototype.checkIfShouldForceRebuild = checkIfShouldForceRebuild;
	WindowsBuilder.prototype.checkIfNeedToRecompile = checkIfNeedToRecompile;
	WindowsBuilder.prototype.checkAppJs = checkAppJs;
}

/**
 * Runs a series of checks to see if the build state has changed and a rebuild must
 * be performed.
 *
 * @returns {Boolean} Returns true if a rebuild is needed.
 */
function checkIfShouldForceRebuild() {
	var manifest = this.buildManifest;

	if (this.cli.argv.force) {
		this.logger.info(__('Forcing rebuild: %s flag was set', '--force'.cyan));
		return true;
	}

	if (!fs.existsSync(this.buildManifestFile)) {
		this.logger.info(__('Forcing rebuild: %s does not exist', this.buildManifestFile.cyan));
		return true;
	}

	// check if the target changed
	if (this.target !== manifest.target) {
		this.logger.info(__('Forcing rebuild: target changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.target));
		this.logger.info('  ' + __('Now: %s', this.target));
		return true;
	}

	// check if the deploy type changed
	if (this.deployType !== manifest.deployType) {
		this.logger.info(__('Forcing rebuild: deploy type changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.deployType));
		this.logger.info('  ' + __('Now: %s', this.deployType));
		return true;
	}

	// if encryption is enabled, then we must recompile the java files
	if (this.encryptJS) {
		this.logger.info(__('Forcing rebuild: JavaScript files need to be re-encrypted'));
		return true;
	}

	// if encryptJS changed, then we need to recompile the java files
	if (this.encryptJS !== manifest.encryptJS) {
		this.logger.info(__('Forcing rebuild: JavaScript encryption flag changed'));
		this.logger.info('  ' + __('Was: %s', manifest.encryptJS));
		this.logger.info('  ' + __('Now: %s', this.encryptJS));
		return true;
	}

	// check if the titanium sdk paths are different
	if (this.platformPath !== manifest.platformPath) {
		this.logger.info(__('Forcing rebuild: Titanium SDK path changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.platformPath));
		this.logger.info('  ' + __('Now: %s', this.platformPath));
		return true;
	}

	// check the git hashes are different
	if (!manifest.gitHash || manifest.gitHash !== ti.manifest.githash) {
		this.logger.info(__('Forcing rebuild: githash changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.gitHash));
		this.logger.info('  ' + __('Now: %s', ti.manifest.githash));
		return true;
	}

	// check if the modules hashes are different
	if (this.modulesHash !== manifest.modulesHash) {
		this.logger.info(__('Forcing rebuild: modules hash changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.modulesHash));
		this.logger.info('  ' + __('Now: %s', this.modulesHash));
		return true;
	}

	if (this.modulesManifestHash !== manifest.modulesManifestHash) {
		this.logger.info(__('Forcing rebuild: module manifest hash changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.modulesManifestHash));
		this.logger.info('  ' + __('Now: %s', this.modulesManifestHash));
		return true;
	}

	if (this.modulesNativeHash !== manifest.modulesNativeHash) {
		this.logger.info(__('Forcing rebuild: native modules hash changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.modulesNativeHash));
		this.logger.info('  ' + __('Now: %s', this.modulesNativeHash));
		return true;
	}

	if (this.modulesBindingsHash !== manifest.modulesBindingsHash) {
		this.logger.info(__('Forcing rebuild: native modules bindings hash changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.modulesBindingsHash));
		this.logger.info('  ' + __('Now: %s', this.modulesBindingsHash));
		return true;
	}

	// next we check if any tiapp.xml values changed so we know if we need to reconstruct the main.m
	if (this.tiapp.name !== manifest.name) {
		this.logger.info(__('Forcing rebuild: tiapp.xml project name changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.name));
		this.logger.info('  ' + __('Now: %s', this.tiapp.name));
		return true;
	}

	if (this.tiapp.id !== manifest.id) {
		this.logger.info(__('Forcing rebuild: tiapp.xml app id changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.id));
		this.logger.info('  ' + __('Now: %s', this.tiapp.id));
		return true;
	}

	if (!this.tiapp.analytics !== !manifest.analytics) {
		this.logger.info(__('Forcing rebuild: tiapp.xml analytics flag changed since last build'));
		this.logger.info('  ' + __('Was: %s', !!manifest.analytics));
		this.logger.info('  ' + __('Now: %s', !!this.tiapp.analytics));
		return true;
	}
	if (this.tiapp.publisher !== manifest.publisher) {
		this.logger.info(__('Forcing rebuild: tiapp.xml publisher changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.publisher));
		this.logger.info('  ' + __('Now: %s', this.tiapp.publisher));
		return true;
	}

	if (this.tiapp.url !== manifest.url) {
		this.logger.info(__('Forcing rebuild: tiapp.xml url changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.url));
		this.logger.info('  ' + __('Now: %s', this.tiapp.url));
		return true;
	}

	if (this.tiapp.version !== manifest.version) {
		this.logger.info(__('Forcing rebuild: tiapp.xml version changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.version));
		this.logger.info('  ' + __('Now: %s', this.tiapp.version));
		return true;
	}

	if (this.tiapp.description !== manifest.description) {
		this.logger.info(__('Forcing rebuild: tiapp.xml description changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.description));
		this.logger.info('  ' + __('Now: %s', this.tiapp.description));
		return true;
	}

	if (this.tiapp.copyright !== manifest.copyright) {
		this.logger.info(__('Forcing rebuild: tiapp.xml copyright changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.copyright));
		this.logger.info('  ' + __('Now: %s', this.tiapp.copyright));
		return true;
	}

	if (this.tiapp.guid !== manifest.guid) {
		this.logger.info(__('Forcing rebuild: tiapp.xml guid changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.guid));
		this.logger.info('  ' + __('Now: %s', this.tiapp.guid));
		return true;
	}

	if (this.tiapp.icon !== manifest.icon) {
		this.logger.info(__('Forcing rebuild: tiapp.xml icon changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.icon));
		this.logger.info('  ' + __('Now: %s', this.tiapp.icon));
		return true;
	}

	if (this.propertiesHash !== manifest.propertiesHash) {
		this.logger.info(__('Forcing rebuild: tiapp.xml properties changed since last build'));
		this.logger.info('  ' + __('Was: %s', manifest.propertiesHash));
		this.logger.info('  ' + __('Now: %s', this.propertiesHash));
		return true;
	}

	return false;
}

/**
 * Checks if we need to rebuild the app and if so, deletes the previous build files.
 *
 * @param {Function} next - A function to call after checking if the app needs to be rebuilt.
 */
function checkIfNeedToRecompile(next) {
	// check if we need to do a rebuild
	this.forceRebuild = this.checkIfShouldForceRebuild();

	if (this.forceRebuild) {
		fs.emptyDirSync(this.buildDir);
	} else {
		fs.ensureDirSync(this.buildDir);
	}

	// now that we've read the build manifest, delete it so if this build
	// becomes incomplete, the next build will be a full rebuild
	fs.existsSync(this.buildManifestFile) && fs.unlinkSync(this.buildManifestFile);

	next();
}

/**
 * Checks that the app.js exists. This has to be done after the "build.pre.compile" event
 * has fired. This gives build hooks such as Alloy the ability to generate an app.js.
 *
 * @param {Function} next - A function to call after the app.js has been verified to exist.
 */
function checkAppJs(next) {
	// Make sure we have an app.js. This used to be validated in validate(), but since plugins like
	// Alloy generate an app.js, it may not have existed during validate(), but should exist now
	// that build.pre.compile was fired.
	ti.validateAppJsExists(this.projectDir, this.logger, 'windows');

	next();
}
