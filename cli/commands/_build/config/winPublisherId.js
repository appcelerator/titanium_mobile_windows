var appc = require('node-appc'),
	fields = require('fields'),
	__ = appc.i18n(__dirname).__;


/**
 * Defines the --win-publisher-id option.
 *
 * @param {Number} order - The order to apply to this option.
 *
 * @returns {Object}
 */
module.exports = function configOptionWindowsPublisherID(order) {
	function validate(value, callback) {
		if (!/^(CN=)?[0-9a-f]{8}-[0-9a-f]{4}-[1-5][0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$/i.test(value)) {
			return callback(new Error(__('Invalid "%s" value "%s"', '--win-publisher-id', value)));
		}
		callback(null, value);
	}

	function shouldPrompt(argv) {
		// You need to check abbreviated form too here because they are not expanded yet
		return (argv['T'] === 'dist-phonestore' || argv['target']      === 'dist-phonestore') ||
		       (argv['T'] === 'dist-winstore'   || argv['target']      === 'dist-winstore') ||
		       (argv['D'] === 'production'      || argv['deploy-type'] === 'production');
	}

	return {
		abbr: 'I',
		default: !shouldPrompt(this.cli.argv) ? '00000000-0000-1000-8000-000000000000' : this.config.get('windows.publisherId'),
		desc: __('your Windows publisher ID, obtained from %s', 'https://dev.windows.com/en-us/Account/Management'.cyan),
		hint: __('id'),
		order: order,
		prompt: function (callback) {
			callback(fields.text({
				promptLabel: __('What is your __Windows Publisher ID__?'),
				validate: validate
			}));
		}.bind(this),
		validate: validate,
		required: true,
		verifyIfRequired: function (callback) {
			callback(shouldPrompt(this.cli.argv));
		}.bind(this)
	};
};