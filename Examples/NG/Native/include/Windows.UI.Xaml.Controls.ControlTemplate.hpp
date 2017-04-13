/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.ControlTemplate
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_CONTROLS_CONTROLTEMPLATE_HPP_
#define _WINDOWS_UI_XAML_CONTROLS_CONTROLTEMPLATE_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.FrameworkTemplate.hpp"

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

		class TITANIUMWINDOWS_NATIVE_EXPORT ControlTemplate : public ::Titanium::Windows::UI::Xaml::FrameworkTemplate, public JSExport<ControlTemplate>
		{

		public:
			TITANIUM_PROPERTY_DEF(TargetType);


			ControlTemplate(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ControlTemplate() = default;
			ControlTemplate(const ControlTemplate&) = default;
			ControlTemplate& operator=(const ControlTemplate&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ControlTemplate(ControlTemplate&&)                 = default;
			ControlTemplate& operator=(ControlTemplate&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Controls::ControlTemplate^ unwrapWindows_UI_Xaml_Controls_ControlTemplate() const;
			void wrap(::Windows::UI::Xaml::Controls::ControlTemplate^ object);

		private:
			::Windows::UI::Xaml::Controls::ControlTemplate^ unwrap() const;

		};

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_CONTROLS_CONTROLTEMPLATE_HPP_
