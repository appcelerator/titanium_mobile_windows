/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UIModule.hpp"
#include "Titanium/UI/Constants.hpp"
#include "Titanium/UI/Tab.hpp"
#include "Titanium/UI/Window.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UI/NavigationWindow.hpp"
#include <sstream>

#define CREATE_TITANIUM_UI(NAME) \
  static auto NAME##_ctor = this_object; \
  static std::once_flag of; \
  std::call_once(of, [=] {\
  JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue UI_property = Titanium.GetProperty("UI"); \
  TITANIUM_ASSERT(UI_property.IsObject()); \
  JSObject UI = static_cast<JSObject>(UI_property); \
  JSValue NAME##_property = UI.GetProperty(#NAME); \
  TITANIUM_ASSERT(NAME##_property.IsObject()); \
  NAME##_ctor = static_cast<JSObject>(NAME##_property); \
  });  \
  auto NAME##_obj = NAME##_ctor.CallAsConstructor(); \
  Titanium::Module::applyProperties(parameters, NAME##_obj); \
  return NAME##_obj;

namespace Titanium
{

	UIModule::UIModule(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context, "Ti.UI")
		, navigationWindow__(JSExport<Titanium::UI::NavigationWindow>::Class())
	{
		TITANIUM_LOG_DEBUG("UIModule:: ctor ", this);
	}

	UIModule::~UIModule() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UIModule:: dtor ", this);
	}

	TITANIUM_PROPERTY_READWRITE(UIModule, std::string, backgroundColor);
	TITANIUM_PROPERTY_READWRITE(UIModule, std::string, backgroundImage);
	TITANIUM_PROPERTY_READWRITE(UIModule, std::shared_ptr<Titanium::UI::Tab>, currentTab);
	TITANIUM_PROPERTY_READWRITE(UIModule, std::shared_ptr<Titanium::UI::Window>, currentWindow);

	TITANIUM_PROPERTY_GETTER(UIModule, ANIMATION_CURVE_EASE_IN)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ANIMATION_CURVE::EASE_IN));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ANIMATION_CURVE_EASE_IN_OUT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ANIMATION_CURVE::EASE_IN_OUT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ANIMATION_CURVE_EASE_OUT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ANIMATION_CURVE::EASE_OUT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ANIMATION_CURVE_LINEAR)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ANIMATION_CURVE::LINEAR));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_ALL)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::ALL));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_CALENDAR)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::CALENDAR));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_EMAIL_ADDRESSES)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::EMAIL_ADDRESSES));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_MAP_ADDRESSES)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::MAP_ADDRESSES));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_NONE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::NONE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_PHONE_NUMBERS)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::PHONE_NUMBERS));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_URLS)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::URLS));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, EXTEND_EDGE_ALL)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::EXTEND_EDGE::ALL));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, EXTEND_EDGE_BOTTOM)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::EXTEND_EDGE::BOTTOM));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, EXTEND_EDGE_LEFT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::EXTEND_EDGE::LEFT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, EXTEND_EDGE_NONE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::EXTEND_EDGE::NONE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, EXTEND_EDGE_RIGHT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::EXTEND_EDGE::RIGHT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, EXTEND_EDGE_TOP)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::EXTEND_EDGE::TOP));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, FACE_DOWN)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::FACE_DOWN));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, FACE_UP)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::FACE_UP));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, FILL)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INHERIT)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::INHERIT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BORDERSTYLE_BEZEL)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BORDERSTYLE::BEZEL));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BORDERSTYLE_LINE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BORDERSTYLE::LINE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BORDERSTYLE_NONE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BORDERSTYLE::NONE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BORDERSTYLE_ROUNDED)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BORDERSTYLE::ROUNDED));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BUTTONMODE_ALWAYS)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BUTTONMODE::ALWAYS));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BUTTONMODE_NEVER)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BUTTONMODE::NEVER));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BUTTONMODE_ONBLUR)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BUTTONMODE::ONBLUR));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BUTTONMODE_ONFOCUS)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BUTTONMODE::ONFOCUS));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_APPEARANCE_DEFAULT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD_APPEARANCE::DEFAULT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_TYPE_ASCII)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::ASCII));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_TYPE_DECIMAL_PAD)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::DECIMAL_PAD));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_TYPE_DEFAULT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::DEFAULT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_TYPE_EMAIL)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::EMAIL));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_TYPE_NAMEPHONE_PAD)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::NAMEPHONE_PAD));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_TYPE_NUMBERS_PUNCTUATION)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::NUMBERS_PUNCTUATION));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_TYPE_NUMBER_PAD)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::NUMBER_PAD));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_TYPE_PHONE_PAD)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::PHONE_PAD));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_TYPE_URL)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::URL));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LANDSCAPE_LEFT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::LANDSCAPE_LEFT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LANDSCAPE_RIGHT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::LANDSCAPE_RIGHT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ACCESSORY_TYPE_CHECKMARK)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ACCESSORY_TYPE::CHECKMARK));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ACCESSORY_TYPE_DETAIL)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ACCESSORY_TYPE::DETAIL));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ACCESSORY_TYPE_DISCLOSURE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ACCESSORY_TYPE::DISCLOSURE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ACCESSORY_TYPE_NONE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ACCESSORY_TYPE::NONE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ITEM_TEMPLATE_CONTACTS)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ITEM_TEMPLATE::CONTACTS));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ITEM_TEMPLATE_DEFAULT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ITEM_TEMPLATE::DEFAULT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ITEM_TEMPLATE_SETTINGS)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ITEM_TEMPLATE::SETTINGS));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ITEM_TEMPLATE_SUBTITLE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ITEM_TEMPLATE::SUBTITLE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, NOTIFICATION_DURATION_LONG)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::NOTIFICATION_DURATION::LONG));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, NOTIFICATION_DURATION_SHORT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::NOTIFICATION_DURATION::SHORT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, PICKER_TYPE_COUNT_DOWN_TIMER)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::PICKER_TYPE::COUNT_DOWN_TIMER));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, PICKER_TYPE_DATE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::PICKER_TYPE::DATE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, PICKER_TYPE_DATE_AND_TIME)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::PICKER_TYPE::DATE_AND_TIME));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, PICKER_TYPE_PLAIN)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::PICKER_TYPE::PLAIN));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, PICKER_TYPE_TIME)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::PICKER_TYPE::TIME));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, PORTRAIT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::PORTRAIT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_DEFAULT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::DEFAULT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_DONE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::DONE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_EMERGENCY_CALL)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::EMERGENCY_CALL));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_GO)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::GO));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_GOOGLE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::GOOGLE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_JOIN)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::JOIN));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_NEXT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::NEXT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_ROUTE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::ROUTE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_SEARCH)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::SEARCH));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_SEND)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::SEND));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_YAHOO)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::YAHOO));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, SIZE)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ALIGNMENT_CENTER)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ALIGNMENT::CENTER));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ALIGNMENT_LEFT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ALIGNMENT::LEFT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ALIGNMENT_RIGHT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ALIGNMENT::RIGHT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ALIGNMENT_JUSTIFY)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ALIGNMENT::JUSTIFY));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_AUTOCAPITALIZATION_ALL)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_AUTOCAPITALIZATION::ALL));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_AUTOCAPITALIZATION_NONE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_AUTOCAPITALIZATION::NONE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_AUTOCAPITALIZATION_SENTENCES)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_AUTOCAPITALIZATION::SENTENCES));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_AUTOCAPITALIZATION_WORDS)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_AUTOCAPITALIZATION::WORDS));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ELLIPSIZE_TRUNCATE_NONE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ELLIPSIZE_TRUNCATE::NONE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ELLIPSIZE_TRUNCATE_CHAR_WRAP)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ELLIPSIZE_TRUNCATE::CHAR_WRAP));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ELLIPSIZE_TRUNCATE_WORD_WRAP)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ELLIPSIZE_TRUNCATE::WORD_WRAP));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ELLIPSIZE_TRUNCATE_CLIP)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ELLIPSIZE_TRUNCATE::CLIP));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ELLIPSIZE_TRUNCATE_START)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ELLIPSIZE_TRUNCATE::START));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ELLIPSIZE_TRUNCATE_MIDDLE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ELLIPSIZE_TRUNCATE::MIDDLE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ELLIPSIZE_TRUNCATE_END)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ELLIPSIZE_TRUNCATE::END));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ELLIPSIZE_TRUNCATE_MARQUEE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ELLIPSIZE_TRUNCATE::MARQUEE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_STYLE_BODY)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::TEXT_STYLE::BODY));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_STYLE_CAPTION1)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::TEXT_STYLE::CAPTION1));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_STYLE_CAPTION2)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::TEXT_STYLE::CAPTION2));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_STYLE_FOOTNOTE)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::TEXT_STYLE::FOOTNOTE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_STYLE_HEADLINE)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::TEXT_STYLE::HEADLINE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_STYLE_SUBHEADLINE)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::TEXT_STYLE::SUBHEADLINE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_VERTICAL_ALIGNMENT_BOTTOM)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_VERTICAL_ALIGNMENT::BOTTOM));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_VERTICAL_ALIGNMENT_CENTER)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_VERTICAL_ALIGNMENT::CENTER));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_VERTICAL_ALIGNMENT_TOP)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_VERTICAL_ALIGNMENT::TOP));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNIT_CM)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::UNIT::Cm));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNIT_DIP)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::UNIT::Dip));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNIT_IN)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::UNIT::In));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNIT_MM)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::UNIT::Mm));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNIT_PX)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::UNIT::Px));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNIT_PPX)
	{
		return get_context().CreateString(Titanium::UI::Constants::to_string(Titanium::UI::UNIT::Ppx));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNKNOWN)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::UNKNOWN));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UPSIDE_PORTRAIT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::UPSIDE_PORTRAIT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_AUTHENTICATION)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::AUTHENTICATION));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_BAD_URL)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::BAD_URL));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_CONNECT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::CONNECT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_FILE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::FILE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_FILE_NOT_FOUND)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::FILE_NOT_FOUND));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_HOST_LOOKUP)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::HOST_LOOKUP));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_REDIRECT_LOOP)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::REDIRECT_LOOP));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_SSL_FAILED)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::SSL_FAILED));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_TIMEOUT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::TIMEOUT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_UNKNOWN)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::UNKNOWN));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_UNSUPPORTED_SCHEME)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::UNSUPPORTED_SCHEME));
	}

	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_FONT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::FONT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_FOREGROUND_COLOR)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::FOREGROUND_COLOR));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_BACKGROUND_COLOR)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::BACKGROUND_COLOR));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_STRIKETHROUGH_STYLE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::STRIKETHROUGH_STYLE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_UNDERLINES_STYLE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::UNDERLINES_STYLE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_LINK)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::LINK));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_UNDERLINE_COLOR)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::UNDERLINE_COLOR));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_KERN)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::KERN));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_STROKE_COLOR)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::STROKE_COLOR));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_STROKE_WIDTH)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::STROKE_WIDTH));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_SHADOW)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::SHADOW));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_WRITING_DIRECTION)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::WRITING_DIRECTION));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_TEXT_EFFECT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::TEXT_EFFECT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_BASELINE_OFFSET)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::BASELINE_OFFSET));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_STRIKETHROUGH_COLOR)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::STRIKETHROUGH_COLOR));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_OBLIQUENESS)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::OBLIQUENESS));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_EXPANSION)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::EXPANSION));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_LINE_BREAK)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_TYPE::LINE_BREAK));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_UNDERLINE_STYLE_NONE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_NONE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_UNDERLINE_STYLE_SINGLE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_SINGLE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_UNDERLINE_STYLE_THICK)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_THICK));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_UNDERLINE_STYLE_DOUBLE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_DOUBLE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_UNDERLINE_PATTERN_SOLID)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_PATTERN_SOLID));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_UNDERLINE_PATTERN_DOT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DOT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_UNDERLINE_PATTERN_DASH)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_UNDERLINE_PATTERN_DASH_DOT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH_DOT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_UNDERLINE_PATTERN_DASH_DOT_DOT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH_DOT_DOT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_UNDERLINE_BY_WORD)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::UNDERLINE_BY_WORD));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_WRITING_DIRECTION_EMBEDDING)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::WRITING_DIRECTION_EMBEDDING));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_WRITING_DIRECTION_OVERRIDE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::WRITING_DIRECTION_OVERRIDE));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_WRITING_DIRECTION_NATURAL)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::WRITING_DIRECTION_NATURAL));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_WRITING_DIRECTION_LEFT_TO_RIGHT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::WRITING_DIRECTION_LEFT_TO_RIGHT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_WRITING_DIRECTION_RIGHT_TO_LEFT)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::WRITING_DIRECTION_RIGHT_TO_LEFT));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_LETTERPRESS_STYLE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::TEXT_EFFECT_LETTERPRESS));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_LINE_BREAK_BY_WORD_WRAPPING)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::LINE_BREAK_BY_WORD_WRAPPING));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_LINE_BREAK_BY_CHAR_WRAPPING)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::LINE_BREAK_BY_CHAR_WRAPPING));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_LINE_BREAK_BY_CLIPPING)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::LINE_BREAK_BY_CLIPPING));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_LINE_BREAK_BY_TRUNCATING_HEAD)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_HEAD));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_LINE_BREAK_BY_TRUNCATING_TAIL)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_TAIL));
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ATTRIBUTE_LINE_BREAK_BY_TRUNCATING_MIDDLE)
	{
		return get_context().CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_MIDDLE));
	}

	void UIModule::JSExportInitialize()
	{
		JSExport<UIModule>::SetClassVersion(1);
		JSExport<UIModule>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_FUNCTION(UIModule, convertUnits);
		TITANIUM_ADD_FUNCTION(UIModule, create2DMatrix);
		TITANIUM_ADD_FUNCTION(UIModule, create3DMatrix);
		TITANIUM_ADD_FUNCTION(UIModule, createMatrix2D);
		TITANIUM_ADD_FUNCTION(UIModule, createMatrix3D);
		TITANIUM_ADD_FUNCTION(UIModule, createActivityIndicator);
		TITANIUM_ADD_FUNCTION(UIModule, createAnimation);
		TITANIUM_ADD_FUNCTION(UIModule, createAlertDialog);
		TITANIUM_ADD_FUNCTION(UIModule, createAttributedString);
		TITANIUM_ADD_FUNCTION(UIModule, createButton);
		TITANIUM_ADD_FUNCTION(UIModule, createEmailDialog);
		TITANIUM_ADD_FUNCTION(UIModule, createImageView);
		TITANIUM_ADD_FUNCTION(UIModule, createLabel);
		TITANIUM_ADD_FUNCTION(UIModule, createListItem);
		TITANIUM_ADD_FUNCTION(UIModule, createListSection);
		TITANIUM_ADD_FUNCTION(UIModule, createListView);
		TITANIUM_ADD_FUNCTION(UIModule, createNavigationWindow);
		TITANIUM_ADD_FUNCTION(UIModule, createNotification);
		TITANIUM_ADD_FUNCTION(UIModule, createOptionDialog);
		TITANIUM_ADD_FUNCTION(UIModule, createPicker);
		TITANIUM_ADD_FUNCTION(UIModule, createPickerRow);
		TITANIUM_ADD_FUNCTION(UIModule, createPickerColumn);
		TITANIUM_ADD_FUNCTION(UIModule, createProgressBar);
		TITANIUM_ADD_FUNCTION(UIModule, createScrollableView);
		TITANIUM_ADD_FUNCTION(UIModule, createScrollView);
		TITANIUM_ADD_FUNCTION(UIModule, createSearchBar);
		TITANIUM_ADD_FUNCTION(UIModule, createSlider);
		TITANIUM_ADD_FUNCTION(UIModule, createSwitch);
		TITANIUM_ADD_FUNCTION(UIModule, createTab);
		TITANIUM_ADD_FUNCTION(UIModule, createTabGroup);
		TITANIUM_ADD_FUNCTION(UIModule, createTextArea);
		TITANIUM_ADD_FUNCTION(UIModule, createTextField);
		TITANIUM_ADD_FUNCTION(UIModule, createTableView);
		TITANIUM_ADD_FUNCTION(UIModule, createTableViewRow);
		TITANIUM_ADD_FUNCTION(UIModule, createTableViewSection);
		TITANIUM_ADD_FUNCTION(UIModule, createView);
		TITANIUM_ADD_FUNCTION(UIModule, createWebView);
		TITANIUM_ADD_FUNCTION(UIModule, createWindow);

		TITANIUM_ADD_FUNCTION(UIModule, getBackgroundColor);
		TITANIUM_ADD_FUNCTION(UIModule, setBackgroundColor);
		TITANIUM_ADD_FUNCTION(UIModule, getBackgroundImage);
		TITANIUM_ADD_FUNCTION(UIModule, setBackgroundImage);
		TITANIUM_ADD_PROPERTY(UIModule, currentTab);
		TITANIUM_ADD_FUNCTION(UIModule, getCurrentTab);
		TITANIUM_ADD_FUNCTION(UIModule, setCurrentTab);

		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ANIMATION_CURVE_EASE_IN);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ANIMATION_CURVE_EASE_IN_OUT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ANIMATION_CURVE_EASE_OUT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ANIMATION_CURVE_LINEAR);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, AUTOLINK_ALL);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, AUTOLINK_CALENDAR);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, AUTOLINK_EMAIL_ADDRESSES);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, AUTOLINK_MAP_ADDRESSES);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, AUTOLINK_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, AUTOLINK_PHONE_NUMBERS);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, AUTOLINK_URLS);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, EXTEND_EDGE_ALL);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, EXTEND_EDGE_BOTTOM);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, EXTEND_EDGE_LEFT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, EXTEND_EDGE_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, EXTEND_EDGE_RIGHT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, EXTEND_EDGE_TOP);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, FACE_DOWN);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, FACE_UP);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, FILL);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, INHERIT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, INPUT_BORDERSTYLE_BEZEL);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, INPUT_BORDERSTYLE_LINE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, INPUT_BORDERSTYLE_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, INPUT_BORDERSTYLE_ROUNDED);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, INPUT_BUTTONMODE_ALWAYS);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, INPUT_BUTTONMODE_NEVER);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, INPUT_BUTTONMODE_ONBLUR);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, INPUT_BUTTONMODE_ONFOCUS);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, KEYBOARD_APPEARANCE_DEFAULT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, KEYBOARD_TYPE_ASCII);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, KEYBOARD_TYPE_DECIMAL_PAD);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, KEYBOARD_TYPE_DEFAULT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, KEYBOARD_TYPE_EMAIL);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, KEYBOARD_TYPE_NAMEPHONE_PAD);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, KEYBOARD_TYPE_NUMBERS_PUNCTUATION);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, KEYBOARD_TYPE_NUMBER_PAD);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, KEYBOARD_TYPE_PHONE_PAD);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, KEYBOARD_TYPE_URL);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, LANDSCAPE_LEFT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, LANDSCAPE_RIGHT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, LIST_ACCESSORY_TYPE_CHECKMARK);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, LIST_ACCESSORY_TYPE_DETAIL);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, LIST_ACCESSORY_TYPE_DISCLOSURE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, LIST_ACCESSORY_TYPE_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, LIST_ITEM_TEMPLATE_CONTACTS);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, LIST_ITEM_TEMPLATE_DEFAULT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, LIST_ITEM_TEMPLATE_SETTINGS);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, LIST_ITEM_TEMPLATE_SUBTITLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, NOTIFICATION_DURATION_LONG);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, NOTIFICATION_DURATION_SHORT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, PICKER_TYPE_COUNT_DOWN_TIMER);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, PICKER_TYPE_DATE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, PICKER_TYPE_DATE_AND_TIME);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, PICKER_TYPE_PLAIN);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, PICKER_TYPE_TIME);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, PORTRAIT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, RETURNKEY_DEFAULT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, RETURNKEY_DONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, RETURNKEY_EMERGENCY_CALL);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, RETURNKEY_GO);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, RETURNKEY_GOOGLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, RETURNKEY_JOIN);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, RETURNKEY_NEXT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, RETURNKEY_ROUTE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, RETURNKEY_SEARCH);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, RETURNKEY_SEND);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, RETURNKEY_YAHOO);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, SIZE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_ALIGNMENT_CENTER);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_ALIGNMENT_LEFT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_ALIGNMENT_RIGHT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_ALIGNMENT_JUSTIFY);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_AUTOCAPITALIZATION_ALL);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_AUTOCAPITALIZATION_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_AUTOCAPITALIZATION_SENTENCES);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_AUTOCAPITALIZATION_WORDS);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_ELLIPSIZE_TRUNCATE_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_ELLIPSIZE_TRUNCATE_CHAR_WRAP);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_ELLIPSIZE_TRUNCATE_WORD_WRAP);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_ELLIPSIZE_TRUNCATE_CLIP);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_ELLIPSIZE_TRUNCATE_START);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_ELLIPSIZE_TRUNCATE_MIDDLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_ELLIPSIZE_TRUNCATE_END);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_ELLIPSIZE_TRUNCATE_MARQUEE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_STYLE_BODY);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_STYLE_CAPTION1);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_STYLE_CAPTION2);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_STYLE_FOOTNOTE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_STYLE_HEADLINE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_STYLE_SUBHEADLINE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_VERTICAL_ALIGNMENT_BOTTOM);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_VERTICAL_ALIGNMENT_CENTER);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TEXT_VERTICAL_ALIGNMENT_TOP);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, UNIT_CM);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, UNIT_DIP);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, UNIT_IN);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, UNIT_MM);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, UNIT_PX);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, UNIT_PPX);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, UNKNOWN);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, UPSIDE_PORTRAIT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, URL_ERROR_AUTHENTICATION);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, URL_ERROR_BAD_URL);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, URL_ERROR_CONNECT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, URL_ERROR_FILE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, URL_ERROR_FILE_NOT_FOUND);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, URL_ERROR_HOST_LOOKUP);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, URL_ERROR_REDIRECT_LOOP);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, URL_ERROR_SSL_FAILED);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, URL_ERROR_TIMEOUT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, URL_ERROR_UNKNOWN);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, URL_ERROR_UNSUPPORTED_SCHEME);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_FONT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_FOREGROUND_COLOR);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_BACKGROUND_COLOR);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_STRIKETHROUGH_STYLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_UNDERLINES_STYLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_LINK);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_UNDERLINE_COLOR);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_KERN);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_STROKE_COLOR);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_STROKE_WIDTH);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_SHADOW);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_WRITING_DIRECTION);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_TEXT_EFFECT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_BASELINE_OFFSET);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_STRIKETHROUGH_COLOR);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_OBLIQUENESS);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_EXPANSION);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_LINE_BREAK);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_UNDERLINE_STYLE_NONE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_UNDERLINE_STYLE_SINGLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_UNDERLINE_STYLE_THICK);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_UNDERLINE_STYLE_DOUBLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_UNDERLINE_PATTERN_SOLID);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_UNDERLINE_PATTERN_DOT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_UNDERLINE_PATTERN_DASH);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_UNDERLINE_PATTERN_DASH_DOT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_UNDERLINE_PATTERN_DASH_DOT_DOT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_UNDERLINE_BY_WORD);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_WRITING_DIRECTION_EMBEDDING);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_WRITING_DIRECTION_OVERRIDE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_WRITING_DIRECTION_NATURAL);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_WRITING_DIRECTION_LEFT_TO_RIGHT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_WRITING_DIRECTION_RIGHT_TO_LEFT);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_LETTERPRESS_STYLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_LINE_BREAK_BY_WORD_WRAPPING);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_LINE_BREAK_BY_CHAR_WRAPPING);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_LINE_BREAK_BY_CLIPPING);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_LINE_BREAK_BY_TRUNCATING_HEAD);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_LINE_BREAK_BY_TRUNCATING_TAIL);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ATTRIBUTE_LINE_BREAK_BY_TRUNCATING_MIDDLE);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Matrix2D);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Matrix3D);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ActivityIndicator);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ActivityIndicatorStyle);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, AlertDialog);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Animation);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, AttributedString);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Button);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Clipboard);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, EmailDialog);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ImageView);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Label);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ListView);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ListSection);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, NavigationWindow);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Notification);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, OptionDialog);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ProgressBar);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Picker);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, PickerRow);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, PickerColumn);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ScrollableView);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, ScrollView);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, SearchBar);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Slider);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Switch);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Tab);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TabGroup);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TableView);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TableViewSection);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TableViewRow);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TextArea);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, TextField);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, View);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, WebView);
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Window);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Matrix2D)
	{
		return get_context().CreateObject(matrix2d__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Matrix3D)
	{
		return get_context().CreateObject(matrix3d__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, ActivityIndicator)
	{
		return get_context().CreateObject(activityIndicator__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, ActivityIndicatorStyle)
	{
		return get_context().CreateObject(activityIndicatorStyle__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, AlertDialog)
	{
		return get_context().CreateObject(alertDialog__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Animation)
	{
		return get_context().CreateObject(animation__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, AttributedString)
	{
		return get_context().CreateObject(attributedString__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Button)
	{
		return get_context().CreateObject(button__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Clipboard)
	{
		return get_context().CreateObject(clipboard__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, EmailDialog)
	{
		return get_context().CreateObject(emaildialog__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, ImageView)
	{
		return get_context().CreateObject(imageview__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Label)
	{
		return get_context().CreateObject(label__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, ListView)
	{
		return get_context().CreateObject(listview__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, ListSection)
	{
		return get_context().CreateObject(listsection__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, NavigationWindow)
	{
		return get_context().CreateObject(navigationWindow__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Notification)
	{
		return get_context().CreateObject(notification__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, OptionDialog)
	{
		return get_context().CreateObject(optionDialog__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, ProgressBar)
	{
		return get_context().CreateObject(progressBar__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Picker)
	{
		return get_context().CreateObject(picker__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, PickerRow)
	{
		return get_context().CreateObject(pickerrow__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, PickerColumn)
	{
		return get_context().CreateObject(pickercolumn__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, ScrollableView)
	{
		return get_context().CreateObject(scrollableView__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, ScrollView)
	{
		return get_context().CreateObject(scrollview__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, SearchBar)
	{
		return get_context().CreateObject(searchBar__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Slider)
	{
		return get_context().CreateObject(slider__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Switch)
	{
		return get_context().CreateObject(switch__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Tab)
	{
		return get_context().CreateObject(tab__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, TabGroup)
	{
		return get_context().CreateObject(tabgroup__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, TableView)
	{
		return get_context().CreateObject(tableview__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, TableViewSection)
	{
		return get_context().CreateObject(tableviewsection__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, TableViewRow)
	{
		return get_context().CreateObject(tableviewrow__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, TextArea)
	{
		return get_context().CreateObject(textarea__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, TextField)
	{
		return get_context().CreateObject(textField__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, View)
	{
		return get_context().CreateObject(view__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, WebView)
	{
		return get_context().CreateObject(webview__);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Window)
	{
		return get_context().CreateObject(window__);
	}

	TITANIUM_FUNCTION(UIModule, convertUnits)
	{
		ENSURE_STRING_AT_INDEX(convertFromValue, 0);
		ENSURE_STRING_AT_INDEX(units, 1);
		return get_context().CreateNumber(convertUnits(convertFromValue, Titanium::UI::Constants::to_UNIT(units)));
	}

	TITANIUM_FUNCTION(UIModule, create2DMatrix)
	{
		get_context().JSEvaluateScript("Ti.API.warn('Ti.UI.create2DMatrix DEPRECATED in 8.0.0, in favor of Ti.UI.createMatrix2D');");
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Matrix2D);
	}

	TITANIUM_FUNCTION(UIModule, create3DMatrix)
	{
		get_context().JSEvaluateScript("Ti.API.warn('Ti.UI.create3DMatrix DEPRECATED in 8.0.0, in favor of Ti.UI.createMatrix3D');");
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Matrix3D);
	}

	TITANIUM_FUNCTION(UIModule, createMatrix2D)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Matrix2D);
	}

	TITANIUM_FUNCTION(UIModule, createMatrix3D)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Matrix3D);
	}

	TITANIUM_FUNCTION(UIModule, createActivityIndicator)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(ActivityIndicator);
	}

	TITANIUM_FUNCTION(UIModule, createAlertDialog)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(AlertDialog);
	}

	TITANIUM_FUNCTION(UIModule, createAnimation)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Animation);
	}

	TITANIUM_FUNCTION(UIModule, createAttributedString)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(AttributedString);
	}

	TITANIUM_FUNCTION(UIModule, createButton)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Button);
	}

	TITANIUM_FUNCTION(UIModule, createEmailDialog)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(EmailDialog);
	}

	TITANIUM_FUNCTION(UIModule, createImageView)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(ImageView);
	}

	TITANIUM_FUNCTION(UIModule, createLabel)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Label);
	}

	TITANIUM_FUNCTION(UIModule, createListItem)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(ListItem);
	}

	TITANIUM_FUNCTION(UIModule, createListSection)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(ListSection);
	}

	TITANIUM_FUNCTION(UIModule, createListView)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(ListView);
	}

	TITANIUM_FUNCTION(UIModule, createNavigationWindow)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(NavigationWindow);
	}

	TITANIUM_FUNCTION(UIModule, createNotification)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Notification);
	}

	TITANIUM_FUNCTION(UIModule, createOptionDialog)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(OptionDialog);
	}

	TITANIUM_FUNCTION(UIModule, createPicker)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Picker);
	}

	TITANIUM_FUNCTION(UIModule, createPickerRow)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(PickerRow);
	}

	TITANIUM_FUNCTION(UIModule, createPickerColumn)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(PickerColumn);
	}

	TITANIUM_FUNCTION(UIModule, createProgressBar)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(ProgressBar);
	}

	TITANIUM_FUNCTION(UIModule, createScrollableView)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(ScrollableView);
	}

	TITANIUM_FUNCTION(UIModule, createScrollView)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(ScrollView);
	}

	TITANIUM_FUNCTION(UIModule, createSearchBar)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(SearchBar);
	}

	TITANIUM_FUNCTION(UIModule, createSlider)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Slider);
	}

	TITANIUM_FUNCTION(UIModule, createSwitch)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Switch);
	}

	TITANIUM_FUNCTION(UIModule, createTab)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Tab);
	}

	TITANIUM_FUNCTION(UIModule, createTabGroup)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(TabGroup);
	}

	TITANIUM_FUNCTION(UIModule, createTableViewRow)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(TableViewRow);
	}

	TITANIUM_FUNCTION(UIModule, createTableViewSection)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(TableViewSection);
	}

	TITANIUM_FUNCTION(UIModule, createTableView)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(TableView);
	}

	TITANIUM_FUNCTION(UIModule, createTextField)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(TextField);
	}

	TITANIUM_FUNCTION(UIModule, createView)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(View);
	}

	TITANIUM_FUNCTION(UIModule, createWindow)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(Window);
	}

	TITANIUM_FUNCTION(UIModule, createTextArea)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(TextArea);
	}

	TITANIUM_FUNCTION(UIModule, createWebView)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(WebView);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, backgroundImage)
	{
		return get_context().CreateString(get_backgroundImage());
	}

	TITANIUM_PROPERTY_SETTER(UIModule, backgroundImage)
	{
		TITANIUM_ASSERT(argument.IsString());
		set_backgroundImage(static_cast<std::string>(argument));
		return true;
	}

	TITANIUM_PROPERTY_GETTER(UIModule, backgroundColor)
	{
		return get_context().CreateString(get_backgroundColor());
	}

	TITANIUM_PROPERTY_SETTER(UIModule, backgroundColor)
	{
		TITANIUM_ASSERT(argument.IsString());
		set_backgroundColor(static_cast<std::string>(argument));
		return true;
	}

	TITANIUM_PROPERTY_GETTER(UIModule, currentTab)
	{
		const auto tab = get_currentTab();
		if (tab != nullptr) {
			return tab->get_object();
		}
		return get_context().CreateNull();
	}

	TITANIUM_PROPERTY_SETTER(UIModule, currentTab)
	{
		if (argument.IsObject()) {
			set_currentTab(static_cast<JSObject>(argument).GetPrivate<Titanium::UI::Tab>());
		} else {
			set_currentTab(nullptr);
		}
		return true;
	}

	TITANIUM_FUNCTION_AS_GETTER(UIModule, getBackgroundImage, backgroundImage)
	TITANIUM_FUNCTION_AS_SETTER(UIModule, setBackgroundImage, backgroundImage)
	TITANIUM_FUNCTION_AS_GETTER(UIModule, getBackgroundColor, backgroundColor)
	TITANIUM_FUNCTION_AS_SETTER(UIModule, setBackgroundColor, backgroundColor)
	TITANIUM_FUNCTION_AS_GETTER(UIModule, getCurrentTab, currentTab)
	TITANIUM_FUNCTION_AS_SETTER(UIModule, setCurrentTab, currentTab)

	UIModule& UIModule::ListViewClass(const JSClass& ListView) TITANIUM_NOEXCEPT
	{
		listview__ = ListView;
		return *this;
	}

	UIModule& UIModule::ListSectionClass(const JSClass& ListSection) TITANIUM_NOEXCEPT
	{
		listsection__ = ListSection;
		return *this;
	}

	UIModule& UIModule::EmailDialogClass(const JSClass& EmailDialog) TITANIUM_NOEXCEPT
	{
		emaildialog__ = EmailDialog;
		return *this;
	}

	UIModule& UIModule::AnimationClass(const JSClass& Animation) TITANIUM_NOEXCEPT
	{
		animation__ = Animation;
		return *this;
	}

	UIModule& UIModule::SwitchClass(const JSClass& Switch) TITANIUM_NOEXCEPT
	{
		switch__ = Switch;
		return *this;
	}

	UIModule& UIModule::Matrix2DClass(const JSClass& Matrix2D) TITANIUM_NOEXCEPT
	{
		matrix2d__ = Matrix2D;
		return *this;
	}

	UIModule& UIModule::Matrix3DClass(const JSClass& Matrix3D) TITANIUM_NOEXCEPT
	{
		matrix3d__ = Matrix3D;
		return *this;
	}

	UIModule& UIModule::NavigationWindowClass(const JSClass& NavigationWindow) TITANIUM_NOEXCEPT
	{
		navigationWindow__ = NavigationWindow;
		return *this;
	}

	UIModule& UIModule::NotificationClass(const JSClass& Notification) TITANIUM_NOEXCEPT
	{
		notification__ = Notification;
		return *this;
	}

	UIModule& UIModule::TextAreaClass(const JSClass& TextArea) TITANIUM_NOEXCEPT
	{
		textarea__ = TextArea;
		return *this;
	}

	UIModule& UIModule::ClipboardClass(const JSClass& Clipboard) TITANIUM_NOEXCEPT
	{
		clipboard__ = Clipboard;
		return *this;
	}

	UIModule& UIModule::ViewClass(const JSClass& View) TITANIUM_NOEXCEPT
	{
		view__ = View;
		return *this;
	}

	UIModule& UIModule::WindowClass(const JSClass& window) TITANIUM_NOEXCEPT
	{
		window__ = window;
		return *this;
	}

	UIModule& UIModule::ButtonClass(const JSClass& button) TITANIUM_NOEXCEPT
	{
		button__ = button;
		return *this;
	}

	UIModule& UIModule::SliderClass(const JSClass& slider) TITANIUM_NOEXCEPT
	{
		slider__ = slider;
		return *this;
	}

	UIModule& UIModule::AlertDialogClass(const JSClass& alertDialog) TITANIUM_NOEXCEPT
	{
		alertDialog__ = alertDialog;
		return *this;
	}

	UIModule& UIModule::ImageViewClass(const JSClass& imageview) TITANIUM_NOEXCEPT
	{
		imageview__ = imageview;
		return *this;
	}

	UIModule& UIModule::LabelClass(const JSClass& label) TITANIUM_NOEXCEPT
	{
		label__ = label;
		return *this;
	}

	UIModule& UIModule::ScrollViewClass(const JSClass& view) TITANIUM_NOEXCEPT
	{
		scrollview__ = view;
		return *this;
	}

	UIModule& UIModule::TextFieldClass(const JSClass& view) TITANIUM_NOEXCEPT
	{
		textField__ = view;
		return *this;
	}

	UIModule& UIModule::WebViewClass(const JSClass& webview) TITANIUM_NOEXCEPT
	{
		webview__ = webview;
		return *this;
	}

	UIModule& UIModule::Tab(const JSClass& view) TITANIUM_NOEXCEPT
	{
		tab__ = view;
		return *this;
	}

	UIModule& UIModule::TabGroup(const JSClass& view) TITANIUM_NOEXCEPT
	{
		tabgroup__ = view;
		return *this;
	}

	UIModule& UIModule::TableViewClass(const JSClass& TableView) TITANIUM_NOEXCEPT
	{
		tableview__ = TableView;
		return *this;
	}

	UIModule& UIModule::TableViewSectionClass(const JSClass& TableViewSection) TITANIUM_NOEXCEPT
	{
		tableviewsection__ = TableViewSection;
		return *this;
	}

	UIModule& UIModule::TableViewRowClass(const JSClass& TableViewRow) TITANIUM_NOEXCEPT
	{
		tableviewrow__ = TableViewRow;
		return *this;
	}

	UIModule& UIModule::ActivityIndicatorClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		activityIndicator__ = value;
		return *this;
	}

	UIModule& UIModule::ActivityIndicatorStyleClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		activityIndicatorStyle__ = value;
		return *this;
	}

	UIModule& UIModule::OptionDialogClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		optionDialog__ = value;
		return *this;
	}

	UIModule& UIModule::ProgressBarClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		progressBar__ = value;
		return *this;
	}

	UIModule& UIModule::PickerClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		picker__ = value;
		return *this;
	}

	UIModule& UIModule::PickerRowClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		pickerrow__ = value;
		return *this;
	}

	UIModule& UIModule::PickerColumnClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		pickercolumn__ = value;
		return *this;
	}

	UIModule& UIModule::ScrollableViewClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		scrollableView__ = value;
		return *this;
	}

	UIModule& UIModule::SearchBarClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		searchBar__ = value;
		return *this;
	}

	UIModule& UIModule::AttributedStringClass(const JSClass& value) TITANIUM_NOEXCEPT
	{
		attributedString__ = value;
		return *this;
	}

	double UIModule::convertUnits(const std::string& convertFromValue, const Titanium::UI::UNIT& convertToUnits) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Ti.UI.convertUnits is not implemented");
		return 0;
	}
}  // namespace Titanium
