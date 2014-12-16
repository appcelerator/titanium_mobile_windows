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
   
   @discussion This is the Titanium.UI.ListView module.
   
   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.ListView
   */
  class TITANIUMKIT_EXPORT ListView : public View, public JSExport<ListView> {
    
  public:
    
    /*!
     @method
     
     @abstract defaultItemTemplate : String/Number

     @discussion Sets the default template for list data items that do
     not specify the template property. Can be set to any of the
     built-in templates or those defined in the templates
     property. Can be changed dynamically.
     */
    virtual LIST_ITEM_TEMPLATE get_defaultItemTemplate() const                                        TITANIUM_NOEXCEPT final;
    virtual void               set_defaultItemTemplate(const LIST_ITEM_TEMPLATE& defaultItemTemplate) TITANIUM_NOEXCEPT;
    
    ListView(const JSContext& js_context)                            TITANIUM_NOEXCEPT;
    ListView(const ListView&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~ListView()                  = default;
    ListView(const ListView&)            = default;
    ListView& operator=(const ListView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    ListView(ListView&&)                 = default;
    ListView& operator=(ListView&&)      = default;
#endif
    
    // TODO: The following functions can automatically be generated
    // from the YAML API docs.
    static void JSExportInitialize();
    
    virtual JSValue getDefaultItemTemplateArgumentValidator() const                  TITANIUM_NOEXCEPT final;
    virtual bool    setDefaultItemTemplateArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;
    
  private:
    
    LIST_ITEM_TEMPLATE defaultItemTemplate__;
  };
}} // namespace Titanium { namespace UI {

#endif // _TITANIUM_UI_LISTVIEW_HPP_
