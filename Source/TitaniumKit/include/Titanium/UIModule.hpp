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

namespace Titanium
{
	namespace UI
	{
		class Window;
		class Tab;
	}

	using namespace HAL;

	/*!
	  @class

	  @discussion This is the Titanium UI Module.

	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI
   */
	class TITANIUMKIT_EXPORT UIModule : public Module, public JSExport<UIModule>
	{
	public:

		/*!
		@property
		@abstract currentTab
		@discussion Value of the `currentTab` property
		*/
		TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<Titanium::UI::Tab>, currentTab);

		/*!
		@property
		@abstract currentWindow
		@discussion Value of the `currentWindow` property
		*/
		TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<Titanium::UI::Window>, currentWindow);

		/*!
		  @property
		  @abstract backgroundColor
		  @discussion Value of the `backgroundColor` property
		*/
		TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundColor);

		/*!
		@property
		@abstract backgroundImage
		@discussion Value of the `backgroundImage` property
		*/
		TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundImage);

		TITANIUM_PROPERTY_DEF(backgroundImage);
		TITANIUM_PROPERTY_DEF(backgroundColor);
		TITANIUM_PROPERTY_DEF(currentTab);

		TITANIUM_PROPERTY_READONLY_DEF(ANIMATION_CURVE_EASE_IN);
		TITANIUM_PROPERTY_READONLY_DEF(ANIMATION_CURVE_EASE_IN_OUT);
		TITANIUM_PROPERTY_READONLY_DEF(ANIMATION_CURVE_EASE_OUT);
		TITANIUM_PROPERTY_READONLY_DEF(ANIMATION_CURVE_LINEAR);
		TITANIUM_PROPERTY_READONLY_DEF(AUTOLINK_ALL);
		TITANIUM_PROPERTY_READONLY_DEF(AUTOLINK_CALENDAR);
		TITANIUM_PROPERTY_READONLY_DEF(AUTOLINK_EMAIL_ADDRESSES);
		TITANIUM_PROPERTY_READONLY_DEF(AUTOLINK_MAP_ADDRESSES);
		TITANIUM_PROPERTY_READONLY_DEF(AUTOLINK_NONE);
		TITANIUM_PROPERTY_READONLY_DEF(AUTOLINK_PHONE_NUMBERS);
		TITANIUM_PROPERTY_READONLY_DEF(AUTOLINK_URLS);
		TITANIUM_PROPERTY_READONLY_DEF(EXTEND_EDGE_ALL);
		TITANIUM_PROPERTY_READONLY_DEF(EXTEND_EDGE_BOTTOM);
		TITANIUM_PROPERTY_READONLY_DEF(EXTEND_EDGE_LEFT);
		TITANIUM_PROPERTY_READONLY_DEF(EXTEND_EDGE_NONE);
		TITANIUM_PROPERTY_READONLY_DEF(EXTEND_EDGE_RIGHT);
		TITANIUM_PROPERTY_READONLY_DEF(EXTEND_EDGE_TOP);
		TITANIUM_PROPERTY_READONLY_DEF(FACE_DOWN);
		TITANIUM_PROPERTY_READONLY_DEF(FACE_UP);
		TITANIUM_PROPERTY_READONLY_DEF(FILL);
		TITANIUM_PROPERTY_READONLY_DEF(INHERIT);
		TITANIUM_PROPERTY_READONLY_DEF(INPUT_BORDERSTYLE_BEZEL);
		TITANIUM_PROPERTY_READONLY_DEF(INPUT_BORDERSTYLE_LINE);
		TITANIUM_PROPERTY_READONLY_DEF(INPUT_BORDERSTYLE_NONE);
		TITANIUM_PROPERTY_READONLY_DEF(INPUT_BORDERSTYLE_ROUNDED);
		TITANIUM_PROPERTY_READONLY_DEF(INPUT_BUTTONMODE_ALWAYS);
		TITANIUM_PROPERTY_READONLY_DEF(INPUT_BUTTONMODE_NEVER);
		TITANIUM_PROPERTY_READONLY_DEF(INPUT_BUTTONMODE_ONBLUR);
		TITANIUM_PROPERTY_READONLY_DEF(INPUT_BUTTONMODE_ONFOCUS);
		TITANIUM_PROPERTY_READONLY_DEF(KEYBOARD_APPEARANCE_ALERT);
		TITANIUM_PROPERTY_READONLY_DEF(KEYBOARD_APPEARANCE_DEFAULT);
		TITANIUM_PROPERTY_READONLY_DEF(KEYBOARD_ASCII);
		TITANIUM_PROPERTY_READONLY_DEF(KEYBOARD_DECIMAL_PAD);
		TITANIUM_PROPERTY_READONLY_DEF(KEYBOARD_DEFAULT);
		TITANIUM_PROPERTY_READONLY_DEF(KEYBOARD_EMAIL);
		TITANIUM_PROPERTY_READONLY_DEF(KEYBOARD_NAMEPHONE_PAD);
		TITANIUM_PROPERTY_READONLY_DEF(KEYBOARD_NUMBERS_PUNCTUATION);
		TITANIUM_PROPERTY_READONLY_DEF(KEYBOARD_NUMBER_PAD);
		TITANIUM_PROPERTY_READONLY_DEF(KEYBOARD_PHONE_PAD);
		TITANIUM_PROPERTY_READONLY_DEF(KEYBOARD_URL);
		TITANIUM_PROPERTY_READONLY_DEF(LANDSCAPE_LEFT);
		TITANIUM_PROPERTY_READONLY_DEF(LANDSCAPE_RIGHT);
		TITANIUM_PROPERTY_READONLY_DEF(LIST_ACCESSORY_TYPE_CHECKMARK);
		TITANIUM_PROPERTY_READONLY_DEF(LIST_ACCESSORY_TYPE_DETAIL);
		TITANIUM_PROPERTY_READONLY_DEF(LIST_ACCESSORY_TYPE_DISCLOSURE);
		TITANIUM_PROPERTY_READONLY_DEF(LIST_ACCESSORY_TYPE_NONE);
		TITANIUM_PROPERTY_READONLY_DEF(LIST_ITEM_TEMPLATE_CONTACTS);
		TITANIUM_PROPERTY_READONLY_DEF(LIST_ITEM_TEMPLATE_DEFAULT);
		TITANIUM_PROPERTY_READONLY_DEF(LIST_ITEM_TEMPLATE_SETTINGS);
		TITANIUM_PROPERTY_READONLY_DEF(LIST_ITEM_TEMPLATE_SUBTITLE);
		TITANIUM_PROPERTY_READONLY_DEF(NOTIFICATION_DURATION_LONG);
		TITANIUM_PROPERTY_READONLY_DEF(NOTIFICATION_DURATION_SHORT);
		TITANIUM_PROPERTY_READONLY_DEF(PICKER_TYPE_COUNT_DOWN_TIMER);
		TITANIUM_PROPERTY_READONLY_DEF(PICKER_TYPE_DATE);
		TITANIUM_PROPERTY_READONLY_DEF(PICKER_TYPE_DATE_AND_TIME);
		TITANIUM_PROPERTY_READONLY_DEF(PICKER_TYPE_PLAIN);
		TITANIUM_PROPERTY_READONLY_DEF(PICKER_TYPE_TIME);
		TITANIUM_PROPERTY_READONLY_DEF(PORTRAIT);
		TITANIUM_PROPERTY_READONLY_DEF(RETURNKEY_DEFAULT);
		TITANIUM_PROPERTY_READONLY_DEF(RETURNKEY_DONE);
		TITANIUM_PROPERTY_READONLY_DEF(RETURNKEY_EMERGENCY_CALL);
		TITANIUM_PROPERTY_READONLY_DEF(RETURNKEY_GO);
		TITANIUM_PROPERTY_READONLY_DEF(RETURNKEY_GOOGLE);
		TITANIUM_PROPERTY_READONLY_DEF(RETURNKEY_JOIN);
		TITANIUM_PROPERTY_READONLY_DEF(RETURNKEY_NEXT);
		TITANIUM_PROPERTY_READONLY_DEF(RETURNKEY_ROUTE);
		TITANIUM_PROPERTY_READONLY_DEF(RETURNKEY_SEARCH);
		TITANIUM_PROPERTY_READONLY_DEF(RETURNKEY_SEND);
		TITANIUM_PROPERTY_READONLY_DEF(RETURNKEY_YAHOO);
		TITANIUM_PROPERTY_READONLY_DEF(SIZE);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_ALIGNMENT_CENTER);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_ALIGNMENT_LEFT);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_ALIGNMENT_RIGHT);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_ALIGNMENT_JUSTIFY);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_AUTOCAPITALIZATION_ALL);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_AUTOCAPITALIZATION_NONE);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_AUTOCAPITALIZATION_SENTENCES);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_AUTOCAPITALIZATION_WORDS);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_STYLE_BODY);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_STYLE_CAPTION1);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_STYLE_CAPTION2);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_STYLE_FOOTNOTE);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_STYLE_HEADLINE);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_STYLE_SUBHEADLINE);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_VERTICAL_ALIGNMENT_BOTTOM);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_VERTICAL_ALIGNMENT_CENTER);
		TITANIUM_PROPERTY_READONLY_DEF(TEXT_VERTICAL_ALIGNMENT_TOP);
		TITANIUM_PROPERTY_READONLY_DEF(UNIT_CM);
		TITANIUM_PROPERTY_READONLY_DEF(UNIT_DIP);
		TITANIUM_PROPERTY_READONLY_DEF(UNIT_IN);
		TITANIUM_PROPERTY_READONLY_DEF(UNIT_MM);
		TITANIUM_PROPERTY_READONLY_DEF(UNIT_PX);
		TITANIUM_PROPERTY_READONLY_DEF(UNKNOWN);
		TITANIUM_PROPERTY_READONLY_DEF(UPSIDE_PORTRAIT);
		TITANIUM_PROPERTY_READONLY_DEF(URL_ERROR_AUTHENTICATION);
		TITANIUM_PROPERTY_READONLY_DEF(URL_ERROR_BAD_URL);
		TITANIUM_PROPERTY_READONLY_DEF(URL_ERROR_CONNECT);
		TITANIUM_PROPERTY_READONLY_DEF(URL_ERROR_FILE);
		TITANIUM_PROPERTY_READONLY_DEF(URL_ERROR_FILE_NOT_FOUND);
		TITANIUM_PROPERTY_READONLY_DEF(URL_ERROR_HOST_LOOKUP);
		TITANIUM_PROPERTY_READONLY_DEF(URL_ERROR_REDIRECT_LOOP);
		TITANIUM_PROPERTY_READONLY_DEF(URL_ERROR_SSL_FAILED);
		TITANIUM_PROPERTY_READONLY_DEF(URL_ERROR_TIMEOUT);
		TITANIUM_PROPERTY_READONLY_DEF(URL_ERROR_UNKNOWN);
		TITANIUM_PROPERTY_READONLY_DEF(URL_ERROR_UNSUPPORTED_SCHEME);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_FONT);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_FOREGROUND_COLOR);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_BACKGROUND_COLOR);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_STRIKETHROUGH_STYLE);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_UNDERLINES_STYLE);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_LINK);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_UNDERLINE_COLOR);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_KERN);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_STROKE_COLOR);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_STROKE_WIDTH);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_SHADOW);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_WRITING_DIRECTION);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_TEXT_EFFECT);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_BASELINE_OFFSET);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_STRIKETHROUGH_COLOR);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_OBLIQUENESS);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_EXPANSION);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_LINE_BREAK);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_UNDERLINE_STYLE_NONE);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_UNDERLINE_STYLE_SINGLE);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_UNDERLINE_STYLE_THICK);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_UNDERLINE_STYLE_DOUBLE);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_UNDERLINE_PATTERN_SOLID);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_UNDERLINE_PATTERN_DOT);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_UNDERLINE_PATTERN_DASH);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_UNDERLINE_PATTERN_DASH_DOT);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_UNDERLINE_PATTERN_DASH_DOT_DOT);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_UNDERLINE_BY_WORD);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_WRITING_DIRECTION_EMBEDDING);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_WRITING_DIRECTION_OVERRIDE);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_WRITING_DIRECTION_NATURAL);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_WRITING_DIRECTION_LEFT_TO_RIGHT);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_WRITING_DIRECTION_RIGHT_TO_LEFT);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_LETTERPRESS_STYLE);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_LINE_BREAK_BY_WORD_WRAPPING);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_LINE_BREAK_BY_CHAR_WRAPPING);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_LINE_BREAK_BY_CLIPPING);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_LINE_BREAK_BY_TRUNCATING_HEAD);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_LINE_BREAK_BY_TRUNCATING_TAIL);
		TITANIUM_PROPERTY_READONLY_DEF(ATTRIBUTE_LINE_BREAK_BY_TRUNCATING_MIDDLE);
		TITANIUM_PROPERTY_READONLY_DEF(2DMatrix);
		TITANIUM_PROPERTY_READONLY_DEF(ActivityIndicator);
		TITANIUM_PROPERTY_READONLY_DEF(ActivityIndicatorStyle);
		TITANIUM_PROPERTY_READONLY_DEF(AlertDialog);
		TITANIUM_PROPERTY_READONLY_DEF(Animation);
		TITANIUM_PROPERTY_READONLY_DEF(AttributedString);
		TITANIUM_PROPERTY_READONLY_DEF(Button);
		TITANIUM_PROPERTY_READONLY_DEF(Clipboard);
		TITANIUM_PROPERTY_READONLY_DEF(EmailDialog);
		TITANIUM_PROPERTY_READONLY_DEF(ImageView);
		TITANIUM_PROPERTY_READONLY_DEF(Label);
		TITANIUM_PROPERTY_READONLY_DEF(ListView);
		TITANIUM_PROPERTY_READONLY_DEF(ListSection);
		TITANIUM_PROPERTY_READONLY_DEF(NavigationWindow);
		TITANIUM_PROPERTY_READONLY_DEF(Notification);
		TITANIUM_PROPERTY_READONLY_DEF(OptionDialog);
		TITANIUM_PROPERTY_READONLY_DEF(ProgressBar);
		TITANIUM_PROPERTY_READONLY_DEF(Picker);
		TITANIUM_PROPERTY_READONLY_DEF(PickerRow);
		TITANIUM_PROPERTY_READONLY_DEF(PickerColumn);
		TITANIUM_PROPERTY_READONLY_DEF(ScrollableView);
		TITANIUM_PROPERTY_READONLY_DEF(ScrollView);
		TITANIUM_PROPERTY_READONLY_DEF(SearchBar);
		TITANIUM_PROPERTY_READONLY_DEF(Slider);
		TITANIUM_PROPERTY_READONLY_DEF(Switch);
		TITANIUM_PROPERTY_READONLY_DEF(Tab);
		TITANIUM_PROPERTY_READONLY_DEF(TabGroup);
		TITANIUM_PROPERTY_READONLY_DEF(TableView);
		TITANIUM_PROPERTY_READONLY_DEF(TableViewSection);
		TITANIUM_PROPERTY_READONLY_DEF(TableViewRow);
		TITANIUM_PROPERTY_READONLY_DEF(TextArea);
		TITANIUM_PROPERTY_READONLY_DEF(TextField);
		TITANIUM_PROPERTY_READONLY_DEF(View);
		TITANIUM_PROPERTY_READONLY_DEF(WebView);
		TITANIUM_PROPERTY_READONLY_DEF(Window);

		UIModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~UIModule() TITANIUM_NOEXCEPT;  //= default;
		UIModule(const UIModule&) = default;
		UIModule& operator=(const UIModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		UIModule(UIModule&&) = default;
		UIModule& operator=(UIModule&&) = default;
#endif

		static void JSExportInitialize();

		TITANIUM_FUNCTION_DEF(create2DMatrix);
		TITANIUM_FUNCTION_DEF(createActivityIndicator);
		TITANIUM_FUNCTION_DEF(createAlertDialog);
		TITANIUM_FUNCTION_DEF(createAnimation);
		TITANIUM_FUNCTION_DEF(createAttributedString);
		TITANIUM_FUNCTION_DEF(createButton);
		TITANIUM_FUNCTION_DEF(createEmailDialog);
		TITANIUM_FUNCTION_DEF(createImageView);
		TITANIUM_FUNCTION_DEF(createLabel);
		TITANIUM_FUNCTION_DEF(createListItem);
		TITANIUM_FUNCTION_DEF(createListSection);
		TITANIUM_FUNCTION_DEF(createListView);
		TITANIUM_FUNCTION_DEF(createNavigationWindow);
		TITANIUM_FUNCTION_DEF(createNotification);
		TITANIUM_FUNCTION_DEF(createOptionDialog);
		TITANIUM_FUNCTION_DEF(createPicker);
		TITANIUM_FUNCTION_DEF(createPickerRow);
		TITANIUM_FUNCTION_DEF(createPickerColumn);
		TITANIUM_FUNCTION_DEF(createProgressBar);
		TITANIUM_FUNCTION_DEF(createScrollableView);
		TITANIUM_FUNCTION_DEF(createScrollView);
		TITANIUM_FUNCTION_DEF(createSearchBar);
		TITANIUM_FUNCTION_DEF(createSlider);
		TITANIUM_FUNCTION_DEF(createSwitch);
		TITANIUM_FUNCTION_DEF(createTab);
		TITANIUM_FUNCTION_DEF(createTabGroup);
		TITANIUM_FUNCTION_DEF(createTableView);
		TITANIUM_FUNCTION_DEF(createTableViewRow);
		TITANIUM_FUNCTION_DEF(createTableViewSection);
		TITANIUM_FUNCTION_DEF(createTextArea);
		TITANIUM_FUNCTION_DEF(createTextField);
		TITANIUM_FUNCTION_DEF(createView);
		TITANIUM_FUNCTION_DEF(createWebView);
		TITANIUM_FUNCTION_DEF(createWindow);

		TITANIUM_FUNCTION_DEF(getBackgroundColor);
		TITANIUM_FUNCTION_DEF(setBackgroundColor);
		TITANIUM_FUNCTION_DEF(getBackgroundImage);
		TITANIUM_FUNCTION_DEF(setBackgroundImage);
		TITANIUM_FUNCTION_DEF(getCurrentTab);
		TITANIUM_FUNCTION_DEF(setCurrentTab);

		UIModule& ListViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& ListSectionClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& EmailDialogClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& AnimationClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& SwitchClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& TwoDMatrixClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& NavigationWindowClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& NotificationClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& TextAreaClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& ClipboardClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& PickerClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& PickerColumnClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& PickerRowClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& ViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& WindowClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& ButtonClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& ImageViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& LabelClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& SliderClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& AlertDialogClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& ScrollViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& TextFieldClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& WebViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& Tab(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& TabGroup(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& TableViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& TableViewSectionClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& TableViewRowClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& ActivityIndicatorClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& ActivityIndicatorStyleClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& OptionDialogClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& ProgressBarClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& ScrollableViewClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& SearchBarClass(const JSClass&) TITANIUM_NOEXCEPT;
		UIModule& AttributedStringClass(const JSClass&) TITANIUM_NOEXCEPT;

	protected:

#pragma warning(push)
#pragma warning(disable: 4251)
		std::shared_ptr<Titanium::UI::Tab> currentTab__;
		std::shared_ptr<Titanium::UI::Window> currentWindow__;

		std::string backgroundColor__;
		std::string backgroundImage__;

		JSClass view__;
		JSClass pickerrow__;
		JSClass pickercolumn__;
		JSClass picker__;
		JSClass clipboard__;
		JSClass textarea__;
		JSClass navigationWindow__;
		JSClass notification__;
		JSClass twodmatrix__;
		JSClass switch__;
		JSClass utils__;
		JSClass animation__;
		JSClass listsection__;
		JSClass listview__;
		JSClass emaildialog__;
		JSClass window__;
		JSClass button__;
		JSClass alertDialog__;
		JSClass imageview__;
		JSClass label__;
		JSClass slider__;
		JSClass scrollview__;
		JSClass textField__;
		JSClass webview__;
		JSClass tab__;
		JSClass tabgroup__;
		JSClass tableview__;
		JSClass tableviewsection__;
		JSClass tableviewrow__;
		JSClass activityIndicator__;
		JSClass activityIndicatorStyle__;
		JSClass optionDialog__;
		JSClass progressBar__;
		JSClass scrollableView__;
		JSClass searchBar__;
		JSClass attributedString__;

#pragma warning(pop)

	};

}  // namespace Titanium

#endif  // _TITANIUM_UI_HPP_
