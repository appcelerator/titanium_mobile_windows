function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function showAlertDialog() {
        $.alert.show();
    }
    function alertDialogClicked(e) {
        alert("Selected button at index: " + e.index);
        log.args("Ti.UI.AlertDialog selected button at index: " + e.index);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/alertdialog";
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
    $.__views.alertdialog = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Alert Dialog",
        id: "alertdialog"
    });
    $.__views.alertdialog && $.addTopLevelView($.__views.alertdialog);
    $.__views.__alloyId14 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        title: "Show Alert Dialog",
        id: "__alloyId14"
    });
    $.__views.alertdialog.add($.__views.__alloyId14);
    showAlertDialog ? $.addListener($.__views.__alloyId14, "click", showAlertDialog) : __defers["$.__views.__alloyId14!click!showAlertDialog"] = true;
    var __alloyId16 = [];
    __alloyId16.push("Confirm");
    __alloyId16.push("Delete");
    __alloyId16.push("Cancel");
    $.__views.alert = Ti.UI.createAlertDialog({
        cancel: 0,
        destructive: 1,
        preferred: 2,
        buttonNames: __alloyId16,
        id: "alert",
        title: "Logout",
        message: "Do you really want to log-out?"
    });
    alertDialogClicked ? $.addListener($.__views.alert, "click", alertDialogClicked) : __defers["$.__views.alert!click!alertDialogClicked"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.__alloyId14!click!showAlertDialog"] && $.addListener($.__views.__alloyId14, "click", showAlertDialog);
    __defers["$.__views.alert!click!alertDialogClicked"] && $.addListener($.__views.alert, "click", alertDialogClicked);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;