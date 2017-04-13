/**
 * Windows Native Wrapper for Windows.UI.Xaml.DependencyPropertyChangedEventArgs
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_DEPENDENCYPROPERTYCHANGEDEVENTARGS_HPP_
#define _WINDOWS_UI_XAML_DEPENDENCYPROPERTYCHANGEDEVENTARGS_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT DependencyPropertyChangedEventArgs : public ::Titanium::Platform::Object, public JSExport<DependencyPropertyChangedEventArgs>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(NewValue);
			TITANIUM_PROPERTY_READONLY_DEF(OldValue);
			TITANIUM_PROPERTY_READONLY_DEF(Property);


			DependencyPropertyChangedEventArgs(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~DependencyPropertyChangedEventArgs() = default;
			DependencyPropertyChangedEventArgs(const DependencyPropertyChangedEventArgs&) = default;
			DependencyPropertyChangedEventArgs& operator=(const DependencyPropertyChangedEventArgs&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			DependencyPropertyChangedEventArgs(DependencyPropertyChangedEventArgs&&)                 = default;
			DependencyPropertyChangedEventArgs& operator=(DependencyPropertyChangedEventArgs&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ unwrapWindows_UI_Xaml_DependencyPropertyChangedEventArgs() const;
			void wrap(::Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ object);

		private:
			::Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ unwrap() const;

		};

			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_DEPENDENCYPROPERTYCHANGEDEVENTARGS_HPP_
