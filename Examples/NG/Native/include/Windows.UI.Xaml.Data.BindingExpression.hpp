/**
 * Windows Native Wrapper for Windows.UI.Xaml.Data.BindingExpression
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_DATA_BINDINGEXPRESSION_HPP_
#define _WINDOWS_UI_XAML_DATA_BINDINGEXPRESSION_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.Data.BindingExpressionBase.hpp"

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

		class TITANIUMWINDOWS_NATIVE_EXPORT BindingExpression : public ::Titanium::Windows::UI::Xaml::Data::BindingExpressionBase, public JSExport<BindingExpression>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(DataItem);
			TITANIUM_PROPERTY_READONLY_DEF(ParentBinding);

			TITANIUM_FUNCTION_DEF(UpdateSource);

			BindingExpression(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~BindingExpression() = default;
			BindingExpression(const BindingExpression&) = default;
			BindingExpression& operator=(const BindingExpression&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			BindingExpression(BindingExpression&&)                 = default;
			BindingExpression& operator=(BindingExpression&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Data::BindingExpression^ unwrapWindows_UI_Xaml_Data_BindingExpression() const;
			void wrap(::Windows::UI::Xaml::Data::BindingExpression^ object);

		private:
			::Windows::UI::Xaml::Data::BindingExpression^ unwrap() const;

		};

				} // namespace Data
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_DATA_BINDINGEXPRESSION_HPP_
