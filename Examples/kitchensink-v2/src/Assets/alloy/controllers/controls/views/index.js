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
        var identifier = "controls/views/" + e.section.getItemAt(e.itemIndex).properties.itemId;
        var component = Alloy.createController(identifier).getView();
        Alloy.CFG.tabGroup.getActiveTab().open(component);
        log.args("Ti.UI.TabGroup.activeTab.open", identifier);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/views/index";
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
    $.__views.index = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Controls",
        id: "index"
    });
    $.__views.index && $.addTopLevelView($.__views.index);
    var __alloyId74 = [];
    $.__views.__alloyId75 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "View",
            subtitle: "'Ti.UI.View'",
            itemId: "view",
            id: "__alloyId75"
        }
    };
    __alloyId74.push($.__views.__alloyId75);
    $.__views.__alloyId76 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Scroll View",
            subtitle: "'Ti.UI.ScrollView'",
            itemId: "scrollview",
            id: "__alloyId76"
        }
    };
    __alloyId74.push($.__views.__alloyId76);
    $.__views.__alloyId77 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Scrollable View",
            subtitle: "'Ti.UI.ScrollableView'",
            itemId: "scrollableview",
            id: "__alloyId77"
        }
    };
    __alloyId74.push($.__views.__alloyId77);
    $.__views.__alloyId78 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "List View",
            subtitle: "'Ti.UI.ListView'",
            itemId: "listview",
            id: "__alloyId78"
        }
    };
    __alloyId74.push($.__views.__alloyId78);
    $.__views.__alloyId79 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Image View",
            subtitle: "'Ti.UI.ImageView'",
            itemId: "imageview",
            id: "__alloyId79"
        }
    };
    __alloyId74.push($.__views.__alloyId79);
    $.__views.__alloyId80 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Web View",
            subtitle: "'Ti.UI.WebView'",
            itemId: "webview",
            id: "__alloyId80"
        }
    };
    __alloyId74.push($.__views.__alloyId80);
    $.__views.__alloyId72 = Ti.UI.createListSection({
        id: "__alloyId72"
    });
    $.__views.__alloyId72.items = __alloyId74;
    var __alloyId81 = [];
    __alloyId81.push($.__views.__alloyId72);
    $.__views.listView = Ti.UI.createListView({
        defaultItemTemplate: Ti.UI.LIST_ITEM_TEMPLATE_SUBTITLE,
        sections: __alloyId81,
        id: "listView"
    });
    $.__views.index.add($.__views.listView);
    openComponent ? $.addListener($.__views.listView, "itemclick", openComponent) : __defers["$.__views.listView!itemclick!openComponent"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.listView!itemclick!openComponent"] && $.addListener($.__views.listView, "itemclick", openComponent);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;