var appc = require('node-appc'),
	fields = require('fields'),
	path = require('path'),
	fs = require('fs'),
	windowslib = require('windowslib'),
	__ = appc.i18n(__dirname).__;

/**
 * Defines the --win-cert option.
 *
 * @param {Number} order - The order to apply to this option.
 *
 * @returns {Object}
 */
module.exports = function configOptionCert(order) {
	var defaultCert = undefined,
		certs = fs.readdirSync('./').filter(function (file) {
			return file.slice(-4).toLowerCase() === '.pfx';
		});
	if (certs.length > 1) {
		defaultCert = certs[0];
	}

	function validate(certFile, callback) {
		if (!certFile || certFile === '') {
			return callback();
		}

		certFile = appc.fs.resolvePath(certFile);

		if (!fs.existsSync(certFile) || !fs.statSync(certFile).isFile()) {
			return callback(new Error(__('Invalid cert file')));
		}

		callback(null, certFile);
	}

	return {
		abbr: 'R',
		desc: __('the location of the cert file; only applicable when target is %s or %s; or win-sdk is %s', 'ws-local'.cyan, 'dist-winstore'.cyan, '10.0'.cyan), // or ws-simulator or ws-remote
		hint: 'path',
		order: order,
		default: defaultCert,
		prompt: function (callback) {
			var certs = fs.readdirSync('./').filter(function (file) {
				return file.slice(-4).toLowerCase() === '.pfx';
			});
			if (certs.length === 1) {
				console.log('(Hint: Found a pfx file in working directory: ' + certs[0] + ')');
			}
			else if (certs.length > 1) {
				console.log('(Hint: Found these pfx files in working directory: ' + certs.join(', ') + ')');
			}
			callback(fields.file({
				promptLabel: __('What __pfx file__ should sign the app? (leave blank to generate)'),
				complete: true,
				showHidden: true,
				ignoreDirs: this.ignoreDirs,
				ignoreFiles: this.ignoreFiles,
				validate: validate
			}));
		},
		validate: validate,
		callback: function (value) {
			var certFile,
				stdout;

			if (!value || value === '') {
				// If dist-winstore or (dist-phonestore && 10.0), require
				// password because they'll be generating a PFX!
				if (this.cli.argv['target']  == 'dist-winstore' ||
					(this.getWindowsSDKTarget() == '10.0' && this.cli.argv['target'] == 'dist-phonestore')) {
					this.conf.options['pfx-password'].required = true;
				}
				// otherwise we'll use the built-in temp key w/no password
				return;
			}

			// At this point, assume we'll need a password by default
			this.conf.options['pfx-password'].required = true;

			// If we're generating it, keep password required
			certFile = appc.fs.resolvePath(value);
			if (!fs.existsSync(value) || !fs.statSync(certFile).isFile()) {
				return;
			}

			// If PFX exists and we can read it with an empty password, don't
			// require pfxPassword option
			try {
				stdout = execSync('certutil -p "" -dump "' + certFile + '"');
				if (stdout.indexOf('The system cannot find the file specified.') >= 0) {
					return; // keep password required. Thsi shouldn't ever happen!
				}
				else {
					// We got the cert details, password isn't required!
					stdout.split('Cert Hash(sha1): ')[1].split('\r')[0].split(' ').join('').toUpperCase();
					this.conf.options['pfx-password'].required = false;
					return;
				}
			} catch (e) {
				return; // keep password required
			}
		}.bind(this),
	};
};
