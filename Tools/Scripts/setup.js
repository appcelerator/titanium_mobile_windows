/**
 * Sets up a Windows machine for Titanium Mobile Windows/HAL/TitaniumKit development.
 *
 * @module setup
 *
 * @copyright
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 *
 * @license
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 *
 * @requires node-appc
 */
var async = require('async'),
	fs = require('fs'),
	colors = require('colors'),
	http = require('http'),
	path = require('path'),
	request = require('request'),
	temp = require('temp'),
	wrench = require('wrench'),
	appc = require('node-appc'),
	HOME = process.env.HOME || process.env.USERPROFILE || process.env.APPDATA,
	spawn = require('child_process').spawn,
	os = require('os'),
	SYMBOLS = {
		OK: '✓',
		ERROR: '✖'
	},
	// Constants
	WIN_8_1 = '8.1',
	WIN_10 = '10.0',
	// Default JSC URL to build for Win 8.1. See https://jira.appcelerator.org/browse/TIMOB-20101
	JSC_81_URL = "http://timobile.appcelerator.com.s3.amazonaws.com/jscore/JavaScriptCore-Windows-1449751225.zip",
	// Default JSC URL for building against Win 10
	JSC_10_URL = "http://timobile.appcelerator.com.s3.amazonaws.com/jscore/JavaScriptCore-Windows-1449385087-win10.zip",
	GTEST_URL = (os.platform() === 'win32') ? "http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-windows.zip" : "http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-osx.zip",
	BOOST_URL = "http://timobile.appcelerator.com.s3.amazonaws.com/boost_1_57_0.zip";


// With node.js on Windows: use symbols available in terminal default fonts
if ('win32' == os.platform()) {
	SYMBOLS.OK = '\u221A';
	SYMBOLS.ERROR = '\u00D7';
}

function downloadURL(url, callback) {
	console.log('Downloading %s', url.cyan);

	var tempName = temp.path({ suffix: '.zip' }),
		tempDir = path.dirname(tempName);
	fs.existsSync(tempDir) || wrench.mkdirSyncRecursive(tempDir);

	var tempStream = fs.createWriteStream(tempName),
		req = request({ url: url });

	req.pipe(tempStream);

	req.on('error', function (err) {
		fs.existsSync(tempName) && fs.unlinkSync(tempName);
		console.log();
		console.error('Failed to download URL: %s', err.toString() + '\n');
		process.exit(1);
	});

	req.on('response', function (req) {
		if (req.statusCode >= 400) {
			// something went wrong, abort
			console.log();
			console.error('Request failed with HTTP status code %s %s\n', req.statusCode, http.STATUS_CODES[req.statusCode] || '');
			process.exit(1);
		} else if (req.headers['content-length']) {
			// we know how big the file is, display the progress bar
			var total = parseInt(req.headers['content-length']),
				bar;

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
				callback(tempName);
			});
		} else {
			// we don't know how big the file is, display a spinner
			var busy;

			if (!process.argv.indexOf('--quiet') && !process.argv.indexOf('--no-progress-bars')) {
				busy = new appc.busyindicator;
				busy.start();
			}

			tempStream.on('close', function () {
				busy && busy.stop();
				logger.log();
				callback(tempName);
			});
		}
	});
}

