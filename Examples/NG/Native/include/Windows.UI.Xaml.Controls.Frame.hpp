/**
 * Windows Native Wrapper for Windows.UI.Xaml.Controls.Frame
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_XAML_CONTROLS_FRAME_HPP_
#define _WINDOWS_UI_XAML_CONTROLS_FRAME_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Windows.UI.Xaml.Controls.ContentControl.hpp"

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

		class TITANIUMWINDOWS_NATIVE_EXPORT Frame : public ::Titanium::Windows::UI::Xaml::Controls::ContentControl, public JSExport<Frame>
		{

		public:
			TITANIUM_PROPERTY_DEF(SourcePageType);
			TITANIUM_PROPERTY_DEF(CacheSize);
			TITANIUM_PROPERTY_READONLY_DEF(BackStackDepth);
			TITANIUM_PROPERTY_READONLY_DEF(CanGoBack);
			TITANIUM_PROPERTY_READONLY_DEF(CanGoForward);
			TITANIUM_PROPERTY_READONLY_DEF(CurrentSourcePageType);
			TITANIUM_PROPERTY_READONLY_DEF(BackStack);
			TITANIUM_PROPERTY_READONLY_DEF(ForwardStack);
			TITANIUM_PROPERTY_READONLY_DEF(BackStackProperty);
			TITANIUM_PROPERTY_READONLY_DEF(ForwardStackProperty);
			TITANIUM_PROPERTY_READONLY_DEF(BackStackDepthProperty);
			TITANIUM_PROPERTY_READONLY_DEF(CacheSizeProperty);
			TITANIUM_PROPERTY_READONLY_DEF(CanGoBackProperty);
			TITANIUM_PROPERTY_READONLY_DEF(CanGoForwardProperty);
			TITANIUM_PROPERTY_READONLY_DEF(CurrentSourcePageTypeProperty);
			TITANIUM_PROPERTY_READONLY_DEF(SourcePageTypeProperty);

			TITANIUM_FUNCTION_DEF(GoBack);
			TITANIUM_FUNCTION_DEF(GoForward);
			TITANIUM_FUNCTION_DEF(Navigate);
			TITANIUM_FUNCTION_DEF(GetNavigationState);
			TITANIUM_FUNCTION_DEF(SetNavigationState);

			Frame(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Frame() = default;
			Frame(const Frame&) = default;
			Frame& operator=(const Frame&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Frame(Frame&&)                 = default;
			Frame& operator=(Frame&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Xaml::Controls::Frame^ unwrapWindows_UI_Xaml_Controls_Frame() const;
			void wrap(::Windows::UI::Xaml::Controls::Frame^ object);

		private:
			::Windows::UI::Xaml::Controls::Frame^ unwrap() const;

		};

				} // namespace Controls
			} // namespace Xaml
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_XAML_CONTROLS_FRAME_HPP_
