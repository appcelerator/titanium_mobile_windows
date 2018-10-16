/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2011-Present by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
/* eslint-env mocha */
/* global Ti */
/* eslint no-unused-expressions: "off" */
'use strict';
var should = require('./utilities/assertions');

describe('Titanium.Database', function () {
	it('apiName', function () {
		should(Ti.Database.apiName).be.eql('Ti.Database');
		should(Ti.Database).have.readOnlyProperty('apiName').which.is.a.String;
	});

	it('FIELD_TYPE_DOUBLE', function () {
		should(Ti.Database).have.constant('FIELD_TYPE_DOUBLE').which.is.a.Number;
	});

	it('FIELD_TYPE_FLOAT', function () {
		should(Ti.Database).have.constant('FIELD_TYPE_FLOAT').which.is.a.Number;
	});

	it('FIELD_TYPE_INT', function () {
		should(Ti.Database).have.constant('FIELD_TYPE_INT').which.is.a.Number;
	});

	it('FIELD_TYPE_STRING', function () {
		should(Ti.Database).have.constant('FIELD_TYPE_STRING').which.is.a.Number;
	});

	// FIXME Get working for iOS - gets back John Smith\\u0000'
	// FIXME Get working on Android, either lastInsertRowId or rowsAffected is starting as 1, not 0
	it.androidAndIosBroken('install()', function () {
		should(Ti.Database.install).not.be.undefined;
		should(Ti.Database.install).be.a.Function;

		// Database name
		var dbName = 'testDbInstall';

		// Copy database 'testDbResource.db' over from the application folder
		// into the application data folder as 'testDbInstall'
		var db = Ti.Database.install('testDbResource.db', dbName);

		// Confirm 'db' is an object
		should(db).be.a.Object;

		// Confirm 'db.file' property is a valid object
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
		var testName = 'John Smith';
		var testNumber = 123456789;
		var testArray = [ 'Smith John', 987654321 ];

		// Execute a query to return the rows of the database
		var rows = db.execute('SELECT rowid, text, number FROM testTable');

		// Validate the returned 'rows' object
		should(rows).be.a.Object;
		should(rows.rowCount).be.eql(2);
		should(rows.fieldCount).be.eql(3);
		// Validate field names
		should(rows.fieldName(0)).be.eql('rowid');
		should(rows.fieldName(1)).be.eql('text');
		should(rows.fieldName(2)).be.eql('number');

		// Loop through each row
		var index = 1;
		while (rows.isValidRow()) {

			// Validate the rowid field
			var rowid = rows.fieldByName('rowid');
			should(rowid).be.a.Number;
			should(rowid).be.eql(index);

			// Case insensitive search
			rowid = rows.fieldByName('ROWID');
			should(rowid).be.a.Number;
			should(rowid).be.eql(index);

			// Validate the text field
			var text = rows.field(1);
			should(text).be.a.String;

			// Validate the number field
			var number = rows.fieldByName('number');
			should(number).be.a.Number;

			// Case insensitive search
			number = rows.fieldByName('NUMBER');
			should(number).be.a.Number;

			// Validate the test data
			if (index === 1) {
				should(text).be.eql(testName);
				should(number).be.eql(testNumber);
			} else if (index === 2) {
				should(number).be.eql(testArray[1]);
				should(text).be.eql(testArray[0]);
			}

			// Next row
			rows.next();
			index++;
		}

		// Close the 'rows' object
		rows.close();

		// test aliased field name
		var aliased = db.execute('SELECT rowid, text AS something FROM testTable');

		// Validate the returned 'rows' object
		should(aliased).be.a.Object;
		should(aliased.rowCount).be.eql(2);
		should(aliased.fieldCount).be.eql(2);
		// Validate field names
		should(aliased.fieldName(0)).be.eql('rowid');
		should(aliased.fieldName(1)).be.eql('something');

		// Close the 'rows' object
		aliased.close();

		// Remove the 'testDbInstall' database file
		db.remove();

		// Close the database (unnecessary as remove() does this for us)
		db.close();
	});

	// Check if open exists and make sure it does not throw exception
	// FIXME Get working on Android, either lastInsertRowId or rowsAffected is starting as 1, not 0
	it.androidBroken('open()', function () {
		should(Ti.Database.open).not.be.undefined;
		should(Ti.Database.open).be.a.Function;

		// Database name
		var dbName = 'testDbOpen';

		// Open database 'testDbOpen' if it exists in the
		// application data folder, otherwise create a new one
		var db = Ti.Database.open(dbName);

		// Confirm 'db' is an object
		should(db).be.a.Object;

		// Confirm 'db.file' property is a valid object
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
		var testName = 'John Smith';
		var testNumber = 123456789;

		// Insert test data into the table
		db.execute('INSERT INTO testTable (text, number) VALUES (?, ?)', testName, testNumber);

		// Validate that only one row has been affected
		should(db.rowsAffected).be.eql(1);

		// Define more test data
		var testArray = [ 'Smith John', 987654321 ];

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
		should(rows.validRow).be.true;
		should(rows.isValidRow()).be.true;

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
			if (index === 1) {
				should(text).be.eql(testName);
				should(number).be.eql(testNumber);
			} else if (index === 2) {
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
	});

	// Check if it guards against 'closed' results
	// FIXME Get working on Android, seems to retain rowCount after Result.close()
	it.androidBroken('closed_guard', function () {
		// Database name
		var dbName = 'testDbOpen';

		// Open database 'testDbOpen' if it exists in the
		// application data folder, otherwise create a new one
		var db = Ti.Database.open(dbName);

		// Execute a query to create a test table
		db.execute('CREATE TABLE IF NOT EXISTS testTable (text TEXT, number INTEGER)');

		// Delete any existing data if the table already existed
		db.execute('DELETE FROM testTable');

		// Define test data
		var testName = 'John Smith';
		var testNumber = 123456789;

		// Insert test data into the table
		db.execute('INSERT INTO testTable (text, number) VALUES (?, ?)', testName, testNumber);

		// Validate that only one row has been affected
		should(db.rowsAffected).be.eql(1);

		// Define more test data
		var testArray = [ 'Smith John', 987654321 ];

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
		should(rows.validRow).be.true;

		// Close the 'rows' object
		rows.close();

		// Make sure row is not 'valid'
		should(rows.rowCount).be.eql(0); // Android still reports 2
		should(rows.fieldCount).be.eql(0);
		should(rows.validRow).be.false;

		// Validate the rowid field
		var rowid = rows.fieldByName('rowid');
		should(rowid).not.exist; // null or undefined

		// Validate the closed field
		var field1 = rows.field(1);
		should(field1).not.exist; // null or undefined

		var field2 = rows.fieldByName('number');
		should(field2).not.exist; // null or undefined

		// Make sure next doesn't cause crash and return false
		should(rows.next()).be.false;

		// Make sure closing again doesn't cause crash
		rows.close();

		// Remove the 'testDbInstall' database file
		db.remove();

		// Close the database (unnecessary as remove() does this for us)
		db.close();
	});

	// Test behavior expected by alloy code for createCollection. See TIMOB-20222
	// skip this test, this behaviour is undocumented. Our current code will return null
	// only if the result contains no fields/columns instead of the result containing no rows
	it.skip('execute() returns null instead of empty result set', function () { // eslint-disable-line mocha/no-skipped-tests
		should(Ti.Database.install).not.be.undefined;
		should(Ti.Database.install).be.a.Function;

		// Call install on a database file that doesn't exist. We should just make a new db with name 'category'
		var db = Ti.Database.install('made.up.sqlite', 'category');

		// Confirm 'db' is an object
		should(db).be.a.Object;

		var rows = db.execute('pragma table_info(\'category\');');

		should(rows).be.null;

		// Remove the 'category' database file
		db.remove();

		// Close the database (unnecessary as remove() does this for us)
		db.close();
	});

});
