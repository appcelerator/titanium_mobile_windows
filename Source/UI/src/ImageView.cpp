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
#include "Titanium/Filesystem/File.hpp"
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

		WindowsImageViewLayoutDelegate::WindowsImageViewLayoutDelegate(Windows::UI::Xaml::Controls::Image^ image) TITANIUM_NOEXCEPT
			: WindowsViewLayoutDelegate()
			, image__(image)
		{
			TITANIUM_LOG_DEBUG("WindowsImageViewLayoutDelegate::ctor ", this);
		}

		WindowsImageViewLayoutDelegate::~WindowsImageViewLayoutDelegate() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("WindowsImageViewLayoutDelegate::dtor ", this);
		}

		void WindowsImageViewLayoutDelegate::stretchImageView() TITANIUM_NOEXCEPT
		{
			const auto fillstr = Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL);
			if (width__ == fillstr && height__ == fillstr) {
				image__->Stretch = Media::Stretch::Fill;
			} else {
				image__->Stretch = Media::Stretch::Uniform;
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
		{
		}

		void ImageView::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::ImageView::postCallAsConstructor(js_context, arguments);	

			bitmaps__ = ref new Platform::Collections::Vector<BitmapImage^>();
			set_image_fn__ = [this](BitmapImage^ image){ set_image(image); };
			
			image__ = ref new Windows::UI::Xaml::Controls::Image();
			image__->SizeChanged += ref new SizeChangedEventHandler([this](Platform::Object^ sender, SizeChangedEventArgs^ e) {
				if (!sizeChanged__) {
					return;
				}
				const auto layout = getViewLayoutDelegate<WindowsImageViewLayoutDelegate>();
				const auto rect = layout->computeRelativeSize(
					Canvas::GetLeft(image__),
					Canvas::GetTop(image__),
					this->image__->ActualWidth,
					this->image__->ActualHeight
					);
				layout->onComponentSizeChange(rect);
				sizeChanged__ = false;
			});

			image__->ImageOpened += ref new RoutedEventHandler([this](Platform::Object^ sender, RoutedEventArgs^ e) {
				const auto layout = getViewLayoutDelegate<WindowsImageViewLayoutDelegate>();
				const auto rect = layout->computeRelativeSize(
					Canvas::GetLeft(image__),
					Canvas::GetTop(image__),
					this->image__->ActualWidth,
					this->image__->ActualHeight
					);
				layout->onComponentSizeChange(rect);
			});

			Titanium::UI::ImageView::setLayoutDelegate<WindowsImageViewLayoutDelegate>(image__);

			border__ = ref new Controls::Border();
			border__->Child = image__;

			// Set parent of the ImageView, to support background color and border
			auto parent = ref new Controls::Grid();

			parent->Children->Append(border__);
			parent->SetColumn(border__, 0);
			parent->SetRow(border__, 0);

			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::SIZE);
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::SIZE);
			layoutDelegate__->set_autoLayoutForHeight(Titanium::UI::LAYOUT::SIZE);
			layoutDelegate__->set_autoLayoutForWidth(Titanium::UI::LAYOUT::SIZE);

			getViewLayoutDelegate<WindowsImageViewLayoutDelegate>()->setComponent(parent, nullptr, border__);
		}

		void ImageView::JSExportInitialize()
		{
			JSExport<ImageView>::SetClassVersion(1);
			JSExport<ImageView>::SetParent(JSExport<Titanium::UI::ImageView>::Class());
		}

		void ImageView::afterPropertiesSet() TITANIUM_NOEXCEPT
		{
			Titanium::UI::ImageView::afterPropertiesSet();
			
			// Initialize image
			if (!get_image().empty()) {
				set_image(get_image());
			} else if (get_imageAsBlob()) {
				set_imageAsBlob(get_imageAsBlob());
			} else if (get_imageAsFile()) {
				set_imageAsFile(get_imageAsFile());
			}
		}

		void ImageView::start() TITANIUM_NOEXCEPT
		{
			// bitmaps are not loaded yet. Will be re-started once all bitmaps are loaded.
			if (!bitmaps_loaded__) {
				bitmaps_waiting__ = true;
				return;
			}

			const auto image_count = bitmaps__->Size;

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

				const auto bitmap = bitmaps__->GetAt(index);
				auto keyFrame = ref new Windows::UI::Xaml::Media::Animation::DiscreteObjectKeyFrame();
				Windows::Foundation::TimeSpan key_time;
				key_time.Duration = timer_interval_ticks.count() * i;
				keyFrame->KeyTime = key_time;
				keyFrame->Value   = bitmap == nullptr ? ref new BitmapImage() : bitmap;
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
			bitmaps_waiting__ = false;

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

		void ImageView::loadBitmaps()
		{
			bitmaps__->Clear();
			bitmaps_loaded__ = false;
			bitmaps_loaded_count__ = 0;

			const auto images = get_images();
			const auto images_count = images.size();
			for (std::size_t i = 0; i < images_count; i++) {
				bitmaps__->Append(nullptr);
				const auto image = images.at(i);
				loadBitmap(image, [this, images_count, i](BitmapImage^ bitmap){
					bitmaps_loaded_count__++;
					bitmaps__->SetAt(i, bitmap);
					// do we load all images?
					if (bitmaps_loaded_count__ >= images_count) {
						bitmaps_loaded__ = true;
						fireEvent("load");
						// start animation when we held it off
						if (bitmaps_waiting__) {
							start();
						}
					}
				});
			}
			if (images.size() > 0) {
				return;
			}

			const auto blobs = get_imagesAsBlob();
			const auto blobs_count = blobs.size();
			for (std::size_t i = 0; i < blobs_count; i++) {
				bitmaps__->Append(nullptr);
				const auto blob = blobs.at(i);
				loadBitmap(blob->getData(), [this, blobs_count, i](BitmapImage^ bitmap){
					bitmaps_loaded_count__++;
					bitmaps__->SetAt(i, bitmap);
					// do we load all images?
					if (bitmaps_loaded_count__ >= blobs_count) {
						bitmaps_loaded__ = true;
						fireEvent("load");
						// start animation when we held it off
						if (bitmaps_waiting__) {
							start();
						}
					}
				});
			}
			if (blobs.size() > 0) {
				return;
			}

			const auto files = get_imagesAsFile();
			const auto files_count = files.size();
			for (std::size_t i = 0; i < files_count; i++) {
				bitmaps__->Append(nullptr);
				const auto file = files.at(i);
				loadBitmap(file->read()->getData(), [this, files_count, i](BitmapImage^ bitmap){
					bitmaps_loaded_count__++;
					bitmaps__->SetAt(i, bitmap);
					// do we load all images?
					if (bitmaps_loaded_count__ >= files_count) {
						bitmaps_loaded__ = true;
						fireEvent("load");
						// start animation when we held it off
						if (bitmaps_waiting__) {
							start();
						}
					}
				});
			}
		}

		void ImageView::set_image(BitmapImage^ bitmap)
		{
			const auto layout = getViewLayoutDelegate<WindowsImageViewLayoutDelegate>();

			if (layout->get_borderRadius() > 0) {
				this->border__->Background = WindowsImageViewLayoutDelegate::CreateImageBrushFromBitmapImage(bitmap);
			} else {
				this->image__->Source = bitmap;
			}

			auto rect = layout->computeRelativeSize(
				Canvas::GetLeft(this->image__),
				Canvas::GetTop(this->image__),
				bitmap->PixelWidth,
				bitmap->PixelHeight
				);
			layout->onComponentSizeChange(rect);

			this->fireEvent("load");
		}

		void ImageView::loadBitmap(std::vector<std::uint8_t>& data, SetBitmapImageCallback_t callback)
		{
			if (data.size() == 0) {
				TITANIUM_LOG_WARN("ImageView: There's no data to load");
				return;
			}

			const auto stream = ref new InMemoryRandomAccessStream();
			const auto writer = ref new DataWriter(stream);

			writer->WriteBytes(Platform::ArrayReference<std::uint8_t>(&data[0], data.size()));

			concurrency::create_task(writer->StoreAsync()).then([this, stream, writer, callback](std::uint32_t) {
				auto bitmap = ref new BitmapImage();
				writer->DetachStream();
				stream->Seek(0);
				concurrency::create_task(bitmap->SetSourceAsync(stream)).then([bitmap, callback]() {
					callback(bitmap);
				});
			});
		}

		void ImageView::loadBitmap(const std::string& path, SetBitmapImageCallback_t callback)
		{
			const auto uri = TitaniumWindows::Utility::GetUriFromPath(path);
			// check if we're loading from local file
			if (boost::starts_with(TitaniumWindows::Utility::ConvertString(uri->SchemeName), "ms-")) {
				concurrency::create_task(StorageFile::GetFileFromApplicationUriAsync(uri)).then([this, callback](concurrency::task<StorageFile^> task){
					try {
						auto file = task.get();
						loadBitmap(TitaniumWindows::Utility::GetContentFromFile(file), callback);
					} catch (Platform::COMException^ ex) {
						TITANIUM_LOG_WARN("ImageView::loadBitmap: ", TitaniumWindows::Utility::ConvertString(ex->Message));
						callback(ref new BitmapImage());
					}
				});
			} else {
				Windows::Web::Http::HttpClient^ httpClient = ref new Windows::Web::Http::HttpClient();
				concurrency::create_task(httpClient->GetBufferAsync(uri)).then([this, callback](concurrency::task<IBuffer^> task){
					try {
						auto buffer = task.get();
						loadBitmap(TitaniumWindows::Utility::GetContentFromBuffer(buffer), callback);
					} catch (Platform::COMException^ ex) {
						TITANIUM_LOG_WARN("ImageView::loadBitmap: ", TitaniumWindows::Utility::ConvertString(ex->Message));
						callback(ref new BitmapImage());
					}
				});
			}
		}

		bool ImageView::prepareImageParams()
		{
			// Make sure to call set_image after all properties are set
			if (!propertiesSet__) {
				return false;
			}

			sizeChanged__ = true;

			return true;
		}

		void ImageView::set_imageAsBlob(const std::shared_ptr<Titanium::Blob>& blob)
		{
			Titanium::UI::ImageView::set_imageAsBlob(blob);

			if (!prepareImageParams()) {
				return;
			}

			TitaniumWindows::Utility::RunOnUIThread([blob, this](){
				loadBitmap(blob->getData(), set_image_fn__);
			});
		}

		void ImageView::set_imageAsFile(const std::shared_ptr<Titanium::Filesystem::File>& file)
		{
			Titanium::UI::ImageView::set_imageAsFile(file);

			if (!prepareImageParams()) {
				return;
			}

			TitaniumWindows::Utility::RunOnUIThread([file, this](){
				loadBitmap(file->read()->getData(), set_image_fn__);
			});
		}

		void ImageView::set_image(const std::string& path) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ImageView::set_image(path);

			// Make sure to call set_image after all properties are set
			if (!prepareImageParams()) {
				return;
			}

			// Make sure to update image from UI thread.
			// We do it here because we're observing even StorageFile doesn't work outside of UI thread.
			TitaniumWindows::Utility::RunOnUIThread([path, this](){
				loadBitmap(path, set_image_fn__);
			});
		}

		void ImageView::set_images(const std::vector<std::string>& images) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ImageView::set_images(images);
			loadBitmaps();
		}

		void ImageView::set_imagesAsBlob(const std::vector<std::shared_ptr<Titanium::Blob>>& images) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ImageView::set_imagesAsBlob(images);
			loadBitmaps();
		}

		void ImageView::set_imagesAsFile(const std::vector<std::shared_ptr<Titanium::Filesystem::File>>& images) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ImageView::set_imagesAsFile(images);
			loadBitmaps();
		}

		void ImageView::set_defaultImage(const std::string& path) TITANIUM_NOEXCEPT
		{
			Titanium::UI::ImageView::set_defaultImage(path);
			image__->Source = ref new BitmapImage(TitaniumWindows::Utility::GetUriFromPath(path));
		}

		std::shared_ptr<Titanium::Blob> ImageView::toImage(JSObject& callback, const bool& honorScaleFactor) TITANIUM_NOEXCEPT
		{
			return getViewLayoutDelegate()->toImage(callback, honorScaleFactor, get_object());
		}
	} // namespace UI
} // namespace TitaniumWindows
