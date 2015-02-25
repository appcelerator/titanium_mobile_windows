/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ImageView.hpp"

namespace Titanium
{
	namespace UI
	{
		ImageView::ImageView(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : View(js_context),
		      duration__(200),
		      image__(js_context.CreateString()),
		      images__(),
		      preventDefaultImage__(false)
		{
		}

		void ImageView::start(JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("ImageView::start unimplemented");
		}

		void ImageView::stop(JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("ImageView::stop unimplemented");
		}

		std::chrono::milliseconds ImageView::get_duration() const TITANIUM_NOEXCEPT
		{
			return duration__;
		}

		void ImageView::set_duration(const std::chrono::milliseconds& duration) TITANIUM_NOEXCEPT
		{
			duration__ = duration;
		}

		std::string ImageView::get_image() const TITANIUM_NOEXCEPT
		{
			return image__;
		}

		void ImageView::set_image(const std::string& image) TITANIUM_NOEXCEPT
		{
			image__ = image;
		}

		std::vector<std::string> ImageView::get_images() const TITANIUM_NOEXCEPT
		{
			return images__;
		}

		void ImageView::set_images(const std::vector<std::string>& images) TITANIUM_NOEXCEPT
		{
			images__ = images;
		}

		bool ImageView::get_preventDefaultImage() const TITANIUM_NOEXCEPT
		{
			return preventDefaultImage__;
		}

		void ImageView::set_preventDefaultImage(const bool& preventDefaultImage) TITANIUM_NOEXCEPT
		{
			preventDefaultImage__ = preventDefaultImage;
		}

		void ImageView::JSExportInitialize()
		{
			JSExport<ImageView>::SetClassVersion(1);
			JSExport<ImageView>::SetParent(JSExport<View>::Class());
			JSExport<ImageView>::AddFunctionProperty("start", std::mem_fn(&ImageView::js_start));
			JSExport<ImageView>::AddFunctionProperty("stop", std::mem_fn(&ImageView::js_stop));
			JSExport<ImageView>::AddValueProperty("duration", std::mem_fn(&ImageView::js_get_duration), std::mem_fn(&ImageView::js_set_duration));
			JSExport<ImageView>::AddValueProperty("image", std::mem_fn(&ImageView::js_get_image), std::mem_fn(&ImageView::js_set_image));
			JSExport<ImageView>::AddValueProperty("images", std::mem_fn(&ImageView::js_get_images), std::mem_fn(&ImageView::js_set_images));
			JSExport<ImageView>::AddValueProperty("preventDefaultImage", std::mem_fn(&ImageView::js_get_preventDefaultImage), std::mem_fn(&ImageView::js_set_preventDefaultImage));
		}

		JSValue ImageView::js_start(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.empty());
			start(this_object);
			return get_context().CreateUndefined();
		}

		JSValue ImageView::js_stop(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(arguments.empty());
			stop(this_object);
			return get_context().CreateUndefined();
		}

		JSValue ImageView::js_get_duration() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateNumber(static_cast<double>(duration__.count()));
		}

		bool ImageView::js_set_duration(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsNumber());
			const auto duration = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<std::uint32_t>(argument)));
			set_duration(duration);
			return true;
		}

		JSValue ImageView::js_get_image() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(image__);
		}

		bool ImageView::js_set_image(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			std::string path = static_cast<std::string>(argument);
			TITANIUM_LOG_DEBUG("ImageView::js_set_image: image = ", path);
			set_image(path);
			return true;
		}

		JSValue ImageView::js_get_images() const TITANIUM_NOEXCEPT
		{
			std::vector<JSValue> images;
			for (auto image : images__) {
				images.push_back(get_context().CreateString(image));
			}
			return get_context().CreateArray(images);
		}

		bool ImageView::js_set_images(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsObject());
			auto object = static_cast<JSObject>(argument);
			TITANIUM_ASSERT(object.IsArray());
			
			std::vector<std::string> images;
			const auto item_count = object.GetPropertyNames().GetCount();
			for (size_t i = 0; i < item_count; ++i) {
				JSValue item = object.GetProperty(i);
				TITANIUM_ASSERT(item.IsString());
				images.push_back(static_cast<std::string>(item));
			}
			set_images(images);
			return true;
		}

		JSValue ImageView::js_get_preventDefaultImage() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateBoolean(preventDefaultImage__);
		}

		bool ImageView::js_set_preventDefaultImage(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_preventDefaultImage(static_cast<bool>(argument));
			return true;
		}
	} // namespace UI
}  // namespace Titanium
