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
    this.__controllerPath = "annotation";
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
    $.__views.annotation = Ti.UI.createView({
        layout: "vertical",
        height: Ti.UI.SIZE,
        width: Ti.UI.SIZE,
        id: "annotation"
    });
    $.__views.annotation && $.addTopLevelView($.__views.annotation);
    $.__views.avatar = Ti.UI.createImageView({
        preventDefaultImage: true,
        borderColor: "#038BC8",
        borderWidth: 5,
        borderRadius: 37.5,
        height: 75,
        width: 75,
        id: "avatar"
    });
    $.__views.annotation.add($.__views.avatar);
    $.__views.__alloyId0 = Ti.UI.createLabel({
        font: {
            fontSize: 30,
            fontFamily: "icomoon"
        },
        text: "",
        color: "#038BC8",
        top: -14,
        id: "__alloyId0"
    });
    $.__views.annotation.add($.__views.__alloyId0);
    exports.destroy = function() {};
    _.extend($, $.__views);
    var args = arguments[0] || {};
    $.avatar.image = args.image;
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;