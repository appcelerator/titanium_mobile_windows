/**
 * Sets up a Windows machine for Titanium Mobile Windows/HAL/TitaniumKit development.
 *
 * @module setup
 *
 * @copyright
 * Copyright (c) 2015-Present by Appcelerator, Inc. All Rights Reserved.
 *
 * @license
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 *
 * @requires node-appc
 */
'use strict';

const fs = require('fs-extra');
const spawn = require('child_process').spawn; // eslint-disable-line security/detect-child-process
const os = require('os');
const http = require('http');
const path = require('path');

const colors = require('colors'); // eslint-disable-line no-unused-vars
const request = require('request');
const temp = require('temp');
const appc = require('node-appc');

// Constants
const HOME = process.env.HOME || process.env.USERPROFILE || process.env.APPDATA;
const WIN_10 = '10.0';
const JSC_10_URL = 'http://timobile.appcelerator.com.s3.amazonaws.com/jscore/dist/JavaScriptCore-Windows-1508145738839-win10.zip';
const JSC_DIR = 'JavaScriptCore'; // directory inside zipfile
const GTEST_URL = (os.platform() === 'win32') ? 'http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-windows.zip' : 'http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-osx.zip';
const GTEST_DIR = (os.platform() === 'win32') ? 'gtest-1.7.0-windows' : 'gtest-1.7.0'; // directory inside zipfile
const BOOST_URL = 'http://nchc.dl.sourceforge.net/project/boost/boost/1.60.0/boost_1_60_0.zip';
const BOOST_DIR = 'boost_1_60_0'; // directory inside zipfile
const SYMBOLS = {
	OK: '✓',
	ERROR: '✖'
};
// With node.js on Windows: use symbols available in terminal default fonts
if (os.platform() === 'win32') {
	SYMBOLS.OK = '\u221A';
	SYMBOLS.ERROR = '\u00D7';
}

function downloadURL(url) {
	return new Promise((resolve, reject) => {
		console.log(`Downloading ${url.cyan}`);

		const tempName = temp.path({ suffix: '.zip' });
		const tempDir = path.dirname(tempName);
		fs.ensureDirSync(tempDir);

		const tempStream = fs.createWriteStream(tempName);
		const req = request({ url: url });
		req.pipe(tempStream);

		req.on('error', function (err) {
			fs.existsSync(tempName) && fs.unlinkSync(tempName);
			reject('Failed to download URL: %s', err.toString() + '\n');
		});

		req.on('response', function (req) {
			if (req.statusCode >= 400) {  // something went wrong, abort
				return reject('Request failed with HTTP status code %s %s\n', req.statusCode, http.STATUS_CODES[req.statusCode] || '');
			}

			if (req.headers['content-length']) {
				// we know how big the file is, display the progress bar
				const total = parseInt(req.headers['content-length']);

				let bar;
				if (!process.argv.indexOf('--quiet') && !process.argv.indexOf('--no-progress-bars')) {
					bar = new appc.progress('  :paddedPercent [:bar] :etas', {
						complete: '='.cyan,
						incomplete: '.'.grey,
						width: 40,
						total: total
					});
				}

				req.on('data', function (buffer) {
					bar && bar.tick(buffer.length);
				});

				tempStream.on('close', function () {
					if (bar) {
						bar.tick(total);
						console.log('\n');
					}
					resolve(tempName);
				});
			} else {
				// we don't know how big the file is, display a spinner
				let busy;
				if (!process.argv.indexOf('--quiet') && !process.argv.indexOf('--no-progress-bars')) {
					busy = new appc.busyindicator();
					busy.start();
				}

				tempStream.on('close', function () {
					busy && busy.stop();
					busy && console.log();
					resolve(tempName);
				});
			}
		});
	});
}

/**
 * [extract description]
 * @param  {string} filename        [description]
 * @param  {string} installLocation [description]
 * @param  {boolean} keepFiles       [description]
 * @return {Promise}                 [description]
 */
