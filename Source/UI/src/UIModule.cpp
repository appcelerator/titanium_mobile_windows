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

	double UIModule::convertUnits(const std::string& convertFromValue, const Titanium::UI::UNIT& convertToUnits) TITANIUM_NOEXCEPT
	{
		if (convertFromValue.find("%") != std::string::npos) {		
			return 0;
		}

		static double RawPixelsPerViewPixel;
		static std::once_flag of;
		std::call_once(of, [=] {
			RawPixelsPerViewPixel = Windows::Graphics::Display::DisplayInformation::GetForCurrentView()->RawPixelsPerViewPixel;
		});

		Titanium::LayoutEngine::PhysicalPixelsFactor = RawPixelsPerViewPixel;

		const auto defaultUnit = TitaniumWindows::UI::WindowsViewLayoutDelegate::GetDefaultUnit(get_context());
		const auto ppi = TitaniumWindows::UI::WindowsViewLayoutDelegate::ComputePPI(Titanium::LayoutEngine::ValueName::Height);
		const auto value = Titanium::LayoutEngine::parseUnitValue(convertFromValue, Titanium::LayoutEngine::ValueType::Fixed, ppi, defaultUnit);

		if (convertToUnits == Titanium::UI::UNIT::Mm) {   // 1 mm = 0.0393701 in, 1 in = 25.4 mm
			return (value * 25.4) / ppi;                        // px = (mm / 25.4) * px/in
		} else if (convertToUnits == Titanium::UI::UNIT::Cm) {  // 1 cm = .393700787 in, 1 in = 2.54 cm
			return (value * 2.54) / ppi;                        // px = (cm / 2.54) * px/in
		} else if (convertToUnits == Titanium::UI::UNIT::In) {
			return value / ppi;  // px = inches * pixels/inch
		} else if (convertToUnits == Titanium::UI::UNIT::Px) {
			return value;  // px is our base value
		} else if (convertToUnits == Titanium::UI::UNIT::Dip) {
			return (value / ppi) * 160.0;  // px = device independent pixels * pixels/inch / 160, see https://www.google.com/design/spec/layout/units-measurements.html#units-measurements-designing-layouts-for-dp
		} else if (convertToUnits == Titanium::UI::UNIT::Ppx) {
			return value * RawPixelsPerViewPixel;
		}
		return value;
	}

}  // namespace TitaniumWindows
