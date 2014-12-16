/**
 * Titanium.UI.View for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_VIEW_HPP_
#define _TITANIUMWINDOWS_UI_VIEW_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"

namespace TitaniumWindows {
  namespace UI {

    using namespace HAL;

    /*!
      @class

      @discussion This is the Titanium.UI.View implementation for
      Windows.
      */
    class TITANIUMWINDOWS_UI_EXPORT View final : public Titanium::UI::View, public JSExport < View > {

    public:

      View(const JSContext& js_context)                        TITANIUM_NOEXCEPT;
      View(const View&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

      virtual Windows::UI::Xaml::UIElement^ get_UIElement() const TITANIUM_NOEXCEPT;

      virtual ~View() = default;
      View(const View&) = default;
      View& operator=(const View&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
      View(View&&)                 = default;
      View& operator=(View&&)      = default;
#endif

      static void JSExportInitialize();

      virtual bool setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;

      static Windows::UI::Color ColorForName(const std::string& colorName);
      static Windows::UI::Color ColorForHexCode(const std::string& hexCode);

    private:

      Windows::UI::Xaml::Controls::Canvas^ canvas__;
    };

  }
}  // namespace TitaniumWindows { namespace UI {

#endif // _TITANIUMWINDOWS_UI_VIEW_HPP_
