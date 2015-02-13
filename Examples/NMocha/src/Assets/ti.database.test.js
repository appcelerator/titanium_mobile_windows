/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe('database', function () {

    // Check if FIELD_TYPE_DOUBLE exists and make sure it does not throw exception
    it('FIELD_TYPE_DOUBLE', function (finish) {
        should(function () {
            should(Ti.Database.FIELD_TYPE_DOUBLE).not.be.undefined;
            should(Ti.Database.FIELD_TYPE_DOUBLE).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Database.FIELD_TYPE_DOUBLE;
            Ti.Database.FIELD_TYPE_DOUBLE = 'try_to_overwrite_READONLY_value';
            should(Ti.Database.FIELD_TYPE_DOUBLE).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if FIELD_TYPE_FLOAT exists and make sure it does not throw exception
    it('FIELD_TYPE_FLOAT', function (finish) {
        should(function () {
            should(Ti.Database.FIELD_TYPE_FLOAT).not.be.undefined;
            should(Ti.Database.FIELD_TYPE_FLOAT).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Database.FIELD_TYPE_FLOAT;
            Ti.Database.FIELD_TYPE_FLOAT = 'try_to_overwrite_READONLY_value';
            should(Ti.Database.FIELD_TYPE_FLOAT).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if FIELD_TYPE_INT exists and make sure it does not throw exception
    it('FIELD_TYPE_INT', function (finish) {
        should(function () {
            should(Ti.Database.FIELD_TYPE_INT).not.be.undefined;
            should(Ti.Database.FIELD_TYPE_INT).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Database.FIELD_TYPE_INT;
            Ti.Database.FIELD_TYPE_INT = 'try_to_overwrite_READONLY_value';
            should(Ti.Database.FIELD_TYPE_INT).be.eql(value);
        }).not.throw();
        finish();
    });
    // Check if FIELD_TYPE_STRING exists and make sure it does not throw exception
    it('FIELD_TYPE_STRING', function (finish) {
        should(function () {
            should(Ti.Database.FIELD_TYPE_STRING).not.be.undefined;
            should(Ti.Database.FIELD_TYPE_STRING).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Database.FIELD_TYPE_STRING;
            Ti.Database.FIELD_TYPE_STRING = 'try_to_overwrite_READONLY_value';
            should(Ti.Database.FIELD_TYPE_STRING).be.eql(value);
        }).not.throw();
        finish();
    });

    // Check if install exists and make sure it does not throw exception
    it('install', function (finish) {
        should(Ti.Database.install).not.be.undefined;
        should(Ti.Database.install).be.a.Function;

        // Database name
        var dbName = "testDbInstall";

        // Copy database 'testDbResource.db' over from the application folder
        // into the application data folder as 'testDbInstall'
        var db = Ti.Database.install("testDbResource.db", dbName);

        // Confirm 'db' is an object
        should(db).be.a.Object;

        // Confirm 'db.file' property is a valid object
        var file = db.file;
        Ti.API.info(db.file.name);
        should(db.file).be.a.Object;

        // Validate the 'db.lastInsertRowId' property
        should(db.lastInsertRowId).be.a.Number;
        should(db.lastInsertRowId).be.eql(0);

        // Confirm 'db.name' is a string
        should(db.name).be.a.String;
        should(db.name).be.eql(dbName);

        // Validate the 'db.rowsAffected' property
        should(db.rowsAffected).be.a.Number;
        should(db.rowsAffected).be.eql(0);

        // Define test data
        var testName = "John Smith";
        var testNumber = 123456789;
        var testArray = ['Smith John', 987654321];

        // Execute a query to return the rows of the database
        var rows = db.execute('SELECT rowid, text, number FROM testTable');

        // Validate the returned 'rows' object
        should(rows).be.a.Object;
        should(rows.rowCount).be.eql(2);
        should(rows.fieldCount).be.eql(3);

        // Loop through each row
        var index = 1;
        while (rows.isValidRow()) {

            // Validate the rowid field
            var rowid = rows.fieldByName('rowid');
            should(rowid).be.a.Number;
            should(rowid).be.eql(index);

            // Validate the text field
            var text = rows.field(1);
            should(text).be.a.String;

            // Validate the number field
            var number = rows.fieldByName('number');
            should(number).be.a.Number;

            // Validate the test data
            if (index == 1) {
                should(text).be.eql(testName);
                should(number).be.eql(testNumber);
            } else if (index == 2) {
                should(number).be.eql(testArray[1]);
                should(text).be.eql(testArray[0]);
            }

            // Next row                                                                                                                                                                                                                                                  
            rows.next();
            index++;
        }

        // Close the 'rows' object
        rows.close();

        // Remove the 'testDbInstall' database file
        db.remove();

        // Close the database (unnecessary as remove() does this for us)
        db.close();

        // Finish mocha test
        finish();
    });

    // Check if open exists and make sure it does not throw exception
    it('open', function (finish) {
        should(Ti.Database.install).not.be.undefined;
        should(Ti.Database.install).be.a.Function;

        // Database name
        var dbName = "testDbOpen";

        // Open database 'testDbOpen' if it exists in the
        // application data folder, otherwise create a new one
        var db = Ti.Database.open(dbName);

        // Confirm 'db' is an object
        should(db).be.a.Object;

        // Confirm 'db.file' property is a valid object
        var file = db.file;
        should(db.file).be.a.Object;

        // Validate the 'db.lastInsertRowId' property
        should(db.lastInsertRowId).be.a.Number;
        should(db.lastInsertRowId).be.eql(0);

        // Confirm 'db.name' is a string
        should(db.name).be.a.String;
        should(db.name).be.eql(dbName);

        // Validate the 'db.rowsAffected' property
        should(db.rowsAffected).be.a.Number;
        should(db.rowsAffected).be.eql(0);

        // Execute a query to create a test table
        db.execute('CREATE TABLE IF NOT EXISTS testTable (text TEXT, number INTEGER)');

        // Delete any existing data if the table already existed
        db.execute('DELETE FROM testTable');

        // Define test data
        var testName = "John Smith";
        var testNumber = 123456789;

        // Insert test data into the table
        db.execute('INSERT INTO testTable (text, number) VALUES (?, ?)', testName, testNumber);

        // Validate that only one row has been affected
        should(db.rowsAffected).be.eql(1);

        // Define more test data
        var testArray = ['Smith John', 987654321];

        // Insert more test data into the table
        db.execute('INSERT INTO testTable (text, number) VALUES (?, ?)', testArray);

        // Validate that only one row has been affected
        should(db.rowsAffected).be.eql(1);

        // Execute a query to return the rows of the database
        var rows = db.execute('SELECT rowid, text, number FROM testTable');

        // Validate the returned 'rows' object
        should(rows).be.a.Object;
        should(rows.rowCount).be.eql(2);
        should(rows.fieldCount).be.eql(3);

        // Loop through each row
        var index = 1;
        while (rows.isValidRow()) {

            // Validate the rowid field
            var rowid = rows.fieldByName('rowid');
            should(rowid).be.a.Number;
            should(rowid).be.eql(index);

            // Validate the text field
            var text = rows.field(1);
            should(text).be.a.String;

            // Validate the number field
            var number = rows.fieldByName('number');
            should(number).be.a.Number;

            // Validate the test data
            if (index == 1) {
                should(text).be.eql(testName);
                should(number).be.eql(testNumber);
            } else if (index == 2) {
                should(number).be.eql(testArray[1]);
                should(text).be.eql(testArray[0]);
            }

            // Next row
            rows.next();
            index++;
        }

        // Close the 'rows' object
        rows.close();

        // Remove the 'testDbInstall' database file
        db.remove();

        // Close the database (unnecessary as remove() does this for us)
        db.close();

        // Finish the mocha test
        finish();
    });
});
