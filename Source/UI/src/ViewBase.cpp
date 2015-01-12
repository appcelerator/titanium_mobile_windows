/**
* Titanium.UI.View for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#include "TitaniumWindows/UI/ViewBase.hpp"
#include <collection.h>
#include <algorithm>
#include <cctype>


namespace TitaniumWindows { namespace UI {

	ViewBase::ViewBase()
	{
		defaultWidth__ = Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE);
		defaultHeight__ = Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE);
	}

	static void onLayoutCallback(Titanium::LayoutEngine::Node* node)
	{
		auto view = static_cast<ViewBase*>(node->data);
		auto rect = Titanium::LayoutEngine::RectMake(node->element.measuredLeft, node->element.measuredTop, node->element.measuredWidth, node->element.measuredHeight);
		view->onLayoutEngineCallback(rect, node->name);
	}

	void ViewBase::setComponent(Windows::UI::Xaml::FrameworkElement^ component)
	{
		using namespace Windows::UI::Xaml;
		using namespace Windows::UI::Xaml::Controls;

		TITANIUM_ASSERT(component_ == nullptr);

		component_ = component;
		is_panel_ = dynamic_cast<Windows::UI::Xaml::Controls::Panel^>(component_) != nullptr;
		is_control_ = dynamic_cast<Windows::UI::Xaml::Controls::Control^>(component_) != nullptr;

		loaded_event_ = component_->Loaded += ref new RoutedEventHandler([this](Platform::Object ^sender, RoutedEventArgs ^e){
			auto component = getComponent();
			auto rect = Titanium::LayoutEngine::RectMake(
				Canvas::GetLeft(component),
				Canvas::GetTop(component),
				component->ActualWidth,
				component->ActualHeight
				);

			onComponentLoaded(rect);
		});

		size_change_event_ = component_->SizeChanged += ref new Windows::UI::Xaml::SizeChangedEventHandler([this](Platform::Object ^sender, SizeChangedEventArgs ^e){
			auto component = getComponent();
			auto rect = Titanium::LayoutEngine::RectMake(
				Canvas::GetLeft(component),
				Canvas::GetTop(component),
				e->NewSize.Width,
				e->NewSize.Height
				);

			onComponentSizeChange(rect);
		});

		layout_node_ = new Titanium::LayoutEngine::Node;
		layout_node_->data = this;
		layout_node_->onLayout = onLayoutCallback;

		if (defaultWidth() == Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE)) {
			is_width_size_ = true;
			layout_node_->properties.defaultWidthType = Titanium::LayoutEngine::ValueType::Size;
		}
		else if (defaultWidth() == Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL)) {
			layout_node_->properties.defaultWidthType = Titanium::LayoutEngine::ValueType::Fill;
		}

		if (defaultHeight() == Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE)) {
			is_height_size_ = true;
			layout_node_->properties.defaultHeightType = Titanium::LayoutEngine::ValueType::Size;
		}
		else if (defaultHeight() == Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL)) {
			layout_node_->properties.defaultHeightType = Titanium::LayoutEngine::ValueType::Fill;
		}
	}

	void ViewBase::onLayoutEngineCallback(Titanium::LayoutEngine::Rect rect, const std::string& name)
	{
		using namespace Windows::UI::Xaml::Controls;
		using namespace Windows::UI::Xaml;
		if (is_height_size_ && rect.height == 0) return;
		if (is_width_size_ && rect.width == 0) return;
		if (rect.width < 0 || rect.height < 0) return;
		if (Titanium::LayoutEngine::RectIsEmpty(rect)) return;
		if (Titanium::LayoutEngine::RectIsEqualToRect(oldRect, rect)) return;

		auto component = getComponent();
		auto panel = is_panel_ ? safe_cast<Panel^>(component) : nullptr;
		auto parentLayout = layout_node_->parent;

		auto setWidth = false;
		auto setHeight = false;
		auto setWidthOnWidget = !is_width_size_;
		auto setHeightOnWidget = !is_height_size_;

		if (!is_panel_ && is_width_size_ && parentLayout != nullptr) {
			if (rect.width > parentLayout->element.measuredWidth && parentLayout->element.measuredWidth > 0) {
				rect.width = parentLayout->element.measuredWidth;
				setWidthOnWidget = true;
			}
		}

		if (!is_panel_ && is_height_size_ && parentLayout != nullptr) {
			if (rect.height > parentLayout->element.measuredHeight && parentLayout->element.measuredHeight > 0) {
				rect.height = parentLayout->element.measuredHeight;
				setHeightOnWidget = true;
			}
		}

		oldRect = Titanium::LayoutEngine::RectMake(rect.x, rect.y, rect.width, rect.height);

		if (is_panel_) {
			for (auto child : panel->Children) {
				child->Visibility = Visibility::Collapsed;
			}

			setWidth = true;
			setHeight = true;
		}

		if ((!is_panel_ && setWidthOnWidget) || setWidth) {
			component->Width = rect.width;
		}

		if ((!is_panel_ && setHeightOnWidget) || setHeight) {
			component->Height = rect.height;
		}

		Canvas::SetLeft(component, rect.x);
		Canvas::SetTop(component, rect.y);

		if (is_panel_) {
			for (auto child : panel->Children) {
				child->Visibility = Visibility::Visible;
			}
		}
	}

	void ViewBase::onComponentLoaded(const Titanium::LayoutEngine::Rect& rect)
	{
		is_loaded_ = true;

		auto root = Titanium::LayoutEngine::nodeRequestLayout(layout_node_);

		if (root) {
			Titanium::LayoutEngine::nodeLayout(root);
		}
	}

	void ViewBase::onComponentSizeChange(const Titanium::LayoutEngine::Rect& rect)
	{
		bool needsLayout = false;

		if (is_width_size_ && !is_panel_) {
			layout_node_->properties.width.value = rect.width;
			layout_node_->properties.width.valueType = Titanium::LayoutEngine::Fixed;
			needsLayout = isLoaded();
		}

		if (is_height_size_ && !is_panel_) {
			layout_node_->properties.height.value = rect.height;
			layout_node_->properties.height.valueType = Titanium::LayoutEngine::Fixed;
			needsLayout = isLoaded();
		}

		if (needsLayout) {
			auto root = Titanium::LayoutEngine::nodeRequestLayout(layout_node_);
			if (root) {
				Titanium::LayoutEngine::nodeLayout(root);
			}
		}

		/* TODO fire post layout callback
			if (post_layout_event_count_ > 0) {
			Ti::Value val;
			val.setProperty("x", Ti::Value(rect.x));
			val.setProperty("y", Ti::Value(rect.y));
			val.setProperty("width", Ti::Value(rect.width));
			val.setProperty("height", Ti::Value(rect.height));
			fireEvent(Ti::Constants::EventPostLayout, val);
			}
			*/
	}

	void ViewBase::setLayoutProperty(const Titanium::LayoutEngine::ValueName& name, const std::string& value)
	{
		Titanium::LayoutEngine::InputProperty prop;
		prop.name = name;
		prop.value = value;

		if (prop.value == Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::SIZE)) {
			prop.value = "UI.SIZE";
		}
		else if (prop.value == Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL)) {
			prop.value = "UI.FILL";
		}

		Titanium::LayoutEngine::populateLayoutPoperties(prop, &layout_node_->properties, 1);

		if (isLoaded()) {
			auto root = Titanium::LayoutEngine::nodeRequestLayout(layout_node_);
			if (root) {
				Titanium::LayoutEngine::nodeLayout(root);
			}
		}
	}

	void ViewBase::setLayout(const std::string& type)
	{
		if (type == "horizontal") {
			layout_node_->element.layoutType = Titanium::LayoutEngine::LayoutType::Horizontal;
		}
		else if (type == "vertical") {
			layout_node_->element.layoutType = Titanium::LayoutEngine::LayoutType::Vertical;
		}
		else {
			layout_node_->element.layoutType = Titanium::LayoutEngine::LayoutType::Composite;
		}

		if (isLoaded()) {
			auto root = Titanium::LayoutEngine::nodeRequestLayout(layout_node_);
			if (root) {
				Titanium::LayoutEngine::nodeLayout(root);
			}
		}
	}

	Windows::UI::Xaml::FrameworkElement ^ ViewBase::get_UIElement()  const TITANIUM_NOEXCEPT{
		TITANIUM_LOG_DEBUG("View::get_UIElement:");
		return dynamic_cast<Windows::UI::Xaml::FrameworkElement^>(component_);
	}


		/////////// Color //////////////

		inline
		bool isASCIIHexDigit(char c) {
		return (c >= '0' && c <= '9') || ((c | 0x20) >= 'a' && (c | 0x20) <= 'f');
	}

	inline
		int toASCIIHexValue(char c) {
		return (c & 0xF) + (c < 'A' ? 0 : 9);
	}

	Windows::UI::Color ViewBase::ColorForHexCode(const std::string& hexCode) {
		unsigned length = hexCode.size();
		char alpha = 255;
		if ((length != 3) && (length != 4) && (length != 6) && (length != 7) && (length != 8)) {
			TITANIUM_LOG_WARN("View::ColorForHexCode: invalid hexCode = ", hexCode);
			return Windows::UI::Colors::Transparent;
		}
		unsigned value = 0;

		for (size_t i = 0; i < length; ++i) {
			unsigned char thisChar = hexCode[i];
			if (thisChar == '#') continue;
			if (!isASCIIHexDigit(thisChar)) {
				return Windows::UI::Colors::Transparent;
			}
			value <<= 4;
			value |= toASCIIHexValue(thisChar);
		}

		if (length < 6) {
			value = ((value & 0xF000) << 16) |
				((value & 0xFF00) << 12) |
				((value & 0xFF0) << 8) |
				((value & 0xFF) << 4) |
				(value & 0xF);
		}

		if ((length % 4) == 0) {
			alpha = ((value >> 24) & 0xFF) * 255;
		}

		int red = (value >> 16) & 0xFF;
		int green = (value >> 8) & 0xFF;
		int blue = value & 0xFF;
		return Windows::UI::ColorHelper::FromArgb(alpha, red, green, blue);
	}

