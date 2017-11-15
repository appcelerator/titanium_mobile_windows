/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_CONSTANTS_HPP_
#define _TITANIUM_UI_CONSTANTS_HPP_

#include "Titanium/detail/TiBase.hpp"
#include <unordered_set>
#include <functional>

namespace Titanium
{
	namespace UI
	{
		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.Animation.curve property.

		  @constant EASE_IN Specify that an animation that starts slowly and
		  speeds up.

		  @constant EASE_IN_OUT Specify that an animation that starts slowly,
		  and speeds up, then slows down at the end of the animation.

		  @constant EASE_OUT Specify that an animation that starts quickly,
		  then slows down at the end of the animation.

		  @constant CURVE_LINEAR Specify that an animation that proceeds at a
		  constant rate.
		*/
		enum class TITANIUMKIT_EXPORT ANIMATION_CURVE {
			EASE_IN,
			EASE_IN_OUT,
			EASE_OUT,
			LINEAR
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.TextArea.autoLink property.

		  @constant ALL Converts all detectable types of data into clickable
		  links.

		  @constant CALENDAR Converts strings formatted as calendar events
		  into clickable links.

		  @constant EMAIL_ADDRESSES Converts strings formatted as email
		  addresses into clickable links.

		  @constant MAP_ADDRESSES Converts strings formatted as addresses
		  into clickable links.

		  @constant NONE Disables converting strings into clickable links.

		  @constant PHONE_NUMBERS Converts strings formatted as phone numbers
		  into clickable links.

		  @constant URLS Converts strings formatted as URLs into clickable
		  links. This property will also convert strings formatted as email
		  addresses into clickable links.
		*/
		enum class TITANIUMKIT_EXPORT AUTOLINK {
			ALL = 1 << 0,              // 1 << 0 == 1
			CALENDAR = 1 << 1,         // 1 << 1 == 2
			EMAIL_ADDRESSES = 1 << 2,  // 1 << 2 == 4
			MAP_ADDRESSES = 1 << 3,    // 1 << 3 == 8
			NONE = 1 << 4,             // 1 << 4 == 16
			PHONE_NUMBERS = 1 << 5,    // 1 << 5 == 32
			URLS = 1 << 6              // 1 << 6 == 64
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.Window.extendEdges property.

		  @constant ALL Specifies that all the edges of the window can
		  extend.

		  @constant BOTTOM Specifies that the bottom edge of the window can
		  extend.

		  @constant LEFT Specifies that the left edge of the window can
		  extend.

		  @constant NONE Specifies that none of the edges of the window can
		  extend.

		  @constant RIGHT Specifies that the right edge of the window can
		  extend.

		  @constant TOP Specifies that the top edge of the window can extend.
		*/
		enum class TITANIUMKIT_EXPORT EXTEND_EDGE {
			ALL = 1 << 0,     // 1 << 0 == 1
			BOTTOM = 1 << 1,  // 1 << 1 == 2
			LEFT = 1 << 2,    // 1 << 2 == 4
			NONE = 1 << 3,    // 1 << 3 == 8
			RIGHT = 1 << 4,   // 1 << 4 == 16
			TOP = 1 << 5      // 1 << 5 == 32
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.Gesture.orientation property.

		  @constant PORTRAIT Orientation constant for portrait mode
		  orientation.

		  @constant UPSIDE_PORTRAIT Orientation constant for inverted portait
		  orientation.

		  @constant LANDSCAPE_LEFT Standard landscape orientation (home
		  button on left).

		  @constant LANDSCAPE_RIGHT Reverse landscape orientation (home
		  button on right).

		  @constant FACE_UP Constant value for face-up orientation.

		  @constant FACE_DOWN Constant value for face-down orientation.

		  @constant UNKNOWN Orientation constant representing an unknown
		  orientation.
		*/
		enum class TITANIUMKIT_EXPORT ORIENTATION {
			PORTRAIT,
			UPSIDE_PORTRAIT,
			LANDSCAPE_LEFT,
			LANDSCAPE_RIGHT,
			FACE_UP,
			FACE_DOWN,
			UNKNOWN
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.TextField.borderStyle property.

		  @constant BEZEL Use a bezel-style border on the input field.

		  @constant LINE Use a simple line border on the input field.

		  @constant NONE Use no border on the input field.

		  @constant ROUNDED Use a rounded-rectangle border on the input
		  field.
		*/
		enum class TITANIUMKIT_EXPORT INPUT_BORDERSTYLE {
			BEZEL,
			LINE,
			NONE,
			ROUNDED
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.TextField.clearButtonMode,
		  Titanium.UI.TextField.leftButtonMode, and
		  Titanium.UI.TextField.rightButtonMode properties.

		  @constant ALWAYS Always show buttons on the input field.

		  @constant NEVER Never show buttons on the input field.

