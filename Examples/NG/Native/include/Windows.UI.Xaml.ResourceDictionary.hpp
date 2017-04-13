/**
 * Windows Native Wrapper for Windows.UI.Xaml.ResourceDictionary
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_RESOURCEDICTIONARY_HPP_
#define _WINDOWS_UI_XAML_RESOURCEDICTIONARY_HPP_

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


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT ResourceDictionary : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<ResourceDictionary>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(Size);
			TITANIUM_PROPERTY_DEF(Source);
			TITANIUM_PROPERTY_READONLY_DEF(MergedDictionaries);
			TITANIUM_PROPERTY_READONLY_DEF(ThemeDictionaries);

			TITANIUM_FUNCTION_DEF(Lookup);
			TITANIUM_FUNCTION_DEF(HasKey);
			TITANIUM_FUNCTION_DEF(GetView);
			TITANIUM_FUNCTION_DEF(Insert);
			TITANIUM_FUNCTION_DEF(Remove);
			TITANIUM_FUNCTION_DEF(Clear);
			TITANIUM_FUNCTION_DEF(First);

			ResourceDictionary(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ResourceDictionary() = default;
			ResourceDictionary(const ResourceDictionary&) = default;
			ResourceDictionary& operator=(const ResourceDictionary&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ResourceDictionary(ResourceDictionary&&)                 = default;
			ResourceDictionary& operator=(ResourceDictionary&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::ResourceDictionary^ unwrapWindows_UI_Xaml_ResourceDictionary() const;
			void wrap(::Windows::UI::Xaml::ResourceDictionary^ object);

		private:
			::Windows::UI::Xaml::ResourceDictionary^ unwrap() const;

		};

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_RESOURCEDICTIONARY_HPP_
