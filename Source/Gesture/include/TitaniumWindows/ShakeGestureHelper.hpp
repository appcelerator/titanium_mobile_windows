/**
* Appcelerator Titanium Mobile
* Copyright (c) 2009-2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_SHAKEGESTUREHELPER_HPP_
#define _TITANIUMWINDOWS_SHAKEGESTUREHELPER_HPP_

#define _USE_MATH_DEFINES

#include <chrono>

namespace TitaniumWindows
{
	class ShakeGestureHelper
	{
	   public:
		ShakeGestureHelper();
		virtual ~ShakeGestureHelper();

		bool isShaken(Windows::Devices::Sensors::AccelerometerReading ^ reading);

	   protected:
	   private:
		std::chrono::system_clock::time_point shakeStart_;
	};
}  // namespace Titanium {

#endif  // _TITANIUMWINDOWS_SHAKEGESTUREHELPER_HPP_
