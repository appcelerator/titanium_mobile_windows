/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

var win = Ti.UI.createWindow({
    backgroundColor: 'lightyellow'
});
win.open();

require('./ti-mocha');
var $results = [],
    failed = false;

// ============================================================================
// Add the tests here using "require"
require('./ti.ui.listview.test');
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
        Ti.API.info('Started: ' + test.title);
        started = new Date().getTime();
    });

    runner.on('fail', function (test, err) {
        test.err = err;
        failed = true;
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
    win.backgroundColor = failed ? 'red' : 'green';

    Ti.API.info('!TEST_RESULTS_START!\n' +
        (JSON.stringify({
            date: new Date,
            results: $results
        })) +
    '\n!TEST_RESULTS_STOP!');
});
