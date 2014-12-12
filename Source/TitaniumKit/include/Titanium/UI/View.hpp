/**
 * TitaniumKit
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_VIEW_HPP_
#define _TITANIUM_UI_VIEW_HPP_

#include "Titanium/Module.hpp"
#include <vector>
#include <memory>

namespace Titanium { namespace UI {
  
  using namespace JavaScriptCoreCPP;
  
  class View;
  
  using NativeChildPtr_t     = std::shared_ptr<Titanium::UI::View>;
  using NativeChildrenList_t = std::vector<NativeChildPtr_t>;
  
  /*!
   @class
   
   @discussion This is the Titanium UI View.
   
   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.View
   */
  class TITANIUMKIT_EXPORT View : public Module, public JSExport<View> {
    
  public:
    
    /*!
     @method
     
     @abstract add( view ) : void
     
     @discussion Adds a child to this view's hierarchy. The child view
     is added as the last child in this view's hierarchy.
     
     @param view View to add to this view's
     hierarchy. (Titanium.UI.View)
     
     @result void
     */
    virtual void add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT;
    
    virtual JSArray get_children() const TITANIUM_NOEXCEPT final;
    
    virtual JSValue get_backgroundColor() const                         TITANIUM_NOEXCEPT final;
    virtual void    set_backgroundColor(const JSValue& backgroundColor) TITANIUM_NOEXCEPT final;
    
    View(const JSContext& js_context)                        TITANIUM_NOEXCEPT;
    View(const View&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~View()              = default;
    View(const View&)            = default;
    View& operator=(const View&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    View(View&&)                 = default;
    View& operator=(View&&)      = default;
#endif
    
    // TODO: The following functions can automatically be generated
    // from the YAML API docs.
    static void JSExportInitialize();
    
    virtual JSValue addArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    
    // Base classes must implement this method. This is the minimum
    // functionality that you should perform:
    //
    // assert(argument.IsString());
    // bool result = false;
    // std::string backgroundColor = static_cast<std::string>(argument);
    // Set the native view's background color to backgroundColor.
    // set_backgroundColor(argument);
    // result = true;
    // return result;
    virtual bool setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT;
    
  protected:
    
    virtual NativeChildrenList_t get_native_children() const TITANIUM_NOEXCEPT final;
    
  private:
    
    JSArray children__;
    JSValue backgroundColor__;
    
  };
}} // namespace Titanium { namespace UI {

#endif // _TITANIUM_UI_VIEW_HPP_
