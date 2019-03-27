var appc = require('node-appc'),
	__ = appc.i18n(__dirname).__,
	windowsPackageJson = appc.pkginfo.package(module);

/**
 * Defines the --architecture option.
 *
 * @param {Number} order - The order to apply to this option.
 *
 * @returns {Object}
 */
module.exports = function configOptionTargetArchitecture(order) {
	return {
		abbr: 'A',
		desc: __('the target architecture to build'),
		hint: __('architecture'),
		order: order,
		values: windowsPackageJson.architectures
	};
};