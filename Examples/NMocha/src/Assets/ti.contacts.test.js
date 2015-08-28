/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe("Titanium.Contacts", function() {
	it('AUTHORIZATION_AUTHORIZED', function (finish) {
        should(function () {
            should(Ti.Contacts.AUTHORIZATION_AUTHORIZED).not.be.undefined;
            should(Ti.Contacts.AUTHORIZATION_AUTHORIZED).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Contacts.AUTHORIZATION_AUTHORIZED;
            Ti.Contacts.AUTHORIZATION_AUTHORIZED = 1234;
            should(Ti.Contacts.AUTHORIZATION_AUTHORIZED).be.eql(value);
        }).not.throw();
        finish();
    });
    it('AUTHORIZATION_DENIED', function (finish) {
        should(function () {
            should(Ti.Contacts.AUTHORIZATION_DENIED).not.be.undefined;
            should(Ti.Contacts.AUTHORIZATION_DENIED).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Contacts.AUTHORIZATION_DENIED;
            Ti.Contacts.AUTHORIZATION_DENIED = 1234;
            should(Ti.Contacts.AUTHORIZATION_DENIED).be.eql(value);
        }).not.throw();
        finish();
    });
    it('AUTHORIZATION_RESTRICTED', function (finish) {
        should(function () {
            should(Ti.Contacts.AUTHORIZATION_RESTRICTED).not.be.undefined;
            should(Ti.Contacts.AUTHORIZATION_RESTRICTED).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Contacts.AUTHORIZATION_RESTRICTED;
            Ti.Contacts.AUTHORIZATION_RESTRICTED = 1234;
            should(Ti.Contacts.AUTHORIZATION_RESTRICTED).be.eql(value);
        }).not.throw();
        finish();
    });
    it('AUTHORIZATION_UNKNOWN', function (finish) {
        should(function () {
            should(Ti.Contacts.AUTHORIZATION_UNKNOWN).not.be.undefined;
            should(Ti.Contacts.AUTHORIZATION_UNKNOWN).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Contacts.AUTHORIZATION_UNKNOWN;
            Ti.Contacts.AUTHORIZATION_UNKNOWN = 1234;
            should(Ti.Contacts.AUTHORIZATION_UNKNOWN).be.eql(value);
        }).not.throw();
        finish();
    });
    it('CONTACTS_KIND_ORGANIZATION', function (finish) {
        should(function () {
            should(Ti.Contacts.CONTACTS_KIND_ORGANIZATION).not.be.undefined;
            should(Ti.Contacts.CONTACTS_KIND_ORGANIZATION).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Contacts.CONTACTS_KIND_ORGANIZATION;
            Ti.Contacts.CONTACTS_KIND_ORGANIZATION = 1234;
            should(Ti.Contacts.CONTACTS_KIND_ORGANIZATION).be.eql(value);
        }).not.throw();
        finish();
    });
    it('CONTACTS_KIND_PERSON', function (finish) {
        should(function () {
            should(Ti.Contacts.CONTACTS_KIND_PERSON).not.be.undefined;
            should(Ti.Contacts.CONTACTS_KIND_PERSON).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Contacts.CONTACTS_KIND_PERSON;
            Ti.Contacts.CONTACTS_KIND_PERSON = 1234;
            should(Ti.Contacts.CONTACTS_KIND_PERSON).be.eql(value);
        }).not.throw();
        finish();
    });
    it('CONTACTS_SORT_FIRST_NAME', function (finish) {
        should(function () {
            should(Ti.Contacts.CONTACTS_SORT_FIRST_NAME).not.be.undefined;
            should(Ti.Contacts.CONTACTS_SORT_FIRST_NAME).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Contacts.CONTACTS_SORT_FIRST_NAME;
            Ti.Contacts.CONTACTS_SORT_FIRST_NAME = 1234;
            should(Ti.Contacts.CONTACTS_SORT_FIRST_NAME).be.eql(value);
        }).not.throw();
        finish();
    });
    it('CONTACTS_SORT_LAST_NAME', function (finish) {
        should(function () {
            should(Ti.Contacts.CONTACTS_SORT_LAST_NAME).not.be.undefined;
            should(Ti.Contacts.CONTACTS_SORT_LAST_NAME).be.a.Number;
            // make sure it is read-only value
            var value = Ti.Contacts.CONTACTS_SORT_LAST_NAME;
            Ti.Contacts.CONTACTS_SORT_LAST_NAME = 1234;
            should(Ti.Contacts.CONTACTS_SORT_LAST_NAME).be.eql(value);
        }).not.throw();
        finish();
    });
    it('contactsAuthorization', function (finish) {
        should(function () {
            should(Ti.Contacts.contactsAuthorization).not.be.undefined;
            should(Ti.Contacts.contactsAuthorization).be.a.Number;
            // should be one of the authorization contants
            should([
            	Ti.Contacts.AUTHORIZATION_UNKNOWN,
            	Ti.Contacts.AUTHORIZATION_RESTRICTED,
            	Ti.Contacts.AUTHORIZATION_DENIED,
            	Ti.Contacts.AUTHORIZATION_AUTHORIZED
            ]).containEql(Ti.Contacts.contactsAuthorization);
        }).not.throw();
        finish();
    });
    it("createGroup", function(finish) {
		should(Ti.Contacts.createGroup).be.a.Function;
		// TODO Now test that it returns a Ti.Contacts.Group
		finish();
	});
	it("createPerson", function(finish) {
		should(Ti.Contacts.createPerson).be.a.Function;
		// TODO Now test that it returns a Ti.Contacts.Person
		finish();
	});
	it("getAllGroups", function(finish) {
		should(Ti.Contacts.getAllGroups).be.a.Function;
		// TODO Now test that it returns an array of Ti.Contacts.Group
		should(Ti.Contacts.getAllGroups()).be.an.Array;
		finish();
	});
	it("getAllPeople", function(finish) {
		should(Ti.Contacts.getAllPeople).be.a.Function;
		// TODO Now test that it returns a an array of Ti.Contacts.Person
		should(Ti.Contacts.getAllPeople()).be.an.Array;
		finish();
	});
	it("getGroupByID", function(finish) {
		should(Ti.Contacts.getGroupByID).be.a.Function;
		// TODO Now test that it returns a Ti.Contacts.Group
		finish();
	});
	it("getGroupByIdentifier", function(finish) {
		should(Ti.Contacts.getGroupByIdentifier).be.a.Function;
		// TODO Now test that it returns a Ti.Contacts.Group
		finish();
	});
	it("getPeopleWithName", function(finish) {
		should(Ti.Contacts.getPeopleWithName).be.a.Function;
		should(Ti.Contacts.getPeopleWithName("smith")).be.an.Array;
		finish();
	});
	it("getPersonByID", function(finish) {
		should(Ti.Contacts.getPersonByID).be.a.Function;
		// TODO Now test that it returns a Ti.Contacts.Person
		finish();
	});
	it("getPersonByIdentifier", function(finish) {
		should(Ti.Contacts.getPersonByIdentifier).be.a.Function;
		// TODO Now test that it returns a Ti.Contacts.Person
		finish();
	});
	it("removeGroup", function(finish) {
		should(Ti.Contacts.removeGroup).be.a.Function;
		// TODO Test the method
		finish();
	});
	it("removePerson", function(finish) {
		should(Ti.Contacts.removePerson).be.a.Function;
		// TODO Test the method
		finish();
	});
	it("requestAuthorization", function(finish) {
		should(Ti.Contacts.requestAuthorization).be.a.Function;
		// TODO Test the method
		finish();
	});
	it("revert", function(finish) {
		should(Ti.Contacts.revert).be.a.Function;
		// TODO Test the method
		finish();
	});
	it("save", function(finish) {
		should(Ti.Contacts.save).be.a.Function;
		// TODO Test the method
		finish();
	});
	it("showContacts", function(finish) {
		should(Ti.Contacts.showContacts).be.a.Function;
		// TODO Test the method
		finish();
	});
	// TODO Test reload event?
});