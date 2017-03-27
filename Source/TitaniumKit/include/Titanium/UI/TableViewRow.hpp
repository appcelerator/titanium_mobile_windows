/**
 * Titanium.UI.TableViewRow
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_TABLEVIEWROW_HPP_
#define _TITANIUM_TABLEVIEWROW_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Font.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium TableViewRow Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.TableViewRow
		*/
		class TITANIUMKIT_EXPORT TableViewRow : public View, public JSExport<TableViewRow>
		{

		public:

			/*!
			  @property
			  @abstract color
			  @discussion Default text color of the row when not selected, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, color);

			/*!
			  @property
			  @abstract font
			  @discussion Font to use for the row title.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Font, font);

			/*!
			  @property
			  @abstract hasCheck
			  @discussion Determines whether a system-provided checkmark is displayed on the right-hand side of the row.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, hasCheck);

			/*!
			  @property
			  @abstract hasChild
			  @discussion Determines whether a system-provided arrow is displayed on the right-hand side of the row.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, hasChild);

			/*!
			  @property
			  @abstract title
			  @discussion Text to display on the row.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, title);

			/*!
			  @property
			  @abstract data
			  @discussion Raw data of the row
			*/
			void set_data(const JSObject& data) TITANIUM_NOEXCEPT;
			JSObject get_data() TITANIUM_NOEXCEPT;

			TableViewRow(const JSContext&) TITANIUM_NOEXCEPT;
			virtual ~TableViewRow() = default;
			TableViewRow(const TableViewRow&) = default;
			TableViewRow& operator=(const TableViewRow&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TableViewRow(TableViewRow&&)                 = default;
			TableViewRow& operator=(TableViewRow&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(font);
			TITANIUM_FUNCTION_DEF(getFont);
			TITANIUM_FUNCTION_DEF(setFont);
			
			TITANIUM_PROPERTY_DEF(hasCheck);
			TITANIUM_FUNCTION_DEF(getHasCheck);
			TITANIUM_FUNCTION_DEF(setHasCheck);
			
			TITANIUM_PROPERTY_DEF(hasChild);
			TITANIUM_FUNCTION_DEF(getHasChild);
			TITANIUM_FUNCTION_DEF(setHasChild);
			
			TITANIUM_PROPERTY_DEF(title);
			TITANIUM_FUNCTION_DEF(getTitle);
			TITANIUM_FUNCTION_DEF(setTitle);
			
			TITANIUM_PROPERTY_DEF(color);
			TITANIUM_FUNCTION_DEF(getColor);
			TITANIUM_FUNCTION_DEF(setColor);

			bool contains(const std::string& query, const bool& filterAnchored, const bool& filterCaseInsensitive, const std::string& filterAttribute);

			bool get_added()
			{
				return added__;
			}

			void set_added(const bool& added) 
			{
				added__ = added;
			}
			protected:
#pragma warning(push)
#pragma warning(disable : 4251)
				std::string color__;
				Font font__;
				bool hasCheck__;
				bool hasChild__;
				std::string title__;
				JSObject data__;
				// This indicates this row is already added to section.
				bool added__;
#pragma warning(pop)
		};
	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_TABLEVIEWROW_HPP_