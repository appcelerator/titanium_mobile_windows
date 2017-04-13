/**
 * Windows Native Wrapper for Windows.UI.Xaml.PropertyPath
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.PropertyPath.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{

		PropertyPath::PropertyPath(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Windows::UI::Xaml::DependencyObject(js_context)
		{
			TITANIUM_LOG_DEBUG("PropertyPath::ctor");
		}

		void PropertyPath::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("PropertyPath::postCallAsConstructor ", this);
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsString(), "Expected String");
			auto path = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_0));

				wrapped__ = ref new ::Windows::UI::Xaml::PropertyPath(path);
			}

		}

		::Windows::UI::Xaml::PropertyPath^ PropertyPath::unwrapWindows_UI_Xaml_PropertyPath() const
		{
			return dynamic_cast<::Windows::UI::Xaml::PropertyPath^>(wrapped__);
		}

		::Windows::UI::Xaml::PropertyPath^ PropertyPath::unwrap() const
		{
			return unwrapWindows_UI_Xaml_PropertyPath();
		}

		void PropertyPath::wrap(::Windows::UI::Xaml::PropertyPath^ object)
		{
			wrapped__ = object;
		}

		void PropertyPath::JSExportInitialize()
		{
			JSExport<PropertyPath>::SetClassVersion(1);
			JSExport<PropertyPath>::SetParent(JSExport<Windows::UI::Xaml::DependencyObject>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(PropertyPath, Path);
		}

		TITANIUM_PROPERTY_GETTER(PropertyPath, Path)
		{
			auto value = unwrap()->Path;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
