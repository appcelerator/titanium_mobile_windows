function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function showIndicator() {
        $.indicatorLight.show();
        $.indicatorDark.show();
        $.indicatorBig.show();
        $.indicatorMessage.show();
        $.indicatorNavBar.show();
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/activityindicator";
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
    $.__views.activityindicator = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Activity Indicator",
        id: "activityindicator"
    });
    $.__views.activityindicator && $.addTopLevelView($.__views.activityindicator);
    showIndicator ? $.addListener($.__views.activityindicator, "open", showIndicator) : __defers["$.__views.activityindicator!open!showIndicator"] = true;
    $.__views.indicatorNavBar = Ti.UI.createActivityIndicator({
        bottom: 20,
        height: Ti.UI.SIZE,
        id: "indicatorNavBar"
    });
    $.__views.activityindicator.rightNavButton = $.__views.indicatorNavBar;
    $.__views.__alloyId13 = Ti.UI.createView({
        width: 300,
        height: Ti.UI.SIZE,
        backgroundColor: "#aaaaaa",
        layout: "vertical",
        id: "__alloyId13"
    });
    $.__views.activityindicator.add($.__views.__alloyId13);
    $.__views.indicatorLight = Ti.UI.createActivityIndicator({
        bottom: 20,
        height: Ti.UI.SIZE,
        top: 20,
        style: Ti.UI.ActivityIndicatorStyle.PLAIN,
        id: "indicatorLight"
    });
    $.__views.__alloyId13.add($.__views.indicatorLight);
    $.__views.indicatorDark = Ti.UI.createActivityIndicator({
        bottom: 20,
        height: Ti.UI.SIZE,
        style: Ti.UI.ActivityIndicatorStyle.DARK,
        id: "indicatorDark"
    });
    $.__views.__alloyId13.add($.__views.indicatorDark);
    $.__views.indicatorBig = Ti.UI.createActivityIndicator({
        bottom: 20,
        height: Ti.UI.SIZE,
        style: Ti.UI.ActivityIndicatorStyle.BIG,
        id: "indicatorBig"
    });
    $.__views.__alloyId13.add($.__views.indicatorBig);
    $.__views.indicatorMessage = Ti.UI.createActivityIndicator({
        bottom: 20,
        height: Ti.UI.SIZE,
        style: Ti.UI.ActivityIndicatorStyle.DARK,
        message: "Loading ...",
        id: "indicatorMessage"
    });
    $.__views.__alloyId13.add($.__views.indicatorMessage);
    exports.destroy = function() {};
    _.extend($, $.__views);
    !function() {}();
    __defers["$.__views.activityindicator!open!showIndicator"] && $.addListener($.__views.activityindicator, "open", showIndicator);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;