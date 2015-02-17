/**
 * TitaniumKit Titanium.UI.ListItem
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_LISTITEM_HPP_
#define _TITANIUM_UI_LISTITEM_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UI/Constants.hpp"
#include "Titanium/Gradient.hpp"
#include "Titanium/Font.hpp"

namespace Titanium
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium ListItem Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.ListItem
		*/
		class TITANIUMKIT_EXPORT ListItem : public Module, public JSExport<ListItem>
		{

		public:

			/*!
			  @property
			  @abstract itemId
			  @discussion A user defined string that gets passed to events.
			*/
			virtual std::string get_itemId() const TITANIUM_NOEXCEPT;
			virtual void set_itemId(const std::string& itemId) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract backgroundColor
			  @discussion Background color of the view, as a color name or hex triplet.
			*/
			virtual std::string get_backgroundColor() const TITANIUM_NOEXCEPT;
			virtual void set_backgroundColor(const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract backgroundImage
			  @discussion Background image to render when the item is not selected.
			*/
			virtual std::string get_backgroundImage() const TITANIUM_NOEXCEPT;
			virtual void set_backgroundImage(const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract backgroundGradient
			  @discussion Background gradient to render when the item is not selected.
			*/
			virtual Titanium::Gradient get_backgroundGradient() const TITANIUM_NOEXCEPT;
			virtual void set_backgroundGradient(const Titanium::Gradient& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract selectedBackgroundColor
			  @discussion Background color of the view, as a color name or hex triplet when item is selected.
			*/
			virtual std::string get_selectedBackgroundColor() const TITANIUM_NOEXCEPT;
			virtual void set_selectedBackgroundColor(const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract selectedBackgroundImage
			  @discussion Background image to render when the item is selected.
			*/
			virtual std::string get_selectedBackgroundImage() const TITANIUM_NOEXCEPT;
			virtual void set_selectedBackgroundImage(const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract searchableText
			  @discussion The text to match against when the [ListView](Titanium.UI.ListView) is performing a search.
			*/
			virtual std::string get_searchableText() const TITANIUM_NOEXCEPT;
			virtual void set_searchableText(const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract color
			  @discussion Default text color of the item when not selected, as a color name or hex triplet.
			*/
			virtual std::string get_color() const TITANIUM_NOEXCEPT;
			virtual void set_color(const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract font
			  @discussion Font to use for the item title.
			*/
			virtual Titanium::Font get_font() const TITANIUM_NOEXCEPT;
			virtual void set_font(const Titanium::Font& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract height
			  @discussion Row height in platform-specific units.
			*/
			virtual std::string get_height() const TITANIUM_NOEXCEPT;
			virtual void set_height(const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract image
			  @discussion Image to render in the image area of the item, specified as a local path or URL.
			*/
			virtual std::string get_image() const TITANIUM_NOEXCEPT;
			virtual void set_image(const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract title
			  @discussion Title to set in the text area of the item.
			*/
			virtual std::string get_title() const TITANIUM_NOEXCEPT;
			virtual void set_title(const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract subtitle
			  @discussion Subtitle to set in the text area of the item.
			*/
			virtual std::string get_subtitle() const TITANIUM_NOEXCEPT;
			virtual void set_subtitle(const std::string& value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract canEdit
			  @discussion Specifies if the item can be deleted by a user initiated action.
			*/
			virtual bool get_canEdit() const TITANIUM_NOEXCEPT;
			virtual void set_canEdit(bool value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract canMove
			  @discussion Specifies if the item can be reordered within the list view by a user initiated action.
			*/
			virtual bool get_canMove() const TITANIUM_NOEXCEPT;
			virtual void set_canMove(bool value) TITANIUM_NOEXCEPT;

			/*!
			  @property
			  @abstract accessoryType
			  @discussion Sets an accessory on the right side of an item.
			*/
			virtual Titanium::UI::LIST_ACCESSORY_TYPE get_accessoryType() const TITANIUM_NOEXCEPT;
			virtual void set_accessoryType(const Titanium::UI::LIST_ACCESSORY_TYPE& value) TITANIUM_NOEXCEPT;

			ListItem(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~ListItem() = default;
			ListItem(const ListItem&) = default;
			ListItem& operator=(const ListItem&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ListItem(ListItem&&)                 = default;
			ListItem& operator=(ListItem&&)      = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_get_itemId() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_itemId(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_backgroundColor() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_backgroundColor(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_backgroundImage() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_backgroundImage(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_backgroundGradient() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_backgroundGradient(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_selectedBackgroundColor() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_selectedBackgroundColor(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_selectedBackgroundImage() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_selectedBackgroundImage(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_searchableText() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_searchableText(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_color() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_color(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_font() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_font(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_height() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_height(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_image() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_image(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_title() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_title(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_subtitle() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_subtitle(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_accessoryType() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_accessoryType(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_canEdit() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_canEdit(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_canMove() const TITANIUM_NOEXCEPT final;
			virtual bool    js_set_canMove(const JSValue& argument) TITANIUM_NOEXCEPT final;

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string itemId__;
			std::string backgroundColor__;
			std::string backgroundImage__;
			std::string selectedBackgroundColor__;
			std::string selectedBackgroundImage__;
			std::string searchableText__;
			std::string color__;
			Gradient backgroundGradient__;
			Font font__;
			std::string height__;
			std::string image__;
			std::string title__;
			std::string subtitle__;
			LIST_ACCESSORY_TYPE accessoryType__;
			bool canEdit__ { false };
			bool canMove__ { false };
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_LISTITEM_HPP_