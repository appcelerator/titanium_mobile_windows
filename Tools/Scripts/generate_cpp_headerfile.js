'use strict';

/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

/*
 * Simple utility to convert JS files into C++ header files
 * Usage: node generate_cpp_headerfile.js
 */

const fs = require('fs'),
	path = require('path');

const source_dir  = path.resolve(__dirname, '..', '..', 'Source', 'TitaniumKit', 'src');
const include_dir = path.resolve(__dirname, '..', '..', 'Source', 'TitaniumKit', 'include', 'Titanium');

const files_to_process = [
	{
		from: path.join(source_dir,  'analytics.js'),
		to:   path.join(include_dir, 'analytics_js.hpp')
	},
	{
		from: path.join(source_dir,  'Global', 'sprintf.js'),
		to:   path.join(include_dir, 'Global', 'sprintf_js.hpp')
	},
	{
		from: path.join(source_dir,  'UI', 'listview.js'),
		to:   path.join(include_dir, 'UI', 'listview_js.hpp')
	},
	{
		from: path.join(source_dir,  'UI', 'webview.js'),
		to:   path.join(include_dir, 'UI', 'webview_js.hpp')
	},
	{
		from: path.join(source_dir,  'XML', 'dom-parser.js'),
		to:   path.join(include_dir, 'XML', 'dom_parser_js.hpp')
	},
	{
		from: path.join(source_dir,  'XML', 'dom.js'),
		to:   path.join(include_dir, 'XML', 'dom_js.hpp')
	},
	{
		from: path.join(source_dir,  'XML', 'sax.js'),
		to:   path.join(include_dir, 'XML', 'sax_js.hpp')
	}
];

function bufferToCIntArray(data) {
	let indent = '    ',
		position = 0,
		split = 30,
		length = data.length,
		output = [];
	for (let i = 0; i < length; ++i, ++position) {
		if ((position % split) === 0) {
			output.push('\n' + indent);
		}
		if (position > 0) {
			output.push(',');
		}
		output.push(data.readInt8(i));
	}
	output.push(',0'); // NULL termination
	return output.join('').trim();
}

for (let i = 0; i < files_to_process.length; i++) {
	const from_file = files_to_process[i].from;
	const to_file   = files_to_process[i].to;

	const varname  = path.basename(from_file).replace(/[^a-z0-9]/g, '_');
	const src = fs.readFileSync(from_file, 'utf8');
	const buffer = bufferToCIntArray(new Buffer(src, 'utf8'));// eslint-disable-line security/detect-new-buffer
	const output = 'static const char ' + varname + '[] = { ' + buffer + ' };\n\n';

	fs.writeFileSync(to_file, output);
}
