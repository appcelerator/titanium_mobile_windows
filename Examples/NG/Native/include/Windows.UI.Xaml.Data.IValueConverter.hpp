/**
 * Windows Native Wrapper for Windows.UI.Xaml.Data.IValueConverter
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_DATA_IVALUECONVERTER_HPP_
#define _WINDOWS_UI_XAML_DATA_IVALUECONVERTER_HPP_

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
				namespace Data
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT IValueConverter : public ::Titanium::Platform::Object, public JSExport<IValueConverter>
		{

		public:

			TITANIUM_FUNCTION_DEF(Convert);
			TITANIUM_FUNCTION_DEF(ConvertBack);

			IValueConverter(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~IValueConverter() = default;
			IValueConverter(const IValueConverter&) = default;
			IValueConverter& operator=(const IValueConverter&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			IValueConverter(IValueConverter&&)                 = default;
			IValueConverter& operator=(IValueConverter&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Data::IValueConverter^ unwrapWindows_UI_Xaml_Data_IValueConverter() const;
			void wrap(::Windows::UI::Xaml::Data::IValueConverter^ object);

		private:
			::Windows::UI::Xaml::Data::IValueConverter^ unwrap() const;

		};

				} // namespace Data
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_DATA_IVALUECONVERTER_HPP_
