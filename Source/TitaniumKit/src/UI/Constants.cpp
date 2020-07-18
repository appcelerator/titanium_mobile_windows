/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Constants.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include <unordered_map>
#include <mutex>

namespace Titanium
{
	namespace UI
	{
		std::string Constants::to_string(const ANIMATION_CURVE& animationCurve) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "ANIMATION_CURVE::Unknown";
			static std::unordered_map<ANIMATION_CURVE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[ANIMATION_CURVE::EASE_IN]     = "ANIMATION_CURVE_EASE_IN";
      map[ANIMATION_CURVE::EASE_IN_OUT] = "ANIMATION_CURVE_EASE_IN_OUT";
      map[ANIMATION_CURVE::EASE_OUT]    = "ANIMATION_CURVE_EASE_OUT";
      map[ANIMATION_CURVE::LINEAR]      = "ANIMATION_CURVE_LINEAR";
			});

			std::string string = unknown_string;
			const auto position = map.find(animationCurve);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		ANIMATION_CURVE Constants::to_ANIMATION_CURVE(const std::string& animationCurveName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, ANIMATION_CURVE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["ANIMATION_CURVE_EASE_IN"]     = ANIMATION_CURVE::EASE_IN;
      map["ANIMATION_CURVE_EASE_IN_OUT"] = ANIMATION_CURVE::EASE_IN_OUT;
      map["ANIMATION_CURVE_EASE_OUT"]    = ANIMATION_CURVE::EASE_OUT;
      map["ANIMATION_CURVE_LINEAR"]      = ANIMATION_CURVE::LINEAR;
			});

			ANIMATION_CURVE animationCurve = ANIMATION_CURVE::LINEAR;
			const auto position = map.find(animationCurveName);
			if (position != map.end()) {
				animationCurve = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ANIMATION_CURVE: Titanium::UI::ANIMATION_CURVE with name '", animationCurveName, "' does not exist");
			}

			return animationCurve;
		}

		ANIMATION_CURVE Constants::to_ANIMATION_CURVE(std::underlying_type<ANIMATION_CURVE>::type animationCurve_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<ANIMATION_CURVE>::type, ANIMATION_CURVE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<ANIMATION_CURVE>::type>(ANIMATION_CURVE::EASE_IN)]     = ANIMATION_CURVE::EASE_IN;
      map[static_cast<std::underlying_type<ANIMATION_CURVE>::type>(ANIMATION_CURVE::EASE_IN_OUT)] = ANIMATION_CURVE::EASE_IN_OUT;
      map[static_cast<std::underlying_type<ANIMATION_CURVE>::type>(ANIMATION_CURVE::EASE_OUT)]    = ANIMATION_CURVE::EASE_OUT;
      map[static_cast<std::underlying_type<ANIMATION_CURVE>::type>(ANIMATION_CURVE::LINEAR)]      = ANIMATION_CURVE::LINEAR;
			});

			ANIMATION_CURVE animationCurve = ANIMATION_CURVE::LINEAR;
			const auto position = map.find(animationCurve_underlying_type);
			if (position != map.end()) {
				animationCurve = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ANIMATION_CURVE: Titanium::UI::ANIMATION_CURVE with value '", animationCurve_underlying_type, "' does not exist");
			}

			return animationCurve;
		}

		std::underlying_type<ANIMATION_CURVE>::type Constants::to_underlying_type(const ANIMATION_CURVE& animationCurve) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<ANIMATION_CURVE>::type>(animationCurve);
		}

		std::string Constants::to_string(const AUTOLINK& autoLinkName) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "AUTOLINK::Unknown";
			static std::unordered_map<AUTOLINK, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[AUTOLINK::ALL]             = "AUTOLINK_ALL";
      map[AUTOLINK::CALENDAR]        = "AUTOLINK_CALENDAR";
      map[AUTOLINK::EMAIL_ADDRESSES] = "AUTOLINK_EMAIL_ADDRESSES";
      map[AUTOLINK::MAP_ADDRESSES]   = "AUTOLINK_MAP_ADDRESSES";
      map[AUTOLINK::NONE]            = "AUTOLINK_NONE";
      map[AUTOLINK::PHONE_NUMBERS]   = "AUTOLINK_PHONE_NUMBERS";
      map[AUTOLINK::URLS]            = "AUTOLINK_URLS";
			});

			std::string string = unknown_string;
			const auto position = map.find(autoLinkName);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		AUTOLINK Constants::to_AUTOLINK(const std::string& autoLinkName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, AUTOLINK> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["AUTOLINK_ALL"]             = AUTOLINK::ALL;
      map["AUTOLINK_CALENDAR"]        = AUTOLINK::CALENDAR;
      map["AUTOLINK_EMAIL_ADDRESSES"] = AUTOLINK::EMAIL_ADDRESSES;
      map["AUTOLINK_MAP_ADDRESSES"]   = AUTOLINK::MAP_ADDRESSES;
      map["AUTOLINK_NONE"]            = AUTOLINK::NONE;
      map["AUTOLINK_PHONE_NUMBERS"]   = AUTOLINK::PHONE_NUMBERS;
      map["AUTOLINK_URLS"]            = AUTOLINK::URLS;
			});

			AUTOLINK autoLink = AUTOLINK::NONE;
			const auto position = map.find(autoLinkName);
			if (position != map.end()) {
				autoLink = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_AUTOLINK: Titanium::UI::AUTOLINK with name '", autoLinkName, "' does not exist");
			}

			return autoLink;
		}

		std::unordered_set<AUTOLINK> Constants::to_AUTOLINK(std::underlying_type<AUTOLINK>::type autoLinks) TITANIUM_NOEXCEPT
		{
			std::unordered_set<AUTOLINK> autoLink_set;
			static_cast<void>((autoLinks & (1 << 0)) && autoLink_set.emplace(AUTOLINK::ALL).second);
			static_cast<void>((autoLinks & (1 << 1)) && autoLink_set.emplace(AUTOLINK::CALENDAR).second);
			static_cast<void>((autoLinks & (1 << 2)) && autoLink_set.emplace(AUTOLINK::EMAIL_ADDRESSES).second);
			static_cast<void>((autoLinks & (1 << 3)) && autoLink_set.emplace(AUTOLINK::MAP_ADDRESSES).second);
			static_cast<void>((autoLinks & (1 << 4)) && autoLink_set.emplace(AUTOLINK::NONE).second);
			static_cast<void>((autoLinks & (1 << 5)) && autoLink_set.emplace(AUTOLINK::PHONE_NUMBERS).second);
			static_cast<void>((autoLinks & (1 << 6)) && autoLink_set.emplace(AUTOLINK::URLS).second);
			return autoLink_set;
		}

		std::underlying_type<AUTOLINK>::type Constants::to_underlying_type(const std::unordered_set<AUTOLINK>& autoLink_set) TITANIUM_NOEXCEPT
		{
			std::underlying_type<AUTOLINK>::type result = 0;
			for (auto autoLink : autoLink_set) {
				result |= static_cast<std::underlying_type<AUTOLINK>::type>(autoLink);
			}

			return result;
		}

		std::underlying_type<AUTOLINK>::type Constants::to_underlying_type(const AUTOLINK& autoLink) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<AUTOLINK>::type>(autoLink);
		}

		std::string Constants::to_string(const EXTEND_EDGE& extendEdge) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "EXTEND_EDGE::Unknown";
			static std::unordered_map<EXTEND_EDGE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[EXTEND_EDGE::ALL]    = "EXTEND_EDGE_ALL";
      map[EXTEND_EDGE::BOTTOM] = "EXTEND_EDGE_BOTTOM";
      map[EXTEND_EDGE::LEFT]   = "EXTEND_EDGE_LEFT";
      map[EXTEND_EDGE::NONE]   = "EXTEND_EDGE_NONE";
      map[EXTEND_EDGE::RIGHT]  = "EXTEND_EDGE_RIGHT";
      map[EXTEND_EDGE::TOP]    = "EXTEND_EDGE_TOP";
			});

			std::string string = unknown_string;
			const auto position = map.find(extendEdge);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		EXTEND_EDGE Constants::to_EXTEND_EDGE(const std::string& extendEdgeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, EXTEND_EDGE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["EXTEND_EDGE_ALL"]    = EXTEND_EDGE::ALL;
      map["EXTEND_EDGE_BOTTOM"] = EXTEND_EDGE::BOTTOM;
      map["EXTEND_EDGE_LEFT"]   = EXTEND_EDGE::LEFT;
      map["EXTEND_EDGE_NONE"]   = EXTEND_EDGE::NONE;
      map["EXTEND_EDGE_RIGHT"]  = EXTEND_EDGE::RIGHT;
      map["EXTEND_EDGE_TOP"]    = EXTEND_EDGE::TOP;
			});

			EXTEND_EDGE extendEdge = EXTEND_EDGE::NONE;
			const auto position = map.find(extendEdgeName);
			if (position != map.end()) {
				extendEdge = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_EXTEND_EDGE: Titanium::UI::EXTEND_EDGE with name '", extendEdgeName, "' does not exist");
			}

			return extendEdge;
		}

		std::unordered_set<EXTEND_EDGE> Constants::to_EXTEND_EDGE(std::underlying_type<EXTEND_EDGE>::type extendEdges) TITANIUM_NOEXCEPT
		{
			std::unordered_set<EXTEND_EDGE> extendEdge_set;
			static_cast<void>((extendEdges & (1 << 0)) && extendEdge_set.emplace(EXTEND_EDGE::ALL).second);
			static_cast<void>((extendEdges & (1 << 1)) && extendEdge_set.emplace(EXTEND_EDGE::BOTTOM).second);
			static_cast<void>((extendEdges & (1 << 2)) && extendEdge_set.emplace(EXTEND_EDGE::LEFT).second);
			static_cast<void>((extendEdges & (1 << 3)) && extendEdge_set.emplace(EXTEND_EDGE::NONE).second);
			static_cast<void>((extendEdges & (1 << 4)) && extendEdge_set.emplace(EXTEND_EDGE::RIGHT).second);
			static_cast<void>((extendEdges & (1 << 5)) && extendEdge_set.emplace(EXTEND_EDGE::TOP).second);
			return extendEdge_set;
		}

		std::underlying_type<EXTEND_EDGE>::type Constants::to_underlying_type(const std::unordered_set<EXTEND_EDGE>& extendEdge_set) TITANIUM_NOEXCEPT
		{
			std::underlying_type<EXTEND_EDGE>::type result = 0;
			for (auto extendEdge : extendEdge_set) {
				result |= static_cast<std::underlying_type<EXTEND_EDGE>::type>(extendEdge);
			}

			return result;
		}

		std::underlying_type<EXTEND_EDGE>::type Constants::to_underlying_type(const EXTEND_EDGE& extendEdge) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<EXTEND_EDGE>::type>(extendEdge);
		}

		std::string Constants::to_string(const ORIENTATION& orientation) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "ORIENTATION::Unknown";
			static std::unordered_map<ORIENTATION, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[ORIENTATION::PORTRAIT]        = "ORIENTATION_PORTRAIT";
      map[ORIENTATION::UPSIDE_PORTRAIT] = "ORIENTATION_UPSIDE_PORTRAIT";
      map[ORIENTATION::LANDSCAPE_LEFT]  = "ORIENTATION_LANDSCAPE_LEFT";
      map[ORIENTATION::LANDSCAPE_RIGHT] = "ORIENTATION_LANDSCAPE_RIGHT";
      map[ORIENTATION::FACE_UP]         = "ORIENTATION_FACE_UP";
      map[ORIENTATION::FACE_DOWN]       = "ORIENTATION_FACE_DOWN";
      map[ORIENTATION::UNKNOWN]         = "ORIENTATION_UNKNOWN";
			});

			std::string string = unknown_string;
			const auto position = map.find(orientation);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		ORIENTATION Constants::to_ORIENTATION(const std::string& orientationName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, ORIENTATION> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["ORIENTATION_PORTRAIT"]        = ORIENTATION::PORTRAIT;
      map["ORIENTATION_UPSIDE_PORTRAIT"] = ORIENTATION::UPSIDE_PORTRAIT;
      map["ORIENTATION_LANDSCAPE_LEFT"]  = ORIENTATION::LANDSCAPE_LEFT;
      map["ORIENTATION_LANDSCAPE_RIGHT"] = ORIENTATION::LANDSCAPE_RIGHT;
      map["ORIENTATION_FACE_UP"]         = ORIENTATION::FACE_UP;
      map["ORIENTATION_FACE_DOWN"]       = ORIENTATION::FACE_DOWN;
      map["ORIENTATION_UNKNOWN"]         = ORIENTATION::UNKNOWN;
			});

			ORIENTATION orientation = ORIENTATION::UNKNOWN;
			const auto position = map.find(orientationName);
			if (position != map.end()) {
				orientation = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ORIENTATION: Titanium::UI::ORIENTATION with name '", orientationName, "' does not exist");
			}

			return orientation;
		}

		ORIENTATION Constants::to_ORIENTATION(std::underlying_type<ORIENTATION>::type orientation_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<ORIENTATION>::type, ORIENTATION> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<ORIENTATION>::type>(ORIENTATION::PORTRAIT)]        = ORIENTATION::PORTRAIT;
      map[static_cast<std::underlying_type<ORIENTATION>::type>(ORIENTATION::UPSIDE_PORTRAIT)] = ORIENTATION::UPSIDE_PORTRAIT;
      map[static_cast<std::underlying_type<ORIENTATION>::type>(ORIENTATION::LANDSCAPE_LEFT)]  = ORIENTATION::LANDSCAPE_LEFT;
      map[static_cast<std::underlying_type<ORIENTATION>::type>(ORIENTATION::LANDSCAPE_RIGHT)] = ORIENTATION::LANDSCAPE_RIGHT;
      map[static_cast<std::underlying_type<ORIENTATION>::type>(ORIENTATION::FACE_UP)]         = ORIENTATION::FACE_UP;
      map[static_cast<std::underlying_type<ORIENTATION>::type>(ORIENTATION::FACE_DOWN)]       = ORIENTATION::FACE_DOWN;
      map[static_cast<std::underlying_type<ORIENTATION>::type>(ORIENTATION::UNKNOWN)]         = ORIENTATION::UNKNOWN;
			});

			ORIENTATION orientation = ORIENTATION::UNKNOWN;
			const auto position = map.find(orientation_underlying_type);
			if (position != map.end()) {
				orientation = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ORIENTATION: Titanium::UI::ORIENTATION with value '", orientation_underlying_type, "' does not exist");
			}

			return orientation;
		}

		std::underlying_type<ORIENTATION>::type Constants::to_underlying_type(const ORIENTATION& orientation) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<ORIENTATION>::type>(orientation);
		}

		std::string Constants::to_string(const INPUT_BORDERSTYLE& inputBorderstyle) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "INPUT_BORDERSTYLE::Unknown";
			static std::unordered_map<INPUT_BORDERSTYLE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[INPUT_BORDERSTYLE::BEZEL]   = "INPUT_BORDERSTYLE_BEZEL";
      map[INPUT_BORDERSTYLE::LINE]    = "INPUT_BORDERSTYLE_LINE";
      map[INPUT_BORDERSTYLE::NONE]    = "INPUT_BORDERSTYLE_NONE";
      map[INPUT_BORDERSTYLE::ROUNDED] = "INPUT_BORDERSTYLE_ROUNDED";
			});

			std::string string = unknown_string;
			const auto position = map.find(inputBorderstyle);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		INPUT_BORDERSTYLE Constants::to_INPUT_BORDERSTYLE(const std::string& inputBorderStyleName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, INPUT_BORDERSTYLE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["INPUT_BORDERSTYLE_BEZEL"]   = INPUT_BORDERSTYLE::BEZEL;
      map["INPUT_BORDERSTYLE_LINE"]    = INPUT_BORDERSTYLE::LINE;
      map["INPUT_BORDERSTYLE_NONE"]    = INPUT_BORDERSTYLE::NONE;
      map["INPUT_BORDERSTYLE_ROUNDED"] = INPUT_BORDERSTYLE::ROUNDED;
			});

			INPUT_BORDERSTYLE inputBorderStyle = INPUT_BORDERSTYLE::NONE;
			const auto position = map.find(inputBorderStyleName);
			if (position != map.end()) {
				inputBorderStyle = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_INPUT_BORDERSTYLE: Titanium::UI::INPUT_BORDERSTYLE with name '", inputBorderStyleName, "' does not exist");
			}

			return inputBorderStyle;
		}

		INPUT_BORDERSTYLE Constants::to_INPUT_BORDERSTYLE(std::underlying_type<INPUT_BORDERSTYLE>::type inputBorderStyle_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<INPUT_BORDERSTYLE>::type, INPUT_BORDERSTYLE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<INPUT_BORDERSTYLE>::type>(INPUT_BORDERSTYLE::BEZEL)]   = INPUT_BORDERSTYLE::BEZEL;
      map[static_cast<std::underlying_type<INPUT_BORDERSTYLE>::type>(INPUT_BORDERSTYLE::LINE)]    = INPUT_BORDERSTYLE::LINE;
      map[static_cast<std::underlying_type<INPUT_BORDERSTYLE>::type>(INPUT_BORDERSTYLE::NONE)]    = INPUT_BORDERSTYLE::NONE;
      map[static_cast<std::underlying_type<INPUT_BORDERSTYLE>::type>(INPUT_BORDERSTYLE::ROUNDED)] = INPUT_BORDERSTYLE::ROUNDED;
			});

			INPUT_BORDERSTYLE inputBorderStyle = INPUT_BORDERSTYLE::NONE;
			const auto position = map.find(inputBorderStyle_underlying_type);
			if (position != map.end()) {
				inputBorderStyle = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_INPUT_BORDERSTYLE: Titanium::UI::INPUT_BORDERSTYLE with value '", inputBorderStyle_underlying_type, "' does not exist");
			}

			return inputBorderStyle;
		}

		std::underlying_type<INPUT_BORDERSTYLE>::type Constants::to_underlying_type(const INPUT_BORDERSTYLE& inputBorderStyle) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<INPUT_BORDERSTYLE>::type>(inputBorderStyle);
		}

		std::string Constants::to_string(const INPUT_BUTTONMODE& inputButtonMode) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "INPUT_BUTTONMODE::Unknown";
			static std::unordered_map<INPUT_BUTTONMODE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[INPUT_BUTTONMODE::ALWAYS]  = "INPUT_BUTTONMODE_ALWAYS";
      map[INPUT_BUTTONMODE::NEVER]   = "INPUT_BUTTONMODE_NEVER";
      map[INPUT_BUTTONMODE::ONBLUR]  = "INPUT_BUTTONMODE_ONBLUR";
      map[INPUT_BUTTONMODE::ONFOCUS] = "INPUT_BUTTONMODE_ONFOCUS";
			});

			std::string string = unknown_string;
			const auto position = map.find(inputButtonMode);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		INPUT_BUTTONMODE Constants::to_INPUT_BUTTONMODE(const std::string& inputButtonModeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, INPUT_BUTTONMODE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["INPUT_BUTTONMODE_ALWAYS"]  = INPUT_BUTTONMODE::ALWAYS;
      map["INPUT_BUTTONMODE_NEVER"]   = INPUT_BUTTONMODE::NEVER;
      map["INPUT_BUTTONMODE_ONBLUR"]  = INPUT_BUTTONMODE::ONBLUR;
      map["INPUT_BUTTONMODE_ONFOCUS"] = INPUT_BUTTONMODE::ONFOCUS;
			});

			INPUT_BUTTONMODE inputButtonMode = INPUT_BUTTONMODE::NEVER;
			const auto position = map.find(inputButtonModeName);
			if (position != map.end()) {
				inputButtonMode = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_INPUT_BUTTONMODE: Titanium::UI::INPUT_BUTTONMODE with name '", inputButtonModeName, "' does not exist");
			}

			return inputButtonMode;
		}

		INPUT_BUTTONMODE Constants::to_INPUT_BUTTONMODE(std::underlying_type<INPUT_BUTTONMODE>::type inputButtonMode_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<INPUT_BUTTONMODE>::type, INPUT_BUTTONMODE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(INPUT_BUTTONMODE::ALWAYS)]  = INPUT_BUTTONMODE::ALWAYS;
      map[static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(INPUT_BUTTONMODE::NEVER)]   = INPUT_BUTTONMODE::NEVER;
      map[static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(INPUT_BUTTONMODE::ONBLUR)]  = INPUT_BUTTONMODE::ONBLUR;
      map[static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(INPUT_BUTTONMODE::ONFOCUS)] = INPUT_BUTTONMODE::ONFOCUS;
			});

			INPUT_BUTTONMODE inputButtonMode = INPUT_BUTTONMODE::NEVER;
			const auto position = map.find(inputButtonMode_underlying_type);
			if (position != map.end()) {
				inputButtonMode = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_INPUT_BUTTONMODE: Titanium::UI::INPUT_BUTTONMODE with value '", inputButtonMode_underlying_type, "' does not exist");
			}

			return inputButtonMode;
		}

		std::underlying_type<INPUT_BUTTONMODE>::type Constants::to_underlying_type(const INPUT_BUTTONMODE& inputButtonMode) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<INPUT_BUTTONMODE>::type>(inputButtonMode);
		}

		std::string Constants::to_string(const KEYBOARD_APPEARANCE& keyboardAppearance) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "KEYBOARD_APPEARANCE_DEFAULT";
			static std::unordered_map<KEYBOARD_APPEARANCE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[KEYBOARD_APPEARANCE::ALERT]   = "KEYBOARD_APPEARANCE_ALERT";
      map[KEYBOARD_APPEARANCE::DEFAULT] = "KEYBOARD_APPEARANCE_DEFAULT";
      map[KEYBOARD_APPEARANCE::DARK]    = "KEYBOARD_APPEARANCE_DARK";
      map[KEYBOARD_APPEARANCE::LIGHT]   = "KEYBOARD_APPEARANCE_LIGHT";
			});

			std::string string = unknown_string;
			const auto position = map.find(keyboardAppearance);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		KEYBOARD_APPEARANCE Constants::to_KEYBOARD_APPEARANCE(const std::string& keyboardAppearanceName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, KEYBOARD_APPEARANCE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["KEYBOARD_APPEARANCE_ALERT"]   = KEYBOARD_APPEARANCE::ALERT;
      map["KEYBOARD_APPEARANCE_DEFAULT"] = KEYBOARD_APPEARANCE::DEFAULT;
      map["KEYBOARD_APPEARANCE_DARK"]    = KEYBOARD_APPEARANCE::DARK;
      map["KEYBOARD_APPEARANCE_LIGHT"]   = KEYBOARD_APPEARANCE::LIGHT;
			});

			KEYBOARD_APPEARANCE keyboardAppearance = KEYBOARD_APPEARANCE::DEFAULT;
			const auto position = map.find(keyboardAppearanceName);
			if (position != map.end()) {
				keyboardAppearance = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_KEYBOARD_APPEARANCE: Titanium::UI::KEYBOARD_APPEARANCE with name '", keyboardAppearanceName, "' does not exist");
			}

			return keyboardAppearance;
		}

		KEYBOARD_APPEARANCE Constants::to_KEYBOARD_APPEARANCE(std::underlying_type<KEYBOARD_APPEARANCE>::type keyboardAppearance_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<KEYBOARD_APPEARANCE>::type, KEYBOARD_APPEARANCE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<KEYBOARD_APPEARANCE>::type>(KEYBOARD_APPEARANCE::ALERT)]   = KEYBOARD_APPEARANCE::ALERT;
      map[static_cast<std::underlying_type<KEYBOARD_APPEARANCE>::type>(KEYBOARD_APPEARANCE::DEFAULT)] = KEYBOARD_APPEARANCE::DEFAULT;
      map[static_cast<std::underlying_type<KEYBOARD_APPEARANCE>::type>(KEYBOARD_APPEARANCE::DARK)]    = KEYBOARD_APPEARANCE::DARK;
      map[static_cast<std::underlying_type<KEYBOARD_APPEARANCE>::type>(KEYBOARD_APPEARANCE::LIGHT)]   = KEYBOARD_APPEARANCE::LIGHT;
			});

			KEYBOARD_APPEARANCE keyboardAppearance = KEYBOARD_APPEARANCE::DEFAULT;
			const auto position = map.find(keyboardAppearance_underlying_type);
			if (position != map.end()) {
				keyboardAppearance = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_KEYBOARD_APPEARANCE: Titanium::UI::KEYBOARD_APPEARANCE with value '", keyboardAppearance_underlying_type, "' does not exist");
			}

			return keyboardAppearance;
		}

		std::underlying_type<KEYBOARD_APPEARANCE>::type Constants::to_underlying_type(const KEYBOARD_APPEARANCE& keyboardAppearance) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<KEYBOARD_APPEARANCE>::type>(keyboardAppearance);
		}

		std::string Constants::to_string(const KEYBOARD& keyboard) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "KEYBOARD::Unknown";
			static std::unordered_map<KEYBOARD, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[KEYBOARD::ASCII]               = "KEYBOARD_ASCII";
      map[KEYBOARD::DECIMAL_PAD]         = "KEYBOARD_DECIMAL_PAD";
      map[KEYBOARD::EMAIL]               = "KEYBOARD_EMAIL";
      map[KEYBOARD::NAMEPHONE_PAD]       = "KEYBOARD_NAMEPHONE_PAD";
      map[KEYBOARD::NUMBERS_PUNCTUATION] = "KEYBOARD_NUMBERS_PUNCTUATION";
      map[KEYBOARD::NUMBER_PAD]          = "KEYBOARD_NUMBER_PAD";
      map[KEYBOARD::PHONE_PAD]           = "KEYBOARD_PHONE_PAD";
      map[KEYBOARD::DEFAULT]             = "KEYBOARD_DEFAULT";
      map[KEYBOARD::WEBSEARCH]           = "KEYBOARD_WEBSEARCH";
      map[KEYBOARD::TWITTER]             = "KEYBOARD_TWITTER";
      map[KEYBOARD::URL]                 = "KEYBOARD_URL";
			});

			std::string string = unknown_string;
			const auto position = map.find(keyboard);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		KEYBOARD Constants::to_KEYBOARD(const std::string& keyboardName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, KEYBOARD> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["KEYBOARD_ASCII"]               = KEYBOARD::ASCII;
      map["KEYBOARD_DECIMAL_PAD"]         = KEYBOARD::DECIMAL_PAD;
      map["KEYBOARD_EMAIL"]               = KEYBOARD::EMAIL;
      map["KEYBOARD_NAMEPHONE_PAD"]       = KEYBOARD::NAMEPHONE_PAD;
      map["KEYBOARD_NUMBERS_PUNCTUATION"] = KEYBOARD::NUMBERS_PUNCTUATION;
      map["KEYBOARD_NUMBER_PAD"]          = KEYBOARD::NUMBER_PAD;
      map["KEYBOARD_PHONE_PAD"]           = KEYBOARD::PHONE_PAD;
      map["KEYBOARD_DEFAULT"]             = KEYBOARD::DEFAULT;
      map["KEYBOARD_WEBSEARCH"]           = KEYBOARD::WEBSEARCH;
      map["KEYBOARD_TWITTER"]             = KEYBOARD::TWITTER;
      map["KEYBOARD_URL"]                 = KEYBOARD::URL;
			});

			KEYBOARD keyboard = KEYBOARD::DEFAULT;
			const auto position = map.find(keyboardName);
			if (position != map.end()) {
				keyboard = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_KEYBOARD: Titanium::UI::KEYBOARD with name '", keyboardName, "' does not exist");
			}

			return keyboard;
		}

		KEYBOARD Constants::to_KEYBOARD(std::underlying_type<KEYBOARD>::type keyboard_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<KEYBOARD>::type, KEYBOARD> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<KEYBOARD>::type>(KEYBOARD::ASCII)]               = KEYBOARD::ASCII;
      map[static_cast<std::underlying_type<KEYBOARD>::type>(KEYBOARD::DECIMAL_PAD)]         = KEYBOARD::DECIMAL_PAD;
      map[static_cast<std::underlying_type<KEYBOARD>::type>(KEYBOARD::EMAIL)]               = KEYBOARD::EMAIL;
      map[static_cast<std::underlying_type<KEYBOARD>::type>(KEYBOARD::NAMEPHONE_PAD)]       = KEYBOARD::NAMEPHONE_PAD;
      map[static_cast<std::underlying_type<KEYBOARD>::type>(KEYBOARD::NUMBERS_PUNCTUATION)] = KEYBOARD::NUMBERS_PUNCTUATION;
      map[static_cast<std::underlying_type<KEYBOARD>::type>(KEYBOARD::NUMBER_PAD)]          = KEYBOARD::NUMBER_PAD;
      map[static_cast<std::underlying_type<KEYBOARD>::type>(KEYBOARD::PHONE_PAD)]           = KEYBOARD::PHONE_PAD;
      map[static_cast<std::underlying_type<KEYBOARD>::type>(KEYBOARD::DEFAULT)]             = KEYBOARD::DEFAULT;
      map[static_cast<std::underlying_type<KEYBOARD>::type>(KEYBOARD::WEBSEARCH)]           = KEYBOARD::WEBSEARCH;
      map[static_cast<std::underlying_type<KEYBOARD>::type>(KEYBOARD::TWITTER)]             = KEYBOARD::TWITTER;
      map[static_cast<std::underlying_type<KEYBOARD>::type>(KEYBOARD::URL)]                 = KEYBOARD::URL;
			});

			KEYBOARD keyboard = KEYBOARD::DEFAULT;
			const auto position = map.find(keyboard_underlying_type);
			if (position != map.end()) {
				keyboard = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_KEYBOARD: Titanium::UI::KEYBOARD with value '", keyboard_underlying_type, "' does not exist");
			}

			return keyboard;
		}

		std::underlying_type<KEYBOARD>::type Constants::to_underlying_type(const KEYBOARD& keyboard) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<KEYBOARD>::type>(keyboard);
		}

		std::string Constants::to_string(const LIST_ACCESSORY_TYPE& listAccessoryType) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "LIST_ACCESSORY_TYPE::Unknown";
			static std::unordered_map<LIST_ACCESSORY_TYPE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[LIST_ACCESSORY_TYPE::CHECKMARK]  = "LIST_ACCESSORY_TYPE_CHECKMARK";
      map[LIST_ACCESSORY_TYPE::DETAIL]     = "LIST_ACCESSORY_TYPE_DETAIL";
      map[LIST_ACCESSORY_TYPE::DISCLOSURE] = "LIST_ACCESSORY_TYPE_DISCLOSURE";
      map[LIST_ACCESSORY_TYPE::NONE]       = "LIST_ACCESSORY_TYPE_NONE";
			});

			std::string string = unknown_string;
			const auto position = map.find(listAccessoryType);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		LIST_ACCESSORY_TYPE Constants::to_LIST_ACCESSORY_TYPE(const std::string& listAccessoryTypeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, LIST_ACCESSORY_TYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["LIST_ACCESSORY_TYPE_CHECKMARK"]  = LIST_ACCESSORY_TYPE::CHECKMARK;
      map["LIST_ACCESSORY_TYPE_DETAIL"]     = LIST_ACCESSORY_TYPE::DETAIL;
      map["LIST_ACCESSORY_TYPE_DISCLOSURE"] = LIST_ACCESSORY_TYPE::DISCLOSURE;
      map["LIST_ACCESSORY_TYPE_NONE"]       = LIST_ACCESSORY_TYPE::NONE;
			});

			LIST_ACCESSORY_TYPE listAccessoryType = LIST_ACCESSORY_TYPE::NONE;
			const auto position = map.find(listAccessoryTypeName);
			if (position != map.end()) {
				listAccessoryType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_LIST_ACCESSORY_TYPE: Titanium::UI::LIST_ACCESSORY_TYPE with name '", listAccessoryTypeName, "' does not exist");
			}

			return listAccessoryType;
		}

		LIST_ACCESSORY_TYPE Constants::to_LIST_ACCESSORY_TYPE(std::underlying_type<LIST_ACCESSORY_TYPE>::type listAccessoryType_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<LIST_ACCESSORY_TYPE>::type, LIST_ACCESSORY_TYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<LIST_ACCESSORY_TYPE>::type>(LIST_ACCESSORY_TYPE::CHECKMARK)]  = LIST_ACCESSORY_TYPE::CHECKMARK;
      map[static_cast<std::underlying_type<LIST_ACCESSORY_TYPE>::type>(LIST_ACCESSORY_TYPE::DETAIL)]     = LIST_ACCESSORY_TYPE::DETAIL;
      map[static_cast<std::underlying_type<LIST_ACCESSORY_TYPE>::type>(LIST_ACCESSORY_TYPE::DISCLOSURE)] = LIST_ACCESSORY_TYPE::DISCLOSURE;
      map[static_cast<std::underlying_type<LIST_ACCESSORY_TYPE>::type>(LIST_ACCESSORY_TYPE::NONE)]       = LIST_ACCESSORY_TYPE::NONE;
			});

			LIST_ACCESSORY_TYPE listAccessoryType = LIST_ACCESSORY_TYPE::NONE;
			const auto position = map.find(listAccessoryType_underlying_type);
			if (position != map.end()) {
				listAccessoryType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_LIST_ACCESSORY_TYPE: Titanium::UI::LIST_ACCESSORY_TYPE with value '", listAccessoryType_underlying_type, "' does not exist");
			}

			return listAccessoryType;
		}

		std::underlying_type<LIST_ACCESSORY_TYPE>::type Constants::to_underlying_type(const LIST_ACCESSORY_TYPE& listAccessoryType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<LIST_ACCESSORY_TYPE>::type>(listAccessoryType);
		}

		std::string Constants::to_string(const LIST_ITEM_TEMPLATE& listItemTemplate) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "LIST_ITEM_TEMPLATE::Unknown";
			static std::unordered_map<LIST_ITEM_TEMPLATE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[LIST_ITEM_TEMPLATE::CONTACTS] = "LIST_ITEM_TEMPLATE_CONTACTS";
      map[LIST_ITEM_TEMPLATE::DEFAULT]  = "LIST_ITEM_TEMPLATE_DEFAULT";
      map[LIST_ITEM_TEMPLATE::SETTINGS] = "LIST_ITEM_TEMPLATE_SETTINGS";
      map[LIST_ITEM_TEMPLATE::SUBTITLE] = "LIST_ITEM_TEMPLATE_SUBTITLE";
			});

			std::string string = unknown_string;
			const auto position = map.find(listItemTemplate);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		LIST_ITEM_TEMPLATE Constants::to_LIST_ITEM_TEMPLATE(const std::string& listItemTemplateName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, LIST_ITEM_TEMPLATE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["LIST_ITEM_TEMPLATE_CONTACTS"] = LIST_ITEM_TEMPLATE::CONTACTS;
      map["LIST_ITEM_TEMPLATE_DEFAULT"]  = LIST_ITEM_TEMPLATE::DEFAULT;
      map["LIST_ITEM_TEMPLATE_SETTINGS"] = LIST_ITEM_TEMPLATE::SETTINGS;
      map["LIST_ITEM_TEMPLATE_SUBTITLE"] = LIST_ITEM_TEMPLATE::SUBTITLE;
			});

			LIST_ITEM_TEMPLATE listItemTemplate = LIST_ITEM_TEMPLATE::DEFAULT;
			const auto position = map.find(listItemTemplateName);
			if (position != map.end()) {
				listItemTemplate = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_LIST_ITEM_TEMPLATE: Titanium::UI::LIST_ITEM_TEMPLATE with name '", listItemTemplateName, "' does not exist");
			}

			return listItemTemplate;
		}

		LIST_ITEM_TEMPLATE Constants::to_LIST_ITEM_TEMPLATE(std::underlying_type<LIST_ITEM_TEMPLATE>::type listItemTemplate_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<LIST_ITEM_TEMPLATE>::type, LIST_ITEM_TEMPLATE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<LIST_ITEM_TEMPLATE>::type>(LIST_ITEM_TEMPLATE::CONTACTS)] = LIST_ITEM_TEMPLATE::CONTACTS;
      map[static_cast<std::underlying_type<LIST_ITEM_TEMPLATE>::type>(LIST_ITEM_TEMPLATE::DEFAULT)]  = LIST_ITEM_TEMPLATE::DEFAULT;
      map[static_cast<std::underlying_type<LIST_ITEM_TEMPLATE>::type>(LIST_ITEM_TEMPLATE::SETTINGS)] = LIST_ITEM_TEMPLATE::SETTINGS;
      map[static_cast<std::underlying_type<LIST_ITEM_TEMPLATE>::type>(LIST_ITEM_TEMPLATE::SUBTITLE)] = LIST_ITEM_TEMPLATE::SUBTITLE;
			});

			LIST_ITEM_TEMPLATE listItemTemplate = LIST_ITEM_TEMPLATE::DEFAULT;
			const auto position = map.find(listItemTemplate_underlying_type);
			if (position != map.end()) {
				listItemTemplate = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_LIST_ITEM_TEMPLATE: Titanium::UI::LIST_ITEM_TEMPLATE with value '", listItemTemplate_underlying_type, "' does not exist");
			}

			return listItemTemplate;
		}

		std::underlying_type<LIST_ITEM_TEMPLATE>::type Constants::to_underlying_type(const LIST_ITEM_TEMPLATE& listItemTemplate) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<LIST_ITEM_TEMPLATE>::type>(listItemTemplate);
		}

		std::string Constants::to_string(const NOTIFICATION_DURATION& notificationDuration) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "NOTIFICATION_DURATION::Unknown";
			static std::unordered_map<NOTIFICATION_DURATION, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[NOTIFICATION_DURATION::LONG]  = "NOTIFICATION_DURATION_LONG";
      map[NOTIFICATION_DURATION::SHORT] = "NOTIFICATION_DURATION_SHORT";
			});

			std::string string = unknown_string;
			const auto position = map.find(notificationDuration);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		NOTIFICATION_DURATION Constants::to_NOTIFICATION_DURATION(const std::string& notificationDurationName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, NOTIFICATION_DURATION> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["NOTIFICATION_DURATION_LONG"]  = NOTIFICATION_DURATION::LONG;
      map["NOTIFICATION_DURATION_SHORT"] = NOTIFICATION_DURATION::SHORT;
			});

			NOTIFICATION_DURATION notificationDuration = NOTIFICATION_DURATION::SHORT;
			const auto position = map.find(notificationDurationName);
			if (position != map.end()) {
				notificationDuration = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_NOTIFICATION_DURATION: Titanium::UI::NOTIFICATION_DURATION with name '", notificationDurationName, "' does not exist");
			}

			return notificationDuration;
		}

		NOTIFICATION_DURATION Constants::to_NOTIFICATION_DURATION(std::underlying_type<NOTIFICATION_DURATION>::type notificationDuration_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<NOTIFICATION_DURATION>::type, NOTIFICATION_DURATION> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<NOTIFICATION_DURATION>::type>(NOTIFICATION_DURATION::LONG)]  = NOTIFICATION_DURATION::LONG;
      map[static_cast<std::underlying_type<NOTIFICATION_DURATION>::type>(NOTIFICATION_DURATION::SHORT)] = NOTIFICATION_DURATION::SHORT;
			});

			NOTIFICATION_DURATION notificationDuration = NOTIFICATION_DURATION::SHORT;
			const auto position = map.find(notificationDuration_underlying_type);
			if (position != map.end()) {
				notificationDuration = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_NOTIFICATION_DURATION: Titanium::UI::NOTIFICATION_DURATION with value '", notificationDuration_underlying_type, "' does not exist");
			}

			return notificationDuration;
		}

		std::underlying_type<NOTIFICATION_DURATION>::type Constants::to_underlying_type(const NOTIFICATION_DURATION& notificationDuration) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<NOTIFICATION_DURATION>::type>(notificationDuration);
		}

		std::string Constants::to_string(const PICKER_TYPE& pickerType) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "PICKER_TYPE::Unknown";
			static std::unordered_map<PICKER_TYPE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[PICKER_TYPE::COUNT_DOWN_TIMER] = "PICKER_TYPE_COUNT_DOWN_TIMER";
      map[PICKER_TYPE::DATE]             = "PICKER_TYPE_DATE";
      map[PICKER_TYPE::DATE_AND_TIME]    = "PICKER_TYPE_DATE_AND_TIME";
      map[PICKER_TYPE::PLAIN]            = "PICKER_TYPE_PLAIN";
      map[PICKER_TYPE::TIME]             = "PICKER_TYPE_TIME";
			});

			std::string string = unknown_string;
			const auto position = map.find(pickerType);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		PICKER_TYPE Constants::to_PICKER_TYPE(const std::string& pickerTypeName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, PICKER_TYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["PICKER_TYPE_COUNT_DOWN_TIMER"] = PICKER_TYPE::COUNT_DOWN_TIMER;
      map["PICKER_TYPE_DATE"]             = PICKER_TYPE::DATE;
      map["PICKER_TYPE_DATE_AND_TIME"]    = PICKER_TYPE::DATE_AND_TIME;
      map["PICKER_TYPE_PLAIN"]            = PICKER_TYPE::PLAIN;
      map["PICKER_TYPE_TIME"]             = PICKER_TYPE::TIME;
			});

			PICKER_TYPE pickerType = PICKER_TYPE::PLAIN;
			const auto position = map.find(pickerTypeName);
			if (position != map.end()) {
				pickerType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_PICKER_TYPE: Titanium::UI::PICKER_TYPE with name '", pickerTypeName, "' does not exist");
			}

			return pickerType;
		}

		PICKER_TYPE Constants::to_PICKER_TYPE(std::underlying_type<PICKER_TYPE>::type pickerType_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<PICKER_TYPE>::type, PICKER_TYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<PICKER_TYPE>::type>(PICKER_TYPE::COUNT_DOWN_TIMER)] = PICKER_TYPE::COUNT_DOWN_TIMER;
      map[static_cast<std::underlying_type<PICKER_TYPE>::type>(PICKER_TYPE::DATE)]             = PICKER_TYPE::DATE;
      map[static_cast<std::underlying_type<PICKER_TYPE>::type>(PICKER_TYPE::DATE_AND_TIME)]    = PICKER_TYPE::DATE_AND_TIME;
      map[static_cast<std::underlying_type<PICKER_TYPE>::type>(PICKER_TYPE::PLAIN)]            = PICKER_TYPE::PLAIN;
      map[static_cast<std::underlying_type<PICKER_TYPE>::type>(PICKER_TYPE::TIME)]             = PICKER_TYPE::TIME;
			});

			PICKER_TYPE pickerType = PICKER_TYPE::PLAIN;
			const auto position = map.find(pickerType_underlying_type);
			if (position != map.end()) {
				pickerType = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_PICKER_TYPE: Titanium::UI::PICKER_TYPE with value '", pickerType_underlying_type, "' does not exist");
			}

			return pickerType;
		}

		std::underlying_type<PICKER_TYPE>::type Constants::to_underlying_type(const PICKER_TYPE& pickerType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<PICKER_TYPE>::type>(pickerType);
		}

		std::string Constants::to_string(const RETURNKEY& returnKey) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "RETURNKEY::Unknown";
			static std::unordered_map<RETURNKEY, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[RETURNKEY::DEFAULT]        = "RETURNKEY_DEFAULT";
      map[RETURNKEY::DONE]           = "RETURNKEY_DONE";
      map[RETURNKEY::EMERGENCY_CALL] = "RETURNKEY_EMERGENCY_CALL";
      map[RETURNKEY::GO]             = "RETURNKEY_GO";
      map[RETURNKEY::GOOGLE]         = "RETURNKEY_GOOGLE";
      map[RETURNKEY::JOIN]           = "RETURNKEY_JOIN";
      map[RETURNKEY::NEXT]           = "RETURNKEY_NEXT";
      map[RETURNKEY::ROUTE]          = "RETURNKEY_ROUTE";
      map[RETURNKEY::SEARCH]         = "RETURNKEY_SEARCH";
      map[RETURNKEY::SEND]           = "RETURNKEY_SEND";
      map[RETURNKEY::YAHOO]          = "RETURNKEY_YAHOO";
			});

			std::string string = unknown_string;
			const auto position = map.find(returnKey);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		RETURNKEY Constants::to_RETURNKEY(const std::string& returnKeyName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, RETURNKEY> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["RETURNKEY_DEFAULT"]        = RETURNKEY::DEFAULT;
      map["RETURNKEY_DONE"]           = RETURNKEY::DONE;
      map["RETURNKEY_EMERGENCY_CALL"] = RETURNKEY::EMERGENCY_CALL;
      map["RETURNKEY_GO"]             = RETURNKEY::GO;
      map["RETURNKEY_GOOGLE"]         = RETURNKEY::GOOGLE;
      map["RETURNKEY_JOIN"]           = RETURNKEY::JOIN;
      map["RETURNKEY_NEXT"]           = RETURNKEY::NEXT;
      map["RETURNKEY_ROUTE"]          = RETURNKEY::ROUTE;
      map["RETURNKEY_SEARCH"]         = RETURNKEY::SEARCH;
      map["RETURNKEY_SEND"]           = RETURNKEY::SEND;
      map["RETURNKEY_YAHOO"]          = RETURNKEY::YAHOO;
			});

			RETURNKEY returnKey = RETURNKEY::DEFAULT;
			const auto position = map.find(returnKeyName);
			if (position != map.end()) {
				returnKey = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_RETURNKEY: Titanium::UI::RETURNKEY with name '", returnKeyName, "' does not exist");
			}

			return returnKey;
		}

		RETURNKEY Constants::to_RETURNKEY(std::underlying_type<RETURNKEY>::type returnKey_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<RETURNKEY>::type, RETURNKEY> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<RETURNKEY>::type>(RETURNKEY::DEFAULT)]        = RETURNKEY::DEFAULT;
      map[static_cast<std::underlying_type<RETURNKEY>::type>(RETURNKEY::DONE)]           = RETURNKEY::DONE;
      map[static_cast<std::underlying_type<RETURNKEY>::type>(RETURNKEY::EMERGENCY_CALL)] = RETURNKEY::EMERGENCY_CALL;
      map[static_cast<std::underlying_type<RETURNKEY>::type>(RETURNKEY::GO)]             = RETURNKEY::GO;
      map[static_cast<std::underlying_type<RETURNKEY>::type>(RETURNKEY::GOOGLE)]         = RETURNKEY::GOOGLE;
      map[static_cast<std::underlying_type<RETURNKEY>::type>(RETURNKEY::JOIN)]           = RETURNKEY::JOIN;
      map[static_cast<std::underlying_type<RETURNKEY>::type>(RETURNKEY::NEXT)]           = RETURNKEY::NEXT;
      map[static_cast<std::underlying_type<RETURNKEY>::type>(RETURNKEY::ROUTE)]          = RETURNKEY::ROUTE;
      map[static_cast<std::underlying_type<RETURNKEY>::type>(RETURNKEY::SEARCH)]         = RETURNKEY::SEARCH;
      map[static_cast<std::underlying_type<RETURNKEY>::type>(RETURNKEY::SEND)]           = RETURNKEY::SEND;
      map[static_cast<std::underlying_type<RETURNKEY>::type>(RETURNKEY::YAHOO)]          = RETURNKEY::YAHOO;
			});

			RETURNKEY returnKey = RETURNKEY::DEFAULT;
			const auto position = map.find(returnKey_underlying_type);
			if (position != map.end()) {
				returnKey = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_RETURNKEY: Titanium::UI::RETURNKEY with value '", returnKey_underlying_type, "' does not exist");
			}

			return returnKey;
		}

		std::underlying_type<RETURNKEY>::type Constants::to_underlying_type(const RETURNKEY& returnKey) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<RETURNKEY>::type>(returnKey);
		}

		std::string Constants::to_string(const TEXT_ALIGNMENT& textAlignment) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "TEXT_ALIGNMENT::Unknown";
			static std::unordered_map<TEXT_ALIGNMENT, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[TEXT_ALIGNMENT::CENTER] = "center";
      map[TEXT_ALIGNMENT::LEFT]   = "left";
      map[TEXT_ALIGNMENT::RIGHT]  = "right";
      map[TEXT_ALIGNMENT::JUSTIFY] = "justify";
			});

			std::string string = unknown_string;
			const auto position = map.find(textAlignment);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		TEXT_ALIGNMENT Constants::to_TEXT_ALIGNMENT(const std::string& textAlignmentName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, TEXT_ALIGNMENT> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["center"] = TEXT_ALIGNMENT::CENTER;
      map["left"]   = TEXT_ALIGNMENT::LEFT;
      map["right"]  = TEXT_ALIGNMENT::RIGHT;
      map["justify"] = TEXT_ALIGNMENT::JUSTIFY;
			});

			TEXT_ALIGNMENT textAlignment = TEXT_ALIGNMENT::LEFT;
			const auto position = map.find(textAlignmentName);
			if (position != map.end()) {
				textAlignment = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_TEXT_ALIGNMENT: Titanium::UI::TEXT_ALIGNMENT with name '", textAlignmentName, "' does not exist");
			}

			return textAlignment;
		}

		TEXT_ALIGNMENT Constants::to_TEXT_ALIGNMENT(std::underlying_type<TEXT_ALIGNMENT>::type textAlignment_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<TEXT_ALIGNMENT>::type, TEXT_ALIGNMENT> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(TEXT_ALIGNMENT::CENTER)]        = TEXT_ALIGNMENT::CENTER;
      map[static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(TEXT_ALIGNMENT::LEFT)]           = TEXT_ALIGNMENT::LEFT;
      map[static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(TEXT_ALIGNMENT::RIGHT)] = TEXT_ALIGNMENT::RIGHT;
      map[static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(TEXT_ALIGNMENT::JUSTIFY)] = TEXT_ALIGNMENT::JUSTIFY;
			});

			TEXT_ALIGNMENT textAlignment = TEXT_ALIGNMENT::LEFT;
			const auto position = map.find(textAlignment_underlying_type);
			if (position != map.end()) {
				textAlignment = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_TEXT_ALIGNMENT: Titanium::UI::TEXT_ALIGNMENT with value '", textAlignment_underlying_type, "' does not exist");
			}

			return textAlignment;
		}

		std::underlying_type<TEXT_ALIGNMENT>::type Constants::to_underlying_type(const TEXT_ALIGNMENT& textAlignment) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<TEXT_ALIGNMENT>::type>(textAlignment);
		}

		std::string Constants::to_string(const TEXT_AUTOCAPITALIZATION& textAutoCapitalization) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "TEXT_AUTOCAPITALIZATION::Unknown";
			static std::unordered_map<TEXT_AUTOCAPITALIZATION, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[TEXT_AUTOCAPITALIZATION::ALL]       = "TEXT_AUTOCAPITALIZATION_ALL";
      map[TEXT_AUTOCAPITALIZATION::NONE]      = "TEXT_AUTOCAPITALIZATION_NONE";
      map[TEXT_AUTOCAPITALIZATION::SENTENCES] = "TEXT_AUTOCAPITALIZATION_SENTENCES";
      map[TEXT_AUTOCAPITALIZATION::WORDS]     = "TEXT_AUTOCAPITALIZATION_WORDS";
			});

			std::string string = unknown_string;
			const auto position = map.find(textAutoCapitalization);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		TEXT_AUTOCAPITALIZATION Constants::to_TEXT_AUTOCAPITALIZATION(const std::string& textAutoCapitalizationName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, TEXT_AUTOCAPITALIZATION> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["TEXT_AUTOCAPITALIZATION_ALL"]       = TEXT_AUTOCAPITALIZATION::ALL;
      map["TEXT_AUTOCAPITALIZATION_NONE"]      = TEXT_AUTOCAPITALIZATION::NONE;
      map["TEXT_AUTOCAPITALIZATION_SENTENCES"] = TEXT_AUTOCAPITALIZATION::SENTENCES;
      map["TEXT_AUTOCAPITALIZATION_WORDS"]     = TEXT_AUTOCAPITALIZATION::WORDS;
			});

			TEXT_AUTOCAPITALIZATION textAutoCapitalization = TEXT_AUTOCAPITALIZATION::NONE;
			const auto position = map.find(textAutoCapitalizationName);
			if (position != map.end()) {
				textAutoCapitalization = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_TEXT_AUTOCAPITALIZATION: Titanium::UI::TEXT_AUTOCAPITALIZATION with name '", textAutoCapitalizationName, "' does not exist");
			}

			return textAutoCapitalization;
		}

		TEXT_AUTOCAPITALIZATION Constants::to_TEXT_AUTOCAPITALIZATION(std::underlying_type<TEXT_AUTOCAPITALIZATION>::type textAutoCapitalization_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type, TEXT_AUTOCAPITALIZATION> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(TEXT_AUTOCAPITALIZATION::ALL)]       = TEXT_AUTOCAPITALIZATION::ALL;
      map[static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(TEXT_AUTOCAPITALIZATION::NONE)]      = TEXT_AUTOCAPITALIZATION::NONE;
      map[static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(TEXT_AUTOCAPITALIZATION::SENTENCES)] = TEXT_AUTOCAPITALIZATION::SENTENCES;
      map[static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(TEXT_AUTOCAPITALIZATION::WORDS)]     = TEXT_AUTOCAPITALIZATION::WORDS;
			});

			TEXT_AUTOCAPITALIZATION textAutoCapitalization = TEXT_AUTOCAPITALIZATION::NONE;
			const auto position = map.find(textAutoCapitalization_underlying_type);
			if (position != map.end()) {
				textAutoCapitalization = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_TEXT_AUTOCAPITALIZATION: Titanium::UI::TEXT_AUTOCAPITALIZATION with value '", textAutoCapitalization_underlying_type, "' does not exist");
			}

			return textAutoCapitalization;
		}

		std::underlying_type<TEXT_AUTOCAPITALIZATION>::type Constants::to_underlying_type(const TEXT_AUTOCAPITALIZATION& textAutoCapitalization) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<TEXT_AUTOCAPITALIZATION>::type>(textAutoCapitalization);
		}

		std::string Constants::to_string(const TEXT_VERTICAL_ALIGNMENT& textVerticalAlignment) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "TEXT_VERTICAL_ALIGNMENT::Unknown";
			static std::unordered_map<TEXT_VERTICAL_ALIGNMENT, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[TEXT_VERTICAL_ALIGNMENT::BOTTOM] = "TEXT_VERTICAL_ALIGNMENT_BOTTOM";
      map[TEXT_VERTICAL_ALIGNMENT::CENTER] = "TEXT_VERTICAL_ALIGNMENT_CENTER";
      map[TEXT_VERTICAL_ALIGNMENT::TOP]    = "TEXT_VERTICAL_ALIGNMENT_TOP";
			});

			std::string string = unknown_string;
			const auto position = map.find(textVerticalAlignment);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		TEXT_VERTICAL_ALIGNMENT Constants::to_TEXT_VERTICAL_ALIGNMENT(const std::string& textVerticalAlignmentName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, TEXT_VERTICAL_ALIGNMENT> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["TEXT_VERTICAL_ALIGNMENT_BOTTOM"] = TEXT_VERTICAL_ALIGNMENT::BOTTOM;
      map["TEXT_VERTICAL_ALIGNMENT_CENTER"] = TEXT_VERTICAL_ALIGNMENT::CENTER;
      map["TEXT_VERTICAL_ALIGNMENT_TOP"]    = TEXT_VERTICAL_ALIGNMENT::TOP;
			});

			TEXT_VERTICAL_ALIGNMENT textVerticalAlignment = TEXT_VERTICAL_ALIGNMENT::CENTER;
			const auto position = map.find(textVerticalAlignmentName);
			if (position != map.end()) {
				textVerticalAlignment = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_TEXT_VERTICAL_ALIGNMENT: Titanium::UI::TEXT_VERTICAL_ALIGNMENT with name '", textVerticalAlignmentName, "' does not exist");
			}

			return textVerticalAlignment;
		}

		TEXT_VERTICAL_ALIGNMENT Constants::to_TEXT_VERTICAL_ALIGNMENT(std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type textVerticalAlignment_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type, TEXT_VERTICAL_ALIGNMENT> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(TEXT_VERTICAL_ALIGNMENT::BOTTOM)] = TEXT_VERTICAL_ALIGNMENT::BOTTOM;
      map[static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(TEXT_VERTICAL_ALIGNMENT::CENTER)] = TEXT_VERTICAL_ALIGNMENT::CENTER;
      map[static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(TEXT_VERTICAL_ALIGNMENT::TOP)]    = TEXT_VERTICAL_ALIGNMENT::TOP;
			});

			TEXT_VERTICAL_ALIGNMENT textVerticalAlignment = TEXT_VERTICAL_ALIGNMENT::CENTER;
			const auto position = map.find(textVerticalAlignment_underlying_type);
			if (position != map.end()) {
				textVerticalAlignment = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_TEXT_VERTICAL_ALIGNMENT: Titanium::UI::TEXT_VERTICAL_ALIGNMENT with value '", textVerticalAlignment_underlying_type, "' does not exist");
			}

			return textVerticalAlignment;
		}

		std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type Constants::to_underlying_type(const TEXT_VERTICAL_ALIGNMENT& textVerticalAlignment) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<TEXT_VERTICAL_ALIGNMENT>::type>(textVerticalAlignment);
		}

		std::string Constants::to_string(const URL_ERROR& urlError) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "URL_ERROR::Unknown";
			static std::unordered_map<URL_ERROR, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[URL_ERROR::AUTHENTICATION]     = "URL_ERROR_AUTHENTICATION";
      map[URL_ERROR::BAD_URL]            = "URL_ERROR_BAD_URL";
      map[URL_ERROR::CONNECT]            = "URL_ERROR_CONNECT";
      map[URL_ERROR::FILE]               = "URL_ERROR_FILE";
      map[URL_ERROR::FILE_NOT_FOUND]     = "URL_ERROR_FILE_NOT_FOUND";
      map[URL_ERROR::HOST_LOOKUP]        = "URL_ERROR_HOST_LOOKUP";
      map[URL_ERROR::REDIRECT_LOOP]      = "URL_ERROR_REDIRECT_LOOP";
      map[URL_ERROR::SSL_FAILED]         = "URL_ERROR_SSL_FAILED";
      map[URL_ERROR::TIMEOUT]            = "URL_ERROR_TIMEOUT";
      map[URL_ERROR::UNKNOWN]            = "URL_ERROR_UNKNOWN";
      map[URL_ERROR::UNSUPPORTED_SCHEME] = "URL_ERROR_UNSUPPORTED_SCHEME";
			});

			std::string string = unknown_string;
			const auto position = map.find(urlError);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		URL_ERROR Constants::to_URL_ERROR(const std::string& urlErrorName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, URL_ERROR> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["URL_ERROR_AUTHENTICATION"]     = URL_ERROR::AUTHENTICATION;
      map["URL_ERROR_BAD_URL"]            = URL_ERROR::BAD_URL;
      map["URL_ERROR_CONNECT"]            = URL_ERROR::CONNECT;
      map["URL_ERROR_FILE"]               = URL_ERROR::FILE;
      map["URL_ERROR_FILE_NOT_FOUND"]     = URL_ERROR::FILE_NOT_FOUND;
      map["URL_ERROR_HOST_LOOKUP"]        = URL_ERROR::HOST_LOOKUP;
      map["URL_ERROR_REDIRECT_LOOP"]      = URL_ERROR::REDIRECT_LOOP;
      map["URL_ERROR_SSL_FAILED"]         = URL_ERROR::SSL_FAILED;
      map["URL_ERROR_TIMEOUT"]            = URL_ERROR::TIMEOUT;
      map["URL_ERROR_UNKNOWN"]            = URL_ERROR::UNKNOWN;
      map["URL_ERROR_UNSUPPORTED_SCHEME"] = URL_ERROR::UNSUPPORTED_SCHEME;
			});

			URL_ERROR urlError = URL_ERROR::UNKNOWN;
			const auto position = map.find(urlErrorName);
			if (position != map.end()) {
				urlError = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_URL_ERROR: Titanium::UI::URL_ERROR with name '", urlErrorName, "' does not exist");
			}

			return urlError;
		}

		URL_ERROR Constants::to_URL_ERROR(std::underlying_type<URL_ERROR>::type urlError_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<URL_ERROR>::type, URL_ERROR> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<URL_ERROR>::type>(URL_ERROR::AUTHENTICATION)]     = URL_ERROR::AUTHENTICATION;
      map[static_cast<std::underlying_type<URL_ERROR>::type>(URL_ERROR::BAD_URL)]            = URL_ERROR::BAD_URL;
      map[static_cast<std::underlying_type<URL_ERROR>::type>(URL_ERROR::CONNECT)]            = URL_ERROR::CONNECT;
      map[static_cast<std::underlying_type<URL_ERROR>::type>(URL_ERROR::FILE)]               = URL_ERROR::FILE;
      map[static_cast<std::underlying_type<URL_ERROR>::type>(URL_ERROR::FILE_NOT_FOUND)]     = URL_ERROR::FILE_NOT_FOUND;
      map[static_cast<std::underlying_type<URL_ERROR>::type>(URL_ERROR::HOST_LOOKUP)]        = URL_ERROR::HOST_LOOKUP;
      map[static_cast<std::underlying_type<URL_ERROR>::type>(URL_ERROR::REDIRECT_LOOP)]      = URL_ERROR::REDIRECT_LOOP;
      map[static_cast<std::underlying_type<URL_ERROR>::type>(URL_ERROR::SSL_FAILED)]         = URL_ERROR::SSL_FAILED;
      map[static_cast<std::underlying_type<URL_ERROR>::type>(URL_ERROR::TIMEOUT)]            = URL_ERROR::TIMEOUT;
      map[static_cast<std::underlying_type<URL_ERROR>::type>(URL_ERROR::UNKNOWN)]            = URL_ERROR::UNKNOWN;
      map[static_cast<std::underlying_type<URL_ERROR>::type>(URL_ERROR::UNSUPPORTED_SCHEME)] = URL_ERROR::UNSUPPORTED_SCHEME;
			});

			URL_ERROR urlError = URL_ERROR::UNKNOWN;
			const auto position = map.find(urlError_underlying_type);
			if (position != map.end()) {
				urlError = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_URL_ERROR: Titanium::UI::URL_ERROR with value '", urlError_underlying_type, "' does not exist");
			}

			return urlError;
		}

		std::underlying_type<URL_ERROR>::type Constants::to_underlying_type(const URL_ERROR& urlError) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<URL_ERROR>::type>(urlError);
		}

		std::string Constants::to_string(const LAYOUT& layout) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "LAYOUT::Unknown";
			static std::unordered_map<LAYOUT, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[LAYOUT::FILL]    = "LAYOUT_FILL";
      map[LAYOUT::INHERIT] = "LAYOUT_INHERIT";
      map[LAYOUT::SIZE]    = "LAYOUT_SIZE";
			});

			std::string string = unknown_string;
			const auto position = map.find(layout);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		LAYOUT Constants::to_LAYOUT(const std::string& layoutName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, LAYOUT> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["LAYOUT_FILL"]    = LAYOUT::FILL;
      map["LAYOUT_INHERIT"] = LAYOUT::INHERIT;
      map["LAYOUT_SIZE"]    = LAYOUT::SIZE;
			});

			LAYOUT layout = LAYOUT::INHERIT;
			const auto position = map.find(layoutName);
			if (position != map.end()) {
				layout = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_LAYOUT: Titanium::UI::LAYOUT with name '", layoutName, "' does not exist");
			}

			return layout;
		}

		LAYOUT Constants::to_LAYOUT(std::underlying_type<LAYOUT>::type layout_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<LAYOUT>::type, LAYOUT> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<LAYOUT>::type>(LAYOUT::FILL)]    = LAYOUT::FILL;
      map[static_cast<std::underlying_type<LAYOUT>::type>(LAYOUT::INHERIT)] = LAYOUT::INHERIT;
      map[static_cast<std::underlying_type<LAYOUT>::type>(LAYOUT::SIZE)]    = LAYOUT::SIZE;
			});

			LAYOUT layout = LAYOUT::INHERIT;
			const auto position = map.find(layout_underlying_type);
			if (position != map.end()) {
				layout = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_LAYOUT: Titanium::UI::LAYOUT with value '", layout_underlying_type, "' does not exist");
			}

			return layout;
		}

		std::underlying_type<LAYOUT>::type Constants::to_underlying_type(const LAYOUT& layout) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<LAYOUT>::type>(layout);
		}

		std::string Constants::to_string(const TEXT_ELLIPSIZE_TRUNCATE& ellipsize) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "TEXT_ELLIPSIZE_TRUNCATE::NONE";
			static std::unordered_map<TEXT_ELLIPSIZE_TRUNCATE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[TEXT_ELLIPSIZE_TRUNCATE::NONE] = "TEXT_ELLIPSIZE_TRUNCATE_NONE";
				map[TEXT_ELLIPSIZE_TRUNCATE::CHAR_WRAP] = "TEXT_ELLIPSIZE_TRUNCATE_CHAR_WRAP";
				map[TEXT_ELLIPSIZE_TRUNCATE::WORD_WRAP] = "TEXT_ELLIPSIZE_TRUNCATE_WORD_WRAP";
				map[TEXT_ELLIPSIZE_TRUNCATE::CLIP] = "TEXT_ELLIPSIZE_TRUNCATE_CLIP";
				map[TEXT_ELLIPSIZE_TRUNCATE::START] = "TEXT_ELLIPSIZE_TRUNCATE_START";
				map[TEXT_ELLIPSIZE_TRUNCATE::MIDDLE] = "TEXT_ELLIPSIZE_TRUNCATE_MIDDLE";
				map[TEXT_ELLIPSIZE_TRUNCATE::END] = "TEXT_ELLIPSIZE_TRUNCATE_END";
				map[TEXT_ELLIPSIZE_TRUNCATE::MARQUEE] = "TEXT_ELLIPSIZE_TRUNCATE_MARQUEE";
			});

			std::string string = unknown_string;
			const auto position = map.find(ellipsize);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		TEXT_ELLIPSIZE_TRUNCATE Constants::to_TEXT_ELLIPSIZE_TRUNCATE(const std::string& name) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, TEXT_ELLIPSIZE_TRUNCATE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["TEXT_ELLIPSIZE_TRUNCATE_NONE"] = TEXT_ELLIPSIZE_TRUNCATE::NONE;
				map["TEXT_ELLIPSIZE_TRUNCATE_CHAR_WRAP"] = TEXT_ELLIPSIZE_TRUNCATE::CHAR_WRAP;
				map["TEXT_ELLIPSIZE_TRUNCATE_WORD_WRAP"] = TEXT_ELLIPSIZE_TRUNCATE::WORD_WRAP;
				map["TEXT_ELLIPSIZE_TRUNCATE_CLIP"] = TEXT_ELLIPSIZE_TRUNCATE::CLIP;
				map["TEXT_ELLIPSIZE_TRUNCATE_START"] = TEXT_ELLIPSIZE_TRUNCATE::START;
				map["TEXT_ELLIPSIZE_TRUNCATE_MIDDLE"] = TEXT_ELLIPSIZE_TRUNCATE::MIDDLE;
				map["TEXT_ELLIPSIZE_TRUNCATE_END"] = TEXT_ELLIPSIZE_TRUNCATE::END;
				map["TEXT_ELLIPSIZE_TRUNCATE_MARQUEE"] = TEXT_ELLIPSIZE_TRUNCATE::MARQUEE;
			});

			TEXT_ELLIPSIZE_TRUNCATE ellipsize = TEXT_ELLIPSIZE_TRUNCATE::NONE;
			const auto position = map.find(name);
			if (position != map.end()) {
				ellipsize = position->second;
			}
			else {
				TITANIUM_LOG_WARN("Constants::to_TEXT_ELLIPSIZE_TRUNCATE: Titanium::UI::TEXT_ELLIPSIZE_TRUNCATE with name '", name, "' does not exist");
			}

			return ellipsize;
		}

		TEXT_ELLIPSIZE_TRUNCATE Constants::to_TEXT_ELLIPSIZE_TRUNCATE(std::underlying_type<TEXT_ELLIPSIZE_TRUNCATE>::type ellipsize_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<TEXT_ELLIPSIZE_TRUNCATE>::type, TEXT_ELLIPSIZE_TRUNCATE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<TEXT_ELLIPSIZE_TRUNCATE>::type>(TEXT_ELLIPSIZE_TRUNCATE::NONE)] = TEXT_ELLIPSIZE_TRUNCATE::NONE;
				map[static_cast<std::underlying_type<TEXT_ELLIPSIZE_TRUNCATE>::type>(TEXT_ELLIPSIZE_TRUNCATE::CHAR_WRAP)] = TEXT_ELLIPSIZE_TRUNCATE::CHAR_WRAP;
				map[static_cast<std::underlying_type<TEXT_ELLIPSIZE_TRUNCATE>::type>(TEXT_ELLIPSIZE_TRUNCATE::WORD_WRAP)] = TEXT_ELLIPSIZE_TRUNCATE::WORD_WRAP;
				map[static_cast<std::underlying_type<TEXT_ELLIPSIZE_TRUNCATE>::type>(TEXT_ELLIPSIZE_TRUNCATE::CLIP)] = TEXT_ELLIPSIZE_TRUNCATE::CLIP;
				map[static_cast<std::underlying_type<TEXT_ELLIPSIZE_TRUNCATE>::type>(TEXT_ELLIPSIZE_TRUNCATE::START)] = TEXT_ELLIPSIZE_TRUNCATE::CLIP;
				map[static_cast<std::underlying_type<TEXT_ELLIPSIZE_TRUNCATE>::type>(TEXT_ELLIPSIZE_TRUNCATE::MIDDLE)] = TEXT_ELLIPSIZE_TRUNCATE::CLIP;
				map[static_cast<std::underlying_type<TEXT_ELLIPSIZE_TRUNCATE>::type>(TEXT_ELLIPSIZE_TRUNCATE::END)] = TEXT_ELLIPSIZE_TRUNCATE::CLIP;
				map[static_cast<std::underlying_type<TEXT_ELLIPSIZE_TRUNCATE>::type>(TEXT_ELLIPSIZE_TRUNCATE::MARQUEE)] = TEXT_ELLIPSIZE_TRUNCATE::CLIP;
			});

			TEXT_ELLIPSIZE_TRUNCATE ellipsize = TEXT_ELLIPSIZE_TRUNCATE::NONE;
			const auto position = map.find(ellipsize_underlying_type);
			if (position != map.end()) {
				ellipsize = position->second;
			}
			else {
				TITANIUM_LOG_WARN("Constants::to_TEXT_ELLIPSIZE_TRUNCATE: Titanium::UI::TEXT_ELLIPSIZE_TRUNCATE with value '", ellipsize_underlying_type, "' does not exist");
			}

			return ellipsize;
		}

		std::underlying_type<TEXT_ELLIPSIZE_TRUNCATE>::type Constants::to_underlying_type(const TEXT_ELLIPSIZE_TRUNCATE& ellipsize) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<TEXT_ELLIPSIZE_TRUNCATE>::type>(ellipsize);
		}

		std::string Constants::to_string(const TEXT_STYLE& textStyle) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "TEXT_STYLE::Unknown";
			static std::unordered_map<TEXT_STYLE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[TEXT_STYLE::BODY]        = "TEXT_STYLE_BODY";
      map[TEXT_STYLE::CAPTION1]    = "TEXT_STYLE_CAPTION1";
      map[TEXT_STYLE::CAPTION2]    = "TEXT_STYLE_CAPTION2";
      map[TEXT_STYLE::FOOTNOTE]    = "TEXT_STYLE_FOOTNOTE";
      map[TEXT_STYLE::HEADLINE]    = "TEXT_STYLE_HEADLINE";
      map[TEXT_STYLE::SUBHEADLINE] = "TEXT_STYLE_SUBHEADLINE";
			});

			std::string string = unknown_string;
			const auto position = map.find(textStyle);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		TEXT_STYLE Constants::to_TEXT_STYLE(const std::string& textStyleName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, TEXT_STYLE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["TEXT_STYLE_BODY"]        = TEXT_STYLE::BODY;
      map["TEXT_STYLE_CAPTION1"]    = TEXT_STYLE::CAPTION1;
      map["TEXT_STYLE_CAPTION2"]    = TEXT_STYLE::CAPTION2;
      map["TEXT_STYLE_FOOTNOTE"]    = TEXT_STYLE::FOOTNOTE;
      map["TEXT_STYLE_HEADLINE"]    = TEXT_STYLE::HEADLINE;
      map["TEXT_STYLE_SUBHEADLINE"] = TEXT_STYLE::SUBHEADLINE;
			});

			TEXT_STYLE textStyle = TEXT_STYLE::BODY;
			const auto position = map.find(textStyleName);
			if (position != map.end()) {
				textStyle = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_TEXT_STYLE: Titanium::UI::TEXT_STYLE with name '", textStyleName, "' does not exist");
			}

			return textStyle;
		}

		TEXT_STYLE Constants::to_TEXT_STYLE(std::underlying_type<TEXT_STYLE>::type textStyle_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<TEXT_STYLE>::type, TEXT_STYLE> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<TEXT_STYLE>::type>(TEXT_STYLE::BODY)]        = TEXT_STYLE::BODY;
      map[static_cast<std::underlying_type<TEXT_STYLE>::type>(TEXT_STYLE::CAPTION1)]    = TEXT_STYLE::CAPTION1;
      map[static_cast<std::underlying_type<TEXT_STYLE>::type>(TEXT_STYLE::CAPTION2)]    = TEXT_STYLE::CAPTION2;
      map[static_cast<std::underlying_type<TEXT_STYLE>::type>(TEXT_STYLE::FOOTNOTE)]    = TEXT_STYLE::FOOTNOTE;
      map[static_cast<std::underlying_type<TEXT_STYLE>::type>(TEXT_STYLE::HEADLINE)]    = TEXT_STYLE::HEADLINE;
      map[static_cast<std::underlying_type<TEXT_STYLE>::type>(TEXT_STYLE::SUBHEADLINE)] = TEXT_STYLE::SUBHEADLINE;
			});

			TEXT_STYLE textStyle = TEXT_STYLE::BODY;
			const auto position = map.find(textStyle_underlying_type);
			if (position != map.end()) {
				textStyle = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_TEXT_STYLE: Titanium::UI::TEXT_STYLE with value '", textStyle_underlying_type, "' does not exist");
			}

			return textStyle;
		}

		std::underlying_type<TEXT_STYLE>::type Constants::to_underlying_type(const TEXT_STYLE& textStyle) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<TEXT_STYLE>::type>(textStyle);
		}

		std::string Constants::to_string(const FONT_WEIGHT& value) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "FONT_WEIGHT::Unknown";
			static std::unordered_map<FONT_WEIGHT, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
			map[FONT_WEIGHT::NORMAL]    = "normal";
			map[FONT_WEIGHT::SEMIBOLD]  = "semibold";
			map[FONT_WEIGHT::BOLD]      = "bold";
			});

			std::string string = unknown_string;
			const auto position = map.find(value);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		FONT_WEIGHT Constants::to_FONT_WEIGHT(const std::string& valueName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, FONT_WEIGHT> map;
			static std::once_flag of;
			std::call_once(of, []() {
			map["normal"]   = FONT_WEIGHT::NORMAL;
			map["semibold"] = FONT_WEIGHT::SEMIBOLD;
			map["bold"]     = FONT_WEIGHT::BOLD;
			});

			FONT_WEIGHT value = FONT_WEIGHT::NORMAL;
			const auto position = map.find(valueName);
			if (position != map.end()) {
				value = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_FONT_WEIGHT: Titanium::UI::FONT_WEIGHT with name '", valueName, "' does not exist");
			}

			return value;
		}

		FONT_WEIGHT Constants::to_FONT_WEIGHT(std::underlying_type<FONT_WEIGHT>::type value_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<FONT_WEIGHT>::type, FONT_WEIGHT> map;
			static std::once_flag of;
			std::call_once(of, []() {
			map[static_cast<std::underlying_type<FONT_WEIGHT>::type>(FONT_WEIGHT::NORMAL)]   = FONT_WEIGHT::NORMAL;
			map[static_cast<std::underlying_type<FONT_WEIGHT>::type>(FONT_WEIGHT::SEMIBOLD)] = FONT_WEIGHT::SEMIBOLD;
			map[static_cast<std::underlying_type<FONT_WEIGHT>::type>(FONT_WEIGHT::BOLD)]     = FONT_WEIGHT::BOLD;
			});

			FONT_WEIGHT value = FONT_WEIGHT::NORMAL;
			const auto position = map.find(value_underlying_type);
			if (position != map.end()) {
				value = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_FONT_WEIGHT: Titanium::UI::FONT_WEIGHT with value '", value_underlying_type, "' does not exist");
			}

			return value;
		}

		std::underlying_type<FONT_WEIGHT>::type Constants::to_underlying_type(const FONT_WEIGHT& value) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<FONT_WEIGHT>::type>(value);
		}

		std::string Constants::to_string(const FONT_STYLE& value) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "FONT_STYLE::Unknown";
			static std::unordered_map<FONT_STYLE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
			map[FONT_STYLE::NORMAL]    = "normal";
			map[FONT_STYLE::ITALIC]    = "italic";
			});

			std::string string = unknown_string;
			const auto position = map.find(value);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		FONT_STYLE Constants::to_FONT_STYLE(const std::string& valueName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, FONT_STYLE> map;
			static std::once_flag of;
			std::call_once(of, []() {
			map["normal"]   = FONT_STYLE::NORMAL;
			map["italic"]   = FONT_STYLE::ITALIC;
			});

			FONT_STYLE value = FONT_STYLE::NORMAL;
			const auto position = map.find(valueName);
			if (position != map.end()) {
				value = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_FONT_STYLE: Titanium::UI::FONT_STYLE with name '", valueName, "' does not exist");
			}

			return value;
		}

		FONT_STYLE Constants::to_FONT_STYLE(std::underlying_type<FONT_STYLE>::type value_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<FONT_STYLE>::type, FONT_STYLE> map;
			static std::once_flag of;
			std::call_once(of, []() {
			map[static_cast<std::underlying_type<FONT_STYLE>::type>(FONT_STYLE::NORMAL)]   = FONT_STYLE::NORMAL;
			map[static_cast<std::underlying_type<FONT_STYLE>::type>(FONT_STYLE::ITALIC)]   = FONT_STYLE::ITALIC;
			});

			FONT_STYLE value = FONT_STYLE::NORMAL;
			const auto position = map.find(value_underlying_type);
			if (position != map.end()) {
				value = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_FONT_STYLE: Titanium::UI::FONT_STYLE with value '", value_underlying_type, "' does not exist");
			}

			return value;
		}

		std::underlying_type<FONT_STYLE>::type Constants::to_underlying_type(const FONT_STYLE& value) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<FONT_STYLE>::type>(value);
		}

		std::string Constants::to_string(const GRADIENT_TYPE& value) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "GRADIENT_TYPE::Unknown";
			static std::unordered_map<GRADIENT_TYPE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
			map[GRADIENT_TYPE::LINEAR]    = "linear";
			map[GRADIENT_TYPE::RADIAL]    = "radial";
			});

			std::string string = unknown_string;
			const auto position = map.find(value);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		GRADIENT_TYPE Constants::to_GRADIENT_TYPE(const std::string& valueName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, GRADIENT_TYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
			map["linear"]   = GRADIENT_TYPE::LINEAR;
			map["radial"]   = GRADIENT_TYPE::RADIAL;
			});

			GRADIENT_TYPE value = GRADIENT_TYPE::LINEAR;
			const auto position = map.find(valueName);
			if (position != map.end()) {
				value = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_GRADIENT_TYPE: Titanium::UI::GRADIENT_TYPE with name '", valueName, "' does not exist");
			}

			return value;
		}

		GRADIENT_TYPE Constants::to_GRADIENT_TYPE(std::underlying_type<GRADIENT_TYPE>::type value_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<GRADIENT_TYPE>::type, GRADIENT_TYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
			map[static_cast<std::underlying_type<GRADIENT_TYPE>::type>(GRADIENT_TYPE::LINEAR)]   = GRADIENT_TYPE::LINEAR;
			map[static_cast<std::underlying_type<GRADIENT_TYPE>::type>(GRADIENT_TYPE::RADIAL)]   = GRADIENT_TYPE::RADIAL;
			});

			GRADIENT_TYPE value = GRADIENT_TYPE::LINEAR;
			const auto position = map.find(value_underlying_type);
			if (position != map.end()) {
				value = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_GRADIENT_TYPE: Titanium::UI::GRADIENT_TYPE with value '", value_underlying_type, "' does not exist");
			}

			return value;
		}

		std::underlying_type<GRADIENT_TYPE>::type Constants::to_underlying_type(const GRADIENT_TYPE& value) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<GRADIENT_TYPE>::type>(value);
		}

		std::string Constants::to_string(const UNIT& unit) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "UNIT::Unknown";
			static std::unordered_map<UNIT, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[UNIT::Cm]  = "cm";
      map[UNIT::Dip] = "dip";
      map[UNIT::In]  = "in";
      map[UNIT::Mm]  = "mm";
      map[UNIT::Px]  = "px";
      map[UNIT::Ppx] = "ppx";
			});

			std::string string = unknown_string;
			const auto position = map.find(unit);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		UNIT Constants::to_UNIT(const std::string& unitName) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, UNIT> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map["cm"]  = UNIT::Cm;
      map["dip"] = UNIT::Dip;
      map["dp"]  = UNIT::Dip;
      map["in"]  = UNIT::In;
      map["mm"]  = UNIT::Mm;
      map["px"]  = UNIT::Px;
      map["ppx"] = UNIT::Ppx;
			});

			UNIT unit = UNIT::Dip;
			const auto position = map.find(unitName);
			if (position != map.end()) {
				unit = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_UNIT: Titanium::UI::UNIT with name '", unitName, "' does not exist");
			}

			return unit;
		}

		UNIT Constants::to_UNIT(std::underlying_type<UNIT>::type unit_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<UNIT>::type, UNIT> map;
			static std::once_flag of;
			std::call_once(of, []() {
      map[static_cast<std::underlying_type<UNIT>::type>(UNIT::Cm)]  = UNIT::Cm;
      map[static_cast<std::underlying_type<UNIT>::type>(UNIT::Dip)] = UNIT::Dip;
      map[static_cast<std::underlying_type<UNIT>::type>(UNIT::In)]  = UNIT::In;
      map[static_cast<std::underlying_type<UNIT>::type>(UNIT::Mm)]  = UNIT::Mm;
      map[static_cast<std::underlying_type<UNIT>::type>(UNIT::Px)]  = UNIT::Px;
      map[static_cast<std::underlying_type<UNIT>::type>(UNIT::Ppx)] = UNIT::Ppx;
			});

			UNIT unit = UNIT::Dip;
			const auto position = map.find(unit_underlying_type);
			if (position != map.end()) {
				unit = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_UNIT: Titanium::UI::UNIT with value '", unit_underlying_type, "' does not exist");
			}

			return unit;
		}

		std::underlying_type<UNIT>::type Constants::to_underlying_type(const UNIT& unit) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<UNIT>::type>(unit);
		}

		std::string Constants::to_string(const ATTRIBUTE_TYPE& name) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "ATTRIBUTE_TYPE::Unknown";
			static std::unordered_map<ATTRIBUTE_TYPE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[ATTRIBUTE_TYPE::FONT] = "ATTRIBUTE_TYPE_FONT";
				map[ATTRIBUTE_TYPE::FOREGROUND_COLOR] = "ATTRIBUTE_TYPE_FOREGROUND_COLOR";
				map[ATTRIBUTE_TYPE::BACKGROUND_COLOR] = "ATTRIBUTE_TYPE_BACKGROUND_COLOR";
				map[ATTRIBUTE_TYPE::STRIKETHROUGH_STYLE] = "ATTRIBUTE_TYPE_STRIKETHROUGH_STYLE";
				map[ATTRIBUTE_TYPE::UNDERLINES_STYLE] = "ATTRIBUTE_TYPE_UNDERLINES_STYLE";
				map[ATTRIBUTE_TYPE::LINK] = "ATTRIBUTE_TYPE_LINK";
				map[ATTRIBUTE_TYPE::LIGATURE] = "ATTRIBUTE_TYPE_LIGATURE";
				map[ATTRIBUTE_TYPE::UNDERLINE_COLOR] = "ATTRIBUTE_TYPE_UNDERLINE_COLOR";
				map[ATTRIBUTE_TYPE::KERN] = "ATTRIBUTE_TYPE_KERN";
				map[ATTRIBUTE_TYPE::STROKE_COLOR] = "ATTRIBUTE_TYPE_STROKE_COLOR";
				map[ATTRIBUTE_TYPE::STROKE_WIDTH] = "ATTRIBUTE_TYPE_STROKE_WIDTH";
				map[ATTRIBUTE_TYPE::SHADOW] = "ATTRIBUTE_TYPE_SHADOW";
				map[ATTRIBUTE_TYPE::WRITING_DIRECTION] = "ATTRIBUTE_TYPE_WRITING_DIRECTION";
				map[ATTRIBUTE_TYPE::TEXT_EFFECT] = "ATTRIBUTE_TYPE_TEXT_EFFECT";
				map[ATTRIBUTE_TYPE::BASELINE_OFFSET] = "ATTRIBUTE_TYPE_BASELINE_OFFSET";
				map[ATTRIBUTE_TYPE::STRIKETHROUGH_COLOR] = "ATTRIBUTE_TYPE_STRIKETHROUGH_COLOR";
				map[ATTRIBUTE_TYPE::OBLIQUENESS] = "ATTRIBUTE_TYPE_OBLIQUENESS";
				map[ATTRIBUTE_TYPE::EXPANSION] = "ATTRIBUTE_TYPE_EXPANSION";
				map[ATTRIBUTE_TYPE::LINE_BREAK] = "ATTRIBUTE_TYPE_LINE_BREAK";
			});

			std::string string = unknown_string;
			const auto position = map.find(name);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		ATTRIBUTE_TYPE Constants::to_ATTRIBUTE_TYPE(const std::string& name) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, ATTRIBUTE_TYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["ATTRIBUTE_TYPE_FONT"] = ATTRIBUTE_TYPE::FONT;
				map["ATTRIBUTE_TYPE_FOREGROUND_COLOR"] = ATTRIBUTE_TYPE::FOREGROUND_COLOR;
				map["ATTRIBUTE_TYPE_BACKGROUND_COLOR"] = ATTRIBUTE_TYPE::BACKGROUND_COLOR;
				map["ATTRIBUTE_TYPE_STRIKETHROUGH_STYLE"] = ATTRIBUTE_TYPE::STRIKETHROUGH_STYLE;
				map["ATTRIBUTE_TYPE_UNDERLINES_STYLE"] = ATTRIBUTE_TYPE::UNDERLINES_STYLE;
				map["ATTRIBUTE_TYPE_LINK"] = ATTRIBUTE_TYPE::LINK;
				map["ATTRIBUTE_TYPE_LIGATURE"] = ATTRIBUTE_TYPE::LIGATURE;
				map["ATTRIBUTE_TYPE_UNDERLINE_COLOR"] = ATTRIBUTE_TYPE::UNDERLINE_COLOR;
				map["ATTRIBUTE_TYPE_KERN"] = ATTRIBUTE_TYPE::KERN;
				map["ATTRIBUTE_TYPE_STROKE_COLOR"] = ATTRIBUTE_TYPE::STROKE_COLOR;
				map["ATTRIBUTE_TYPE_STROKE_WIDTH"] = ATTRIBUTE_TYPE::STROKE_WIDTH;
				map["ATTRIBUTE_TYPE_SHADOW"] = ATTRIBUTE_TYPE::SHADOW;
				map["ATTRIBUTE_TYPE_WRITING_DIRECTION"] = ATTRIBUTE_TYPE::WRITING_DIRECTION;
				map["ATTRIBUTE_TYPE_TEXT_EFFECT"] = ATTRIBUTE_TYPE::TEXT_EFFECT;
				map["ATTRIBUTE_TYPE_BASELINE_OFFSET"] = ATTRIBUTE_TYPE::BASELINE_OFFSET;
				map["ATTRIBUTE_TYPE_STRIKETHROUGH_COLOR"] = ATTRIBUTE_TYPE::STRIKETHROUGH_COLOR;
				map["ATTRIBUTE_TYPE_OBLIQUENESS"] = ATTRIBUTE_TYPE::OBLIQUENESS;
				map["ATTRIBUTE_TYPE_EXPANSION"] = ATTRIBUTE_TYPE::EXPANSION;
				map["ATTRIBUTE_TYPE_LINE_BREAK"] = ATTRIBUTE_TYPE::LINE_BREAK;
			});

			ATTRIBUTE_TYPE autoLink = ATTRIBUTE_TYPE::FONT;
			const auto position = map.find(name);
			if (position != map.end()) {
				autoLink = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ATTRIBUTE_TYPE: Titanium::UI::ATTRIBUTE_TYPE with name '", name, "' does not exist");
			}

			return autoLink;
		}

		ATTRIBUTE_TYPE Constants::to_ATTRIBUTE_TYPE(std::underlying_type<ATTRIBUTE_TYPE>::type value_underlying_type) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::underlying_type<ATTRIBUTE_TYPE>::type, ATTRIBUTE_TYPE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::FONT)] = ATTRIBUTE_TYPE::FONT;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::FOREGROUND_COLOR)] = ATTRIBUTE_TYPE::FOREGROUND_COLOR;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::BACKGROUND_COLOR)] = ATTRIBUTE_TYPE::BACKGROUND_COLOR;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::STRIKETHROUGH_STYLE)] = ATTRIBUTE_TYPE::STRIKETHROUGH_STYLE;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::UNDERLINES_STYLE)] = ATTRIBUTE_TYPE::UNDERLINES_STYLE;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::LINK)] = ATTRIBUTE_TYPE::LINK;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::LIGATURE)] = ATTRIBUTE_TYPE::LIGATURE;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::UNDERLINE_COLOR)] = ATTRIBUTE_TYPE::UNDERLINE_COLOR;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::KERN)] = ATTRIBUTE_TYPE::KERN;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::STROKE_COLOR)] = ATTRIBUTE_TYPE::STROKE_COLOR;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::STROKE_WIDTH)] = ATTRIBUTE_TYPE::STROKE_WIDTH;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::SHADOW)] = ATTRIBUTE_TYPE::SHADOW;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::WRITING_DIRECTION)] = ATTRIBUTE_TYPE::WRITING_DIRECTION;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::TEXT_EFFECT)] = ATTRIBUTE_TYPE::TEXT_EFFECT;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::BASELINE_OFFSET)] = ATTRIBUTE_TYPE::BASELINE_OFFSET;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::STRIKETHROUGH_COLOR)] = ATTRIBUTE_TYPE::STRIKETHROUGH_COLOR;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::OBLIQUENESS)] = ATTRIBUTE_TYPE::OBLIQUENESS;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::EXPANSION)] = ATTRIBUTE_TYPE::EXPANSION;
				map[static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(ATTRIBUTE_TYPE::LINE_BREAK)] = ATTRIBUTE_TYPE::LINE_BREAK;
			});

			ATTRIBUTE_TYPE value = ATTRIBUTE_TYPE::FONT;
			const auto position = map.find(value_underlying_type);
			if (position != map.end()) {
				value = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ATTRIBUTE_TYPE: Titanium::UI::ATTRIBUTE_TYPE with value '", value_underlying_type, "' does not exist");
			}

			return value;
		}

		std::underlying_type<ATTRIBUTE_TYPE>::type Constants::to_underlying_type(const ATTRIBUTE_TYPE& attrType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<ATTRIBUTE_TYPE>::type>(attrType);
		}

		std::string Constants::to_string(const ATTRIBUTE_STYLE& name) TITANIUM_NOEXCEPT
		{
			static std::string unknown_string = "ATTRIBUTE_STYLE::Unknown";
			static std::unordered_map<ATTRIBUTE_STYLE, std::string> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map[ATTRIBUTE_STYLE::UNDERLINE_NONE] = "ATTRIBUTE_STYLE_UNDERLINE_NONE";
				map[ATTRIBUTE_STYLE::UNDERLINE_SINGLE] = "ATTRIBUTE_STYLE_UNDERLINE_SINGLE";
				map[ATTRIBUTE_STYLE::UNDERLINE_THICK] = "ATTRIBUTE_STYLE_UNDERLINE_THICK";
				map[ATTRIBUTE_STYLE::UNDERLINE_DOUBLE] = "ATTRIBUTE_STYLE_UNDERLINE_DOUBLE";
				map[ATTRIBUTE_STYLE::UNDERLINE_PATTERN_SOLID] = "ATTRIBUTE_STYLE_UNDERLINE_PATTERN_SOLID";
				map[ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DOT] = "ATTRIBUTE_STYLE_UNDERLINE_PATTERN_DOT";
				map[ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH] = "ATTRIBUTE_STYLE_UNDERLINE_PATTERN_DASH";
				map[ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH_DOT] = "ATTRIBUTE_STYLE_UNDERLINE_PATTERN_DASH_DOT";
				map[ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH_DOT_DOT] = "ATTRIBUTE_STYLE_UNDERLINE_PATTERN_DASH_DOT_DOT";
				map[ATTRIBUTE_STYLE::UNDERLINE_BY_WORD] = "ATTRIBUTE_STYLE_UNDERLINE_BY_WORD";
				map[ATTRIBUTE_STYLE::WRITING_DIRECTION_EMBEDDING] = "ATTRIBUTE_STYLE_WRITING_DIRECTION_EMBEDDING";
				map[ATTRIBUTE_STYLE::WRITING_DIRECTION_OVERRIDE] = "ATTRIBUTE_STYLE_WRITING_DIRECTION_OVERRIDE";
				map[ATTRIBUTE_STYLE::WRITING_DIRECTION_NATURAL] = "ATTRIBUTE_STYLE_WRITING_DIRECTION_NATURAL";
				map[ATTRIBUTE_STYLE::WRITING_DIRECTION_LEFT_TO_RIGHT] = "ATTRIBUTE_STYLE_WRITING_DIRECTION_LEFT_TO_RIGHT";
				map[ATTRIBUTE_STYLE::WRITING_DIRECTION_RIGHT_TO_LEFT] = "ATTRIBUTE_STYLE_WRITING_DIRECTION_RIGHT_TO_LEFT";
				map[ATTRIBUTE_STYLE::TEXT_EFFECT_LETTERPRESS] = "ATTRIBUTE_STYLE_TEXT_EFFECT_LETTERPRESS";
				map[ATTRIBUTE_STYLE::LINE_BREAK_BY_WORD_WRAPPING] = "ATTRIBUTE_STYLE_LINE_BREAK_BY_WORD_WRAPPING";
				map[ATTRIBUTE_STYLE::LINE_BREAK_BY_CHAR_WRAPPING] = "ATTRIBUTE_STYLE_LINE_BREAK_BY_CHAR_WRAPPING";
				map[ATTRIBUTE_STYLE::LINE_BREAK_BY_CLIPPING] = "ATTRIBUTE_STYLE_LINE_BREAK_BY_CLIPPING";
				map[ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_HEAD] = "ATTRIBUTE_STYLE_LINE_BREAK_BY_TRUNCATING_HEAD";
				map[ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_TAIL] = "ATTRIBUTE_STYLE_LINE_BREAK_BY_TRUNCATING_TAIL";
				map[ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_MIDDLE] = "ATTRIBUTE_STYLE_LINE_BREAK_BY_TRUNCATING_MIDDLE";
			});

			std::string string = unknown_string;
			const auto position = map.find(name);
			if (position != map.end()) {
				string = position->second;
			}

			return string;
		}

		ATTRIBUTE_STYLE Constants::to_ATTRIBUTE_STYLE(const std::string& name) TITANIUM_NOEXCEPT
		{
			static std::unordered_map<std::string, ATTRIBUTE_STYLE> map;
			static std::once_flag of;
			std::call_once(of, []() {
				map["ATTRIBUTE_STYLE_UNDERLINE_NONE"] = ATTRIBUTE_STYLE::UNDERLINE_NONE;
				map["ATTRIBUTE_STYLE_UNDERLINE_SINGLE"] = ATTRIBUTE_STYLE::UNDERLINE_SINGLE;
				map["ATTRIBUTE_STYLE_UNDERLINE_THICK"] = ATTRIBUTE_STYLE::UNDERLINE_THICK;
				map["ATTRIBUTE_STYLE_UNDERLINE_DOUBLE"] = ATTRIBUTE_STYLE::UNDERLINE_DOUBLE;
				map["ATTRIBUTE_STYLE_UNDERLINE_PATTERN_SOLID"] = ATTRIBUTE_STYLE::UNDERLINE_PATTERN_SOLID;
				map["ATTRIBUTE_STYLE_UNDERLINE_PATTERN_DOT"] = ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DOT;
				map["ATTRIBUTE_STYLE_UNDERLINE_PATTERN_DASH"] = ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH;
				map["ATTRIBUTE_STYLE_UNDERLINE_PATTERN_DASH_DOT"] = ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH_DOT;
				map["ATTRIBUTE_STYLE_UNDERLINE_PATTERN_DASH_DOT_DOT"] = ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH_DOT_DOT;
				map["ATTRIBUTE_STYLE_UNDERLINE_BY_WORD"] = ATTRIBUTE_STYLE::UNDERLINE_BY_WORD;
				map["ATTRIBUTE_STYLE_WRITING_DIRECTION_EMBEDDING"] = ATTRIBUTE_STYLE::WRITING_DIRECTION_EMBEDDING;
				map["ATTRIBUTE_STYLE_WRITING_DIRECTION_OVERRIDE"] = ATTRIBUTE_STYLE::WRITING_DIRECTION_OVERRIDE;
				map["ATTRIBUTE_STYLE_WRITING_DIRECTION_NATURAL"] = ATTRIBUTE_STYLE::WRITING_DIRECTION_NATURAL;
				map["ATTRIBUTE_STYLE_WRITING_DIRECTION_LEFT_TO_RIGHT"] = ATTRIBUTE_STYLE::WRITING_DIRECTION_LEFT_TO_RIGHT;
				map["ATTRIBUTE_STYLE_WRITING_DIRECTION_RIGHT_TO_LEFT"] = ATTRIBUTE_STYLE::WRITING_DIRECTION_RIGHT_TO_LEFT;
				map["ATTRIBUTE_STYLE_TEXT_EFFECT_LETTERPRESS"] = ATTRIBUTE_STYLE::TEXT_EFFECT_LETTERPRESS;
				map["ATTRIBUTE_STYLE_LINE_BREAK_BY_WORD_WRAPPING"] = ATTRIBUTE_STYLE::LINE_BREAK_BY_WORD_WRAPPING;
				map["ATTRIBUTE_STYLE_LINE_BREAK_BY_CHAR_WRAPPING"] = ATTRIBUTE_STYLE::LINE_BREAK_BY_CHAR_WRAPPING;
				map["ATTRIBUTE_STYLE_LINE_BREAK_BY_CLIPPING"] = ATTRIBUTE_STYLE::LINE_BREAK_BY_CLIPPING;
				map["ATTRIBUTE_STYLE_LINE_BREAK_BY_TRUNCATING_HEAD"] = ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_HEAD;
				map["ATTRIBUTE_STYLE_LINE_BREAK_BY_TRUNCATING_TAIL"] = ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_TAIL;
				map["ATTRIBUTE_STYLE_LINE_BREAK_BY_TRUNCATING_MIDDLE"] = ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_MIDDLE;
			});

			ATTRIBUTE_STYLE autoLink = ATTRIBUTE_STYLE::UNDERLINE_NONE;
			const auto position = map.find(name);
			if (position != map.end()) {
				autoLink = position->second;
			} else {
				TITANIUM_LOG_WARN("Constants::to_ATTRIBUTE_STYLE: Titanium::UI::ATTRIBUTE_STYLE with name '", name, "' does not exist");
			}

			return autoLink;
		}

		std::unordered_set<ATTRIBUTE_STYLE> Constants::to_ATTRIBUTE_STYLE(std::underlying_type<ATTRIBUTE_STYLE>::type types) TITANIUM_NOEXCEPT
		{
			std::unordered_set<ATTRIBUTE_STYLE> type_set;
			static_cast<void>((types & (1 << 0)) && type_set.emplace(ATTRIBUTE_STYLE::UNDERLINE_NONE).second);
			static_cast<void>((types & (1 << 1)) && type_set.emplace(ATTRIBUTE_STYLE::UNDERLINE_SINGLE).second);
			static_cast<void>((types & (1 << 2)) && type_set.emplace(ATTRIBUTE_STYLE::UNDERLINE_THICK).second);
			static_cast<void>((types & (1 << 3)) && type_set.emplace(ATTRIBUTE_STYLE::UNDERLINE_DOUBLE).second);
			static_cast<void>((types & (1 << 4)) && type_set.emplace(ATTRIBUTE_STYLE::UNDERLINE_PATTERN_SOLID).second);
			static_cast<void>((types & (1 << 5)) && type_set.emplace(ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DOT).second);
			static_cast<void>((types & (1 << 6)) && type_set.emplace(ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH).second);
			static_cast<void>((types & (1 << 7)) && type_set.emplace(ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH_DOT).second);
			static_cast<void>((types & (1 << 8)) && type_set.emplace(ATTRIBUTE_STYLE::UNDERLINE_PATTERN_DASH_DOT_DOT).second);
			static_cast<void>((types & (1 << 9)) && type_set.emplace(ATTRIBUTE_STYLE::UNDERLINE_BY_WORD).second);
			static_cast<void>((types & (1 << 10)) && type_set.emplace(ATTRIBUTE_STYLE::WRITING_DIRECTION_EMBEDDING).second);
			static_cast<void>((types & (1 << 11)) && type_set.emplace(ATTRIBUTE_STYLE::WRITING_DIRECTION_OVERRIDE).second);
			static_cast<void>((types & (1 << 12)) && type_set.emplace(ATTRIBUTE_STYLE::WRITING_DIRECTION_NATURAL).second);
			static_cast<void>((types & (1 << 13)) && type_set.emplace(ATTRIBUTE_STYLE::WRITING_DIRECTION_LEFT_TO_RIGHT).second);
			static_cast<void>((types & (1 << 14)) && type_set.emplace(ATTRIBUTE_STYLE::WRITING_DIRECTION_RIGHT_TO_LEFT).second);
			static_cast<void>((types & (1 << 15)) && type_set.emplace(ATTRIBUTE_STYLE::TEXT_EFFECT_LETTERPRESS).second);
			static_cast<void>((types & (1 << 16)) && type_set.emplace(ATTRIBUTE_STYLE::LINE_BREAK_BY_WORD_WRAPPING).second);
			static_cast<void>((types & (1 << 17)) && type_set.emplace(ATTRIBUTE_STYLE::LINE_BREAK_BY_CHAR_WRAPPING).second);
			static_cast<void>((types & (1 << 18)) && type_set.emplace(ATTRIBUTE_STYLE::LINE_BREAK_BY_CLIPPING).second);
			static_cast<void>((types & (1 << 19)) && type_set.emplace(ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_HEAD).second);
			static_cast<void>((types & (1 << 20)) && type_set.emplace(ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_TAIL).second);
			static_cast<void>((types & (1 << 21)) && type_set.emplace(ATTRIBUTE_STYLE::LINE_BREAK_BY_TRUNCATING_MIDDLE).second);
			return type_set;
		}

		std::underlying_type<ATTRIBUTE_STYLE>::type Constants::to_underlying_type(const std::unordered_set<ATTRIBUTE_STYLE>& type_set) TITANIUM_NOEXCEPT
		{
			std::underlying_type<ATTRIBUTE_STYLE>::type result = 0;
			for (auto attrType : type_set) {
				result |= static_cast<std::underlying_type<ATTRIBUTE_STYLE>::type>(attrType);
			}

			return result;
		}

		std::underlying_type<ATTRIBUTE_STYLE>::type Constants::to_underlying_type(const ATTRIBUTE_STYLE& attrType) TITANIUM_NOEXCEPT
		{
			return static_cast<std::underlying_type<ATTRIBUTE_STYLE>::type>(attrType);
		}

	} // namespace UI
}  // namespace Titanium
