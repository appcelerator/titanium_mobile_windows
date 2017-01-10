function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function openSoundComponent(e) {
        var identifier = "phone/" + e.section.getItemAt(e.itemIndex).properties.itemId;
        var component = Alloy.createController(identifier).getView();
        Alloy.CFG.tabGroup.getActiveTab().open(component);
        log.args("Ti.UI.TabGroup.activeTab.open", identifier);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "phone/sound";
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
    $.__views.sound = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Sound",
        id: "sound"
    });
    $.__views.sound && $.addTopLevelView($.__views.sound);
    var __alloyId143 = [];
    $.__views.__alloyId144 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Local Sound",
            itemId: "soundLocal",
            id: "__alloyId144"
        }
    };
    __alloyId143.push($.__views.__alloyId144);
    $.__views.__alloyId145 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Remote Sound",
            itemId: "soundRemote",
            id: "__alloyId145"
        }
    };
    __alloyId143.push($.__views.__alloyId145);
    $.__views.__alloyId146 = {
        properties: {
            accessoryType: Ti.UI.LIST_ACCESSORY_TYPE_DISCLOSURE,
            subtitleColor: "#777",
            title: "Remote Streaming",
            itemId: "soundRemoteStreaming",
            id: "__alloyId146"
        }
    };
    __alloyId143.push($.__views.__alloyId146);
    $.__views.__alloyId141 = Ti.UI.createListSection({
        id: "__alloyId141"
    });
    $.__views.__alloyId141.items = __alloyId143;
    var __alloyId147 = [];
    __alloyId147.push($.__views.__alloyId141);
    $.__views.listView = Ti.UI.createListView({
        sections: __alloyId147,
        id: "listView"
    });
    $.__views.sound.add($.__views.listView);
    openSoundComponent ? $.addListener($.__views.listView, "itemclick", openSoundComponent) : __defers["$.__views.listView!itemclick!openSoundComponent"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.listView!itemclick!openSoundComponent"] && $.addListener($.__views.listView, "itemclick", openSoundComponent);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;