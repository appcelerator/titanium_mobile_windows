var Alloy = require("alloy"), _ = require("alloy/underscore")._, model, collection;

var moment = require("alloy/moment");

exports.definition = {
    config: {
        columns: {
            item: "text",
            done: "integer",
            date_completed: "text"
        },
        adapter: {
            type: "sql",
            collection_name: "todo"
        }
    },
    extendModel: function(Model) {
        _.extend(Model.prototype, {
            validate: function(attrs) {
                for (var key in attrs) {
                    var value = attrs[key];
                    if (value) {
                        if ("item" === key && /^\s*$/.test(value)) return "Error: No item!";
                        if ("done" === key && value.length <= 0) return "Error: No completed flag!";
                    }
                }
            }
        });
        return Model;
    },
    extendCollection: function(Collection) {
        _.extend(Collection.prototype, {});
        return Collection;
    }
};

model = Alloy.M("todo", exports.definition, [ function(migration) {
    migration.name = "todo";
    migration.id = "201209301904312";
    migration.up = function(migrator) {
        migrator.createTable({
            columns: {
                item: "text",
                done: "integer",
                date_completed: "text"
            }
        });
    };
    migration.down = function(migrator) {
        migrator.dropTable("todo");
    };
} ]);

collection = Alloy.C("todo", exports.definition, model);

exports.Model = model;

exports.Collection = collection;