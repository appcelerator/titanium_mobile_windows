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
    this.__controllerPath = "phone/soundRemote";
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
    $.__views.soundRemote = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Remote Sound",
        id: "soundRemote"
    });
    $.__views.soundRemote && $.addTopLevelView($.__views.soundRemote);
    $.__views.__alloyId153 = Ti.UI.createLabel({
        width: 250,
        height: 125,
        color: "#333",
        backgroundColor: "#eee",
        borderRadius: 4,
        textAlign: Ti.UI.TEXT_ALIGNMENT_CENTER,
        text: "To be added ⚒",
        id: "__alloyId153"
    });
    $.__views.soundRemote.add($.__views.__alloyId153);
    exports.destroy = function() {};
    _.extend($, $.__views);
    require("log");
    !function() {}();
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;