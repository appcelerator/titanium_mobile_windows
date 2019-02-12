/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Gesture.hpp"
#include <iostream>
#include <objbase.h>

namespace TitaniumWindows
{
	// Setup orientation event listener
	// This method should be called after main Window is initialized,
	// otherwise DisplayInformation::GetForCurrentView() will fail.
	void Gesture::setupOrientationListener()
	{
		using namespace std::placeholders;
		using namespace Windows::Graphics::Display;
		if (!orientationEventSet_) {
			const auto display = DisplayInformation::GetForCurrentView();
			// Setup OrientationChanged event
			const auto orientationchangeCallback = [this](DisplayInformation^ sender, ::Platform::Object^ args) {
				try {
					const auto ctx = get_context();
					auto obj = ctx.CreateObject();
					obj.SetProperty("orientation", ctx.CreateNumber(Titanium::UI::Constants::to_underlying_type(updateOrientation())));

					TitaniumWindows::Utility::RunOnUIThread([this, obj]() {
						fireEvent("orientationchange", obj);
					});
				} catch (...) {
					TITANIUM_LOG_DEBUG("Error at Gesture.orientationchange");
				}
			};

			orientationchange_event_ = display->OrientationChanged += ref new Windows::Foundation::TypedEventHandler<Windows::Graphics::Display::DisplayInformation^, ::Platform::Object^>(orientationchangeCallback);
			orientationEventSet_ = true;
		}
	}

	Gesture::Gesture(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Titanium::Gesture(js_context)
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Gesture::ctor");
		setupOrientationListener();
	}

	Gesture::~Gesture()
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Gesture::dtor");
		if (orientationEventSet_) {
			const auto display = Windows::Graphics::Display::DisplayInformation::GetForCurrentView();
			display->OrientationChanged -= orientationchange_event_;
			orientationEventSet_ = false;
		}
	}

	void Gesture::JSExportInitialize()
	{
		JSExport<Gesture>::SetClassVersion(1);
		JSExport<Gesture>::SetParent(JSExport<Titanium::Gesture>::Class());
	}

	void Gesture::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Gesture::enableEvent");
		if (event_name == "shake") {
			accelerometer_ = Windows::Devices::Sensors::Accelerometer::GetDefault();

			if (accelerometer_ == nullptr) {
				std::clog << "[ERROR] Ti.Gesture: No accelerometer found" << std::endl;
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
					try {
						auto obj = ctx.CreateObject();
						const auto reading = self->accelerometer_->GetCurrentReading();
						unsigned timestamp = 0;
						if (self->previous_acceleromter_time_.UniversalTime > 0) {
							timestamp = static_cast<unsigned>((reading->Timestamp.UniversalTime - self->previous_acceleromter_time_.UniversalTime) / 10000.0);
							// wait for 500 milliseconds until next shake event (taken from Titanium Android)
							if (timestamp < 500) {
								return;
							}
						}

						if (self->shakeGestureHelper.isShaken(reading)) {
							self->previous_acceleromter_time_ = reading->Timestamp;
							obj.SetProperty("timestamp", ctx.CreateNumber(timestamp));
							obj.SetProperty("x", ctx.CreateNumber(reading->AccelerationX));
							obj.SetProperty("y", ctx.CreateNumber(reading->AccelerationY));
							obj.SetProperty("z", ctx.CreateNumber(reading->AccelerationZ));
							self->fireEvent("shake", obj);
						}
					} catch (...) {
						TITANIUM_LOG_DEBUG("Error at Gesture.shake");
					}
				};

				if (current) {
					current->Dispatcher->RunAsync(
						Windows::UI::Core::CoreDispatcherPriority::Normal,
						ref new Windows::UI::Core::DispatchedHandler(dispatchedCallback));
				}
			};

			shake_event_ = accelerometer_->ReadingChanged += ref new Windows::Foundation::TypedEventHandler<Windows::Devices::Sensors::Accelerometer^, Windows::Devices::Sensors::AccelerometerReadingChangedEventArgs^>(updateCallback);
		}
	}

	void Gesture::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Gesture::disableEvent");
		if (event_name == "shake") {
			accelerometer_->ReadingChanged -= shake_event_;
		}
	}

	Titanium::UI::ORIENTATION Gesture::get_orientation() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("TitaniumWindows::Gesture::get_orientation");
		return orientation_;
	}

	Titanium::UI::ORIENTATION Gesture::updateOrientation()
	{
		using namespace Windows::Graphics::Display;
		const auto display = DisplayInformation::GetForCurrentView();
		const auto orientation = display->CurrentOrientation;
		if (orientation == DisplayOrientations::Landscape) {
			orientation_ = Titanium::UI::ORIENTATION::LANDSCAPE_LEFT;
		} else if (orientation == DisplayOrientations::LandscapeFlipped) {
			orientation_ = Titanium::UI::ORIENTATION::LANDSCAPE_RIGHT;
		} else if (orientation == DisplayOrientations::Portrait) {
			orientation_ = Titanium::UI::ORIENTATION::PORTRAIT;
		} else if (orientation == DisplayOrientations::PortraitFlipped) {
			orientation_ = Titanium::UI::ORIENTATION::UPSIDE_PORTRAIT;
		} else {
			orientation_ = Titanium::UI::ORIENTATION::UNKNOWN;
		}
		return orientation_;
	}
}  // namespace TitaniumWindows
