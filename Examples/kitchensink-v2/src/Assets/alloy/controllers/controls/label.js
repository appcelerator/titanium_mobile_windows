function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function changeToCenterAlignment() {
        $.myLabel.setTextAlign("center");
    }
    function changeToRightAlignment() {
        $.myLabel.setTextAlign("right");
    }
    function changeColor() {
        $.myLabel.setColor("red");
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/label";
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
    $.__views.label = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Label",
        id: "label"
    });
    $.__views.label && $.addTopLevelView($.__views.label);
    $.__views.myLabel = Ti.UI.createLabel({
        top: 50,
        textAlign: "left",
        left: 50,
        right: 50,
        text: "Lorem ipsum dolor sit amet, consetetur sadipscing elitr, sed diam nonumy eirmod tempor.",
        id: "myLabel"
    });
    $.__views.label.add($.__views.myLabel);
    $.__views.__alloyId35 = Ti.UI.createView({
        top: 200,
        layout: "vertical",
        id: "__alloyId35"
    });
    $.__views.label.add($.__views.__alloyId35);
    $.__views.__alloyId36 = Ti.UI.createButton({
        title: "Change text align to center",
        id: "__alloyId36"
    });
    $.__views.__alloyId35.add($.__views.__alloyId36);
    changeToCenterAlignment ? $.addListener($.__views.__alloyId36, "click", changeToCenterAlignment) : __defers["$.__views.__alloyId36!click!changeToCenterAlignment"] = true;
    $.__views.__alloyId37 = Ti.UI.createButton({
        title: "Change text align to right",
        id: "__alloyId37"
    });
    $.__views.__alloyId35.add($.__views.__alloyId37);
    changeToRightAlignment ? $.addListener($.__views.__alloyId37, "click", changeToRightAlignment) : __defers["$.__views.__alloyId37!click!changeToRightAlignment"] = true;
    $.__views.__alloyId38 = Ti.UI.createButton({
        title: "Change color to red",
        id: "__alloyId38"
    });
    $.__views.__alloyId35.add($.__views.__alloyId38);
    changeColor ? $.addListener($.__views.__alloyId38, "click", changeColor) : __defers["$.__views.__alloyId38!click!changeColor"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    !function() {}();
    __defers["$.__views.__alloyId36!click!changeToCenterAlignment"] && $.addListener($.__views.__alloyId36, "click", changeToCenterAlignment);
    __defers["$.__views.__alloyId37!click!changeToRightAlignment"] && $.addListener($.__views.__alloyId37, "click", changeToRightAlignment);
    __defers["$.__views.__alloyId38!click!changeColor"] && $.addListener($.__views.__alloyId38, "click", changeColor);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;