		  @constant ONBLUR Show buttons on the input field when it loses
		  focus.

		  @constant ONFOCUS Show buttons on the input field when it gains
		  focus.
		*/
		enum class TITANIUMKIT_EXPORT INPUT_BUTTONMODE {
			ALWAYS,
			NEVER,
			ONBLUR,
			ONFOCUS
		};

		/*!
		  @enum

		  @constant ALERT Use a keyboard appearance suitable for entering
		  text on an alert.

		  @constant DEFAULT Use the platform-specific default keyboard
		  appearance.
		*/
		enum class TITANIUMKIT_EXPORT KEYBOARD_APPEARANCE {
			ALERT,
			DEFAULT,
			DARK,
			LIGHT
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.TextField.keyboardType and
		  Titanium.UI.TextArea.keyboardType properties.

		  @constant ASCII Use an ASCII keyboard, with the standard keyboard
		  layout.

		  @constant DECIMAL_PAD Use a keyboard with decimal numbers only,
		  with the pad keyboard layout.

		  @constant DEFAULT Use the default keyboard, depending on the
		  platform.

		  @constant EMAIL Use a keyboard suitable for composing email, with
		  the standard keyboard layout.

		  @constant NAMEPHONE_PAD Use a keyboard suitable for entering names
		  and phone numbers, with the pad keyboard layout.

		  @constant NUMBERS_PUNCTUATION Use a keyboard with numbers and
		  punctuation only, with the standard keyboard layout.

		  @constant NUMBER_PAD Use a keyboard with a number pad only, with
		  the pad keyboard layout.

		  @constant PHONE_PAD Use a keyboard with a phone-style number pad,
		  with the pad keyboard layout.

		  @constant URL Use an keyboard optimized for entering URLs, with the
		  standard keyboard layout.
		*/
		enum class TITANIUMKIT_EXPORT KEYBOARD {
			ASCII,
			DECIMAL_PAD,
			DEFAULT,
			EMAIL,
			NAMEPHONE_PAD,
			NUMBERS_PUNCTUATION,
			NUMBER_PAD,
			PHONE_PAD,
			WEBSEARCH,
			TWITTER,
			URL
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.ListItem.accessoryType property.

		  @constant CHECKMARK Displays a checkmark on the right side of an
		  item in a list view. Use to indicate an item in a list is selected.

		  @constant DETAIL Displays a detail disclosure button on the right
		  side of an item in a list view. Use to indicate that selecting this
		  item results in the display of a detailed view of that item.

		  @constant DISCLOSURE Displays a disclosure indicator on the right
		  side of an item in a list view. Use to indicate that selecting this
		  item results in the display of another list, reflecting the next
		  level in the data model hierarchy.

		  @constant NONE Do not display anything on the right side of an item
		  in a list view.
		*/
		enum class TITANIUMKIT_EXPORT LIST_ACCESSORY_TYPE {
			CHECKMARK,
			DETAIL,
			DISCLOSURE,
			NONE
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.ListView.defaultItemTemplate and ListDataItem.template
		  properties.

		  @constant CONTACTS A built-in style for an item with a title label
		  on the left side of the cell with right-aligned, blue text, which
		  is next to a subtitle label with left-aligned, black text. The
		  title label value and subtitle label value bind to the title and
		  subtitle properties, respectively, of the data item. If a property
		  is not set, that element is not displayed.

		  @constant DEFAULT A built-in style for an item with an image view
		  and black, left-aligned title label. The text label value and image
		  value bind to the title and image properties, respectively, of the
		  data item. If a property is not set, that element is not displayed.

		  @constant SETTINGS A built-in style for a item with an image view;
		  a black, left-aligned title label; and a smaller blue,
		  right-aligned subtitle label. The title label value, subtitle label
		  value and image value bind to the title, subtitle and image
		  properties, respectively, of the data item. If a property is not
		  set, that element is not displayed.

		  @constant SUBTITLE A built-in style for an item with an image view;
		  a black, left-aligned title label across the top of the cell and a
		  subtitle label below it in smaller gray text. The title label
		  value, subtitle label value and image value bind to the title,
		  subtitle and image properties, respectively, of the data item. If a
		  property is not set, that element is not displayed.
		*/
		enum class TITANIUMKIT_EXPORT LIST_ITEM_TEMPLATE {
			CONTACTS,
			DEFAULT,
			SETTINGS,
			SUBTITLE
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.Notification.duration property.

		  @constant LONG Specifies a long duration for a Toast notification.

		  @constant SHORT Specifies a short duration for a Toast
		  notification.
		*/
		enum class TITANIUMKIT_EXPORT NOTIFICATION_DURATION {
			LONG,
			SHORT
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.Picker.type property.

		  @constant COUNT_DOWN_TIMER Use a picker with a countdown timer
		  appearance, showing hours and minutes. For an actual countdown
		  timer, the application is responsible for setting a timer to update
		  the picker values.

