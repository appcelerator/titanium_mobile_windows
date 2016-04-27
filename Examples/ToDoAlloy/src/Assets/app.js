var Alloy = require("alloy"), _ = Alloy._, Backbone = Alloy.Backbone;

Alloy.Collections.todo = Alloy.createCollection("todo");

Alloy.Globals.top = 0;

Alloy.Globals.tableTop = "50dp";

try {} catch (e) {}

Alloy.createController("index");