/**
* Titanium.UI for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/UIModule.hpp"
#include "TitaniumWindows/UI/WindowsModule.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"

namespace TitaniumWindows
{

	using namespace TitaniumWindows::UI;

	UIModule::UIModule(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::UIModule(js_context)
	{
	}

	UIModule::~UIModule() TITANIUM_NOEXCEPT
	{
	}

	void UIModule::JSExportInitialize() 
	{
		JSExport<UIModule>::SetClassVersion(1);
		JSExport<UIModule>::SetParent(JSExport<Titanium::UIModule>::Class());
		TITANIUM_ADD_CONSTANT_PROPERTY(UIModule, Windows);
	}

	TITANIUM_PROPERTY_GETTER(UIModule, Windows)
	{
		return get_context().CreateObject(JSExport<TitaniumWindows::WindowsModule>::Class());
	}

	void UIModule::set_backgroundColor(const std::string& color) TITANIUM_NOEXCEPT
	{
		Titanium::UIModule::set_backgroundColor(color);
		auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
		if (rootFrame != nullptr) {
			rootFrame->Background = ref new Windows::UI::Xaml::Media::SolidColorBrush(WindowsViewLayoutDelegate::ColorForName(color));
		}
	}

}  // namespace TitaniumWindows
