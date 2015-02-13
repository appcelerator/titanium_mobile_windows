/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_HPP_
#define _TITANIUM_UI_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UI/AlertDialog.hpp"
#include "Titanium/UI/Button.hpp" 
#include "Titanium/UI/ImageView.hpp"
#include "Titanium/UI/Label.hpp"
#include "Titanium/UI/ScrollView.hpp"
#include "Titanium/UI/Slider.hpp"
#include "Titanium/UI/TextField.hpp"
#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Window.hpp"
#include "Titanium/UI/WebView.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class

	  @discussion This is the Titanium UI Module.

	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI
   */
	class TITANIUMKIT_EXPORT UIModule final : public Module, public JSExport<UIModule>
	{
	public:
		/*!
		  @method

		  @abstract createAlertDialog( [parameters] ) : Titanium.UI.AlertDialog

		  @discussion Creates and returns an instance of
		  Titanium.UI.AlertDialog.

		  @param parameters Properties to set on a new object, including
		  any defined by Titanium.UI.AlertDialog except those marked
		  not-creation or read-only.  (Dictionary<Titanium.UI.AlertDialog>)

		  @result Titanium.UI.AlertDialog
		*/
		JSObject createAlertDialog(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract createButton( [parameters] ) : Titanium.UI.Button
     
		  @discussion Creates and returns an instance of
		  Titanium.UI.Button.

		  @param parameters Properties to set on a new object, including
		  any defined by Titanium.UI.Button except those marked
		  not-creation or read-only.  (Dictionary<Titanium.UI.Button>)

		  @result Titanium.UI.Button
		*/
		JSObject createButton(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract createImageView( [parameters] ) : Titanium.UI.ImageView

		  @discussion Creates and returns an instance of
		  Titanium.UI.ImageView.

		  @param parameters Properties to set on a new object, including
		  any defined by Titanium.UI.ImageView except those marked
		  not-creation or read-only.  (Dictionary<Titanium.UI.ImageView>)

		  @result Titanium.UI.ImageView
		*/
		JSObject createImageView(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract createLabel( [parameters] ) : Titanium.UI.Label

		  @discussion Creates and returns an instance of
		  Titanium.UI.Label.

		  @param parameters Properties to set on a new object, including
		  any defined by Titanium.UI.Label except those marked
		  not-creation or read-only.  (Dictionary<Titanium.UI.Label>)

		  @result Titanium.UI.Label
		*/
		JSObject createLabel(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract createScrolView( [parameters] ) : Titanium.UI.ScrolView

		  @discussion Creates and returns an instance of
		  Titanium.UI.ScrolView.

		  @param parameters Properties to set on a new object, including
		  any defined by Titanium.UI.ScrolView except those marked
		  not-creation or read-only.  (Dictionary<Titanium.UI.ScrolView>)

		  @result Titanium.UI.ScrolView
		*/
		JSObject createScrollView(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract createSlider( [parameters] ) : Titanium.UI.Slider

		  @discussion Creates and returns an instance of
		  Titanium.UI.Slider.

		  @param parameters Properties to set on a new object, including
		  any defined by Titanium.UI.Slider except those marked
		  not-creation or read-only.  (Dictionary<Titanium.UI.Slider>)

		  @result Titanium.UI.Slider
		*/
		JSObject createSlider(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract createTab( [parameters] ) : Titanium.UI.Tab

		  @discussion Creates and returns an instance of
		  Titanium.UI.Tab.

		  @param parameters Properties to set on a new object, including
		  any defined by Titanium.UI.Tab except those marked
		  not-creation or read-only.  (Dictionary<Titanium.UI.Tab>)

		  @result Titanium.UI.Tab
		*/
		JSObject createTab(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract createTabGroup( [parameters] ) : Titanium.UI.TabGroup

		  @discussion Creates and returns an instance of
		  Titanium.UI.TabGroup.

		  @param parameters Properties to set on a new object, including
		  any defined by Titanium.UI.TabGroup except those marked
		  not-creation or read-only.  (Dictionary<Titanium.UI.TabGroup>)

		  @result Titanium.UI.TabGroup
		*/
		JSObject createTabGroup(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract createTextField( [parameters] ) : Titanium.UI.TextField

		  @discussion Creates and returns an instance of
		  Titanium.UI.TextField.

		  @param parameters Properties to set on a new object, including
		  any defined by Titanium.UI.TextField except those marked
		  not-creation or read-only.  (Dictionary<Titanium.UI.TextField>)

		  @result Titanium.UI.TextField
		*/
		JSObject createTextField(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract createView( [parameters] ) : Titanium.UI.View

		  @discussion Creates and returns an instance of Titanium.UI.View.

		  @param parameters Properties to set on a new object, including
		  any defined by Titanium.UI.View except those marked not-creation
		  or read-only.  (Dictionary<Titanium.UI.View>)

		  @result Titanium.UI.View
		*/
		JSObject createView(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract createWindow( [parameters] ) : Titanium.UI.Window

		  @discussion Creates and returns an instance of
		  Titanium.UI.Window.

		  @param parameters Properties to set on a new object, including
		  any defined by Titanium.UI.Window except those marked
		  not-creation or read-only.  (Dictionary<Titanium.UI.Window>)

		  @result Titanium.UI.Window
		*/
		JSObject createWindow(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		/*!
		  @method

		  @abstract createWebView( [parameters] ) : Titanium.UI.WebView

		  @discussion Creates and returns an instance of
		  Titanium.UI.WebView.

		  @param parameters Properties to set on a new object, including
		  any defined by Titanium.UI.WebView except those marked
		  not-creation or read-only.  (Dictionary<Titanium.UI.WebView>)

		  @result Titanium.UI.WebView
		*/
		JSObject createWebView(const JSObject& parameters, JSObject& this_object) TITANIUM_NOEXCEPT;

		virtual JSValue ANIMATION_CURVE_EASE_IN() const TITANIUM_NOEXCEPT final;
		virtual JSValue ANIMATION_CURVE_EASE_IN_OUT() const TITANIUM_NOEXCEPT final;
		virtual JSValue ANIMATION_CURVE_EASE_OUT() const TITANIUM_NOEXCEPT final;
		virtual JSValue ANIMATION_CURVE_LINEAR() const TITANIUM_NOEXCEPT final;
		virtual JSValue AUTOLINK_ALL() const TITANIUM_NOEXCEPT final;
		virtual JSValue AUTOLINK_CALENDAR() const TITANIUM_NOEXCEPT final;
		virtual JSValue AUTOLINK_EMAIL_ADDRESSES() const TITANIUM_NOEXCEPT final;
		virtual JSValue AUTOLINK_MAP_ADDRESSES() const TITANIUM_NOEXCEPT final;
		virtual JSValue AUTOLINK_NONE() const TITANIUM_NOEXCEPT final;
		virtual JSValue AUTOLINK_PHONE_NUMBERS() const TITANIUM_NOEXCEPT final;
		virtual JSValue AUTOLINK_URLS() const TITANIUM_NOEXCEPT final;
		virtual JSValue EXTEND_EDGE_ALL() const TITANIUM_NOEXCEPT final;
		virtual JSValue EXTEND_EDGE_BOTTOM() const TITANIUM_NOEXCEPT final;
		virtual JSValue EXTEND_EDGE_LEFT() const TITANIUM_NOEXCEPT final;
		virtual JSValue EXTEND_EDGE_NONE() const TITANIUM_NOEXCEPT final;
		virtual JSValue EXTEND_EDGE_RIGHT() const TITANIUM_NOEXCEPT final;
		virtual JSValue EXTEND_EDGE_TOP() const TITANIUM_NOEXCEPT final;
		virtual JSValue FACE_DOWN() const TITANIUM_NOEXCEPT final;
		virtual JSValue FACE_UP() const TITANIUM_NOEXCEPT final;
		virtual JSValue FILL() const TITANIUM_NOEXCEPT;
		virtual JSValue INHERIT() const TITANIUM_NOEXCEPT;
		virtual JSValue INPUT_BORDERSTYLE_BEZEL() const TITANIUM_NOEXCEPT final;
		virtual JSValue INPUT_BORDERSTYLE_LINE() const TITANIUM_NOEXCEPT final;
		virtual JSValue INPUT_BORDERSTYLE_NONE() const TITANIUM_NOEXCEPT final;
		virtual JSValue INPUT_BORDERSTYLE_ROUNDED() const TITANIUM_NOEXCEPT final;
		virtual JSValue INPUT_BUTTONMODE_ALWAYS() const TITANIUM_NOEXCEPT final;
		virtual JSValue INPUT_BUTTONMODE_NEVER() const TITANIUM_NOEXCEPT final;
		virtual JSValue INPUT_BUTTONMODE_ONBLUR() const TITANIUM_NOEXCEPT final;
		virtual JSValue INPUT_BUTTONMODE_ONFOCUS() const TITANIUM_NOEXCEPT final;
		virtual JSValue KEYBOARD_APPEARANCE_ALERT() const TITANIUM_NOEXCEPT final;
		virtual JSValue KEYBOARD_APPEARANCE_DEFAULT() const TITANIUM_NOEXCEPT final;
		virtual JSValue KEYBOARD_ASCII() const TITANIUM_NOEXCEPT final;
		virtual JSValue KEYBOARD_DECIMAL_PAD() const TITANIUM_NOEXCEPT final;
		virtual JSValue KEYBOARD_DEFAULT() const TITANIUM_NOEXCEPT final;
		virtual JSValue KEYBOARD_EMAIL() const TITANIUM_NOEXCEPT final;
		virtual JSValue KEYBOARD_NAMEPHONE_PAD() const TITANIUM_NOEXCEPT final;
		virtual JSValue KEYBOARD_NUMBERS_PUNCTUATION() const TITANIUM_NOEXCEPT final;
		virtual JSValue KEYBOARD_NUMBER_PAD() const TITANIUM_NOEXCEPT final;
		virtual JSValue KEYBOARD_PHONE_PAD() const TITANIUM_NOEXCEPT final;
		virtual JSValue KEYBOARD_URL() const TITANIUM_NOEXCEPT final;
		virtual JSValue LANDSCAPE_LEFT() const TITANIUM_NOEXCEPT final;
		virtual JSValue LANDSCAPE_RIGHT() const TITANIUM_NOEXCEPT final;
		virtual JSValue LIST_ACCESSORY_TYPE_CHECKMARK() const TITANIUM_NOEXCEPT final;
		virtual JSValue LIST_ACCESSORY_TYPE_DETAIL() const TITANIUM_NOEXCEPT final;
		virtual JSValue LIST_ACCESSORY_TYPE_DISCLOSURE() const TITANIUM_NOEXCEPT final;
		virtual JSValue LIST_ACCESSORY_TYPE_NONE() const TITANIUM_NOEXCEPT final;
		virtual JSValue LIST_ITEM_TEMPLATE_CONTACTS() const TITANIUM_NOEXCEPT final;
		virtual JSValue LIST_ITEM_TEMPLATE_DEFAULT() const TITANIUM_NOEXCEPT final;
		virtual JSValue LIST_ITEM_TEMPLATE_SETTINGS() const TITANIUM_NOEXCEPT final;
		virtual JSValue LIST_ITEM_TEMPLATE_SUBTITLE() const TITANIUM_NOEXCEPT final;
		virtual JSValue NOTIFICATION_DURATION_LONG() const TITANIUM_NOEXCEPT final;
		virtual JSValue NOTIFICATION_DURATION_SHORT() const TITANIUM_NOEXCEPT final;
		virtual JSValue PICKER_TYPE_COUNT_DOWN_TIMER() const TITANIUM_NOEXCEPT final;
		virtual JSValue PICKER_TYPE_DATE() const TITANIUM_NOEXCEPT final;
		virtual JSValue PICKER_TYPE_DATE_AND_TIME() const TITANIUM_NOEXCEPT final;
		virtual JSValue PICKER_TYPE_PLAIN() const TITANIUM_NOEXCEPT final;
		virtual JSValue PICKER_TYPE_TIME() const TITANIUM_NOEXCEPT final;
		virtual JSValue PORTRAIT() const TITANIUM_NOEXCEPT final;
		virtual JSValue RETURNKEY_DEFAULT() const TITANIUM_NOEXCEPT final;
		virtual JSValue RETURNKEY_DONE() const TITANIUM_NOEXCEPT final;
		virtual JSValue RETURNKEY_EMERGENCY_CALL() const TITANIUM_NOEXCEPT final;
		virtual JSValue RETURNKEY_GO() const TITANIUM_NOEXCEPT final;
		virtual JSValue RETURNKEY_GOOGLE() const TITANIUM_NOEXCEPT final;
		virtual JSValue RETURNKEY_JOIN() const TITANIUM_NOEXCEPT final;
		virtual JSValue RETURNKEY_NEXT() const TITANIUM_NOEXCEPT final;
		virtual JSValue RETURNKEY_ROUTE() const TITANIUM_NOEXCEPT final;
		virtual JSValue RETURNKEY_SEARCH() const TITANIUM_NOEXCEPT final;
		virtual JSValue RETURNKEY_SEND() const TITANIUM_NOEXCEPT final;
		virtual JSValue RETURNKEY_YAHOO() const TITANIUM_NOEXCEPT final;
		virtual JSValue SIZE() const TITANIUM_NOEXCEPT;
		virtual JSValue TEXT_ALIGNMENT_CENTER() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_ALIGNMENT_LEFT() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_ALIGNMENT_RIGHT() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_AUTOCAPITALIZATION_ALL() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_AUTOCAPITALIZATION_NONE() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_AUTOCAPITALIZATION_SENTENCES() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_AUTOCAPITALIZATION_WORDS() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_STYLE_BODY() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_STYLE_CAPTION1() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_STYLE_CAPTION2() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_STYLE_FOOTNOTE() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_STYLE_HEADLINE() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_STYLE_SUBHEADLINE() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_VERTICAL_ALIGNMENT_BOTTOM() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_VERTICAL_ALIGNMENT_CENTER() const TITANIUM_NOEXCEPT final;
		virtual JSValue TEXT_VERTICAL_ALIGNMENT_TOP() const TITANIUM_NOEXCEPT final;
		virtual JSValue UNIT_CM() const TITANIUM_NOEXCEPT final;
		virtual JSValue UNIT_DIP() const TITANIUM_NOEXCEPT final;
		virtual JSValue UNIT_IN() const TITANIUM_NOEXCEPT final;
		virtual JSValue UNIT_MM() const TITANIUM_NOEXCEPT final;
		virtual JSValue UNIT_PX() const TITANIUM_NOEXCEPT final;
		virtual JSValue UNKNOWN() const TITANIUM_NOEXCEPT final;
		virtual JSValue UPSIDE_PORTRAIT() const TITANIUM_NOEXCEPT final;
		virtual JSValue URL_ERROR_AUTHENTICATION() const TITANIUM_NOEXCEPT final;
		virtual JSValue URL_ERROR_BAD_URL() const TITANIUM_NOEXCEPT final;
		virtual JSValue URL_ERROR_CONNECT() const TITANIUM_NOEXCEPT final;
		virtual JSValue URL_ERROR_FILE() const TITANIUM_NOEXCEPT final;
		virtual JSValue URL_ERROR_FILE_NOT_FOUND() const TITANIUM_NOEXCEPT final;
		virtual JSValue URL_ERROR_HOST_LOOKUP() const TITANIUM_NOEXCEPT final;
		virtual JSValue URL_ERROR_REDIRECT_LOOP() const TITANIUM_NOEXCEPT final;
		virtual JSValue URL_ERROR_SSL_FAILED() const TITANIUM_NOEXCEPT final;
		virtual JSValue URL_ERROR_TIMEOUT() const TITANIUM_NOEXCEPT final;
		virtual JSValue URL_ERROR_UNKNOWN() const TITANIUM_NOEXCEPT final;
		virtual JSValue URL_ERROR_UNSUPPORTED_SCHEME() const TITANIUM_NOEXCEPT final;

		UIModule(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

		virtual ~UIModule() TITANIUM_NOEXCEPT;  //= default;
		UIModule(const UIModule&) = default;
		UIModule& operator=(const UIModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		UIModule(UIModule&&) = default;
		UIModule& operator=(UIModule&&) = default;
#endif

		// TODO: The following functions can automatically be generated from
		// the YAML API docs.
		static void JSExportInitialize();
		JSValue js_createAlertDialog(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_createButton(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_createImageView(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_createLabel(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_createScrollView(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_createSlider(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_createTab(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_createTabGroup(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_createTextField(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_createView(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_createWindow(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_createWebView(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_setBackgroundColor(const std::vector<JSValue>& arguments, JSObject& this_object);

	private:
		JSValue animation_curve_ease_in__;
		JSValue animation_curve_ease_in_out__;
		JSValue animation_curve_ease_out__;
		JSValue animation_curve_linear__;
		JSValue autolink_all__;
		JSValue autolink_calendar__;
		JSValue autolink_email_addresses__;
		JSValue autolink_map_addresses__;
		JSValue autolink_none__;
		JSValue autolink_phone_numbers__;
		JSValue autolink_urls__;
		JSValue extend_edge_all__;
		JSValue extend_edge_bottom__;
		JSValue extend_edge_left__;
		JSValue extend_edge_none__;
		JSValue extend_edge_right__;
		JSValue extend_edge_top__;
		JSValue face_down__;
		JSValue face_up__;
		JSValue fill__;
		JSValue inherit__;
		JSValue input_borderstyle_bezel__;
		JSValue input_borderstyle_line__;
		JSValue input_borderstyle_none__;
		JSValue input_borderstyle_rounded__;
		JSValue input_buttonmode_always__;
		JSValue input_buttonmode_never__;
		JSValue input_buttonmode_onblur__;
		JSValue input_buttonmode_onfocus__;
		JSValue keyboard_appearance_alert__;
		JSValue keyboard_appearance_default__;
		JSValue keyboard_ascii__;
		JSValue keyboard_decimal_pad__;
		JSValue keyboard_default__;
		JSValue keyboard_email__;
		JSValue keyboard_namephone_pad__;
		JSValue keyboard_numbers_punctuation__;
		JSValue keyboard_number_pad__;
		JSValue keyboard_phone_pad__;
		JSValue keyboard_url__;
		JSValue landscape_left__;
		JSValue landscape_right__;
		JSValue list_accessory_type_checkmark__;
		JSValue list_accessory_type_detail__;
		JSValue list_accessory_type_disclosure__;
		JSValue list_accessory_type_none__;
		JSValue list_item_template_contacts__;
		JSValue list_item_template_default__;
		JSValue list_item_template_settings__;
		JSValue list_item_template_subtitle__;
		JSValue notification_duration_long__;
		JSValue notification_duration_short__;
		JSValue picker_type_count_down_timer__;
		JSValue picker_type_date__;
		JSValue picker_type_date_and_time__;
		JSValue picker_type_plain__;
		JSValue picker_type_time__;
		JSValue portrait__;
		JSValue returnkey_default__;
		JSValue returnkey_done__;
		JSValue returnkey_emergency_call__;
		JSValue returnkey_go__;
		JSValue returnkey_google__;
		JSValue returnkey_join__;
		JSValue returnkey_next__;
		JSValue returnkey_route__;
		JSValue returnkey_search__;
		JSValue returnkey_send__;
		JSValue returnkey_yahoo__;
		JSValue size__;
		JSValue text_alignment_center__;
		JSValue text_alignment_left__;
		JSValue text_alignment_right__;
		JSValue text_autocapitalization_all__;
		JSValue text_autocapitalization_none__;
		JSValue text_autocapitalization_sentences__;
		JSValue text_autocapitalization_words__;
		JSValue text_style_body__;
		JSValue text_style_caption1__;
		JSValue text_style_caption2__;
		JSValue text_style_footnote__;
		JSValue text_style_headline__;
		JSValue text_style_subheadline__;
		JSValue text_vertical_alignment_bottom__;
		JSValue text_vertical_alignment_center__;
		JSValue text_vertical_alignment_top__;
		JSValue unit_cm__;
		JSValue unit_dip__;
		JSValue unit_in__;
		JSValue unit_mm__;
		JSValue unit_px__;
		JSValue unknown__;
		JSValue upside_portrait__;
		JSValue url_error_authentication__;
		JSValue url_error_bad_url__;
		JSValue url_error_connect__;
		JSValue url_error_file__;
		JSValue url_error_file_not_found__;
		JSValue url_error_host_lookup__;
		JSValue url_error_redirect_loop__;
		JSValue url_error_ssl_failed__;
		JSValue url_error_timeout__;
		JSValue url_error_unknown__;
		JSValue url_error_unsupported_scheme__;

		JSFunction createViewFunction(const JSContext& js_context, const std::string& viewClass) const TITANIUM_NOEXCEPT;
	};

}  // namespace Titanium

#endif  // _TITANIUM_UI_HPP_
