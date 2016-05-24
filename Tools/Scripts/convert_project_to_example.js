// TODO Assumes we have a ti project that has had ti build -p windows run for it and has a build folder
// TODO Create a folder under Examples with name matching project name
// copy Examples/NG/Native over into it

var path = require('path'),
	fs = require('fs'),
	async = require('async'),
	wrench = require('wrench'),
	EXAMPLES_DIR = path.join(__dirname, '..', '..', 'Examples'),
	NG_DIR = path.join(EXAMPLES_DIR, 'NG');

/**
 * Copies a file.
 * @param from
 * @param to
 */
function copyFile(from, to, next) {
	fs.createReadStream(from).pipe(fs.createWriteStream(to)).on('finish', function (err) {
		if (err) {
			next(err);
		}
		else {
			next();
		}
	});
}


function generateExample(projectPath, next) {
	var projectName = path.basename(projectPath),
		projectExample = path.join(EXAMPLES_DIR, projectName);

	// Copy NG over as base
	wrench.copyDirSyncRecursive(NG_DIR, projectExample);

	// Replace Examples/proj/Native/src with contents from build/windows/Native/src
	wrench.rmdirSyncRecursive(path.join(projectExample, 'Native', 'src'));
	wrench.copyDirSyncRecursive(path.join(projectPath, 'build', 'windows', 'Native', 'src'), path.join(projectExample, 'Native', 'src'));

	// Replace Examples/proj/Native/include with contents from build/windows/Native/include
	wrench.rmdirSyncRecursive(path.join(projectExample, 'Native', 'include'));
	wrench.copyDirSyncRecursive(path.join(projectPath, 'build', 'windows', 'Native', 'include'), path.join(projectExample, 'Native', 'include'));

	// Copy over the package manifests and replace references to the externalized strings in package manifests
	// FIXME We should fix this to actually set up PRIResource pointers to the i18n files.
	// Looks like CMake 3.4.0 hs this, just need to include resw files in the source listing like we do for js/jpg/png files
	async.each(['phone', 'store', 'win10'], function (name, next) {
		var packageName = 'Package.' + name + '.appxmanifest.in';

		fs.readFile(path.join(projectPath, 'build', 'windows', packageName), 'utf8', function (err, data) {
		  if (err) {
			return next(err);
		  }
		  var result = data.replace(/ms-resource:app_(name|description)/g, '@SHORT_NAME@')
		   fs.writeFile(path.join(projectExample, 'src', packageName), result, 'utf8', function (err) {
				 if (err) return next(err);
				 next();
			});
		});
	});

	// Replace src/Assets with projectPath/build/windows/Assets
	wrench.rmdirSyncRecursive(path.join(projectExample, 'src', 'Assets'));
	wrench.copyDirSyncRecursive(path.join(projectPath, 'build', 'windows', 'Assets'), path.join(projectExample, 'Assets'));


	// TODO How do we combine the CMakeLists.txt files together?
	fs.readFile(path.join(projectExample, 'CMakeLists.txt'), 'utf8', function (err, data) {
	  if (err) {
	    return next(err);
	  }

	  fs.readFile(path.join(projectPath, 'build', 'windows', 'CMakeLists.txt'), 'utf8', function (err, projectCmake) {
	    if (err) {
	      return next(err);
	    }

		// Get the contents of NG copy, split by newlines
		var lines = data.split(/\r?\n/);
		var replacement = projectCmake.split(/\r?\n/).slice(85, -51);
		// Cut out the section we don't want from NG, insert section from project and stick them together
		// (we keep lines 1-17, 20-117, 150+)
		// TODO Use lines 65-71 from projectCmake to replace lines 100-107?
		var result = lines.slice(0, 17).concat(['project(' + projectName + ')'], lines.slice(20, 117), replacement, lines.slice(150)).join("\n");
		  fs.writeFile(path.join(projectExample, 'CMakeLists.txt'), result, 'utf8', function (err) {
		     if (err) return next(err);
			 next();
		  });
	  });
	});
};

// When run as single script.
if (module.id === ".") {
	(function () {
		generateExample(path.resolve(process.argv[2]), function (err, results) {
			if (err) {
				console.error(err.toString().red);
				process.exit(1);
			} else {
				process.exit(0);
			}
		});
	})();
}
