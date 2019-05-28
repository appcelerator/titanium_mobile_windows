/**
 * Windows Titanium Module Generator
 *
 * Copyright (c) 2015-Present by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
'use strict';

// FIXME: This script needs lots of love to work right again! We've changed our sources quite a bit since it was written!
const fs = require('fs-extra');
const ejs = require('ejs');
const inq = require('inquirer');
const path = require('path');
const walkSync = require('klaw-sync');

const MODULE_FOLDER = 'module_template';
const SOURCE_FOLDER = '../../../Source/';

const JSCA = fs.readJsonSync('api.jsca');

// slice off node and generate.js from args
const myArgs = process.argv.slice(2);
if (myArgs.length === 0) {
	// Interactive module selection
	const modules = Object.keys(JSCA).filter(name => name.includes('Titanium'));
	inq.prompt(
		[ {
			type: 'list',
			name: 'module',
			message: 'Select a module to generate',
			choices: modules
		} ],
		result => {
			generateModule(result.module, JSCA)
				.then(() => process.exit(0))
				.catch(err => {
					console.error(err);
					process.exit(1);
				});
		});
} else {
	// user passed in proxy name as argument
	generateModule(myArgs[0], JSCA)
		.then(() => process.exit(0))
		.catch(err => {
			console.error(err);
			process.exit(1);
		});
}

/**
 * [generateModule description]
 * @param  {string} module fully qualified module name
 * @param  {object} jsca the jsca definitions (from api.jsca stolen from an SDK)
 * @return {Promise}        [description]
 */
function generateModule(module, jsca) {
	console.log(`Generating ${module}...`);

	const module_data = jsca[module];
	const module_classes = module.split('.');
	const module_name = module_classes[module_classes.length - 1];
	const module_parent = module_classes[1];
	const module_path = divideArray(module_classes, '/', 1);
	const sub_class = (module_classes.length > 2);
	const namespace = (sub_class ? module_name : module_name + 'Module');
	const full_namespace =  (sub_class ? divideArray(module_classes, '::', 1) : module_name + 'Module');

	const data = {
		module,
		module_parent,
		module_classes,
		module_path,
		sub_class,
		full_namespace,
		namespace,
		name: module_name,
		name_upper: module_name.toUpperCase(),
		name_lower: module_name.toLowerCase(),
		data: module_data
	};

	const filterFn = item => {
		return item.stats.isFile() && (!sub_class || path.basename(item.path).startsWith('Module'));
	};
	const files = walkSync(MODULE_FOLDER, { filter: filterFn });
	const allPromises = Promise.all(files.map(file => render(file.path)));
	return allPromises.then(() => includeModule(data));
}

/**
 * [render description]
 * @param  {string} file [description]
 * @param  {object} data  object holding rendering info
 * @param  {boolean} data.sub_class whether this is a sub class
 * @param  {string} data.module_parent portion of fully qualified module name
 * @param  {string} data.name last portion of fully qualified module name (base name)
 * @param  {string} data.module_path path of module
 * @return {Promise}      [description]
 */
async function render(file, data) {
	console.log(`Rendering ${file}...`);
	const contents = await fs.readFile(file, 'utf8');
	const r = ejs.render(contents, data);
	if (data.sub_class && !file.contains('TitaniumKit')) {
		file = file.replace(/Module/, data.module_parent);
	}
	const replacement = file.contains('UI' + path.sep + 'src') ? data.name : data.module_path;
	const filePath = SOURCE_FOLDER + file.substring(MODULE_FOLDER.length + 1).replace(/Module/g, replacement);
	await writeFile(filePath, r);
}

/**
 * [backupAndModifyFile description]
 * @param  {string} filepath [description]
 * @param  {map<regexp, string>} mods replacement pairs
 * @return {Promise}          [description]
 */
