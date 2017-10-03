'use strict';

const appc = require('node-appc'),
	fields = require('fields'),
	__ = appc.i18n(__dirname).__;

/**
 * Defines the --win-product-guid option.
 *
 * @param {Number} order - The order to apply to this option.
 *
 * @returns {Object}
 */
module.exports = function configOptionProductID(order) {
	function validate(value, callback) {
		if (!/^[0-9a-f]{8}-[0-9a-f]{4}-[1-5][0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i.test(value)) {
			return callback(new Error(__('Invalid "%s" value "%s"', '--win-product-guid', value)));
		}
		callback(null, value);
	}

	return {
		abbr: 'H',
		default: this.config.get('windows.phone.productId'),
		desc: __('The Windows 8 product ID, used for upgrading Win 8 apps to Win 8.1. Discussed at %s; only applicable when target is %s, %s, or %s', 'https://msdn.microsoft.com/en-us/library/windows/apps/Dn642081(v=VS.105).aspx'.cyan, 'wp-emulator'.cyan, 'wp-device'.cyan, 'dist-phonestore'.cyan),
		hint: __('productid'),
		order: order,
		prompt: function (callback) {
			callback(fields.text({
				promptLabel: __('What is your __Windows 8 Phone Product ID__?'),
				validate: validate
			}));
		},
		validate: validate
	};
};
