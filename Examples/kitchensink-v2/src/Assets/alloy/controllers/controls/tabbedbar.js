function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function tabbedBarSelectedIndex(e) {
        log.args("Ti.UI.iOS.TabbedBar changed to index: ", e.index);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/tabbedbar";
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
    $.__views.tabbedbar = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Tabbed Bar",
        id: "tabbedbar"
    });
    $.__views.tabbedbar && $.addTopLevelView($.__views.tabbedbar);
    var __alloyId61 = [];
    var __alloyId65 = {
        title: "One"
    };
    __alloyId61.push(__alloyId65);
    var __alloyId66 = {
        title: "Two"
    };
    __alloyId61.push(__alloyId66);
    var __alloyId67 = {
        title: "Three"
    };
    __alloyId61.push(__alloyId67);
    $.__views.__alloyId59 = Ti.UI.iOS.createTabbedBar({
        tintColor: Alloy.CFG.styles.tintColor,
        width: 200,
        index: 1,
        labels: __alloyId61,
        id: "__alloyId59"
    });
    $.__views.tabbedbar.add($.__views.__alloyId59);
    tabbedBarSelectedIndex ? $.addListener($.__views.__alloyId59, "click", tabbedBarSelectedIndex) : __defers["$.__views.__alloyId59!click!tabbedBarSelectedIndex"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.__alloyId59!click!tabbedBarSelectedIndex"] && $.addListener($.__views.__alloyId59, "click", tabbedBarSelectedIndex);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;