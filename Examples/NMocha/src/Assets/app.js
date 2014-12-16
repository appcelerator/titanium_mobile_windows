/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var win = Ti.UI.createWindow({
    backgroundColor: 'lightyellow'
});
win.open();

require('ti-mocha');
var should = require('should');
var $results = [];

// ============================================================================
// Add the tests here using "require"
require('ti.builtin.test');
// ============================================================================

// add a special mocha reporter that will time each test run using
// our microsecond timer
function $Reporter(runner) {
    var started,
		title;

    runner.on('suite', function (suite) {
        title = suite.title;
    });

    runner.on('test', function (test) {
        started = new Date().getTime();
    });

    runner.on('fail', function (test, err) {
        test.err = err;
    });

    runner.on('test end', function (test) {
        var tdiff = new Date().getTime() - started;
        $results.push({
            state: test.state || 'skipped',
            duration: tdiff,
            suite: title,
            title: test.title,
            error: test.err
        });
    });
};

mocha.setup({
    reporter: $Reporter,
    quiet: true
});

// dump the output, which will get interpreted above in the logging code
mocha.run(function () {
    Ti.API.info('!TEST_RESULTS_START!');
    Ti.API.info(JSON.stringify({
        date: new Date,
        results: $results
    }, null, '\t'));
    Ti.API.info('!TEST_RESULTS_STOP!');
});
