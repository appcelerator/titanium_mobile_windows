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
		    : UIBase(js_context),
		      image__(js_context.CreateString())
		{
		}

		std::string ImageView::get_image() const TITANIUM_NOEXCEPT
		{
			return image__;
		}

		void ImageView::set_image(const std::string& image) TITANIUM_NOEXCEPT
		{
			image__ = image;
		}

		// TODO: The following functions can automatically be generated from
		// the YAML API docs.

		void ImageView::JSExportInitialize()
		{
			JSExport<ImageView>::SetClassVersion(1);
			JSExport<ImageView>::SetParent(JSExport<UIBase>::Class());
			JSExport<ImageView>::AddValueProperty("image", std::mem_fn(&ImageView::js_get_image), std::mem_fn(&ImageView::js_set_image));
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
	} // namespace UI
}  // namespace Titanium
