/**
 * Windows Native Wrapper for Windows.UI.Xaml.Media.FontFamily
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Media.FontFamily.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Media
				{

		FontFamily::FontFamily(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("FontFamily::ctor");
		}

		void FontFamily::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("FontFamily::postCallAsConstructor ", this);
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsString(), "Expected String");
			auto familyName = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_0));

				wrapped__ = ref new ::Windows::UI::Xaml::Media::FontFamily(familyName);
			}

		}

		::Windows::UI::Xaml::Media::FontFamily^ FontFamily::unwrapWindows_UI_Xaml_Media_FontFamily() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Media::FontFamily^>(wrapped__);
		}

		::Windows::UI::Xaml::Media::FontFamily^ FontFamily::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Media_FontFamily();
		}

		void FontFamily::wrap(::Windows::UI::Xaml::Media::FontFamily^ object)
		{
			wrapped__ = object;
		}

		void FontFamily::JSExportInitialize()
		{
			JSExport<FontFamily>::SetClassVersion(1);
			JSExport<FontFamily>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(FontFamily, Source);
		}

		TITANIUM_PROPERTY_GETTER(FontFamily, Source)
		{
			auto value = unwrap()->Source;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

				} // namespace Media
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
