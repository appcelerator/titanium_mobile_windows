/**
* Titanium.UI.ImageView for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/ImageView.hpp"
#include "LayoutEngine/LayoutEngine.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		ImageView::ImageView(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			  : Titanium::UI::ImageView(js_context, arguments),
			    Titanium::UI::View(js_context, arguments),
			    ViewBase(js_context, arguments),
		        image__(ref new Windows::UI::Xaml::Controls::Image())
		{
			using namespace Windows::UI::Xaml;
			using namespace Windows::UI::Xaml::Controls;

			TITANIUM_LOG_DEBUG("ImageView::ctor");

			setComponent(image__);

			internal_load_event_ = image__->ImageOpened += ref new RoutedEventHandler([this](::Platform::Object^ sender, RoutedEventArgs^ e) {
				auto rect = Titanium::LayoutEngine::RectMake(
					Canvas::GetLeft(this->image__),
					Canvas::GetTop(this->image__),
					this->image__->ActualWidth,
					this->image__->ActualHeight
				);
				this->onComponentSizeChange(rect);
			});

		}

		void ImageView::JSExportInitialize()
		{
			JSExport<ImageView>::SetClassVersion(1);
			JSExport<ImageView>::SetParent(JSExport<Titanium::UI::ImageView>::Class());
		}

		void ImageView::set_image(const std::string& path) TITANIUM_NOEXCEPT
		{
			std::string modified = path;
			// if the path isn't an http/s URI already, fix URI to point to local files in app
			if (!boost::starts_with(modified, "http://") && !boost::starts_with(modified, "https://")) {
				// URIs must be absolute
				if (!boost::starts_with(modified, "/")) {
					modified = "/" + modified;
				}
				// use MS's in-app URL scheme
				modified = "ms-appx://" + modified;
			}
			auto uri = ref new Windows::Foundation::Uri(ref new Platform::String(std::wstring(modified.begin(), modified.end()).c_str()));
			auto image = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(uri);
			image__->Source = image;
		}

		void ImageView::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("ImageView::enableEvent: (event name '", event_name, "'");

			const JSContext ctx = this->get_context();

			using namespace Windows::UI::Xaml::Input;
			using namespace Windows::UI::Xaml;

			if (event_name == "click") {
				if (click_event_count_ == 0) {
					click_event_ = getComponent()->Tapped += ref new TappedEventHandler([this, ctx](::Platform::Object^ sender, TappedRoutedEventArgs^ e) {
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
