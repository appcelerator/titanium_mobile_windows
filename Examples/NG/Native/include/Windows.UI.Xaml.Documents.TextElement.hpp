/**
 * Windows Native Wrapper for Windows.UI.Xaml.Documents.TextElement
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_DOCUMENTS_TEXTELEMENT_HPP_
#define _WINDOWS_UI_XAML_DOCUMENTS_TEXTELEMENT_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.DependencyObject.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Documents
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT TextElement : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<TextElement>
		{

		public:
			TITANIUM_PROPERTY_DEF(Language);
			TITANIUM_PROPERTY_DEF(Foreground);
			TITANIUM_PROPERTY_DEF(FontWeight);
			TITANIUM_PROPERTY_DEF(FontStyle);
			TITANIUM_PROPERTY_DEF(FontStretch);
			TITANIUM_PROPERTY_DEF(FontSize);
			TITANIUM_PROPERTY_DEF(FontFamily);
			TITANIUM_PROPERTY_DEF(CharacterSpacing);
			TITANIUM_PROPERTY_READONLY_DEF(ContentEnd);
			TITANIUM_PROPERTY_READONLY_DEF(ContentStart);
			TITANIUM_PROPERTY_READONLY_DEF(ElementEnd);
			TITANIUM_PROPERTY_READONLY_DEF(ElementStart);
			TITANIUM_PROPERTY_READONLY_DEF(Name);
			TITANIUM_PROPERTY_READONLY_DEF(CharacterSpacingProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontFamilyProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontSizeProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontStretchProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontStyleProperty);
			TITANIUM_PROPERTY_READONLY_DEF(FontWeightProperty);
			TITANIUM_PROPERTY_READONLY_DEF(ForegroundProperty);
			TITANIUM_PROPERTY_READONLY_DEF(LanguageProperty);

			TITANIUM_FUNCTION_DEF(FindName);

			TextElement(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~TextElement() = default;
			TextElement(const TextElement&) = default;
			TextElement& operator=(const TextElement&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TextElement(TextElement&&)                 = default;
			TextElement& operator=(TextElement&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Documents::TextElement^ unwrapWindows_UI_Xaml_Documents_TextElement() const;
			void wrap(::Windows::UI::Xaml::Documents::TextElement^ object);

		private:
			::Windows::UI::Xaml::Documents::TextElement^ unwrap() const;

		};

				} // namespace Documents
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_DOCUMENTS_TEXTELEMENT_HPP_
