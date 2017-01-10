var moment = require("alloy/moment");

var Log = module.exports = _.extend({}, Backbone.Events);

Log.history = "";

Log.args = function() {
    var args = Array.prototype.slice.call(arguments);
    args = args.map(function(arg) {
        return "string" == typeof arg ? arg : JSON.stringify(arg, null, 2);
    });
    var message = args.join(" ");
    console["info"](message);
    Log.history = (Log.history || "") + "[" + moment().format("HH:mm:ss.SS") + "] " + message + "\n\n";
    Log.trigger("change");
};