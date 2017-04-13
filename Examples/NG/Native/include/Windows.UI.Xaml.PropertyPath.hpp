/**
 * Windows Native Wrapper for Windows.UI.Xaml.PropertyPath
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_PROPERTYPATH_HPP_
#define _WINDOWS_UI_XAML_PROPERTYPATH_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT PropertyPath : public ::Titanium::Windows::UI::Xaml::DependencyObject, public JSExport<PropertyPath>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(Path);


			PropertyPath(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~PropertyPath() = default;
			PropertyPath(const PropertyPath&) = default;
			PropertyPath& operator=(const PropertyPath&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			PropertyPath(PropertyPath&&)                 = default;
			PropertyPath& operator=(PropertyPath&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::PropertyPath^ unwrapWindows_UI_Xaml_PropertyPath() const;
			void wrap(::Windows::UI::Xaml::PropertyPath^ object);

		private:
			::Windows::UI::Xaml::PropertyPath^ unwrap() const;

		};

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_PROPERTYPATH_HPP_
