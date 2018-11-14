/**
 * This script downloads a pre-built SDK with iOS/Android, extracts it,
 * copies the built Windows SDK portion into it, modifies some files to denote
 * the Windows SDK was included and then zips it back up.
 */
const path = require('path');
const fs = require('fs');
const async = require('async');
const colors = require('colors');
const wrench = require('wrench');
const spawn = require('child_process').spawn;
const exec = require('child_process').exec;
const titanium = path.join(__dirname, 'node_modules', 'titanium', 'bin', 'titanium');
const DIST_DIR = path.join(__dirname, '..', '..', '..', 'dist');
const WINDOWS_DIST_DIR = path.join(DIST_DIR, 'windows');
	// Global vars
let hadWindowsSDK = false;

/**
 * Installs the latest SDK from master branch remotely, sets it as the default
 * SDK. We'll be hacking it to add our locally built Windows SDK into it.
 *
 * @param {string} branch branch name or URL of Titanium SDK to use
 * @param {Function} next callback function
 **/
function installSDK(branch, next) {
	var prc = spawn('node', [titanium, 'sdk', 'install', '-b', branch, '-d', '--no-colors']),
		sdkVersion;
	prc.stdout.on('data', function (data) {
		var value = data.toString().trim(),
			regexp = /You're up\-to\-date\. Version (\d+\.\d+\.\d+\.v\d+)/, // when SDK is already installed
			regexp2 = /Titanium SDK (\d+\.\d+\.\d+\.v\d+) successfully installed/, // when we installed the SDK
			matches = value.match(regexp);
		if (!matches) { // first regexp didn't find anything (check if normal successful install)
			matches = value.match(regexp2);
		}
		if (matches) { // did either regexp get the sdk version?
			sdkVersion = matches[1];
		}
		console.log(value);
	});
	prc.stderr.on('data', function (data) {
		console.error(data.toString().trim());
	});

	prc.on('close', function (code) {
		if (code != 0) {
			next("Failed to install SDK. Exit code: " + code);
		} else {
			console.log("Making sure " + sdkVersion + " is selected");
			var selectPrc = spawn('node', [titanium, 'sdk', 'select', sdkVersion]);
			selectPrc.stdout.on('data', function (data) {
				console.log(data.toString());
			});
			selectPrc.stderr.on('data', function (data) {
				console.error(data.toString().trim());
			});
			selectPrc.on('close', function (code) {
				if (code != 0) {
					next("Failed to select SDK. Exit code: " + code);
				} else {
					next(null, sdkVersion);
				}
			});
		}
	});
}

/**
 * Look up the full path to the SDK we just installed (the SDK we'll be hacking
 * to add our locally built Windows SDK into).
 *
 * @param {string} tiSDKVersion The version we installed (if we know it)
 * @param {Function} next callback function
 **/
function getSDKInstallDir(tiSDKVersion, next) {
	var prc = exec('node "' + titanium + '" info -o json -t titanium', function (error, stdout, stderr) {
		var out,
			selectedSDK;
		if (error !== null) {
			return next('Failed to get SDK install dir: ' + error);
		}

		out = JSON.parse(stdout);
		if (tiSDKVersion) {
			console.log("Looks like the SDK was already installed: " + tiSDKVersion);
			selectedSDK = tiSDKVersion;
		} else {
			selectedSDK = out['titaniumCLI']['selectedSDK'];
		}
		if (!selectedSDK) {
			console.error("There is no selected SDK for the titanium CLI and we didn't sniff the version on install!");
		}

		next(null, out['titanium'][selectedSDK]['path']);
	});
}

/**
 * Adds 'windows' into the list of supported platforms for a given SDK we're
 * hacking.
 *
 * @param {String} sdkPath path to the Titanium SDK we'll be hacking to copy our
 * 													locally built Windows SDK into
 * @param {Function} next callback function
 **/
function copyWindowsIntoSDK(sdkPath, distDir, next) {
	var dest = path.join(sdkPath, 'windows');
	if (fs.existsSync(dest)) {
		hadWindowsSDK = true;
		wrench.rmdirSyncRecursive(dest);
	}
	// TODO Be smarter about copying to speed it up? Only copy diff?
	wrench.copyDirSyncRecursive(distDir, dest);
	next();
}

/**
 * Adds 'windows' into the list of supported platforms for a given SDK we're
 * hacking.
 *
 * @param {String} sdkPath path to the Titanium SDK we'll be hacking
 * @param {Function} next callback function
 **/
function addWindowsToSDKManifest(sdkPath, next) {
	var manifest = path.join(sdkPath, 'manifest.json');

	fs.readFile(manifest, function (err, data) {
		if (err) {
			next(err);
		}
		// append 'windows' to platforms array
		var json = JSON.parse(data);
		json['platforms'].push('windows');
		// Write new JSON back to file
		fs.writeFile(manifest, JSON.stringify(json), function (err) {
			if (err) {
				next(err);
			}
			next();
		});
	});
}


function setupSDK(branch, location) {

	async.series([
		function (next) {
			// If this is already installed we don't re-install, thankfully
			console.log("Installing SDK from " + branch + " branch");
			installSDK(branch, function (err, version) {
				if (err) {
					return next(err);
				}
				tiSDKVersion = version;
				next();
			});
		},
		function (next) {
			getSDKInstallDir(tiSDKVersion, function (err, installPath) {
				if (err) {
					return next(err);
				}
				sdkPath = installPath;
				next();
			});
		},
		function (next) {
			console.log("Copying built Windows SDK from " + location + " into master SDK at " + sdkPath);
			copyWindowsIntoSDK(sdkPath, location, next);
		},
		function (next) {
			if (hadWindowsSDK) {
				next();
			} else {
				addWindowsToSDKManifest(sdkPath, next);
			}
		}
	]);
}

// When run as single script.
if (module.id === ".") {
	(function () {
		var program = require('commander');

		// TODO Allow specifying what device id?
		program
			.version('0.0.1')
			.option('-b, --branch [branch]', 'Specify the Titanium SDK build/branch to use for testing', 'master')
			.option('-l --location [location]', 'Location of the Windows build dist to use', WINDOWS_DIST_DIR)
			.parse(process.argv);

		setupSDK(program.branch, program.location, function(err, results) {
			if (err) {
				console.error(err.toString().red);
				process.exit(1);
			} else {
				process.exit(0);
			}
		});
	})();
}
