/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_WEBVIEWERROREVENT_HPP_
#define _TITANIUM_UI_WEBVIEWERROREVENT_HPP_

#include "Titanium/detail/TiBase.hpp"
#include "Titanium/UI/Constants.hpp"

namespace Titanium { namespace UI {
  
  using namespace HAL;
  
  /*!
   @class
   
   @discussion This is the Titanium.UI.WebView.error event module. This event is fired when the web view cannot load the content.
   
   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.WebView-event-error
   */
  class TITANIUMKIT_EXPORT WebViewErrorEvent : public JSExportObject, public JSExport<WebViewErrorEvent> {
    
  public:
    
    /*!
     @method
     
     @abstract error : Event

     @discussion Fired when the web view cannot load the content.
     */
    virtual URL_ERROR get_error() const                 TITANIUM_NOEXCEPT final;
    virtual void      set_error(const URL_ERROR& error) TITANIUM_NOEXCEPT;
    
    WebViewErrorEvent(const JSContext& js_context)                                     TITANIUM_NOEXCEPT;
    WebViewErrorEvent(const WebViewErrorEvent&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~WebViewErrorEvent()                           = default;
    WebViewErrorEvent(const WebViewErrorEvent&)            = default;
    WebViewErrorEvent& operator=(const WebViewErrorEvent&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    WebViewErrorEvent(WebViewErrorEvent&&)                 = default;
    WebViewErrorEvent& operator=(WebViewErrorEvent&&)      = default;
#endif
    
    // TODO: The following functions can automatically be generated
    // from the YAML API docs.
    static void JSExportInitialize();
    
    virtual JSValue getErrorArgumentValidator() const                  TITANIUM_NOEXCEPT final;
    virtual bool    setErrorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;
    
  private:
    
    URL_ERROR error__;
  };
}} // namespace Titanium { namespace UI {

#endif // _TITANIUM_UI_WEBVIEWERROREVENT_HPP_