function extract(filename, installLocation, keepFiles) {
	return new Promise((resolve, reject) => {
		console.log(`Extracting to ${installLocation.cyan}`);

		let bar;
		appc.zip.unzip(filename, installLocation, {
			visitor: function (entry, i, total) {
				if (i === 0) {
					if (!process.argv.indexOf('--quiet') && !process.argv.indexOf('--no-progress-bars')) {
						bar = new appc.progress('  :paddedPercent [:bar]', {
							complete: '='.cyan,
							incomplete: '.'.grey,
							width: 40,
							total: total
						});
					}
				}
				bar && bar.tick();
			}
		}, function (err, extracted, total) {
			if (err) {
				keepFiles || fs.unlinkSync(filename);
				const msg = `Failed to unzip: ${String(err).trim()}`;
				return reject(new Error(msg));
			}
			if (bar) {
				bar.tick(total);
				console.log('\n');
			}
			keepFiles || fs.unlinkSync(filename);
			resolve();
		});
	});
}

/**
 * [setENV description]
 * @param {string} key   [description]
 * @param {string} value [description]
 * @return {Promise}
 */
function setENV(key, value) {
	if (os.platform() !== 'win32') {
		const msg = `Please set the environment variable ${key} to ${value}
		The easiest way to achieve this is to append the following to your ~/.bash_profile:\n\nexport ${key}=${value}\n`;
		console.log(msg);
		return Promise.resolve();
		// return Promise.reject(new Error(msg));
	}

	return new Promise((resolve, reject) => {
		// Set the env var "permanently" for user
		const prc = spawn('setx', [ key, value ]);
		// prc.stdout.on('data', function (data) {
		//   console.log(data.toString());
		// });
		prc.on('close', function (code) {
			if (code !== 0) {
				return reject(new Error('Failed to run SETX'));
			}

			// FIXME Can't seem to run SET to also set for current session!
			console.log((SYMBOLS.OK + ' ' + key + ' set').green);
			resolve();
		});
	});
}

/**
 * Used to determine if there is an existing install of JSC and it's fromt he same URL as we want.
 * @param {string} destination place to download file
 * @param {string} url URL to download
 * @return {boolean}
 */
function isUpToDate(destination, url) {
	const urlFile = path.join(destination, 'SOURCE_URL');
	if (!fs.existsSync(destination) || !fs.existsSync(urlFile)) {
		return false;
	}

	// read contents of urlFile
	const contents = fs.readFileSync(urlFile).toString();
	// check if it's the same as url
	return contents === url;
}

/**
 * [writeSourceURL description]
 * @param  {string} destination directory to place SOURCE_URL file in
 * @param  {string} url URL to write to file
 * @return {Promise}
 */
function writeSourceURL(destination, url) {
	const urlFile = path.join(destination, 'SOURCE_URL');
	return fs.ensureDir(destination)
		.then(() => fs.writeFile(urlFile, url));
}

/**
 * Common logic for downloading a zip file from an URL for a dependency and setting up the right ENV var to point at the unzipped folder.
 * @param {String} envKey The ENV variable key we should look at or set
 * @param {String} defaultDest The default location to install if no ENV var is set (first time)
 * @param {String} expectedDir Expected enclosing directory isnide the zipfile. Used to rename the extract directory to the expected path in ENV
 * @param {String} url the URL of the zip file to download.
 * @return {Promise}
 **/
async function downloadIfNecessary(envKey, defaultDest, expectedDir, url) {
	const envValue = process.env[envKey];
	let destination = '';
	// retrieve environment variable
	if (typeof envValue !== 'undefined') {
		destination = path.normalize(envValue);
	} else {
		// set environment variable
		destination = defaultDest;
		await setENV(envKey, defaultDest);
	}

	// Does it already exist, and is it up to date?
	if (isUpToDate(destination, url)) {
		// Nothing to do, we're all set
		console.log((SYMBOLS.OK + ' ' + envKey + ' set').green);
		return;
	}

	// TODO What if we have local copy already in renamed folder? Look for that first!
	const filename = await downloadURL(url);
	// What if it _does_ exist and is out of date? We should "wipe it", or move it...
	if (fs.existsSync(destination)) {
		const urlFile = path.join(destination, 'SOURCE_URL');
		if (fs.existsSync(urlFile)) {
			const contents = fs.readFileSync(urlFile).toString();
			const base = path.basename(contents.slice(7), '.zip');
			const byURL = path.normalize(path.join(destination, '..', base));
			console.log(`Destination for ${url} already exists, moving existing directory to ${byURL} before extracting.`);
			if (!fs.existsSync(byURL)) {
				fs.copySync(destination, byURL);
			}
		}
		fs.removeSync(destination);
	}
	// Extract to parent of destination...
	const dest = path.normalize(path.join(destination, '..'));
	await extract(filename, dest, true);
	// Need to rename the extracted directory to match our expected destination!
	const extractedDir = path.join(dest, expectedDir);
	fs.copySync(extractedDir, destination);

	writeSourceURL(destination, url);
}

