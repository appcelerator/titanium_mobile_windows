var appc = require('node-appc'),
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
	WindowsBuilder.prototype.loginfo = loginfo;
}

/**
 * Displays information about the build settings.
 *
 * @param {Function} next - A function to call after the build settings have been logged.
 */
function loginfo(next) {
	switch (this.target) {
		// windows phone targets
		case 'wp-emulator':
			this.logger.info(this.deviceId
					? __('Building for Windows Phone emulator: %s', this.deviceId.cyan)
					: __('Building for Windows Phone emulator')
			);
			break;
		case 'wp-device':
			this.logger.info(this.deviceId
					? __('Building for Windows Phone device: %s', this.deviceId.cyan)
					: __('Building for Windows Phone device')
			);
			break;
		case 'dist-phonestore':
			this.logger.info(__('Building for Windows Phone Store'));
			break;

		// windows store targets
		case 'ws-simulator':
			this.logger.info(__('Building Windows Simulator'));
			break;
		case 'ws-local':
			this.logger.info(__('Building local Windows machine'));
			break;
		case 'ws-remote':
			this.logger.info(__('Building remote Windows machine'));
			break;
		case 'dist-winstore':
			this.logger.info(__('Building for Windows App Store'));
			break;
	}

	if (this.buildOnly) {
		this.logger.info(__('Performing build only'));
	}

	this.logger.debug(__('CMake generator name: %s', this.cmakeGeneratorName.cyan));
	this.logger.debug(__('CMAKE_SYSTEM_NAME: %s', this.cmakePlatform.cyan));
	this.logger.debug(__('CMAKE_SYSTEM_VERSION: %s', this.wpsdk.cyan));

	this.logger.debug(__('Titanium SDK Windows directory: %s', this.platformPath.cyan));
	this.logger.info(__('Deploy type: %s', this.deployType.cyan));

	if (this.debugHost) {
		this.logger.info(__('Debugging enabled via debug host: %s', String(this.debugHost).cyan));
	} else {
		this.logger.info(__('Debugging disabled'));
	}

	if (this.profilerHost) {
		this.logger.info(__('Profiler enabled via profiler host: %s', String(this.profilerHost).cyan));
	} else {
		this.logger.info(__('Profiler disabled'));
	}

	next();
}
