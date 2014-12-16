/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_LISTITEM_HPP_
#define _TITANIUM_UI_LISTITEM_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UI/Constants.hpp"

namespace Titanium { namespace UI {
  
  using namespace HAL;
  
  /*!
   @class
   
   @discussion This is the Titanium.UI.ListItem module.
   
   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.ListItem
   */
  class TITANIUMKIT_EXPORT ListItem : public Module, public JSExport<ListItem> {
    
  public:
    
    /*!
     @method
     
     @abstract accessoryType : Number

     @discussion Sets an accessory on the right side of an item.
     */
    virtual LIST_ACCESSORY_TYPE get_accessoryType() const                                   TITANIUM_NOEXCEPT final;
    virtual void                set_accessoryType(const LIST_ACCESSORY_TYPE& accessoryType) TITANIUM_NOEXCEPT;
    
    ListItem(const JSContext& js_context)                            TITANIUM_NOEXCEPT;
    ListItem(const ListItem&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~ListItem()                  = default;
    ListItem(const ListItem&)            = default;
    ListItem& operator=(const ListItem&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    ListItem(ListItem&&)                 = default;
    ListItem& operator=(ListItem&&)      = default;
#endif
    
    // TODO: The following functions can automatically be generated
    // from the YAML API docs.
    static void JSExportInitialize();
    
    virtual JSValue getAccessoryTypeArgumentValidator() const                  TITANIUM_NOEXCEPT final;
    virtual bool    setAccessoryTypeArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;
    
  private:
    
    LIST_ACCESSORY_TYPE accessoryType__;
  };
}} // namespace Titanium { namespace UI {

#endif // _TITANIUM_UI_LISTITEM_HPP_
