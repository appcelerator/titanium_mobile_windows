/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/XML.hpp"
#include <type_traits>

#include "Titanium/XML/dom_js.hpp"
#include "Titanium/XML/dom_parser_js.hpp"
#include "Titanium/XML/sax_js.hpp"

namespace Titanium
{

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
	    : Module(js_context),
	      func_parseString__(js_context.CreateObject()),
	      func_serializeToString__(js_context.CreateObject()),
		  ti_xml__(js_context.CreateObject())
	{
		// There's no "new Ti.XML()" 
		TITANIUM_LOG_DEBUG("XML:: ctor ", this);
	}

	void XML::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
		HAL_LOG_DEBUG("XML:: postCallAsConstructor ", this);
	}

	void XML::JSExportInitialize()
	{
		JSExport<XML>::SetClassVersion(1);
		JSExport<XML>::SetParent(JSExport<Module>::Class());
		JSExport<XML>::AddFunctionProperty("parseString", std::mem_fn(&XML::js_parseString));
		JSExport<XML>::AddFunctionProperty("serializeToString", std::mem_fn(&XML::js_serializeToString));
	}

	bool XML::loadJS(const JSContext& js_context) {
		if (func_parseString__.IsFunction() && func_serializeToString__.IsFunction()) {
			return true;
		}

		ti_xml__ = js_context.CreateObject();

		get_context().JSEvaluateScript(sax_js, ti_xml__);
		get_context().JSEvaluateScript(dom_js, ti_xml__);
		get_context().JSEvaluateScript(dom_parser_js, ti_xml__);
		get_context().JSEvaluateScript(ti_xml_js, ti_xml__);

		if (ti_xml__.HasProperty("exports")) {
			const auto exports = static_cast<JSObject>(ti_xml__.GetProperty("exports"));
			if (exports.HasProperty("parseString") && exports.HasProperty("serializeToString")) {
				const auto parseString_property = exports.GetProperty("parseString");
				const auto serializeToString_property = exports.GetProperty("serializeToString");
				
				TITANIUM_ASSERT(parseString_property.IsObject());
				TITANIUM_ASSERT(serializeToString_property.IsObject());
				
				func_parseString__       = static_cast<JSObject>(parseString_property);
				func_serializeToString__ = static_cast<JSObject>(serializeToString_property);
				
				return func_parseString__.IsFunction() && func_serializeToString__.IsFunction();
			}
		}
		return false;
	}

	JSValue XML::js_parseString(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		// lazy loading
		const auto loaded = loadJS(this_object.get_context());

		if (loaded && arguments.size() > 0) {
			return func_parseString__(arguments, ti_xml__);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute XML.parseString");
			return get_context().CreateNull();
		}
	}

	JSValue XML::js_serializeToString(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		// lazy loading
		const auto loaded = loadJS(this_object.get_context());

		if (loaded && arguments.size() > 0) {
			return func_serializeToString__(arguments, ti_xml__);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute XML.serializeToString");
			return get_context().CreateNull();
		}
	}

}  // namespace Titanium
