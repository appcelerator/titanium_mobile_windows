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
        var identifier = "platform/" + e.section.getItemAt(e.itemIndex).properties.itemId;
        var component = Alloy.createController(identifier).getView();
        Alloy.CFG.tabGroup.getActiveTab().open(component);
        log.args("Ti.UI.TabGroup.activeTab.open", identifier);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "platform/index";
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
    $.__views.__alloyId155 = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Platform",
        id: "__alloyId155"
    });
    var __alloyId158 = [];
    $.__views.__alloyId159 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Network",
            itemId: "network",
            id: "__alloyId159"
        }
    };
    __alloyId158.push($.__views.__alloyId159);
    $.__views.__alloyId156 = Ti.UI.createListSection({
        id: "__alloyId156"
    });
    $.__views.__alloyId156.items = __alloyId158;
    var __alloyId160 = [];
    __alloyId160.push($.__views.__alloyId156);
    $.__views.listView = Ti.UI.createListView({
        sections: __alloyId160,
        id: "listView"
    });
    $.__views.__alloyId155.add($.__views.listView);
    openComponent ? $.addListener($.__views.listView, "itemclick", openComponent) : __defers["$.__views.listView!itemclick!openComponent"] = true;
    $.__views.index = Ti.UI.createTab({
        icon: "images/icons/tab.png",
        window: $.__views.__alloyId155,
        title: "Platform",
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