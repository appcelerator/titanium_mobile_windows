function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function validateDocsInfo() {
        if (true === Ti.App.Properties.getBool("showNotice", true)) {
            var alertNotice = Ti.UI.createAlertDialog({
                title: "Notice",
                message: "While this KitchenSink provides an extensive demonstration of the Titanium API, its structure is not recommended for production apps. Please refer to our documentation for more details.",
                buttonNames: [ "OK", "Visit docs", "Don't show again" ],
                cancel: 0
            });
            alertNotice.addEventListener("click", function(e) {
                1 === e.index ? Ti.Platform.openURL("http://wiki.appcelerator.org/display/guides/Example+Applications") : 2 === e.index && Ti.App.Properties.setBool("showNotice", false);
            });
            alertNotice.show();
        }
    }
    function handleShortcutItem(e) {
        log.args("Ti.App.iOS.shortcutitemclick", e);
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
    var __alloyId1 = [];
    $.__views.__alloyId2 = Alloy.createController("controls/index", {
        id: "__alloyId2"
    });
    __alloyId1.push($.__views.__alloyId2.getViewEx({
        recurse: true
    }));
    $.__views.__alloyId4 = Alloy.createController("phone/index", {
        id: "__alloyId4"
    });
    __alloyId1.push($.__views.__alloyId4.getViewEx({
        recurse: true
    }));
    $.__views.__alloyId6 = Alloy.createController("platform/index", {
        id: "__alloyId6"
    });
    __alloyId1.push($.__views.__alloyId6.getViewEx({
        recurse: true
    }));
    $.__views.__alloyId8 = Alloy.createController("mashups/index", {
        id: "__alloyId8"
    });
    __alloyId1.push($.__views.__alloyId8.getViewEx({
        recurse: true
    }));
    $.__views.__alloyId10 = Alloy.createController("console/index", {
        id: "__alloyId10"
    });
    __alloyId1.push($.__views.__alloyId10.getViewEx({
        recurse: true
    }));
    $.__views.index = Ti.UI.createTabGroup({
        tabs: __alloyId1,
        id: "index"
    });
    $.__views.index && $.addTopLevelView($.__views.index);
    validateDocsInfo ? $.addListener($.__views.index, "open", validateDocsInfo) : __defers["$.__views.index!open!validateDocsInfo"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {
        //Ti.App.iOS.addEventListener("shortcutitemclick", handleShortcutItem);
        Alloy.CFG.tabGroup = $.index;
        $.index.open();
    }();
    __defers["$.__views.index!open!validateDocsInfo"] && $.addListener($.__views.index, "open", validateDocsInfo);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;