		  @constant DATE Use a date picker.

		  @constant DATE_AND_TIME Use a date and time picker.

		  @constant PLAIN Use a plain picker (for values other than date or
		  time).

		  @constant TIME Use a time picker.
		*/
		enum class TITANIUMKIT_EXPORT PICKER_TYPE {
			COUNT_DOWN_TIMER,
			DATE,
			DATE_AND_TIME,
			PLAIN,
			TIME
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.TextField.returnKeyType and
		  Titanium.UI.TextArea.returnKeyType properties.

		  @constant DEFAULT Use the default return key on the virtual
		  keyboard.

		  @constant DONE Set the return key text to "Done".

		  @constant EMERGENCY_CALL Set the return key text to "Emergency
		  Call".

		  @constant GO Set the return key text to "Go".

		  @constant GOOGLE Set the return key text to "Google".

		  @constant JOIN Set the return key text to "Join".

		  @constant NEXT Set the return key text to "Next".

		  @constant ROUTE Set the return key text to "Route".

		  @constant SEARCH Set the return key text to "Search".

		  @constant SEND Set the return key text to "Send".

		  @constant YAHOO Set the return key text to "Yahoo".
		*/
		enum class TITANIUMKIT_EXPORT RETURNKEY {
			DEFAULT,
			DONE,
			EMERGENCY_CALL,
			GO,
			GOOGLE,
			JOIN,
			NEXT,
			ROUTE,
			SEARCH,
			SEND,
			YAHOO
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.TextField.textAlign and Titanium.UI.TextArea.textAlign
		  properties.

		  @constant CENTER Center align text.

		  @constant LEFT Left align text.

		  @constant RIGHT Right align text.

		  @constant JUSTIFY Justify align text.
		*/
		enum class TITANIUMKIT_EXPORT TEXT_ALIGNMENT {
			CENTER,
			LEFT,
			RIGHT,
			JUSTIFY
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.TextField.autocapitalization and
		  Titanium.UI.TextArea.autocapitalization properties.

		  @constant ALL Auto-capitalize all text in the input field.

		  @constant NONE Do not auto-capitalize.

		  @constant SENTENCES Use sentence-style auto-capitalization in the
		  input field.

		  @constant WORDS Auto-capitalize the first letter of each word in
		  the input field.
		*/
		enum class TITANIUMKIT_EXPORT TEXT_AUTOCAPITALIZATION {
			ALL,
			NONE,
			SENTENCES,
			WORDS
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.TextField.verticalAlign and
		  Titanium.UI.TextArea.verticalAlign properties.

		  @constant BOTTOM Align text to the bottom of the view.

		  @constant CENTER Vertically align text to the center of the view.

		  @constant TOP Align text to the top of the view.
		*/
		enum class TITANIUMKIT_EXPORT TEXT_VERTICAL_ALIGNMENT {
			BOTTOM,
			CENTER,
			TOP
		};

		/*!
		  @enum

		  @abstract These constants are for use with the
		  Titanium.UI.WebView.error.code property.

		  @constant AUTHENTICATION Authentication error code.

		  @constant BAD_URL Bad url error code.

		  @constant CONNECT Error code reported for a failure to connect to
		  host.

		  @constant FILE Error code reported for a failure to access a file
		  resource on a host, except "file not found", which has its own
		  constant.

		  @constant FILE_NOT_FOUND Error code reported when a requested file
		  does not exist on the host.

		  @constant HOST_LOOKUP Error code reported when a host name cannot
		  be resolved, such as via a DNS lookup error.

		  @constant REDIRECT_LOOP Error code reported when a redirect loop is
		  detected.

		  @constant SSL_FAILED Error code reported for an SSL failure.

		  @constant TIMEOUT Error code reported when a timeout occurs.

		  @constant UNKNOWN Error code reported when an unknown error occurs.

		  @constant UNSUPPORTED_SCHEME Error code reported when a url
		  contains an unsupported scheme.
		*/
		enum class TITANIUMKIT_EXPORT URL_ERROR {
			AUTHENTICATION,
			BAD_URL,
			CONNECT,
			FILE,
			FILE_NOT_FOUND,
			HOST_LOOKUP,
			REDIRECT_LOOP,
			SSL_FAILED,
			TIMEOUT,
			UNKNOWN,
			UNSUPPORTED_SCHEME
		};

		/*!
		  @enum

		  @abstract These constants specify UI layout behavior.

		  @constant FILL UI layout behavior where the view will grow its size
		  to fill its parent.

		  @constant INHERIT UI layout behavior which allows the width/height
		  of a view to be determined by the parent. If a parent has a size of
		  SIZE, then the child will inherit a size of SIZE. Otherwise, the
		  child inherits a size of FILL.

		  @constant SIZE UI layout behavior where the view will constrain its
		  size to fit its contents.
		*/
		enum class TITANIUMKIT_EXPORT LAYOUT {
			FILL,
			INHERIT,
			SIZE
		};

