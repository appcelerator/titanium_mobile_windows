/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UIModule.hpp"
#include <sstream>

#define CREATE_TITANIUM_UI(NAME) \
  JSValue Titanium_property = this_object.get_context().get_global_object().GetProperty("Titanium"); \
  TITANIUM_ASSERT(Titanium_property.IsObject()); \
  JSObject Titanium = static_cast<JSObject>(Titanium_property); \
  JSValue UI_property = Titanium.GetProperty("UI"); \
  TITANIUM_ASSERT(UI_property.IsObject()); \
  JSObject UI = static_cast<JSObject>(UI_property); \
  JSValue NAME##_property = UI.GetProperty(#NAME); \
  TITANIUM_ASSERT(NAME##_property.IsObject()); \
  JSObject NAME = static_cast<JSObject>(NAME##_property); \
  auto NAME##_obj = NAME.CallAsConstructor(parameters); \
  Titanium::applyProperties(NAME##_obj, parameters); \
  return NAME##_obj;

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
		TITANIUM_LOG_DEBUG("UIModule:: ctor ", this);
	}

	UIModule::~UIModule() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("UIModule:: dtor ", this);
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

		return static_cast<JSObject>(get_context().CreateFunction(script, { "_arguments" })({ parameters }, this_object));
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

      _tab.__ti_private__.title.addEventListener('postlayout', function() {
          self.__ti_private__.bar.height =  _tab.__ti_private__.title.size.height;
      });

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
		return static_cast<JSObject>(get_context().CreateFunction(script, { "_arguments" })({ parameters }, this_object));
	}

	TITANIUM_PROPERTY_GETTER(UIModule, ANIMATION_CURVE_EASE_IN)
	{
		return animation_curve_ease_in__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ANIMATION_CURVE_EASE_IN_OUT)
	{
		return animation_curve_ease_in_out__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ANIMATION_CURVE_EASE_OUT)
	{
		return animation_curve_ease_out__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, ANIMATION_CURVE_LINEAR)
	{
		return animation_curve_linear__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_ALL)
	{
		return autolink_all__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_CALENDAR)
	{
		return autolink_calendar__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_EMAIL_ADDRESSES)
	{
		return autolink_email_addresses__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_MAP_ADDRESSES)
	{
		return autolink_map_addresses__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_NONE)
	{
		return autolink_none__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_PHONE_NUMBERS)
	{
		return autolink_phone_numbers__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, AUTOLINK_URLS)
	{
		return autolink_urls__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, EXTEND_EDGE_ALL)
	{
		return extend_edge_all__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, EXTEND_EDGE_BOTTOM)
	{
		return extend_edge_bottom__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, EXTEND_EDGE_LEFT)
	{
		return extend_edge_left__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, EXTEND_EDGE_NONE)
	{
		return extend_edge_none__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, EXTEND_EDGE_RIGHT)
	{
		return extend_edge_right__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, EXTEND_EDGE_TOP)
	{
		return extend_edge_top__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, FACE_DOWN)
	{
		return face_down__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, FACE_UP)
	{
		return face_up__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, FILL)
	{
		return fill__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INHERIT)
	{
		return inherit__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BORDERSTYLE_BEZEL)
	{
		return input_borderstyle_bezel__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BORDERSTYLE_LINE)
	{
		return input_borderstyle_line__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BORDERSTYLE_NONE)
	{
		return input_borderstyle_none__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BORDERSTYLE_ROUNDED)
	{
		return input_borderstyle_rounded__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BUTTONMODE_ALWAYS)
	{
		return input_buttonmode_always__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BUTTONMODE_NEVER)
	{
		return input_buttonmode_never__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BUTTONMODE_ONBLUR)
	{
		return input_buttonmode_onblur__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, INPUT_BUTTONMODE_ONFOCUS)
	{
		return input_buttonmode_onfocus__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_APPEARANCE_ALERT)
	{
		return keyboard_appearance_alert__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_APPEARANCE_DEFAULT)
	{
		return keyboard_appearance_default__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_ASCII)
	{
		return keyboard_ascii__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_DECIMAL_PAD)
	{
		return keyboard_decimal_pad__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_DEFAULT)
	{
		return keyboard_default__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_EMAIL)
	{
		return keyboard_email__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_NAMEPHONE_PAD)
	{
		return keyboard_namephone_pad__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_NUMBERS_PUNCTUATION)
	{
		return keyboard_numbers_punctuation__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_NUMBER_PAD)
	{
		return keyboard_number_pad__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_PHONE_PAD)
	{
		return keyboard_phone_pad__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, KEYBOARD_URL)
	{
		return keyboard_url__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LANDSCAPE_LEFT)
	{
		return landscape_left__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LANDSCAPE_RIGHT)
	{
		return landscape_right__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ACCESSORY_TYPE_CHECKMARK)
	{
		return list_accessory_type_checkmark__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ACCESSORY_TYPE_DETAIL)
	{
		return list_accessory_type_detail__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ACCESSORY_TYPE_DISCLOSURE)
	{
		return list_accessory_type_disclosure__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ACCESSORY_TYPE_NONE)
	{
		return list_accessory_type_none__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ITEM_TEMPLATE_CONTACTS)
	{
		return list_item_template_contacts__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ITEM_TEMPLATE_DEFAULT)
	{
		return list_item_template_default__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ITEM_TEMPLATE_SETTINGS)
	{
		return list_item_template_settings__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, LIST_ITEM_TEMPLATE_SUBTITLE)
	{
		return list_item_template_subtitle__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, NOTIFICATION_DURATION_LONG)
	{
		return notification_duration_long__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, NOTIFICATION_DURATION_SHORT)
	{
		return notification_duration_short__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, PICKER_TYPE_COUNT_DOWN_TIMER)
	{
		return picker_type_count_down_timer__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, PICKER_TYPE_DATE)
	{
		return picker_type_date__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, PICKER_TYPE_DATE_AND_TIME)
	{
		return picker_type_date_and_time__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, PICKER_TYPE_PLAIN)
	{
		return picker_type_plain__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, PICKER_TYPE_TIME)
	{
		return picker_type_time__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, PORTRAIT)
	{
		return portrait__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_DEFAULT)
	{
		return returnkey_default__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_DONE)
	{
		return returnkey_done__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_EMERGENCY_CALL)
	{
		return returnkey_emergency_call__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_GO)
	{
		return returnkey_go__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_GOOGLE)
	{
		return returnkey_google__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_JOIN)
	{
		return returnkey_join__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_NEXT)
	{
		return returnkey_next__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_ROUTE)
	{
		return returnkey_route__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_SEARCH)
	{
		return returnkey_search__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_SEND)
	{
		return returnkey_send__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, RETURNKEY_YAHOO)
	{
		return returnkey_yahoo__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, SIZE)
	{
		return size__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ALIGNMENT_CENTER)
	{
		return text_alignment_center__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ALIGNMENT_LEFT)
	{
		return text_alignment_left__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_ALIGNMENT_RIGHT)
	{
		return text_alignment_right__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_AUTOCAPITALIZATION_ALL)
	{
		return text_autocapitalization_all__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_AUTOCAPITALIZATION_NONE)
	{
		return text_autocapitalization_none__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_AUTOCAPITALIZATION_SENTENCES)
	{
		return text_autocapitalization_sentences__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_AUTOCAPITALIZATION_WORDS)
	{
		return text_autocapitalization_words__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_STYLE_BODY)
	{
		return text_style_body__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_STYLE_CAPTION1)
	{
		return text_style_caption1__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_STYLE_CAPTION2)
	{
		return text_style_caption2__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_STYLE_FOOTNOTE)
	{
		return text_style_footnote__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_STYLE_HEADLINE)
	{
		return text_style_headline__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_STYLE_SUBHEADLINE)
	{
		return text_style_subheadline__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_VERTICAL_ALIGNMENT_BOTTOM)
	{
		return text_vertical_alignment_bottom__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_VERTICAL_ALIGNMENT_CENTER)
	{
		return text_vertical_alignment_center__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, TEXT_VERTICAL_ALIGNMENT_TOP)
	{
		return text_vertical_alignment_top__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNIT_CM)
	{
		return unit_cm__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNIT_DIP)
	{
		return unit_dip__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNIT_IN)
	{
		return unit_in__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNIT_MM)
	{
		return unit_mm__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNIT_PX)
	{
		return unit_px__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UNKNOWN)
	{
		return unknown__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, UPSIDE_PORTRAIT)
	{
		return upside_portrait__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_AUTHENTICATION)
	{
		return url_error_authentication__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_BAD_URL)
	{
		return url_error_bad_url__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_CONNECT)
	{
		return url_error_connect__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_FILE)
	{
		return url_error_file__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_FILE_NOT_FOUND)
	{
		return url_error_file_not_found__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_HOST_LOOKUP)
	{
		return url_error_host_lookup__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_REDIRECT_LOOP)
	{
		return url_error_redirect_loop__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_SSL_FAILED)
	{
		return url_error_ssl_failed__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_TIMEOUT)
	{
		return url_error_timeout__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_UNKNOWN)
	{
		return url_error_unknown__;
	}
	TITANIUM_PROPERTY_GETTER(UIModule, URL_ERROR_UNSUPPORTED_SCHEME)
	{
		return url_error_unsupported_scheme__;
	}

	// TODO: The following functions can automatically be generated from
	// the YAML API docs.

	void UIModule::JSExportInitialize()
	{
		JSExport<UIModule>::SetClassVersion(1);
		JSExport<UIModule>::SetParent(JSExport<Module>::Class());
		TITANIUM_ADD_FUNCTION(UIModule, createAlertDialog);
		TITANIUM_ADD_FUNCTION(UIModule, createButton);
		TITANIUM_ADD_FUNCTION(UIModule, createEmailDialog);
		TITANIUM_ADD_FUNCTION(UIModule, createImageView);
		TITANIUM_ADD_FUNCTION(UIModule, createLabel);
		TITANIUM_ADD_FUNCTION(UIModule, createScrollView);
		TITANIUM_ADD_FUNCTION(UIModule, createSlider);
		TITANIUM_ADD_FUNCTION(UIModule, createSwitch);
		TITANIUM_ADD_FUNCTION(UIModule, createTab);
		TITANIUM_ADD_FUNCTION(UIModule, createTabGroup);
		TITANIUM_ADD_FUNCTION(UIModule, createTextField);
		TITANIUM_ADD_FUNCTION(UIModule, createView);
		TITANIUM_ADD_FUNCTION(UIModule, createWindow);
		TITANIUM_ADD_FUNCTION(UIModule, createListView);
		TITANIUM_ADD_FUNCTION(UIModule, createListSection);
		TITANIUM_ADD_FUNCTION(UIModule, createListItem);
		TITANIUM_ADD_FUNCTION(UIModule, createWebView);
		TITANIUM_ADD_FUNCTION(UIModule, createTableView);
		TITANIUM_ADD_FUNCTION(UIModule, createTableViewSection);
		TITANIUM_ADD_FUNCTION(UIModule, createTableViewRow);
		TITANIUM_ADD_FUNCTION(UIModule, setBackgroundColor);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, ANIMATION_CURVE_EASE_IN);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, ANIMATION_CURVE_EASE_IN_OUT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, ANIMATION_CURVE_EASE_OUT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, ANIMATION_CURVE_LINEAR);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, AUTOLINK_ALL);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, AUTOLINK_CALENDAR);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, AUTOLINK_EMAIL_ADDRESSES);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, AUTOLINK_MAP_ADDRESSES);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, AUTOLINK_NONE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, AUTOLINK_PHONE_NUMBERS);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, AUTOLINK_URLS);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, EXTEND_EDGE_ALL);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, EXTEND_EDGE_BOTTOM);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, EXTEND_EDGE_LEFT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, EXTEND_EDGE_NONE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, EXTEND_EDGE_RIGHT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, EXTEND_EDGE_TOP);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, FACE_DOWN);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, FACE_UP);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, FILL);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, INHERIT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, INPUT_BORDERSTYLE_BEZEL);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, INPUT_BORDERSTYLE_LINE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, INPUT_BORDERSTYLE_NONE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, INPUT_BORDERSTYLE_ROUNDED);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, INPUT_BUTTONMODE_ALWAYS);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, INPUT_BUTTONMODE_NEVER);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, INPUT_BUTTONMODE_ONBLUR);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, INPUT_BUTTONMODE_ONFOCUS);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, KEYBOARD_APPEARANCE_ALERT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, KEYBOARD_APPEARANCE_DEFAULT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, KEYBOARD_ASCII);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, KEYBOARD_DECIMAL_PAD);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, KEYBOARD_DEFAULT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, KEYBOARD_EMAIL);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, KEYBOARD_NAMEPHONE_PAD);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, KEYBOARD_NUMBERS_PUNCTUATION);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, KEYBOARD_NUMBER_PAD);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, KEYBOARD_PHONE_PAD);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, KEYBOARD_URL);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, LANDSCAPE_LEFT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, LANDSCAPE_RIGHT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, LIST_ACCESSORY_TYPE_CHECKMARK);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, LIST_ACCESSORY_TYPE_DETAIL);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, LIST_ACCESSORY_TYPE_DISCLOSURE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, LIST_ACCESSORY_TYPE_NONE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, LIST_ITEM_TEMPLATE_CONTACTS);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, LIST_ITEM_TEMPLATE_DEFAULT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, LIST_ITEM_TEMPLATE_SETTINGS);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, LIST_ITEM_TEMPLATE_SUBTITLE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, NOTIFICATION_DURATION_LONG);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, NOTIFICATION_DURATION_SHORT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, PICKER_TYPE_COUNT_DOWN_TIMER);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, PICKER_TYPE_DATE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, PICKER_TYPE_DATE_AND_TIME);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, PICKER_TYPE_PLAIN);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, PICKER_TYPE_TIME);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, PORTRAIT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, RETURNKEY_DEFAULT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, RETURNKEY_DONE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, RETURNKEY_EMERGENCY_CALL);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, RETURNKEY_GO);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, RETURNKEY_GOOGLE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, RETURNKEY_JOIN);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, RETURNKEY_NEXT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, RETURNKEY_ROUTE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, RETURNKEY_SEARCH);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, RETURNKEY_SEND);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, RETURNKEY_YAHOO);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, SIZE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_ALIGNMENT_CENTER);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_ALIGNMENT_LEFT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_ALIGNMENT_RIGHT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_AUTOCAPITALIZATION_ALL);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_AUTOCAPITALIZATION_NONE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_AUTOCAPITALIZATION_SENTENCES);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_AUTOCAPITALIZATION_WORDS);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_STYLE_BODY);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_STYLE_CAPTION1);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_STYLE_CAPTION2);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_STYLE_FOOTNOTE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_STYLE_HEADLINE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_STYLE_SUBHEADLINE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_VERTICAL_ALIGNMENT_BOTTOM);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_VERTICAL_ALIGNMENT_CENTER);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, TEXT_VERTICAL_ALIGNMENT_TOP);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, UNIT_CM);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, UNIT_DIP);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, UNIT_IN);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, UNIT_MM);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, UNIT_PX);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, UNKNOWN);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, UPSIDE_PORTRAIT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, URL_ERROR_AUTHENTICATION);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, URL_ERROR_BAD_URL);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, URL_ERROR_CONNECT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, URL_ERROR_FILE);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, URL_ERROR_FILE_NOT_FOUND);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, URL_ERROR_HOST_LOOKUP);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, URL_ERROR_REDIRECT_LOOP);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, URL_ERROR_SSL_FAILED);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, URL_ERROR_TIMEOUT);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, URL_ERROR_UNKNOWN);
		TITANIUM_ADD_PROPERTY_READONLY(UIModule, URL_ERROR_UNSUPPORTED_SCHEME);
	}

	TITANIUM_FUNCTION(UIModule, createAlertDialog)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(AlertDialog);
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

	TITANIUM_FUNCTION(UIModule, createScrollView)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(ScrollView);
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
		return createTab(parameters, this_object);
	}

	TITANIUM_FUNCTION(UIModule, createTabGroup)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		return createTabGroup(parameters, this_object);
	}

	TITANIUM_FUNCTION(UIModule, createTextField)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(TextField);
	}

	TITANIUM_FUNCTION(UIModule, createListView)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(ListView);
	}

	TITANIUM_FUNCTION(UIModule, createListSection)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(ListSection);
	}

	TITANIUM_FUNCTION(UIModule, createListItem)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(ListItem);
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

	TITANIUM_FUNCTION(UIModule, createWebView)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(WebView);
	}

	TITANIUM_FUNCTION(UIModule, createTableView)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(TableView);
	}

	TITANIUM_FUNCTION(UIModule, createTableViewSection)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(TableViewSection);
	}

	TITANIUM_FUNCTION(UIModule, createTableViewRow)
	{
		ENSURE_OPTIONAL_OBJECT_AT_INDEX(parameters, 0);
		CREATE_TITANIUM_UI(TableViewRow);
	}

	// TODO empty implementation so that it won't break default app template. Need to implement later on.
	TITANIUM_FUNCTION(UIModule, setBackgroundColor)
	{
		TITANIUM_LOG_DEBUG("UI::setBackgroundColor Not implemented");
		return this_object.get_context().CreateUndefined();
	}

}  // namespace Titanium
