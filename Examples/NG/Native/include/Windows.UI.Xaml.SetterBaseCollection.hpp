/**
 * Windows Native Wrapper for Windows.UI.Xaml.SetterBaseCollection
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_SETTERBASECOLLECTION_HPP_
#define _WINDOWS_UI_XAML_SETTERBASECOLLECTION_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT SetterBaseCollection : public ::Titanium::Platform::Object, public JSExport<SetterBaseCollection>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(IsSealed);
			TITANIUM_PROPERTY_READONLY_DEF(Size);

			TITANIUM_FUNCTION_DEF(GetAt);
			TITANIUM_FUNCTION_DEF(GetView);
			TITANIUM_FUNCTION_DEF(IndexOf);
			TITANIUM_FUNCTION_DEF(SetAt);
			TITANIUM_FUNCTION_DEF(InsertAt);
			TITANIUM_FUNCTION_DEF(RemoveAt);
			TITANIUM_FUNCTION_DEF(Append);
			TITANIUM_FUNCTION_DEF(RemoveAtEnd);
			TITANIUM_FUNCTION_DEF(Clear);
			TITANIUM_FUNCTION_DEF(GetMany);
			TITANIUM_FUNCTION_DEF(ReplaceAll);
			TITANIUM_FUNCTION_DEF(First);

			SetterBaseCollection(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~SetterBaseCollection() = default;
			SetterBaseCollection(const SetterBaseCollection&) = default;
			SetterBaseCollection& operator=(const SetterBaseCollection&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			SetterBaseCollection(SetterBaseCollection&&)                 = default;
			SetterBaseCollection& operator=(SetterBaseCollection&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::SetterBaseCollection^ unwrapWindows_UI_Xaml_SetterBaseCollection() const;
			void wrap(::Windows::UI::Xaml::SetterBaseCollection^ object);

		private:
			::Windows::UI::Xaml::SetterBaseCollection^ unwrap() const;

		};

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_SETTERBASECOLLECTION_HPP_
