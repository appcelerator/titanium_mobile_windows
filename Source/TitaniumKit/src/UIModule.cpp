/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UIModule.hpp"
#include <sstream>

namespace Titanium
{
	static void applyProperties(JSObject& view, const JSObject& parameters)
	{
		if (parameters.GetPropertyNames().GetCount() > 0) {
			const auto propertyNames = parameters.GetPropertyNames();
			for (const auto& property_name : static_cast<std::vector<JSString>>(propertyNames)) {
				view.SetProperty(property_name, parameters.GetProperty(property_name));
			}
		}
	}

	UIModule::UIModule(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Module(js_context),
	      animation_curve_ease_in__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ANIMATION_CURVE::EASE_IN))),
	      animation_curve_ease_in_out__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ANIMATION_CURVE::EASE_IN_OUT))),
	      animation_curve_ease_out__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ANIMATION_CURVE::EASE_OUT))),
	      animation_curve_linear__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ANIMATION_CURVE::LINEAR))),
	      autolink_all__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::ALL))),
	      autolink_calendar__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::CALENDAR))),
	      autolink_email_addresses__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::EMAIL_ADDRESSES))),
	      autolink_map_addresses__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::MAP_ADDRESSES))),
	      autolink_none__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::NONE))),
	      autolink_phone_numbers__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::PHONE_NUMBERS))),
	      autolink_urls__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::AUTOLINK::URLS))),
	      extend_edge_all__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::EXTEND_EDGE::ALL))),
	      extend_edge_bottom__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::EXTEND_EDGE::BOTTOM))),
	      extend_edge_left__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::EXTEND_EDGE::LEFT))),
	      extend_edge_none__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::EXTEND_EDGE::NONE))),
	      extend_edge_right__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::EXTEND_EDGE::RIGHT))),
	      extend_edge_top__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::EXTEND_EDGE::TOP))),
	      face_down__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::FACE_DOWN))),
	      face_up__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::FACE_UP))),
	      fill__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL))),
	      inherit__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::INHERIT))),
	      input_borderstyle_bezel__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BORDERSTYLE::BEZEL))),
	      input_borderstyle_line__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BORDERSTYLE::LINE))),
	      input_borderstyle_none__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BORDERSTYLE::NONE))),
	      input_borderstyle_rounded__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BORDERSTYLE::ROUNDED))),
	      input_buttonmode_always__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BUTTONMODE::ALWAYS))),
	      input_buttonmode_never__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BUTTONMODE::NEVER))),
	      input_buttonmode_onblur__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BUTTONMODE::ONBLUR))),
	      input_buttonmode_onfocus__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::INPUT_BUTTONMODE::ONFOCUS))),
	      keyboard_appearance_alert__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD_APPEARANCE::ALERT))),
	      keyboard_appearance_default__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD_APPEARANCE::DEFAULT))),
	      keyboard_ascii__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::ASCII))),
	      keyboard_decimal_pad__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::DECIMAL_PAD))),
	      keyboard_default__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::DEFAULT))),
	      keyboard_email__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::EMAIL))),
	      keyboard_namephone_pad__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::NAMEPHONE_PAD))),
	      keyboard_numbers_punctuation__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::NUMBERS_PUNCTUATION))),
	      keyboard_number_pad__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::NUMBER_PAD))),
	      keyboard_phone_pad__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::PHONE_PAD))),
	      keyboard_url__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::KEYBOARD::URL))),
	      landscape_left__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::LANDSCAPE_LEFT))),
	      landscape_right__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::LANDSCAPE_RIGHT))),
	      list_accessory_type_checkmark__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ACCESSORY_TYPE::CHECKMARK))),
	      list_accessory_type_detail__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ACCESSORY_TYPE::DETAIL))),
	      list_accessory_type_disclosure__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ACCESSORY_TYPE::DISCLOSURE))),
	      list_accessory_type_none__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ACCESSORY_TYPE::NONE))),
	      list_item_template_contacts__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ITEM_TEMPLATE::CONTACTS))),
	      list_item_template_default__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ITEM_TEMPLATE::DEFAULT))),
	      list_item_template_settings__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ITEM_TEMPLATE::SETTINGS))),
	      list_item_template_subtitle__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::LIST_ITEM_TEMPLATE::SUBTITLE))),
	      notification_duration_long__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::NOTIFICATION_DURATION::LONG))),
	      notification_duration_short__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::NOTIFICATION_DURATION::SHORT))),
	      picker_type_count_down_timer__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::PICKER_TYPE::COUNT_DOWN_TIMER))),
	      picker_type_date__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::PICKER_TYPE::DATE))),
	      picker_type_date_and_time__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::PICKER_TYPE::DATE_AND_TIME))),
	      picker_type_plain__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::PICKER_TYPE::PLAIN))),
	      picker_type_time__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::PICKER_TYPE::TIME))),
	      portrait__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::PORTRAIT))),
	      returnkey_default__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::DEFAULT))),
	      returnkey_done__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::DONE))),
	      returnkey_emergency_call__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::EMERGENCY_CALL))),
	      returnkey_go__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::GO))),
	      returnkey_google__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::GOOGLE))),
	      returnkey_join__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::JOIN))),
	      returnkey_next__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::NEXT))),
	      returnkey_route__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::ROUTE))),
	      returnkey_search__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::SEARCH))),
	      returnkey_send__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::SEND))),
	      returnkey_yahoo__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::RETURNKEY::YAHOO))),
	      size__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE))),
	      text_alignment_center__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ALIGNMENT::CENTER))),
	      text_alignment_left__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ALIGNMENT::LEFT))),
	      text_alignment_right__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_ALIGNMENT::RIGHT))),
	      text_autocapitalization_all__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_AUTOCAPITALIZATION::ALL))),
	      text_autocapitalization_none__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_AUTOCAPITALIZATION::NONE))),
	      text_autocapitalization_sentences__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_AUTOCAPITALIZATION::SENTENCES))),
	      text_autocapitalization_words__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_AUTOCAPITALIZATION::WORDS))),
	      text_style_body__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::TEXT_STYLE::BODY))),
	      text_style_caption1__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::TEXT_STYLE::CAPTION1))),
	      text_style_caption2__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::TEXT_STYLE::CAPTION2))),
	      text_style_footnote__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::TEXT_STYLE::FOOTNOTE))),
	      text_style_headline__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::TEXT_STYLE::HEADLINE))),
	      text_style_subheadline__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::TEXT_STYLE::SUBHEADLINE))),
	      text_vertical_alignment_bottom__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_VERTICAL_ALIGNMENT::BOTTOM))),
	      text_vertical_alignment_center__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_VERTICAL_ALIGNMENT::CENTER))),
	      text_vertical_alignment_top__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::TEXT_VERTICAL_ALIGNMENT::TOP))),
	      unit_cm__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::UNIT::CM))),
	      unit_dip__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::UNIT::DIP))),
	      unit_in__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::UNIT::IN))),
	      unit_mm__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::UNIT::MM))),
	      unit_px__(js_context.CreateString(Titanium::UI::Constants::to_string(Titanium::UI::UNIT::PX))),
	      unknown__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::UNKNOWN))),
	      upside_portrait__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::ORIENTATION::UPSIDE_PORTRAIT))),
	      url_error_authentication__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::AUTHENTICATION))),
	      url_error_bad_url__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::BAD_URL))),
	      url_error_connect__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::CONNECT))),
	      url_error_file__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::FILE))),
	      url_error_file_not_found__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::FILE_NOT_FOUND))),
	      url_error_host_lookup__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::HOST_LOOKUP))),
	      url_error_redirect_loop__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::REDIRECT_LOOP))),
	      url_error_ssl_failed__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::SSL_FAILED))),
	      url_error_timeout__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::TIMEOUT))),
	      url_error_unknown__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::UNKNOWN))),
	      url_error_unsupported_scheme__(js_context.CreateNumber(Titanium::UI::Constants::to_underlying_type(Titanium::UI::URL_ERROR::UNSUPPORTED_SCHEME)))
	{
		TITANIUM_LOG_DEBUG("UIModule:: ctor 1 ", this);
	}

	UIModule::UIModule(const UIModule& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
	    : Module(rhs, arguments),
	      animation_curve_ease_in__(rhs.animation_curve_ease_in__),
	      animation_curve_ease_in_out__(rhs.animation_curve_ease_in_out__),
	      animation_curve_ease_out__(rhs.animation_curve_ease_out__),
	      animation_curve_linear__(rhs.animation_curve_linear__),
	      autolink_all__(rhs.autolink_all__),
	      autolink_calendar__(rhs.autolink_calendar__),
	      autolink_email_addresses__(rhs.autolink_email_addresses__),
	      autolink_map_addresses__(rhs.autolink_map_addresses__),
	      autolink_none__(rhs.autolink_none__),
	      autolink_phone_numbers__(rhs.autolink_phone_numbers__),
	      autolink_urls__(rhs.autolink_urls__),
	      extend_edge_all__(rhs.extend_edge_all__),
	      extend_edge_bottom__(rhs.extend_edge_bottom__),
	      extend_edge_left__(rhs.extend_edge_left__),
	      extend_edge_none__(rhs.extend_edge_none__),
	      extend_edge_right__(rhs.extend_edge_right__),
	      extend_edge_top__(rhs.extend_edge_top__),
	      face_down__(rhs.face_down__),
	      face_up__(rhs.face_up__),
	      fill__(rhs.fill__),
	      inherit__(rhs.inherit__),
	      input_borderstyle_bezel__(rhs.input_borderstyle_bezel__),
	      input_borderstyle_line__(rhs.input_borderstyle_line__),
	      input_borderstyle_none__(rhs.input_borderstyle_none__),
	      input_borderstyle_rounded__(rhs.input_borderstyle_rounded__),
	      input_buttonmode_always__(rhs.input_buttonmode_always__),
	      input_buttonmode_never__(rhs.input_buttonmode_never__),
	      input_buttonmode_onblur__(rhs.input_buttonmode_onblur__),
	      input_buttonmode_onfocus__(rhs.input_buttonmode_onfocus__),
	      keyboard_appearance_alert__(rhs.keyboard_appearance_alert__),
	      keyboard_appearance_default__(rhs.keyboard_appearance_default__),
	      keyboard_ascii__(rhs.keyboard_ascii__),
	      keyboard_decimal_pad__(rhs.keyboard_decimal_pad__),
	      keyboard_default__(rhs.keyboard_default__),
	      keyboard_email__(rhs.keyboard_email__),
	      keyboard_namephone_pad__(rhs.keyboard_namephone_pad__),
	      keyboard_numbers_punctuation__(rhs.keyboard_numbers_punctuation__),
	      keyboard_number_pad__(rhs.keyboard_number_pad__),
	      keyboard_phone_pad__(rhs.keyboard_phone_pad__),
	      keyboard_url__(rhs.keyboard_url__),
	      landscape_left__(rhs.landscape_left__),
	      landscape_right__(rhs.landscape_right__),
	      list_accessory_type_checkmark__(rhs.list_accessory_type_checkmark__),
	      list_accessory_type_detail__(rhs.list_accessory_type_detail__),
	      list_accessory_type_disclosure__(rhs.list_accessory_type_disclosure__),
	      list_accessory_type_none__(rhs.list_accessory_type_none__),
	      list_item_template_contacts__(rhs.list_item_template_contacts__),
	      list_item_template_default__(rhs.list_item_template_default__),
	      list_item_template_settings__(rhs.list_item_template_settings__),
	      list_item_template_subtitle__(rhs.list_item_template_subtitle__),
	      notification_duration_long__(rhs.notification_duration_long__),
	      notification_duration_short__(rhs.notification_duration_short__),
	      picker_type_count_down_timer__(rhs.picker_type_count_down_timer__),
	      picker_type_date__(rhs.picker_type_date__),
	      picker_type_date_and_time__(rhs.picker_type_date_and_time__),
	      picker_type_plain__(rhs.picker_type_plain__),
	      picker_type_time__(rhs.picker_type_time__),
	      portrait__(rhs.portrait__),
	      returnkey_default__(rhs.returnkey_default__),
	      returnkey_done__(rhs.returnkey_done__),
	      returnkey_emergency_call__(rhs.returnkey_emergency_call__),
	      returnkey_go__(rhs.returnkey_go__),
	      returnkey_google__(rhs.returnkey_google__),
	      returnkey_join__(rhs.returnkey_join__),
	      returnkey_next__(rhs.returnkey_next__),
	      returnkey_route__(rhs.returnkey_route__),
	      returnkey_search__(rhs.returnkey_search__),
	      returnkey_send__(rhs.returnkey_send__),
	      returnkey_yahoo__(rhs.returnkey_yahoo__),
	      size__(rhs.size__),
	      text_alignment_center__(rhs.text_alignment_center__),
	      text_alignment_left__(rhs.text_alignment_left__),
	      text_alignment_right__(rhs.text_alignment_right__),
	      text_autocapitalization_all__(rhs.text_autocapitalization_all__),
	      text_autocapitalization_none__(rhs.text_autocapitalization_none__),
	      text_autocapitalization_sentences__(rhs.text_autocapitalization_sentences__),
	      text_autocapitalization_words__(rhs.text_autocapitalization_words__),
	      text_style_body__(rhs.text_style_body__),
	      text_style_caption1__(rhs.text_style_caption1__),
	      text_style_caption2__(rhs.text_style_caption2__),
	      text_style_footnote__(rhs.text_style_footnote__),
	      text_style_headline__(rhs.text_style_headline__),
	      text_style_subheadline__(rhs.text_style_subheadline__),
	      text_vertical_alignment_bottom__(rhs.text_vertical_alignment_bottom__),
	      text_vertical_alignment_center__(rhs.text_vertical_alignment_center__),
	      text_vertical_alignment_top__(rhs.text_vertical_alignment_top__),
	      unit_cm__(rhs.unit_cm__),
	      unit_dip__(rhs.unit_dip__),
	      unit_in__(rhs.unit_in__),
	      unit_mm__(rhs.unit_mm__),
	      unit_px__(rhs.unit_px__),
	      unknown__(rhs.unknown__),
	      upside_portrait__(rhs.upside_portrait__),
	      url_error_authentication__(rhs.url_error_authentication__),
	      url_error_bad_url__(rhs.url_error_bad_url__),
	      url_error_connect__(rhs.url_error_connect__),
	      url_error_file__(rhs.url_error_file__),
	      url_error_file_not_found__(rhs.url_error_file_not_found__),
	      url_error_host_lookup__(rhs.url_error_host_lookup__),
	      url_error_redirect_loop__(rhs.url_error_redirect_loop__),
	      url_error_ssl_failed__(rhs.url_error_ssl_failed__),
	      url_error_timeout__(rhs.url_error_timeout__),
	      url_error_unknown__(rhs.url_error_unknown__),
	      url_error_unsupported_scheme__(rhs.url_error_unsupported_scheme__)
	{
		TITANIUM_LOG_DEBUG("UIModule:: ctor 2 ", this);
	}

	UIModule::~UIModule() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UIModule:: dtor ", this);
	}

	JSObject UIModule::createView(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UI::createView");

		JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = Titanium_property;

		JSValue UI_property = Titanium.GetProperty("UI");
		TITANIUM_ASSERT(UI_property.IsObject());  // precondition
		JSObject UI = UI_property;

		JSValue View_property = UI.GetProperty("View");
		TITANIUM_ASSERT(View_property.IsObject());  // precondition
		JSObject View = View_property;

		auto view = View.CallAsConstructor(parameters);
		Titanium::applyProperties(view, parameters);
		return view;
	}

	JSObject UIModule::createWindow(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UI::createWindow");

		JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = Titanium_property;

		JSValue UI_property = Titanium.GetProperty("UI");
		TITANIUM_ASSERT(UI_property.IsObject());  // precondition
		JSObject UI = UI_property;

		JSValue Window_property = UI.GetProperty("Window");
		TITANIUM_ASSERT(Window_property.IsObject());  // precondition
		JSObject Window = Window_property;

		auto window = Window.CallAsConstructor(parameters);
		Titanium::applyProperties(window, parameters);
		return window;
	}

	JSObject UIModule::createButton(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UI::createButton");

		JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = Titanium_property;

		JSValue UI_property = Titanium.GetProperty("UI");
		TITANIUM_ASSERT(UI_property.IsObject());  // precondition
		JSObject UI = UI_property;

		JSValue Button_property = UI.GetProperty("Button");
		TITANIUM_ASSERT(Button_property.IsObject());  // precondition
		JSObject Button = Button_property;

		auto button = Button.CallAsConstructor(parameters);
		Titanium::applyProperties(button, parameters);
		return button;
	}

	JSObject UIModule::createSlider(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UI::createSlider");

		JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = Titanium_property;

		JSValue UI_property = Titanium.GetProperty("UI");
		TITANIUM_ASSERT(UI_property.IsObject());  // precondition
		JSObject UI = UI_property;

		JSValue Slider_property = UI.GetProperty("Slider");
		TITANIUM_ASSERT(Slider_property.IsObject());  // precondition
		JSObject Slider = Slider_property;

		auto slider = Slider.CallAsConstructor(parameters);
		Titanium::applyProperties(slider, parameters);
		return slider;
	}

	JSObject UIModule::createAlertDialog(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UI::createAlertDialog");

		JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = Titanium_property;

		JSValue UI_property = Titanium.GetProperty("UI");
		TITANIUM_ASSERT(UI_property.IsObject());  // precondition
		JSObject UI = UI_property;

		JSValue AlertDialog_property = UI.GetProperty("AlertDialog");
		TITANIUM_ASSERT(AlertDialog_property.IsObject());  // precondition
		JSObject AlertDialog = AlertDialog_property;

		auto alertDialog = AlertDialog.CallAsConstructor(parameters);
		Titanium::applyProperties(alertDialog, parameters);
		return alertDialog;
	}

	JSObject UIModule::createTab(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UI::createTab");
		//
		// TODO: Evaluate and cache this function at startup
		//
		const std::string script = R"JS(
  var Tab = function() {
    Object.defineProperty(this, "__ti_private__", {
        enumerable: false,
        value: {}
    });
    this.__ti_private__.window = null;
    this.__ti_private__.title = Ti.UI.createButton({title:'', height:'Ti.UI.SIZE', left:0, borderWidth:0});
    this.__ti_private__.title.font = { fontSize: 20 };
  };
  Object.defineProperties(Tab.prototype, {
    "window": {
        set:function(value){this.setWindow(value);},
        get:function(){return this.getWindow();},
        enumerable:true
    },
    "title": {
        set:function(value){this.setTitle(value);},
        get:function(){return this.getTitle();},
        enumerable:true
    },
    "icon": {
        set:function(value){this.setIcon(value);},
        get:function(){return this.getIocon();},
        enumerable:true
    }
  });
  Tab.prototype.setWindow = function (_window) {
      this.__ti_private__.window = _window;
      this.__ti_private__.window.height = Ti.UI.FILL;
  };
  Tab.prototype.getWindow = function () {
      return this.__ti_private__.window;
  }
  Tab.prototype.getTitle = function () {
      return this.__ti_private__.title.title;
  };
  Tab.prototype.setTitle = function (_title) {
      this.__ti_private__.title.title = _title;
  };
  Tab.prototype.getIcon = function () {
      return this.__ti_private__.title.image;
  };
  Tab.prototype.setIcon = function (_icon) {
      this.__ti_private__.title.image = _icon;
  };
  Tab.prototype.open = function (_window) {
      _window.open();
  };
  Tab.prototype.close = function (_window) {
      _window.close();
  };
  Tab.prototype.applyProperties = function (_args) {
      _args = _args || {};
      for (var key in _args) {
          this[key] = _args[key];
      }
  };
  var ui = new Tab();
  ui.applyProperties(_arguments);
  return ui;
    )JS";

		return get_context().CreateFunction(script, {"_arguments"})({parameters}, this_object);
	}

	JSObject UIModule::createTabGroup(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UI::createTabGroup");
		//
		// TODO: Evaluate and cache this function at startup
		//
		const std::string script = R"JS(
  var TabGroup = function() {
    Object.defineProperty(this, "__ti_private__", {
        enumerable: false,
        value: {}
    });
    this.__ti_private__.window = Ti.UI.createWindow();
    this.__ti_private__.window.name = 'tab_window';
    this.__ti_private__.window.layout = 'vertical';
    this.__ti_private__.bar = Ti.UI.createView();
    this.__ti_private__.bar.top = 0;
    this.__ti_private__.bar.width  = Ti.UI.FILL;
    this.__ti_private__.bar.height = Ti.UI.SIZE;
    this.__ti_private__.bar.backgroundColor = 'red';
    this.__ti_private__.bar.layout = 'horizontal';
    this.__ti_private__.bar.name = 'tabBar';
    this.__ti_private__.content = Ti.UI.createScrollView();
    this.__ti_private__.content.scrollingEnabled = false;
    this.__ti_private__.content.showHorizontalScrollIndicator = false;
    this.__ti_private__.content.showVerticalScrollIndicator = false;
    this.__ti_private__.content.top = 0;
    this.__ti_private__.content.width  = Ti.UI.FILL;
    this.__ti_private__.content.height = Ti.UI.FILL;
    this.__ti_private__.content.layout = "horizontal";
    this.__ti_private__.content.name = 'scrollView';
    this.__ti_private__.content.backgroundColor = '#ccc';
    this.__ti_private__.window.add(this.__ti_private__.bar);
    this.__ti_private__.window.add(this.__ti_private__.content);
    this.__ti_private__.index = 0;
    this.__ti_private__.tabs = [];
    var self = this;
  };
  TabGroup.prototype.applyProperties = function (_args) {
      _args = _args || {};
      for (var key in _args) {
          this[key] = _args[key];
      }
  };
  TabGroup.prototype.setActiveTab = function (_n) {
      this.__ti_private__.index = _n;
      this.__ti_private__.content.scrollTo(this.__ti_private__.windowWidth*_n, 0);
  }
  TabGroup.prototype.open = function () {
      this.__ti_private__.window.open();
      this.setActiveTab(0);
  };
  TabGroup.prototype.addTab = function (_tab) {
      var self = this;
      this.__ti_private__.tabs.push(_tab);
      this.__ti_private__.bar.add(_tab.__ti_private__.title);
      this.__ti_private__.content.add(_tab.window);

      var tabLength = this.__ti_private__.tabs.length;
      var width = (1 / tabLength * 100) + '%';
      this.__ti_private__.tabs.forEach(function (tab) {
          tab.title.width = width;
          tab.window.width = width;
      });

      // TODO This works only when TabGroup is filled fulll screen.
      // This should be set from actual window width
      this.__ti_private__.windowWidth = Ti.Platform.displayCaps.platformWidth;
      this.__ti_private__.content.contentWidth = Ti.Platform.displayCaps.platformWidth * tabLength;
      
      _tab.__ti_private__.index = tabLength - 1;
      var index = _tab.__ti_private__.index;
      _tab.__ti_private__.title.addEventListener('click', function (e) {
          self.setActiveTab(index);
      });
  };
  var ui = new TabGroup();
  ui.applyProperties(_arguments);
  return ui;
    )JS";
		return get_context().CreateFunction(script, {"_arguments"})({parameters}, this_object);
	}

	JSObject UIModule::createScrollView(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UI::createScrollView");

		JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = Titanium_property;

		JSValue UI_property = Titanium.GetProperty("UI");
		TITANIUM_ASSERT(UI_property.IsObject());  // precondition
		JSObject UI = UI_property;

		JSValue ScrollView_property = UI.GetProperty("ScrollView");
		TITANIUM_ASSERT(ScrollView_property.IsObject());  // precondition
		JSObject ScrollView = ScrollView_property;

		auto view = ScrollView.CallAsConstructor(parameters);
		Titanium::applyProperties(view, parameters);
		return view;
	}

	JSObject UIModule::createLabel(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UI::createLabel");

		JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = Titanium_property;

		JSValue UI_property = Titanium.GetProperty("UI");
		TITANIUM_ASSERT(UI_property.IsObject());  // precondition
		JSObject UI = UI_property;

		JSValue Label_property = UI.GetProperty("Label");
		TITANIUM_ASSERT(Label_property.IsObject());  // precondition
		JSObject Label = Label_property;

		auto label = Label.CallAsConstructor(parameters);
		Titanium::applyProperties(label, parameters);
		return label;
	}

	JSObject UIModule::createImageView(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UI::createImageView");

		JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = Titanium_property;

		JSValue UI_property = Titanium.GetProperty("UI");
		TITANIUM_ASSERT(UI_property.IsObject());  // precondition
		JSObject UI = UI_property;

		JSValue ImageView_property = UI.GetProperty("ImageView");
		TITANIUM_ASSERT(ImageView_property.IsObject());  // precondition
		JSObject ImageView = ImageView_property;

		auto image_view = ImageView.CallAsConstructor(parameters);
		Titanium::applyProperties(image_view, parameters);
		return image_view;
	}

	JSValue UIModule::ANIMATION_CURVE_EASE_IN() const TITANIUM_NOEXCEPT
	{
		return animation_curve_ease_in__;
	}
	JSValue UIModule::ANIMATION_CURVE_EASE_IN_OUT() const TITANIUM_NOEXCEPT
	{
		return animation_curve_ease_in_out__;
	}
	JSValue UIModule::ANIMATION_CURVE_EASE_OUT() const TITANIUM_NOEXCEPT
	{
		return animation_curve_ease_out__;
	}
	JSValue UIModule::ANIMATION_CURVE_LINEAR() const TITANIUM_NOEXCEPT
	{
		return animation_curve_linear__;
	}
	JSValue UIModule::AUTOLINK_ALL() const TITANIUM_NOEXCEPT
	{
		return autolink_all__;
	}
	JSValue UIModule::AUTOLINK_CALENDAR() const TITANIUM_NOEXCEPT
	{
		return autolink_calendar__;
	}
	JSValue UIModule::AUTOLINK_EMAIL_ADDRESSES() const TITANIUM_NOEXCEPT
	{
		return autolink_email_addresses__;
	}
	JSValue UIModule::AUTOLINK_MAP_ADDRESSES() const TITANIUM_NOEXCEPT
	{
		return autolink_map_addresses__;
	}
	JSValue UIModule::AUTOLINK_NONE() const TITANIUM_NOEXCEPT
	{
		return autolink_none__;
	}
	JSValue UIModule::AUTOLINK_PHONE_NUMBERS() const TITANIUM_NOEXCEPT
	{
		return autolink_phone_numbers__;
	}
	JSValue UIModule::AUTOLINK_URLS() const TITANIUM_NOEXCEPT
	{
		return autolink_urls__;
	}
	JSValue UIModule::EXTEND_EDGE_ALL() const TITANIUM_NOEXCEPT
	{
		return extend_edge_all__;
	}
	JSValue UIModule::EXTEND_EDGE_BOTTOM() const TITANIUM_NOEXCEPT
	{
		return extend_edge_bottom__;
	}
	JSValue UIModule::EXTEND_EDGE_LEFT() const TITANIUM_NOEXCEPT
	{
		return extend_edge_left__;
	}
	JSValue UIModule::EXTEND_EDGE_NONE() const TITANIUM_NOEXCEPT
	{
		return extend_edge_none__;
	}
	JSValue UIModule::EXTEND_EDGE_RIGHT() const TITANIUM_NOEXCEPT
	{
		return extend_edge_right__;
	}
	JSValue UIModule::EXTEND_EDGE_TOP() const TITANIUM_NOEXCEPT
	{
		return extend_edge_top__;
	}
	JSValue UIModule::FACE_DOWN() const TITANIUM_NOEXCEPT
	{
		return face_down__;
	}
	JSValue UIModule::FACE_UP() const TITANIUM_NOEXCEPT
	{
		return face_up__;
	}
	JSValue UIModule::FILL() const TITANIUM_NOEXCEPT
	{
		return fill__;
	}
	JSValue UIModule::INHERIT() const TITANIUM_NOEXCEPT
	{
		return inherit__;
	}
	JSValue UIModule::INPUT_BORDERSTYLE_BEZEL() const TITANIUM_NOEXCEPT
	{
		return input_borderstyle_bezel__;
	}
	JSValue UIModule::INPUT_BORDERSTYLE_LINE() const TITANIUM_NOEXCEPT
	{
		return input_borderstyle_line__;
	}
	JSValue UIModule::INPUT_BORDERSTYLE_NONE() const TITANIUM_NOEXCEPT
	{
		return input_borderstyle_none__;
	}
	JSValue UIModule::INPUT_BORDERSTYLE_ROUNDED() const TITANIUM_NOEXCEPT
	{
		return input_borderstyle_rounded__;
	}
	JSValue UIModule::INPUT_BUTTONMODE_ALWAYS() const TITANIUM_NOEXCEPT
	{
		return input_buttonmode_always__;
	}
	JSValue UIModule::INPUT_BUTTONMODE_NEVER() const TITANIUM_NOEXCEPT
	{
		return input_buttonmode_never__;
	}
	JSValue UIModule::INPUT_BUTTONMODE_ONBLUR() const TITANIUM_NOEXCEPT
	{
		return input_buttonmode_onblur__;
	}
	JSValue UIModule::INPUT_BUTTONMODE_ONFOCUS() const TITANIUM_NOEXCEPT
	{
		return input_buttonmode_onfocus__;
	}
	JSValue UIModule::KEYBOARD_APPEARANCE_ALERT() const TITANIUM_NOEXCEPT
	{
		return keyboard_appearance_alert__;
	}
	JSValue UIModule::KEYBOARD_APPEARANCE_DEFAULT() const TITANIUM_NOEXCEPT
	{
		return keyboard_appearance_default__;
	}
	JSValue UIModule::KEYBOARD_ASCII() const TITANIUM_NOEXCEPT
	{
		return keyboard_ascii__;
	}
	JSValue UIModule::KEYBOARD_DECIMAL_PAD() const TITANIUM_NOEXCEPT
	{
		return keyboard_decimal_pad__;
	}
	JSValue UIModule::KEYBOARD_DEFAULT() const TITANIUM_NOEXCEPT
	{
		return keyboard_default__;
	}
	JSValue UIModule::KEYBOARD_EMAIL() const TITANIUM_NOEXCEPT
	{
		return keyboard_email__;
	}
	JSValue UIModule::KEYBOARD_NAMEPHONE_PAD() const TITANIUM_NOEXCEPT
	{
		return keyboard_namephone_pad__;
	}
	JSValue UIModule::KEYBOARD_NUMBERS_PUNCTUATION() const TITANIUM_NOEXCEPT
	{
		return keyboard_numbers_punctuation__;
	}
	JSValue UIModule::KEYBOARD_NUMBER_PAD() const TITANIUM_NOEXCEPT
	{
		return keyboard_number_pad__;
	}
	JSValue UIModule::KEYBOARD_PHONE_PAD() const TITANIUM_NOEXCEPT
	{
		return keyboard_phone_pad__;
	}
	JSValue UIModule::KEYBOARD_URL() const TITANIUM_NOEXCEPT
	{
		return keyboard_url__;
	}
	JSValue UIModule::LANDSCAPE_LEFT() const TITANIUM_NOEXCEPT
	{
		return landscape_left__;
	}
	JSValue UIModule::LANDSCAPE_RIGHT() const TITANIUM_NOEXCEPT
	{
		return landscape_right__;
	}
	JSValue UIModule::LIST_ACCESSORY_TYPE_CHECKMARK() const TITANIUM_NOEXCEPT
	{
		return list_accessory_type_checkmark__;
	}
	JSValue UIModule::LIST_ACCESSORY_TYPE_DETAIL() const TITANIUM_NOEXCEPT
	{
		return list_accessory_type_detail__;
	}
	JSValue UIModule::LIST_ACCESSORY_TYPE_DISCLOSURE() const TITANIUM_NOEXCEPT
	{
		return list_accessory_type_disclosure__;
	}
	JSValue UIModule::LIST_ACCESSORY_TYPE_NONE() const TITANIUM_NOEXCEPT
	{
		return list_accessory_type_none__;
	}
	JSValue UIModule::LIST_ITEM_TEMPLATE_CONTACTS() const TITANIUM_NOEXCEPT
	{
		return list_item_template_contacts__;
	}
	JSValue UIModule::LIST_ITEM_TEMPLATE_DEFAULT() const TITANIUM_NOEXCEPT
	{
		return list_item_template_default__;
	}
	JSValue UIModule::LIST_ITEM_TEMPLATE_SETTINGS() const TITANIUM_NOEXCEPT
	{
		return list_item_template_settings__;
	}
	JSValue UIModule::LIST_ITEM_TEMPLATE_SUBTITLE() const TITANIUM_NOEXCEPT
	{
		return list_item_template_subtitle__;
	}
	JSValue UIModule::NOTIFICATION_DURATION_LONG() const TITANIUM_NOEXCEPT
	{
		return notification_duration_long__;
	}
	JSValue UIModule::NOTIFICATION_DURATION_SHORT() const TITANIUM_NOEXCEPT
	{
		return notification_duration_short__;
	}
	JSValue UIModule::PICKER_TYPE_COUNT_DOWN_TIMER() const TITANIUM_NOEXCEPT
	{
		return picker_type_count_down_timer__;
	}
	JSValue UIModule::PICKER_TYPE_DATE() const TITANIUM_NOEXCEPT
	{
		return picker_type_date__;
	}
	JSValue UIModule::PICKER_TYPE_DATE_AND_TIME() const TITANIUM_NOEXCEPT
	{
		return picker_type_date_and_time__;
	}
	JSValue UIModule::PICKER_TYPE_PLAIN() const TITANIUM_NOEXCEPT
	{
		return picker_type_plain__;
	}
	JSValue UIModule::PICKER_TYPE_TIME() const TITANIUM_NOEXCEPT
	{
		return picker_type_time__;
	}
	JSValue UIModule::PORTRAIT() const TITANIUM_NOEXCEPT
	{
		return portrait__;
	}
	JSValue UIModule::RETURNKEY_DEFAULT() const TITANIUM_NOEXCEPT
	{
		return returnkey_default__;
	}
	JSValue UIModule::RETURNKEY_DONE() const TITANIUM_NOEXCEPT
	{
		return returnkey_done__;
	}
	JSValue UIModule::RETURNKEY_EMERGENCY_CALL() const TITANIUM_NOEXCEPT
	{
		return returnkey_emergency_call__;
	}
	JSValue UIModule::RETURNKEY_GO() const TITANIUM_NOEXCEPT
	{
		return returnkey_go__;
	}
	JSValue UIModule::RETURNKEY_GOOGLE() const TITANIUM_NOEXCEPT
	{
		return returnkey_google__;
	}
	JSValue UIModule::RETURNKEY_JOIN() const TITANIUM_NOEXCEPT
	{
		return returnkey_join__;
	}
	JSValue UIModule::RETURNKEY_NEXT() const TITANIUM_NOEXCEPT
	{
		return returnkey_next__;
	}
	JSValue UIModule::RETURNKEY_ROUTE() const TITANIUM_NOEXCEPT
	{
		return returnkey_route__;
	}
	JSValue UIModule::RETURNKEY_SEARCH() const TITANIUM_NOEXCEPT
	{
		return returnkey_search__;
	}
	JSValue UIModule::RETURNKEY_SEND() const TITANIUM_NOEXCEPT
	{
		return returnkey_send__;
	}
	JSValue UIModule::RETURNKEY_YAHOO() const TITANIUM_NOEXCEPT
	{
		return returnkey_yahoo__;
	}
	JSValue UIModule::SIZE() const TITANIUM_NOEXCEPT
	{
		return size__;
	}
	JSValue UIModule::TEXT_ALIGNMENT_CENTER() const TITANIUM_NOEXCEPT
	{
		return text_alignment_center__;
	}
	JSValue UIModule::TEXT_ALIGNMENT_LEFT() const TITANIUM_NOEXCEPT
	{
		return text_alignment_left__;
	}
	JSValue UIModule::TEXT_ALIGNMENT_RIGHT() const TITANIUM_NOEXCEPT
	{
		return text_alignment_right__;
	}
	JSValue UIModule::TEXT_AUTOCAPITALIZATION_ALL() const TITANIUM_NOEXCEPT
	{
		return text_autocapitalization_all__;
	}
	JSValue UIModule::TEXT_AUTOCAPITALIZATION_NONE() const TITANIUM_NOEXCEPT
	{
		return text_autocapitalization_none__;
	}
	JSValue UIModule::TEXT_AUTOCAPITALIZATION_SENTENCES() const TITANIUM_NOEXCEPT
	{
		return text_autocapitalization_sentences__;
	}
	JSValue UIModule::TEXT_AUTOCAPITALIZATION_WORDS() const TITANIUM_NOEXCEPT
	{
		return text_autocapitalization_words__;
	}
	JSValue UIModule::TEXT_STYLE_BODY() const TITANIUM_NOEXCEPT
	{
		return text_style_body__;
	}
	JSValue UIModule::TEXT_STYLE_CAPTION1() const TITANIUM_NOEXCEPT
	{
		return text_style_caption1__;
	}
	JSValue UIModule::TEXT_STYLE_CAPTION2() const TITANIUM_NOEXCEPT
	{
		return text_style_caption2__;
	}
	JSValue UIModule::TEXT_STYLE_FOOTNOTE() const TITANIUM_NOEXCEPT
	{
		return text_style_footnote__;
	}
	JSValue UIModule::TEXT_STYLE_HEADLINE() const TITANIUM_NOEXCEPT
	{
		return text_style_headline__;
	}
	JSValue UIModule::TEXT_STYLE_SUBHEADLINE() const TITANIUM_NOEXCEPT
	{
		return text_style_subheadline__;
	}
	JSValue UIModule::TEXT_VERTICAL_ALIGNMENT_BOTTOM() const TITANIUM_NOEXCEPT
	{
		return text_vertical_alignment_bottom__;
	}
	JSValue UIModule::TEXT_VERTICAL_ALIGNMENT_CENTER() const TITANIUM_NOEXCEPT
	{
		return text_vertical_alignment_center__;
	}
	JSValue UIModule::TEXT_VERTICAL_ALIGNMENT_TOP() const TITANIUM_NOEXCEPT
	{
		return text_vertical_alignment_top__;
	}
	JSValue UIModule::UNIT_CM() const TITANIUM_NOEXCEPT
	{
		return unit_cm__;
	}
	JSValue UIModule::UNIT_DIP() const TITANIUM_NOEXCEPT
	{
		return unit_dip__;
	}
	JSValue UIModule::UNIT_IN() const TITANIUM_NOEXCEPT
	{
		return unit_in__;
	}
	JSValue UIModule::UNIT_MM() const TITANIUM_NOEXCEPT
	{
		return unit_mm__;
	}
	JSValue UIModule::UNIT_PX() const TITANIUM_NOEXCEPT
	{
		return unit_px__;
	}
	JSValue UIModule::UNKNOWN() const TITANIUM_NOEXCEPT
	{
		return unknown__;
	}
	JSValue UIModule::UPSIDE_PORTRAIT() const TITANIUM_NOEXCEPT
	{
		return upside_portrait__;
	}
	JSValue UIModule::URL_ERROR_AUTHENTICATION() const TITANIUM_NOEXCEPT
	{
		return url_error_authentication__;
	}
	JSValue UIModule::URL_ERROR_BAD_URL() const TITANIUM_NOEXCEPT
	{
		return url_error_bad_url__;
	}
	JSValue UIModule::URL_ERROR_CONNECT() const TITANIUM_NOEXCEPT
	{
		return url_error_connect__;
	}
	JSValue UIModule::URL_ERROR_FILE() const TITANIUM_NOEXCEPT
	{
		return url_error_file__;
	}
	JSValue UIModule::URL_ERROR_FILE_NOT_FOUND() const TITANIUM_NOEXCEPT
	{
		return url_error_file_not_found__;
	}
	JSValue UIModule::URL_ERROR_HOST_LOOKUP() const TITANIUM_NOEXCEPT
	{
		return url_error_host_lookup__;
	}
	JSValue UIModule::URL_ERROR_REDIRECT_LOOP() const TITANIUM_NOEXCEPT
	{
		return url_error_redirect_loop__;
	}
	JSValue UIModule::URL_ERROR_SSL_FAILED() const TITANIUM_NOEXCEPT
	{
		return url_error_ssl_failed__;
	}
	JSValue UIModule::URL_ERROR_TIMEOUT() const TITANIUM_NOEXCEPT
	{
		return url_error_timeout__;
	}
	JSValue UIModule::URL_ERROR_UNKNOWN() const TITANIUM_NOEXCEPT
	{
		return url_error_unknown__;
	}
	JSValue UIModule::URL_ERROR_UNSUPPORTED_SCHEME() const TITANIUM_NOEXCEPT
	{
		return url_error_unsupported_scheme__;
	}

	// TODO: The following functions can automatically be generated from
	// the YAML API docs.

	void UIModule::JSExportInitialize()
	{
		JSExport<UIModule>::SetClassVersion(1);
		JSExport<UIModule>::SetParent(JSExport<Module>::Class());
		JSExport<UIModule>::AddFunctionProperty("createView", std::mem_fn(&UIModule::js_createView));
		JSExport<UIModule>::AddFunctionProperty("createWindow", std::mem_fn(&UIModule::js_createWindow));
		JSExport<UIModule>::AddFunctionProperty("createButton", std::mem_fn(&UIModule::js_createButton));
		JSExport<UIModule>::AddFunctionProperty("createTab", std::mem_fn(&UIModule::js_createTab));
		JSExport<UIModule>::AddFunctionProperty("createTabGroup", std::mem_fn(&UIModule::js_createTabGroup));
		JSExport<UIModule>::AddFunctionProperty("createScrollView", std::mem_fn(&UIModule::js_createScrollView));
		JSExport<UIModule>::AddFunctionProperty("createImageView", std::mem_fn(&UIModule::js_createImageView));
		JSExport<UIModule>::AddFunctionProperty("createLabel", std::mem_fn(&UIModule::js_createLabel));
		JSExport<UIModule>::AddFunctionProperty("createSlider", std::mem_fn(&UIModule::js_createSlider));
		JSExport<UIModule>::AddFunctionProperty("createAlertDialog", std::mem_fn(&UIModule::js_createAlertDialog));
		JSExport<UIModule>::AddFunctionProperty("setBackgroundColor", std::mem_fn(&UIModule::js_setBackgroundColor));
		JSExport<UIModule>::AddValueProperty("ANIMATION_CURVE_EASE_IN", std::mem_fn(&UIModule::ANIMATION_CURVE_EASE_IN));
		JSExport<UIModule>::AddValueProperty("ANIMATION_CURVE_EASE_IN_OUT", std::mem_fn(&UIModule::ANIMATION_CURVE_EASE_IN_OUT));
		JSExport<UIModule>::AddValueProperty("ANIMATION_CURVE_EASE_OUT", std::mem_fn(&UIModule::ANIMATION_CURVE_EASE_OUT));
		JSExport<UIModule>::AddValueProperty("ANIMATION_CURVE_LINEAR", std::mem_fn(&UIModule::ANIMATION_CURVE_LINEAR));
		JSExport<UIModule>::AddValueProperty("AUTOLINK_ALL", std::mem_fn(&UIModule::AUTOLINK_ALL));
		JSExport<UIModule>::AddValueProperty("AUTOLINK_CALENDAR", std::mem_fn(&UIModule::AUTOLINK_CALENDAR));
		JSExport<UIModule>::AddValueProperty("AUTOLINK_EMAIL_ADDRESSES", std::mem_fn(&UIModule::AUTOLINK_EMAIL_ADDRESSES));
		JSExport<UIModule>::AddValueProperty("AUTOLINK_MAP_ADDRESSES", std::mem_fn(&UIModule::AUTOLINK_MAP_ADDRESSES));
		JSExport<UIModule>::AddValueProperty("AUTOLINK_NONE", std::mem_fn(&UIModule::AUTOLINK_NONE));
		JSExport<UIModule>::AddValueProperty("AUTOLINK_PHONE_NUMBERS", std::mem_fn(&UIModule::AUTOLINK_PHONE_NUMBERS));
		JSExport<UIModule>::AddValueProperty("AUTOLINK_URLS", std::mem_fn(&UIModule::AUTOLINK_URLS));
		JSExport<UIModule>::AddValueProperty("EXTEND_EDGE_ALL", std::mem_fn(&UIModule::EXTEND_EDGE_ALL));
		JSExport<UIModule>::AddValueProperty("EXTEND_EDGE_BOTTOM", std::mem_fn(&UIModule::EXTEND_EDGE_BOTTOM));
		JSExport<UIModule>::AddValueProperty("EXTEND_EDGE_LEFT", std::mem_fn(&UIModule::EXTEND_EDGE_LEFT));
		JSExport<UIModule>::AddValueProperty("EXTEND_EDGE_NONE", std::mem_fn(&UIModule::EXTEND_EDGE_NONE));
		JSExport<UIModule>::AddValueProperty("EXTEND_EDGE_RIGHT", std::mem_fn(&UIModule::EXTEND_EDGE_RIGHT));
		JSExport<UIModule>::AddValueProperty("EXTEND_EDGE_TOP", std::mem_fn(&UIModule::EXTEND_EDGE_TOP));
		JSExport<UIModule>::AddValueProperty("FACE_DOWN", std::mem_fn(&UIModule::FACE_DOWN));
		JSExport<UIModule>::AddValueProperty("FACE_UP", std::mem_fn(&UIModule::FACE_UP));
		JSExport<UIModule>::AddValueProperty("FILL", std::mem_fn(&UIModule::FILL));
		JSExport<UIModule>::AddValueProperty("INHERIT", std::mem_fn(&UIModule::INHERIT));
		JSExport<UIModule>::AddValueProperty("INPUT_BORDERSTYLE_BEZEL", std::mem_fn(&UIModule::INPUT_BORDERSTYLE_BEZEL));
		JSExport<UIModule>::AddValueProperty("INPUT_BORDERSTYLE_LINE", std::mem_fn(&UIModule::INPUT_BORDERSTYLE_LINE));
		JSExport<UIModule>::AddValueProperty("INPUT_BORDERSTYLE_NONE", std::mem_fn(&UIModule::INPUT_BORDERSTYLE_NONE));
		JSExport<UIModule>::AddValueProperty("INPUT_BORDERSTYLE_ROUNDED", std::mem_fn(&UIModule::INPUT_BORDERSTYLE_ROUNDED));
		JSExport<UIModule>::AddValueProperty("INPUT_BUTTONMODE_ALWAYS", std::mem_fn(&UIModule::INPUT_BUTTONMODE_ALWAYS));
		JSExport<UIModule>::AddValueProperty("INPUT_BUTTONMODE_NEVER", std::mem_fn(&UIModule::INPUT_BUTTONMODE_NEVER));
		JSExport<UIModule>::AddValueProperty("INPUT_BUTTONMODE_ONBLUR", std::mem_fn(&UIModule::INPUT_BUTTONMODE_ONBLUR));
		JSExport<UIModule>::AddValueProperty("INPUT_BUTTONMODE_ONFOCUS", std::mem_fn(&UIModule::INPUT_BUTTONMODE_ONFOCUS));
		JSExport<UIModule>::AddValueProperty("KEYBOARD_APPEARANCE_ALERT", std::mem_fn(&UIModule::KEYBOARD_APPEARANCE_ALERT));
		JSExport<UIModule>::AddValueProperty("KEYBOARD_APPEARANCE_DEFAULT", std::mem_fn(&UIModule::KEYBOARD_APPEARANCE_DEFAULT));
		JSExport<UIModule>::AddValueProperty("KEYBOARD_ASCII", std::mem_fn(&UIModule::KEYBOARD_ASCII));
		JSExport<UIModule>::AddValueProperty("KEYBOARD_DECIMAL_PAD", std::mem_fn(&UIModule::KEYBOARD_DECIMAL_PAD));
		JSExport<UIModule>::AddValueProperty("KEYBOARD_DEFAULT", std::mem_fn(&UIModule::KEYBOARD_DEFAULT));
		JSExport<UIModule>::AddValueProperty("KEYBOARD_EMAIL", std::mem_fn(&UIModule::KEYBOARD_EMAIL));
		JSExport<UIModule>::AddValueProperty("KEYBOARD_NAMEPHONE_PAD", std::mem_fn(&UIModule::KEYBOARD_NAMEPHONE_PAD));
		JSExport<UIModule>::AddValueProperty("KEYBOARD_NUMBERS_PUNCTUATION", std::mem_fn(&UIModule::KEYBOARD_NUMBERS_PUNCTUATION));
		JSExport<UIModule>::AddValueProperty("KEYBOARD_NUMBER_PAD", std::mem_fn(&UIModule::KEYBOARD_NUMBER_PAD));
		JSExport<UIModule>::AddValueProperty("KEYBOARD_PHONE_PAD", std::mem_fn(&UIModule::KEYBOARD_PHONE_PAD));
		JSExport<UIModule>::AddValueProperty("KEYBOARD_URL", std::mem_fn(&UIModule::KEYBOARD_URL));
		JSExport<UIModule>::AddValueProperty("LANDSCAPE_LEFT", std::mem_fn(&UIModule::LANDSCAPE_LEFT));
		JSExport<UIModule>::AddValueProperty("LANDSCAPE_RIGHT", std::mem_fn(&UIModule::LANDSCAPE_RIGHT));
		JSExport<UIModule>::AddValueProperty("LIST_ACCESSORY_TYPE_CHECKMARK", std::mem_fn(&UIModule::LIST_ACCESSORY_TYPE_CHECKMARK));
		JSExport<UIModule>::AddValueProperty("LIST_ACCESSORY_TYPE_DETAIL", std::mem_fn(&UIModule::LIST_ACCESSORY_TYPE_DETAIL));
		JSExport<UIModule>::AddValueProperty("LIST_ACCESSORY_TYPE_DISCLOSURE", std::mem_fn(&UIModule::LIST_ACCESSORY_TYPE_DISCLOSURE));
		JSExport<UIModule>::AddValueProperty("LIST_ACCESSORY_TYPE_NONE", std::mem_fn(&UIModule::LIST_ACCESSORY_TYPE_NONE));
		JSExport<UIModule>::AddValueProperty("LIST_ITEM_TEMPLATE_CONTACTS", std::mem_fn(&UIModule::LIST_ITEM_TEMPLATE_CONTACTS));
		JSExport<UIModule>::AddValueProperty("LIST_ITEM_TEMPLATE_DEFAULT", std::mem_fn(&UIModule::LIST_ITEM_TEMPLATE_DEFAULT));
		JSExport<UIModule>::AddValueProperty("LIST_ITEM_TEMPLATE_SETTINGS", std::mem_fn(&UIModule::LIST_ITEM_TEMPLATE_SETTINGS));
		JSExport<UIModule>::AddValueProperty("LIST_ITEM_TEMPLATE_SUBTITLE", std::mem_fn(&UIModule::LIST_ITEM_TEMPLATE_SUBTITLE));
		JSExport<UIModule>::AddValueProperty("NOTIFICATION_DURATION_LONG", std::mem_fn(&UIModule::NOTIFICATION_DURATION_LONG));
		JSExport<UIModule>::AddValueProperty("NOTIFICATION_DURATION_SHORT", std::mem_fn(&UIModule::NOTIFICATION_DURATION_SHORT));
		JSExport<UIModule>::AddValueProperty("PICKER_TYPE_COUNT_DOWN_TIMER", std::mem_fn(&UIModule::PICKER_TYPE_COUNT_DOWN_TIMER));
		JSExport<UIModule>::AddValueProperty("PICKER_TYPE_DATE", std::mem_fn(&UIModule::PICKER_TYPE_DATE));
		JSExport<UIModule>::AddValueProperty("PICKER_TYPE_DATE_AND_TIME", std::mem_fn(&UIModule::PICKER_TYPE_DATE_AND_TIME));
		JSExport<UIModule>::AddValueProperty("PICKER_TYPE_PLAIN", std::mem_fn(&UIModule::PICKER_TYPE_PLAIN));
		JSExport<UIModule>::AddValueProperty("PICKER_TYPE_TIME", std::mem_fn(&UIModule::PICKER_TYPE_TIME));
		JSExport<UIModule>::AddValueProperty("PORTRAIT", std::mem_fn(&UIModule::PORTRAIT));
		JSExport<UIModule>::AddValueProperty("RETURNKEY_DEFAULT", std::mem_fn(&UIModule::RETURNKEY_DEFAULT));
		JSExport<UIModule>::AddValueProperty("RETURNKEY_DONE", std::mem_fn(&UIModule::RETURNKEY_DONE));
		JSExport<UIModule>::AddValueProperty("RETURNKEY_EMERGENCY_CALL", std::mem_fn(&UIModule::RETURNKEY_EMERGENCY_CALL));
		JSExport<UIModule>::AddValueProperty("RETURNKEY_GO", std::mem_fn(&UIModule::RETURNKEY_GO));
		JSExport<UIModule>::AddValueProperty("RETURNKEY_GOOGLE", std::mem_fn(&UIModule::RETURNKEY_GOOGLE));
		JSExport<UIModule>::AddValueProperty("RETURNKEY_JOIN", std::mem_fn(&UIModule::RETURNKEY_JOIN));
		JSExport<UIModule>::AddValueProperty("RETURNKEY_NEXT", std::mem_fn(&UIModule::RETURNKEY_NEXT));
		JSExport<UIModule>::AddValueProperty("RETURNKEY_ROUTE", std::mem_fn(&UIModule::RETURNKEY_ROUTE));
		JSExport<UIModule>::AddValueProperty("RETURNKEY_SEARCH", std::mem_fn(&UIModule::RETURNKEY_SEARCH));
		JSExport<UIModule>::AddValueProperty("RETURNKEY_SEND", std::mem_fn(&UIModule::RETURNKEY_SEND));
		JSExport<UIModule>::AddValueProperty("RETURNKEY_YAHOO", std::mem_fn(&UIModule::RETURNKEY_YAHOO));
		JSExport<UIModule>::AddValueProperty("SIZE", std::mem_fn(&UIModule::SIZE));
		JSExport<UIModule>::AddValueProperty("TEXT_ALIGNMENT_CENTER", std::mem_fn(&UIModule::TEXT_ALIGNMENT_CENTER));
		JSExport<UIModule>::AddValueProperty("TEXT_ALIGNMENT_LEFT", std::mem_fn(&UIModule::TEXT_ALIGNMENT_LEFT));
		JSExport<UIModule>::AddValueProperty("TEXT_ALIGNMENT_RIGHT", std::mem_fn(&UIModule::TEXT_ALIGNMENT_RIGHT));
		JSExport<UIModule>::AddValueProperty("TEXT_AUTOCAPITALIZATION_ALL", std::mem_fn(&UIModule::TEXT_AUTOCAPITALIZATION_ALL));
		JSExport<UIModule>::AddValueProperty("TEXT_AUTOCAPITALIZATION_NONE", std::mem_fn(&UIModule::TEXT_AUTOCAPITALIZATION_NONE));
		JSExport<UIModule>::AddValueProperty("TEXT_AUTOCAPITALIZATION_SENTENCES", std::mem_fn(&UIModule::TEXT_AUTOCAPITALIZATION_SENTENCES));
		JSExport<UIModule>::AddValueProperty("TEXT_AUTOCAPITALIZATION_WORDS", std::mem_fn(&UIModule::TEXT_AUTOCAPITALIZATION_WORDS));
		JSExport<UIModule>::AddValueProperty("TEXT_STYLE_BODY", std::mem_fn(&UIModule::TEXT_STYLE_BODY));
		JSExport<UIModule>::AddValueProperty("TEXT_STYLE_CAPTION1", std::mem_fn(&UIModule::TEXT_STYLE_CAPTION1));
		JSExport<UIModule>::AddValueProperty("TEXT_STYLE_CAPTION2", std::mem_fn(&UIModule::TEXT_STYLE_CAPTION2));
		JSExport<UIModule>::AddValueProperty("TEXT_STYLE_FOOTNOTE", std::mem_fn(&UIModule::TEXT_STYLE_FOOTNOTE));
		JSExport<UIModule>::AddValueProperty("TEXT_STYLE_HEADLINE", std::mem_fn(&UIModule::TEXT_STYLE_HEADLINE));
		JSExport<UIModule>::AddValueProperty("TEXT_STYLE_SUBHEADLINE", std::mem_fn(&UIModule::TEXT_STYLE_SUBHEADLINE));
		JSExport<UIModule>::AddValueProperty("TEXT_VERTICAL_ALIGNMENT_BOTTOM", std::mem_fn(&UIModule::TEXT_VERTICAL_ALIGNMENT_BOTTOM));
		JSExport<UIModule>::AddValueProperty("TEXT_VERTICAL_ALIGNMENT_CENTER", std::mem_fn(&UIModule::TEXT_VERTICAL_ALIGNMENT_CENTER));
		JSExport<UIModule>::AddValueProperty("TEXT_VERTICAL_ALIGNMENT_TOP", std::mem_fn(&UIModule::TEXT_VERTICAL_ALIGNMENT_TOP));
		JSExport<UIModule>::AddValueProperty("UNIT_CM", std::mem_fn(&UIModule::UNIT_CM));
		JSExport<UIModule>::AddValueProperty("UNIT_DIP", std::mem_fn(&UIModule::UNIT_DIP));
		JSExport<UIModule>::AddValueProperty("UNIT_IN", std::mem_fn(&UIModule::UNIT_IN));
		JSExport<UIModule>::AddValueProperty("UNIT_MM", std::mem_fn(&UIModule::UNIT_MM));
		JSExport<UIModule>::AddValueProperty("UNIT_PX", std::mem_fn(&UIModule::UNIT_PX));
		JSExport<UIModule>::AddValueProperty("UNKNOWN", std::mem_fn(&UIModule::UNKNOWN));
		JSExport<UIModule>::AddValueProperty("UPSIDE_PORTRAIT", std::mem_fn(&UIModule::UPSIDE_PORTRAIT));
		JSExport<UIModule>::AddValueProperty("URL_ERROR_AUTHENTICATION", std::mem_fn(&UIModule::URL_ERROR_AUTHENTICATION));
		JSExport<UIModule>::AddValueProperty("URL_ERROR_BAD_URL", std::mem_fn(&UIModule::URL_ERROR_BAD_URL));
		JSExport<UIModule>::AddValueProperty("URL_ERROR_CONNECT", std::mem_fn(&UIModule::URL_ERROR_CONNECT));
		JSExport<UIModule>::AddValueProperty("URL_ERROR_FILE", std::mem_fn(&UIModule::URL_ERROR_FILE));
		JSExport<UIModule>::AddValueProperty("URL_ERROR_FILE_NOT_FOUND", std::mem_fn(&UIModule::URL_ERROR_FILE_NOT_FOUND));
		JSExport<UIModule>::AddValueProperty("URL_ERROR_HOST_LOOKUP", std::mem_fn(&UIModule::URL_ERROR_HOST_LOOKUP));
		JSExport<UIModule>::AddValueProperty("URL_ERROR_REDIRECT_LOOP", std::mem_fn(&UIModule::URL_ERROR_REDIRECT_LOOP));
		JSExport<UIModule>::AddValueProperty("URL_ERROR_SSL_FAILED", std::mem_fn(&UIModule::URL_ERROR_SSL_FAILED));
		JSExport<UIModule>::AddValueProperty("URL_ERROR_TIMEOUT", std::mem_fn(&UIModule::URL_ERROR_TIMEOUT));
		JSExport<UIModule>::AddValueProperty("URL_ERROR_UNKNOWN", std::mem_fn(&UIModule::URL_ERROR_UNKNOWN));
		JSExport<UIModule>::AddValueProperty("URL_ERROR_UNSUPPORTED_SCHEME", std::mem_fn(&UIModule::URL_ERROR_UNSUPPORTED_SCHEME));
	}

	JSValue UIModule::js_createView(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		JSObject parameters = get_context().CreateObject();
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = _0;
		}
		return createView(parameters, this_object);
	}

	JSValue UIModule::js_createWindow(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		JSObject parameters = get_context().CreateObject();
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = _0;
		}
		return createWindow(parameters, this_object);
	}

	JSValue UIModule::js_createButton(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		JSObject parameters = get_context().CreateObject();
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = _0;
		}
		return createButton(parameters, this_object);
	}

	JSValue UIModule::js_createSlider(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		JSObject parameters = get_context().CreateObject();
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = _0;
		}
		return createSlider(parameters, this_object);
	}

	JSValue UIModule::js_createAlertDialog(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		JSObject parameters = get_context().CreateObject();
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = _0;
		}
		return createAlertDialog(parameters, this_object);
	}

	JSValue UIModule::js_createImageView(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		JSObject parameters = get_context().CreateObject();
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = _0;
		}
		return createImageView(parameters, this_object);
	}

	JSValue UIModule::js_createLabel(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		JSObject parameters = get_context().CreateObject();
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = _0;
		}
		return createLabel(parameters, this_object);
	}

	JSValue UIModule::js_createTab(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		JSObject parameters = get_context().CreateObject();
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = _0;
		}
		return createTab(parameters, this_object);
	}

	JSValue UIModule::js_createTabGroup(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		JSObject parameters = get_context().CreateObject();
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = _0;
		}
		return createTabGroup(parameters, this_object);
	}

	JSValue UIModule::js_createScrollView(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		JSObject parameters = get_context().CreateObject();
		if (arguments.size() >= 1) {
			const auto _0 = arguments.at(0);
			TITANIUM_ASSERT(_0.IsObject());
			parameters = _0;
		}
		return createScrollView(parameters, this_object);
	}

	// TODO empty implementation so that it won't break default app template. Need to implement later on.
	JSValue UIModule::js_setBackgroundColor(const std::vector<JSValue>& arguments, JSObject& this_object)
	{
		TITANIUM_LOG_DEBUG("UI::setBackgroundColor Not implemented");
		return get_context().CreateUndefined();
	}

}  // namespace Titanium {
