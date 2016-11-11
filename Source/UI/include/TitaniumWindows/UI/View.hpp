/**
 * Titanium.UI.View for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_VIEW_HPP_
#define _TITANIUMWINDOWS_UI_VIEW_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/View.hpp"
#include <unordered_map>

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class View
		  @ingroup Titanium.UI.View

		  @discussion This is the Titanium.UI.View implementation for
		  Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT View final : public Titanium::UI::View, public JSExport<View>
		{

		public:

			TITANIUM_PROPERTY_UNIMPLEMENTED(accessibilityHidden);
			TITANIUM_PROPERTY_UNIMPLEMENTED(accessibilityHint);
			TITANIUM_PROPERTY_UNIMPLEMENTED(accessibilityLabel);
			TITANIUM_PROPERTY_UNIMPLEMENTED(accessibilityValue);
			TITANIUM_PROPERTY_UNIMPLEMENTED(anchorPoint);
			TITANIUM_PROPERTY_UNIMPLEMENTED(animatedCenter);
			TITANIUM_PROPERTY_UNIMPLEMENTED(backgroundRepeat);
			TITANIUM_PROPERTY_UNIMPLEMENTED(backgroundLeftCap);
			TITANIUM_PROPERTY_UNIMPLEMENTED(backgroundTopCap);
			TITANIUM_PROPERTY_UNIMPLEMENTED(clipMode);
			TITANIUM_PROPERTY_UNIMPLEMENTED(focusable);
			TITANIUM_PROPERTY_UNIMPLEMENTED(overrideCurrentAnimation);
			TITANIUM_PROPERTY_UNIMPLEMENTED(pullBackgroundColor);
			TITANIUM_PROPERTY_UNIMPLEMENTED(softKeyboardOnFocus);
			TITANIUM_PROPERTY_UNIMPLEMENTED(tintColor);
			TITANIUM_PROPERTY_UNIMPLEMENTED(transform);
			TITANIUM_PROPERTY_UNIMPLEMENTED(viewShadowRadius);
			TITANIUM_PROPERTY_UNIMPLEMENTED(viewShadowColor);
			TITANIUM_PROPERTY_UNIMPLEMENTED(viewShadowOffset);
			TITANIUM_PROPERTY_UNIMPLEMENTED(horizontalWrap);
			TITANIUM_PROPERTY_UNIMPLEMENTED(keepScreenOn);

			// Implemented, works with some components which uses Xaml.Controls.Control
			// But it doesn't work on TI.UI.View because it's Xaml.Controls.Panel
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderColor);

			View(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~View();
			View(const View&) = default;
			View& operator=(const View&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			View(View&&) = default;
			View& operator=(View&&) = default;
#endif

			static void JSExportInitialize();
			static Windows::UI::Xaml::Media::FontFamily^ LookupFont(const JSContext& js_context, const std::string& family);

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual Windows::UI::Xaml::FrameworkElement^ getComponent() TITANIUM_NOEXCEPT;

		private:

			Windows::UI::Xaml::Controls::Canvas^ canvas__;

#pragma warning(push)
#pragma warning(disable : 4251)
			static std::unordered_map<std::string, std::string> CustomFonts__;
#pragma warning(pop)

		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_VIEW_HPP_
