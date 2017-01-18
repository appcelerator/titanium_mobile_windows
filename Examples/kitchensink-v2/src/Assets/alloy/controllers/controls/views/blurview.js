function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function applyBlur() {
        $.blurView.setEffect(Ti.UI.iOS.BLUR_EFFECT_STYLE_LIGHT);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/views/blurview";
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
    $.__views.blurview = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Blur View",
        id: "blurview"
    });
    $.__views.blurview && $.addTopLevelView($.__views.blurview);
    $.__views.blurView = Ti.UI.iOS.createBlurView({
        id: "blurView"
    });
    $.__views.blurview.add($.__views.blurView);
    $.__views.__alloyId70 = Ti.UI.createImageView({
        image: "/images/titanium-logo.png",
        width: 200,
        id: "__alloyId70"
    });
    $.__views.blurView.add($.__views.__alloyId70);
    $.__views.__alloyId71 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 40,
        title: "Blur Image",
        id: "__alloyId71"
    });
    $.__views.blurview.add($.__views.__alloyId71);
    applyBlur ? $.addListener($.__views.__alloyId71, "click", applyBlur) : __defers["$.__views.__alloyId71!click!applyBlur"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    !function() {}();
    __defers["$.__views.__alloyId71!click!applyBlur"] && $.addListener($.__views.__alloyId71, "click", applyBlur);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;