#if defined(INSERT_WINDOWS_UI_COLOR)
#error "LOGIC ERROR: INSERT_WINDOWS_UI_COLOR already defined."
#endif

	inline
		std::string toLowerCase(const std::string& string) {
		std::string copy(string);
		std::transform(string.begin(), string.end(), copy.begin(), std::tolower);
		return copy;
	}

#define INSERT_WINDOWS_UI_COLOR(COLOR_NAME) color_name_map.insert(std::make_pair(toLowerCase(#COLOR_NAME), Windows::UI::Colors::##COLOR_NAME));

	// Can this be optimized? MS is giving a lot of choices for colors!
	Windows::UI::Color ViewBase::ColorForName(const std::string& colorName) {
		// pre condition
		TITANIUM_ASSERT(!colorName.empty());

		static const Windows::UI::Color defaultColor = Windows::UI::Colors::Transparent;
		using ColorNameMap_t = std::unordered_map < std::string, Windows::UI::Color > ;
		static ColorNameMap_t color_name_map;
		static std::once_flag of;
		std::call_once(of, [] {
			INSERT_WINDOWS_UI_COLOR(AliceBlue);
			INSERT_WINDOWS_UI_COLOR(AntiqueWhite);
			INSERT_WINDOWS_UI_COLOR(Aqua);
			INSERT_WINDOWS_UI_COLOR(Aquamarine);
			INSERT_WINDOWS_UI_COLOR(Azure);
			INSERT_WINDOWS_UI_COLOR(Beige);
			INSERT_WINDOWS_UI_COLOR(Bisque);
			INSERT_WINDOWS_UI_COLOR(Black);
			INSERT_WINDOWS_UI_COLOR(BlanchedAlmond);
			INSERT_WINDOWS_UI_COLOR(Blue);
			INSERT_WINDOWS_UI_COLOR(BlueViolet);
			INSERT_WINDOWS_UI_COLOR(Brown);
			INSERT_WINDOWS_UI_COLOR(BurlyWood);
			INSERT_WINDOWS_UI_COLOR(CadetBlue);
			INSERT_WINDOWS_UI_COLOR(Chartreuse);
			INSERT_WINDOWS_UI_COLOR(Chocolate);
			INSERT_WINDOWS_UI_COLOR(Coral);
			INSERT_WINDOWS_UI_COLOR(CornflowerBlue);
			INSERT_WINDOWS_UI_COLOR(Cornsilk);
			INSERT_WINDOWS_UI_COLOR(Crimson);
			INSERT_WINDOWS_UI_COLOR(Cyan);
			INSERT_WINDOWS_UI_COLOR(DarkBlue);
			INSERT_WINDOWS_UI_COLOR(DarkCyan);
			INSERT_WINDOWS_UI_COLOR(DarkGoldenrod);
			INSERT_WINDOWS_UI_COLOR(DarkGray);
			INSERT_WINDOWS_UI_COLOR(DarkGreen);
			INSERT_WINDOWS_UI_COLOR(DarkKhaki);
			INSERT_WINDOWS_UI_COLOR(DarkMagenta);
			INSERT_WINDOWS_UI_COLOR(DarkOliveGreen);
			INSERT_WINDOWS_UI_COLOR(DarkOrange);
			INSERT_WINDOWS_UI_COLOR(DarkOrchid);
			INSERT_WINDOWS_UI_COLOR(DarkRed);
			INSERT_WINDOWS_UI_COLOR(DarkSalmon);
			INSERT_WINDOWS_UI_COLOR(DarkSeaGreen);
			INSERT_WINDOWS_UI_COLOR(DarkSlateBlue);
			INSERT_WINDOWS_UI_COLOR(DarkSlateGray);
			INSERT_WINDOWS_UI_COLOR(DarkTurquoise);
			INSERT_WINDOWS_UI_COLOR(DarkViolet);
			INSERT_WINDOWS_UI_COLOR(DeepPink);
			INSERT_WINDOWS_UI_COLOR(DeepSkyBlue);
			INSERT_WINDOWS_UI_COLOR(DimGray);
			INSERT_WINDOWS_UI_COLOR(DodgerBlue);
			INSERT_WINDOWS_UI_COLOR(Firebrick);
			INSERT_WINDOWS_UI_COLOR(FloralWhite);
			INSERT_WINDOWS_UI_COLOR(ForestGreen);
			INSERT_WINDOWS_UI_COLOR(Fuchsia);
			INSERT_WINDOWS_UI_COLOR(Gainsboro);
			INSERT_WINDOWS_UI_COLOR(GhostWhite);
			INSERT_WINDOWS_UI_COLOR(Gold);
			INSERT_WINDOWS_UI_COLOR(Goldenrod);
			INSERT_WINDOWS_UI_COLOR(Gray);
			INSERT_WINDOWS_UI_COLOR(Green);
			INSERT_WINDOWS_UI_COLOR(GreenYellow);
			INSERT_WINDOWS_UI_COLOR(Honeydew);
			INSERT_WINDOWS_UI_COLOR(HotPink);
			INSERT_WINDOWS_UI_COLOR(IndianRed);
			INSERT_WINDOWS_UI_COLOR(Indigo);
			INSERT_WINDOWS_UI_COLOR(Ivory);
			INSERT_WINDOWS_UI_COLOR(Khaki);
			INSERT_WINDOWS_UI_COLOR(Lavender);
			INSERT_WINDOWS_UI_COLOR(LavenderBlush);
			INSERT_WINDOWS_UI_COLOR(LawnGreen);
			INSERT_WINDOWS_UI_COLOR(LemonChiffon);
			INSERT_WINDOWS_UI_COLOR(LightBlue);
			INSERT_WINDOWS_UI_COLOR(LightCoral);
			INSERT_WINDOWS_UI_COLOR(LightCyan);
			INSERT_WINDOWS_UI_COLOR(LightGoldenrodYellow);
			INSERT_WINDOWS_UI_COLOR(LightGray);
			INSERT_WINDOWS_UI_COLOR(LightGreen);
			INSERT_WINDOWS_UI_COLOR(LightPink);
			INSERT_WINDOWS_UI_COLOR(LightSalmon);
			INSERT_WINDOWS_UI_COLOR(LightSeaGreen);
			INSERT_WINDOWS_UI_COLOR(LightSkyBlue);
			INSERT_WINDOWS_UI_COLOR(LightSlateGray);
			INSERT_WINDOWS_UI_COLOR(LightSteelBlue);
			INSERT_WINDOWS_UI_COLOR(LightYellow);
			INSERT_WINDOWS_UI_COLOR(Lime);
			INSERT_WINDOWS_UI_COLOR(LimeGreen);
			INSERT_WINDOWS_UI_COLOR(Linen);
			INSERT_WINDOWS_UI_COLOR(Magenta);
			INSERT_WINDOWS_UI_COLOR(Maroon);
			INSERT_WINDOWS_UI_COLOR(MediumAquamarine);
			INSERT_WINDOWS_UI_COLOR(MediumBlue);
			INSERT_WINDOWS_UI_COLOR(MediumOrchid);
			INSERT_WINDOWS_UI_COLOR(MediumPurple);
			INSERT_WINDOWS_UI_COLOR(MediumSeaGreen);
			INSERT_WINDOWS_UI_COLOR(MediumSlateBlue);
			INSERT_WINDOWS_UI_COLOR(MediumSpringGreen);
			INSERT_WINDOWS_UI_COLOR(MediumTurquoise);
			INSERT_WINDOWS_UI_COLOR(MediumVioletRed);
			INSERT_WINDOWS_UI_COLOR(MidnightBlue);
			INSERT_WINDOWS_UI_COLOR(MintCream);
			INSERT_WINDOWS_UI_COLOR(MistyRose);
			INSERT_WINDOWS_UI_COLOR(Moccasin);
			INSERT_WINDOWS_UI_COLOR(NavajoWhite);
			INSERT_WINDOWS_UI_COLOR(Navy);
			INSERT_WINDOWS_UI_COLOR(OldLace);
			INSERT_WINDOWS_UI_COLOR(Olive);
			INSERT_WINDOWS_UI_COLOR(OliveDrab);
			INSERT_WINDOWS_UI_COLOR(Orange);
			INSERT_WINDOWS_UI_COLOR(OrangeRed);
			INSERT_WINDOWS_UI_COLOR(Orchid);
			INSERT_WINDOWS_UI_COLOR(PaleGoldenrod);
			INSERT_WINDOWS_UI_COLOR(PaleGreen);
			INSERT_WINDOWS_UI_COLOR(PaleTurquoise);
			INSERT_WINDOWS_UI_COLOR(PaleVioletRed);
			INSERT_WINDOWS_UI_COLOR(PapayaWhip);
			INSERT_WINDOWS_UI_COLOR(PeachPuff);
			INSERT_WINDOWS_UI_COLOR(Peru);
			INSERT_WINDOWS_UI_COLOR(Pink);
			INSERT_WINDOWS_UI_COLOR(Plum);
			INSERT_WINDOWS_UI_COLOR(PowderBlue);
			INSERT_WINDOWS_UI_COLOR(Purple);
			INSERT_WINDOWS_UI_COLOR(Red);
			INSERT_WINDOWS_UI_COLOR(RosyBrown);
			INSERT_WINDOWS_UI_COLOR(RoyalBlue);
			INSERT_WINDOWS_UI_COLOR(SaddleBrown);
			INSERT_WINDOWS_UI_COLOR(Salmon);
			INSERT_WINDOWS_UI_COLOR(SandyBrown);
			INSERT_WINDOWS_UI_COLOR(SeaGreen);
			INSERT_WINDOWS_UI_COLOR(SeaShell);
			INSERT_WINDOWS_UI_COLOR(Sienna);
			INSERT_WINDOWS_UI_COLOR(Silver);
			INSERT_WINDOWS_UI_COLOR(SkyBlue);
			INSERT_WINDOWS_UI_COLOR(SlateBlue);
			INSERT_WINDOWS_UI_COLOR(SlateGray);
			INSERT_WINDOWS_UI_COLOR(Snow);
			INSERT_WINDOWS_UI_COLOR(SpringGreen);
			INSERT_WINDOWS_UI_COLOR(SteelBlue);
			INSERT_WINDOWS_UI_COLOR(Tan);
			INSERT_WINDOWS_UI_COLOR(Teal);
			INSERT_WINDOWS_UI_COLOR(Thistle);
			INSERT_WINDOWS_UI_COLOR(Tomato);
			INSERT_WINDOWS_UI_COLOR(Transparent);
			INSERT_WINDOWS_UI_COLOR(Turquoise);
			INSERT_WINDOWS_UI_COLOR(Violet);
			INSERT_WINDOWS_UI_COLOR(Wheat);
			INSERT_WINDOWS_UI_COLOR(White);
			INSERT_WINDOWS_UI_COLOR(WhiteSmoke);
			INSERT_WINDOWS_UI_COLOR(Yellow);
			INSERT_WINDOWS_UI_COLOR(YellowGreen);
		});

		if (colorName[0] == '#') {
			return ColorForHexCode(colorName.substr(1));
		}

		auto position = color_name_map.find(toLowerCase(colorName));

		Windows::UI::Color color = defaultColor;
		if (position != color_name_map.end()) {
			color = position->second;
		}

		return color;
	}

}}  // namespace TitaniumWindows { namespace UI {


