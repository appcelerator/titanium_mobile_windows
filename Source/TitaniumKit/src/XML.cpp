/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/XML.hpp"
#include <type_traits>

namespace Titanium
{
	static const std::string dom_parser_js = "";
	static const std::string dom_js = "";
	static const std::string sax_js = "";
	static const std::string ti_xml_js = R"TI_XML_JS(
exports = {};
exports.parseString = function(_string) {
    var result = new DOMParser().parseFromString(_string, 'text/xml');
    if (result === undefined) {
        throw new Error("Unable to parse string as XML");
    } else {
        return result;
    }
}; 
exports.serializeToString = function(_xml) {
    return new XMLSerializer().serializeToString(_xml);
};
)TI_XML_JS";


	XML::XML(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context)
			, ti_xml(js_context.CreateNull())
	{
	}

	XML::XML(const XML& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
	    : Module(rhs, arguments)
			, ti_xml(rhs.ti_xml) 
	{
		auto export_object = loadResource();
		if (export_object.HasProperty("exports")) {
			ti_xml = static_cast<JSObject>(export_object.GetProperty("exports"));
		} else {
			TITANIUM_LOG_ERROR("Failed to load XML resources");
		}
		TITANIUM_ASSERT(ti_xml.HasProperty("parseString"));
	}

	void XML::JSExportInitialize()
	{
		JSExport<XML>::SetClassVersion(1);
		JSExport<XML>::SetParent(JSExport<Module>::Class());
		JSExport<XML>::AddFunctionProperty("parseString", std::mem_fn(&XML::js_parseString));
		JSExport<XML>::AddFunctionProperty("serializeToString", std::mem_fn(&XML::js_serializeToString));
	}

	JSObject XML::loadResource() TITANIUM_NOEXCEPT {
		auto export_object = get_context().CreateObject();

		get_context().JSEvaluateScript(dom_js, export_object);
		get_context().JSEvaluateScript(sax_js, export_object);
		get_context().JSEvaluateScript(dom_parser_js, export_object);
		get_context().JSEvaluateScript(ti_xml_js, export_object);

		return export_object;
	}

	JSValue XML::js_parseString(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (ti_xml.HasProperty("parseString")) {
			auto func = ti_xml.GetProperty("parseString");
			return static_cast<JSObject>(func)();
		} else {
			TITANIUM_LOG_ERROR("Failed to execute XML.parseString");
			return get_context().CreateNull();
		}
	}

	JSValue XML::js_serializeToString(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (ti_xml.HasProperty("serializeToString")) {
			auto func = ti_xml.GetProperty("serializeToString");
			return static_cast<JSObject>(func)();
		} else {
			TITANIUM_LOG_ERROR("Failed to execute XML.serializeToString");
			return get_context().CreateNull();
		}
	}

}  // namespace Titanium
