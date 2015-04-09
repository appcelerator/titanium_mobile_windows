/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Application.hpp"
#include "Titanium/ApplicationBuilder.hpp"
#include <sstream>

namespace Titanium
{
	Application::Application(const ApplicationBuilder& builder)
	    : js_context__(builder.js_context__)
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
    try {
        Ti.API.error("Application Error: "+JSON.stringify(e, null, 2));

        var f = e.fileName || "",
            match = f.match(/:\/\/.+(\/.*)/),
            filename = match ? match[1] : e.fileName,
            line = e.lineNumber,
            win = Ti.UI.createWindow({
                backgroundColor: "#f00",
                layout: "vertical"
            }),
            view,
            button;

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

        win.add(view = Ti.UI.createView({ height: "12%" }));
        makeLabel("Application Error", "15%", "#0f0", "34");
        makeLabel((e.message || e.toString()).trim() + (line ? " (line " + line + ")" : ""), "45%", "#fff", "26");
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
			os << "} catch (E) {\n";
			os << "  Titanium_RedScreenOfDeath(E);\n";
			os << "}";
			return js_context__.JSEvaluateScript(os.str());
		} catch (const std::exception& stdex) {
			const std::string what = stdex.what();
			TITANIUM_LOG_ERROR(what);
			return js_context__.JSEvaluateScript("Titanium_RedScreenOfDeath('" + what + "');");
		}
		return js_context__.CreateUndefined();
	}

	JSContext Application::get_context() const
	{
		return js_context__;
	}

}  // namespace Titanium
