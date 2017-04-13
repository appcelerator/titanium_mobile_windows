/**
 * Windows Native Wrapper for Windows.UI.Xaml.CreateDefaultValueCallback
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_CREATEDEFAULTVALUECALLBACK_HPP_
#define _WINDOWS_UI_XAML_CREATEDEFAULTVALUECALLBACK_HPP_

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


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT CreateDefaultValueCallback : public ::Titanium::Platform::Object, public JSExport<CreateDefaultValueCallback>
		{

		public:

			TITANIUM_FUNCTION_DEF(Invoke);

			CreateDefaultValueCallback(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~CreateDefaultValueCallback() = default;
			CreateDefaultValueCallback(const CreateDefaultValueCallback&) = default;
			CreateDefaultValueCallback& operator=(const CreateDefaultValueCallback&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			CreateDefaultValueCallback(CreateDefaultValueCallback&&)                 = default;
			CreateDefaultValueCallback& operator=(CreateDefaultValueCallback&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::CreateDefaultValueCallback^ unwrapWindows_UI_Xaml_CreateDefaultValueCallback() const;
			void wrap(::Windows::UI::Xaml::CreateDefaultValueCallback^ object);

		private:
			::Windows::UI::Xaml::CreateDefaultValueCallback^ unwrap() const;

		};

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_CREATEDEFAULTVALUECALLBACK_HPP_
