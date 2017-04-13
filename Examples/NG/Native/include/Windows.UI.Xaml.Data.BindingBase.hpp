/**
 * Windows Native Wrapper for Windows.UI.Xaml.Data.BindingBase
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_DATA_BINDINGBASE_HPP_
#define _WINDOWS_UI_XAML_DATA_BINDINGBASE_HPP_

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
				namespace Data
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT BindingBase : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<BindingBase>
		{

		public:


			BindingBase(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~BindingBase() = default;
			BindingBase(const BindingBase&) = default;
			BindingBase& operator=(const BindingBase&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			BindingBase(BindingBase&&)                 = default;
			BindingBase& operator=(BindingBase&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Data::BindingBase^ unwrapWindows_UI_Xaml_Data_BindingBase() const;
			void wrap(::Windows::UI::Xaml::Data::BindingBase^ object);

		private:
			::Windows::UI::Xaml::Data::BindingBase^ unwrap() const;

		};

				} // namespace Data
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_DATA_BINDINGBASE_HPP_
