'use strict';

module.exports = function (grunt) {
	// TODO: node_modules should all be in the top level
	// Project configuration.
	grunt.initConfig({
		appcJs: {
			src: [
				'Gruntfile.js',
				'apidoc/*.js',
				'cli/!(locales)/**/*.js',
				'templates/**/*.js',
				'Tools/**/*.js',
				'!**/node_modules/**/*.js'
			]
		},
		clangFormat: {
			src: [ 'Source/**/*.cpp', 'Source/**/*.hpp' ]
		}
	});

	// Load grunt plugins for modules
	grunt.loadNpmTasks('grunt-appc-js');
	grunt.loadNpmTasks('grunt-clang-format');

	// register tasks
	grunt.registerTask('lint', [ 'appcJs' ]);

	grunt.registerTask('clang', [ 'clangFormat' ]);

	// register tasks
	grunt.registerTask('default', [ 'lint' ]);
};
