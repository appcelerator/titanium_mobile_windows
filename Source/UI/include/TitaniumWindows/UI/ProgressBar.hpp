/**
 * Titanium.UI.ProgressBar for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_PROGRESSBAR_HPP_
#define _TITANIUMWINDOWS_PROGRESSBAR_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/ProgressBar.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{
	namespace UI
	{

		using namespace HAL;

		class TITANIUMWINDOWS_UI_EXPORT ProgressBarLayoutDelegate : public WindowsViewLayoutDelegate {
		public:
			ProgressBarLayoutDelegate(Windows::UI::Xaml::Controls::ProgressBar^) TITANIUM_NOEXCEPT;
			virtual ~ProgressBarLayoutDelegate() = default;

			// Hides progress bar and stops the animation.
			virtual void hide() TITANIUM_NOEXCEPT override;

			// Shows progress Bar and starts the animation.
			virtual void show() TITANIUM_NOEXCEPT override;

			virtual void set_borderWidth(const std::string& borderWidth) TITANIUM_NOEXCEPT override;
		protected:
			Windows::UI::Xaml::Controls::ProgressBar^ bar__;
			bool isIndeterminate__ { false };
		};

		/*!
		  @class ProgressBar
		  @ingroup Titanium.UI.ProgressBar

		  @discussion This is the Titanium.UI.ProgressBar implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT ProgressBar final : public Titanium::UI::ProgressBar, public JSExport<ProgressBar>
		{

		public:
			TITANIUM_FUNCTION_UNIMPLEMENTED(add);
			TITANIUM_FUNCTION_UNIMPLEMENTED(remove);
			TITANIUM_PROPERTY_UNIMPLEMENTED(font);
			TITANIUM_PROPERTY_UNIMPLEMENTED(style);
			TITANIUM_PROPERTY_UNIMPLEMENTED(borderRadius);

			ProgressBar(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ProgressBar();
			ProgressBar(const ProgressBar&)            = default;
			ProgressBar& operator=(const ProgressBar&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ProgressBar(ProgressBar&&)                 = default;
			ProgressBar& operator=(ProgressBar&&)      = default;
#endif

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;
			static void JSExportInitialize();

			virtual void set_color(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_message(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_min(const double&)   TITANIUM_NOEXCEPT override;
			virtual void set_max(const double&)   TITANIUM_NOEXCEPT override;
			virtual void set_tintColor(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_trackTintColor(const std::string&) TITANIUM_NOEXCEPT override;
			virtual void set_value(const double&) TITANIUM_NOEXCEPT override;

		private:
			Windows::UI::Xaml::Controls::StackPanel^ panel__;
			Windows::UI::Xaml::Controls::ProgressBar^ bar__;
			Windows::UI::Xaml::Controls::TextBlock^ label__;

			Windows::Foundation::EventRegistrationToken sizechanged_event__;

		};
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_PROGRESSBAR_HPP_