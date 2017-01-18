function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function showLogs() {
        $.log.setText(log.history);
        $.scrollView.scrollToBottom();
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "console/index";
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
    $.__views.__alloyId11 = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Console",
        id: "__alloyId11"
    });
    showLogs ? $.addListener($.__views.__alloyId11, "open", showLogs) : __defers["$.__views.__alloyId11!open!showLogs"] = true;
    $.__views.scrollView = Ti.UI.createScrollView({
        contentWidth: Ti.UI.FILL,
        contentHeight: Ti.UI.SIZE,
        id: "scrollView"
    });
    $.__views.__alloyId11.add($.__views.scrollView);
    $.__views.log = Ti.UI.createLabel({
        top: 10,
        right: 10,
        left: 10,
        width: Ti.UI.FILL,
        height: Ti.UI.SIZE,
        font: {
            fontFamily: "Courier New"
        },
        id: "log"
    });
    $.__views.scrollView.add($.__views.log);
    $.__views.index = Ti.UI.createTab({
        icon: "images/icons/console.png",
        window: $.__views.__alloyId11,
        title: "Console",
        id: "index"
    });
    $.__views.index && $.addTopLevelView($.__views.index);
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {
        log.on("change", showLogs);
    }();
    __defers["$.__views.__alloyId11!open!showLogs"] && $.addListener($.__views.__alloyId11, "open", showLogs);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;