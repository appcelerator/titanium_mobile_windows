function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function switchChanged(e) {
        $.state.setText("The switch value changed to " + e.value);
        log.args("Ti.UI.Switch value changed to " + e.value);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/switchcontrol";
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
    $.__views.switchcontrol = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Switch",
        id: "switchcontrol"
    });
    $.__views.switchcontrol && $.addTopLevelView($.__views.switchcontrol);
    $.__views.state = Ti.UI.createLabel({
        top: 100,
        left: 20,
        right: 20,
        width: Ti.UI.FILL,
        textAlign: "center",
        font: {
            fontSize: 15
        },
        id: "state"
    });
    $.__views.switchcontrol.add($.__views.state);
    $.__views.__alloyId58 = Ti.UI.createSwitch({
        onTintColor: "blue",
        id: "__alloyId58"
    });
    $.__views.switchcontrol.add($.__views.__alloyId58);
    switchChanged ? $.addListener($.__views.__alloyId58, "change", switchChanged) : __defers["$.__views.__alloyId58!change!switchChanged"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.__alloyId58!change!switchChanged"] && $.addListener($.__views.__alloyId58, "change", switchChanged);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;