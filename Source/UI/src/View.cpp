/**
 * Titanium.UI.View for Windows
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/UI/Button.hpp"
#include <algorithm>
#include <cctype>

namespace TitaniumWindows {
  namespace UI {

    View::View(const JSContext& js_context) TITANIUM_NOEXCEPT
      :Titanium::UI::View(js_context)
      , canvas__(ref new Windows::UI::Xaml::Controls::Canvas()) {
      TITANIUM_LOG_DEBUG("View::ctor Initialize");
    }

    View::View(const View& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
      : Titanium::UI::View(rhs, arguments)
      , canvas__(ref new Windows::UI::Xaml::Controls::Canvas()) {
      TITANIUM_LOG_DEBUG("View::ctor CallAsConstructor");
    }

    Windows::UI::Xaml::UIElement ^ View::get_UIElement()  const TITANIUM_NOEXCEPT{
      TITANIUM_LOG_DEBUG("View::get_UIElement:");
      for (auto view_ptr : get_native_children()) {
        const auto native_view_ptr = std::dynamic_pointer_cast<TitaniumWindows::UI::View>(view_ptr);
        if (native_view_ptr) {
          TITANIUM_LOG_DEBUG("View::get_UIElement: native_view_ptr = ", native_view_ptr);
          TITANIUM_ASSERT(native_view_ptr);
          canvas__->Children->Append(native_view_ptr->get_UIElement());
        }

        const auto native_button_ptr = std::dynamic_pointer_cast<TitaniumWindows::UI::Button>(view_ptr);
        if (native_button_ptr) {
          TITANIUM_LOG_DEBUG("View::get_UIElement: native_button_ptr = ", native_button_ptr);
          canvas__->Children->Append(native_button_ptr->get_UIElement());
        }
      }

      return dynamic_cast<Windows::UI::Xaml::UIElement^>(canvas__);
    }

      void View::JSExportInitialize() {
      JSExport<View>::SetClassVersion(1);
      JSExport<View>::SetParent(JSExport<Titanium::UI::View>::Class());
    }

    bool View::setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT{
      TITANIUM_ASSERT(argument.IsString());
      bool result = false;
      std::string backgroundColorName = static_cast<std::string>(argument);
      TITANIUM_LOG_INFO("View::setBackgroundColorArgumentValidator: backgroundColor = ", backgroundColorName);
      const auto backgroundColor = ColorForName(backgroundColorName);
      canvas__->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(backgroundColor);
      set_backgroundColor(argument);
      result = true;
      return result;
    }

      // Code inspired by our iOS SDK
      inline
      bool isASCIIHexDigit(char c) {
      return (c >= '0' && c <= '9') || ((c | 0x20) >= 'a' && (c | 0x20) <= 'f');
    }

    inline
      int toASCIIHexValue(char c) {
      return (c & 0xF) + (c < 'A' ? 0 : 9);
    }

    // Code inspired by our iOS SDK
    Windows::UI::Color View::ColorForHexCode(const std::string& hexCode) {
      unsigned length = hexCode.size();
      char alpha = 255;
      if ((length != 3) && (length != 4) && (length != 6) && (length != 7) && (length != 8)) {
        TITANIUM_LOG_WARN("View::ColorForHexCode: invalid hexCode = ", hexCode);
        return Windows::UI::Colors::Transparent;
      }
      unsigned value = 0;

      for (size_t i = 0; i < length; ++i) {
        unsigned char thisChar = hexCode[i];
        if (thisChar == '#') continue;
        if (!isASCIIHexDigit(thisChar)) {
          return Windows::UI::Colors::Transparent;
        }
        value <<= 4;
        value |= toASCIIHexValue(thisChar);
      }

      if (length < 6) {
        value = ((value & 0xF000) << 16) |
          ((value & 0xFF00) << 12) |
          ((value & 0xFF0) << 8) |
          ((value & 0xFF) << 4) |
          (value & 0xF);
      }

      if ((length % 4) == 0) {
        alpha = ((value >> 24) & 0xFF) * 255;
      }

      int red = (value >> 16) & 0xFF;
      int green = (value >> 8) & 0xFF;
      int blue = value & 0xFF;
      return Windows::UI::ColorHelper::FromArgb(alpha, red, green, blue);
    }

#if defined(INSERT_WINDOWS_UI_COLOR)
#error "LOGIC ERROR: INSERT_WINDOWS_UI_COLOR already defined."
#endif

    inline
      std::string toLowerCase(const std::string& string) {
      std::string copy(string);
      std::transform(string.begin(), string.end(), copy.begin(), std::tolower);
      return copy;
  }

#define INSERT_WINDOWS_UI_COLOR(COLOR_NAME) color_name_map.insert(std::make_pair(toLowerCase(#COLOR_NAME), Windows::UI::Colors::##COLOR_NAME));

    // Can this be optimized? MS is giving a lot of choices for colors!
    Windows::UI::Color View::ColorForName(const std::string& colorName) {
      // pre condition
      TITANIUM_ASSERT(!colorName.empty());

      static const Windows::UI::Color defaultColor = Windows::UI::Colors::Transparent;
      using ColorNameMap_t = std::unordered_map < std::string, Windows::UI::Color > ;
      static ColorNameMap_t color_name_map;
      static std::once_flag of;
      std::call_once(of, [] {
        INSERT_WINDOWS_UI_COLOR(AliceBlue);
        INSERT_WINDOWS_UI_COLOR(AntiqueWhite);
        INSERT_WINDOWS_UI_COLOR(Aqua);
        INSERT_WINDOWS_UI_COLOR(Aquamarine);
        INSERT_WINDOWS_UI_COLOR(Azure);
        INSERT_WINDOWS_UI_COLOR(Beige);
        INSERT_WINDOWS_UI_COLOR(Bisque);
        INSERT_WINDOWS_UI_COLOR(Black);
        INSERT_WINDOWS_UI_COLOR(BlanchedAlmond);
        INSERT_WINDOWS_UI_COLOR(Blue);
        INSERT_WINDOWS_UI_COLOR(BlueViolet);
        INSERT_WINDOWS_UI_COLOR(Brown);
        INSERT_WINDOWS_UI_COLOR(BurlyWood);
        INSERT_WINDOWS_UI_COLOR(CadetBlue);
        INSERT_WINDOWS_UI_COLOR(Chartreuse);
        INSERT_WINDOWS_UI_COLOR(Chocolate);
        INSERT_WINDOWS_UI_COLOR(Coral);
        INSERT_WINDOWS_UI_COLOR(CornflowerBlue);
        INSERT_WINDOWS_UI_COLOR(Cornsilk);
        INSERT_WINDOWS_UI_COLOR(Crimson);
        INSERT_WINDOWS_UI_COLOR(Cyan);
        INSERT_WINDOWS_UI_COLOR(DarkBlue);
        INSERT_WINDOWS_UI_COLOR(DarkCyan);
        INSERT_WINDOWS_UI_COLOR(DarkGoldenrod);
        INSERT_WINDOWS_UI_COLOR(DarkGray);
        INSERT_WINDOWS_UI_COLOR(DarkGreen);
        INSERT_WINDOWS_UI_COLOR(DarkKhaki);
        INSERT_WINDOWS_UI_COLOR(DarkMagenta);
        INSERT_WINDOWS_UI_COLOR(DarkOliveGreen);
        INSERT_WINDOWS_UI_COLOR(DarkOrange);
        INSERT_WINDOWS_UI_COLOR(DarkOrchid);
        INSERT_WINDOWS_UI_COLOR(DarkRed);
        INSERT_WINDOWS_UI_COLOR(DarkSalmon);
        INSERT_WINDOWS_UI_COLOR(DarkSeaGreen);
        INSERT_WINDOWS_UI_COLOR(DarkSlateBlue);
        INSERT_WINDOWS_UI_COLOR(DarkSlateGray);
        INSERT_WINDOWS_UI_COLOR(DarkTurquoise);
        INSERT_WINDOWS_UI_COLOR(DarkViolet);
        INSERT_WINDOWS_UI_COLOR(DeepPink);
        INSERT_WINDOWS_UI_COLOR(DeepSkyBlue);
        INSERT_WINDOWS_UI_COLOR(DimGray);
        INSERT_WINDOWS_UI_COLOR(DodgerBlue);
        INSERT_WINDOWS_UI_COLOR(Firebrick);
        INSERT_WINDOWS_UI_COLOR(FloralWhite);
        INSERT_WINDOWS_UI_COLOR(ForestGreen);
        INSERT_WINDOWS_UI_COLOR(Fuchsia);
        INSERT_WINDOWS_UI_COLOR(Gainsboro);
        INSERT_WINDOWS_UI_COLOR(GhostWhite);
        INSERT_WINDOWS_UI_COLOR(Gold);
        INSERT_WINDOWS_UI_COLOR(Goldenrod);
        INSERT_WINDOWS_UI_COLOR(Gray);
        INSERT_WINDOWS_UI_COLOR(Green);
        INSERT_WINDOWS_UI_COLOR(GreenYellow);
        INSERT_WINDOWS_UI_COLOR(Honeydew);
        INSERT_WINDOWS_UI_COLOR(HotPink);
        INSERT_WINDOWS_UI_COLOR(IndianRed);
        INSERT_WINDOWS_UI_COLOR(Indigo);
        INSERT_WINDOWS_UI_COLOR(Ivory);
        INSERT_WINDOWS_UI_COLOR(Khaki);
        INSERT_WINDOWS_UI_COLOR(Lavender);
        INSERT_WINDOWS_UI_COLOR(LavenderBlush);
        INSERT_WINDOWS_UI_COLOR(LawnGreen);
        INSERT_WINDOWS_UI_COLOR(LemonChiffon);
        INSERT_WINDOWS_UI_COLOR(LightBlue);
        INSERT_WINDOWS_UI_COLOR(LightCoral);
        INSERT_WINDOWS_UI_COLOR(LightCyan);
        INSERT_WINDOWS_UI_COLOR(LightGoldenrodYellow);
        INSERT_WINDOWS_UI_COLOR(LightGray);
        INSERT_WINDOWS_UI_COLOR(LightGreen);
        INSERT_WINDOWS_UI_COLOR(LightPink);
        INSERT_WINDOWS_UI_COLOR(LightSalmon);
        INSERT_WINDOWS_UI_COLOR(LightSeaGreen);
        INSERT_WINDOWS_UI_COLOR(LightSkyBlue);
        INSERT_WINDOWS_UI_COLOR(LightSlateGray);
        INSERT_WINDOWS_UI_COLOR(LightSteelBlue);
        INSERT_WINDOWS_UI_COLOR(LightYellow);
        INSERT_WINDOWS_UI_COLOR(Lime);
        INSERT_WINDOWS_UI_COLOR(LimeGreen);
        INSERT_WINDOWS_UI_COLOR(Linen);
        INSERT_WINDOWS_UI_COLOR(Magenta);
        INSERT_WINDOWS_UI_COLOR(Maroon);
        INSERT_WINDOWS_UI_COLOR(MediumAquamarine);
        INSERT_WINDOWS_UI_COLOR(MediumBlue);
        INSERT_WINDOWS_UI_COLOR(MediumOrchid);
        INSERT_WINDOWS_UI_COLOR(MediumPurple);
        INSERT_WINDOWS_UI_COLOR(MediumSeaGreen);
        INSERT_WINDOWS_UI_COLOR(MediumSlateBlue);
        INSERT_WINDOWS_UI_COLOR(MediumSpringGreen);
        INSERT_WINDOWS_UI_COLOR(MediumTurquoise);
        INSERT_WINDOWS_UI_COLOR(MediumVioletRed);
        INSERT_WINDOWS_UI_COLOR(MidnightBlue);
        INSERT_WINDOWS_UI_COLOR(MintCream);
        INSERT_WINDOWS_UI_COLOR(MistyRose);
        INSERT_WINDOWS_UI_COLOR(Moccasin);
        INSERT_WINDOWS_UI_COLOR(NavajoWhite);
        INSERT_WINDOWS_UI_COLOR(Navy);
        INSERT_WINDOWS_UI_COLOR(OldLace);
        INSERT_WINDOWS_UI_COLOR(Olive);
        INSERT_WINDOWS_UI_COLOR(OliveDrab);
        INSERT_WINDOWS_UI_COLOR(Orange);
        INSERT_WINDOWS_UI_COLOR(OrangeRed);
        INSERT_WINDOWS_UI_COLOR(Orchid);
        INSERT_WINDOWS_UI_COLOR(PaleGoldenrod);
        INSERT_WINDOWS_UI_COLOR(PaleGreen);
        INSERT_WINDOWS_UI_COLOR(PaleTurquoise);
        INSERT_WINDOWS_UI_COLOR(PaleVioletRed);
        INSERT_WINDOWS_UI_COLOR(PapayaWhip);
        INSERT_WINDOWS_UI_COLOR(PeachPuff);
        INSERT_WINDOWS_UI_COLOR(Peru);
        INSERT_WINDOWS_UI_COLOR(Pink);
        INSERT_WINDOWS_UI_COLOR(Plum);
        INSERT_WINDOWS_UI_COLOR(PowderBlue);
        INSERT_WINDOWS_UI_COLOR(Purple);
        INSERT_WINDOWS_UI_COLOR(Red);
        INSERT_WINDOWS_UI_COLOR(RosyBrown);
        INSERT_WINDOWS_UI_COLOR(RoyalBlue);
        INSERT_WINDOWS_UI_COLOR(SaddleBrown);
        INSERT_WINDOWS_UI_COLOR(Salmon);
        INSERT_WINDOWS_UI_COLOR(SandyBrown);
        INSERT_WINDOWS_UI_COLOR(SeaGreen);
        INSERT_WINDOWS_UI_COLOR(SeaShell);
        INSERT_WINDOWS_UI_COLOR(Sienna);
        INSERT_WINDOWS_UI_COLOR(Silver);
        INSERT_WINDOWS_UI_COLOR(SkyBlue);
        INSERT_WINDOWS_UI_COLOR(SlateBlue);
        INSERT_WINDOWS_UI_COLOR(SlateGray);
        INSERT_WINDOWS_UI_COLOR(Snow);
        INSERT_WINDOWS_UI_COLOR(SpringGreen);
        INSERT_WINDOWS_UI_COLOR(SteelBlue);
        INSERT_WINDOWS_UI_COLOR(Tan);
        INSERT_WINDOWS_UI_COLOR(Teal);
        INSERT_WINDOWS_UI_COLOR(Thistle);
        INSERT_WINDOWS_UI_COLOR(Tomato);
        INSERT_WINDOWS_UI_COLOR(Transparent);
        INSERT_WINDOWS_UI_COLOR(Turquoise);
        INSERT_WINDOWS_UI_COLOR(Violet);
        INSERT_WINDOWS_UI_COLOR(Wheat);
        INSERT_WINDOWS_UI_COLOR(White);
        INSERT_WINDOWS_UI_COLOR(WhiteSmoke);
        INSERT_WINDOWS_UI_COLOR(Yellow);
        INSERT_WINDOWS_UI_COLOR(YellowGreen);
      });

      if (colorName[0] == '#') {
        return ColorForHexCode(colorName.substr(1));
      }

      auto position = color_name_map.find(toLowerCase(colorName));

      Windows::UI::Color color = defaultColor;
      if (position != color_name_map.end()) {
        color = position->second;
      }

      return color;
    }

}
}  // namespace TitaniumWindows { namespace UI {
