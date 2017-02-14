/**
 * Titanium.UI.TableViewRow
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/TableViewRow.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <boost/algorithm/string.hpp>

namespace Titanium
{
	namespace UI
	{
    	TableViewRow::TableViewRow(const JSContext& js_context) TITANIUM_NOEXCEPT
        	: View(js_context, "Ti.UI.TableViewRow"),
        	color__(""),
        	hasCheck__(false),
        	hasChild__(false),
        	title__(""),
        	data__(js_context.CreateObject())
    	{
    	}

		TITANIUM_PROPERTY_READWRITE(TableViewRow, std::string, color)
		TITANIUM_PROPERTY_READWRITE(TableViewRow, Font, font)
		TITANIUM_PROPERTY_READWRITE(TableViewRow, bool, hasCheck)
		TITANIUM_PROPERTY_READWRITE(TableViewRow, bool, hasChild)
		TITANIUM_PROPERTY_READWRITE(TableViewRow, std::string, title)

		TITANIUM_PROPERTY_WRITE(TableViewRow, JSObject, data)
		JSObject TableViewRow::get_data() TITANIUM_NOEXCEPT
		{
			// This indicates raw data is empty. In this case we should return TableViewRow
			if (!data__.HasProperty("title")) {
				return get_object();
			}
			return data__;
		}

		void TableViewRow::JSExportInitialize()
		{
			JSExport<TableViewRow>::SetClassVersion(1);
			JSExport<TableViewRow>::SetParent(JSExport<View>::Class());

			TITANIUM_ADD_PROPERTY(TableViewRow, color);
			TITANIUM_ADD_PROPERTY(TableViewRow, font);
			TITANIUM_ADD_PROPERTY(TableViewRow, hasCheck);
			TITANIUM_ADD_PROPERTY(TableViewRow, hasChild);
			TITANIUM_ADD_PROPERTY(TableViewRow, title);

			TITANIUM_ADD_FUNCTION(TableViewRow, getColor);
			TITANIUM_ADD_FUNCTION(TableViewRow, setColor);
			TITANIUM_ADD_FUNCTION(TableViewRow, getFont);
			TITANIUM_ADD_FUNCTION(TableViewRow, setFont);
			TITANIUM_ADD_FUNCTION(TableViewRow, getHasCheck);
			TITANIUM_ADD_FUNCTION(TableViewRow, setHasCheck);
			TITANIUM_ADD_FUNCTION(TableViewRow, getHasChild);
			TITANIUM_ADD_FUNCTION(TableViewRow, setHasChild);
			TITANIUM_ADD_FUNCTION(TableViewRow, getTitle);
			TITANIUM_ADD_FUNCTION(TableViewRow, setTitle);
		}

		TITANIUM_PROPERTY_GETTER(TableViewRow, color)
		{
			return get_context().CreateString(get_color());
		}

		TITANIUM_PROPERTY_SETTER(TableViewRow, color)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_color(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TableViewRow, getColor, color)
		TITANIUM_FUNCTION_AS_SETTER(TableViewRow, setColor, color)

		TITANIUM_PROPERTY_GETTER(TableViewRow, font)
		{
			return Font_to_js(get_context(), get_font());
		}

		TITANIUM_PROPERTY_SETTER(TableViewRow, font)
		{
			TITANIUM_ASSERT(argument.IsObject());
			set_font(js_to_Font(static_cast<JSObject>(argument)));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TableViewRow, getFont, font)
		TITANIUM_FUNCTION_AS_SETTER(TableViewRow, setFont, font)

		TITANIUM_PROPERTY_GETTER(TableViewRow, hasCheck)
		{
			return get_context().CreateBoolean(get_hasCheck());
		}

		TITANIUM_PROPERTY_SETTER(TableViewRow, hasCheck)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_hasCheck(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TableViewRow, getHasCheck, hasCheck)
		TITANIUM_FUNCTION_AS_SETTER(TableViewRow, setHasCheck, hasCheck)

		TITANIUM_PROPERTY_GETTER(TableViewRow, hasChild)
		{
			return get_context().CreateBoolean(get_hasChild());
		}

		TITANIUM_PROPERTY_SETTER(TableViewRow, hasChild)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_hasChild(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TableViewRow, getHasChild, hasChild)
		TITANIUM_FUNCTION_AS_SETTER(TableViewRow, setHasChild, hasChild)

		TITANIUM_PROPERTY_GETTER(TableViewRow, title)
		{
			return get_context().CreateString(get_title());
		}

		TITANIUM_PROPERTY_SETTER(TableViewRow, title)
		{
			TITANIUM_ASSERT(argument.IsString());
			set_title(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(TableViewRow, getTitle, title)
		TITANIUM_FUNCTION_AS_SETTER(TableViewRow, setTitle, title)

		bool TableViewRow::contains(const std::string& query, const bool& filterAnchored, const bool& filterCaseInsensitive, const std::string& filterAttribute)
		{
			const auto title = filterAttribute.empty() ? get_title() : static_cast<std::string>(get_data().GetProperty(filterAttribute));
			const auto normalized_title = filterCaseInsensitive ? boost::algorithm::to_lower_copy(title) : title;
			const auto normalized_query = filterCaseInsensitive ? boost::algorithm::to_lower_copy(query) : query;

			if (filterAnchored) {
				return boost::starts_with(normalized_title, normalized_query);
			} else {
				return normalized_title.find(normalized_query) != std::string::npos;
			}
		}
	} // namespace UI
} // namespace Titanium
