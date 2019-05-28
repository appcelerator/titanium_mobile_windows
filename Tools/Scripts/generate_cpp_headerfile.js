/**
 * Copyright (c) 2014-Present by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
'use strict';

/*
 * Simple utility to convert JS files into C++ header files
 * Usage: node generate_cpp_headerfile.js
 */
const fs = require('fs-extra');
const path = require('path');

const ROOT_DIR = path.resolve(__dirname, '../..');
const TitaniumKitDir = path.resolve(ROOT_DIR, 'Source/TitaniumKit');
const source_dir = path.resolve(TitaniumKitDir, 'src');
const include_dir = path.resolve(TitaniumKitDir, 'include', 'Titanium');

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
	const indent = '    ';
	let position = 0;
	const split = 30;
	const length = data.length;
	const output = [];
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

/**
 * Convert a JS file to a static C++ byte array.
 * @param  {string} src  source js file
 * @param  {string} dest destination hpp file
 * @return {Promise}
 */
async function convert(src, dest) {
	console.log(`Converting ${path.relative(ROOT_DIR, src)} to ${path.relative(ROOT_DIR, dest)}...`);
	const varname = path.basename(src).replace(/[^a-z0-9]/g, '_');
	const inputBuffer = await fs.readFile(src);
	const buffer = bufferToCIntArray(inputBuffer);
	await fs.writeFile(dest, `static const char ${varname}[] = { ${buffer} };\n\n`);
}

Promise.all(files_to_process.map(pair => convert(pair.from, pair.to)))
	.then(() => process.exit(0))
	.catch(err => {
		console.error(err);
		process.exit(1);
	});
