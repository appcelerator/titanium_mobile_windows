/**
 * Windows Native Wrapper for Windows.UI.Xaml.Documents.Inline
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_DOCUMENTS_INLINE_HPP_
#define _WINDOWS_UI_XAML_DOCUMENTS_INLINE_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.Documents.TextElement.hpp"

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

		class TITANIUMWINDOWS_NATIVE_EXPORT Inline : public ::Titanium::Windows::UI::Xaml::Documents::TextElement, public JSExport<Inline>
		{

		public:


			Inline(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Inline() = default;
			Inline(const Inline&) = default;
			Inline& operator=(const Inline&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Inline(Inline&&)                 = default;
			Inline& operator=(Inline&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Documents::Inline^ unwrapWindows_UI_Xaml_Documents_Inline() const;
			void wrap(::Windows::UI::Xaml::Documents::Inline^ object);

		private:
			::Windows::UI::Xaml::Documents::Inline^ unwrap() const;

		};

				} // namespace Documents
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_DOCUMENTS_INLINE_HPP_
