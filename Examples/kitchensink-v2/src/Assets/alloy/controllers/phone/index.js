function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function openComponent(e) {
        var identifier = "phone/" + e.section.getItemAt(e.itemIndex).properties.itemId;
        var component = Alloy.createController(identifier).getView();
        Alloy.CFG.tabGroup.getActiveTab().open(component);
        log.args("Ti.UI.TabGroup.activeTab.open", identifier);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "phone/index";
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
    $.__views.__alloyId125 = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Phone",
        id: "__alloyId125"
    });
    var __alloyId128 = [];
    $.__views.__alloyId129 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "3D-Touch: Shortcut Items",
            itemId: "shortcutItems",
            id: "__alloyId129"
        }
    };
    __alloyId128.push($.__views.__alloyId129);
    $.__views.__alloyId130 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "3D-Touch: Peek and Pop",
            itemId: "peekAndPop",
            id: "__alloyId130"
        }
    };
    __alloyId128.push($.__views.__alloyId130);
    $.__views.__alloyId131 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Sound",
            itemId: "sound",
            id: "__alloyId131"
        }
    };
    __alloyId128.push($.__views.__alloyId131);
    $.__views.__alloyId126 = Ti.UI.createListSection({
        id: "__alloyId126"
    });
    $.__views.__alloyId126.items = __alloyId128;
    var __alloyId132 = [];
    __alloyId132.push($.__views.__alloyId126);
    $.__views.listView = Ti.UI.createListView({
        sections: __alloyId132,
        id: "listView"
    });
    $.__views.__alloyId125.add($.__views.listView);
    openComponent ? $.addListener($.__views.listView, "itemclick", openComponent) : __defers["$.__views.listView!itemclick!openComponent"] = true;
    $.__views.index = Ti.UI.createTab({
        icon: "images/icons/phone.png",
        window: $.__views.__alloyId125,
        title: "Phone",
        id: "index"
    });
    $.__views.index && $.addTopLevelView($.__views.index);
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.listView!itemclick!openComponent"] && $.addListener($.__views.listView, "itemclick", openComponent);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;