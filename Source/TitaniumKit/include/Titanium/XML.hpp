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

		virtual ~XML() = default;
		XML(const XML&) = default;
		XML& operator=(const XML&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		XML(XML&&) = default;
		XML& operator=(XML&&) = default;
#endif

		static void JSExportInitialize();
		static JSObject GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT;

		bool loadJS();

		TITANIUM_FUNCTION_DEF(parseString);
		TITANIUM_FUNCTION_DEF(serializeToString);

	private:
		JSObject ti_xml__;
		JSObject func_parseString__;
		JSObject func_serializeToString__;
	};
}  // namespace Titanium

#endif  // _TITANIUM_XML_HPP_
