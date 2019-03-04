/**
* Windows.Style
*
* Copyright (c) 2017 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "TitaniumWindows/UI/Windows/Style.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/UI/View.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/UI/Windows/ViewHelper.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		namespace WindowsXaml {

			using namespace ::Windows::UI::Xaml;
			using namespace ::Windows::UI::Xaml::Input;

			Style::Style(const JSContext& js_context) TITANIUM_NOEXCEPT
				: Titanium::Module(js_context, "Ti.UI.Windows.Style")
				, source__("ms-appx:///Styles.xaml")
			{
				TITANIUM_LOG_DEBUG("Style::ctor Initialize");
			}

			void Style::afterPropertiesSet() TITANIUM_NOEXCEPT
			{
				Titanium::Module::afterPropertiesSet();
			}

			void Style::JSExportInitialize()
			{
				JSExport<Style>::SetClassVersion(1);
				JSExport<Style>::SetParent(JSExport<Titanium::Module>::Class());
				TITANIUM_ADD_PROPERTY(Style, source);
				TITANIUM_ADD_FUNCTION(Style, apply);
			}

			TITANIUM_PROPERTY_GETTER(Style, source)
			{
				return get_context().CreateString(TitaniumWindows::Utility::ConvertUTF8String(source__));
			}

			TITANIUM_PROPERTY_SETTER(Style, source)
			{
				source__   = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(argument));
				return true;
			}

			TITANIUM_FUNCTION(Style, apply)
			{
				ENSURE_ARGUMENT_INDEX(0);
				ENSURE_OBJECT_AT_INDEX(target, 0);
				ENSURE_OPTIONAL_STRING_AT_INDEX(styleKey, 1, "");

				apply(target.GetPrivate<Titanium::UI::View>(), styleKey);

				return get_context().CreateUndefined();
			}

			void Style::apply(const std::shared_ptr<Titanium::UI::View>& view, const std::string& styleKey) TITANIUM_NOEXCEPT
			{
				const auto layout = view->getViewLayoutDelegate<WindowsViewLayoutDelegate>();
				if (layout) {
					const auto component = layout->getStyleComponent();
					const auto resources = TitaniumWindows::UI::ViewHelper::LookupXamlResource(source__);

					if (resources == nullptr) {
						detail::ThrowRuntimeError("Style::apply", "Unable to locate " + TitaniumWindows::Utility::ConvertUTF8String(source__));
					}

					component->Resources = resources;

					if (resources && !styleKey.empty()) {
						const auto key = TitaniumWindows::Utility::ConvertUTF8String(styleKey);
						if (resources->HasKey(key)) {
							const auto style = dynamic_cast<Windows::UI::Xaml::Style^>(resources->Lookup(key));
							if (style) {
								component->Style = style;
							} else {
								detail::ThrowRuntimeError("Style::apply", "Invalid Style object for " + styleKey);
							}
						} else {
							detail::ThrowRuntimeError("Style::apply", "Invalid Style object for " + styleKey);
						}
					}
				}
			}

		} // namespace WindowsXaml
	}  // namespace UI
}  // namespace TitaniumWindows
