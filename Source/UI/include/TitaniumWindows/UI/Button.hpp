/**
* Titanium.UI.Button for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_BUTTON_HPP_
#define _TITANIUMWINDOWS_UI_BUTTON_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/Button.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		class TITANIUMWINDOWS_UI_EXPORT WindowsButtonLayoutDelegate : public WindowsViewLayoutDelegate {
		public:
			WindowsButtonLayoutDelegate() TITANIUM_NOEXCEPT : WindowsViewLayoutDelegate() { };
			virtual ~WindowsButtonLayoutDelegate() = default;

			virtual Windows::UI::Xaml::FrameworkElement^ getComponent() const TITANIUM_NOEXCEPT override
			{
				return component__;
			}
		};

		/*!
		  @class Button
		  @ingroup Titanium.UI.Button

		  @discussion This is the Titanium.UI.Button implementation for Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT Button final : public Titanium::UI::Button, public JSExport<Button>
		{
		public:

			Button(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Button() = default;
			Button(const Button&) = default;
			Button& operator=(const Button&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Button(Button&&) = default;
			Button& operator=(Button&&) = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void set_color(const std::string& color) TITANIUM_NOEXCEPT override final;
			virtual void set_font(const Titanium::UI::Font& font) TITANIUM_NOEXCEPT override final;
			virtual void set_image(const std::string& image) TITANIUM_NOEXCEPT override final;
			virtual void set_imageAsBlob(const std::shared_ptr<Titanium::Blob>& image) TITANIUM_NOEXCEPT override final;
			virtual void set_textAlign(const Titanium::UI::TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT override final;
			virtual void set_title(const std::string& title) TITANIUM_NOEXCEPT override final;
			virtual void set_verticalAlign(const Titanium::UI::TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT override final;

			static const std::uint32_t DefaultFontSize = 20;

			virtual void enableEvent(const std::string& event_name)  TITANIUM_NOEXCEPT override final;
		private:
			Windows::UI::Xaml::Controls::Border^ border__;
			Windows::UI::Xaml::Controls::Button^ button__;
#pragma warning(push)
#pragma warning(disable : 4251)
			Windows::Foundation::EventRegistrationToken loaded_event__;
			Windows::Foundation::EventRegistrationToken click_event__;
#pragma warning(pop)

		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_BUTTON_HPP_
