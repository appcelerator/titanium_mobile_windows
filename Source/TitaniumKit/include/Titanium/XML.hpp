/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_XML_HPP_
#define _TITANIUM_XML_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class
	  @discussion This is the Titanium.XML module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.XML
	*/
	class TITANIUMKIT_EXPORT XML : public Module, public JSExport<XML>
	{
	public:
		XML(const JSContext&) TITANIUM_NOEXCEPT;
		virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

		virtual ~XML() = default;
		XML(const XML&) = default;
		XML& operator=(const XML&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		XML(XML&&) = default;
		XML& operator=(XML&&) = default;
#endif

		static void JSExportInitialize();

		bool loadJS(const JSContext& js_context);
		virtual JSValue js_parseString(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
		virtual JSValue js_serializeToString(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

	private:
		JSObject ti_xml__;
		JSObject func_parseString__;
		JSObject func_serializeToString__;
	};
}  // namespace Titanium

#endif  // _TITANIUM_XML_HPP_
