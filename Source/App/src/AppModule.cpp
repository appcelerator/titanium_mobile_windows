/**
* Titanium.App for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/AppModule.hpp"

using namespace Windows::Foundation;
using namespace Windows::UI::ViewManagement;

namespace TitaniumWindows
{
	AppModule::AppModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::AppModule(js_context)
	{
		TITANIUM_LOG_DEBUG("AppModule::ctor Initialize");
	}

	void AppModule::JSExportInitialize() {
		JSExport<AppModule>::SetClassVersion(1);
		JSExport<AppModule>::SetParent(JSExport<Titanium::AppModule>::Class());
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
		}
	}

	void AppModule::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
	{
		Titanium::AppModule::disableEvent(event_name);
		if (event_name == "keyboardframechanged") {
			Windows::UI::ViewManagement::InputPane::GetForCurrentView()->Showing -= keyboardframe_showing_event__;
			Windows::UI::ViewManagement::InputPane::GetForCurrentView()->Hiding  -= keyboardframe_hiding_event__;
		}
	}

	bool AppModule::keyboardVisible() const TITANIUM_NOEXCEPT
	{
		return keyboardVisible__;
	}

}  // namespace TitaniumWindows