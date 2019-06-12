'use strict';

const appc = require('node-appc');
const fs = require('fs-extra');
const path = require('path');
const __ = appc.i18n(__dirname).__;

/*
 Public API.
 */
exports.mixin = mixin;

/*
 Implementation.
 */
function mixin(WindowsBuilder) {
	WindowsBuilder.prototype.processEncryption = processEncryption;
}

function processEncryption(next) {

	// figure out which titanium prep to run
	var titaniumPrep = 'titanium_prep.win32.exe';

	// encrypt the javascript
	var fileListing = path.join(this.buildDir, 'titanium_prep_listing.txt'),
		args = [this.tiapp.guid, this.tiapp.id, this.buildTargetAssetsDir, '--file-listing', fileListing];

	fs.writeFileSync(fileListing, this.jsFilesToEncrypt.join('\n'));

	var opts = {
			env: appc.util.mix({}, process.env, this.jdkInfo ? {
				// we force the JAVA_HOME so that titanium_prep doesn't complain
				'JAVA_HOME': this.jdkInfo.home
			} : {})
		},
		fatal = function fatal(err) {
			this.logger.error(__('Failed to encrypt JavaScript files'));
			err.msg.split('\n').forEach(this.logger.error);
			this.logger.log();
			process.exit(1);
		}.bind(this),
		titaniumPrepHook = this.cli.createHook('build.windows.titaniumprep', this, function (exe, args, opts, done) {
			var filesToEncrypt = args.slice(1);
			this.logger.info(__('Encrypting JavaScript files: %s', (exe + ' "' + filesToEncrypt.join('" "') + '"').cyan));
			appc.subprocess.run(exe, args, opts, function (code, out, err) {
				if (code) {
					return done({
						code: code,
						msg: err.trim() || out.trim()
					});
				}

				var mainCPPPath = path.join(this.buildDir, 'src', 'main.cpp'),
					mainCPPContents = fs.readFileSync(mainCPPPath, 'utf-8')
						.replace(/TitaniumWindows::Application\(\);/, 'TitaniumWindows::Application("' + out.trim() + '");');
				fs.writeFileSync(mainCPPPath, mainCPPContents);

				done();
			}.bind(this));
		});

	titaniumPrepHook(
		path.join(this.platformPath, titaniumPrep),
		args.slice(0),
		opts,
		function (err) {
			if (!err) {
				return next();
			}

			if (process.platform !== 'win32' || !/jvm\.dll/i.test(err.msg) && !/JAVA_HOME/i.test(err.msg)) {
				fatal(err);
			}

			// windows 32-bit failed, try again using 64-bit
			this.logger.debug(__('32-bit titanium prep failed, trying again using 64-bit'));
			titaniumPrep = 'titanium_prep.win64.exe';
			titaniumPrepHook(
				path.join(this.platformPath, titaniumPrep),
				args,
				opts,
				function (err) {
					if (err) {
						fatal(err);
					}
					next();
				}
			);
		}.bind(this)
	);
}
