function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function pickerValueChanged(e) {
        $.state.setText("Picker value changed to " + e.selectedValue);
        log.args("Ti.UI.Picker changed value to: " + e.selectedValue);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/picker";
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
    $.__views.picker = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Picker",
        id: "picker"
    });
    $.__views.picker && $.addTopLevelView($.__views.picker);
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
    $.__views.picker.add($.__views.state);
    $.__views.__alloyId45 = Ti.UI.createPicker({
        height: 300,
        bottom: 0,
        width: Ti.UI.FILL,
        selectionIndicator: true,
        useSpinner: true,
        id: "__alloyId45"
    });
    $.__views.picker.add($.__views.__alloyId45);
    var __alloyId46 = [];
    $.__views.__alloyId47 = Ti.UI.createPickerColumn({
        id: "__alloyId47"
    });
    __alloyId46.push($.__views.__alloyId47);
    $.__views.__alloyId48 = Ti.UI.createPickerRow({
        title: "Bananas",
        id: "__alloyId48"
    });
    $.__views.__alloyId47.addRow($.__views.__alloyId48);
    $.__views.__alloyId49 = Ti.UI.createPickerRow({
        title: "Strawberries",
        id: "__alloyId49"
    });
    $.__views.__alloyId47.addRow($.__views.__alloyId49);
    $.__views.__alloyId50 = Ti.UI.createPickerRow({
        title: "Mangos",
        id: "__alloyId50"
    });
    $.__views.__alloyId47.addRow($.__views.__alloyId50);
    $.__views.__alloyId51 = Ti.UI.createPickerRow({
        title: "Grapes",
        id: "__alloyId51"
    });
    $.__views.__alloyId47.addRow($.__views.__alloyId51);
    $.__views.column2 = Ti.UI.createPickerColumn({
        id: "column2"
    });
    __alloyId46.push($.__views.column2);
    $.__views.__alloyId52 = Ti.UI.createPickerRow({
        title: "Red",
        id: "__alloyId52"
    });
    $.__views.column2.addRow($.__views.__alloyId52);
    $.__views.__alloyId53 = Ti.UI.createPickerRow({
        title: "Green",
        id: "__alloyId53"
    });
    $.__views.column2.addRow($.__views.__alloyId53);
    $.__views.__alloyId54 = Ti.UI.createPickerRow({
        title: "Blue",
        id: "__alloyId54"
    });
    $.__views.column2.addRow($.__views.__alloyId54);
    $.__views.__alloyId55 = Ti.UI.createPickerRow({
        title: "Orange",
        id: "__alloyId55"
    });
    $.__views.column2.addRow($.__views.__alloyId55);
    $.__views.__alloyId45.add(__alloyId46);
    pickerValueChanged ? $.addListener($.__views.__alloyId45, "change", pickerValueChanged) : __defers["$.__views.__alloyId45!change!pickerValueChanged"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.__alloyId45!change!pickerValueChanged"] && $.addListener($.__views.__alloyId45, "change", pickerValueChanged);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;