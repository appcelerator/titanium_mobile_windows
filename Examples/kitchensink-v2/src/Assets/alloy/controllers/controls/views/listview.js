function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function handleListViewClick(e) {
        log.args("Ti.UI.ListView clicked cell at index", e.sectionIndex + " / " + e.itemIndex);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/views/listview";
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
    $.__views.listview = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "List View",
        id: "listview"
    });
    $.__views.listview && $.addTopLevelView($.__views.listview);
    var __alloyId83 = {};
    var __alloyId86 = [];
    var __alloyId88 = {
        type: "Ti.UI.Label",
        bindId: "title",
        properties: {
            left: 15,
            color: "red",
            bindId: "title"
        }
    };
    __alloyId86.push(__alloyId88);
    var __alloyId90 = {
        type: "Ti.UI.Label",
        bindId: "detail",
        properties: {
            right: 5,
            color: "green",
            font: {
                fontWeight: "bold"
            },
            bindId: "detail"
        }
    };
    __alloyId86.push(__alloyId90);
    var __alloyId85 = {
        properties: {
            name: "MyCustomTemplate"
        },
        childTemplates: __alloyId86
    };
    __alloyId83["MyCustomTemplate"] = __alloyId85;
    var __alloyId93 = [];
    $.__views.__alloyId94 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Bananas",
            image: "/images/icons/tab.png",
            id: "__alloyId94"
        }
    };
    __alloyId93.push($.__views.__alloyId94);
    $.__views.__alloyId95 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Apples",
            subtitle: "Oranges",
            id: "__alloyId95"
        },
        template: Ti.UI.LIST_ITEM_TEMPLATE_SUBTITLE
    };
    __alloyId93.push($.__views.__alloyId95);
    $.__views.__alloyId96 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Mangos",
            subtitle: "Strawberries",
            id: "__alloyId96"
        },
        template: Ti.UI.LIST_ITEM_TEMPLATE_SETTINGS
    };
    __alloyId93.push($.__views.__alloyId96);
    $.__views.__alloyId97 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Lemon",
            subtitle: "Melone",
            id: "__alloyId97"
        },
        template: Ti.UI.LIST_ITEM_TEMPLATE_CONTACTS
    };
    __alloyId93.push($.__views.__alloyId97);
    $.__views.__alloyId91 = Ti.UI.createListSection({
        headerTitle: "System Item Templates",
        id: "__alloyId91"
    });
    $.__views.__alloyId91.items = __alloyId93;
    var __alloyId98 = [];
    __alloyId98.push($.__views.__alloyId91);
    var __alloyId101 = [];
    $.__views.__alloyId102 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            id: "__alloyId102"
        },
        template: "MyCustomTemplate",
        title: {
            text: "Nectarine"
        },
        detail: {
            text: 3
        }
    };
    __alloyId101.push($.__views.__alloyId102);
    $.__views.__alloyId103 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            id: "__alloyId103"
        },
        template: "MyCustomTemplate",
        title: {
            text: "Pear"
        },
        detail: {
            text: 7,
            color: "blue"
        }
    };
    __alloyId101.push($.__views.__alloyId103);
    $.__views.__alloyId99 = Ti.UI.createListSection({
        headerTitle: "Custom Item Templates",
        id: "__alloyId99"
    });
    $.__views.__alloyId99.items = __alloyId101;
    __alloyId98.push($.__views.__alloyId99);
    var __alloyId106 = [];
    $.__views.__alloyId107 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_NONE,
            subtitleColor: "#777",
            title: "No Accessory",
            id: "__alloyId107"
        }
    };
    __alloyId106.push($.__views.__alloyId107);
    $.__views.__alloyId108 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DETAIL,
            subtitleColor: "#777",
            title: "Detail Accessory",
            id: "__alloyId108"
        }
    };
    __alloyId106.push($.__views.__alloyId108);
    $.__views.__alloyId109 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Disclosure Accessory",
            id: "__alloyId109"
        }
    };
    __alloyId106.push($.__views.__alloyId109);
    $.__views.__alloyId110 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_CHECKMARK,
            subtitleColor: "#777",
            title: "Checkmark Accessory",
            id: "__alloyId110"
        }
    };
    __alloyId106.push($.__views.__alloyId110);
    $.__views.__alloyId104 = Ti.UI.createListSection({
        headerTitle: "Accessory Types",
        id: "__alloyId104"
    });
    $.__views.__alloyId104.items = __alloyId106;
    __alloyId98.push($.__views.__alloyId104);
    $.__views.__alloyId82 = Ti.UI.createListView({
        sections: __alloyId98,
        templates: __alloyId83,
        id: "__alloyId82"
    });
    $.__views.listview.add($.__views.__alloyId82);
    handleListViewClick ? $.addListener($.__views.__alloyId82, "itemclick", handleListViewClick) : __defers["$.__views.__alloyId82!itemclick!handleListViewClick"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.__alloyId82!itemclick!handleListViewClick"] && $.addListener($.__views.__alloyId82, "itemclick", handleListViewClick);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;