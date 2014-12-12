/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_ACCELEROMETER_HPP_
#define _TITANIUMWINDOWS_ACCELEROMETER_HPP_

#include "TitaniumWindows/detail/AccelerometerBase.hpp"

namespace TitaniumWindows {

  using namespace JavaScriptCoreCPP;

  /*!
    @class

    @discussion This is the Titanium.Accelerometer implementation for Windows.
    */
  class TITANIUMWINDOWS_ACCELEROMETER_EXPORT Accelerometer final : public Titanium::Accelerometer, public JSExport < Accelerometer > {

  public:

    Accelerometer(const JSContext& js_context) TITANIUM_NOEXCEPT;
    Accelerometer(const Accelerometer&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

    virtual ~Accelerometer()             = default;
    Accelerometer(const Accelerometer&)            = default;
    Accelerometer& operator=(const Accelerometer&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    Accelerometer(Accelerometer&&)                 = default;
    Accelerometer& operator=(Accelerometer&&)      = default;
#endif

    static void JSExportInitialize();

	virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
	virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;

  protected:

  private:
    Windows::Foundation::DateTime previous_acceleromter_time_;
	  Windows::Devices::Sensors::Accelerometer^ accelerometer_;

	  Windows::Foundation::EventRegistrationToken update_event_;
  };

}  // namespace TitaniumWindows

#endif // _TITANIUMWINDOWS_ACCELEROMETER_HPP_
