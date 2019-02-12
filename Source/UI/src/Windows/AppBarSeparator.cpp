/**
* Windows.AppBarSeparator
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/UI/Windows/AppBarSeparator.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		namespace WindowsXaml {

			using namespace ::Windows::UI::Xaml;

			AppBarSeparator::AppBarSeparator(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Titanium::Module(js_context, "Ti.UI.Windows.AppBarSeparator")
			{
				TITANIUM_LOG_DEBUG("AppBarSeparator::ctor Initialize");
			}

			void AppBarSeparator::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
			{
				TITANIUM_LOG_DEBUG("AppBarSeparator::postCallAsConstructor");
				Titanium::Module::postCallAsConstructor(js_context, arguments);

				separator__ = ref new Controls::AppBarSeparator();
			}

			void AppBarSeparator::JSExportInitialize()
			{
				JSExport<AppBarSeparator>::SetClassVersion(1);
				JSExport<AppBarSeparator>::SetParent(JSExport<Titanium::Module>::Class());
			}

		} // namespace WindowsXaml
	}  // namespace UI
}  // namespace TitaniumWindows