		/*!
		  @enum

		  @abstract These constants specify text styles for the Font Object.

		  @constant BODY

		  @constant CAPTION1

		  @constant CAPTION2

		  @constant FOOTNOTE

		  @constant HEADLINE

		  @constant SUBHEADLINE
		*/
		enum class TITANIUMKIT_EXPORT TEXT_STYLE {
			BODY,
			CAPTION1,
			CAPTION2,
			FOOTNOTE,
			HEADLINE,
			SUBHEADLINE
		};

		/*!
		  @enum

		  @abstract These constants specify font weight for the Font Object.

		  @constant NORMAL

		  @constant SEMIBOLD

		  @constant BOLD
		*/
		enum class TITANIUMKIT_EXPORT FONT_WEIGHT {
			NORMAL,
			SEMIBOLD,
			BOLD
		};

		/*!
		  @enum

		  @abstract These constants specify font style for the Font Object.

		  @constant NORMAL

		  @constant ITALIC
		*/
		enum class TITANIUMKIT_EXPORT FONT_STYLE {
			NORMAL,
			ITALIC
		};

		/*!
		  @enum

		  @abstract These constants specify text styles for the Font Object.

		  @constant CM Unit constant representing units in centimeters.

		  @constant DIP Unit constant representing units in
		  density-independent pixels.

		  @constant IN Unit constant representing units in inches.

		  @constant MM Unit constant representing units in millimeters.

		  @constant PX Unit constant representing units in pixels.
		*/
		enum class TITANIUMKIT_EXPORT UNIT {
			Cm,
			Dip,
			In,
			Mm,
			Px
		};

		/*!
		  @enum

		  @abstract These constants specify type of gradient for the Gradient Object.

		  @constant LINEAR

		  @constant RADIAL
		*/
		enum class TITANIUMKIT_EXPORT GRADIENT_TYPE {
			LINEAR,
			RADIAL
		};

		/*!
		  @enum

		  @abstract These constants specify type of attribute for the Attribute Object.

		  @constant FONT
		  @constant FOREGROUND_COLOR
		  @constant BACKGROUND_COLOR
		  @constant STRIKETHROUGH_STYLE
		  @constant UNDERLINES_STYLE
		  @constant LINK
		  @constant UNDERLINE_COLOR
		  @constant KERN
		  @constant STROKE_COLOR
		  @constant STROKE_WIDTH
		  @constant SHADOW
		  @constant WRITING_DIRECTION
		  @constant TEXT_EFFECT
		  @constant BASELINE_OFFSET
		  @constant STRIKETHROUGH_COLOR
		  @constant OBLIQUENESS
		  @constant EXPANSION
		  @constant LINE_BREAK 
		*/
		enum class TITANIUMKIT_EXPORT ATTRIBUTE_TYPE {
			FONT,
			FOREGROUND_COLOR,
			BACKGROUND_COLOR,
			STRIKETHROUGH_STYLE,
			UNDERLINES_STYLE,
			LINK,
			LIGATURE,
			UNDERLINE_COLOR,
			KERN,
			STROKE_COLOR,
			STROKE_WIDTH,
			SHADOW,
			WRITING_DIRECTION,
			TEXT_EFFECT,
			BASELINE_OFFSET,
			STRIKETHROUGH_COLOR,
			OBLIQUENESS,
			EXPANSION,
			LINE_BREAK
		};

