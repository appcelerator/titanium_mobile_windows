/**
 * Titanium.UI.View for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		View::View(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::View(js_context)
		{
		}

		void View::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::View::postCallAsConstructor(js_context, arguments);	
			
			canvas__ = ref new Windows::UI::Xaml::Controls::Canvas();

			Titanium::UI::View::setLayoutDelegate<WindowsViewLayoutDelegate>();

			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);

			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(canvas__);
		}

		void View::JSExportInitialize()
		{
			JSExport<View>::SetClassVersion(1);
			JSExport<View>::SetParent(JSExport<Titanium::UI::View>::Class());
		}

		Windows::UI::Xaml::FrameworkElement^ View::getComponent() TITANIUM_NOEXCEPT
		{
			return getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
		}

		void View::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			using namespace Windows::UI::Xaml::Input;
			using namespace Windows::UI::Xaml;

			if (event_name == "touchmove") {
				auto component = getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
				component->ManipulationMode = ManipulationModes::All;
				touch_move_event_ = component->ManipulationDelta += ref new ManipulationDeltaEventHandler([ctx, this](Platform::Object^ sender, ManipulationDeltaRoutedEventArgs^ e) {
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
			else if (event_name == "focus") {
				focus_event_ = getComponent()->GotFocus += ref new RoutedEventHandler([this, ctx](Platform::Object^ sender, RoutedEventArgs^ e) {
					JSObject eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("source", this->get_object());
					eventArgs.SetProperty("type", ctx.CreateString("focus"));
					this->fireEvent("focus", eventArgs);
				});
				return;
			}
		}
	} // namespace UI
} // namespace TitaniumWindows
