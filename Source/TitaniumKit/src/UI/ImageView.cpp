/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/ImageView.hpp"

namespace Titanium { namespace UI {
	
	ImageView::ImageView(const JSContext& js_context) TITANIUM_NOEXCEPT
		: View(js_context)
		, image__(js_context.CreateString()) {
	}
	
	ImageView::ImageView(const ImageView& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
	: View(rhs, arguments)
		, image__(rhs.image__) {
	}
	
	JSValue ImageView::get_image() const TITANIUM_NOEXCEPT {
		return image__;
	}
	
	void ImageView::set_image(const JSValue& title) TITANIUM_NOEXCEPT {
		image__ = title;
	}
	
	// TODO: The following functions can automatically be generated from
	// the YAML API docs.
	
	void ImageView::JSExportInitialize() {
		JSExport<ImageView>::SetClassVersion(1);
		JSExport<ImageView>::SetParent(JSExport<View>::Class());
		JSExport<ImageView>::AddValueProperty("image", std::mem_fn(&ImageView::get_image), std::mem_fn(&ImageView::setImageArgumentValidator));
	}
	
	bool ImageView::setImageArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT {
		TITANIUM_LOG_WARN("Image::setImageArgumentValidator: Unimplemented");

		// Base classes must implement this method. This is the minimum
		// functionality that you should perform:
		//
		// TITANIUM_ASSERT(argument.IsString());
		// set_image(argument);
		// return true;

		return false;
	}
	
}} // namespace Titanium { namespace UI {
