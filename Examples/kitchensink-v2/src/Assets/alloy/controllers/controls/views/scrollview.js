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
    this.__controllerPath = "controls/views/scrollview";
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
    $.__views.scrollview = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Scroll View",
        id: "scrollview"
    });
    $.__views.scrollview && $.addTopLevelView($.__views.scrollview);
    $.__views.__alloyId115 = Ti.UI.createScrollView({
        id: "__alloyId115"
    });
    $.__views.scrollview.add($.__views.__alloyId115);
    $.__views.__alloyId116 = Ti.UI.createLabel({
        text: "S\nC\nR\nO\nL\nL\nS\n\nC\nR\nO\nL\nL\n\nS\nC\nR\nO\nL\nL\n\nS\nC\nR\nO\nL\nL\n\nS\nC\nR\nO\nL\nL\n\nS\nC\nR\nO\nL\nL\n\nS\nC\nR\nO\nL\nL\n\nS\nC\nR\nO\nL\nL\n\nS\nC\nR\nO\nL\nL\n\nS\nC\nR\nO\nL\nL\n\nS\nC\nR\nO\nL\nL\n\nS\nC\nR\nO\nL\nL\n\nS\nC\nR\nO\nL\nL\n\nS\nC\nR\nO\nL\nL\n\n",
        id: "__alloyId116"
    });
    $.__views.__alloyId115.add($.__views.__alloyId116);
    exports.destroy = function() {};
    _.extend($, $.__views);
    !function() {}();
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;