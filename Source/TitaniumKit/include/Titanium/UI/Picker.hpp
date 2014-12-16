/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_LISTVIEW_HPP_
#define _TITANIUM_UI_LISTVIEW_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Constants.hpp"

namespace Titanium { namespace UI {
  
  using namespace HAL;
  
  /*!
   @class
   
   @discussion This is the Titanium.UI.Picker module.
   
   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.Picker
   */
  class TITANIUMKIT_EXPORT Picker : public View, public JSExport<Picker> {
    
  public:
    
    /*!
     @method
     
     @abstract type : Number

     @discussion Determines the type of picker displayed. You can only
     set columns for the plain picker. If you set the type to anything
     else except Titanium.UI.PICKER_TYPE_PLAIN, you cannot modify the
     columns.
     */
    virtual PICKER_TYPE get_type() const                  TITANIUM_NOEXCEPT final;
    virtual void        set_type(const PICKER_TYPE& type) TITANIUM_NOEXCEPT;
    
    Picker(const JSContext& js_context)                          TITANIUM_NOEXCEPT;
    Picker(const Picker&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~Picker()                = default;
    Picker(const Picker&)            = default;
    Picker& operator=(const Picker&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    Picker(Picker&&)                 = default;
    Picker& operator=(Picker&&)      = default;
#endif
    
    // TODO: The following functions can automatically be generated
    // from the YAML API docs.
    static void JSExportInitialize();
    
    virtual JSValue getTypeArgumentValidator() const                  TITANIUM_NOEXCEPT final;
    virtual bool    setTypeArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;
    
  private:
    
    PICKER_TYPE type__;
  };
}} // namespace Titanium { namespace UI {

#endif // _TITANIUM_UI_LISTVIEW_HPP_
