function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function sliderValueChanged(e) {
        $.state.setText("Current value: " + e.value.toFixed(2) + " / " + e.source.max);
        log.args("Ti.UI.Slider value changed to " + e.value);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/slider";
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
    $.__views.slider = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Slider",
        id: "slider"
    });
    $.__views.slider && $.addTopLevelView($.__views.slider);
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
    $.__views.slider.add($.__views.state);
    $.__views.__alloyId56 = Ti.UI.createSlider({
        tintColor: "green",
        min: 0,
        max: 1,
        width: 200,
        value: .75,
        id: "__alloyId56"
    });
    $.__views.slider.add($.__views.__alloyId56);
    sliderValueChanged ? $.addListener($.__views.__alloyId56, "change", sliderValueChanged) : __defers["$.__views.__alloyId56!change!sliderValueChanged"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.__alloyId56!change!sliderValueChanged"] && $.addListener($.__views.__alloyId56, "change", sliderValueChanged);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;