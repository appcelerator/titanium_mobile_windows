function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function textFieldValueChanged(e) {
        log.args("Ti.UI.TextField changed value to " + e.value);
    }
    function textFieldFocussed() {
        log.args("Ti.UI.TextField focussed!");
    }
    function textFieldBlurred() {
        log.args("Ti.UI.TextField blurred!");
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/textfield";
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
    $.__views.textfield = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Text Field",
        id: "textfield"
    });
    $.__views.textfield && $.addTopLevelView($.__views.textfield);
    $.__views.__alloyId69 = Ti.UI.createTextField({
        width: 300,
        height: 40,
        backgroundColor: "#f0f0f0",
        borderRadius: 4,
        id: "__alloyId69"
    });
    $.__views.textfield.add($.__views.__alloyId69);
    textFieldValueChanged ? $.addListener($.__views.__alloyId69, "change", textFieldValueChanged) : __defers["$.__views.__alloyId69!change!textFieldValueChanged"] = true;
    textFieldFocussed ? $.addListener($.__views.__alloyId69, "focus", textFieldFocussed) : __defers["$.__views.__alloyId69!focus!textFieldFocussed"] = true;
    textFieldBlurred ? $.addListener($.__views.__alloyId69, "blur", textFieldBlurred) : __defers["$.__views.__alloyId69!blur!textFieldBlurred"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.__alloyId69!change!textFieldValueChanged"] && $.addListener($.__views.__alloyId69, "change", textFieldValueChanged);
    __defers["$.__views.__alloyId69!focus!textFieldFocussed"] && $.addListener($.__views.__alloyId69, "focus", textFieldFocussed);
    __defers["$.__views.__alloyId69!blur!textFieldBlurred"] && $.addListener($.__views.__alloyId69, "blur", textFieldBlurred);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;