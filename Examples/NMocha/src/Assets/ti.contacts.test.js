/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */
var should = require('./should');

describe("Titanium.Contacts", function() {
	it('apiName', function (finish) {
		should(function () {
			should(Ti.Contacts.apiName).be.eql("Titanium.Contacts");
		}).not.throw();
		finish();
	});

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
		// exercising Ti.Contacts.Group creation is done in ti.contacts.group.test.js
		finish();
	});
	it("createPerson", function(finish) {
		should(Ti.Contacts.createPerson).be.a.Function;
		// exercising Ti.Contacts.Person creation is done in ti.contacts.person.test.js
		finish();
	});
	it("getAllGroups", function (finish) {
		should(Ti.Contacts.getAllGroups).be.a.Function;
		var groups = Ti.Contacts.getAllGroups();
		should(groups).be.an.Array;
		for (var i = 0; i < groups.length; i++) {
			should(groups[i]).not.be.null;
			should(groups[i].apiName).be.eql("Titanium.Contacts.Group");
		}
		finish();
	});
	// Skip on Windows 10.0 for now: https://jira.appcelerator.org/browse/TIMOB-23332
	(Ti.Platform.version.indexOf('10.0' == 0) ? it.skip : it)("getAllPeople", function(finish) {
		should(Ti.Contacts.getAllPeople).be.a.Function;
		var people = Ti.Contacts.getAllPeople();
		should(people).be.an.Array;
		for (var i = 0; i < people.length; i++) {
			should(people[i]).not.be.null;
			should(people[i].apiName).be.eql("Titanium.Contacts.Person");
		}
		finish();
	});
	it("getGroupByID", function(finish) {
		should(Ti.Contacts.getGroupByID).be.a.Function;
		// deprecated, do no more for now
		finish();
	});
	it("getGroupByIdentifier", function (finish) {
	    should(Ti.Contacts.getGroupByIdentifier).be.a.Function;
	    var noGroup = Ti.Contacts.getGroupByIdentifier("doesntexist");
	    should(noGroup).be.null;
	    finish();
	});
	// Skip on Windows 8.1
	(Ti.Platform.version.indexOf('8.1' == 0) ? it.skip : it)("Group add/remove", function (finish) {
	    // Look for existing group and remove it first before we try to create dupe (which fails)
	    var allGroups = Ti.Contacts.getAllGroups();
	    for (var i = 0; i < allGroups.length; i++) {
	        if (allGroups[i].name == 'mygroup') {
	            Ti.Contacts.removeGroup(allGroups[i]);
	            Ti.Contacts.save();
	            break;
	        }
	    }

	    var group = Ti.Contacts.createGroup({ name: 'mygroup' });
	    Ti.Contacts.save();

	    var queriedGroup = Ti.Contacts.getGroupByIdentifier(group.identifier);
	    should(queriedGroup).not.be.null;
	    should(queriedGroup.name).be.eql(group.name);
	    should(queriedGroup.identifier).be.eql(group.identifier);

	    // Now remove the group we created to clean up properly
	    Ti.Contacts.removeGroup(group);
	    Ti.Contacts.save();

        // Make sure it was removed
	    queriedGroup = Ti.Contacts.getGroupByIdentifier(group.identifier);
	    should(queriedGroup).be.null;

	    finish();
	});
	it("getPeopleWithName", function(finish) {
		should(Ti.Contacts.getPeopleWithName).be.a.Function;
		var smiths = Ti.Contacts.getPeopleWithName("smith");
		should(smiths).be.an.Array;
		finish();
	});
	it("getPersonByID", function(finish) {
		should(Ti.Contacts.getPersonByID).be.a.Function;
		// deprecated, do no more for now
		finish();
	});
	it("getPersonByIdentifier", function(finish) {
		should(Ti.Contacts.getPersonByIdentifier).be.a.Function;
		// check for a person by bad identifier
		var noPerson = Ti.Contacts.getPersonByIdentifier("doesntexist");
		should(noPerson).be.null;
		finish();
	});
	// Skip on Windows 8.1
	(Ti.Platform.version.indexOf('8.1' == 0) ? it.skip : it)("Person add/remove", function (finish) {
	    // TODO Remove Arthur first if he already exists!

	    // create a person
	    var person = Ti.Contacts.createPerson({
	        firstName: 'Arthur',
	        lastName: 'Evans'
	    });
	    Ti.Contacts.save();

	    // Query for person we created
	    var queriedPerson = Ti.Contacts.getPersonByIdentifier(person.identifier);
	    should(queriedPerson).not.be.null;
	    should(queriedPerson.firstName).be.eql(person.firstName);
	    should(queriedPerson.lastName).be.eql(person.lastName);
	    should(queriedPerson.identifier).be.eql(person.identifier);

	    // remove the person
	    Ti.Contacts.removePerson(queriedPerson);
	    Ti.Contacts.save();

	    // Make sure they got removed
	    queriedPerson = Ti.Contacts.getPersonByIdentifier(person.identifier);
	    should(queriedPerson).be.null;
	    finish();
	});
	it("removeGroup", function(finish) {
	    should(Ti.Contacts.removeGroup).be.a.Function;
        // We exercise removal in Group add/remove
		finish();
	});
	it("removePerson", function(finish) {
		should(Ti.Contacts.removePerson).be.a.Function;
		// We exercise removal in Person add/remove
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
		// We exercise save above when we test adding/removing groups and person
		finish();
	});
	it("showContacts", function(finish) {
		should(Ti.Contacts.showContacts).be.a.Function;
		// TODO Test the method
		finish();
	});
	// TODO Test reload event?
});
