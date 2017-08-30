var appc = require('node-appc'),
	__ = appc.i18n(__dirname).__;


/**
 * Defines the --win-sdk option.
 *
 * @param {Number} order - The order to apply to this option.
 *
 * @returns {Object}
 */
module.exports = function configOptionSDK(order) {
	var sdkTargets = [],
		unsupportedTargets = ['8.0', '8.1'];

	if (this.windowsInfo) {
		for (var version in this.windowsInfo.windowsphone) {
			if (unsupportedTargets.indexOf(version) === -1) {
				sdkTargets.push(version);
			}
		}
		if (this.windowsInfo.windowsphone && this.windowsInfo.windowsphone[version]) {
			sdkTargets = sdkTargets.concat(this.windowsInfo.windowsphone[version].sdks);
		}
	}

	function isWindows10(wpsdk) {
		return (wpsdk && wpsdk.startsWith && wpsdk.startsWith('10.0'));
	}

	return {
		abbr: 'S',
		callback: function (value) {
			// target various Windows 10.0.X SDKs
			if (value.startsWith('10.0.')) {
				this.targetPlatformSdkVersion = value;
				this.cli.argv['win-sdk'] = '10.0';
			}
			var target = this.cli.argv['target'];
			// We can use built-in temp key for local/emulator builds. For dist,
			// insist on user/generated PFX when app requires one
			if (target == 'dist-winstore' || (isWindows10(value) && target == 'dist-phonestore')) {
				// --ws-cert will be deprecated in the future release
				if (this.cli.argv['ws-cert'] == undefined) {
					this.conf.options['win-cert'].required = true;
				}
			}
		}.bind(this),
		desc: __('the Windows SDK version; only used when target is %s, %s, or %s', 'wp-emulator'.cyan, 'wp-device'.cyan, 'dist-phonestore'.cyan),
		hint: __('version'),
		order: order,
		values: sdkTargets
	};
};
