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
#include "TitaniumWindows/UI/View.hpp"
#include "Titanium/Blob.hpp"
#include <ppltasks.h>
#include <boost/algorithm/string.hpp>

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::UI::Xaml;
		using namespace Windows::UI::Xaml::Controls;
		using namespace Windows::UI::Xaml::Media::Imaging;
		using namespace Windows::Storage;
		using namespace Windows::Storage::Streams;

		WindowsImageViewLayoutDelegate::WindowsImageViewLayoutDelegate() TITANIUM_NOEXCEPT
			: WindowsViewLayoutDelegate()
		{
			TITANIUM_LOG_DEBUG("WindowsImageViewLayoutDelegate::ctor ", this);
		}

		WindowsImageViewLayoutDelegate::~WindowsImageViewLayoutDelegate() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("WindowsImageViewLayoutDelegate::dtor ", this);
		}

		void WindowsImageViewLayoutDelegate::stretchImageView() TITANIUM_NOEXCEPT
		{
			const auto imageview = dynamic_cast<Image^>(component__);
			TITANIUM_ASSERT(imageview != nullptr);
			const auto fillstr = Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL);
			if (width__ == fillstr && height__ == fillstr) {
				imageview->Stretch = Media::Stretch::Fill;
			} else {
				imageview->Stretch = Media::Stretch::Uniform;
			}
		}

		void WindowsImageViewLayoutDelegate::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			WindowsViewLayoutDelegate::set_width(width);
			stretchImageView();
		}

		void WindowsImageViewLayoutDelegate::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			WindowsViewLayoutDelegate::set_height(height);
			stretchImageView();
		}

		ImageView::ImageView(const JSContext& js_context) TITANIUM_NOEXCEPT
			  : Titanium::UI::ImageView(js_context)
			  , loaded__(false)
			  , loaded_event_set__(false)
		{
		}

		void ImageView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::ImageView::postCallAsConstructor(js_context, arguments);	

			image__ = ref new Windows::UI::Xaml::Controls::Image();

			layout_event__ = image__->ImageOpened += ref new RoutedEventHandler([this](::Platform::Object^ sender, RoutedEventArgs^ e) {
				const auto layout = getViewLayoutDelegate<WindowsImageViewLayoutDelegate>();
				auto rect = layout->computeRelativeSize(
					Canvas::GetLeft(this->image__),
					Canvas::GetTop(this->image__),
					this->image__->ActualWidth,
					this->image__->ActualHeight
				);
				layout->onComponentSizeChange(rect);
			});

			Titanium::UI::ImageView::setLayoutDelegate<WindowsImageViewLayoutDelegate>();

			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForWidth(Titanium::UI::LAYOUT::FILL);

			getViewLayoutDelegate<WindowsImageViewLayoutDelegate>()->setComponent(image__);
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
				auto uri = TitaniumWindows::Utility::GetUriFromPath(images.at(index));

				auto keyFrame = ref new Windows::UI::Xaml::Media::Animation::DiscreteObjectKeyFrame();
				Windows::Foundation::TimeSpan key_time;
				key_time.Duration = timer_interval_ticks.count() * i;
				keyFrame->KeyTime = key_time;
				keyFrame->Value = ref new BitmapImage(uri);
				animation->KeyFrames->Append(keyFrame);
			}
			storyboard__->Children->Append(animation);
			storyboard__->SetTarget(animation, image__);
			storyboard__->SetTargetProperty(animation, "(Image.Source)");

			storyboard__->Completed += ref new Windows::Foundation::EventHandler<Platform::Object ^>([this](Platform::Object^ sender, Platform::Object ^ e) mutable {
				animating__ = false;
				paused__ = false;

				this->fireEvent("stop");
			});

			storyboard__->Begin();
			animating__ = true;
			paused__ = false;

			fireEvent("start");
		}

		void ImageView::stop() TITANIUM_NOEXCEPT
		{
			if (storyboard__ != nullptr) {
				storyboard__->Stop();
				fireEvent("stop");
				animating__ = false;
				paused__ = false;
				// TODO Delete the storyboard?
			}
		}

		void ImageView::pause() TITANIUM_NOEXCEPT
		{
			if (storyboard__ != nullptr) {
				storyboard__->Pause();
				animating__ = false;
				paused__ = true;
				fireEvent("pause");
			}
		}

		void ImageView::resume() TITANIUM_NOEXCEPT
		{
			if (storyboard__ != nullptr) {
				storyboard__->Resume();
				animating__ = true;
				paused__ = false;
				// TODO: Do we want to fire "start" event here?
				// fireEvent("resume");
			}
		}

		void ImageView::loadContentFromData(std::vector<std::uint8_t>& data)
		{
			const auto stream = ref new InMemoryRandomAccessStream();
			const auto writer = ref new DataWriter(stream);

			writer->WriteBytes(Platform::ArrayReference<std::uint8_t>(&data[0], data.size()));

			concurrency::create_task(writer->StoreAsync()).then([this, stream, writer](std::uint32_t) {
				auto bitmap = ref new BitmapImage();
				writer->DetachStream();
				stream->Seek(0);
				bitmap->SetSourceAsync(stream);
				this->image__->Source = bitmap;
			});
		}

		void ImageView::set_image(const std::string& path) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ImageView::set_image(path);

			// lazy load image event so it doesn't fire load event for defaultImage
			if (!loaded_event_set__) {
				loaded_event__ = image__->ImageOpened += ref new RoutedEventHandler([this](::Platform::Object^ sender, RoutedEventArgs^ e) {
					loaded__ = true;
					this->fireEvent("load", this->get_context().CreateObject());
				});
				loaded_event_set__ = true;
			}

			const auto uri = TitaniumWindows::Utility::GetUriFromPath(path);
			// check if we're loading from local file
			if (boost::starts_with(TitaniumWindows::Utility::ConvertString(uri->SchemeName), "ms-")) {
				concurrency::create_task(StorageFile::GetFileFromApplicationUriAsync(uri)).then([this](concurrency::task<StorageFile^> task){
					try {
						auto file = task.get();
						loadContentFromData(TitaniumWindows::Utility::GetContentFromFile(file));
					} catch (Platform::COMException^ ex) {
						TITANIUM_LOG_WARN("ImageView.image: ", TitaniumWindows::Utility::ConvertString(ex->Message));
					}
				}, concurrency::task_continuation_context::use_current());
			} else {
				Windows::Web::Http::HttpClient^ httpClient = ref new Windows::Web::Http::HttpClient();
				concurrency::create_task(httpClient->GetBufferAsync(uri)).then([this](concurrency::task<IBuffer^> task){
					try {
						auto buffer = task.get();
						loadContentFromData(TitaniumWindows::Utility::GetContentFromBuffer(buffer));
					} catch (Platform::COMException^ ex) {
						TITANIUM_LOG_WARN("ImageView.image: ", TitaniumWindows::Utility::ConvertString(ex->Message));
					}
				}, concurrency::task_continuation_context::use_current());
			}
		}

		void ImageView::set_images(const std::vector<std::string>& images) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ImageView::set_images(images);
			// HACK For now let's cheat and just set the first image as a static one
			set_image(images.at(0));
		}

		void ImageView::set_defaultImage(const std::string& path) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ImageView::set_defaultImage(path);

			// do nothing when image is already loaded
			// otherwise start loading defaultImage
			if (!loaded__) {
				image__->Source = ref new BitmapImage(TitaniumWindows::Utility::GetUriFromPath(path));
			}
		}

		std::shared_ptr<Titanium::Blob> ImageView::toBlob(JSValue callback) TITANIUM_NOEXCEPT
		{
			return this->toImage(callback, false);
		}

		std::shared_ptr<Titanium::Blob> ImageView::toImage(JSValue callback, const bool& honorScaleFactor) TITANIUM_NOEXCEPT
		{
			if (callback.IsObject() && static_cast<JSObject>(callback).IsFunction()) {
				TitaniumWindows::UI::View::ToImage(image__, callback, get_object());
			} else {
				HAL::detail::ThrowRuntimeError("ImageView.toImage", "ImageView.toImage only works with callback");
			}

			return nullptr;
		}
	} // namespace UI
} // namespace TitaniumWindows
