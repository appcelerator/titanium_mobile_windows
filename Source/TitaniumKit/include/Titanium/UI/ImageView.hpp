/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_IMAGEVIEW_HPP_
#define _TITANIUM_UI_IMAGEVIEW_HPP_

#include "Titanium/UI/View.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium UI ImageView.

		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.ImageView
		*/
		class TITANIUMKIT_EXPORT ImageView : public View, public JSExport<ImageView>
		{
		public:

			/*!
			  @method

			  @abstract start() : void

			  @discussion Starts the image animation. On Android and Mobile Web, also resets index to the first image.

			  This method only works if multiple images are specified.

			  @result void
			*/
			virtual void start(JSObject& this_object) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract stop() : void

			  @discussion Stops a running animation. On iOS and Mobile Web, also resets index to the first image.

			  This method only works if multiple images are specified.

			  @result void
			*/
			virtual void stop(JSObject& this_object) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract duration : Number

			  @discussion Amount of time in milliseconds to animate one cycle.

			  Starting with release 2.1.1, the minimum duration is 30 ms and the default duration is 200 ms.

			  On Android, prior to release 2.1.1, if any images are assigned to the images property when the animation is started, duration will be set to the number of images multiplied by 33 ms. If no images are assigned, duration will be set to 100 ms.

			  On iOS, Tizen and Mobile Web, prior to release 2.1.1, the default is 30 ms.

			  On Android, if the value of duration is changed, stop and start need to be called for the new value to take effect.

			  Default: 200 ms in Release 2.1.1 and later. Platform-specific default in earlier releases.
			*/
			virtual std::chrono::milliseconds get_duration() const TITANIUM_NOEXCEPT final;
			virtual void set_duration(const std::chrono::milliseconds& duration) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract image : String/Titanium.Blob/Titanium.Filesystem.File

			  @discussion Image to display.

			  Image to display, defined using a local filesystem path, a File object, a remote URL, or a Blob object containing image data. Blob and File objects are not supported on Mobile Web.
			*/
			virtual std::string get_image() const TITANIUM_NOEXCEPT final;
			virtual void set_image(const std::string& image) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract image : String[]/Titanium.Blob[]/Titanium.Filesystem.File[]

			  @discussion Array of images to animate, defined using local filesystem paths, File objects, remote URLs (Android only), or Blob objects containing image data. Blob and File objects are not supported on Mobile Web.
			*/
			virtual std::vector<std::string> get_images() const TITANIUM_NOEXCEPT final;
			virtual void set_images(const std::vector<std::string>& images) TITANIUM_NOEXCEPT;

			/*!
			  @method

			  @abstract preventDefaultImage : Boolean

			  @discussion Prevent the default image from being displayed while loading a remote image. This property is ignored when the defaultImage property is set.

			  Default: false
			*/
			virtual bool get_preventDefaultImage() const TITANIUM_NOEXCEPT final;
			virtual void set_preventDefaultImage(const bool& preventDefaultImage) TITANIUM_NOEXCEPT;

			ImageView(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~ImageView() = default;
			ImageView(const ImageView&) = default;
			ImageView& operator=(const ImageView&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ImageView(ImageView&&) = default;
			ImageView& operator=(ImageView&&) = default;
#endif

			// TODO: The following functions can automatically be generated
			// from the YAML API docs.
			static void JSExportInitialize();

			virtual JSValue js_start(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
			virtual JSValue js_stop(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

			virtual JSValue js_get_duration() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_duration(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_image() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_image(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_images() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_images(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_get_preventDefaultImage() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_preventDefaultImage(const JSValue& argument) TITANIUM_NOEXCEPT final;

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::chrono::milliseconds duration__;
			std::string image__;
			std::vector<std::string> images__;
			bool preventDefaultImage__;
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_IMAGEVIEW_HPP_
