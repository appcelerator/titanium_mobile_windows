/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.UIElementCollection
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_CONTROLS_UIELEMENTCOLLECTION_HPP_
#define _WINDOWS_UI_XAML_CONTROLS_UIELEMENTCOLLECTION_HPP_

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
				namespace Controls
				{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT UIElementCollection : public ::Titanium::Platform::Object, public JSExport<UIElementCollection>
		{

		public:
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
			TITANIUM_FUNCTION_DEF(Move);

			UIElementCollection(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~UIElementCollection() = default;
			UIElementCollection(const UIElementCollection&) = default;
			UIElementCollection& operator=(const UIElementCollection&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			UIElementCollection(UIElementCollection&&)                 = default;
			UIElementCollection& operator=(UIElementCollection&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Controls::UIElementCollection^ unwrapWindows_UI_Xaml_Controls_UIElementCollection() const;
			void wrap(::Windows::UI::Xaml::Controls::UIElementCollection^ object);

		private:
			::Windows::UI::Xaml::Controls::UIElementCollection^ unwrap() const;

		};

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_CONTROLS_UIELEMENTCOLLECTION_HPP_
