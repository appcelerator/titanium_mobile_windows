/**
 * Windows Native Wrapper for Windows.UI.Xaml.Input.Pointer
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_INPUT_POINTER_HPP_
#define _WINDOWS_UI_XAML_INPUT_POINTER_HPP_

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
				namespace Input
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT Pointer : public ::Titanium::Platform::Object, public JSExport<Pointer>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(IsInContact);
			TITANIUM_PROPERTY_READONLY_DEF(IsInRange);
			TITANIUM_PROPERTY_READONLY_DEF(PointerDeviceType);
			TITANIUM_PROPERTY_READONLY_DEF(PointerId);


			Pointer(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Pointer() = default;
			Pointer(const Pointer&) = default;
			Pointer& operator=(const Pointer&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Pointer(Pointer&&)                 = default;
			Pointer& operator=(Pointer&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Input::Pointer^ unwrapWindows_UI_Xaml_Input_Pointer() const;
			void wrap(::Windows::UI::Xaml::Input::Pointer^ object);

		private:
			::Windows::UI::Xaml::Input::Pointer^ unwrap() const;

		};

				} // namespace Input
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_INPUT_POINTER_HPP_
