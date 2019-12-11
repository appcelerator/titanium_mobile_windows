/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_ACCELEROMETER_HPP_
#define _TITANIUM_ACCELEROMETER_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class
	  @discussion This is the Ti.Accelerometer Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Ti.Accelerometer
	*/
	class TITANIUMKIT_EXPORT Accelerometer : public Module, public JSExport<Accelerometer>
	{
	public:
		Accelerometer(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~Accelerometer() = default;
		Accelerometer(const Accelerometer&) = default;
		Accelerometer& operator=(const Accelerometer&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Accelerometer(Accelerometer&&) = default;
		Accelerometer& operator=(Accelerometer&&) = default;
#endif

		static void JSExportInitialize();

		virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
		virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
	};

}  // namespace Titanium

#endif  // _TITANIUM_ACCELEROMETER_HPP_
