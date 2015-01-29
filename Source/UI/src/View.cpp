/**
 * Titanium.UI.View for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/View.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		View::View(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::UI::View(js_context, arguments),
			  ViewBase(js_context, arguments),
		      canvas__(ref new Windows::UI::Xaml::Controls::Canvas())
		{
			TITANIUM_LOG_DEBUG("View::ctor");

			setDefaultHeight(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
			setDefaultWidth(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));

			setComponent(canvas__);
		}

		void View::JSExportInitialize()
		{
			JSExport<View>::SetClassVersion(1);
			JSExport<View>::SetParent(JSExport<Titanium::UI::View>::Class());
		}

		void View::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("View::enableEvent: (event name '", event_name, "'");

			const JSContext ctx = this->get_context();

			using namespace Windows::UI::Xaml::Input;
			using namespace Windows::UI::Xaml;

			if (event_name == "touchmove") {
				if (touch_move_event_count_ == 0) {
					getComponent()->ManipulationMode = ManipulationModes::All;
					touch_move_event_ = getComponent()->ManipulationDelta += ref new ManipulationDeltaEventHandler([ctx, this](Platform::Object^ sender, ManipulationDeltaRoutedEventArgs^ e) {
						JSObject  delta = ctx.CreateObject();
						delta.SetProperty("x", ctx.CreateNumber(e->Delta.Translation.X));
						delta.SetProperty("y", ctx.CreateNumber(e->Delta.Translation.Y));

						JSObject  eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("x", ctx.CreateNumber(e->Position.X));
						eventArgs.SetProperty("y", ctx.CreateNumber(e->Position.Y));
						eventArgs.SetProperty("delta", delta);

						this->fireEvent("touchmove", eventArgs);
					});
				}

				++touch_move_event_count_;

				return;
			}
		}
	} // namespace UI
} // namespace TitaniumWindows
