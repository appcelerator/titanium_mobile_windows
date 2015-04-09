/**
* Titanium.UI.ImageView for Windows
*
* Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/ImageView.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "LayoutEngine/LayoutEngine.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		ImageView::ImageView(const JSContext& js_context) TITANIUM_NOEXCEPT
			  : Titanium::UI::ImageView(js_context)
		{
		}

		void ImageView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			using namespace Windows::UI::Xaml;
			using namespace Windows::UI::Xaml::Controls;

			Titanium::UI::ImageView::postCallAsConstructor(js_context, arguments);	

			image__ = ref new Windows::UI::Xaml::Controls::Image();

			internal_load_event_ = image__->ImageOpened += ref new RoutedEventHandler([this](::Platform::Object^ sender, RoutedEventArgs^ e) {
				const auto layout = getViewLayoutDelegate<WindowsViewLayoutDelegate>();
				auto rect = layout->computeRelativeSize(
					Canvas::GetLeft(this->image__),
					Canvas::GetTop(this->image__),
					this->image__->ActualWidth,
					this->image__->ActualHeight
				);
				layout->onComponentSizeChange(rect);

				this->fireEvent("load", this->get_context().CreateObject());
			});

			Titanium::UI::ImageView::setLayoutDelegate<WindowsViewLayoutDelegate>();

			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(image__);
		}

		void ImageView::JSExportInitialize()
		{
			JSExport<ImageView>::SetClassVersion(1);
			JSExport<ImageView>::SetParent(JSExport<Titanium::UI::ImageView>::Class());
		}

		void ImageView::start() TITANIUM_NOEXCEPT
		{
			const auto images = get_images();
			const size_t image_count = images.size();

			storyboard__ = ref new Windows::UI::Xaml::Media::Animation::Storyboard();
			Windows::Foundation::TimeSpan time_span;
			std::chrono::duration<std::chrono::nanoseconds::rep, std::ratio_multiply<std::ratio<100>, std::nano>> timer_interval_ticks = get_duration();
			time_span.Duration = timer_interval_ticks.count() * image_count;
			storyboard__->Duration = time_span;
			auto animation = ref new Windows::UI::Xaml::Media::Animation::ObjectAnimationUsingKeyFrames();
			
			auto repeat_count = get_repeatCount();
			if (repeat_count == 0) {
				storyboard__->RepeatBehavior = Windows::UI::Xaml::Media::Animation::RepeatBehaviorHelper::Forever;
			} else {
				storyboard__->RepeatBehavior = Windows::UI::Xaml::Media::Animation::RepeatBehaviorHelper::FromCount(repeat_count);
			}
			
			const bool reverse = get_reverse();
			for (size_t i = 0; i < image_count; i++) {
				size_t index = reverse ? (image_count - 1) - i : i;
				auto image = images.at(index);

				// TODO Extract out common code with set_image()!
				std::string modified = image;
				// if the path isn't an http/s URI already, fix URI to point to local files in app
				if (!boost::starts_with(modified, "http://") && !boost::starts_with(modified, "https://")) {
					// URIs must be absolute
					if (!boost::starts_with(modified, "/")) {
						modified = "/" + modified;
					}
					// use MS's in-app URL scheme
					modified = "ms-appx://" + modified;
				}
				auto uri = ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertUTF8String(modified));

				auto keyFrame = ref new Windows::UI::Xaml::Media::Animation::DiscreteObjectKeyFrame();
				Windows::Foundation::TimeSpan key_time;
				key_time.Duration = timer_interval_ticks.count() * i;
				keyFrame->KeyTime = key_time;
				keyFrame->Value = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(uri);
				animation->KeyFrames->Append(keyFrame);
			}
			storyboard__->Children->Append(animation);
			storyboard__->SetTarget(animation, image__);
			storyboard__->SetTargetProperty(animation, "(Image.Source)");

			storyboard__->Completed += ref new Windows::Foundation::EventHandler<Platform::Object ^>([this](Platform::Object^ sender, Platform::Object ^ e) mutable {
				is_animating__ = false;
				is_paused__ = false;

				// TODO Fire stop event!
			});

			storyboard__->Begin();
			is_animating__ = true;
			is_paused__ = false;
			// TODO Fire start event!
		}

		void ImageView::stop() TITANIUM_NOEXCEPT
		{
			if (storyboard__ != nullptr) {
				storyboard__->Stop();
				// TODO Fire stop event!
				is_animating__ = false;
				is_paused__ = false;
				// TODO Delete the storyboard?
			}
		}

		void ImageView::pause() TITANIUM_NOEXCEPT
		{
			if (storyboard__ != nullptr) {
				storyboard__->Pause();
				is_animating__ = false;
				is_paused__ = true;
				// TODO Fire pause event!
			}
		}

		void ImageView::resume() TITANIUM_NOEXCEPT
		{
			if (storyboard__ != nullptr) {
				storyboard__->Resume();
				is_animating__ = true;
				is_paused__ = false;
				// TODO Fire start event?
			}
		}

		bool ImageView::get_animating() const TITANIUM_NOEXCEPT
		{
			return is_animating__;
		}

		void ImageView::set_image(const std::string& path) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ImageView::set_image(path);
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
			auto uri = ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertUTF8String(modified));
			auto image = ref new Windows::UI::Xaml::Media::Imaging::BitmapImage(uri);
			image__->Source = image;
		}

		void ImageView::set_images(const std::vector<std::string>& images) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ImageView::set_images(images);
			// HACK For now let's cheat and just set the first image as a static one
			set_image(images.at(0));
		}

		bool ImageView::get_paused() const TITANIUM_NOEXCEPT
		{
			return is_paused__;
		}

		void ImageView::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ImageView::enableEvent(event_name);

			const JSContext ctx = this->get_context();

			using namespace Windows::UI::Xaml::Input;
			using namespace Windows::UI::Xaml;

			auto component = getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
			// TODO Handle change/error/load/pause/start/stop!
			if (event_name == "click") { // TODO Can't superclass handle common events like click?
				click_event_ = component->Tapped += ref new TappedEventHandler([this, ctx](::Platform::Object^ sender, TappedRoutedEventArgs^ e) {
					auto component = safe_cast<FrameworkElement^>(sender);
					auto position = e->GetPosition(component);

					JSObject  eventArgs = ctx.CreateObject();
					eventArgs.SetProperty("x", ctx.CreateNumber(position.X));
					eventArgs.SetProperty("y", ctx.CreateNumber(position.Y));

					this->fireEvent("click", eventArgs);
				});
			}
		}
	} // namespace UI
} // namespace TitaniumWindows
