var appc = require('node-appc'),
	DOMParser = require('xmldom').DOMParser,
	fs = require('fs'),
	os = require('os'),
	path = require('path'),
	ti = require('node-titanium-sdk'),
	__ = appc.i18n(__dirname).__;

/*
 Public API.
 */
exports.mixin = mixin;

/*
 Implementation.
 */
function mixin(WindowsBuilder) {
	WindowsBuilder.prototype.readBuildManifest = readBuildManifest;
	WindowsBuilder.prototype.readTiAppManifest = readTiAppManifest;
}

/**
 * Reads the build manifest, if exists, from the previous build so that we can
 * detect changes and force a rebuild.
 *
 * @param {Function} next - A function to call after the build manifest has been read.
 */
function readBuildManifest(next) {
	// read the build manifest from the last build, if exists, so we
	// can determine if we need to do a full rebuild
	this.buildManifest = {};

	if (fs.existsSync(this.buildManifestFile)) {
		try {
			this.buildManifest = JSON.parse(fs.readFileSync(this.buildManifestFile)) || {};
		} catch (e) {}
	}

	next();
}

/**
 * Read windows manifests from tiapp.xml
 */
function readTiAppManifest() {
	if (this.tiapp.windows.manifests) {
		return;
	}

	var tiapp = fs.readFileSync(path.join(this.projectDir, 'tiapp.xml'), 'utf8'),
		dom = new DOMParser().parseFromString(tiapp, 'text/xml'),
		root = dom.documentElement,
		_t = this, windows_node;

	appc.xml.forEachElement(root, function (elem) {
		if (elem.tagName == "windows") {
			windows_node = elem;
		}
	});

	if (!windows_node) {
		return;
	}

	appc.xml.forEachElement(windows_node, function (elem) {
		switch (elem.tagName) {
			case 'manifest':
				_t.tiapp.windows.manifests = _t.tiapp.windows.manifests || [];
				_t.tiapp.windows.manifests.push(elem.toString());
				break;
		}
	});
}
