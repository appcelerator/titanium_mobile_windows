var appc = require('node-appc'),
	__ = appc.i18n(__dirname).__;


/**
 * Defines the --wp-sdk option.
 *
 * @param {Number} order - The order to apply to this option.
 *
 * @returns {Object}
 */
module.exports = function configOptionWPSDK(order) {
	var defaultTarget = '10.0',
		sdkTargets = [],
		unsupportedTargets = ['8.0'];

	if (this.windowsInfo) {
		for (var version in this.windowsInfo.windowsphone) {
			if (unsupportedTargets.indexOf(version) === -1) {
				sdkTargets.push(version);
				sdkTargets = sdkTargets.concat(this.windowsInfo.windowsphone[version].sdks);
			}
			if (this.windowsInfo.windowsphone[version].selected) {
				defaultTarget = version;
			}
		}
	}

	return {
		abbr: 'S',
		callback: function (value) {
			// target various Windows 10.0.X SDKs
			if (value.startsWith('10.0.')) {
				this.targetSdk = value;
				this.cli.argv['wp-sdk'] = '10.0';
			}
			// We can use built-in temp key for local/emulator builds. For dist,
			// insist on user/generated PFX when app requires one
			if (this.conf.options['target'] == 'dist-winstore' ||
				(value == '10.0' && this.conf.options['target'] == 'dist-phonestore')) {
				this.conf.options['ws-cert'].required = true;
			}
		}.bind(this),
		default: defaultTarget,
		desc: __('the Windows Phone SDK version; only used when target is %s, %s, or %s', 'wp-emulator'.cyan, 'wp-device'.cyan, 'dist-phonestore'.cyan),
		hint: __('version'),
		order: order,
		values: sdkTargets
	};
};
