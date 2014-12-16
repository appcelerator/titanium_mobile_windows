/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_WINDOW_HPP_
#define _TITANIUM_UI_WINDOW_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Constants.hpp"

namespace Titanium { namespace UI {
  
  using namespace HAL;
  
  /*!
   @class
   
   @discussion This is the Titanium UI Window.
   
   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.Window
   */
  class TITANIUMKIT_EXPORT Window : public View, public JSExport<Window> {
    
  public:
    
    /*!
     @method
     
     @abstract open( [params] ) : void
     
     @discussion Opens the window.
     
     @param params Optimized animation or display properties to use
     when opening the window. (openWindowParams)
     
     @result void
     */
    virtual void open(const JSObject& params, JSObject& this_object) const TITANIUM_NOEXCEPT;
    
    /*!
     @method
     
     @abstract extendEdges : Number[]
     
     @discussion An array of supported values specified using the EXTEND_EDGE constants in Titanium.UI.
     */
    virtual std::unordered_set<EXTEND_EDGE> get_extendEdges() const                                             TITANIUM_NOEXCEPT final;
    virtual void                            set_extendEdges(const std::unordered_set<EXTEND_EDGE>& extendEdges) TITANIUM_NOEXCEPT;

    Window(const JSContext& js_context)                          TITANIUM_NOEXCEPT;
    Window(const Window&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~Window()                   = default;
    Window(const Window&)               = default;
    Window& operator=(const Window&)    = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    Window(Window&&)                    = default;
    Window& operator=(Window&&)         = default;
#endif
    
    // TODO: The following functions can automatically be generated
    // from the YAML API docs.
    static void JSExportInitialize();
    
    virtual JSValue openArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue getExtendEdgesArgumentValidator() const                                             TITANIUM_NOEXCEPT final;
    virtual bool    setExtendEdgesArgumentValidator(const JSValue& argument)                            TITANIUM_NOEXCEPT final;
    
  private:
    
    // Silence 4251 on Windows since private member variables do not
    // need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable: 4251)
    std::unordered_set<EXTEND_EDGE> extendEdges__;
#pragma warning(pop)
  };
}} // namespace Titanium { namespace UI {

#endif // _TITANIUM_UI_WINDOW_HPP_
