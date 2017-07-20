/**
* View Helper for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#ifndef _TITANIUMWINDOWS_WINDOWS_VIEWHELPER_HPP_
#define _TITANIUMWINDOWS_WINDOWS_VIEWHELPER_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/UI/Font.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		namespace ViewHelper
		{
			using namespace HAL;

			//
			// Setup font from Titanium::UI::Font
			//
			template <typename T>
			void SetFont(const JSContext& js_context, T component, const Titanium::UI::Font& font);

			Windows::UI::Xaml::ResourceDictionary^ LookupXamlResource(Platform::String^ source = "ms-appx:///Styles.xaml");

		} // namespace ViewHelper
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_WINDOWS_VIEWHELPER_HPP_