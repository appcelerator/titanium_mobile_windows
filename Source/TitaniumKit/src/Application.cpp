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

    Ti.App.fireEvent('uncaughtException', e);

    // We don't want to show RSOD in production mode.
    if (Ti.App.deployType == 'production') {
        return;
    }

    try {
        var win = Ti.UI.createWindow({
                backgroundColor: '#F5F5F5',
                layout: 'vertical'
            }),
            button;

        function makeMessage(e) {
            return 'Runtime Exception: ' + (e.fileName ? 'In ' + e.fileName + ' ' : '') + (e.message || e.toString()).trim() + (e.lineNumber ? ' (line ' + e.lineNumber + ' column ' + e.columnNumber + ')' : '');
        }
        function makeLabel(label, str) {
            label.add(Ti.UI.createLabel({
                color: '#E53935',
                width:  Ti.UI.FILL,
                height: Ti.UI.SIZE,
                textAlign: Ti.UI.TEXT_ALIGNMENT_LEFT,
                verticalAlign: Ti.UI.TEXT_VERTICAL_ALIGNMENT_TOP,
                font: { fontFamily: 'Lucida Console'},
                text: str,
            }));
        }

        Ti.API.error('Message: Uncaught Error: ' + makeMessage(e));
        if (e.stack) {
            Ti.API.error(e.stack);
        }
        if (e.nativeStack) {
            Ti.API.error(e.nativeStack);
        }

        var label = Ti.UI.createView({
            height: '90%',
            width: Ti.UI.FILL,
            top: 10, left: 10,
            layout: 'vertical',            
        });
        makeLabel(label, makeMessage(e));
        if (e.stack) {
            label.add(Ti.UI.createView({width: Ti.UI.FILL, height: 20}));
            makeLabel(label, e.stack);
        }
        if (e.nativeStack) {
            label.add(Ti.UI.createView({width: Ti.UI.FILL, height: 20}));
            makeLabel(label, e.nativeStack);
        }
        win.add(label);

        win.add(button = Ti.UI.createButton({ title: 'CONTINUE', backgroundColor: '#E53935', width: Ti.UI.FILL, height: '10%', bottom: 0 }));
        button.addEventListener('click', function () {
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
