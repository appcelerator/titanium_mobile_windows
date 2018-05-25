/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Application.hpp"
#include "Titanium/Module.hpp"
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
                backgroundColor: "#f4f4f4",
                layout: "vertical"
            }),
            button;

        function makeMessage(e) {
            return (e.fileName ? "In " + e.fileName + " " : "") + (e.message || e.toString()).trim() + (e.lineNumber ? " (line " + e.lineNumber + " column " + e.columnNumber + ")" : "");
        }

        Ti.API.error("Message: Uncaught Error: " + makeMessage(e));
        if (e.nativeStack) {
            Ti.API.error(e.nativeStack);
        }

        var label = Ti.UI.createView({
            height: '90%',
            width: Ti.UI.FILL,
            top: 10, left: 10,
            layout: 'vertical',            
        });
        label.add(Ti.UI.createLabel({
            color: 'red',
            width:  Ti.UI.FILL,
            height: Ti.UI.SIZE,
            textAlign: Ti.UI.TEXT_ALIGNMENT_LEFT,
            verticalAlign: Ti.UI.TEXT_VERTICAL_ALIGNMENT_TOP,
            text: makeMessage(e),
        }));
        if (e.nativeStack) {
            label.add(Ti.UI.createView({width: Ti.UI.FILL, height: 20}));
            label.add(Ti.UI.createLabel({
                color: 'red',
                width:  Ti.UI.FILL,
                height: Ti.UI.SIZE,
                textAlign: Ti.UI.TEXT_ALIGNMENT_LEFT,
                verticalAlign: Ti.UI.TEXT_VERTICAL_ALIGNMENT_TOP,
                text: e.nativeStack,
            }));
        }
        win.add(label);

        win.add(button = Ti.UI.createButton({ title: "CONTINUE", backgroundColor: 'red', width: Ti.UI.FILL, height: '10%', bottom: 0 }));
        button.addEventListener("click", function () {
            win.close();
        });

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
			std::ostringstream stacktrace;
			std::uint32_t i = 0;
			for (auto iter = Titanium::Module::BackTrace__.rbegin(); iter != Titanium::Module::BackTrace__.rend(); ++iter) {
				i++;
				stacktrace << i << "  " << *iter << "\n";
			}
			auto js_error = js_context__.CreateError();
			js_error.SetProperty("message", js_context__.CreateString(stdex.what()));
			js_error.SetProperty("nativeStack", js_context__.CreateString(stacktrace.str()));

			const auto rsod = js_context__.get_global_object().GetProperty("Titanium_RedScreenOfDeath");
			auto rsod_func = static_cast<JSObject>(rsod);
			const std::vector<JSValue> args = { js_error };
			return rsod_func(args, rsod_func);
		}
		return js_context__.CreateUndefined();
	}

	JSContext Application::get_context() const
	{
		return js_context__;
	}

}  // namespace Titanium
