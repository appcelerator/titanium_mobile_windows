/**
* Titanium.UI.ImageView for Windows
*
* Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_IMAGEVIEW_HPP_
#define _TITANIUMWINDOWS_UI_IMAGEVIEW_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/ImageView.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include <collection.h>

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;
		using SetBitmapImageCallback_t = std::function<void(Windows::UI::Xaml::Media::Imaging::BitmapImage^)> ;

		class TITANIUMWINDOWS_UI_EXPORT WindowsImageViewLayoutDelegate : public WindowsViewLayoutDelegate {
		public:
			WindowsImageViewLayoutDelegate(Windows::UI::Xaml::Controls::Image^ image) TITANIUM_NOEXCEPT;
			virtual ~WindowsImageViewLayoutDelegate();

			void stretchImageView() TITANIUM_NOEXCEPT;

			virtual void set_width(const std::string& width) TITANIUM_NOEXCEPT override;
			virtual void set_height(const std::string& height) TITANIUM_NOEXCEPT override;

			virtual Windows::UI::Xaml::FrameworkElement^ getComponent() const TITANIUM_NOEXCEPT override
			{
				return component__;
			}
		private:
			Windows::UI::Xaml::Controls::Image^ image__;
		};

		/*!
		  @class ImageView
		  @ingroup Titanium.UI.ImageView

		  @discussion This is the Titanium.UI.ImageView implementation for
		  Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT ImageView final : public Titanium::UI::ImageView, public JSExport<ImageView>
		{
		public:

			TITANIUM_PROPERTY_UNIMPLEMENTED(autorotate);
			TITANIUM_PROPERTY_UNIMPLEMENTED(decodeRetries);
			TITANIUM_PROPERTY_UNIMPLEMENTED(enableZoomControls);
			TITANIUM_PROPERTY_UNIMPLEMENTED(hires);
			TITANIUM_PROPERTY_UNIMPLEMENTED(preventDefaultImage);
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderRadius);

			ImageView(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ImageView() = default;
			ImageView(const ImageView&) = default;
			ImageView& operator=(const ImageView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ImageView(ImageView&&) = default;
			ImageView& operator=(ImageView&&) = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;
			virtual void afterPropertiesSet() TITANIUM_NOEXCEPT override;

			// Methods
			virtual void pause() TITANIUM_NOEXCEPT override final;
			virtual void resume() TITANIUM_NOEXCEPT override final;
			virtual void start() TITANIUM_NOEXCEPT override final;
			virtual void stop() TITANIUM_NOEXCEPT override final;
			virtual std::shared_ptr<Titanium::Blob> toImage(JSObject& callback, const bool& honorScaleFactor) TITANIUM_NOEXCEPT override;

			// properties
			virtual void set_image(const std::string& image) TITANIUM_NOEXCEPT override final;
			virtual void set_imageAsBlob(const std::shared_ptr<Titanium::Blob>& image) TITANIUM_NOEXCEPT override final;
			virtual void set_imageAsFile(const std::shared_ptr<Titanium::Filesystem::File>& image) TITANIUM_NOEXCEPT override final;
			virtual void set_images(const std::vector<std::string>&) TITANIUM_NOEXCEPT override final;
			virtual void set_imagesAsBlob(const std::vector<std::shared_ptr<Titanium::Blob>>&) TITANIUM_NOEXCEPT override final;
			virtual void set_imagesAsFile(const std::vector<std::shared_ptr<Titanium::Filesystem::File>>&) TITANIUM_NOEXCEPT override final;
			virtual void set_defaultImage(const std::string&) TITANIUM_NOEXCEPT override final;
		private:

#pragma warning(push)
#pragma warning(disable : 4251)

			SetBitmapImageCallback_t set_image_fn__;

			std::uint32_t bitmaps_loaded_count__{ 0 };
			bool bitmaps_waiting__ { false };
			bool bitmaps_loaded__ { false };
			::Platform::Collections::Vector<Windows::UI::Xaml::Media::Imaging::BitmapImage^>^ bitmaps__;

			bool prepareImageParams();
			void loadBitmap(std::vector<std::uint8_t>& data, SetBitmapImageCallback_t);
			void loadBitmaps();

			void set_image(Windows::UI::Xaml::Media::Imaging::BitmapImage^);

			Windows::UI::Xaml::Controls::Border^ border__{ nullptr };
			Windows::UI::Xaml::Controls::Image^ image__{ nullptr };
			Windows::UI::Xaml::Media::Animation::Storyboard^ storyboard__;
			bool sizeChanged__{ true };
			bool imageOpened__{ false };
			std::vector<JSObject> to_image_queue__;

			void fireLoadEvent(const bool& multiple);
#pragma warning(pop)
		};
	} // namespace UI
} // namespace TitaniumWindow

#endif  // _TITANIUMWINDOWS_UI_IMAGEVIEW_HPP_
