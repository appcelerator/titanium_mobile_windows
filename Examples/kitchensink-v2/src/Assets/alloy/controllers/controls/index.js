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
        var identifier = "controls/" + e.section.getItemAt(e.itemIndex).properties.itemId;
        var component = Alloy.createController(identifier).getView();
        Alloy.CFG.tabGroup.getActiveTab().open(component);
        log.args("Ti.UI.TabGroup.activeTab.open", identifier);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/index";
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
    $.__views.__alloyId20 = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Controls",
        id: "__alloyId20"
    });
    var __alloyId23 = [];
    $.__views.__alloyId24 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Views",
            subtitle: "'Ti.UI.View, Ti.UI.ImageView, ...'",
            itemId: "views/index",
            id: "__alloyId24"
        }
    };
    __alloyId23.push($.__views.__alloyId24);
    $.__views.__alloyId25 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Label",
            subtitle: "'Ti.UI.Label'",
            itemId: "label",
            id: "__alloyId25"
        }
    };
    __alloyId23.push($.__views.__alloyId25);
    $.__views.__alloyId26 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Switch",
            subtitle: "'Ti.UI.Switch'",
            itemId: "switchcontrol",
            id: "__alloyId26"
        }
    };
    __alloyId23.push($.__views.__alloyId26);
    $.__views.__alloyId27 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Slider",
            subtitle: "'Ti.UI.Slider'",
            itemId: "slider",
            id: "__alloyId27"
        }
    };
    __alloyId23.push($.__views.__alloyId27);
    $.__views.__alloyId28 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Activity Indicator",
            subtitle: "'Ti.UI.ActivityIndicator'",
            itemId: "activityindicator",
            id: "__alloyId28"
        }
    };
    __alloyId23.push($.__views.__alloyId28);
    $.__views.__alloyId29 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Picker",
            subtitle: "'Ti.UI.Picker'",
            itemId: "picker",
            id: "__alloyId29"
        }
    };
    __alloyId23.push($.__views.__alloyId29);
    $.__views.__alloyId30 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Alert Dialog",
            subtitle: "'Ti.UI.AlertDialog'",
            itemId: "alertdialog",
            id: "__alloyId30"
        }
    };
    __alloyId23.push($.__views.__alloyId30);
    $.__views.__alloyId31 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Option Dialog",
            subtitle: "'Ti.UI.OptionDialog'",
            itemId: "optiondialog",
            id: "__alloyId31"
        }
    };
    __alloyId23.push($.__views.__alloyId31);
    $.__views.__alloyId32 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Text Field",
            subtitle: "'Ti.UI.TextField'",
            itemId: "textfield",
            id: "__alloyId32"
        }
    };
    __alloyId23.push($.__views.__alloyId32);
    $.__views.__alloyId33 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Text Area",
            subtitle: "'Ti.UI.TextArea'",
            itemId: "textarea",
            id: "__alloyId33"
        }
    };
    __alloyId23.push($.__views.__alloyId33);
    $.__views.__alloyId21 = Ti.UI.createListSection({
        id: "__alloyId21"
    });
    $.__views.__alloyId21.items = __alloyId23;
    var __alloyId34 = [];
    __alloyId34.push($.__views.__alloyId21);
    $.__views.listView = Ti.UI.createListView({
        defaultItemTemplate: Ti.UI.LIST_ITEM_TEMPLATE_DEFAULT,
        sections: __alloyId34,
        id: "listView"
    });
    $.__views.__alloyId20.add($.__views.listView);
    openComponent ? $.addListener($.__views.listView, "itemclick", openComponent) : __defers["$.__views.listView!itemclick!openComponent"] = true;
    $.__views.index = Ti.UI.createTab({
        icon: "images/icons/tab.png",
        window: $.__views.__alloyId20,
        title: "Controls",
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