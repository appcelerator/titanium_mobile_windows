function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function textAreaValueChanged(e) {
        log.args("Ti.UI.TextArea changed value to " + e.value);
    }
    function textAreaFocussed() {
        log.args("Ti.UI.TextArea focussed!");
    }
    function textAreaBlurred() {
        log.args("Ti.UI.TextArea blurred!");
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/textarea";
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
    $.__views.textarea = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Text Area",
        id: "textarea"
    });
    $.__views.textarea && $.addTopLevelView($.__views.textarea);
    $.__views.__alloyId68 = Ti.UI.createTextArea({
        width: 300,
        height: 100,
        backgroundColor: "#f0f0f0",
        borderRadius: 4,
        id: "__alloyId68"
    });
    $.__views.textarea.add($.__views.__alloyId68);
    textAreaValueChanged ? $.addListener($.__views.__alloyId68, "change", textAreaValueChanged) : __defers["$.__views.__alloyId68!change!textAreaValueChanged"] = true;
    textAreaFocussed ? $.addListener($.__views.__alloyId68, "focus", textAreaFocussed) : __defers["$.__views.__alloyId68!focus!textAreaFocussed"] = true;
    textAreaBlurred ? $.addListener($.__views.__alloyId68, "blur", textAreaBlurred) : __defers["$.__views.__alloyId68!blur!textAreaBlurred"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.__alloyId68!change!textAreaValueChanged"] && $.addListener($.__views.__alloyId68, "change", textAreaValueChanged);
    __defers["$.__views.__alloyId68!focus!textAreaFocussed"] && $.addListener($.__views.__alloyId68, "focus", textAreaFocussed);
    __defers["$.__views.__alloyId68!blur!textAreaBlurred"] && $.addListener($.__views.__alloyId68, "blur", textAreaBlurred);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;