
/**
 * Displays installed Titanium SDKs and installs new SDKs.
 *
 * @module commands/sdk
 *
 * @see SdkSubcommands
 *
 * @copyright
 * Copyright (c) 2009-2013 by Appcelerator, Inc. All Rights Reserved.
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
	};

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
			
			bar = new appc.progress('  :paddedPercent [:bar] :etas', {
				complete: '='.cyan,
				incomplete: '.'.grey,
				width: 40,
				total: total
			});

			req.on('data', function (buffer) {
				bar.tick(buffer.length);
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

			if (!cli.argv.quiet && !!cli.argv['progress-bars']) {
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
				bar = new appc.progress('  :paddedPercent [:bar]', {
					complete: '='.cyan,
					incomplete: '.'.grey,
					width: 40,
					total: total
				});
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
		// RSet the env var "permanently" for user
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

// We could change this to series, but we'd have to ditch the progress bars above
async.series([
	function (next) {
		var boostRoot = path.join(home, "boost_1_57_0");
		// assume if env var is set that the location also exists
    	if (typeof process.env.BOOST_ROOT !== 'undefined') {
    		console.log((symbols.ok + ' BOOST_ROOT set').green);
    		next();
    		// if env var isn't set, but destination exists, just set env var
    	} else if (fs.existsSync(boostRoot)) {
    		setENV('BOOST_ROOT', boostRoot, next);
    	} else {
    		// no env var and no destination. Download, extract, and set env var
		    downloadURL("http://timobile.appcelerator.com.s3.amazonaws.com/boost_1_57_0.zip", function (filename) {
				extract(filename, home, true, function () {
					setENV('BOOST_ROOT', boostRoot, next);
				});
			});
		}
    },
    function (next) {
    	var gtest_root = path.join(home, "gtest-1.7.0-windows");
    	if (typeof process.env.GTEST_ROOT !== 'undefined') {
    		console.log((symbols.ok + ' GTEST_ROOT set').green);
    		next();
    	}
    	else if (fs.existsSync(gtest_root)) {
			setENV('GTEST_ROOT', gtest_root, next);
    	}
		else {
			downloadURL("http://timobile.appcelerator.com.s3.amazonaws.com/gtest-1.7.0-windows.zip", function (filename) {
				extract(filename, home, true, function () {
					setENV('GTEST_ROOT', gtest_root, next);
				});
			});
		}
    },
    function (next) {
    	var jscHome = path.join(home, "JavaScriptCore-Windows-1411436814");
    	if (typeof process.env.JavaScriptCore_HOME !== 'undefined') {
    		console.log((symbols.ok + ' JavaScriptCore_HOME set').green);
    		next();
    	} else if (fs.existsSync(jscHome)) {
    		setENV('JavaScriptCore_HOME', jscHome, next);
    	} else {
		    downloadURL("http://timobile.appcelerator.com.s3.amazonaws.com/jscore/JavaScriptCore-Windows-1411436814.zip", function (filename) {
				extract(filename, home, true, function() {
					setENV('JavaScriptCore_HOME', jscHome, next);
				});
			});
		}
    },
    // Add the included cmake bin dir to the user's PATH?
    function (next) {
	    var cmakeBinPath = path.join(__dirname, '..', '..', 'cli', 'vendor', 'cmake', 'bin');
	    if (process.env.PATH.indexOf(cmakeBinPath) == -1) {
			console.log("Appending %s to PATH", cmakeBinPath);
	    	setENV('PATH', process.env.PATH + ';' + cmakeBinPath, next);
		} else {
			// If we can find cmake.exe on PATH, don't append it
			console.log((symbols.ok + ' Included cmake on PATH').green);
			next();
		}
    },
    // Change Windows PowerShell permissions
    function (next) {
    	if (os.platform() === 'win32') {
    		var output = '',
				prc = spawn(process.env.SystemRoot + '\\system32\\WindowsPowerShell\\v1.0\\powershell.exe', ['Get-ExecutionPolicy', '-Scope', 'CurrentUser']);
			prc.stdout.on('data', function (data) {
			    output += data.toString();
			});

			prc.on('close', function (code) {
				output = output.trim();
				// Check to make sure Execution Policy is liberal enough for us!
				if (output !== 'RemoteSigned' && output !== 'Unrestricted') {
		    		console.log("Changing PowerShell policy to RemoteSigned for CLI");
					var p = spawn(process.env.SystemRoot + '\\system32\\WindowsPowerShell\\v1.0\\powershell.exe', ['Set-ExecutionPolicy', '-ExecutionPolicy', 'RemoteSigned', '-Scope', 'CurrentUser']);
					p.stdout.on('data', function (data) {
					    console.log(data.toString());
					});

					p.on('close', function (code) {
						if (code != 0) {
							next("Failed to change PowerShell policy");
						} else {
							console.log((symbols.ok + ' PowerShell ExecutionPolicy set to "RemoteSigned"').green);
					    	next();
						}
					});
				}
				else {
					console.log((symbols.ok + ' PowerShell ExecutionPolicy at least "RemoteSigned"').green);
					next();
				}
			});
		} else {
			next();
		}
    }
    // TODO Download VS2013 Express? (It's Huuuuuuge! 6.61 GB!)
], function (err, results) {
	if (err) {
		console.error((symbols.error + ' ' + err.toString()).red);
		process.exit(1);
	}
});
