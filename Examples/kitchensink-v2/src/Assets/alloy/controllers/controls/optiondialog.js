function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function showOptionDialog() {
        $.dialog.show();
    }
    function optionDialogClicked(e) {
        alert("Selected option at index: " + e.index);
        log.args("Ti.UI.OptionDialog selected option at index: " + e.index);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/optiondialog";
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
    $.__views.optiondialog = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Option Dialog",
        id: "optiondialog"
    });
    $.__views.optiondialog && $.addTopLevelView($.__views.optiondialog);
    $.__views.__alloyId39 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        title: "Show Option Dialog",
        id: "__alloyId39"
    });
    $.__views.optiondialog.add($.__views.__alloyId39);
    showOptionDialog ? $.addListener($.__views.__alloyId39, "click", showOptionDialog) : __defers["$.__views.__alloyId39!click!showOptionDialog"] = true;
    var __alloyId41 = [];
    __alloyId41.push("Confirm");
    __alloyId41.push("Delete");
    __alloyId41.push("Cancel");
    $.__views.dialog = Ti.UI.createOptionDialog({
        options: __alloyId41,
        id: "dialog",
        title: "Available Options"
    });
    optionDialogClicked ? $.addListener($.__views.dialog, "click", optionDialogClicked) : __defers["$.__views.dialog!click!optionDialogClicked"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.__alloyId39!click!showOptionDialog"] && $.addListener($.__views.__alloyId39, "click", showOptionDialog);
    __defers["$.__views.dialog!click!optionDialogClicked"] && $.addListener($.__views.dialog, "click", optionDialogClicked);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;