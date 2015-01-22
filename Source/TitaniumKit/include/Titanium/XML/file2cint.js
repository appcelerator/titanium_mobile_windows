/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

/*
 * Simple utility to convert file into C char array
 * Usage: node file2int [filename1] [filename2] ...
 */

var fs = require('fs'),
    path = require('path');

function bufferToCIntArray(data) {
	var indent = '    ',
		position = 0,
		split = 30,
		length = data.length,
		output = [];
	for (var i=0;i<length;++i,++position) {
		if ((position % split) === 0) {
			output.push("\n"+indent);
		}
		if (position > 0) {
			output.push(",");
		}
		output.push(data.readInt8(i));
	}
	output.push(",0"); // NULL termination
	return output.join('').trim();
}

if (process.argv.length < 3) {
	console.error('Simple utility to convert file into C char array');
	console.error('Usage: node file2int [filename1] [filename2] ...');
	return;
}

for (var i = 2; i < process.argv.length; i++) {
	var filename = process.argv[i];
	var varname  = path.basename(filename).replace(/[^a-z0-9]/g, '_');
	var src = fs.readFileSync(filename, 'utf8');
	var buffer = bufferToCIntArray(new Buffer(src, 'utf8'));
	console.log('static const char '+varname+'[] = { '+buffer+' };');
	console.log('');
}
