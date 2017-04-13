/**
 * Windows Native Wrapper for Windows.UI.Xaml.Data.Binding
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_DATA_BINDING_HPP_
#define _WINDOWS_UI_XAML_DATA_BINDING_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.Data.BindingBase.hpp"

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

		class TITANIUMWINDOWS_NATIVE_EXPORT Binding : public ::Titanium::Windows::UI::Xaml::Data::BindingBase, public JSExport<Binding>
		{

		public:
			TITANIUM_PROPERTY_DEF(UpdateSourceTrigger);
			TITANIUM_PROPERTY_DEF(TargetNullValue);
			TITANIUM_PROPERTY_DEF(FallbackValue);
			TITANIUM_PROPERTY_DEF(Source);
			TITANIUM_PROPERTY_DEF(RelativeSource);
			TITANIUM_PROPERTY_DEF(Path);
			TITANIUM_PROPERTY_DEF(Mode);
			TITANIUM_PROPERTY_DEF(ElementName);
			TITANIUM_PROPERTY_DEF(ConverterParameter);
			TITANIUM_PROPERTY_DEF(ConverterLanguage);
			TITANIUM_PROPERTY_DEF(Converter);


			Binding(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Binding() = default;
			Binding(const Binding&) = default;
			Binding& operator=(const Binding&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Binding(Binding&&)                 = default;
			Binding& operator=(Binding&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Data::Binding^ unwrapWindows_UI_Xaml_Data_Binding() const;
			void wrap(::Windows::UI::Xaml::Data::Binding^ object);

		private:
			::Windows::UI::Xaml::Data::Binding^ unwrap() const;

		};

				} // namespace Data
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_DATA_BINDING_HPP_
