/**
 * Windows Native Wrapper for Windows.UI.Xaml.PropertyChangedCallback
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.DependencyObject.hpp"
#include "Windows.UI.Xaml.DependencyPropertyChangedEventArgs.hpp"
#include "Windows.UI.Xaml.PropertyChangedCallback.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{

		PropertyChangedCallback::PropertyChangedCallback(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("PropertyChangedCallback::ctor");
		}

		void PropertyChangedCallback::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("PropertyChangedCallback::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::PropertyChangedCallback^ PropertyChangedCallback::unwrapWindows_UI_Xaml_PropertyChangedCallback() const
		{
			return dynamic_cast<::Windows::UI::Xaml::PropertyChangedCallback^>(wrapped__);
		}

		::Windows::UI::Xaml::PropertyChangedCallback^ PropertyChangedCallback::unwrap() const
		{
			return unwrapWindows_UI_Xaml_PropertyChangedCallback();
		}

		void PropertyChangedCallback::wrap(::Windows::UI::Xaml::PropertyChangedCallback^ object)
		{
			wrapped__ = object;
		}

		void PropertyChangedCallback::JSExportInitialize()
		{
			JSExport<PropertyChangedCallback>::SetClassVersion(1);
			JSExport<PropertyChangedCallback>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_FUNCTION(PropertyChangedCallback, Invoke);
		}

		TITANIUM_FUNCTION(PropertyChangedCallback, Invoke)
		{
			auto context = get_context();
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_d = static_cast<JSObject>(_0);
 
			auto wrapper_d = object_d.GetPrivate<Windows::UI::Xaml::DependencyObject>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto d = wrapper_d->unwrapWindows_UI_Xaml_DependencyObject();

				auto _1 = arguments.at(1);
			TITANIUM_ASSERT_AND_THROW(_1.IsObject(), "Expected Object");
			auto object_e = static_cast<JSObject>(_1);
 
			auto wrapper_e = object_e.GetPrivate<Windows::UI::Xaml::DependencyPropertyChangedEventArgs>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto e = wrapper_e->unwrapWindows_UI_Xaml_DependencyPropertyChangedEventArgs();

				unwrap()->Invoke(d, e);
				return context.CreateUndefined(); 
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched PropertyChangedCallback::Invoke with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
