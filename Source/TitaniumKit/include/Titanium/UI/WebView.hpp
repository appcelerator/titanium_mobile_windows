/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_WEBVIEW_HPP_
#define _TITANIUM_UI_WEBVIEW_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/WebViewErrorEvent.hpp"
#include "Titanium/UI/Constants.hpp"

namespace Titanium { namespace UI {
  
  using namespace HAL;
  
  /*!
   @class
   
   @discussion This is the Titanium.UI.WebView module.
   
   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.WebView
   */
  class TITANIUMKIT_EXPORT WebView : public View, public JSExport<WebView> {
    
  public:
    
    WebView(const JSContext& js_context)                           TITANIUM_NOEXCEPT;
    WebView(const WebView&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~WebView()                 = default;
    WebView(const WebView&)            = default;
    WebView& operator=(const WebView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    WebView(WebView&&)                 = default;
    WebView& operator=(WebView&&)      = default;
#endif
    
    // TODO: The following functions can automatically be generated
    // from the YAML API docs.
    static void JSExportInitialize();
  };
}} // namespace Titanium { namespace UI {

#endif // _TITANIUM_UI_WEBVIEW_HPP_
