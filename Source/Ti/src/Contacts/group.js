
function Group(name, identifier, recordId) {
	this.name = name;
	this.identifier = identifier; // generated UUID upon creation
	this.recordId = recordId; // Number, becomes rowid of entry in DB
}

/**
 * Create Database if necessary and set up tables. Opens the Database for operations. Callers must close the database when done!
 **/
function createDatabase() {
    var db = Ti.Database.open('appc_contacts');
    db.execute('CREATE TABLE IF NOT EXISTS people_groups (group_id INTEGER PRIMARY KEY, person_identifier TEXT)');
    db.execute('CREATE TABLE IF NOT EXISTS groups (name TEXT, identifier TEXT)');
	return db;
}

/**
 * Creates a group with the given name and returns it.
 **/
Group.create = function (name) {
	var db = createDatabase(),
		identifier = Ti.Platform.createUUID();
	try {
		db.execute('INSERT INTO groups (name, identifier) VALUES (?, ?)', name, identifier);
		return new Group(name, identifier, db.lastInsertRowId);
	}
	finally {
	    db && db.close();
	}
};

/**
 * Adds a person to this group in our database.
 **/
Group.prototype.add = function (person) {
	var db = createDatabase();
	try {
		db.execute('INSERT INTO people_groups (group_id, person_identifier) VALUES (?, ?)', this.recordId, person.identifier);
	}
	finally {
	    db && db.close();
	}
};

/**
 * Removes a person from this group in our database.
 **/
Group.prototype.remove = function (person) {
	var db = createDatabase();
	try {
		db.execute('DELETE FROM people_groups WHERE (group_id IS ? AND person_identifier IS ?)', this.recordId, person.identifier);
	}
	finally {
	    db && db.close();
	}
};

/**
 * Removes this group from the database and removes any associations with people from the database as well.
 *
 **/
Group.prototype.destroy = function () {
	var db = createDatabase();
	try {
		db.execute('DELETE FROM people_groups WHERE (group_id IS ?)', this.recordId);
		db.execute('DELETE FROM groups WHERE (rowid IS ?)', this.recordId);
	}
	finally {
	    db && db.close();
	}
};

/**
 * Returns an array of strings holding the identifiers of the people in this group.
 * @return {Array[String]} identifiers of the group's members (Ti.Contacts.Person.identifier)
 **/
Group.prototype.memberIdentifiers = function () {
	var db,
		rows,
		identifiers = [];
	// group hasn't been saved yet
	if (this.recordId == null) {
		return identifiers;
	}

	db = createDatabase();
	try {
		rows = db.execute('SELECT person_identifier FROM people_groups WHERE (group_id IS ?)', this.recordId);
		try {
			while (rows.isValidRow()) {
				identifiers.push(rows.fieldByName('person_identifier'));
				rows.next();
			}
			return identifiers;
		}
		finally {
		    rows && rows.close();
		}
	}
	finally {
	    db && db.close();
	}
};

/**
 * Returns an array of the people in this group.
 *
 * FIXME this is a very dumb/naive approach where we grab all the identifiers
 * of the members and then grab them one by one. We should be able to batch this better somehow.
 * Maybe at least past a certain threshold we do a Ti.Contacts.getAllPeople(); and then match them up.
 *
 * @return {Array[Ti.Contacts.Person]}
 **/
Group.prototype.members = function () {
	var identifiers = memberIdentifiers(),
			result = [];
	// TODO Any way we can grab them async/in parallel?
	for (var i = 0; i < identifiers.length; i++) {
		result.push(Ti.Contacts.getPersonByIdentifier(identifiers[i]));
	}
	return result;
};

/**
 *
 * @return {Array[Group]}
 **/
Group.getAllGroups = function () {
	var db = createDatabase(),
		rows,
		groups = [];
	try {
		rows = db.execute('SELECT * FROM groups');
		try {
			while (rows.isValidRow()) {
				groups.push(new Group(rows.fieldByName('name'), rows.fieldByName('identifier'), rows.fieldByName('rowid')));
				rows.next();
			}
			return groups;
		}
		finally {
			rows && rows.close();
		}
	}
	finally {
	    db && db.close();
	}
};

Group.getGroupByIdentifier = function (identifier) {
	var db = createDatabase(),
		rows,
		group;
	try {
		rows = db.execute('SELECT * FROM groups WHERE identifier = ?', identifier);
		try {
			if (rows.isValidRow()) {
				group = new Group(rows.fieldByName('name'), rows.fieldByName('identifier'), rows.fieldByName('rowid'));
			}
			return group;
		}
		finally {
		    rows && rows.close();
		}
	}
	finally {
	    db && db.close();
	}
};


// API
this.exports = Group;
