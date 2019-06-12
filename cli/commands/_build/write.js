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
	WindowsBuilder.prototype.writeBuildManifest = writeBuildManifest;
}

/**
 * Writes the build manifest file so subsequent builds will know if a rebuild is needed.
 *
 * @param {Function} next - A function to call after the build manifest has been written.
 */
function writeBuildManifest(next) {
	this.logger.info(__('Writing build manifest: %s', this.buildManifestFile.cyan));

	this.cli.createHook('build.windows.writeBuildManifest', this, function (manifest, cb) {
		fs.ensureDirSync(this.buildDir);
		fs.existsSync(this.buildManifestFile) && fs.unlinkSync(this.buildManifestFile);
		fs.writeFile(this.buildManifestFile, JSON.stringify(this.buildManifest = manifest, null, '\t'), cb);
	})({
		target: this.target,
		deployType: this.deployType,
		platformPath: this.platformPath,
		modulesHash: this.modulesHash,
		modulesManifestHash: this.modulesManifestHash,
		modulesNativeHash: this.modulesNativeHash,
		modulesBindingsHash: this.modulesBindingsHash,
		gitHash: ti.manifest.githash,
		outputDir: this.outputDir,
		name: this.tiapp.name,
		id: this.tiapp.id,
		analytics: this.tiapp.analytics,
		publisher: this.tiapp.publisher,
		url: this.tiapp.url,
		version: this.tiapp.version,
		buildNumber: this.buildNumber,
		description: this.tiapp.description,
		copyright: this.tiapp.copyright,
		guid: this.tiapp.guid,
		icon: this.tiapp.icon,
		skipJSMinification: !!this.cli.argv['skip-js-minify'],
		encryptJS: this.encryptJS,
		propertiesHash: this.propertiesHash
	}, next);
};
