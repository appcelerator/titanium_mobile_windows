/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.ContentControl
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_CONTROLS_CONTENTCONTROL_HPP_
#define _WINDOWS_UI_XAML_CONTROLS_CONTENTCONTROL_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT ContentControl : public ::Titanium::Windows::UI::Xaml::Controls::Control, public JSExport<ContentControl>
		{

		public:
			TITANIUM_PROPERTY_DEF(ContentTransitions);
			TITANIUM_PROPERTY_DEF(ContentTemplateSelector);
			TITANIUM_PROPERTY_DEF(ContentTemplate);
			TITANIUM_PROPERTY_DEF(Content);
			TITANIUM_PROPERTY_READONLY_DEF(ContentTemplateRoot);
			TITANIUM_PROPERTY_READONLY_DEF(ContentProperty);
			TITANIUM_PROPERTY_READONLY_DEF(ContentTemplateProperty);
			TITANIUM_PROPERTY_READONLY_DEF(ContentTemplateSelectorProperty);
			TITANIUM_PROPERTY_READONLY_DEF(ContentTransitionsProperty);


			ContentControl(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ContentControl() = default;
			ContentControl(const ContentControl&) = default;
			ContentControl& operator=(const ContentControl&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ContentControl(ContentControl&&)                 = default;
			ContentControl& operator=(ContentControl&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Controls::ContentControl^ unwrapWindows_UI_Xaml_Controls_ContentControl() const;
			void wrap(::Windows::UI::Xaml::Controls::ContentControl^ object);

		private:
			::Windows::UI::Xaml::Controls::ContentControl^ unwrap() const;

		};

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_CONTROLS_CONTENTCONTROL_HPP_
