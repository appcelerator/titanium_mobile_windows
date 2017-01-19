function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "platform/network";
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
    $.__views.network = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Network",
        id: "network"
    });
    $.__views.network && $.addTopLevelView($.__views.network);
    $.__views.statusLabel = Ti.UI.createLabel({
        id: "statusLabel"
    });
    $.__views.network.add($.__views.statusLabel);
    $.__views.eventLabel = Ti.UI.createLabel({
        id: "eventLabel"
    });
    $.__views.network.add($.__views.eventLabel);
    exports.destroy = function() {};
    _.extend($, $.__views);
    !function() {
        $.statusLabel.setText("Network type: " + Ti.Network.networkType + ", online: " + Ti.Network.online + ", name: " + Ti.Network.networkTypeName);
        Ti.Network.addEventListener("change", function(e) {
            $.eventLabel.setText("Change fired! Network type: " + e.networkType + ", online: " + e.online + ", name: " + e.networkTypeName);
        });
    }();
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;