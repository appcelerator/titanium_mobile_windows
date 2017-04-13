/**
 * Windows Native Wrapper for Windows.UI.Xaml.SetterBase
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_SETTERBASE_HPP_
#define _WINDOWS_UI_XAML_SETTERBASE_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT SetterBase : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<SetterBase>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(IsSealed);


			SetterBase(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~SetterBase() = default;
			SetterBase(const SetterBase&) = default;
			SetterBase& operator=(const SetterBase&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			SetterBase(SetterBase&&)                 = default;
			SetterBase& operator=(SetterBase&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::SetterBase^ unwrapWindows_UI_Xaml_SetterBase() const;
			void wrap(::Windows::UI::Xaml::SetterBase^ object);

		private:
			::Windows::UI::Xaml::SetterBase^ unwrap() const;

		};

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_SETTERBASE_HPP_
