/**
 * TitaniumKit Titanium.UI.AttributedString
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_ATTRIBUTEDSTRING_HPP_
#define _TITANIUM_ATTRIBUTEDSTRING_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UI/Constants.hpp"
#include "Titanium/UI/Font.hpp"
#include <vector>
#include <unordered_set>

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @struct
		  @discussion An abstract datatype for specifying an attributed string attribute.
		   Attributes are added to the Titanium.UI.AttributedString object to create styled text.
		   The attribute is a JavaScript Object containing three properties: type, value and range.
		  See http://docs.appcelerator.com/platform/latest/#!/api/Attribute
		*/
		struct Attribute
		{
			//
			// Let take a value as-is...because value is pretty dynamic (string, double, ATTRIBUTE_STYLE etc)
			//
			JSValue value;
			std::uint32_t from;
			std::uint32_t length;
			ATTRIBUTE_TYPE type;
		};
		
		TITANIUMKIT_EXPORT Attribute js_to_Attribute(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject  Attribute_to_js(const JSContext& context, const Attribute& value);

		/*!
		  @class
		  @discussion This is the Titanium AttributedString Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.AttributedString
		*/
		class TITANIUMKIT_EXPORT AttributedString : public Module, public JSExport<AttributedString>
		{

		public:

			/*!
			  @property
			  @abstract text
			  @discussion The text applied to the attributed string.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, text);

			/*!
			  @property
			  @abstract attributes
			  @discussion An array of attributes to add.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::vector<Attribute>, attributes);

			/*!
			  @method
			  @abstract addAttribute
			  @discussion Adds an [attribute](Attribute) with the given name and value to the characters in the specified range.
			*/
			virtual void addAttribute(const Attribute& attribute) TITANIUM_NOEXCEPT;

			AttributedString(const JSContext&) TITANIUM_NOEXCEPT;
			virtual ~AttributedString()                          = default;
			AttributedString(const AttributedString&)            = default;
			AttributedString& operator=(const AttributedString&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			AttributedString(AttributedString&&)                 = default;
			AttributedString& operator=(AttributedString&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(text);
			TITANIUM_PROPERTY_DEF(attributes);

			TITANIUM_FUNCTION_DEF(addAttribute);
			TITANIUM_FUNCTION_DEF(getText);
			TITANIUM_FUNCTION_DEF(setText);
			TITANIUM_FUNCTION_DEF(getAttributes);
			TITANIUM_FUNCTION_DEF(setAttributes);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string text__;
			std::vector<Attribute> attributes__;
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_ATTRIBUTEDSTRING_HPP_