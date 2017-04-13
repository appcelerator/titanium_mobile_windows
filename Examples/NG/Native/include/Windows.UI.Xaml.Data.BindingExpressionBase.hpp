/**
 * Windows Native Wrapper for Windows.UI.Xaml.Data.BindingExpressionBase
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_DATA_BINDINGEXPRESSIONBASE_HPP_
#define _WINDOWS_UI_XAML_DATA_BINDINGEXPRESSIONBASE_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT BindingExpressionBase : public ::Titanium::Platform::Object, public JSExport<BindingExpressionBase>
		{

		public:


			BindingExpressionBase(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~BindingExpressionBase() = default;
			BindingExpressionBase(const BindingExpressionBase&) = default;
			BindingExpressionBase& operator=(const BindingExpressionBase&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			BindingExpressionBase(BindingExpressionBase&&)                 = default;
			BindingExpressionBase& operator=(BindingExpressionBase&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Data::BindingExpressionBase^ unwrapWindows_UI_Xaml_Data_BindingExpressionBase() const;
			void wrap(::Windows::UI::Xaml::Data::BindingExpressionBase^ object);

		private:
			::Windows::UI::Xaml::Data::BindingExpressionBase^ unwrap() const;

		};

				} // namespace Data
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_DATA_BINDINGEXPRESSIONBASE_HPP_
