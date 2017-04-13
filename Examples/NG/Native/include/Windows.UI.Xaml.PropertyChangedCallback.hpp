/**
 * Windows Native Wrapper for Windows.UI.Xaml.PropertyChangedCallback
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_PROPERTYCHANGEDCALLBACK_HPP_
#define _WINDOWS_UI_XAML_PROPERTYCHANGEDCALLBACK_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT PropertyChangedCallback : public ::Titanium::Platform::Object, public JSExport<PropertyChangedCallback>
		{

		public:

			TITANIUM_FUNCTION_DEF(Invoke);

			PropertyChangedCallback(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~PropertyChangedCallback() = default;
			PropertyChangedCallback(const PropertyChangedCallback&) = default;
			PropertyChangedCallback& operator=(const PropertyChangedCallback&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			PropertyChangedCallback(PropertyChangedCallback&&)                 = default;
			PropertyChangedCallback& operator=(PropertyChangedCallback&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::PropertyChangedCallback^ unwrapWindows_UI_Xaml_PropertyChangedCallback() const;
			void wrap(::Windows::UI::Xaml::PropertyChangedCallback^ object);

		private:
			::Windows::UI::Xaml::PropertyChangedCallback^ unwrap() const;

		};

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_PROPERTYCHANGEDCALLBACK_HPP_
