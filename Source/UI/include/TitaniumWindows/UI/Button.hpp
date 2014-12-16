/**
 * Titanium.UI.Button for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_BUTTON_HPP_
#define _TITANIUMWINDOWS_UI_BUTTON_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include <string>

namespace TitaniumWindows {
  namespace UI {

    using namespace HAL;

    /*!
      @class

      @discussion This is the Titanium.UI.Button implementation for
      Windows.
      */
    class TITANIUMWINDOWS_UI_EXPORT Button final : public Titanium::UI::Button, public JSExport < Button > {

    public:

      Windows::UI::Xaml::UIElement^ get_UIElement() const TITANIUM_NOEXCEPT;

      Button(const JSContext& js_context)                          TITANIUM_NOEXCEPT;
      Button(const Button&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

      virtual ~Button();
      Button(const Button&) = default;
      Button& operator=(const Button&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
      Button(Button&&)                 = default;
      Button& operator=(Button&&)      = default;
#endif

      static void JSExportInitialize();

      virtual bool setTitleArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;

    private:

      Windows::UI::Xaml::Controls::Button^        button__;
      Windows::Foundation::EventRegistrationToken click_event__;
    };

  }
}  // namespace TitaniumWindows { namespace UI {

#endif // _TITANIUMWINDOWS_UI_BUTTON_HPP_