async function backupAndModifyFile(filepath, mods) {
	// - making a backup file
	const backup = filepath + '.bak';
	await fs.rename(filepath, backup);
	// - reading the backup file
	const contents = await fs.readFile(backup, 'utf8');
	// - making modifications
	let data = contents;
	for (const [ regexp, replacement ] of mods) {
		data = modify(data, regexp, replacement);
	}
	// - writing the modified file
	await writeFile(filepath, data);
}

/**
 * [includeModule description]
 * @param  {object} module_data [description]
 * @return {Promise}             [description]
 */
async function includeModule(module_data) {
	console.log(`Implementing ${module_data.module}...`);

	const isUI = module_data.module_parent === 'UI';

	if (module_data.sub_class) {
		let path_tik_module_hpp = SOURCE_FOLDER + 'TitaniumKit/include/Titanium/' + module_data.module_parent + '.hpp';
		let path_tik_module_cpp = SOURCE_FOLDER + 'TitaniumKit/src/' + module_data.module_parent + '.cpp';
		if (!fs.existsSync(path_tik_module_hpp)) {
			path_tik_module_hpp = SOURCE_FOLDER + 'TitaniumKit/include/Titanium/' + module_data.module_parent + 'Module.hpp';
			path_tik_module_cpp = SOURCE_FOLDER + 'TitaniumKit/src/' + module_data.module_parent + 'Module.cpp';
		}
		// for path_tik_module_hpp
		const regex_tikm_head_1 = /Module.hpp"/g;
		const mod_tikm_head_1 = 'Module.hpp"\n'
								+ '#include "Titanium/' + module_data.module_path + '.hpp"';

		// for path_tik_module_hpp
		const regex_tikm_method_1 = /TITANIUM_FUNCTION_DEF\(createWindow\);/g;
		const mod_tikm_method_1 = 'TITANIUM_FUNCTION_DEF(createWindow);\n\t\t'
								+ 'TITANIUM_FUNCTION_DEF(create' + module_data.name + ');';

		const parentReplacements = new Map([ [ regex_tikm_head_1, mod_tikm_head_1 ], [ regex_tikm_method_1, mod_tikm_method_1 ] ]);
		await backupAndModifyFile(path_tik_module_hpp, parentReplacements);

		// for path_tik_module_cpp
		const regex_tikm_method_2 = /TITANIUM_FUNCTION\(UIModule, createWebView\)/g;
		const mod_tikm_method_2 = 'TITANIUM_FUNCTION(UIModule, create' + module_data.name + ')\n\t'
								+ '{\n\t\t'
								+ 'ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);\n\t\t'
								+ 'CREATE_TITANIUM_UI(' + module_data.name + ');\n\t'
								+ '}\n\n\tTITANIUM_FUNCTION(UIModule, createWebView)';
		await backupAndModifyFile(path_tik_module_cpp, new Map([ [ regex_tikm_method_2, mod_tikm_method_2 ] ]));

		// CMakeLists.txt
		const path_module_cmake = SOURCE_FOLDER + module_data.module_parent + '/CMakeLists.txt';
		const regex_tim_cmake_1 = new RegExp('set\\(SOURCE_' + module_data.module_parent + '\n', 'g'); // eslint-disable-line security/detect-non-literal-regexp
		const mod_tim_cmake_1 = 'set(SOURCE_' + module_data.module_parent + '\n'
								+ '  include/TitaniumWindows/' + module_data.module_path + '.hpp\n'
								+ '  src/' + (isUI ? module_data.name : module_data.module_path) + '.cpp\n';
		await backupAndModifyFile(path_module_cmake, new Map([ [ regex_tim_cmake_1, mod_tim_cmake_1 ] ]));
	} else {
		// Titanium CMakeLists.txt modifications
		const path_ti_cmake = SOURCE_FOLDER + 'Titanium/CMakeLists.txt';
		const regex_ti_cmake_1 = /get_filename_component\(UI_SOURCE_DIR/g;
		const mod_ti_cmake_1 = 'get_filename_component(' + module_data.name + '_SOURCE_DIR        ${PROJECT_SOURCE_DIR}/../' // eslint-disable-line no-template-curly-in-string
			+ module_data.name + '        ABSOLUTE)\n'
			+ 'get_filename_component(UI_SOURCE_DIR';

		const regex_ti_cmake_2 = /add_subdirectory\(\${UI_SOURCE_DIR}/g;
		const mod_ti_cmake_2 = 'add_subdirectory(${' + module_data.name + '_SOURCE_DIR}    ${CMAKE_CURRENT_BINARY_DIR}/' // eslint-disable-line no-template-curly-in-string
			+ module_data.name + '    EXCLUDE_FROM_ALL)\n'
			+ 'add_subdirectory(${UI_SOURCE_DIR}'; // eslint-disable-line no-template-curly-in-string

		const regex_ti_cmake_3 = / {2}\$<TARGET_PROPERTY:TitaniumWindows_UI/g;
		const mod_ti_cmake_3 = '  $<TARGET_PROPERTY:TitaniumWindows_' + module_data.name + ',INTERFACE_INCLUDE_DIRECTORIES>\n'
													+ '  $<TARGET_PROPERTY:TitaniumWindows_UI';

		const regex_ti_cmake_4 = / {2}TitaniumWindows_UI/g;
		const mod_ti_cmake_4 = '  TitaniumWindows_' + module_data.name + '\n'
								+ '  TitaniumWindows_UI';
		await backupAndModifyFile(path_ti_cmake, new Map([
			[ regex_ti_cmake_1, mod_ti_cmake_1 ],
			[ regex_ti_cmake_2, mod_ti_cmake_2 ],
			[ regex_ti_cmake_3, mod_ti_cmake_3 ],
			[ regex_ti_cmake_4, mod_ti_cmake_4 ] ]));

		// Titanium build_and_test.sh modifications
		const path_ti_bt = SOURCE_FOLDER + 'Titanium/build_and_test.sh';
		const regex_ti_bt_1 = /cmd\+=" -DTitaniumWindows_UI_/g;
		const mod_ti_bt_1 = 'cmd+=" -DTitaniumWindows_' + module_data.name + '_DISABLE_TESTS=ON"\n'
								+ 'cmd+=" -DTitaniumWindows_UI_';
		await backupAndModifyFile(path_ti_bt, new Map([ [ regex_ti_bt_1, mod_ti_bt_1 ] ]));

		// Titanium TiModule.hpp modifications
		const path_tik_ti = SOURCE_FOLDER + 'TitaniumKit/include/Titanium/TiModule.hpp';
		const regex_tik_ti_1 = /UIModule.hpp"/g;
		const mod_tik_ti_1 = 'UIModule.hpp"\n'
								+ '#include "Titanium/' + module_data.name + '.hpp"';
		await backupAndModifyFile(path_tik_ti, new Map([ [ regex_tik_ti_1, mod_tik_ti_1 ] ]));
	}
}

/**
 * Like String.join, but starting from a specified index
 * @param  {string[]} array   [description]
 * @param  {string} divider [description]
 * @param  {number} [i]       [description]
 * @return {string}         [description]
 */
function divideArray(array, divider, i) {
	let ret = '';
	if (i == undefined) { // eslint-disable-line eqeqeq
		i = 0;
	}
	while (i < array.length) {
		ret += array[i];
		if (i < array.length - 1) {
			ret += divider;
		}
		i++;
	}
	return ret;
}

/**
 * Replaces a regexp with a string, returns replaced string. Logs if failed to change the string.
 * @param  {string} string  [description]
 * @param  {RegExp} regex   [description]
 * @param  {string} replace [description]
 * @return {string}         [description]
 */
function modify(string, regex, replace) {
	const result = string.replace(regex, replace);
	if (result === string) {
		console.log(`Error: Could not find signature '${regex}' in: ${string}`);
	}
	return result;
}

async function writeFile(filename, content) {
	await fs.ensureDir(path.dirname(filename));
	await fs.writeFile(filename, content);
}
