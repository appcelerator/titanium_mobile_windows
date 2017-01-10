function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function stepperValueChanged(e) {
        $.state.setText("The stepper value changed to " + e.value);
        log.args("Ti.UI.Stepper value changed to " + e.value);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/stepper";
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
    $.__views.stepper = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Stepper",
        id: "stepper"
    });
    $.__views.stepper && $.addTopLevelView($.__views.stepper);
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
    $.__views.stepper.add($.__views.state);
    $.__views.__alloyId57 = Ti.UI.iOS.createStepper({
        mininum: 0,
        maximum: 10,
        tintColor: "red",
        id: "__alloyId57"
    });
    $.__views.stepper.add($.__views.__alloyId57);
    stepperValueChanged ? $.addListener($.__views.__alloyId57, "change", stepperValueChanged) : __defers["$.__views.__alloyId57!change!stepperValueChanged"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.__alloyId57!change!stepperValueChanged"] && $.addListener($.__views.__alloyId57, "change", stepperValueChanged);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;