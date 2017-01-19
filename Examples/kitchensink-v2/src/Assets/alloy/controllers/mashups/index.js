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
        var identifier = "mashups/" + e.section.getItemAt(e.itemIndex).properties.itemId;
        var component = Alloy.createController(identifier).getView();
        Alloy.CFG.tabGroup.getActiveTab().open(component);
        log.args("Ti.UI.TabGroup.activeTab.open", identifier);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "mashups/index";
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
    $.__views.__alloyId118 = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Mashups",
        id: "__alloyId118"
    });
    var __alloyId121 = [];
    $.__views.__alloyId122 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Twitter",
            itemId: "twitter",
            id: "__alloyId122"
        }
    };
    __alloyId121.push($.__views.__alloyId122);
    $.__views.__alloyId119 = Ti.UI.createListSection({
        id: "__alloyId119"
    });
    $.__views.__alloyId119.items = __alloyId121;
    var __alloyId123 = [];
    __alloyId123.push($.__views.__alloyId119);
    $.__views.listView = Ti.UI.createListView({
        sections: __alloyId123,
        id: "listView"
    });
    $.__views.__alloyId118.add($.__views.listView);
    openComponent ? $.addListener($.__views.listView, "itemclick", openComponent) : __defers["$.__views.listView!itemclick!openComponent"] = true;
    $.__views.index = Ti.UI.createTab({
        icon: "images/icons/mashups.png",
        window: $.__views.__alloyId118,
        title: "Mashups",
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