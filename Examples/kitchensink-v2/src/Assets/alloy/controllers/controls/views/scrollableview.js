function __processArg(obj, key) {
    var arg = null;
    if (obj) {
        arg = obj[key] || null;
        delete obj[key];
    }
    return arg;
}

function Controller() {
    function scrollableViewDidScroll(e) {
        log.args("Ti.UI.ScrollableView did scroll to index " + e.currentPage);
    }
    require("alloy/controllers/BaseController").apply(this, Array.prototype.slice.call(arguments));
    this.__controllerPath = "controls/views/scrollableview";
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
    $.__views.scrollableview = Ti.UI.createWindow({
        backgroundColor: "black",
        title: "Scrollable View",
        id: "scrollableview"
    });
    $.__views.scrollableview && $.addTopLevelView($.__views.scrollableview);
    var __alloyId111 = [];
    $.__views.view1 = Ti.UI.createView({
        id: "view1",
        backgroundColor: "#836"
    });
    __alloyId111.push($.__views.view1);
    $.__views.__alloyId112 = Ti.UI.createLabel({
        text: "View 1",
        id: "__alloyId112"
    });
    $.__views.view1.add($.__views.__alloyId112);
    $.__views.view2 = Ti.UI.createView({
        id: "view2",
        backgroundColor: "#246"
    });
    __alloyId111.push($.__views.view2);
    $.__views.__alloyId113 = Ti.UI.createLabel({
        text: "View 2",
        id: "__alloyId113"
    });
    $.__views.view2.add($.__views.__alloyId113);
    $.__views.view3 = Ti.UI.createView({
        id: "view3",
        backgroundColor: "#48b"
    });
    __alloyId111.push($.__views.view3);
    $.__views.__alloyId114 = Ti.UI.createLabel({
        text: "View 3",
        id: "__alloyId114"
    });
    $.__views.view3.add($.__views.__alloyId114);
    $.__views.scrollable = Ti.UI.createScrollableView({
        top: 40,
        showPagingControl: true,
        pagingControlColor: Alloy.CFG.styles.tintColor,
        views: __alloyId111,
        id: "scrollable"
    });
    $.__views.scrollableview.add($.__views.scrollable);
    scrollableViewDidScroll ? $.addListener($.__views.scrollable, "scrollend", scrollableViewDidScroll) : __defers["$.__views.scrollable!scrollend!scrollableViewDidScroll"] = true;
    exports.destroy = function() {};
    _.extend($, $.__views);
    var log = require("log");
    !function() {}();
    __defers["$.__views.scrollable!scrollend!scrollableViewDidScroll"] && $.addListener($.__views.scrollable, "scrollend", scrollableViewDidScroll);
    _.extend($, exports);
}

var Alloy = require("alloy"), Backbone = Alloy.Backbone, _ = Alloy._;

module.exports = Controller;