// TODO Assumes we have a ti project that has had ti build -p windows run for it and has a build folder
// TODO Create a folder under Examples with name matching project name
// copy Examples/NG/Native over into it
'use strict';

const path = require('path');
const fs = require('fs-extra');

const EXAMPLES_DIR = path.join(__dirname, '..', '..', 'Examples');
const NG_DIR = path.join(EXAMPLES_DIR, 'NG');

async function generateExample(projectPath) {
	const projectName = path.basename(projectPath);
	const projectExample = path.join(EXAMPLES_DIR, projectName);

	// Copy NG over as base
	await fs.copy(NG_DIR, projectExample);

	// Replace Examples/proj/Native/src with contents from build/windows/Native/src
	await fs.remove(path.join(projectExample, 'Native', 'src'));
	await fs.copy(path.join(projectPath, 'build', 'windows', 'Native', 'src'), path.join(projectExample, 'Native', 'src'));

	// Replace Examples/proj/Native/include with contents from build/windows/Native/include
	await fs.remove(path.join(projectExample, 'Native', 'include'));
	await fs.copy(path.join(projectPath, 'build', 'windows', 'Native', 'include'), path.join(projectExample, 'Native', 'include'));

	// Copy over the package manifests and replace references to the externalized strings in package manifests
	// FIXME We should fix this to actually set up PRIResource pointers to the i18n files.
	// Looks like CMake 3.4.0 hs this, just need to include resw files in the source listing like we do for js/jpg/png files

	const packageName = 'Package.win10.appxmanifest.in';
	const data = await fs.readFile(path.join(projectPath, 'build', 'windows', packageName), 'utf8');
	const appxmanifest = data.replace(/ms-resource:app_(name|description)/g, '@SHORT_NAME@');
	await fs.writeFile(path.join(projectExample, 'src', packageName), appxmanifest);

	// Replace src/Assets with projectPath/build/windows/Assets
	fs.remove(path.join(projectExample, 'src', 'Assets'));
	fs.copy(path.join(projectPath, 'build', 'windows', 'Assets'), path.join(projectExample, 'Assets'));

	// TODO How do we combine the CMakeLists.txt files together?
	const exampleCmake = await fs.readFile(path.join(projectExample, 'CMakeLists.txt'), 'utf8');
	const projectCmake = await fs.readFile(path.join(projectPath, 'build', 'windows', 'CMakeLists.txt'), 'utf8');

	// Get the contents of NG copy, split by newlines
	const lines = exampleCmake.split(/\r?\n/);
	const replacement = projectCmake.split(/\r?\n/).slice(85, -51);
	// Cut out the section we don't want from NG, insert section from project and stick them together
	// (we keep lines 1-17, 20-117, 150+)
	// TODO Use lines 65-71 from projectCmake to replace lines 100-107?
	const cmakeLists = lines.slice(0, 17).concat([ `project(${projectName})` ], lines.slice(20, 117), replacement, lines.slice(150)).join('\n');
	await fs.writeFile(path.join(projectExample, 'CMakeLists.txt'), cmakeLists, 'utf8');
}

// When run as single script.
if (module.id === '.') {
	(function () {
		generateExample(path.resolve(process.argv[2]))
			.then(() => process.exit(0))
			.catch(err => {
				console.error(err.toString().red);
				process.exit(1);
			});
	}());
}
