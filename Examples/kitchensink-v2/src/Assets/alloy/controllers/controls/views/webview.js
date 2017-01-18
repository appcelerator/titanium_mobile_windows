function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function onBeforeLoad(e) {
        log.args("Ti.UI.WebView will start loading content", e);
    }
    function onLoad(e) {
        log.args("Ti.UI.WebView completed loading content", e);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/views/webview";
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
    $.__views.webview = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Web View",
        id: "webview"
    });
    $.__views.webview && $.addTopLevelView($.__views.webview);
    $.__views.__alloyId117 = Ti.UI.createWebView({
        url: "https://appcelerator.com",
        id: "__alloyId117"
    });
    $.__views.webview.add($.__views.__alloyId117);
    onBeforeLoad ? $.addListener($.__views.__alloyId117, "beforeload", onBeforeLoad) : __defers["$.__views.__alloyId117!beforeload!onBeforeLoad"] = true;
    onLoad ? $.addListener($.__views.__alloyId117, "load", onLoad) : __defers["$.__views.__alloyId117!load!onLoad"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.__alloyId117!beforeload!onBeforeLoad"] && $.addListener($.__views.__alloyId117, "beforeload", onBeforeLoad);
    __defers["$.__views.__alloyId117!load!onLoad"] && $.addListener($.__views.__alloyId117, "load", onLoad);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;