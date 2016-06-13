var appc = require('node-appc'),
	windowslib = require('windowslib'),
	__ = appc.i18n(__dirname).__;

/**
 * Defines the --vs-target option.
 *
 * @param {Number} order - The order to apply to this option.
 *
 * @returns {Object}
 */
module.exports = function configOptionVisualStudioTarget(order) {
	var defaultTarget = (this.windowsInfo && this.windowsInfo.selectedVisualStudio) ? this.windowsInfo.selectedVisualStudio.version : undefined;

	var vsTargets = [];
	if (this.windowsInfo) {
		for (var version in this.windowsInfo.visualstudio) {
			vsTargets.push(version);
		}
	}

	return {
		abbr: 'V',
		default: defaultTarget,
		desc: __('the Visual Studio target to build for'),
		order: order,
		required: true,
		values: vsTargets
	};
};
