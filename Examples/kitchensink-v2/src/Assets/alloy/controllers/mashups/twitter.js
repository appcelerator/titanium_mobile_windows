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
    this.__controllerPath = "mashups/twitter";
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
    $.__views.twitter = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Twitter",
        id: "twitter"
    });
    $.__views.twitter && $.addTopLevelView($.__views.twitter);
    $.__views.__alloyId124 = Ti.UI.createLabel({
        width: 250,
        height: 125,
        color: "#333",
        backgroundColor: "#eee",
        borderRadius: 4,
        textAlign: Ti.UI.TEXT_ALIGNMENT_CENTER,
        text: "To be added ⚒",
        id: "__alloyId124"
    });
    $.__views.twitter.add($.__views.__alloyId124);
    exports.destroy = function() {};
    _.extend($, $.__views);
    !function() {}();
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;