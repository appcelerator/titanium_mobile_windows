/**
 * TitaniumKit
 * Author: Matthew D. Langston
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_GESTURE_HPP_
#define _TITANIUM_GESTURE_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UI/Constants.hpp"

namespace Titanium {
  
  using namespace JavaScriptCoreCPP;
  
  /*!
   @class
   
   @discussion This is the Titanium.Gesture module.
   
   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Gesture
   */
  class TITANIUMKIT_EXPORT Gesture : public Module, public JSExport<Gesture> {
    
  public:
    
    /*!
     @method
     
     @abstract orientation : Number
     
     @discussion Orientation of the current window
     */
    virtual Titanium::UI::ORIENTATION get_orientation() const TITANIUM_NOEXCEPT;
    
    Gesture(const JSContext& js_context)                           TITANIUM_NOEXCEPT;
    Gesture(const Gesture&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~Gesture()                 = default;
    Gesture(const Gesture&)            = default;
    Gesture& operator=(const Gesture&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    Gesture(Gesture&&)                 = default;
    Gesture& operator=(Gesture&&)      = default;
#endif
    
    // TODO: The following functions can automatically be generated
    // from the YAML API docs.
    static void JSExportInitialize();
    
    virtual JSValue get_orientation_ArgumentValidator() const TITANIUM_NOEXCEPT final;
    virtual JSValue get_landscape_ArgumentValidator() const TITANIUM_NOEXCEPT final;
    virtual JSValue get_portrait_ArgumentValidator() const TITANIUM_NOEXCEPT final;

    virtual JSValue getLandscape_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue getPortrait_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue getOrientation_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue isFaceDown_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    virtual JSValue isFaceUp_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
    
    virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
    virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;

  };
} // namespace Titanium {

#endif // _TITANIUM_GESTURE_HPP_
