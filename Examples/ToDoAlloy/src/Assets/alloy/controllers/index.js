function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function __alloyId7(e) {
        if (e && e.fromAdapter) return;
        __alloyId7.opts || {};
        var models = whereFunction(__alloyId6);
        var len = models.length;
        var rows = [];
        for (var i = 0; len > i; i++) {
            var __alloyId3 = models[i];
            __alloyId3.__transform = transformFunction(__alloyId3);
            var __alloyId5 = Alloy.createController("row", {
                $model: __alloyId3
            });
            rows.push(__alloyId5.getViewEx({
                recurse: true
            }));
        }
        $.__views.todoTable.setData(rows);
    }
    function whereFunction(collection) {
        return whereIndex ? collection.where({
            done: 1 === whereIndex ? 0 : 1
        }) : collection.models;
    }
    function transformFunction(model) {
        var transform = model.toJSON();
        transform.item = "[" + transform.item + "]";
        return transform;
    }
    function addToDoItem() {
        Alloy.createController("add").getView().open();
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "index";
    this.args = arguments[0] || {};
    if (arguments[0]) {
        {
            __processArg(arguments[0], "__parentSymbol");
        }
        {
            __processArg(arguments[0], "$model");
        }
        {
            __processArg(arguments[0], "__itemTemplate");
        }
    }
    var $ = this;
    var exports = {};
    var __defers = {};
    $.__views.todoWin = Ti.UI.createWindow({
        backgroundColor: "#fff",
        fullscreen: false,
        navBarHidden: true,
        exitOnClose: true,
        id: "todoWin",
        title: "Todo"
    });
    $.__views.todoWin && $.addTopLevelView($.__views.todoWin);
    $.__views.header = Ti.UI.createView({
        top: Alloy.Globals.top,
        height: "50dp",
        width: Ti.UI.FILL,
        backgroundGradient: {
            type: "linear",
            startPoint: {
                x: "0%",
                y: "0%"
            },
            endPoint: {
                x: "0%",
                y: "100%"
            },
            colors: [ {
                color: "#a00",
                offset: 0
            }, {
                color: "#800",
                offset: 1
            } ]
        },
        id: "header"
    });
    $.__views.todoWin.add($.__views.header);
    $.__views.title = Ti.UI.createLabel({
        color: "#fff",
        left: "10dp",
        font: {
            fontSize: "24dp",
            fontWeight: "bold"
        },
        text: "Alloy Todo",
        id: "title"
    });
    $.__views.header.add($.__views.title);
    $.__views.__alloyId2 = Ti.UI.createView({
        height: "48dp",
        width: "3dp",
        top: "1dp",
        right: "50dp",
        backgroundGradient: {
            type: "linear",
            startPoint: {
                x: "0%",
                y: "0%"
            },
            endPoint: {
                x: "100%",
                y: "0%"
            },
            colors: [ {
                color: "#666",
                offset: 0
            }, {
                color: "#ccc",
                offset: .5
            }, {
                color: "#666",
                offset: 1
            } ]
        },
        id: "__alloyId2"
    });
    $.__views.header.add($.__views.__alloyId2);
    $.__views.addView = Ti.UI.createView({
        top: 0,
        bottom: 0,
        right: 0,
        width: "50dp",
        id: "addView"
    });
    $.__views.header.add($.__views.addView);
    addToDoItem ? $.addListener($.__views.addView, "click", addToDoItem) : __defers["$.__views.addView!click!addToDoItem"] = true;
    $.__views.addImage = Ti.UI.createImageView({
        height: Ti.UI.FILL,
        width: Ti.UI.FILL,
        color: "#fff",
        backgroundColor: "transparent",
        image: "/ic_menu_add.png",
        touchEnabled: false,
        id: "addImage"
    });
    $.__views.addView.add($.__views.addImage);
    $.__views.todoTable = Ti.UI.createTableView({
        top: Alloy.Globals.tableTop,
        bottom: "46dp",
        id: "todoTable",
        backgroundColor:'blue'
    });
    $.__views.todoWin.add($.__views.todoTable);
    var __alloyId6 = Alloy.Collections["todo"] || todo;
    __alloyId6.on("fetch destroy change add remove reset", __alloyId7);
    exports.destroy = function() {
        __alloyId6.off("fetch destroy change add remove reset", __alloyId7);
    };
    _.extend($, $.__views);
    var todos = Alloy.Collections.todo;
    var INDEXES = {
        All: 0,
        Active: 1,
        Done: 2
    };
    var whereIndex = INDEXES["All"];
    $.todoWin.open();
    todos && todos.fetch();
    __defers["$.__views.addView!click!addToDoItem"] && $.addListener($.__views.addView, "click", addToDoItem);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;