/**
 * TitaniumKit Titanium.UI.ListItem
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ListItem.hpp"

namespace Titanium
{
	namespace UI
	{


		ListItem::ListItem(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Module(js_context, arguments),
			itemId__(""),
			backgroundColor__(""),
			backgroundImage__(""),
			selectedBackgroundColor__(""),
			selectedBackgroundImage__(""),
			searchableText__(""),
			color__(""),
			image__(""),
			title__(""),
			accessoryType__(Titanium::UI::LIST_ACCESSORY_TYPE::NONE)
		{
		}

		std::string ListItem::get_itemId() const TITANIUM_NOEXCEPT
		{
			return itemId__;
		}

		void ListItem::set_itemId(const std::string& value) TITANIUM_NOEXCEPT
		{
			itemId__ = value;
		}

		std::string ListItem::get_backgroundColor() const TITANIUM_NOEXCEPT
		{
			return backgroundColor__;
		}

		void ListItem::set_backgroundColor(const std::string& value) TITANIUM_NOEXCEPT
		{
			backgroundColor__ = value;
		}

		std::string ListItem::get_backgroundImage() const TITANIUM_NOEXCEPT
		{
			return backgroundImage__;
		}

		void ListItem::set_backgroundImage(const std::string& value) TITANIUM_NOEXCEPT
		{
			backgroundImage__ = value;
		}

		Titanium::Gradient ListItem::get_backgroundGradient() const TITANIUM_NOEXCEPT
		{
			return backgroundGradient__;
		}

		void ListItem::set_backgroundGradient(const Titanium::Gradient& value) TITANIUM_NOEXCEPT
		{
			backgroundGradient__ = value;
		}

		std::string ListItem::get_selectedBackgroundColor() const TITANIUM_NOEXCEPT
		{
			return selectedBackgroundColor__;
		}

		void ListItem::set_selectedBackgroundColor(const std::string& value) TITANIUM_NOEXCEPT
		{
			selectedBackgroundColor__ = value;
		}

		std::string ListItem::get_selectedBackgroundImage() const TITANIUM_NOEXCEPT
		{
			return selectedBackgroundImage__;
		}

		void ListItem::set_selectedBackgroundImage(const std::string& value) TITANIUM_NOEXCEPT
		{
			selectedBackgroundImage__ = value;
		}

		std::string ListItem::get_searchableText() const TITANIUM_NOEXCEPT
		{
			return searchableText__;
		}

		void ListItem::set_searchableText(const std::string& value) TITANIUM_NOEXCEPT
		{
			searchableText__ = value;
		}

		std::string ListItem::get_color() const TITANIUM_NOEXCEPT
		{
			return color__;
		}

		void ListItem::set_color(const std::string& value) TITANIUM_NOEXCEPT
		{
			color__ = value;
		}

		Titanium::Font ListItem::get_font() const TITANIUM_NOEXCEPT
		{
			return font__;
		}

		void ListItem::set_font(const Titanium::Font& value) TITANIUM_NOEXCEPT
		{
			font__ = value;
		}

		std::string ListItem::get_height() const TITANIUM_NOEXCEPT
		{
			return height__;
		}

		void ListItem::set_height(const std::string& value) TITANIUM_NOEXCEPT
		{
			height__ = value;
		}

		std::string ListItem::get_image() const TITANIUM_NOEXCEPT
		{
			return image__;
		}

		void ListItem::set_image(const std::string& value) TITANIUM_NOEXCEPT
		{
			image__ = value;
		}

		std::string ListItem::get_title() const TITANIUM_NOEXCEPT
		{
			return title__;
		}

		void ListItem::set_title(const std::string& value) TITANIUM_NOEXCEPT
		{
			title__ = value;
		}

		std::string ListItem::get_subtitle() const TITANIUM_NOEXCEPT
		{
			return subtitle__;
		}

		void ListItem::set_subtitle(const std::string& value) TITANIUM_NOEXCEPT
		{
			subtitle__ = value;
		}

		bool ListItem::get_canEdit() const TITANIUM_NOEXCEPT
		{
			return canEdit__;
		}

		void ListItem::set_canEdit(bool value) TITANIUM_NOEXCEPT
		{
			canEdit__ = value;
		}

		bool ListItem::get_canMove() const TITANIUM_NOEXCEPT
		{
			return canMove__;
		}

		void ListItem::set_canMove(bool value) TITANIUM_NOEXCEPT
		{
			canMove__ = value;
		}

		LIST_ACCESSORY_TYPE ListItem::get_accessoryType() const TITANIUM_NOEXCEPT
		{
			return accessoryType__;
		}

		void ListItem::set_accessoryType(const LIST_ACCESSORY_TYPE& value) TITANIUM_NOEXCEPT
		{
			accessoryType__ = value;
		}

		void ListItem::JSExportInitialize() {
			JSExport<ListItem>::SetClassVersion(1);
			JSExport<ListItem>::SetParent(JSExport<Module>::Class());

			JSExport<ListItem>::AddValueProperty("itemId", std::mem_fn(&ListItem::js_get_itemId), std::mem_fn(&ListItem::js_set_itemId));
			JSExport<ListItem>::AddValueProperty("backgroundColor", std::mem_fn(&ListItem::js_get_backgroundColor), std::mem_fn(&ListItem::js_set_backgroundColor));
			JSExport<ListItem>::AddValueProperty("backgroundImage", std::mem_fn(&ListItem::js_get_backgroundImage), std::mem_fn(&ListItem::js_set_backgroundImage));
			JSExport<ListItem>::AddValueProperty("backgroundGradient", std::mem_fn(&ListItem::js_get_backgroundGradient), std::mem_fn(&ListItem::js_set_backgroundGradient));
			JSExport<ListItem>::AddValueProperty("selectedBackgroundColor", std::mem_fn(&ListItem::js_get_selectedBackgroundColor), std::mem_fn(&ListItem::js_set_selectedBackgroundColor));
			JSExport<ListItem>::AddValueProperty("selectedBackgroundImage", std::mem_fn(&ListItem::js_get_selectedBackgroundImage), std::mem_fn(&ListItem::js_set_selectedBackgroundImage));
			JSExport<ListItem>::AddValueProperty("searchableText", std::mem_fn(&ListItem::js_get_searchableText), std::mem_fn(&ListItem::js_set_searchableText));
			JSExport<ListItem>::AddValueProperty("color", std::mem_fn(&ListItem::js_get_color), std::mem_fn(&ListItem::js_set_color));
			JSExport<ListItem>::AddValueProperty("font", std::mem_fn(&ListItem::js_get_font),   std::mem_fn(&ListItem::js_set_font));
			JSExport<ListItem>::AddValueProperty("height", std::mem_fn(&ListItem::js_get_height), std::mem_fn(&ListItem::js_set_height));
			JSExport<ListItem>::AddValueProperty("image", std::mem_fn(&ListItem::js_get_image), std::mem_fn(&ListItem::js_set_image));
			JSExport<ListItem>::AddValueProperty("title", std::mem_fn(&ListItem::js_get_title), std::mem_fn(&ListItem::js_set_title));
			JSExport<ListItem>::AddValueProperty("subtitle", std::mem_fn(&ListItem::js_get_subtitle), std::mem_fn(&ListItem::js_set_subtitle));
			JSExport<ListItem>::AddValueProperty("accessoryType", std::mem_fn(&ListItem::js_get_accessoryType), std::mem_fn(&ListItem::js_set_accessoryType));
			JSExport<ListItem>::AddValueProperty("canEdit", std::mem_fn(&ListItem::js_get_canEdit), std::mem_fn(&ListItem::js_set_canEdit));
			JSExport<ListItem>::AddValueProperty("canMove", std::mem_fn(&ListItem::js_get_canMove), std::mem_fn(&ListItem::js_set_canMove));
		}

		JSValue ListItem::js_get_itemId() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_itemId());
		}

		bool ListItem::js_set_itemId(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsString());
			set_itemId(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListItem::js_get_backgroundColor() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_backgroundColor());
		}

		bool ListItem::js_set_backgroundColor(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsString());
			set_backgroundColor(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListItem::js_get_backgroundImage() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_backgroundImage());
		}

		bool ListItem::js_set_backgroundImage(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			set_backgroundImage(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListItem::js_get_backgroundGradient() const TITANIUM_NOEXCEPT
		{
			return Titanium::Gradient_to_js(get_context(), get_backgroundGradient());
		}

		bool ListItem::js_set_backgroundGradient(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			if(!argument.IsObject()) {
				return false;
			}
			set_backgroundGradient(js_to_Gradient(static_cast<JSObject>(argument)));
			return true;
		}

		JSValue ListItem::js_get_selectedBackgroundColor() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_selectedBackgroundColor());
		}

		bool ListItem::js_set_selectedBackgroundColor(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsString());
			set_selectedBackgroundColor(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListItem::js_get_selectedBackgroundImage() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_selectedBackgroundImage());
		}

		bool ListItem::js_set_selectedBackgroundImage(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsString());
			set_selectedBackgroundImage(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListItem::js_get_searchableText() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_searchableText());
		}

		bool ListItem::js_set_searchableText(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsString());
			set_searchableText(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListItem::js_get_color() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_color());
		}

		bool ListItem::js_set_color(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsString());
			set_color(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListItem::js_get_font() const TITANIUM_NOEXCEPT
		{
			return Titanium::Font_to_js(get_context(), get_font());
		}

		bool ListItem::js_set_font(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			if(!argument.IsObject()) {
				return false;
			}
			set_font(js_to_Font(static_cast<JSObject>(argument)));
			return true;
		}

		JSValue ListItem::js_get_height() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_height());
		}

		bool ListItem::js_set_height(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsString());
			set_height(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListItem::js_get_image() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_image());
		}

		bool ListItem::js_set_image(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsString());
			set_image(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListItem::js_get_title() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_title());
		}

		bool ListItem::js_set_title(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsString());
			set_title(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListItem::js_get_subtitle() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(get_subtitle());
		}

		bool ListItem::js_set_subtitle(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsString());
			set_subtitle(static_cast<std::string>(argument));
			return true;
		}

		JSValue ListItem::js_get_accessoryType() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<std::underlying_type<LIST_ACCESSORY_TYPE>::type>(get_accessoryType()));
		}

		bool ListItem::js_set_accessoryType(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_accessoryType(Constants::to_LIST_ACCESSORY_TYPE(static_cast<std::underlying_type<LIST_ACCESSORY_TYPE>::type>(argument)));
			return true;
		}

		JSValue ListItem::js_get_canEdit() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_canEdit());
		}

		bool ListItem::js_set_canEdit(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_canEdit(static_cast<bool>(argument));
			return true;
		}

		JSValue ListItem::js_get_canMove() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(get_canMove());
		}

		bool ListItem::js_set_canMove(const JSValue& argument) TITANIUM_NOEXCEPT 
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_canMove(static_cast<bool>(argument));
			return true;
		}

	} // namespace UI
} // namespace Titanium