function extract(filename, installLocation, keepFiles, callback) {
	console.log('Extracting to %s', installLocation.cyan);

	var bar;

	appc.zip.unzip(filename, installLocation, {
		visitor: function (entry, i, total) {
			if (i == 0) {
				if(!process.argv.indexOf('--quiet') && !process.argv.indexOf('--no-progress-bars')) {
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
			console.log();
			console.error('Failed to unzip');
			String(err).trim().split('\n').forEach(console.error);
			console.log();
			process.exit(1);
		} else {
			if (bar) {
				bar.tick(total);
				console.log('\n');
			}
			keepFiles || fs.unlinkSync(filename);
			callback();
		}
	});
}

function setENV(key, value, next) {
	if (os.platform() === 'win32') {
		// Set the env var "permanently" for user
		var prc = spawn('setx', [key, value]);
		//prc.stdout.on('data', function (data) {
		//   console.log(data.toString());
		//});

		prc.on('close', function (code) {
			var setProcess;
			if (code != 0) {
				next("Failed to run SETX");
			} else {
				// FIXME Can't seem to run SET to also set for current session!
				console.log((SYMBOLS.OK + ' ' + key + ' set').green);
				next();
			}
		});
	} else {
		// FIXME Batch together all the changes and modify the ~/.bash_profile for the user (after making a copy)?
		console.log('Please set the environment variable %s to %s', key, value);
		console.log('The easiest way to achieve this to to append the following to your ~/.bash_profile:\n\nexport %s=%s\n', key, value);
		next();
	}
}

/**
 * Used to determine if there is an existing install of JSC and it's fromt he same URL as we want.
 */
function isUpToDate(destination, url) {
	var urlFile = path.join(destination, 'SOURCE_URL'),
		contents = '';
	if (!fs.existsSync(destination) || !fs.existsSync(urlFile)) {
		return false;
	}
	// read contents of urlFile
	contents = fs.readFileSync(urlFile).toString();
	// check if it's the same as url
	return contents === url;
}

function writeSourceURL(destination, url) {
	var urlFile = path.join(destination, 'SOURCE_URL');
	fs.writeFileSync(urlFile, url);
}

/**
 * Common logic for downloading a zip file from an URL for a dependency and setting up the right ENV var to point at the unzipped folder.
 **/
function downloadIfNecessary(envKey, defaultDest, url, next) {
	var envValue = process.env[envKey],
		destination = '';

	// retreive environment variable
	if (typeof envValue !== 'undefined') {
		destination = path.normalize(envValue);
	} else {
		// set environment variable
		destination = defaultDest;
		setENV(envKey, defaultDest);
	}

	// Does it already exist, and is it up to date?
	if (!isUpToDate(destination, url)) {
		downloadURL(url, function (filename) {
			// What if it _does_ exist and is out of date? We should "wipe it", or move it...
			if (fs.existsSync(destination)) {
				console.log("Destination for " + url + " already exists, wiping before extracting.");
				// TODO move/rename it instead of deleting it?
				wrench.rmdirSyncRecursive(destination);
			}
			// Etxract to parent of destionation...
			var dest = path.normalize(destination + "\\..");
			extract(filename, dest, true, function() {
				writeSourceURL(destination, url);
				next();
			});
		});
	} else {
		// Nothing to do, we're all set
		console.log((SYMBOLS.OK + ' ' + envKey + ' set').green);
		next();
	}
}

/**
 * Downloads Boost headers from BOOST_URL if necessary, and sets BOOST_ROOT env var to it.
 * @param [url] {String} override source URL to grab Boost from.
 * @param next {Function} callback function when finished
 */
function setupBoost(url, next) {
	if (typeof url == 'function') {
		next = url;
		url = BOOST_URL;
	}

	console.log("Setting up Boost libraries...");
	var boostRoot = path.join(HOME, "boost_1_57_0");
	downloadIfNecessary('BOOST_ROOT', boostRoot, url, next);
}

/**
 * Downloads GTest from GTEST_URL if necessary, and sets GTEST_ROOT env var to it.
 * @param [url] {String} override source URL to grab GTest from.
 * @param next {Function} callback function when finished
 */
function setupGTest(url, next) {
	if (typeof url == 'function') {
		next = url;
		url = GTEST_URL;
	}

	console.log("Setting up GTest...");
	var gtestRoot = path.join(HOME, "gtest-1.7.0-windows"); // FIXME What about mac?
	downloadIfNecessary('GTEST_ROOT', gtestRoot, url, next);
}

/**
 * Downloads JavaScriptCore from JSC_URL if necessary, and sets JavaScriptCore_HOME env var to it.
 * @param [url] {String} override source URL to grab JSC from.
 * @param next {Function} callback function when finished
 */
function setupJSC(url, next) {
	if (typeof url == 'function') {
		next = url;
		url = JSC_URL;
	}

	console.log("Setting up JavaScriptCore pre-built libraries...");
	var jscHome = path.join(HOME, "JavaScriptCore");
	downloadIfNecessary('JavaScriptCore_HOME', jscHome, url, next);
}

/**
 * Modifies PATH to include bin folder of included cmake.
 **/
function setupCMake(next) {
	console.log("Appending included cmake to PATH...");
	var cmakeBinPath = path.join(__dirname, '..', '..', 'cli', 'vendor', 'cmake', 'bin');
	if (process.env.PATH.indexOf(cmakeBinPath) == -1) {
		console.log("Appending %s to PATH", cmakeBinPath);
		setENV('PATH', process.env.PATH + ';' + cmakeBinPath, next);
	} else {
		// If we can find cmake.exe on PATH, don't append it
		console.log((SYMBOLS.OK + ' Included cmake on PATH').green);
		next();
	}
}

/**
 * @param [overrides] {Object}
 * @param [overrides.boost] {String} Source URL to use for Boost
 * @param [overrides.gtest] {String} Source URL to use for GTest
 * @param [overrides.jsc] {String} Source URL to use for JavaScriptCore
 * @param callback {Function} callback function when finished
 **/
function setup(overrides, callback) {
	if (typeof overrides == 'function') {
		callback = overrides;
		overrides = {};
	}
	// We could change this to parallel, but we'd have to ditch the progress bars above
	async.series([
		function (next) {
			setupBoost(overrides.boost, next);
		},
		function (next) {
			setupGTest(overrides.gtest, next);
		},
		function (next) {
			if (os.platform() === 'win32') {
				setupJSC(overrides.jsc, next);
			} else {
				next();
			}
		},
		// Add the included cmake bin dir to the user's PATH?
		setupCMake
		// TODO Download a VS2013/VS2015 version? (It's Huuuuuuge! Many GB!)
	], callback);
}

// public API
exports.setup = setup;
exports.setupBoost = setupBoost;
exports.setupGTest = setupGTest;
exports.setupJSC = setupJSC;
exports.setupCMake = setupCMake;

// When run as single script.
if (module.id === ".") {
	(function () {
		var program = require('commander');

		program
			.version('0.0.1')
			.option('-j, --javascriptcore [javascriptcore]', 'Override the source URL for JavaScriptCore')
			.option('-g, --gtest [gtest]', 'Override the source URL for GTest', GTEST_URL)
			.option('-b, --boost [boost]', 'Override the source URL for Boost', BOOST_URL)
			.option('-s, --sdk-version [version]', 'Target a specific Windows SDK version [version]', /^(8\.1|10\.0)$/, WIN_8_1)
			.allowUnknownOption()
			.parse(process.argv);

		// If not overriding the JSC URL pick default based on sdk version we're targetting
		if (!program.javascriptcore) {
			if (program.sdkVersion === WIN_10) {
				program.javascriptcore = JSC_10_URL;
			} else {
				program.javascriptcore = JSC_81_URL;
			}
		}

		setup({
			boost: program.boost,
			gtest: program.gtest,
			jsc: program.javascriptcore
		}, function (err, results) {
			if (err) {
				console.error((SYMBOLS.ERROR + ' ' + err.toString()).red);
				process.exit(1);
			}
			process.exit(0);
		});
	})();
}
