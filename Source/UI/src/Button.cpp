/**
* Titanium.UI.Button for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/Button.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		Button::Button(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Titanium::UI::Button(js_context)
		{
			TITANIUM_LOG_DEBUG("Button::ctor");
		}

		void Button::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::Button::postCallAsConstructor(js_context, arguments);	
			button__ = ref new Windows::UI::Xaml::Controls::Button();
			Titanium::UI::Button::setLayoutDelegate<WindowsViewLayoutDelegate>();

			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(button__);
		}

		void Button::JSExportInitialize()
		{
			JSExport<Button>::SetClassVersion(1);
			JSExport<Button>::SetParent(JSExport<Titanium::UI::Button>::Class());
		}

		void Button::set_title(const std::string& title) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Button::set_title(title);
			button__->Content = TitaniumWindows::Utility::ConvertUTF8String(title);
		}

		void Button::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::Button::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			using namespace Windows::UI::Xaml::Input;
			using namespace Windows::UI::Xaml;

			auto component = getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();

			if (event_name == "click") {
				if (click_event_count_ == 0) {
					click_event_ = component->Tapped += ref new TappedEventHandler([this, ctx](Platform::Object^ sender, TappedRoutedEventArgs^ e) {
						auto component = safe_cast<FrameworkElement^>(sender);
						auto position = e->GetPosition(component);

						JSObject  eventArgs = ctx.CreateObject();
						eventArgs.SetProperty("x", ctx.CreateNumber(position.X));
						eventArgs.SetProperty("y", ctx.CreateNumber(position.Y));

						this->fireEvent("click", eventArgs);
					});
				}

				++click_event_count_;

				return;
			}
		}
	} // namespace UI
} // namespace TitaniumWindows
