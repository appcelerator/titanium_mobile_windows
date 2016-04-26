var appc = require('node-appc'),
	fields = require('fields'),
	windowslib = require('windowslib'),
	__ = appc.i18n(__dirname).__;

/**
 * Defines the --device-id option.
 *
 * @param {Number} order - The order to apply to this option.
 *
 * @returns {Object}
 */
module.exports = function configOptionDeviceID(order) {
	var cli = this.cli;

	function validate(value, callback) {
		if (!value && value !== 0) {
			return callback(new Error(__('Invalid device id')));
		}

		var devices = this.getTargetDevices(),
			dev = null;

		// xd: first emulator
		// de: first device
		if (((cli.argv.target === 'wp-emulator' && value === 'xd') ||
			 (cli.argv.target === 'wp-device' && value === 'de')) && devices[0]) {

			// use wpsdk for device
			if (devices[0].wpsdk) {
				cli.argv['wp-sdk'] = devices[0].wpsdk;
			}
			return callback(null, devices[0].udid);
		}

		// validate device
		if (!devices.some(function (d) {
			// because we specify ignorecase below, we may get the name lowercased!
				if (d.udid == value || d.name.toLowerCase() === value.toLowerCase()) {
					dev = d;
					value = d.udid;
					return true;
				}
				return false;
			})) {
			return callback(new Error(__('Invalid device id "%s"', value)));
		}

		// use wpsdk specified for device
		if (dev.wpsdk) {
			cli.argv['wp-sdk'] = dev.wpsdk;
		}

		// check the device
		if (cli.argv.target === 'wp-device') {
			this.windowslibOptions['wpsdk'] = cli.argv['wp-sdk'];
		}
		callback(null, value);
	}

	return {
		abbr: 'C',
		desc: __('the Windows Phone device or emulator udid to launch the app on; only applicable when target is %s or %s', 'wp-emulator'.cyan, 'wp-device'.cyan),
		hint: 'udid',
		order: order,
		prompt: function (callback) {
			var devices = this.getTargetDevices(),
				maxLen = devices.reduce(function (a, b) { return Math.max(a, b.name.length); }, 0);

			if (!devices.length) {
				// this shouldn't happen
				throw new Error(
					cli.argv.target === 'wp-emulator'
						? __('No Windows Phone emulators found')
						: __('No Windows Phone devices found')
				);
			}

			callback(fields.select({
				title: cli.argv.target === 'wp-emulator'
					? __("Which emulator do you want to install your app on?")
					: __("Which device do you want to install your app on?"),
				promptLabel: __('Select by number or name'),
				default: devices.length && devices[0].name,
				formatters: {
					option: function (opt, idx, num) {
						return '  ' + num + appc.string.rpad(opt.name, maxLen).cyan + '  ' + __('(udid: %s)', opt.udid).grey;
					}
				},
				margin: '',
				autoSelectOne: true,
				numbered: true,
				relistOnError: true,
				complete: ['name', 'udid'],
				completeIgnoreCase: true,
				ignoreCase: true,
				suggest: false,
				optionLabel: 'name',
				optionValue: 'udid',
				options: devices,
				validate: validate.bind(this)
			}));
		}.bind(this),
		validate: validate.bind(this),
		verifyIfRequired: function (callback) {
			callback(!this.cli.argv['build-only']);
		}.bind(this)
	};
};
