/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ImageView.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/Filesystem/File.hpp"
#include "Titanium/detail/TiImpl.hpp"

#define IMAGEVIEW_MIN_INTERVAL 30

namespace Titanium
{
	namespace UI
	{
		ImageView::ImageView(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : View(js_context, "Ti.UI.ImageView"),
			animating__(false),
			autorotate__(false),
			decodeRetries__(5),
			defaultImage__(""),
			enableZoomControls__(false),
			duration__(200),
			image__(""),
			images__(),
			preventDefaultImage__(false),
			reverse__(false)
		{
		}

		void ImageView::start() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("ImageView::start unimplemented");
		}

		void ImageView::stop() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("ImageView::stop unimplemented");
		}

		void ImageView::pause() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("ImageView::pause unimplemented");
		}

		void ImageView::resume() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("ImageView::resume unimplemented");
		}

		std::shared_ptr<Titanium::Blob> ImageView::toBlob(JSObject& callback) TITANIUM_NOEXCEPT
		{
			if (imageAsBlob__) {
				return imageAsBlob__;
			} else if (imageAsFile__) {
				return imageAsFile__->read();
			} else {
				return toImage(callback, false);
			}
		}

		TITANIUM_PROPERTY_READ(ImageView, bool, animating)
		TITANIUM_PROPERTY_READWRITE(ImageView, bool, autorotate)
		TITANIUM_PROPERTY_READWRITE(ImageView, uint32_t, decodeRetries)
		TITANIUM_PROPERTY_READWRITE(ImageView, std::string, defaultImage)

		std::chrono::milliseconds ImageView::get_duration() const TITANIUM_NOEXCEPT
		{
			return duration__;
		}

		void ImageView::set_duration(const std::chrono::milliseconds& duration) TITANIUM_NOEXCEPT
		{
			// enforce minimum TODO Move this into the js_ bridge function?
			if (duration.count() < IMAGEVIEW_MIN_INTERVAL) {
				duration__ = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(IMAGEVIEW_MIN_INTERVAL));
			} else {
				duration__ = duration;
			}
		}

		TITANIUM_PROPERTY_READWRITE(ImageView, bool, enableZoomControls)
		TITANIUM_PROPERTY_READWRITE(ImageView, bool, hires)
		TITANIUM_PROPERTY_READWRITE(ImageView, std::string, image)
		TITANIUM_PROPERTY_READWRITE(ImageView, std::shared_ptr<Titanium::Blob>, imageAsBlob)
		TITANIUM_PROPERTY_READWRITE(ImageView, std::shared_ptr<Titanium::Filesystem::File>, imageAsFile)
		TITANIUM_PROPERTY_READWRITE(ImageView, std::vector<std::string>, images)
		TITANIUM_PROPERTY_READWRITE(ImageView, std::vector<std::shared_ptr<Titanium::Blob>>, imagesAsBlob)
		TITANIUM_PROPERTY_READWRITE(ImageView, std::vector<std::shared_ptr<Titanium::Filesystem::File>>, imagesAsFile)
		TITANIUM_PROPERTY_READ(ImageView, bool, paused)
		TITANIUM_PROPERTY_READWRITE(ImageView, bool, preventDefaultImage)
		TITANIUM_PROPERTY_READWRITE(ImageView, uint32_t, repeatCount)
		TITANIUM_PROPERTY_READWRITE(ImageView, bool, reverse)

		void ImageView::JSExportInitialize()
		{
			JSExport<ImageView>::SetClassVersion(1);
			JSExport<ImageView>::SetParent(JSExport<View>::Class());
			// methods
			TITANIUM_ADD_FUNCTION(ImageView, pause);
			TITANIUM_ADD_FUNCTION(ImageView, resume);
			TITANIUM_ADD_FUNCTION(ImageView, start);
			TITANIUM_ADD_FUNCTION(ImageView, stop);
			TITANIUM_ADD_FUNCTION(ImageView, toBlob);
			// properties
			TITANIUM_ADD_PROPERTY_READONLY(ImageView, animating);
			TITANIUM_ADD_PROPERTY(ImageView, autorotate);
			TITANIUM_ADD_PROPERTY(ImageView, decodeRetries);
			TITANIUM_ADD_PROPERTY(ImageView, defaultImage);
			TITANIUM_ADD_PROPERTY(ImageView, duration);
			TITANIUM_ADD_PROPERTY(ImageView, enableZoomControls);
			TITANIUM_ADD_PROPERTY(ImageView, hires);
			TITANIUM_ADD_PROPERTY(ImageView, image);
			TITANIUM_ADD_PROPERTY(ImageView, images);
			TITANIUM_ADD_PROPERTY_READONLY(ImageView, paused);
			TITANIUM_ADD_PROPERTY(ImageView, preventDefaultImage);
			TITANIUM_ADD_PROPERTY(ImageView, repeatCount);
			TITANIUM_ADD_PROPERTY(ImageView, reverse);
			// accessor/setter methods
			TITANIUM_ADD_FUNCTION(ImageView, getAnimating);
			TITANIUM_ADD_FUNCTION(ImageView, getAutorotate);
			TITANIUM_ADD_FUNCTION(ImageView, getDecodeRetries);
			TITANIUM_ADD_FUNCTION(ImageView, setDecodeRetries);
			TITANIUM_ADD_FUNCTION(ImageView, getDefaultImage);
			TITANIUM_ADD_FUNCTION(ImageView, setDefaultImage);
			TITANIUM_ADD_FUNCTION(ImageView, getDuration);
			TITANIUM_ADD_FUNCTION(ImageView, setDuration);
			TITANIUM_ADD_FUNCTION(ImageView, getEnableZoomControls);
			TITANIUM_ADD_FUNCTION(ImageView, setEnableZoomControls);
			TITANIUM_ADD_FUNCTION(ImageView, getHires);
			TITANIUM_ADD_FUNCTION(ImageView, setHires);
			TITANIUM_ADD_FUNCTION(ImageView, getImage);
			TITANIUM_ADD_FUNCTION(ImageView, setImage);
			TITANIUM_ADD_FUNCTION(ImageView, getImages);
			TITANIUM_ADD_FUNCTION(ImageView, setImages);
			TITANIUM_ADD_FUNCTION(ImageView, getPaused);
			TITANIUM_ADD_FUNCTION(ImageView, getPreventDefaultImage);
			TITANIUM_ADD_FUNCTION(ImageView, setPreventDefaultImage);
			TITANIUM_ADD_FUNCTION(ImageView, getRepeatCount);
			TITANIUM_ADD_FUNCTION(ImageView, setRepeatCount);
			TITANIUM_ADD_FUNCTION(ImageView, getReverse);
			TITANIUM_ADD_FUNCTION(ImageView, setReverse);
		}

		TITANIUM_FUNCTION(ImageView, pause)
		{
			TITANIUM_ASSERT(arguments.empty());
			pause();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ImageView, resume)
		{
			TITANIUM_ASSERT(arguments.empty());
			resume();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ImageView, start)
		{
			TITANIUM_ASSERT(arguments.empty());
			start();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ImageView, stop)
		{
			TITANIUM_ASSERT(arguments.empty());
			stop();
			return get_context().CreateUndefined();
		}

		TITANIUM_FUNCTION(ImageView, toBlob)
		{
			ENSURE_OPTIONAL_OBJECT_AT_INDEX(callback, 0);
			const auto image = toBlob(callback);
			if (image) {
				return image->get_object();
			}
			else {
				return get_context().CreateNull();
			}
		}

		TITANIUM_PROPERTY_GETTER(ImageView, animating)
		{
			return get_context().CreateBoolean(get_animating());
		}

		TITANIUM_PROPERTY_GETTER(ImageView, autorotate)
		{
			return get_context().CreateBoolean(get_autorotate());
		}

		TITANIUM_PROPERTY_SETTER(ImageView, autorotate)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_autorotate(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ImageView, decodeRetries)
		{
			return get_context().CreateNumber(get_decodeRetries());
		}

		TITANIUM_PROPERTY_SETTER(ImageView, decodeRetries)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_decodeRetries(static_cast<uint32_t>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ImageView, defaultImage)
		{
			return get_context().CreateString(get_defaultImage());
		}

		TITANIUM_PROPERTY_SETTER(ImageView, defaultImage)
		{
			TITANIUM_ASSERT(argument.IsString());
			std::string path = static_cast<std::string>(argument);
			set_defaultImage(static_cast<std::string>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ImageView, duration)
		{
			return get_context().CreateNumber(static_cast<double>(duration__.count()));
		}

		TITANIUM_PROPERTY_SETTER(ImageView, duration)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			const auto duration = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(static_cast<std::uint32_t>(argument)));
			set_duration(duration);
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ImageView, enableZoomControls)
		{
			return get_context().CreateBoolean(get_enableZoomControls());
		}

		TITANIUM_PROPERTY_SETTER(ImageView, enableZoomControls)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_enableZoomControls(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ImageView, hires)
		{
			return get_context().CreateBoolean(get_hires());
		}

		TITANIUM_PROPERTY_SETTER(ImageView, hires)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_hires(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ImageView, image)
		{
			const auto image = get_image();
			if (!image.empty()) {
				return get_context().CreateString(image);
			}
			const auto blob = get_imageAsBlob();
			if (blob) {
				return blob->get_object();
			}
			const auto file = get_imageAsFile();
			if (file) {
				return file->get_object();
			}
			return get_context().CreateNull();
		}

		TITANIUM_PROPERTY_SETTER(ImageView, image)
		{
			if (argument.IsObject()) {
				auto obj = static_cast<JSObject>(argument);
				auto blob = obj.GetPrivate<Titanium::Blob>();
				if (blob) {
					set_imageAsBlob(blob);
					return true;
				}
				auto file = obj.GetPrivate<Titanium::Filesystem::File>();
				if (file) {
					set_imageAsFile(file);
					return true;
				}
				TITANIUM_LOG_WARN("ImageView.image only accepts String, Blob or File");
			} else {
				set_image(static_cast<std::string>(argument));
			}
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ImageView, images)
		{
			const auto ctx = get_context();
			const auto blobs = get_imagesAsBlob();
			if (blobs.size() > 0) {
				std::vector<JSValue> images;
				for (auto blob : blobs) {
					images.push_back(blob->get_object());
				}
				return ctx.CreateArray(images);
			}
			const auto files = get_imagesAsFile();
			if (files.size() > 0) {
				std::vector<JSValue> images;
				for (auto file : files) {
					images.push_back(file->get_object());
				}
				return ctx.CreateArray(images);
			}

			std::vector<JSValue> images;
			for (auto image : get_images()) {
				images.push_back(ctx.CreateString(image));
			}
			return ctx.CreateArray(images);
		}

		TITANIUM_PROPERTY_SETTER(ImageView, images)
		{
			TITANIUM_ASSERT(argument.IsObject());
			auto object = static_cast<JSObject>(argument);
			TITANIUM_ASSERT(object.IsArray());

			std::vector<std::string> images;
			std::vector<std::shared_ptr<Titanium::Blob>> imagesAsBlob;
			std::vector<std::shared_ptr<Titanium::Filesystem::File>> imagesAsFile;

			auto useBlob = false;
			auto useFile = false;
			const auto item_count = object.GetPropertyNames().GetCount();
			for (uint32_t i = 0; i < item_count; ++i) {
				JSValue item = object.GetProperty(i);
				if (item.IsObject()) {
					auto itemObj = static_cast<JSObject>(item);
					auto blob = itemObj.GetPrivate<Titanium::Blob>();
					auto file = itemObj.GetPrivate<Titanium::Filesystem::File>();
					if (blob) {
						useBlob = true;
						imagesAsBlob.push_back(blob);
					} else if (file) {
						useFile = true;
						imagesAsFile.push_back(file);
					} else {
						TITANIUM_LOG_WARN("ImageView.images only accepts String, Blob or File");
					}
				} else {
					images.push_back(static_cast<std::string>(item));
				}
			}

			if (useBlob) {
				set_imagesAsBlob(imagesAsBlob);
			} else if (useFile) {
				set_imagesAsFile(imagesAsFile);
			} else {
				set_images(images);
			}

			return true;
		}

		TITANIUM_PROPERTY_GETTER(ImageView, paused)
		{
			return get_context().CreateBoolean(get_paused());
		}

		TITANIUM_PROPERTY_GETTER(ImageView, preventDefaultImage)
		{
			return get_context().CreateBoolean(get_preventDefaultImage());
		}

		TITANIUM_PROPERTY_SETTER(ImageView, preventDefaultImage)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_preventDefaultImage(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ImageView, repeatCount)
		{
			return get_context().CreateNumber(get_repeatCount());
		}

		TITANIUM_PROPERTY_SETTER(ImageView, repeatCount)
		{
			TITANIUM_ASSERT(argument.IsNumber());
			set_repeatCount(static_cast<uint32_t>(argument));
			return true;
		}

		TITANIUM_PROPERTY_GETTER(ImageView, reverse)
		{
			return get_context().CreateBoolean(get_reverse());
		}

		TITANIUM_PROPERTY_SETTER(ImageView, reverse)
		{
			TITANIUM_ASSERT(argument.IsBoolean());
			set_reverse(static_cast<bool>(argument));
			return true;
		}

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getAnimating, animating)

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getAutorotate, autorotate)

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getDecodeRetries, decodeRetries)
		TITANIUM_FUNCTION_AS_SETTER(ImageView, setDecodeRetries, decodeRetries)

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getDefaultImage, defaultImage)
		TITANIUM_FUNCTION_AS_SETTER(ImageView, setDefaultImage, defaultImage)

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getDuration, duration)
		TITANIUM_FUNCTION_AS_SETTER(ImageView, setDuration, duration)

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getEnableZoomControls, enableZoomControls)
		TITANIUM_FUNCTION_AS_SETTER(ImageView, setEnableZoomControls, enableZoomControls)

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getHires, hires)
		TITANIUM_FUNCTION_AS_SETTER(ImageView, setHires, hires)

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getImage, image)
		TITANIUM_FUNCTION_AS_SETTER(ImageView, setImage, image)

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getImages, images)
		TITANIUM_FUNCTION_AS_SETTER(ImageView, setImages, images)

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getPaused, paused)

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getPreventDefaultImage, preventDefaultImage)
		TITANIUM_FUNCTION_AS_SETTER(ImageView, setPreventDefaultImage, preventDefaultImage)

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getRepeatCount, repeatCount)
		TITANIUM_FUNCTION_AS_SETTER(ImageView, setRepeatCount, repeatCount)

		TITANIUM_FUNCTION_AS_GETTER(ImageView, getReverse, reverse)
		TITANIUM_FUNCTION_AS_SETTER(ImageView, setReverse, reverse)

	} // namespace UI
}  // namespace Titanium
