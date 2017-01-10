function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function listStaticShortcuts() {
        if (!appShortcuts) return alert("This device does not support Force Touch");
        log.args("Ti.UI.iOS.ApplicationShortcuts.listStaticShortcuts", appShortcuts.listStaticShortcuts());
    }
    function listDynamicShortcuts() {
        if (!appShortcuts) return alert("This device does not support Force Touch");
        var res = appShortcuts.listDynamicShortcuts();
        log.args("Ti.UI.iOS.ApplicationShortcuts.listDynamicShortcuts", res);
        0 === res.length && Ti.UI.createAlertDialog({
            title: "None",
            message: "Use createDynamicShortcut() to create a dynamic shortcut."
        }).show();
    }
    function dynamicShortcutExists() {
        if (!appShortcuts) return alert("This device does not support Force Touch");
        var res = appShortcuts.dynamicShortcutExists("details");
        log.args("Ti.UI.iOS.ApplicationShortcuts.dynamicShortcutExists", "details", res);
        res || Ti.UI.createAlertDialog({
            title: "Does not exist",
            message: "Use createDynamicShortcut() to create a dynamic shortcut."
        }).show();
    }
    function getDynamicShortcut() {
        if (!appShortcuts) return alert("This device does not support Force Touch");
        var res = appShortcuts.getDynamicShortcut("details");
        log.args("Ti.UI.iOS.ApplicationShortcuts.getDynamicShortcut", "details", res);
        res || Ti.UI.createAlertDialog({
            title: "Does not exist",
            message: "Use createDynamicShortcut() to create a dynamic shortcut."
        }).show();
    }
    function removeDynamicShortcut() {
        if (!appShortcuts) return alert("This device does not support Force Touch");
        appShortcuts.removeDynamicShortcut("details");
        Ti.UI.createAlertDialog({
            title: "Removed",
            message: "Use createDynamicShortcut() to create a dynamic shortcut."
        }).show();
    }
    function createDynamicShortcut() {
        if (!appShortcuts) return alert("This device does not support Force Touch");
        appShortcuts.addDynamicShortcut({
            itemtype: "details",
            title: "Titanium rocks!",
            subtitle: "(Dynamically created)",
            icon: "images/icons/shortcutItemIcon.png",
            userInfo: {
                created_at: Date.now()
            }
        });
    }
    function removeAllDynamicShortcuts() {
        if (!appShortcuts) return alert("This device does not support Force Touch");
        appShortcuts.removeAllDynamicShortcuts();
        Ti.UI.createAlertDialog({
            title: "Removed",
            message: "Use createDynamicShortcut() to create a dynamic shortcut."
        }).show();
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "phone/shortcutItems";
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
    $.__views.shortcutItems = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Shortcut Items",
        layout: "vertical",
        id: "shortcutItems"
    });
    $.__views.shortcutItems && $.addTopLevelView($.__views.shortcutItems);
    $.__views.__alloyId134 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        title: "listStaticShortcuts()",
        id: "__alloyId134"
    });
    $.__views.shortcutItems.add($.__views.__alloyId134);
    listStaticShortcuts ? $.addListener($.__views.__alloyId134, "click", listStaticShortcuts) : __defers["$.__views.__alloyId134!click!listStaticShortcuts"] = true;
    $.__views.__alloyId135 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        title: "listDynamicShortcuts()",
        id: "__alloyId135"
    });
    $.__views.shortcutItems.add($.__views.__alloyId135);
    listDynamicShortcuts ? $.addListener($.__views.__alloyId135, "click", listDynamicShortcuts) : __defers["$.__views.__alloyId135!click!listDynamicShortcuts"] = true;
    $.__views.__alloyId136 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        title: "dynamicShortcutExists('details')",
        id: "__alloyId136"
    });
    $.__views.shortcutItems.add($.__views.__alloyId136);
    dynamicShortcutExists ? $.addListener($.__views.__alloyId136, "click", dynamicShortcutExists) : __defers["$.__views.__alloyId136!click!dynamicShortcutExists"] = true;
    $.__views.__alloyId137 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        title: "getDynamicShortcut('details')",
        id: "__alloyId137"
    });
    $.__views.shortcutItems.add($.__views.__alloyId137);
    getDynamicShortcut ? $.addListener($.__views.__alloyId137, "click", getDynamicShortcut) : __defers["$.__views.__alloyId137!click!getDynamicShortcut"] = true;
    $.__views.__alloyId138 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        title: "createDynamicShortcut()",
        id: "__alloyId138"
    });
    $.__views.shortcutItems.add($.__views.__alloyId138);
    createDynamicShortcut ? $.addListener($.__views.__alloyId138, "click", createDynamicShortcut) : __defers["$.__views.__alloyId138!click!createDynamicShortcut"] = true;
    $.__views.__alloyId139 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        title: "removeDynamicShortcut('details')",
        id: "__alloyId139"
    });
    $.__views.shortcutItems.add($.__views.__alloyId139);
    removeDynamicShortcut ? $.addListener($.__views.__alloyId139, "click", removeDynamicShortcut) : __defers["$.__views.__alloyId139!click!removeDynamicShortcut"] = true;
    $.__views.__alloyId140 = Ti.UI.createButton({
        width: 300,
        height: 40,
        tintColor: "white",
        borderRadius: 4,
        backgroundColor: Alloy.CFG.styles.tintColor,
        top: 20,
        title: "removeAllDynamicShortcuts()",
        id: "__alloyId140"
    });
    $.__views.shortcutItems.add($.__views.__alloyId140);
    removeAllDynamicShortcuts ? $.addListener($.__views.__alloyId140, "click", removeAllDynamicShortcuts) : __defers["$.__views.__alloyId140!click!removeAllDynamicShortcuts"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    var appShortcuts;
    !function() {
        Ti.UI.iOS.forceTouchSupported && (appShortcuts = Ti.UI.iOS.createApplicationShortcuts());
    }(arguments[0] || {});
    __defers["$.__views.__alloyId134!click!listStaticShortcuts"] && $.addListener($.__views.__alloyId134, "click", listStaticShortcuts);
    __defers["$.__views.__alloyId135!click!listDynamicShortcuts"] && $.addListener($.__views.__alloyId135, "click", listDynamicShortcuts);
    __defers["$.__views.__alloyId136!click!dynamicShortcutExists"] && $.addListener($.__views.__alloyId136, "click", dynamicShortcutExists);
    __defers["$.__views.__alloyId137!click!getDynamicShortcut"] && $.addListener($.__views.__alloyId137, "click", getDynamicShortcut);
    __defers["$.__views.__alloyId138!click!createDynamicShortcut"] && $.addListener($.__views.__alloyId138, "click", createDynamicShortcut);
    __defers["$.__views.__alloyId139!click!removeDynamicShortcut"] && $.addListener($.__views.__alloyId139, "click", removeDynamicShortcut);
    __defers["$.__views.__alloyId140!click!removeAllDynamicShortcuts"] && $.addListener($.__views.__alloyId140, "click", removeAllDynamicShortcuts);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;