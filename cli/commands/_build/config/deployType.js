'use strict';

const appc = require('node-appc'),
	__ = appc.i18n(__dirname).__;

/**
 * Defines the --deploy-type option.
 *
 * @param {Number} order - The order to apply to this option.
 *
 * @returns {Object}
 */
module.exports = function configOptionDeployType(order) {
	return {
		abbr: 'D',
		desc: __('the type of deployment; only applicable when target is %s, %s, or %s', 'wp-emulator'.cyan, 'wp-device'.cyan, 'ws-local'.cyan), // or ws-simulator or ws-remote
		hint: __('type'),
		order: order,
		values: [ 'test', 'development', 'production' ]
	};
};
