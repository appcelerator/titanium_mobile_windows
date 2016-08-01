/**
* Titanium.App for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/AppModule.hpp"
#include "TitaniumWindows/App/WindowsModule.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include "TitaniumWindows/Utility.hpp"
#include <concrt.h>

using namespace Windows::Foundation;
using namespace Windows::UI::ViewManagement;
using namespace Windows::Devices::Enumeration;
using namespace Windows::Devices::Sensors;

namespace TitaniumWindows
{
	AppModule::AppModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::AppModule(js_context)
	{
		TITANIUM_LOG_DEBUG("AppModule::ctor Initialize");
	}

	void AppModule::JSExportInitialize() 
	{
		JSExport<AppModule>::SetClassVersion(1);
		JSExport<AppModule>::SetParent(JSExport<Titanium::AppModule>::Class());
		TITANIUM_ADD_CONSTANT_PROPERTY(AppModule, Windows);
	}

	TITANIUM_PROPERTY_GETTER(AppModule, Windows)
	{
		return get_context().CreateObject(JSExport<TitaniumWindows::App::WindowsModule>::Class());
	}

	JSObject AppModule::RectToJS(const JSContext& js_context, const Windows::Foundation::Rect& rect)
	{
		auto obj = js_context.CreateObject();
		obj.SetProperty("width", js_context.CreateNumber(rect.Width));
		obj.SetProperty("height", js_context.CreateNumber(rect.Height));
		obj.SetProperty("x", js_context.CreateNumber(rect.X));
		obj.SetProperty("y", js_context.CreateNumber(rect.Y));
		return obj;
	}

	void AppModule::initProximitySensor()
	{
#if defined(IS_WINDOWS_10)
		if (!no_proximitySensor__) {
			concurrency::event evt;
			const auto watcher = DeviceInformation::CreateWatcher(ProximitySensor::GetDeviceSelector());
			const auto watcher_event = watcher->Added += ref new TypedEventHandler<DeviceWatcher^, DeviceInformation^>([&](DeviceWatcher^ sender, DeviceInformation^ device) {
				if (proximitySensor__ == nullptr) {
					proximitySensor__ = ProximitySensor::FromId(device->Id);
				}
				sender->Stop();
				evt.set();
			});
			watcher->Start();
			evt.wait(3000); // timeout to detect sensor
			if (proximitySensor__ == nullptr) {
				watcher->Stop();
				no_proximitySensor__ = true;
				TITANIUM_LOG_WARN("Device does not contain a proximity sensor!");
			}
			watcher->Added -= watcher_event;
		}
#endif
	}

	void AppModule::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		Titanium::AppModule::enableEvent(event_name);
		if (event_name == "keyboardframechanged") {
			keyboardframe_showing_event__ = InputPane::GetForCurrentView()->Showing += ref new TypedEventHandler<InputPane^, InputPaneVisibilityEventArgs^>([this](InputPane^ sender, InputPaneVisibilityEventArgs^ e) {
				keyboardVisible__ = true;
				const auto ctx = this->get_context();
				auto event_arg = ctx.CreateObject();
				event_arg.SetProperty("keyboardFrame", RectToJS(ctx, e->OccludedRect));
				this->fireEvent("keyboardframechanged", event_arg);
			});
			keyboardframe_hiding_event__ = InputPane::GetForCurrentView()->Hiding += ref new TypedEventHandler<InputPane^, InputPaneVisibilityEventArgs^>([this](InputPane^ sender, InputPaneVisibilityEventArgs^ e) {
				keyboardVisible__ = false;
				const auto ctx = this->get_context();
				auto event_arg = ctx.CreateObject();
				event_arg.SetProperty("keyboardFrame", RectToJS(ctx, e->OccludedRect));
				this->fireEvent("keyboardframechanged", event_arg);
			});
		} else if (event_name == "proximity") {
#if defined(IS_WINDOWS_10)
			if (proximitySensor__ == nullptr) {
				initProximitySensor();
			}
			if (!no_proximitySensor__) {
				proximity_event__ = proximitySensor__->ReadingChanged += ref new TypedEventHandler<ProximitySensor^, ProximitySensorReadingChangedEventArgs^>([this](ProximitySensor^ sender, ProximitySensorReadingChangedEventArgs^ e) {
					if (proximityDetection__) {
						const auto ctx = this->get_context();
						auto event_arg = ctx.CreateObject();
						event_arg.SetProperty("state", ctx.CreateBoolean(e->Reading->IsDetected));
						TitaniumWindows::Utility::RunOnUIThread([this, event_arg]() {
							this->fireEvent("proximity", event_arg);
						});
					}
				});
			}
#endif
		}
	}

	void AppModule::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		Titanium::AppModule::disableEvent(event_name);
		if (event_name == "keyboardframechanged") {
			Windows::UI::ViewManagement::InputPane::GetForCurrentView()->Showing -= keyboardframe_showing_event__;
			Windows::UI::ViewManagement::InputPane::GetForCurrentView()->Hiding  -= keyboardframe_hiding_event__;
		} else if (event_name == "proximity") {
#if defined(IS_WINDOWS_10)
			if (proximitySensor__) {
				proximitySensor__->ReadingChanged -= proximity_event__;
			}
#endif
		}
	}

	void AppModule::setProximityDetection(const bool& proximityDetection) TITANIUM_NOEXCEPT
	{
		Titanium::AppModule::setProximityDetection(proximityDetection);
#if defined(IS_WINDOWS_10)
		if (proximityDetection__ && proximitySensor__ == nullptr) {
			initProximitySensor();
		}
#else
		TITANIUM_LOG_WARN("Titanium.App.proximityDetection is only supported on Windows 10");
#endif
	}

	bool AppModule::proximityState() const TITANIUM_NOEXCEPT
	{
#if defined(IS_WINDOWS_10)
		if (proximityDetection__ && proximitySensor__) {
			const auto reading = proximitySensor__->GetCurrentReading();
			return reading->IsDetected;
		}
#endif
		return false;
	}

	bool AppModule::keyboardVisible() const TITANIUM_NOEXCEPT
	{
		return keyboardVisible__;
	}

}  // namespace TitaniumWindows