/**
* Appcelerator Titanium Mobile
* Copyright (c) 2009-2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/ShakeGestureHelper.hpp"
#include <math.h>

namespace TitaniumWindows {

  ShakeGestureHelper::ShakeGestureHelper() {
  }

  ShakeGestureHelper::~ShakeGestureHelper() {
  }

  // detect shake event
  bool ShakeGestureHelper::isShaken(Windows::Devices::Sensors::AccelerometerReading^ reading) {
    using namespace std::chrono;

    const auto x = reading->AccelerationX;
    const auto y = reading->AccelerationY;
    const auto z = reading->AccelerationZ;

    // should be close to 1 when there's no force
    if (sqrt(x*x + y*y + z*z) > 1.2) {
      const auto now = high_resolution_clock::now();
      const auto duration = duration_cast<milliseconds>(now - shakeStart_);
      // set shake resolution time
      if (duration.count() > 500) {
        shakeStart_ = now;
        return true;
      }
    }

    return false;
  }
} // namespace TitaniumWindows

