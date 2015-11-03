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
	home = process.env.HOME || process.env.USERPROFILE || process.env.APPDATA,
	spawn = require('child_process').spawn,
	os = require('os'),
	symbols = {
	  ok: '✓',
	  err: '✖',
	  dot: '․'
	},
	JSC_URL = "http://timobile.appcelerator.com.s3.amazonaws.com/jscore/JavaScriptCore-Windows-1439837221.zip",
	GTEST_URL = (os.platform() === 'win32') ? "http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-windows.zip" : "http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-osx.zip",
	BOOST_URL = "http://timobile.appcelerator.com.s3.amazonaws.com/boost_1_57_0.zip";


// With node.js on Windows: use symbols available in terminal default fonts
if ('win32' == os.platform()) {
	symbols.ok = '\u221A';
	symbols.err = '\u00D7';
	symbols.dot = '.';
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
	var prc;
	if (os.platform() === 'win32') {
		// Set the env var "permanently" for user
		prc = spawn('SetX', [key, value]);
		//prc.stdout.on('data', function (data) {
		//   console.log(data.toString());
		//});

		prc.on('close', function (code) {
			var setProcess;
			if (code != 0) {
				next("Failed to run SETX");
			} else {
				// FIXME Can't seem to run SET to also set for current session!
				console.log((symbols.ok + ' ' + key + ' set').green);
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
		destination = (typeof envValue !== 'undefined') ? path.normalize(envValue) : defaultDest;

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
		console.log((symbols.ok + ' ' + envKey + ' set').green);
		next();
	}	
}

/**
 * Downloads Boost headers from BOOST_URL if necessary, and sets BOOST_ROOT env var to it.
 */
function setupBoost(next) {
	console.log("Setting up Boost libraries...");
	var boostRoot = path.join(home, "boost_1_57_0");
	downloadIfNecessary('BOOST_ROOT', boostRoot, BOOST_URL, next);
}

/**
 * Downloads GTest from GTEST_URL if necessary, and sets GTEST_ROOT env var to it.
 */
function setupGTest(next) {
	console.log("Setting up GTest...");
	var gtestRoot = path.join(home, "gtest-1.7.0-windows"); // FIXME What about mac?
	downloadIfNecessary('GTEST_ROOT', gtestRoot, GTEST_URL, next);
}

/**
 * Downloads JavaScriptCore from JSC_URL if necessary, and sets JavaScriptCore_HOME env var to it.
 */
function setupJSC(next) {
	console.log("Setting up JavaScriptCore pre-built libraries...");
	var jscHome = path.join(home, "JavaScriptCore");
	downloadIfNecessary('JavaScriptCore_HOME', jscHome, JSC_URL, next);
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
		console.log((symbols.ok + ' Included cmake on PATH').green);
		next();
	}
}

function setup(callback) {
	// We could change this to series, but we'd have to ditch the progress bars above
	async.series([
		function (next) {
			setupBoost(next);
		},
		function (next) {
			setupGTest(next);
		},
		function (next) {
			if (os.platform() === 'win32') {
				setupJSC(next);
			} else {
				next(); // TODO Do we need to do anything for Mac?
			}
		},
		// Add the included cmake bin dir to the user's PATH?
		function (next) {
			setupCMake(next);
		}
		// TODO Download a VS2013 version? (It's Huuuuuuge! Many GB!)
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
	setup(function (err, results) {
		if (err) {
			console.error((symbols.error + ' ' + err.toString()).red);
			process.exit(1);
		}
		process.exit(0);
	});
}
