/**
 * Windows Native Wrapper for Windows.UI.Xaml.DataTemplate
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_DATATEMPLATE_HPP_
#define _WINDOWS_UI_XAML_DATATEMPLATE_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.FrameworkTemplate.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT DataTemplate : public ::Titanium::Windows::UI::Xaml::FrameworkTemplate, public JSExport<DataTemplate>
		{

		public:

			TITANIUM_FUNCTION_DEF(LoadContent);

			DataTemplate(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~DataTemplate() = default;
			DataTemplate(const DataTemplate&) = default;
			DataTemplate& operator=(const DataTemplate&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			DataTemplate(DataTemplate&&)                 = default;
			DataTemplate& operator=(DataTemplate&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::DataTemplate^ unwrapWindows_UI_Xaml_DataTemplate() const;
			void wrap(::Windows::UI::Xaml::DataTemplate^ object);

		private:
			::Windows::UI::Xaml::DataTemplate^ unwrap() const;

		};

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_DATATEMPLATE_HPP_
