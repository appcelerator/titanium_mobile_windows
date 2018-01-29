/**
* Titanium.UI.Label for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_UI_LABEL_HPP_
#define _TITANIUMWINDOWS_UI_LABEL_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/Label.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class Label
		  @ingroup Titanium.UI.Label

		  @discussion This is the Titanium.UI.Label implementation for
		  Windows.
		*/
		class TITANIUMWINDOWS_UI_EXPORT Label final : public Titanium::UI::Label, public JSExport<Label>
		{
		public:
			TITANIUM_PROPERTY_UNIMPLEMENTED(ellipsize);

			Label(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Label();
			Label(const Label&) = default;
			Label& operator=(const Label&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Label(Label&&) = default;
			Label& operator=(Label&&) = default;
#endif

			static void JSExportInitialize();
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual void set_color(const std::string& color) TITANIUM_NOEXCEPT override final;
			virtual void set_text(const std::string& text) TITANIUM_NOEXCEPT override final;
			virtual void set_text(const std::string& text, const bool resize) TITANIUM_NOEXCEPT;
			virtual void set_textAlign(const Titanium::UI::TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT override final;
			virtual void set_verticalAlign(const Titanium::UI::TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT override final;
			virtual void set_wordWrap(const bool& wordWrap) TITANIUM_NOEXCEPT override final;
			virtual void set_font(const Titanium::UI::Font& font) TITANIUM_NOEXCEPT override final;
			virtual void set_attributedString(const std::shared_ptr<Titanium::UI::AttributedString>& attr) TITANIUM_NOEXCEPT override final;
			virtual void set_autoLink(const std::unordered_set<Titanium::UI::AUTOLINK>& autoLink) TITANIUM_NOEXCEPT override final;
			virtual void set_maxLines(const std::uint32_t& maxLines) TITANIUM_NOEXCEPT override final;

			static const std::uint32_t DefaultFontSize = 20;

		private:
			// Measure desired size based on current text.
			void measureDesiredSize() TITANIUM_NOEXCEPT;

			Windows::UI::Xaml::Controls::Border^ border__;
			Windows::UI::Xaml::Controls::TextBlock^ label__;
			Windows::UI::Color defaultForegroundColor__;

			bool need_measure__ { false };
#pragma warning(push)
#pragma warning(disable : 4251)
			Titanium::LayoutEngine::Rect previousSize__;
#pragma warning(pop)
		};
	} // namespace UI
} // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UI_LABEL_HPP_
