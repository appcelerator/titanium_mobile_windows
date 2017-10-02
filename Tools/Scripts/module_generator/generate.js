'use strict';

/**
 * Windows Titanium Module Generator
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

var fs = require('fs.extra'),
	ejs = require('ejs'),
	inq = require('inquirer'),
	path = require('path'),
	async = require('async');

const API_FILE = 'api.jsca';

const MODULE_FOLDER = 'module_template';
const SOURCE_FOLDER = '../../../Source/';

String.prototype.contains = function (str) {
	return this.indexOf(str) != -1;
};
String.prototype.endsWith = function (str) {
	return this.indexOf(str, this.length - str.length) !== -1;
};
String.prototype.startsWith = function (str) {
	return this.indexOf(str, 0) !== -1;
};
String.prototype.repeat = function (x) {
	return (new Array(x + 1)).join(this);
};

var jsca = JSON.parse(fs.readFileSync('api.jsca'));

// slice off node and generate.js from args
var myArgs = process.argv.slice(2);
if (myArgs.length == 0) {
	// Interactive module selection
	var modules = [];
	for (module in jsca) {
		if (module.contains('Titanium')) {
			modules.push(module);
		}
	}
	inq.prompt(
		[ {
			type: 'list',
			name: 'module',
			message: 'Select a module to generate',
			choices: modules
		} ],
		function (result) {
			generateModule(result.module);
		}
	);
} else {
	// user passed in proxy name as argument
	generateModule(myArgs[0]);
}

function generateModule(module) {

	console.log('Generating ' + module + '...');

	var module_data = jsca[module];

	var module_classes = module.split('.');
	var module_name = module_classes[module_classes.length - 1];
	var module_parent = module_classes[1];
	var module_path = divideArray(module_classes, '/', 1);
	var sub_class = (module_classes.length > 2);
	var namespace = (sub_class ? module_name : module_name + 'Module');
	var full_namespace =  (sub_class ? divideArray(module_classes, '::', 1) : module_name + 'Module');

	var data = { module: module, module_parent: module_parent, module_classes: module_classes, module_path: module_path, sub_class: sub_class, full_namespace: full_namespace, namespace: namespace, name:module_name, name_upper:module_name.toUpperCase(), name_lower:module_name.toLowerCase(), data: module_data };

	var walker = fs.walk(MODULE_FOLDER);
	walker.on('file', function (root, stat, next) {
		if ((sub_class && stat.name.startsWith('Module')) || !sub_class) {
			var file = path.join(root, stat.name);
			try {
				var r = ejs.render('' + fs.readFileSync(file), data);

				if (sub_class && !root.contains('TitaniumKit')) {
					file = file.replace(/Module/, module_parent);
				}

				var filePath = SOURCE_FOLDER + file.substring(MODULE_FOLDER.length + 1).replace(/Module/g, file.contains('UI' + path.sep + 'src') ? module_name : module_path);
				writeFile(filePath, r);
			} catch (e) {
				console.log(e.toString());
			}
		}
		next();
	});
	walker.on('end', function () {
		includeModule(data);
	});
}

function includeModule(module_data) {

	console.log('Implementing ' + module_data.module + '...');

	var isUI = module_data.module_parent == 'UI';

	// File paths
	var path_tik_cmake = SOURCE_FOLDER + 'TitaniumKit/CMakeLists.txt';
	var path_ti_cmake = SOURCE_FOLDER + 'Titanium/CMakeLists.txt';
	var path_ti_bt = SOURCE_FOLDER + 'Titanium/build_and_test.sh';
	var path_tik_ti = SOURCE_FOLDER + 'TitaniumKit/include/Titanium/Titanium.hpp';
	var path_ti_tiw = SOURCE_FOLDER + 'Titanium/src/TitaniumWindows.cpp';
	var path_tik_app_hpp = SOURCE_FOLDER + 'TitaniumKit/include/Titanium/ApplicationBuilder.hpp';
	var path_tik_app_cpp = SOURCE_FOLDER + 'TitaniumKit/src/ApplicationBuilder.cpp';
	var path_tik_module_hpp = SOURCE_FOLDER + 'TitaniumKit/include/Titanium/' + module_data.module_parent + '.hpp';
	var path_tik_module_cpp = SOURCE_FOLDER + 'TitaniumKit/src/' + module_data.module_parent + '.cpp';
	if (!fs.existsSync(path_tik_module_hpp)) {
		path_tik_module_hpp = SOURCE_FOLDER + 'TitaniumKit/include/Titanium/' + module_data.module_parent + 'Module.hpp';
		path_tik_module_cpp = SOURCE_FOLDER + 'TitaniumKit/src/' + module_data.module_parent + 'Module.cpp';
	}
	var path_module_cmake = SOURCE_FOLDER + module_data.module_parent + '/CMakeLists.txt';

	// TitaniumKit CMakeLists.txt modifications
	var regex_tik_cmake_1 = /source_group\(TitaniumKit /g;
	var mod_tik_cmake_1 = 'set(SOURCE_' + module_data.name + '\n'
		                  + '  include/Titanium/' + module_data.module_path + '.hpp\n'
		                  + '  src/' + module_data.module_path + '.cpp\n'
		                  + ')\n\n'
																										+ 'source_group(TitaniumKit ';

	var regex_tik_cmake_2 = /source_group\(TitaniumKit\\\\UI /g;
	var mod_tik_cmake_2 = 'source_group(TitaniumKit\\\\' + module_data.module_path.replace(/\//g, '\\\\') + '       FILES ${SOURCE_' + module_data.name + '})\n'
																										+ 'source_group(TitaniumKit\\\\UI ';

	var regex_tik_cmake_3 = / {2}\${SOURCE_UI}/g;
	var mod_tik_cmake_3 = '  ${SOURCE_' + module_data.name + '}\n'
																										+ '  ${SOURCE_UI}';

	var regex_tik_cmake_ui = /set\(SOURCE_UI/g;
	var mod_tik_cmake_ui = 'set(SOURCE_UI\n'
		                   + '  include/Titanium/' + module_data.module_path + '.hpp\n'
		                   + '  src/' + module_data.module_path + '.cpp';

	// Titaniumkit ApplicationBuilder.hpp modifications
	var regex_tik_app_1 = /JSObject ViewObject\(/g;
	var mod_tik_app_1 = 'JSObject ' + module_data.name + 'Object() const TITANIUM_NOEXCEPT;\n\t\t'
						+ 'ApplicationBuilder& ' + module_data.name + 'Object(const JSObject&) TITANIUM_NOEXCEPT;\n\n\t\t'
    					+ 'JSObject ViewObject(';

	var regex_tik_app_2 = / view__;/g;
	var mod_tik_app_2 = ' view__;\n\t\t'
    					+ 'JSObject ' + module_data.name.toLowerCase() + '__;';

	// Titaniumkit ApplicationBuilder.cpp modifications
	var regex_tik_app_3 = /UI::View>::Class\(\)\)\),/g;
	var mod_tik_app_3 = 'UI::View>::Class())),\n	      '
    					+ module_data.name.toLowerCase() + '__(js_context__.CreateObject(JSExport<Titanium::' + module_data.full_namespace + '>::Class())),';

	var regex_tik_app_4 = /UIModule.hpp\"/g;
	var mod_tik_app_4 = 'UIModule.hpp"\n'
    					+ '#include "Titanium/' + module_data.module_path + '.hpp"';

	var regex_tik_app_5 = /JSString builtin/g;
	var mod_tik_app_5 = (module_data.sub_class ? '\t\t' + module_data.module_parent.toLowerCase() + '__' : 'titanium') + '.SetProperty("' + module_data.name + '", ' + module_data.name.toLowerCase() + '__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});\n'
    					+ 'JSString builtin';

	var regex_tik_app_6 = /JSObject ApplicationBuilder::ViewObject\(/g;
	var mod_tik_app_6 = 'JSObject ApplicationBuilder::' + module_data.name + 'Object() const TITANIUM_NOEXCEPT\n\t'
						+ '{\n\t\t'
						+ 'return ' + module_data.name.toLowerCase() + '__;\n\t'
						+ '}\n\n\t'
						+ 'ApplicationBuilder& ApplicationBuilder::' + module_data.name + 'Object(const JSObject& ' + module_data.name + ') TITANIUM_NOEXCEPT\n\t'
						+ '{\n\t\t'
						+ module_data.name.toLowerCase() + '__ = ' + module_data.name + ';\n\t\t'
						+ 'return *this;\n\t'
						+ '}\n\n\t'
    					+ 'JSObject ApplicationBuilder::ViewObject(';

	// Titanium CMakeLists.txt modifications
	var regex_ti_cmake_1 = /get_filename_component\(UI_SOURCE_DIR/g;
	var mod_ti_cmake_1 = 'get_filename_component(' + module_data.name + '_SOURCE_DIR        ${PROJECT_SOURCE_DIR}/../' + module_data.name + '        ABSOLUTE)\n'
																									+ 'get_filename_component(UI_SOURCE_DIR';

	var regex_ti_cmake_2 = /add_subdirectory\(\${UI_SOURCE_DIR}/g;
	var mod_ti_cmake_2 = 'add_subdirectory(${' + module_data.name + '_SOURCE_DIR}    ${CMAKE_CURRENT_BINARY_DIR}/' + module_data.name + '    EXCLUDE_FROM_ALL)\n'
																									+ 'add_subdirectory(${UI_SOURCE_DIR}';

	var regex_ti_cmake_3 = / {2}\$<TARGET_PROPERTY:TitaniumWindows_UI/g;
	var mod_ti_cmake_3 = '  $<TARGET_PROPERTY:TitaniumWindows_' + module_data.name + ',INTERFACE_INCLUDE_DIRECTORIES>\n'
																									+ '  $<TARGET_PROPERTY:TitaniumWindows_UI';

	var regex_ti_cmake_4 = / {2}TitaniumWindows_UI/g;
	var mod_ti_cmake_4 = '  TitaniumWindows_' + module_data.name + '\n'
    					 + '  TitaniumWindows_UI';

	// Titanium Titanium.hpp modifications
	var regex_tik_ti_1 = /UIModule.hpp\"/g;
	var mod_tik_ti_1 = 'UIModule.hpp"\n'
    				  + '#include "Titanium/' + module_data.name + '.hpp"';

	// Titanium TitaniumWindows.cpp modifications
	var regex_ti_tiw_1 = /UIModule.hpp\"/g;
	var mod_ti_tiw_1 = 'UIModule.hpp"\n'
    					 + '#include "TitaniumWindows/' + module_data.module_path + '.hpp"';

	var regex_ti_tiw_2 = /UI::View>::Class\(\)\)\)/g;
	var mod_ti_tiw_2 = 'UI::View>::Class()))\n		                                                            '
						 + '.' + module_data.name + 'Object(js_context__.CreateObject(JSExport<TitaniumWindows::' + module_data.full_namespace + '>::Class()))';

	// Titanium build_and_test.sh modifications
	var regex_ti_bt_1 = /cmd\+=\" \-DTitaniumWindows_UI_/g;
	var mod_ti_bt_1 = 'cmd+=" -DTitaniumWindows_' + module_data.name + '_DISABLE_TESTS=ON"\n'
    				  + 'cmd+=" -DTitaniumWindows_UI_';

	// Titanium module CMakeLists.txt modifications
	var regex_tim_cmake_1 = new RegExp('set\\(SOURCE_' + module_data.module_parent + '\n', 'g');
	var mod_tim_cmake_1 = 'set(SOURCE_' + module_data.module_parent + '\n'
						  + '  include/TitaniumWindows/' + module_data.module_path + '.hpp\n'
						  + '  src/' + (isUI ? module_data.name : module_data.module_path) + '.cpp\n';

	var regex_tikm_head_1 = /Module.hpp\"/g;
	var mod_tikm_head_1 = 'Module.hpp"\n'
						  + '#include "Titanium/' + module_data.module_path + '.hpp"';

	var regex_tikm_method_1 = /TITANIUM_FUNCTION_DEF\(createWindow\);/g;
	var mod_tikm_method_1 = 'TITANIUM_FUNCTION_DEF(createWindow);\n\t\t'
							+ 'TITANIUM_FUNCTION_DEF(create' + module_data.name + ');';

	var regex_tikm_method_2 = /TITANIUM_FUNCTION\(UIModule, createWebView\)/g;
	var mod_tikm_method_2 = 'TITANIUM_FUNCTION(UIModule, create' + module_data.name + ')\n\t'
							+ '{\n\t\t'
							+ 'ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);\n\t\t'
							+ 'CREATE_TITANIUM_UI(' + module_data.name + ');\n\t'
							+ '}\n\n\tTITANIUM_FUNCTION(UIModule, createWebView)';

	var regex_tiw_ui = /#include \"TitaniumWindows\/UI\/Window.hpp\"/g;
	var mod_tiw_ui = '#include "TitaniumWindows/UI/Window.hpp"\n'
					 + '#include "TitaniumWindows/UI/' + module_data.name + '.hpp"';

	// Async task to create backups before modifications
	var asyncTasks = [];
	asyncTasks.push(asyncRenameFile(path_tik_cmake, path_tik_cmake + '.bak'));
	asyncTasks.push(asyncRenameFile(path_ti_tiw, path_ti_tiw + '.bak'));
	asyncTasks.push(asyncRenameFile(path_tik_app_hpp, path_tik_app_hpp + '.bak'));
	asyncTasks.push(asyncRenameFile(path_tik_app_cpp, path_tik_app_cpp + '.bak'));
	if (module_data.sub_class) {
		asyncTasks.push(asyncRenameFile(path_tik_module_hpp, path_tik_module_hpp + '.bak'));
		asyncTasks.push(asyncRenameFile(path_tik_module_cpp, path_tik_module_cpp + '.bak'));
		asyncTasks.push(asyncRenameFile(path_module_cmake, path_module_cmake + '.bak'));
	} else {
		asyncTasks.push(asyncRenameFile(path_ti_cmake, path_ti_cmake + '.bak'));
		asyncTasks.push(asyncRenameFile(path_ti_bt, path_ti_bt + '.bak'));
		asyncTasks.push(asyncRenameFile(path_tik_ti, path_tik_ti + '.bak'));
	}
	async.parallel(asyncTasks,
		function (error) {
			if (error) { throw error; }

			// Modify TitaniumKit CMakeLists.txt
			fs.readFile(path_tik_cmake + '.bak', 'utf8',
				function (error, data) {
					if (error) { throw error; }

					data = [ data ];
					if (module_data.module_parent == 'UI') {
						modify(data, regex_tik_cmake_ui, mod_tik_cmake_ui);
					} else {
						modify(data, regex_tik_cmake_1, mod_tik_cmake_1);
						modify(data, regex_tik_cmake_2, mod_tik_cmake_2);
						modify(data, regex_tik_cmake_3, mod_tik_cmake_3);
					}
					data = data[0];

					writeFile(path_tik_cmake, data);
				}
			);

			if (!module_data.sub_class) {

				// Modify Titanium CMakeLists.txt
				fs.readFile(path_ti_cmake + '.bak', 'utf8',
					function (error, data) {
						if (error) { throw error; }

						data = [ data ];
						modify(data, regex_ti_cmake_1, mod_ti_cmake_1);
						modify(data, regex_ti_cmake_2, mod_ti_cmake_2);
						modify(data, regex_ti_cmake_3, mod_ti_cmake_3);
						modify(data, regex_ti_cmake_4, mod_ti_cmake_4);
						data = data[0];

						writeFile(path_ti_cmake, data);
					}
				);

				// Modify Titanium build_and_test.sh
				fs.readFile(path_ti_bt + '.bak', 'utf8',
					function (error, data) {
						if (error) { throw error; }

						data = [ data ];
						modify(data, regex_ti_bt_1, mod_ti_bt_1);
						data = data[0];

						writeFile(path_ti_bt, data);
					}
				);

				// Modify TitaniumKit Titanium.hpp
				fs.readFile(path_tik_ti + '.bak', 'utf8',
					function (error, data) {
						if (error) { throw error; }

						data = [ data ];
						modify(data, regex_tik_ti_1, mod_tik_ti_1);
						data = data[0];

						writeFile(path_tik_ti, data);
					}
				);
			}

			// Modify Titanium TitaniumWindows.cpp
			fs.readFile(path_ti_tiw + '.bak', 'utf8',
				function (error, data) {
					if (error) { throw error; }

					data = [ data ];
					modify(data, regex_ti_tiw_1, mod_ti_tiw_1);
					modify(data, regex_ti_tiw_2, mod_ti_tiw_2);
					data = data[0];

					writeFile(path_ti_tiw, data);
				}
			);

			// Modify TitaniumKit ApplicationBuilder.hpp
			fs.readFile(path_tik_app_hpp + '.bak', 'utf8',
				function (error, data) {
					if (error) { throw error; }

					data = [ data ];
					modify(data, regex_tik_app_1, mod_tik_app_1);
					modify(data, regex_tik_app_2, mod_tik_app_2);
					data = data[0];

					writeFile(path_tik_app_hpp, data);
				}
			);

			// Modify Titaniumkit ApplicationBuilder.cpp
			fs.readFile(path_tik_app_cpp + '.bak', 'utf8',
				function (error, data) {
					if (error) { throw error; }

					data = [ data ];
					modify(data, regex_tik_app_3, mod_tik_app_3);
					modify(data, regex_tik_app_4, mod_tik_app_4);
					modify(data, regex_tik_app_5, mod_tik_app_5);
					modify(data, regex_tik_app_6, mod_tik_app_6);
					data = data[0];

					writeFile(path_tik_app_cpp, data);
				}
			);

			if (module_data.sub_class) {

				// Modify TitaniumKit Module.hpp
				fs.readFile(path_tik_module_hpp + '.bak', 'utf8',
					function (error, data) {
						if (error) { throw error; }

						data = [ data ];
						modify(data, regex_tikm_head_1, mod_tikm_head_1);
						modify(data, regex_tikm_method_1, mod_tikm_method_1);
						data = data[0];

						writeFile(path_tik_module_hpp, data);
					}
				);

				// Modify TitaniumKit Module.cpp
				fs.readFile(path_tik_module_cpp + '.bak', 'utf8',
					function (error, data) {
						if (error) { throw error; }

						data = [ data ];
						modify(data, regex_tikm_method_2, mod_tikm_method_2);
						data = data[0];

						writeFile(path_tik_module_cpp, data);
					}
				);

				// Modify TitaniumKit module CMakeLists.txt
				fs.readFile(path_module_cmake + '.bak', 'utf8',
					function (error, data) {
						if (error) { throw error; }

						data = [ data ];
						modify(data, regex_tim_cmake_1, mod_tim_cmake_1);
						data = data[0];

						writeFile(path_module_cmake, data);
					}
				);
			}
		}
	);
}
function asyncRenameFile(source, destination) {
	return function (next) {
		fs.rename(source, destination,
			function (error) {
				if (error) { throw error; }
				next();
			}
		);
	};
}
function divideArray(array, divider, i) {
	var ret = '';
	if (i == undefined) { i = 0; }
	while (i < array.length) {
		ret += array[i];
		if (i < array.length - 1) { ret += divider; }
		i++;
	}
	return ret;
}
function modify(string, regex, replace) {
	var ret = false;
	string[0] = string[0].replace(regex,
		function (token) {
			ret = true;
			return replace;
		}
	);
	if (!ret) { console.log('Error : Could not find signature \'' + regex + '\''); }
	return ret;
}
function mkdir(dirname, cb) {
	if (cb) {
		fs.mkdirp(dirname, cb);
	} else {
		try {
			fs.mkdirpSync(dirname);
			return true;
		} catch (e) {
			console.error(e.message);
			return false;
		}
	}
}
function writeFile(filename, content) {
	mkdir(path.dirname(filename));
	try {
		fs.writeFileSync(filename, content, { flags : 'w' });
		return true;
	} catch (e) {
		console.error(e.message);
		return false;
	}
}
