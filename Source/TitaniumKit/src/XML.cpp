/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/XML.hpp"
#include <type_traits>

namespace Titanium
{

#include "Titanium/XML/scripts.hpp"

	static const std::string ti_xml_js = R"TI_XML_JS(
this.exports = {};
this.exports.parseString = function(_string) {
    var result = new DOMParser().parseFromString(_string, 'text/xml');
    if (result === undefined) {
        throw new Error("Unable to parse string as XML");
    } else {
        return result;
    }
}; 
this.exports.serializeToString = function(_xml) {
    return new XMLSerializer().serializeToString(_xml);
};
)TI_XML_JS";


	XML::XML(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context)
			, ti_xml(js_context.CreateObject())
	{
	}

	XML::XML(const XML& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
	    : Module(rhs.get_context(), arguments)
			, ti_xml(rhs.ti_xml) 
	{
		// There's no "new Ti.XML()" 
	}

	void XML::JSExportInitialize()
	{
		JSExport<XML>::SetClassVersion(1);
		JSExport<XML>::SetParent(JSExport<Module>::Class());
		JSExport<XML>::AddFunctionProperty("parseString", std::mem_fn(&XML::js_parseString));
		JSExport<XML>::AddFunctionProperty("serializeToString", std::mem_fn(&XML::js_serializeToString));
	}

	bool XML::loadResource(const JSContext& js_context) {
		if (ti_xml.HasProperty("parseString") && ti_xml.HasProperty("serializeToString")) {
			return true;
		}

		auto export_object = js_context.CreateObject();

		get_context().JSEvaluateScript(dom_js, export_object);
		get_context().JSEvaluateScript(sax_js, export_object);
		get_context().JSEvaluateScript(dom_parser_js, export_object);
		get_context().JSEvaluateScript(ti_xml_js, export_object);

		if (export_object.HasProperty("exports")) {
			ti_xml = static_cast<JSObject>(export_object.GetProperty("exports"));
		} else {
			return false;
		}
		return true;
	}

	JSValue XML::js_parseString(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		// lazy loading
		const auto loaded = loadResource(get_context());

		if (loaded && arguments.size() > 0) {
			auto func = ti_xml.GetProperty("parseString");
			return static_cast<JSObject>(func)(arguments, this_object);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute XML.parseString");
			return get_context().CreateNull();
		}
	}

	JSValue XML::js_serializeToString(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		// lazy loading
		const auto loaded = loadResource(get_context());

		if (loaded && arguments.size() > 0) {
			auto func = ti_xml.GetProperty("serializeToString");
			return static_cast<JSObject>(func)(arguments, this_object);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute XML.serializeToString");
			return get_context().CreateNull();
		}
	}

}  // namespace Titanium
