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
    this.__controllerPath = "controls/views/imageview";
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
    $.__views.imageview = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Image View",
        id: "imageview"
    });
    $.__views.imageview && $.addTopLevelView($.__views.imageview);
    $.__views.myImage = Ti.UI.createImageView({
        image: "/images/titanium-logo.png",
        width: 300,
        id: "myImage"
    });
    $.__views.imageview.add($.__views.myImage);
    exports.destroy = function() {};
    _.extend($, $.__views);
    !function() {}();
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;