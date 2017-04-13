/**
 * Windows Native Wrapper for Windows.UI.Xaml.TriggerBase
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_TRIGGERBASE_HPP_
#define _WINDOWS_UI_XAML_TRIGGERBASE_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT TriggerBase : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<TriggerBase>
		{

		public:


			TriggerBase(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~TriggerBase() = default;
			TriggerBase(const TriggerBase&) = default;
			TriggerBase& operator=(const TriggerBase&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TriggerBase(TriggerBase&&)                 = default;
			TriggerBase& operator=(TriggerBase&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::TriggerBase^ unwrapWindows_UI_Xaml_TriggerBase() const;
			void wrap(::Windows::UI::Xaml::TriggerBase^ object);

		private:
			::Windows::UI::Xaml::TriggerBase^ unwrap() const;

		};

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_TRIGGERBASE_HPP_
