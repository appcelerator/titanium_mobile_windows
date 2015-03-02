/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Accelerometer.hpp"
#include "Titanium/detail/TiBase.hpp"
#include <iostream>
#include <objbase.h>

namespace TitaniumWindows
{
	Accelerometer::Accelerometer(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Titanium::Accelerometer(js_context)
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Accelerometer::ctor");
	}

	void Accelerometer::JSExportInitialize()
	{
		JSExport<Accelerometer>::SetClassVersion(1);
		JSExport<Accelerometer>::SetParent(JSExport<Titanium::Accelerometer>::Class());
	}

	void Accelerometer::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Accelerometer::enableEvent: (event name '", event_name, "'");
		if (event_name == "update") {
			accelerometer_ = Windows::Devices::Sensors::Accelerometer::GetDefault();

			if (accelerometer_ == nullptr) {
				std::clog << "[ERROR] Ti.Accelerometer: No accelerometer found" << std::endl;
				return;
			}

			// Select a report interval that is both suitable for the purposes of the app and supported by the sensor.
			const auto minReportInterval = accelerometer_->MinimumReportInterval;
			accelerometer_->ReportInterval = minReportInterval > 16 ? minReportInterval : 16;

			// Capture Window::Current here because getting it outside of UI thread seems always return nullptr
			const auto current = Windows::UI::Xaml::Window::Current;
			const auto self = this;

			using namespace std::placeholders;
			const auto updateCallback = [current, self](Windows::Devices::Sensors::Accelerometer^ sender, Windows::Devices::Sensors::AccelerometerReadingChangedEventArgs^ e) {
				const auto dispatchedCallback = [current, self]() {
					const auto ctx = self->get_context();
					auto obj = ctx.CreateObject();
					const auto reading = self->accelerometer_->GetCurrentReading();
					unsigned long long timestamp = 0;
					if (self->previous_acceleromter_time_.UniversalTime > 0) {
						timestamp = (reading->Timestamp.UniversalTime - self->previous_acceleromter_time_.UniversalTime) / 10000;
						// Suppress fireEvent so that it doesn't block UI thread (taken from Titanium Android)
						if (timestamp < 100) {
							return;
						}
					}
					self->previous_acceleromter_time_ = reading->Timestamp;
					obj.SetProperty("timestamp", ctx.CreateNumber(static_cast<double>(timestamp)));
					obj.SetProperty("x", ctx.CreateNumber(reading->AccelerationX));
					obj.SetProperty("y", ctx.CreateNumber(reading->AccelerationY));
					obj.SetProperty("z", ctx.CreateNumber(reading->AccelerationZ));

					self->fireEvent("update", obj);
				};

				if (current) {
					current->Dispatcher->RunAsync(
						Windows::UI::Core::CoreDispatcherPriority::Normal,
						ref new Windows::UI::Core::DispatchedHandler(dispatchedCallback));
				}
			};

			update_event_ = accelerometer_->ReadingChanged += ref new Windows::Foundation::TypedEventHandler<Windows::Devices::Sensors::Accelerometer^, Windows::Devices::Sensors::AccelerometerReadingChangedEventArgs^>(updateCallback);
		}
	}

	void Accelerometer::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Accelerometer::disableEvent: (event name '", event_name, "'");
		if (event_name == "update") {
			accelerometer_->ReadingChanged -= update_event_;
		}
	}

}  // namespace TitaniumWindows
