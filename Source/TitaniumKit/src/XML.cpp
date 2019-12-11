/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/XML.hpp"
#include "Titanium/detail/TiImpl.hpp"
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
	    : Module(js_context, "Ti.XML"),
		  ti_xml__(js_context.CreateObject()),
	      func_parseString__(js_context.CreateObject()),
	      func_serializeToString__(js_context.CreateObject())
	{
		// There's no "new Ti.XML()"
		TITANIUM_LOG_DEBUG("XML:: ctor ", this);
	}

	void XML::JSExportInitialize()
	{
		JSExport<XML>::SetClassVersion(1);
		JSExport<XML>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_FUNCTION(XML, parseString);
		TITANIUM_ADD_FUNCTION(XML, serializeToString);
	}


	JSObject XML::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		static JSObject cached = js_context.CreateObject();
		static std::once_flag of;
		std::call_once(of, [=] {
			JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
			JSObject Titanium = static_cast<JSObject>(Titanium_property);

			JSValue Object_property = Titanium.GetProperty("XML");
			TITANIUM_ASSERT(Object_property.IsObject());  // precondition
			cached = static_cast<JSObject>(Object_property);
		});
		return cached;
	}

	bool XML::loadJS() {
		if (func_parseString__.IsFunction() && func_serializeToString__.IsFunction()) {
			return true;
		}

		ti_xml__ = get_context().CreateObject();

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

	TITANIUM_FUNCTION(XML, parseString)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<XML>();

		// lazy loading
		const auto loaded = object_ptr->loadJS();

		if (loaded && arguments.size() > 0) {
			return object_ptr->func_parseString__(arguments, this_object);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute XML.parseString");
			return get_context().CreateNull();
		}
	}

	TITANIUM_FUNCTION(XML, serializeToString)
	{
		const auto js_context = this_object.get_context();
		const auto object_ptr = GetStaticObject(js_context).GetPrivate<XML>();

		// lazy loading
		const auto loaded = object_ptr->loadJS();

		if (loaded && arguments.size() > 0) {
			return object_ptr->func_serializeToString__(arguments, ti_xml__);
		} else {
			TITANIUM_LOG_ERROR("Failed to execute XML.serializeToString");
			return get_context().CreateNull();
		}
	}

}  // namespace Titanium
