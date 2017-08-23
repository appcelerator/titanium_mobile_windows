/**
* Windows.Style
*
* Copyright (c) 2017 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#ifndef _TITANIUMWINDOWS_WINDOWS_STYLE_HPP_
#define _TITANIUMWINDOWS_WINDOWS_STYLE_HPP_

#include "TitaniumWindows_UI_EXPORT.h"
#include "Titanium/Module.hpp"

namespace Titanium
{
	namespace UI
	{
		class View;
	}
}

namespace TitaniumWindows
{
	namespace UI
	{
		// Use WindowsXaml namespace instead of "Windows" because it screws entire namespace in UI...
		namespace WindowsXaml
		{
			using namespace HAL;

			/*!
			  @class

			  @discussion This is the Titanium.UI.Windows.Style implementation
			*/
			class TITANIUMWINDOWS_UI_EXPORT Style final : public Titanium::Module, public JSExport<Style>
			{

			public:
				Style(const JSContext&) TITANIUM_NOEXCEPT;

				virtual ~Style()                = default;
				Style(const Style&)            = default;
				Style& operator=(const Style&) = default;
	#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
				Style(Style&&)                 = default;
				Style& operator=(Style&&)      = default;
	#endif

				static void JSExportInitialize();

				virtual void apply(const std::shared_ptr<Titanium::UI::View>& view, const std::string& styleKey) TITANIUM_NOEXCEPT;

				TITANIUM_PROPERTY_DEF(source);
				TITANIUM_FUNCTION_DEF(apply);

				virtual void afterPropertiesSet() TITANIUM_NOEXCEPT override;

			private:

				Platform::String^ source__;

			};
		} // namespace WindowsXaml
	}  // namespace UI
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_WINDOWS_STYLE_HPP_