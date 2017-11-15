/**
 * Titanium.UI.ActivityIndicator for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_ACTIVITYINDICATOR_HPP_
#define _TITANIUMWINDOWS_ACTIVITYINDICATOR_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "Titanium/UI/ActivityIndicator.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace HAL;

		class TITANIUMWINDOWS_UI_EXPORT ActivityIndicatorLayoutDelegate : public WindowsViewLayoutDelegate {
		public:
			ActivityIndicatorLayoutDelegate(Windows::UI::Xaml::Controls::ProgressRing^) TITANIUM_NOEXCEPT;
			virtual ~ActivityIndicatorLayoutDelegate() = default;

			// Hides the activity indicator and stops the animation.
			virtual void hide() TITANIUM_NOEXCEPT override;

			// Shows the activity indicator and starts the animation.
			virtual void show() TITANIUM_NOEXCEPT override;
		protected:
			Windows::UI::Xaml::Controls::ProgressRing^ ring__;
		};

		/*!
		  @class ActivityIndicator
		  @ingroup Titanium.UI.ActivityIndicator

		  @discussion This is the Titanium.UI.ActivityIndicator implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT ActivityIndicator final : public Titanium::UI::ActivityIndicator, public JSExport<ActivityIndicator>
		{

		public:
			TITANIUM_PROPERTY_UNIMPLEMENTED(style);
			TITANIUM_PROPERTY_UNIMPLEMENTED(indicatorDiameter);

			ActivityIndicator(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ActivityIndicator()                  = default;
			ActivityIndicator(const ActivityIndicator&)            = default;
			ActivityIndicator& operator=(const ActivityIndicator&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ActivityIndicator(ActivityIndicator&&)                 = default;
			ActivityIndicator& operator=(ActivityIndicator&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void set_color(const std::string& color)      TITANIUM_NOEXCEPT override;
			virtual void set_font(const Titanium::UI::Font& font) TITANIUM_NOEXCEPT override;
			virtual void set_message(const std::string& message)  TITANIUM_NOEXCEPT override;
			virtual void set_indicatorColor(const std::string& color) TITANIUM_NOEXCEPT override;
			virtual void set_indicatorDiameter(const std::string& diameter) TITANIUM_NOEXCEPT override;

		private:
			Windows::UI::Xaml::Controls::StackPanel^ panel__;
			Windows::UI::Xaml::Controls::ProgressRing^ ring__;
			Windows::UI::Xaml::Controls::TextBlock^ label__;

		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_ACTIVITYINDICATOR_HPP_