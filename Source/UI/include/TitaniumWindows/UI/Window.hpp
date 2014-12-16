/**
 * Titanium.UI.Window for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_WINDOW_HPP_
#define _TITANIUMWINDOWS_UI_WINDOW_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"

namespace TitaniumWindows {
  namespace UI {

    using namespace HAL;

    /*!
      @class

      @discussion This is the Titanium.UI.Window implementation for
      Windows.
      */
    class TITANIUMWINDOWS_UI_EXPORT Window final : public Titanium::UI::Window, public JSExport < Window > {

    public:

      virtual void open(const JSObject& params, JSObject& this_object) const TITANIUM_NOEXCEPT override final;

      Window(const JSContext& js_context)                          TITANIUM_NOEXCEPT;
      Window(const Window&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

      virtual ~Window();

      Window(const Window&) = default;
      Window& operator=(const Window&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
      Window(Window&&)                 = default;
      Window& operator=(Window&&)      = default;
#endif

      static void JSExportInitialize();

    private:

      Windows::UI::Xaml::Controls::Canvas^ canvas__;
    };

  }
}  // namespace TitaniumWindows { namespace UI {

#endif // _TITANIUMWINDOWS_UI_WINDOW_HPP_
