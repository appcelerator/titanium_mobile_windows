/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_MODULE_HPP_
#define _TITANIUM_MODULE_HPP_

#include "Titanium/detail/TiBase.hpp"
#include <unordered_map>
#include <vector>

namespace Titanium {
  
  using namespace HAL;
  
  /*!
   @class
   
   @discussion This is the Titanium Module.
   
   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium
   */
  class TITANIUMKIT_EXPORT Module : public JSExportObject, public JSExport<Module> {
    
  public:
    
    /*!
     @method
     
     @abstract addEventListener( name, callback ) : void
     
     @discussion Adds the specified callback as an event listener for
     the named event.
     
     @param name Name of the event (String).
     
     @param callback Callback function to invoke when the event is
     fired (Function).
     
     @result void
     */
    virtual void addEventListener(const std::string& name, JSObject& callback, JSObject& this_object) TITANIUM_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract addEventListener( name, callback ) : void
     
     @discussion Removes the specified callback as an event listener
     for the named event.
     
     Multiple listeners can be registered for the same event, so the
     callback parameter is used to determine which listener to remove.
     
     When adding a listener, you must save a reference to the callback
     function in order to remove the listener later:
     
     @param name Name of the event (String).
     
     @param callback Callback function to invoke when the event is
     fired (Function).
     
     @result void
     */
    virtual void removeEventListener(const std::string& name, JSObject& callback, JSObject& this_object) TITANIUM_NOEXCEPT final;
    
    /*!
     @method
     
     @abstract applyProperties( props ) : void
     
     @discussion Copy the enumerable properties from the given
     JavaScript object to this JavaScript object.
     
     @param props The JavaScript object to copy the properties from
     (Dictionary).
     
     @result void
     */
    virtual void applyProperties(const JSObject& props, JSObject& this_object) TITANIUM_NOEXCEPT;
    
    /*!
     @method
     
     @abstract fireEvent( name, event ) : void
     
     @discussion Fires a synthesized event to any registered
     listeners.
     
     @param name Name of the event (String).
     
     @param event A dictionary of keys and values to add to the
     Titanium.Event object sent to the listeners. (Dictionary).
     
     @result void
     */
    virtual void fireEvent(const std::string& name, const JSObject& event) const TITANIUM_NOEXCEPT final;
    
    Module(const JSContext& js_context)                          TITANIUM_NOEXCEPT;
    Module(const Module&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~Module()                = default;
    Module(const Module&)            = default;
    Module& operator=(const Module&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    Module(Module&&)                 = default;
    Module& operator=(Module&&)      = default;
#endif
    
    // TODO: The following functions can automatically be generated from
    // the YAML API docs.
    static void JSExportInitialize();
    JSValue addEventListenerArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object);
    JSValue removeEventListenerArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object);
    JSValue applyPropertiesArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object);
    JSValue fireEventArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object);
    
  protected:
    
    
    /*!
     @method
     
     @abstract Notify Module subclasses that there are event listeners
     for the event with the given name.
     
     @param event_name Name of the event for which there are event
     listeners.
     
     @result void
     */
    virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT;
    
    /*!
     @method
     
     @abstract Notify Module subclasses that there are no longer any
     event listeners for the event with the given name. It is
     guaranteed that the method enableEvent will have been called
     before disableEvent.
     
     @param event_name Name of the event for which there are no longer
     any event listeners.
     
     @result void
     */
    virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT;
    
  private:
    
    static unsigned eventListenerIndex(const JSObject& event_listener_list, const std::string& name, JSObject& callback) TITANIUM_NOEXCEPT;
    
    JSObject event_listener_map__;
  };
} // namespace Titanium {

#endif // _TITANIUM_MODULE_HPP_
