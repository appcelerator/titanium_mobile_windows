/**
 * Titanium.UI.View for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/View.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/FilesystemModule.hpp"
#include "Titanium/Filesystem/File.hpp"

#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/case_conv.hpp>

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::UI::Xaml;

		std::vector<std::string> View::fontFiles__;
		std::unordered_map<std::string, std::string> View::fonts__;

		View::View(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::UI::View(js_context)
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::UI::View::ctor ", this);
		}

		View::~View() 
		{
			TITANIUM_LOG_DEBUG("TitaniumWindows::UI::View::dtor ", this);
		}

		void View::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
		{
			Titanium::UI::View::postCallAsConstructor(js_context, arguments);	
			
			canvas__ = ref new Windows::UI::Xaml::Controls::Canvas();

			Titanium::UI::View::setLayoutDelegate<WindowsViewLayoutDelegate>();

			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_autoLayoutForWidth(Titanium::UI::LAYOUT::FILL);

			getViewLayoutDelegate<WindowsViewLayoutDelegate>()->setComponent(canvas__);
		}

		void View::JSExportInitialize()
		{
			JSExport<View>::SetClassVersion(1);
			JSExport<View>::SetParent(JSExport<Titanium::UI::View>::Class());
		}

		Windows::UI::Xaml::Media::FontFamily^ View::LookupFont(const JSContext& js_context, const std::string& family)
		{
			auto path = family;

			// if we have a cached value, use it
			if (fonts__.count(family) > 0) {
				path = fonts__.at(family);
			} else {

				// load fonts
				if (fontFiles__.size() == 0) {
					const auto titanium_js = js_context.get_global_object().GetProperty("Titanium");
					TITANIUM_ASSERT(titanium_js.IsObject());
					const auto titanium_obj = static_cast<JSObject>(titanium_js);

					const auto filesystem_js = titanium_obj.GetProperty("Filesystem");
					TITANIUM_ASSERT(filesystem_js.IsObject());
					const auto filesystem_obj = static_cast<JSObject>(filesystem_js);
					const auto filesystem = filesystem_obj.GetPrivate<Titanium::FilesystemModule>();

					const auto fontsDirectory = filesystem->getFile(js_context, filesystem->applicationDirectory() + "/fonts");
					fontFiles__ = fontsDirectory->getDirectoryListing();

					// filter fonts, currently only True Type Fonts
					fontFiles__.erase(std::remove_if(fontFiles__.begin(), fontFiles__.end(), [](std::string file) {
						return !boost::ends_with(file, ".ttf");
					}), fontFiles__.end());
				}

				// font file and family specified
				if (boost::contains(family, "#")) {
					path = "/fonts/" + family;

				// font name same as font file
				} else {
					auto family_lower = family;
					boost::to_lower(family_lower);
					for (auto file : fontFiles__) {
						boost::to_lower(file);
						if (boost::starts_with(file, family_lower)) {
							path = "/fonts/" + file + "#" + family;
							break;
						}
					}
				}

				fonts__.emplace(family, path);
			}
			
			return ref new Windows::UI::Xaml::Media::FontFamily(Utility::ConvertUTF8String(path));
		}

		Windows::UI::Xaml::FrameworkElement^ View::getComponent() TITANIUM_NOEXCEPT
		{
			return getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
		}
	} // namespace UI
} // namespace TitaniumWindows
