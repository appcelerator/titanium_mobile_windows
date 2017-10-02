'use strict';

module.exports = function (grunt) {

	// Project configuration.
	grunt.initConfig({
		appcJs: {
			src: [ 'Gruntfile.js', 'Tools/**/*.js', 'cli/!(locales)/**/*.js' ]
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
