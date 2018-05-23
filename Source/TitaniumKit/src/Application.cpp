/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Application.hpp"
#include <sstream>

namespace Titanium
{
	Application::Application(const JSContext& js_context)
	    : js_context__(js_context)
	{
	}

	JSValue Application::Run(const std::string& app_js)
	{
		std::string show_error_js = R"js(
/**
 * Creates the Red Screen Of Death!
 * @param (e) Error or Exception
 */
function Titanium_RedScreenOfDeath(e) {

    // We don't want to show RSOD in production mode. re-throw.
    if (Ti.App.deployType == "production") {
        throw e;
    }

    try {
        var win = Ti.UI.createWindow({
                backgroundColor: "#f00",
                layout: "vertical"
            }),
            view,
            button;

        function makeMessage(e) {
            return (e.fileName ? "In " + e.fileName + " " : "") + (e.message || e.toString()).trim() + (e.lineNumber ? " (line " + e.lineNumber + " column " + e.columnNumber + ")" : "");
        } 
        function makeLabel(text, height, color, fontSize) {
            var label = Ti.UI.createView({
                height: height,
                width: Ti.UI.FILL
            });
            label.add(Ti.UI.createLabel({
                color: color,
                font: { fontSize: fontSize, fontWeight: "bold" },
                width:  Ti.UI.FILL,
                height: Ti.UI.FILL,
                textAlign: Ti.UI.TEXT_ALIGNMENT_CENTER,
                text: text
            }));
            win.add(label);
        }

        Ti.API.error("----- Titanium Javascript Runtime Error -----");
        Ti.API.error("Message: Uncaught Error: " + makeMessage(e));

        win.add(view = Ti.UI.createView({ height: "12%" }));
        makeLabel("Application Error", "15%", "#0f0", "34");
        makeLabel(makeMessage(e), "45%", "#fff", "26");
        win.add(view = Ti.UI.createView({ height: "12%" }));
        view.add(button = Ti.UI.createButton({ title: "Dismiss" }));
        button.addEventListener("click", function () {
            win.close();
        });

        makeLabel("Error messages will only be displayed during development. When your app is packaged for final distribution, no error screen will appear. Test your code!", "16%", "#000", "20");

        win.open();
    } catch (er) {
        Ti.API.error(er);
    }
}
  )js";

		js_context__.JSEvaluateScript(show_error_js);

		try {
			std::ostringstream os;
			os << "try {\n";
			os << "  require('" << app_js << "');\n";
			os << "  Ti.Analytics._startPostingEvents();\n";
			os << "} catch (E) {\n";
			os << "  Titanium_RedScreenOfDeath(E);\n";
			os << "}";
			return js_context__.JSEvaluateScript(os.str());
		} catch (const std::exception& stdex) {
			const auto what = js_context__.CreateString(stdex.what());
			const auto rsod = js_context__.get_global_object().GetProperty("Titanium_RedScreenOfDeath");
			auto rsod_func = static_cast<JSObject>(rsod);
			const std::vector<JSValue> args = { what };
			return rsod_func(args, rsod_func);
		}
		return js_context__.CreateUndefined();
	}

	JSContext Application::get_context() const
	{
		return js_context__;
	}

}  // namespace Titanium
