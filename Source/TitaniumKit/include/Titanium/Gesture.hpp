/**
 * TitaniumKit
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

using namespace HAL;

/*!
   @class
   @discussion This is the Ti.Gesture Module.
   See http://docs.appcelerator.com/titanium/latest/#!/api/Ti.Gesture
  */
class TITANIUMKIT_EXPORT Gesture : public Module, public JSExport<Gesture> {
 public:
  /*!
     @method
     @abstract get_Orientation
     @discussion Orientation of the current window.
    */
  virtual Titanium::UI::ORIENTATION get_orientation() const TITANIUM_NOEXCEPT;

  Gesture(const JSContext& js_context) TITANIUM_NOEXCEPT;
  Gesture(const Gesture&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

  virtual ~Gesture() = default;
  Gesture(const Gesture&) = default;
  Gesture& operator=(const Gesture&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
  Gesture(Gesture&&) = default;
  Gesture& operator=(Gesture&&) = default;
#endif

  static void JSExportInitialize();

  /*!
     @method
     @abstract get_orientation_ArgumentValidator
     @discussion Orientation of the current window.
    */
  virtual JSValue get_orientation_ArgumentValidator() const TITANIUM_NOEXCEPT final;

  /*!
     @method
     @abstract get_landscape_ArgumentValidator
     @discussion Indicates whether current window is considered landscape by the device.
    */
  virtual JSValue get_landscape_ArgumentValidator() const TITANIUM_NOEXCEPT final;
  /*!
     @method
     @abstract get_portrait_ArgumentValidator
     @discussion Indicates whether current window is considered portrait by the device.
    */
  virtual JSValue get_portrait_ArgumentValidator() const TITANIUM_NOEXCEPT final;

  /*!
     @method
     @abstract getLandscape_ArgumentValidator
     @discussion Gets the value of the landscape property.
    */
  virtual JSValue getLandscape_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

  /*!
     @method
     @abstract getPortrait_ArgumentValidator
     @discussion Gets the value of the portrait property.
    */
  virtual JSValue getPortrait_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

  /*!
     @method
     @abstract getOrientation_ArgumentValidator
     @discussion Gets the value of the orientation property.
    */
  virtual JSValue getOrientation_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

  /*!
     @method
     @abstract isFaceDown_ArgumentValidator
     @discussion Returns whether current window is considered face down by the device.
    */
  virtual JSValue isFaceDown_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

  /*!
     @method
     @abstract isFaceUp_ArgumentValidator
     @discussion Returns whether current window is considered face up by the device.
    */
  virtual JSValue isFaceUp_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
  virtual JSValue isLandscape_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
  virtual JSValue isPortrait_ArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

  virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
  virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
};
}  // namespace Titanium {

#endif  // _TITANIUM_GESTURE_HPP_
