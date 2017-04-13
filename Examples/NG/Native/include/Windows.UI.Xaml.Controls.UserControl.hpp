/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.UserControl
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_CONTROLS_USERCONTROL_HPP_
#define _WINDOWS_UI_XAML_CONTROLS_USERCONTROL_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.Controls.Control.hpp"

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

		class TITANIUMWINDOWS_NATIVE_EXPORT UserControl : public ::Titanium::Windows::UI::Xaml::Controls::Control, public JSExport<UserControl>
		{

		public:
			TITANIUM_PROPERTY_DEF(Content);
			TITANIUM_PROPERTY_READONLY_DEF(ContentProperty);


			UserControl(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~UserControl() = default;
			UserControl(const UserControl&) = default;
			UserControl& operator=(const UserControl&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			UserControl(UserControl&&)                 = default;
			UserControl& operator=(UserControl&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Controls::UserControl^ unwrapWindows_UI_Xaml_Controls_UserControl() const;
			void wrap(::Windows::UI::Xaml::Controls::UserControl^ object);

		private:
			::Windows::UI::Xaml::Controls::UserControl^ unwrap() const;

		};

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_CONTROLS_USERCONTROL_HPP_
