/**
 * Windows Native Wrapper for Windows.UI.Xaml.Documents.TextPointer
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_DOCUMENTS_TEXTPOINTER_HPP_
#define _WINDOWS_UI_XAML_DOCUMENTS_TEXTPOINTER_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Platform.Object.hpp"

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

		class TITANIUMWINDOWS_NATIVE_EXPORT TextPointer : public ::Titanium::Platform::Object, public JSExport<TextPointer>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(LogicalDirection);
			TITANIUM_PROPERTY_READONLY_DEF(Offset);
			TITANIUM_PROPERTY_READONLY_DEF(Parent);
			TITANIUM_PROPERTY_READONLY_DEF(VisualParent);

			TITANIUM_FUNCTION_DEF(GetCharacterRect);
			TITANIUM_FUNCTION_DEF(GetPositionAtOffset);

			TextPointer(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~TextPointer() = default;
			TextPointer(const TextPointer&) = default;
			TextPointer& operator=(const TextPointer&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TextPointer(TextPointer&&)                 = default;
			TextPointer& operator=(TextPointer&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Documents::TextPointer^ unwrapWindows_UI_Xaml_Documents_TextPointer() const;
			void wrap(::Windows::UI::Xaml::Documents::TextPointer^ object);

		private:
			::Windows::UI::Xaml::Documents::TextPointer^ unwrap() const;

		};

				} // namespace Documents
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_DOCUMENTS_TEXTPOINTER_HPP_
