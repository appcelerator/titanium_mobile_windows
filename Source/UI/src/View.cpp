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

		void View::add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			auto nativeView = dynamic_cast<Windows::UI::Xaml::Controls::Panel^>(getComponent());

			if (nativeView == nullptr) {
				TITANIUM_LOG_DEBUG("View::add: nativeView = nullptr");
				return;
			}

			auto view_ptr = view.GetPrivate<Titanium::UI::View>();
			auto newView = std::dynamic_pointer_cast<TitaniumWindows::UI::ViewBase>(view_ptr);
			auto nativeChildView = newView->getComponent();
			if (nativeChildView != nullptr) {
				Titanium::LayoutEngine::nodeAddChild(layout_node_, newView->layout_node_);
				if (isLoaded()) {
					auto root = Titanium::LayoutEngine::nodeRequestLayout(layout_node_);
					if (root) {
						Titanium::LayoutEngine::nodeLayout(root);
					}
				}

				canvas__->Children->Append(nativeChildView);
			} else {
				TITANIUM_LOG_DEBUG("View::add: nativeChildView = nullptr");
			}
		}

		void View::hide(JSObject& this_object) TITANIUM_NOEXCEPT
		{
			getComponent()->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		}

		void View::show(JSObject& this_object) TITANIUM_NOEXCEPT
		{
			getComponent()->Visibility = Windows::UI::Xaml::Visibility::Visible;
		}

		void View::set_backgroundColor(const std::string& backgroundColorName) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_backgroundColor(backgroundColorName);
			const auto backgroundColor = ColorForName(backgroundColorName);
			canvas__->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(backgroundColor);
		}

		void View::set_opacity(const double& opacity) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_opacity(opacity);
			getComponent()->Opacity = opacity;
		}

		void View::set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_bottom(bottom);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Bottom, bottom);
		}

		void View::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_height(height);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, height);
		}

		void View::set_left(const std::string& left) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_left(left);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, left);
		}

		void View::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_layout(layout);
			setLayout(layout);
		}

		void View::set_right(const std::string& right) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_right(right);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, right);
		}

		void View::set_top(const std::string& top) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_top(top);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, top);
		}

		void View::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_width(width);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, width);
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
