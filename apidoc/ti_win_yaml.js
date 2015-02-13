/**
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

var lbl = require('line-by-line'),
    path = require('path'),
	fs = require('fs.extra'),
	TI_KIT_SRC_DIRECTORY = '../Source/TitaniumKit/src',
	TI_WIN_DOC_DIRECTORY = '../apidoc/Titanium';

// Add 'contains' prototype to String
if (typeof String.prototype.contains === 'undefined') {
	String.prototype.contains = function(str) {
		return this.indexOf(str) != -1;
	}
}

// Define signatures
var property_signature = 'AddValueProperty(\"';
var method_signature = 'AddFunctionProperty(\"';
var export_signature = 'JSExport<';
var namespace_signature = 'namespace ';

var properties_found = 0;
var methods_found = 0;

// Walk through the TitaniumKit source directory
var walker = fs.walk(TI_KIT_SRC_DIRECTORY)
walker.on("file",
	function (root, stat, next) {
		if (stat.name.contains('.cpp')) {
		    processClass(root, stat.name, next);
		} else {
			next();
		}
	}
);
walker.on("end",
	function () {
		console.log('\nFound '+methods_found+' methods');
		console.log('Found '+properties_found+' propeties');
		console.log('Total APIs : '+(methods_found+properties_found));
		
		var docPath = process.argv[1].replace(/\\/g, '/')
		docPath = docPath.substring(0, docPath.lastIndexOf('/'))+'/Titanium';
		console.log('\nTo append the documentation run the following command from titanium_mobile/apidoc :\n\nnode docgen.js -f parity -a '+docPath);
	}
);

// Extract titanium properties and methods from the class file
function processClass(root, file, next) {

	var module_name = null;
	var namespaces = [];
	var module = null;
	var properties = [];
	var methods = [];

    var l = new lbl(path.join(root, file));
	l.on('line',
		function (line) {
			
			var isProperty = line.contains(property_signature);
			var isMethod = line.contains(method_signature);

			if (isProperty || isMethod) {
				if (module == null) {
					module = line.substr(line.indexOf(export_signature)+export_signature.length).split('>')[0].replace('Module','');
					if (module == 'Ti') module = 'Titanium';
					if (module == 'Titanium') module = '';
				}

				var name = line.split('\"')[1];

				if (module_name == null) module_name = namespaces.join('.')+(module != '' ? '.'+module : '');

				if (isProperty) properties.push(name);
				if (isMethod) methods.push(name);

			} else if (line.contains(namespace_signature)) {
				var namespace = line.substr(line.indexOf(namespace_signature)+namespace_signature.length).replace('Module','');
				if (namespace.contains(' ')) namespace = namespace.split(' ')[0];
				if (namespace.contains('{')) namespace = namespace.split('{')[0];
				if (!namespace.contains('.') && !namespace.contains(':') && !namespace.contains(';'))
					namespaces.push(namespace);
			}
		}
	);
	l.on('error',
		function (err) {
			console.log('Error : ' + err);
		}
	);
	l.on('end',
		function () {
			properties_found += properties.length;
			methods_found += methods.length;
			if (module != null) {
				if (module == '') module = 'Titanium';
				generateYAML(root, module_name, module, properties, methods, next);
			} else {
				next();
			}
		}
	);
}

// Generate a YAML file from the extracted information
function generateYAML(root, module_name, module, properties, methods, next) {
	var folder = root.split('/').pop();

	var yaml = 'name: '+module_name+'\n'+
	           'platforms: [windowsphone]\n\n';
	if (properties.length > 0) yaml += 'properties:\n';
	for(i in properties) {
		var property = properties[i];
	    yaml += '  - name: '+property+'\n'+
	            '    platforms: [windowsphone]\n';
	}
	if (methods.length > 0) yaml += 'methods:\n';
	for (i in methods) {
		var method = methods[i];
		yaml += '  - name: '+method+'\n'+
	            '    platforms: [windowsphone]\n';
	}

	var target = TI_WIN_DOC_DIRECTORY+(folder != 'src' ? '/'+folder+'/' : '/');

	fs.mkdirp(target,
		function (err) {
			if (err) {
				console.log(err);
			} else {
				fs.writeFile(target+module+'.yml', yaml,
					function(err) {
					    if(err) {
					        console.log(err);
					    } else {
					        console.log('Generated '+module+'.yml');
					    	next();
					    }
					}
				);
			}
		}
	);
}
