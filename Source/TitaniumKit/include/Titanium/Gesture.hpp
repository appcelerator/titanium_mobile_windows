/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_GESTURE_HPP_
#define _TITANIUM_GESTURE_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UI/Constants.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class
	  @discussion This is the Ti.Gesture Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Ti.Gesture
	*/
	class TITANIUMKIT_EXPORT Gesture : public Module, public JSExport<Gesture>
	{
	public:
		/*!
		  @method
		  @abstract get_Orientation
		  @discussion Orientation of the current window.
		*/
		virtual Titanium::UI::ORIENTATION get_orientation() const TITANIUM_NOEXCEPT;

		Gesture(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~Gesture() = default;
		Gesture(const Gesture&) = default;
		Gesture& operator=(const Gesture&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Gesture(Gesture&&) = default;
		Gesture& operator=(Gesture&&) = default;
#endif

		static void JSExportInitialize();
		static JSObject GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT;

		/*!
		  @method
		  @abstract js_get_orientation
		  @discussion Orientation of the current window.
		*/
		TITANIUM_MODULE_PROPERTY_READONLY_DEF(orientation)

		/*!
		  @method
		  @abstract js_get_landscape
		  @discussion Indicates whether current window is considered landscape by the device.
		*/
		TITANIUM_MODULE_PROPERTY_READONLY_DEF(landscape)
		
		/*!
		  @method
		  @abstract js_get_portrait
		  @discussion Indicates whether current window is considered portrait by the device.
		*/
		TITANIUM_MODULE_PROPERTY_READONLY_DEF(portrait)

		/*!
		  @method
		  @abstract js_getLandscape
		  @discussion Gets the value of the landscape property.
		*/
		TITANIUM_MODULE_FUNCTION_DEF(getLandscape)

		/*!
		  @method
		  @abstract js_getPortrait
		  @discussion Gets the value of the portrait property.
		*/
		TITANIUM_MODULE_FUNCTION_DEF(getPortrait)

		/*!
		  @method
		  @abstract js_getOrientation
		  @discussion Gets the value of the orientation property.
		*/
		TITANIUM_MODULE_FUNCTION_DEF(getOrientation)

		/*!
		  @method
		  @abstract js_isFaceDown
		  @discussion Returns whether current window is considered face down by the device.
		*/
		TITANIUM_MODULE_FUNCTION_DEF(isFaceDown)

		/*!
		  @method
		  @abstract js_isFaceUp
		  @discussion Returns whether current window is considered face up by the device.
		*/
		TITANIUM_MODULE_FUNCTION_DEF(isFaceUp)
		TITANIUM_MODULE_FUNCTION_DEF(isLandscape)
		TITANIUM_MODULE_FUNCTION_DEF(isPortrait)

		virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
		virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;

	};
}  // namespace Titanium

#endif  // _TITANIUM_GESTURE_HPP_
