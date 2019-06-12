/**
 * This script downloads a pre-built SDK with iOS/Android, extracts it,
 * copies the built Windows SDK portion into it, modifies some files to denote
 * the Windows SDK was included and then zips it back up.
 */
'use strict';

const path = require('path');
const fs = require('fs-extra');
const colors = require('colors'); // eslint-disable-line no-unused-vars
const spawn = require('child_process').spawn; // eslint-disable-line security/detect-child-process
const exec = require('child_process').exec; // eslint-disable-line security/detect-child-process
const TITANIUM = require.resolve('titanium');
const DIST_DIR = path.join(__dirname, '..', '..', '..', 'dist');
const WINDOWS_DIST_DIR = path.join(DIST_DIR, 'windows');

/**
 * Installs the latest SDK from master branch remotely, sets it as the default
 * SDK. We'll be hacking it to add our locally built Windows SDK into it.
 *
 * @param {string} branch branch name or URL of Titanium SDK to use
 * @return {Promise<string>}
 **/
function installSDK(branch) {
	const regexp = /You're up-to-date\. Version (\d+\.\d+\.\d+\.v\d+)/; // when SDK is already installed
	const regexp2 = /Titanium SDK (\d+\.\d+\.\d+\.v\d+) successfully installed/; // when we installed the SDK
	return new Promise((resolve, reject) => {
		console.log('Installing SDK from ' + branch + ' branch');
		let sdkVersion;
		const prc = spawn('node', [ TITANIUM, 'sdk', 'install', '-b', branch, '-d', '--no-colors' ]);
		prc.stdout.on('data', data => {
			const value = data.toString().trim();
			let matches = value.match(regexp);
			if (!matches) { // first regexp didn't find anything (check if normal successful install)
				matches = value.match(regexp2);
			}
			if (matches) { // did either regexp get the sdk version?
				sdkVersion = matches[1];
			}
			console.log(value);
		});
		prc.stderr.on('data', data => console.error(data.toString().trim()));

		prc.on('close', installCode => {
			if (installCode !== 0) {
				return reject(`Failed to install SDK. Exit code: ${installCode}`);
			}

			console.log('Making sure ' + sdkVersion + ' is selected');
			const selectPrc = spawn('node', [ TITANIUM, 'sdk', 'select', sdkVersion ]);
			selectPrc.stdout.on('data', data => console.log(data.toString()));
			selectPrc.stderr.on('data', data => console.error(data.toString().trim()));
			selectPrc.on('close', code => {
				if (code !== 0) {
					return reject(`Failed to select SDK. Exit code: ${code}`);
				}
				resolve(sdkVersion);
			});
		});
	});
}

/**
 * Look up the full path to the SDK we just installed (the SDK we'll be hacking
 * to add our locally built Windows SDK into).
 *
 * @param {string} tiSDKVersion The version we installed (if we know it)
 * @return {Promise<string>} path to the sdk
 **/
function getSDKInstallDir(tiSDKVersion) {
	return new Promise((resolve, reject) => {
		exec(`node "${TITANIUM}" info -o json -t titanium`, (error, stdout) => {
			if (error) {
				return reject(`Failed to get SDK install dir: ${error}`);
			}

			const out = JSON.parse(stdout);
			let selectedSDK;
			if (tiSDKVersion) {
				console.log(`Looks like the SDK was already installed: ${tiSDKVersion}`);
				selectedSDK = tiSDKVersion;
			} else {
				selectedSDK = out['titaniumCLI']['selectedSDK'];
			}
			if (!selectedSDK) {
				return reject('There is no selected SDK for the titanium CLI and we didn\'t sniff the version on install!');
			}

			resolve(out['titanium'][selectedSDK]['path']);
		});
	});
}

/**
 * Adds 'windows' into the list of supported platforms for a given SDK we're
 * hacking.
 *
 * @param {String} sdkPath path to the Titanium SDK we'll be hacking to copy our
 * 													locally built Windows SDK into
 * @param {String} distDir path to the Windows SDK we'll be copying
 * @return {Promise}
 **/
async function copyWindowsIntoSDK(sdkPath, distDir) {
	console.log(`Copying built Windows SDK from ${distDir} into SDK at ${sdkPath}`);
	const dest = path.join(sdkPath, 'windows');
	const hadWindowsSDK = await fs.pathExists(dest);
	if (hadWindowsSDK) {
		await fs.remove(dest);
	}
	// TODO Be smarter about copying to speed it up? Only copy diff?
	await fs.copy(distDir, dest);
	if (!hadWindowsSDK) {
		await addWindowsToSDKManifest(sdkPath);
	}
}

/**
 * Adds 'windows' into the list of supported platforms for a given SDK we're
 * hacking.
 *
 * @param {String} sdkPath path to the Titanium SDK we'll be hacking
 * @return {Promise}
 **/
async function addWindowsToSDKManifest(sdkPath) {
	const manifest = path.join(sdkPath, 'manifest.json');
	const json = await fs.readJson(manifest);
	// append 'windows' to platforms array
	json['platforms'].push('windows');
	// Write new JSON back to file
	await fs.writeJSON(manifest, json);
}

/**
 * [setupSDK description]
 * @param  {string} branch   [description]
 * @param  {string} location [description]
 * @return {Promise}          [description]
 */
async function setupSDK(branch, location) {
	// If this is already installed we don't re-install, thankfully
	const sdkVersion = await installSDK(branch);
	const sdkPath = await getSDKInstallDir(sdkVersion);
	await copyWindowsIntoSDK(sdkPath, location);
}

// When run as single script.
if (module.id === '.') {
	(function () {
		const program = require('commander');

		// TODO Allow specifying what device id?
		program
			.version('0.0.1')
			.option('-b, --branch [branch]', 'Specify the Titanium SDK build/branch to use for testing', 'master')
			.option('-l --location [location]', 'Location of the Windows build dist to use', WINDOWS_DIST_DIR)
			.parse(process.argv);

		setupSDK(program.branch, program.location)
			.then(() => process.exit(0))
			.catch(err => {
				console.error(err.toString().red);
				process.exit(1);
			});
	}());
}
