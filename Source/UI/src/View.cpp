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
#include "Titanium/Blob.hpp"

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace Windows::UI::Xaml;

		std::unordered_map<std::string, std::string> View::CustomFonts__;

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

		// FIXME What file formats does windows support for fonts? We need to limit here! Most of what I read says only TTF, but I see some mentions of OpenType
		static const std::string ti_label_js = R"JS(
	this.exports = {};
	this.exports.getFontFilePath = function(fontFamily) {
		var iconsFolder = Ti.Filesystem.getFile(Ti.Filesystem.applicationDirectory, 'fonts');
		var files = iconsFolder.getDirectoryListing();
		for (var i = 0; i < files.length; i++) {
			var name = files[i];
			if (name.toLowerCase() == fontFamily.toLowerCase() || name.toLowerCase().indexOf(fontFamily.toLowerCase() + '.') == 0) {
				return name;
			}
		}
		return null;
	};
	)JS";

		Windows::UI::Xaml::Media::FontFamily^ View::LookupFont(const JSContext& js_context, const std::string& family)
		{
			auto path = family;
			// if we have a cached value, use it
			if (CustomFonts__.count(family) > 0) {
				path = CustomFonts__.at(family);
			}
			else {
				// new font
				// Look up to see if this is a custom font, or builtin
				auto export_object = js_context.CreateObject();
				js_context.JSEvaluateScript(ti_label_js, export_object);
				TITANIUM_ASSERT(export_object.HasProperty("exports"));
				auto exports = export_object.GetProperty("exports");
				TITANIUM_ASSERT(exports.IsObject());
				auto exports_object = static_cast<JSObject>(exports);
				auto eval_result = exports_object.GetProperty("getFontFilePath");
				TITANIUM_ASSERT(eval_result.IsObject());
				auto func = static_cast<JSObject>(eval_result);
				TITANIUM_ASSERT(func.IsFunction());
				auto result = func(family, js_context.get_global_object());
				if (result.IsNull()) { // we have no custom font by this name, assume it's a built-in font
					path = family;
				} else {
					TITANIUM_ASSERT(result.IsString()); // custom font file
					const auto file_name = static_cast<std::string>(result);
					path = "/fonts/" + file_name + "#" + family;
				}
				CustomFonts__.emplace(family, path);
			}
			
			return ref new Windows::UI::Xaml::Media::FontFamily(Utility::ConvertUTF8String(path));
		}

		Windows::UI::Xaml::FrameworkElement^ View::getComponent() TITANIUM_NOEXCEPT
		{
			return getViewLayoutDelegate<WindowsViewLayoutDelegate>()->getComponent();
		}
	} // namespace UI
} // namespace TitaniumWindows
