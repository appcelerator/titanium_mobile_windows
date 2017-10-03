'use strict';

const appc = require('node-appc'),
	fields = require('fields'),
	__ = appc.i18n(__dirname).__;

/**
 * Defines the --wp-publisher-guid option.
 *
 * @param {Number} order - The order to apply to this option.
 *
 * @returns {Object}
 */
module.exports = function configOptionWPPublisherGUID(order) {
	function validate(value, callback) {
		if (!/^[0-9a-f]{8}-[0-9a-f]{4}-[1-5][0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i.test(value)) {
			return callback(new Error(__('Invalid "%s" value "%s"', '--wp-publisher-guid', value)));
		}
		callback(null, value);
	}

	return {
		abbr: 'G',
		default: this.config.get('windows.phone.publisherGuid'),
		desc: __('Your Windows Phone publisher ID, obtained from %s; only applicable when target is %s, %s, or %s', 'https://dev.windows.com/en-us/Account/Management'.cyan, 'wp-emulator'.cyan, 'wp-device'.cyan, 'dist-phonestore'.cyan),
		hint: __('guid'),
		order: order,
		prompt: function (callback) {
			callback(fields.text({
				promptLabel: __('What is your __Windows Phone Publisher ID__?'),
				validate: validate
			}));
		},
		validate: validate
	};
};
