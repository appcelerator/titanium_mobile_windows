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
		class TITANIUMKIT_EXPORT ImageView : public virtual View, public JSExport<ImageView>
		{
		public:
			virtual std::string get_image() const TITANIUM_NOEXCEPT final;
			virtual void set_image(const std::string& image) TITANIUM_NOEXCEPT;

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

			virtual JSValue js_get_image() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_image(const JSValue& argument) TITANIUM_NOEXCEPT final;

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string image__;
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_IMAGEVIEW_HPP_