/**
 * Downloads Boost headers from BOOST_URL if necessary, and sets BOOST_ROOT env var to it.
 * @param {String} url source URL to grab Boost from.
 * @return {Promise}
 */
function setupBoost(url) {
	console.log('Setting up Boost libraries...');
	const boostRoot = path.join(HOME, 'boost');
	return downloadIfNecessary('BOOST_ROOT', boostRoot, BOOST_DIR, url);
}

/**
 * Downloads GTest from GTEST_URL if necessary, and sets GTEST_ROOT env var to it.
 * @param {String} url source URL to grab GTest from.
 * @return {Promise}
 */
function setupGTest(url) {
	console.log('Setting up GTest...');
	const gtestRoot = path.join(HOME, 'gtest');
	return downloadIfNecessary('GTEST_ROOT', gtestRoot, GTEST_DIR, url);
}

/**
 * Downloads JavaScriptCore from JSC_URL if necessary, and sets JavaScriptCore_HOME env var to it.
 * @param {String} sdkVersion '8.1' || '10'
 * @param {String} url source URL to grab JSC from.
 * @return {Promise}
 */
function setupJSC(sdkVersion, url) {
	console.log('Setting up JavaScriptCore pre-built libraries...');
	// Download to directory pegged to sdk version
	const jscHome = path.join(HOME, `JavaScriptCore-${sdkVersion}`);
	// Set env specific to windows sdk version
	return downloadIfNecessary(`JavaScriptCore_${sdkVersion}_HOME`, jscHome, JSC_DIR, url)
		.then(() => setENV('JavaScriptCore_HOME', jscHome));
}

/**
 * Modifies PATH to include bin folder of included cmake.
 * @returns {Promise}
 **/
function setupCMake() {
	console.log('Appending included cmake to PATH...');
	const cmakeBinPath = path.join(__dirname, '../../cli/vendor/cmake/bin');
	if (!process.env.PATH.includes(cmakeBinPath)) {
		console.log(`Appending ${cmakeBinPath} to PATH`);
		return setENV('PATH', `${process.env.PATH};${cmakeBinPath}`);
	}

	// If we can find cmake.exe on PATH, don't append it
	console.log((`${SYMBOLS.OK} Included cmake on PATH`).green);
	return Promise.resolve();
}

/**
 * @param {Object} [overrides] override URLs for downloads
 * @param {String} [overrides.boost] Source URL to use for Boost
 * @param {String} [overrides.gtest] Source URL to use for GTest
 * @param {String} [overrides.jsc] Source URL to use for JavaScriptCore
 * @return {Promise}
 **/
async function setup(overrides = {}) {
	await setupBoost(overrides.boost);
	await setupGTest(overrides.gtest);
	await setupJSC(overrides.sdkVersion, overrides.jsc);
	await setupCMake();
}

// When run as single script.
if (module.id === '.') {
	(function () {
		const program = require('commander');

		program
			.version('0.0.1')
			.option('-j, --javascriptcore [javascriptcore]', 'Override the source URL for JavaScriptCore', JSC_10_URL)
			.option('-g, --gtest [gtest]', 'Override the source URL for GTest', GTEST_URL)
			.option('-b, --boost [boost]', 'Override the source URL for Boost', BOOST_URL)
			.allowUnknownOption()
			.parse(process.argv);

		setup({
			boost: program.boost,
			gtest: program.gtest,
			jsc: program.javascriptcore,
			sdkVersion: WIN_10
		})
			.then(() => process.exit(0))
			.catch(err => {
				console.error((SYMBOLS.ERROR + ' ' + err.toString()).red);
				process.exit(1);
			});
	}());
}
