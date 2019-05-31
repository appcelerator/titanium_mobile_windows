/**
 * Signs an app.
 *
 * @copyright
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 *
 * @license
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
'use strict';

const appc = require('node-appc');
const fs = require('fs');
const path = require('path');
const async = require('async');
const windowslib = require('windowslib');
const __ = appc.i18n(__dirname).__;
const CMAKE_TEMP_KEY = path.join(__dirname, '..', 'vendor', 'cmake', 'share', 'cmake-3.8', 'Templates', 'Windows', 'Windows_TemporaryKey.pfx');

exports.cliVersion = '>=3.2';

exports.init = function (logger, config, cli) {

	cli.on('build.pre.compile', {
		priority: 10000,
		post: function (builder, finished) {
			if (!/^ws-local|dist-winstore$/.test(builder.target) && builder.wpsdk !== '10.0') {
				return finished();
			}

			// If we're not distributing and we haven't specified a PFX,
			// Then use the included temp key from cmake
			if (!builder.wsCert && builder.target !== 'dist-winstore' &&
				!(builder.target === 'dist-phonestore' && builder.wpsdk === '10.0')) {
				logger.info(__('Using existing temporary pfx'));
				builder.certificatePath = CMAKE_TEMP_KEY;
				return windowslib.certs.thumbprint(CMAKE_TEMP_KEY, null, function (err, thumbprint) {
					builder.certificateThumbprint = thumbprint;
					err ? finished(err) : finished();
				});
			}

			var projectDir = builder.projectDir,
				wsCert = builder.wsCert;

			if (wsCert) {
				builder.certificatePath = wsCert;
				windowslib.certs.thumbprint(wsCert, builder.pfxPassword, function (err, thumbprint) {
					builder.certificateThumbprint = thumbprint;
					finished();
				});

				return;
			}

			var pvk = path.join(projectDir, 'generated.pvk'),
				cer = path.join(projectDir, 'generated.cer'),
				pfx = path.join(projectDir, 'generated.pfx');

			async.series([
				function checkCertificates(next) {
					if (fs.existsSync(pvk) && fs.existsSync(cer)) {
						logger.info(__('Using existing generated pvk and cer'));
						return next();
					}

					logger.info('');
					logger.info(__('Creating a certificate'));
					logger.info(__('Please follow the prompts'));
					windowslib.certs.generate(builder.publisherId, cer, builder.windowslibOptions, function (err, privateKey, certFile) {
						return !err ? next() : next(err || new Error('Certificate generation failed'));
					});
				},
				function checkPFX(next) {
					if (fs.existsSync(pfx)) {
						logger.info(__('Using existing generated pfx'));
						return next();
					}
					logger.info(__('Creating a PFX'));
					windowslib.certs.generatePFX(pvk, cer, pfx, builder.pfxPassword, builder.windowslibOptions, function (err, pfxFile) {
						if (err) {
							next(err);
						} else if (!fs.existsSync(pfx)) {
							next(new Error('PFX file was not generated at: "' + pfx + '"'));
						} else {
							next();
						}
					});
				},
				function makeSurePFXIsInstalled(next) {
					// No password?
					if (!builder.pfxPassword) {
						// Visual Studio can import the pfx on its own without us. Move on!
						return next();
					}
					// Otherwise...
					logger.info('');
					logger.info(__('Importing PFX'));
					logger.info(__('Please follow the prompts'));
					logger.info(__('(The default options will suffice)'));

					var pfxDir = path.dirname(pfx),
						pfxName = path.basename(pfx);
					require('child_process').exec('start /B /WAIT /D "' + pfxDir + '" ' + pfxName, function (err) {
						err ? next(err) : next();
					});
				},
				function usePFX(next) {
					builder.certificatePath = pfx;
					windowslib.certs.thumbprint(pfx, builder.pfxPassword, function (err, thumbprint) {
						builder.certificateThumbprint = thumbprint;
						err ? next(err) : next();
					});
				}
			], finished);
		}
	});
};
