function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/views/view";
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
    $.__views.view = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "View",
        id: "view"
    });
    $.__views.view && $.addTopLevelView($.__views.view);
    $.__views.view1 = Ti.UI.createView({
        top: 10,
        width: 100,
        height: 100,
        backgroundColor: "#f00",
        id: "view1"
    });
    $.__views.view.add($.__views.view1);
    $.__views.view2 = Ti.UI.createView({
        width: 100,
        height: 100,
        backgroundColor: "#0f0",
        id: "view2"
    });
    $.__views.view.add($.__views.view2);
    $.__views.view3 = Ti.UI.createView({
        bottom: 10,
        width: 100,
        height: 100,
        backgroundColor: "#00f",
        id: "view3"
    });
    $.__views.view.add($.__views.view3);
    exports.destroy = function() {};
    _.extend($, $.__views);
    !function() {}();
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;