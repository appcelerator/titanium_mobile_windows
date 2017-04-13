/**
 * Windows Native Wrapper for Windows.UI.Xaml.Input.Pointer
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Xaml.Input.Pointer.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Xaml
			{
				namespace Input
				{

		Pointer::Pointer(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("Pointer::ctor");
		}

		void Pointer::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Pointer::postCallAsConstructor ", this);

		}

		::Windows::UI::Xaml::Input::Pointer^ Pointer::unwrapWindows_UI_Xaml_Input_Pointer() const
		{
			return dynamic_cast<::Windows::UI::Xaml::Input::Pointer^>(wrapped__);
		}

		::Windows::UI::Xaml::Input::Pointer^ Pointer::unwrap() const
		{
			return unwrapWindows_UI_Xaml_Input_Pointer();
		}

		void Pointer::wrap(::Windows::UI::Xaml::Input::Pointer^ object)
		{
			wrapped__ = object;
		}

		void Pointer::JSExportInitialize()
		{
			JSExport<Pointer>::SetClassVersion(1);
			JSExport<Pointer>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(Pointer, IsInContact);
			TITANIUM_ADD_PROPERTY_READONLY(Pointer, IsInRange);
			TITANIUM_ADD_PROPERTY_READONLY(Pointer, PointerDeviceType);
			TITANIUM_ADD_PROPERTY_READONLY(Pointer, PointerId);
		}

		TITANIUM_PROPERTY_GETTER(Pointer, IsInContact)
		{
			auto value = unwrap()->IsInContact;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Pointer, IsInRange)
		{
			auto value = unwrap()->IsInRange;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Pointer, PointerDeviceType)
		{
			auto value = unwrap()->PointerDeviceType;
			auto context = get_context();

			auto result = context.CreateNumber(static_cast<int32_t>(static_cast<int>(value))); // FIXME What if the enum isn't an int based one?!

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Pointer, PointerId)
		{
			auto value = unwrap()->PointerId;
			auto context = get_context();
 
			auto result = context.CreateNumber(value);

			return result;
		}

				} // namespace Input
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