		/*!
		  @enum

		  @abstract These constants specify type of attribute for the Attribute Object.

		  @constant UNDERLINE_NONE
		  @constant UNDERLINE_SINGLE
		  @constant UNDERLINE_THICK
		  @constant UNDERLINE_DOUBLE
		  @constant UNDERLINE_PATTERN_SOLID
		  @constant UNDERLINE_PATTERN_DOT
		  @constant UNDERLINE_PATTERN_DASH
		  @constant UNDERLINE_PATTERN_DASH_DOT
		  @constant UNDERLINE_PATTERN_DASH_DOT_DOT
		  @constant UNDERLINE_BY_WORD
		  @constant WRITING_DIRECTION_EMBEDDING
		  @constant WRITING_DIRECTION_OVERRIDE
		  @constant WRITING_DIRECTION_NATURAL
		  @constant WRITING_DIRECTION_LEFT_TO_RIGHT
		  @constant WRITING_DIRECTION_RIGHT_TO_LEFT
		  @constant TEXT_EFFECT_LETTERPRESS
		  @constant LINE_BREAK_BY_WORD_WRAPPING
		  @constant LINE_BREAK_BY_CHAR_WRAPPING
		  @constant LINE_BREAK_BY_CLIPPING
		  @constant LINE_BREAK_BY_TRUNCATING_HEAD
		  @constant LINE_BREAK_BY_TRUNCATING_TAIL
		  @constant LINE_BREAK_BY_TRUNCATING_MIDDLE
		*/
		enum class TITANIUMKIT_EXPORT ATTRIBUTE_STYLE {
			UNDERLINE_NONE    = 1 << 0,
			UNDERLINE_SINGLE  = 1 << 1,
			UNDERLINE_THICK   = 1 << 2,
			UNDERLINE_DOUBLE  = 1 << 3,
			UNDERLINE_PATTERN_SOLID  = 1 << 4,
			UNDERLINE_PATTERN_DOT    = 1 << 5,
			UNDERLINE_PATTERN_DASH   = 1 << 6,
			UNDERLINE_PATTERN_DASH_DOT      = 1 << 7,
			UNDERLINE_PATTERN_DASH_DOT_DOT  = 1 << 8,
			UNDERLINE_BY_WORD  = 1 << 9,
			WRITING_DIRECTION_EMBEDDING  = 1 << 10,
			WRITING_DIRECTION_OVERRIDE   = 1 << 11,
			WRITING_DIRECTION_NATURAL    = 1 << 12,
			WRITING_DIRECTION_LEFT_TO_RIGHT  = 1 << 13,
			WRITING_DIRECTION_RIGHT_TO_LEFT  = 1 << 14,
			TEXT_EFFECT_LETTERPRESS  = 1 << 15,
			LINE_BREAK_BY_WORD_WRAPPING  = 1 << 16,
			LINE_BREAK_BY_CHAR_WRAPPING  = 1 << 17,
			LINE_BREAK_BY_CLIPPING = 1 << 18,
			LINE_BREAK_BY_TRUNCATING_HEAD  = 1 << 19,
			LINE_BREAK_BY_TRUNCATING_TAIL  = 1 << 20,
			LINE_BREAK_BY_TRUNCATING_MIDDLE  = 1 << 21 
		};
	} // namespace UI
}  // namespace Titanium

// Provide a hash function so that a Titanium::UI::AUTOLINK can be stored in an
// unordered container.
namespace std
{
	using Titanium::UI::ANIMATION_CURVE;
	template <>
	struct hash<ANIMATION_CURVE>
	{
		using argument_type = ANIMATION_CURVE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::AUTOLINK;
	template <>
	struct hash<AUTOLINK>
	{
		using argument_type = AUTOLINK;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::EXTEND_EDGE;
	template <>
	struct hash<EXTEND_EDGE>
	{
		using argument_type = EXTEND_EDGE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::ORIENTATION;
	template <>
	struct hash<ORIENTATION>
	{
		using argument_type = ORIENTATION;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::INPUT_BORDERSTYLE;
	template <>
	struct hash<INPUT_BORDERSTYLE>
	{
		using argument_type = INPUT_BORDERSTYLE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::INPUT_BUTTONMODE;
	template <>
	struct hash<INPUT_BUTTONMODE>
	{
		using argument_type = INPUT_BUTTONMODE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::KEYBOARD_APPEARANCE;
	template <>
	struct hash<KEYBOARD_APPEARANCE>
	{
		using argument_type = KEYBOARD_APPEARANCE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::KEYBOARD;
	template <>
	struct hash<KEYBOARD>
	{
		using argument_type = KEYBOARD;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::LIST_ACCESSORY_TYPE;
	template <>
	struct hash<LIST_ACCESSORY_TYPE>
	{
		using argument_type = LIST_ACCESSORY_TYPE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::LIST_ITEM_TEMPLATE;
	template <>
	struct hash<LIST_ITEM_TEMPLATE>
	{
		using argument_type = LIST_ITEM_TEMPLATE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::NOTIFICATION_DURATION;
	template <>
	struct hash<NOTIFICATION_DURATION>
	{
		using argument_type = NOTIFICATION_DURATION;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::PICKER_TYPE;
	template <>
	struct hash<PICKER_TYPE>
	{
		using argument_type = PICKER_TYPE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::RETURNKEY;
	template <>
	struct hash<RETURNKEY>
	{
		using argument_type = RETURNKEY;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::TEXT_ALIGNMENT;
	template <>
	struct hash<TEXT_ALIGNMENT>
	{
		using argument_type = TEXT_ALIGNMENT;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::TEXT_AUTOCAPITALIZATION;
	template <>
	struct hash<TEXT_AUTOCAPITALIZATION>
	{
		using argument_type = TEXT_AUTOCAPITALIZATION;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::TEXT_VERTICAL_ALIGNMENT;
	template <>
	struct hash<TEXT_VERTICAL_ALIGNMENT>
	{
		using argument_type = TEXT_VERTICAL_ALIGNMENT;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::URL_ERROR;
	template <>
	struct hash<URL_ERROR>
	{
		using argument_type = URL_ERROR;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::LAYOUT;
	template <>
	struct hash<LAYOUT>
	{
		using argument_type = LAYOUT;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::TEXT_STYLE;
	template <>
	struct hash<TEXT_STYLE>
	{
		using argument_type = TEXT_STYLE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::FONT_WEIGHT;
	template <>
	struct hash<FONT_WEIGHT>
	{
		using argument_type = FONT_WEIGHT;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::FONT_STYLE;
	template <>
	struct hash<FONT_STYLE>
	{
		using argument_type = FONT_STYLE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::GRADIENT_TYPE;
	template <>
	struct hash<GRADIENT_TYPE>
	{
		using argument_type = GRADIENT_TYPE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::UNIT;
	template <>
	struct hash<UNIT>
	{
		using argument_type = UNIT;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::ATTRIBUTE_TYPE;
	template <>
	struct hash<ATTRIBUTE_TYPE>
	{
		using argument_type = ATTRIBUTE_TYPE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::UI::ATTRIBUTE_STYLE;
	template <>
	struct hash<ATTRIBUTE_STYLE>
	{
		using argument_type = ATTRIBUTE_STYLE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};
}  // namespace std

namespace Titanium
{
	namespace UI
	{
		class TITANIUMKIT_EXPORT Constants final
		{
		public:
			static std::string to_string(const ANIMATION_CURVE&) TITANIUM_NOEXCEPT;
			static ANIMATION_CURVE to_ANIMATION_CURVE(const std::string& animationCurveName) TITANIUM_NOEXCEPT;
			static ANIMATION_CURVE to_ANIMATION_CURVE(std::underlying_type<ANIMATION_CURVE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<ANIMATION_CURVE>::type to_underlying_type(const ANIMATION_CURVE&) TITANIUM_NOEXCEPT;

			static std::string to_string(const AUTOLINK&) TITANIUM_NOEXCEPT;
			static AUTOLINK to_AUTOLINK(const std::string& autoLinkName) TITANIUM_NOEXCEPT;
			static std::unordered_set<AUTOLINK> to_AUTOLINK(std::underlying_type<AUTOLINK>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<AUTOLINK>::type to_underlying_type(const std::unordered_set<AUTOLINK>&) TITANIUM_NOEXCEPT;
			static std::underlying_type<AUTOLINK>::type to_underlying_type(const AUTOLINK&) TITANIUM_NOEXCEPT;

			static std::string to_string(const EXTEND_EDGE&) TITANIUM_NOEXCEPT;
			static EXTEND_EDGE to_EXTEND_EDGE(const std::string& extendEdgeName) TITANIUM_NOEXCEPT;
			static std::unordered_set<EXTEND_EDGE> to_EXTEND_EDGE(std::underlying_type<EXTEND_EDGE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<EXTEND_EDGE>::type to_underlying_type(const std::unordered_set<EXTEND_EDGE>& extendEdge_set) TITANIUM_NOEXCEPT;
			static std::underlying_type<EXTEND_EDGE>::type to_underlying_type(const EXTEND_EDGE&) TITANIUM_NOEXCEPT;

			static std::string to_string(const ORIENTATION&) TITANIUM_NOEXCEPT;
			static ORIENTATION to_ORIENTATION(const std::string& orientationName) TITANIUM_NOEXCEPT;
			static ORIENTATION to_ORIENTATION(std::underlying_type<ORIENTATION>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<ORIENTATION>::type to_underlying_type(const ORIENTATION&) TITANIUM_NOEXCEPT;

			static std::string to_string(const INPUT_BORDERSTYLE&) TITANIUM_NOEXCEPT;
			static INPUT_BORDERSTYLE to_INPUT_BORDERSTYLE(const std::string& inputBorderstyleName) TITANIUM_NOEXCEPT;
			static INPUT_BORDERSTYLE to_INPUT_BORDERSTYLE(std::underlying_type<INPUT_BORDERSTYLE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<INPUT_BORDERSTYLE>::type to_underlying_type(const INPUT_BORDERSTYLE&) TITANIUM_NOEXCEPT;

			static std::string to_string(const INPUT_BUTTONMODE&) TITANIUM_NOEXCEPT;
			static INPUT_BUTTONMODE to_INPUT_BUTTONMODE(const std::string& inputButtonmodeName) TITANIUM_NOEXCEPT;
			static INPUT_BUTTONMODE to_INPUT_BUTTONMODE(std::underlying_type<INPUT_BUTTONMODE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<INPUT_BUTTONMODE>::type to_underlying_type(const INPUT_BUTTONMODE&) TITANIUM_NOEXCEPT;

			static std::string to_string(const KEYBOARD_APPEARANCE&) TITANIUM_NOEXCEPT;
			static KEYBOARD_APPEARANCE to_KEYBOARD_APPEARANCE(const std::string& keyboardAppearanceName) TITANIUM_NOEXCEPT;
			static KEYBOARD_APPEARANCE to_KEYBOARD_APPEARANCE(std::underlying_type<KEYBOARD_APPEARANCE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<KEYBOARD_APPEARANCE>::type to_underlying_type(const KEYBOARD_APPEARANCE&) TITANIUM_NOEXCEPT;

			static std::string to_string(const KEYBOARD&) TITANIUM_NOEXCEPT;
			static KEYBOARD to_KEYBOARD(const std::string& keyboardName) TITANIUM_NOEXCEPT;
			static KEYBOARD to_KEYBOARD(std::underlying_type<KEYBOARD>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<KEYBOARD>::type to_underlying_type(const KEYBOARD&) TITANIUM_NOEXCEPT;

			static std::string to_string(const LIST_ACCESSORY_TYPE&) TITANIUM_NOEXCEPT;
			static LIST_ACCESSORY_TYPE to_LIST_ACCESSORY_TYPE(const std::string& listAccessoryTypeName) TITANIUM_NOEXCEPT;
			static LIST_ACCESSORY_TYPE to_LIST_ACCESSORY_TYPE(std::underlying_type<LIST_ACCESSORY_TYPE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<LIST_ACCESSORY_TYPE>::type to_underlying_type(const LIST_ACCESSORY_TYPE&) TITANIUM_NOEXCEPT;

			static std::string to_string(const LIST_ITEM_TEMPLATE&) TITANIUM_NOEXCEPT;
			static LIST_ITEM_TEMPLATE to_LIST_ITEM_TEMPLATE(const std::string& listItemTemplateName) TITANIUM_NOEXCEPT;
			static LIST_ITEM_TEMPLATE to_LIST_ITEM_TEMPLATE(std::underlying_type<LIST_ITEM_TEMPLATE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<LIST_ITEM_TEMPLATE>::type to_underlying_type(const LIST_ITEM_TEMPLATE&) TITANIUM_NOEXCEPT;

			static std::string to_string(const NOTIFICATION_DURATION&) TITANIUM_NOEXCEPT;
			static NOTIFICATION_DURATION to_NOTIFICATION_DURATION(const std::string& notificationDurationName) TITANIUM_NOEXCEPT;
			static NOTIFICATION_DURATION to_NOTIFICATION_DURATION(std::underlying_type<NOTIFICATION_DURATION>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<NOTIFICATION_DURATION>::type to_underlying_type(const NOTIFICATION_DURATION&) TITANIUM_NOEXCEPT;

			static std::string to_string(const PICKER_TYPE&) TITANIUM_NOEXCEPT;
			static PICKER_TYPE to_PICKER_TYPE(const std::string& pickerTypeName) TITANIUM_NOEXCEPT;
			static PICKER_TYPE to_PICKER_TYPE(std::underlying_type<PICKER_TYPE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<PICKER_TYPE>::type to_underlying_type(const PICKER_TYPE&) TITANIUM_NOEXCEPT;

			static std::string to_string(const RETURNKEY&) TITANIUM_NOEXCEPT;
			static RETURNKEY to_RETURNKEY(const std::string& returnKeyName) TITANIUM_NOEXCEPT;
			static RETURNKEY to_RETURNKEY(std::underlying_type<RETURNKEY>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<RETURNKEY>::type to_underlying_type(const RETURNKEY&) TITANIUM_NOEXCEPT;

			static std::string to_string(const TEXT_ALIGNMENT&) TITANIUM_NOEXCEPT;
			static TEXT_ALIGNMENT to_TEXT_ALIGNMENT(const std::string& textAlignmentName) TITANIUM_NOEXCEPT;
			static TEXT_ALIGNMENT to_TEXT_ALIGNMENT(std::underlying_type<TEXT_ALIGNMENT>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<TEXT_ALIGNMENT>::type to_underlying_type(const TEXT_ALIGNMENT&) TITANIUM_NOEXCEPT;

			static std::string to_string(const TEXT_AUTOCAPITALIZATION&) TITANIUM_NOEXCEPT;
			static TEXT_AUTOCAPITALIZATION to_TEXT_AUTOCAPITALIZATION(const std::string& textAutoCapitalizationName) TITANIUM_NOEXCEPT;
			static TEXT_AUTOCAPITALIZATION to_TEXT_AUTOCAPITALIZATION(std::underlying_type<TEXT_AUTOCAPITALIZATION>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<TEXT_AUTOCAPITALIZATION>::type to_underlying_type(const TEXT_AUTOCAPITALIZATION&) TITANIUM_NOEXCEPT;

			static std::string to_string(const TEXT_VERTICAL_ALIGNMENT&) TITANIUM_NOEXCEPT;
			static TEXT_VERTICAL_ALIGNMENT to_TEXT_VERTICAL_ALIGNMENT(const std::string& textVerticalAlignmentName) TITANIUM_NOEXCEPT;
			static TEXT_VERTICAL_ALIGNMENT to_TEXT_VERTICAL_ALIGNMENT(std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type to_underlying_type(const TEXT_VERTICAL_ALIGNMENT&) TITANIUM_NOEXCEPT;

			static std::string to_string(const URL_ERROR&) TITANIUM_NOEXCEPT;
			static URL_ERROR to_URL_ERROR(const std::string& urlErrorName) TITANIUM_NOEXCEPT;
			static URL_ERROR to_URL_ERROR(std::underlying_type<URL_ERROR>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<URL_ERROR>::type to_underlying_type(const URL_ERROR&) TITANIUM_NOEXCEPT;

			static std::string to_string(const LAYOUT&) TITANIUM_NOEXCEPT;
			static LAYOUT to_LAYOUT(const std::string& layoutName) TITANIUM_NOEXCEPT;
			static LAYOUT to_LAYOUT(std::underlying_type<LAYOUT>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<LAYOUT>::type to_underlying_type(const LAYOUT&) TITANIUM_NOEXCEPT;

			static std::string to_string(const TEXT_STYLE&) TITANIUM_NOEXCEPT;
			static TEXT_STYLE to_TEXT_STYLE(const std::string& textStyleName) TITANIUM_NOEXCEPT;
			static TEXT_STYLE to_TEXT_STYLE(std::underlying_type<TEXT_STYLE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<TEXT_STYLE>::type to_underlying_type(const TEXT_STYLE&) TITANIUM_NOEXCEPT;

			static std::string to_string(const FONT_WEIGHT&) TITANIUM_NOEXCEPT;
			static FONT_WEIGHT to_FONT_WEIGHT(const std::string& fontWeightName) TITANIUM_NOEXCEPT;
			static FONT_WEIGHT to_FONT_WEIGHT(std::underlying_type<FONT_WEIGHT>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<FONT_WEIGHT>::type to_underlying_type(const FONT_WEIGHT&) TITANIUM_NOEXCEPT;

			static std::string to_string(const FONT_STYLE&) TITANIUM_NOEXCEPT;
			static FONT_STYLE to_FONT_STYLE(const std::string& fontStyleName) TITANIUM_NOEXCEPT;
			static FONT_STYLE to_FONT_STYLE(std::underlying_type<FONT_STYLE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<FONT_STYLE>::type to_underlying_type(const FONT_STYLE&) TITANIUM_NOEXCEPT;

			static std::string to_string(const GRADIENT_TYPE&) TITANIUM_NOEXCEPT;
			static GRADIENT_TYPE to_GRADIENT_TYPE(const std::string& gradientTypeName) TITANIUM_NOEXCEPT;
			static GRADIENT_TYPE to_GRADIENT_TYPE(std::underlying_type<GRADIENT_TYPE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<GRADIENT_TYPE>::type to_underlying_type(const GRADIENT_TYPE&) TITANIUM_NOEXCEPT;

			static std::string to_string(const UNIT&) TITANIUM_NOEXCEPT;
			static UNIT to_UNIT(const std::string& textStyleName) TITANIUM_NOEXCEPT;
			static UNIT to_UNIT(std::underlying_type<UNIT>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<UNIT>::type to_underlying_type(const UNIT&) TITANIUM_NOEXCEPT;

			static std::string to_string(const ATTRIBUTE_TYPE&) TITANIUM_NOEXCEPT;
			static ATTRIBUTE_TYPE to_ATTRIBUTE_TYPE(const std::string& name) TITANIUM_NOEXCEPT;
			static ATTRIBUTE_TYPE to_ATTRIBUTE_TYPE(std::underlying_type<ATTRIBUTE_TYPE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<ATTRIBUTE_TYPE>::type to_underlying_type(const ATTRIBUTE_TYPE&) TITANIUM_NOEXCEPT;

			static std::string to_string(const ATTRIBUTE_STYLE&) TITANIUM_NOEXCEPT;
			static ATTRIBUTE_STYLE to_ATTRIBUTE_STYLE(const std::string& name) TITANIUM_NOEXCEPT;
			static std::unordered_set<ATTRIBUTE_STYLE> to_ATTRIBUTE_STYLE(std::underlying_type<ATTRIBUTE_STYLE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<ATTRIBUTE_STYLE>::type to_underlying_type(const std::unordered_set<ATTRIBUTE_STYLE>&) TITANIUM_NOEXCEPT;
			static std::underlying_type<ATTRIBUTE_STYLE>::type to_underlying_type(const ATTRIBUTE_STYLE&) TITANIUM_NOEXCEPT;

		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_CONSTANTS_HPP_
