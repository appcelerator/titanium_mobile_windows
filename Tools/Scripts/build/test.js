
var path = require('path'),
	fs = require('fs'),
	async = require('async'),
	colors = require('colors'),
	wrench = require('wrench'),
	ejs = require('ejs'),
	spawn = require('child_process').spawn,
	exec = require('child_process').exec,
	titanium = path.join(__dirname, 'node_modules', 'titanium', 'bin', 'titanium'),
	sdkPath,
	hadWindowsSDK = false,
	testResults,
	jsonResults;

console.log(titanium);

function installSDK(next) {
	var prc = spawn('node', [titanium, 'sdk', 'install', '-b', 'master', '-d']);
	prc.stdout.on('data', function (data) {
	   console.log(data.toString().trim());
	});

	prc.on('close', function (code) {
		var setProcess;
		if (code != 0) {
			cnext("Failed to install master SDK");
		} else {
			next();
		}
	});
}

function getSDKInstallDir(next) {
	var prc = exec('node "' + titanium + '" info -o json -t titanium', function (error, stdout, stderr) {
		var out,
			selectedSDK;
		if (error !== null) {
		  next('Failed to get SDK install dir: ' + error);
		}

		out = JSON.parse(stdout);
		selectedSDK = out['titaniumCLI']['selectedSDK'];

		sdkPath = out['titanium'][selectedSDK]['path'];
		next();
	});
}

function copyWindowsIntoSDK(sdkPath, next) {
	var windowsSDKDir = path.join(__dirname, '..', '..', '..', 'dist', 'windows'),
		dest = path.join(sdkPath, 'windows');
	if (fs.existsSync(dest)) {
		hadWindowsSDK = true;
		wrench.rmdirSyncRecursive(dest);
	}
	// TODO Be smarter about copying to speed it up? Only copy diff? 
	wrench.copyDirSyncRecursive(windowsSDKDir, dest);
	next();
}

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

function generateWindowsProject(next) {
	var projectDir = path.join(__dirname, 'mocha'),
		prc;
	// If the project already exists, wipe it
	if (fs.existsSync(projectDir)) {
		wrench.rmdirSyncRecursive(projectDir);
	}
	prc = spawn('node', [titanium, 'create', '-t', 'app', '-p', 'windows', '-n', 'mocha', '--id', 'com.appcelerator.mocha.testing', '-u', 'http://www.appcelerator.com', '-d', '.', '--no-prompt']);

	prc.on('close', function (code) {
		var setProcess;
		if (code != 0) {
			next("Failed to create project");
		} else {
			next();
		}
	});
}

function copyMochaAssets(next) {
	var mochaAssetsDir = path.join(__dirname, '..', '..', '..', 'Examples', 'NMocha', 'src', 'Assets'),
		dest = path.join(__dirname, 'mocha', 'Resources');
	wrench.copyDirSyncRecursive(mochaAssetsDir, dest, {
    	forceDelete: true
	});
	next();
}

function runBuild(next) {
	var prc,
		inResults = false;
	prc = spawn('node', [titanium, 'build', '-d', 'mocha', '-p', 'windows', '-T', 'wp-emulator', '--wp-publisher-guid', '00000000-0000-1000-8000-000000000000', '-C', '8-1-1', '--no-prompt', '--no-colors']);
	prc.stdout.on('data', function (data) {
		var lines = data.toString().trim().match(/^.*([\n\r]+|$)/gm);
		for (var i = 0; i < lines.length; i++) {
	    	var str = lines[i],
	    		index = -1;
	    	if (inResults) {
				if ((index = str.indexOf('[INFO]')) != -1) {
					str = str.slice(index + 8).trim();
				}
				if ((index = str.indexOf('!TEST_RESULTS_STOP!')) != -1) {
					str = str.slice(0, index).trim();
					inResults = false;
				}

				testResults += str;
				if (!inResults) {
					testResults = testResults.trim(); // for some reason, there's a leading space that is messing with everything!
					prc.kill();
					break;
				}
			}
			else if ((index = str.indexOf('!TEST_RESULTS_START!')) != -1) {
				inResults = true;
				testResults = str.substr(index + 20).trim();
			}
		}
		
	});
//	prc.stderr.on('data', function (data) {
//		//console.log(data.toString());
//	});

	prc.on('close', function (code) {
		next();
	});
}

function parseTestResults(testResults, next) {
	// preserve newlines, etc - use valid JSON
	testResults = testResults.replace(/\\n/g, "\\n")  
               .replace(/\\'/g, "\\'")
               .replace(/\\"/g, '\\"')
               .replace(/\\&/g, "\\&")
               .replace(/\\r/g, "\\r")
               .replace(/\\t/g, "\\t")
               .replace(/\\b/g, "\\b")
               .replace(/\\f/g, "\\f");
	// remove non-printable and other non-valid JSON chars
	testResults = testResults.replace(/[\u0000-\u0019]+/g,""); 
	jsonResults = JSON.parse(testResults);
	next();
}

function outputJUnitXML(jsonResults, next) {
	// We need to go through the results and separate them out into suites!
	var suites = {},
		keys = [],
		values = [],
		r = '';
	jsonResults.results.forEach(function(item) {
		var s = suites[item.suite] || {tests: [], suite: item.suite, duration: 0, passes: 0, failures: 0, start:''}; // suite name to group by
		s.tests.unshift(item);
		s.duration += item.duration;
		if (item.state == 'failed') {
			s.failures += 1;
		} else if (item.state == 'passed') {
			s.passes += 1;
		}
		suites[item.suite] = s;
	});
	keys = Object.keys(suites);
	values = keys.map(function(v) { return suites[v]; });
	var r = ejs.render('' + fs.readFileSync(path.join('.', 'junit.xml.ejs')),  { 'suites': values });

	// Write the JUnit XML to a file
	fs.writeFileSync(path.join('..', '..', '..', 'dist', 'junit_report.xml'), r);
	next();
}

async.series([
	function (next) {
		// If this is already installed we don't re-install, thankfully
		console.log("Installing SDK from master branch");
		installSDK(next);
	},
	function (next) {
		getSDKInstallDir(next);
	},
	function (next) {
		console.log("Copying built Windows SDK into master SDK");
		copyWindowsIntoSDK(sdkPath, next);
	},
	function (next) {
		if (hadWindowsSDK) {
			next();
		} else {
			addWindowsToSDKManifest(sdkPath, next);
		}
	},
	function (next) {
		console.log("Generating Windows project");
		generateWindowsProject(next);
	},
	function (next) {
		console.log("Copying test scripts into project");
		copyMochaAssets(next);
	},
	function (next) {
		console.log("Launching test project in simulator");
		runBuild(next);
	},
	function (next) {
		parseTestResults(testResults, next);
	},
	function (next) {
		outputJUnitXML(jsonResults, next);
	}
], function (err, results) {
	if (err) {
		console.error(err.toString().red);
		process.exit(1);
	}
});
