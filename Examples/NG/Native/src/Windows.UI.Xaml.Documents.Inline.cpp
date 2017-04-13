/**
 * Windows Native Wrapper for Windows.UI.Xaml.Documents.Inline
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Documents.Inline.hpp"
#include "Windows.UI.Xaml.Documents.TextElement.hpp"
#include "Titanium/detail/TiImpl.hpp"

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

		Inline::Inline(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::Documents::TextElement(js_context)
		{
			TITANIUM_LOG_DEBUG("Inline::ctor");
		}

		void Inline::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Inline::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Documents::Inline^ Inline::unwrapWindows_UI_Xaml_Documents_Inline() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Documents::Inline^>(wrapped__);
		}

		::Windows::UI::Xaml::Documents::Inline^ Inline::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Documents_Inline();
		}

		void Inline::wrap(::Windows::UI::Xaml::Documents::Inline^ object)
		{
			wrapped__ = object;
		}

		void Inline::JSExportInitialize()
		{
			JSExport<Inline>::SetClassVersion(1);
			JSExport<Inline>::SetParent(JSExport<Windows::UI::Xaml::Documents::TextElement>::Class());

		}

				} // namespace Documents
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
