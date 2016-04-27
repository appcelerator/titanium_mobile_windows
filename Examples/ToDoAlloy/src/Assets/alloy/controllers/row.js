function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function toggleStatus() {
        setTimeout(function () {
            var todo = todos.get(id);
            todo.set({
                done: todo.get("done") ? 0 : 1,
                date_completed: moment().unix()
            }).save();
        }, 500);
    }
    function deleteTask(e) {
        e.cancelBubble = true;
        var todo = todos.get(id);
        todo.destroy();
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "row";
    this.args = arguments[0] || {};
    if (arguments[0]) {
        {
            __processArg(arguments[0], "__parentSymbol");
        }
        var $model = __processArg(arguments[0], "$model");
        {
            __processArg(arguments[0], "__itemTemplate");
        }
    }
    var $ = this;
    var exports = {};
    var __defers = {};
    $.__views.row = Ti.UI.createTableViewRow({
        height: "50dp",
        backgroundColor: "#fff",
        focusable: false,
        id: "row"
    });
    $.__views.row && $.addTopLevelView($.__views.row);
    $.__views.check = Ti.UI.createImageView({
        image: "/tick_gray_64.png",
        left: 0,
        height: "50dp",
        width: "50dp",
        id: "check"
    });
    $.__views.row.add($.__views.check);
    toggleStatus ? $.addListener($.__views.check, "click", toggleStatus) : __defers["$.__views.check!click!toggleStatus"] = true;
    $.__views.task = Ti.UI.createLabel({
        color: "#000",
        left: "50dp",
        right: "50dp",
        height: Ti.UI.SIZE,
        width: Ti.UI.FILL,
        font: {
            fontSize: "18dp"
        },
        id: "task",
        text: "undefined" != typeof $model.__transform["item"] ? $model.__transform["item"] : $model.get("item")
    });
    $.__views.row.add($.__views.task);
    $.__views.remove = Ti.UI.createImageView({
        image: "/red_x.png",
        right: 20,
        height: "50dp",
        width: "50dp",
        id: "remove"
    });
    $.__views.row.add($.__views.remove);
    deleteTask ? $.addListener($.__views.remove, "click", deleteTask) : __defers["$.__views.remove!click!deleteTask"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var moment = require("alloy/moment");
    var todos = Alloy.Collections.todo;
    var id;
    if ($model) {
        id = $model.id;
        if ($model.get("done")) {
            $.row.backgroundColor = "#eee";
            $.check.backgroundColor = "#eee";
            $.task.color = "#ccc";
            $.check.image = "/tick_64.png";
        } else {
            $.row.backgroundColor = "#fff";
            $.check.backgroundColor = "#fff";
            $.task.color = "#000";
            $.check.image = "/tick_gray_64.png";
        }
    }
    __defers["$.__views.check!click!toggleStatus"] && $.addListener($.__views.check, "click", toggleStatus);
    __defers["$.__views.remove!click!deleteTask"] && $.addListener($.__views.remove, "click", deleteTask);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;