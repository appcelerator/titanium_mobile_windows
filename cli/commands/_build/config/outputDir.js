'use strict';

const appc = require('node-appc'),
	fields = require('fields'),
	path = require('path'),
	__ = appc.i18n(__dirname).__;

/**
 * Defines the --output-dir option.
 *
 * @param {Number} order - The order to apply to this option.
 *
 * @returns {Object}
 */
module.exports = function configOptionOutputDir(order) {
	function validate(outputDir, callback) {
		callback(outputDir || !this.conf.options['output-dir'].required ? null : new Error(__('Invalid output directory')), outputDir);
	}

	return {
		abbr: 'O',
		desc: __('the output directory to copy the built app; only applicable when target is %s or %s', 'dist-phonestore'.cyan, 'dist-winstore'.cyan),
		hint: 'dir',
		order: order,
		prompt: function (callback) {
			callback(fields.file({
				promptLabel: __('Where would you like the built app saved?'),
				default: this.cli.argv['project-dir'] && path.join(this.cli.argv['project-dir'], 'dist'),
				complete: true,
				showHidden: true,
				ignoreDirs: this.ignoreDirs,
				ignoreFiles: /.*/,
				validate: validate.bind(this)
			}));
		}.bind(this),
		validate: validate.bind(this)
	};
};
