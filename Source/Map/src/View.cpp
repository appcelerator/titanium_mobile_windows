/**
 * Titanium.Map.View for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Map/View.hpp"
#include "TitaniumWindows/Utility.hpp"

using namespace Windows::Devices::Geolocation;

namespace TitaniumWindows
{
	namespace Map
	{
		View::View(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::Map::View(js_context, arguments),
			mapview__(ref new MapControl())
		{
			TITANIUM_LOG_DEBUG("View::ctor Initialize");
				
			// View loaded callback
			//mapview__->Loaded += ref new Windows::UI::Xaml::RoutedEventHandler([this](Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^e) {
			//	zoom(zoom__);
			//	set_region();
			//	set_mapType(mapType__);
			//});

			// Set service token
			// TODO : Load this from app properties, windows_map_service_token?
			mapview__->MapServiceToken = "VrSrmXR8B5bgklWrs0CK_w";

			// Layout engine
			TitaniumWindows::UI::ViewBase::setDefaultHeight(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
			TitaniumWindows::UI::ViewBase::setDefaultWidth(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
			TitaniumWindows::UI::ViewBase::setComponent(mapview__);
		}

		View::~View()
		{
			mapview__ = nullptr;
		}

		void View::JSExportInitialize() 
		{
			JSExport<View>::SetClassVersion(1);
			JSExport<View>::SetParent(JSExport<Titanium::UI::View>::Class());
		}

		uint32_t View::get_maxZoomLevel() const TITANIUM_NOEXCEPT
		{
			return static_cast<uint32_t>(mapview__->MaxZoomLevel); // should be 20
		}

		uint32_t View::get_minZoomLevel() const TITANIUM_NOEXCEPT
		{
			return static_cast<uint32_t>(mapview__->MinZoomLevel); // should be 1
		}

		void View::set_mapType(const Titanium::Map::MAP_TYPE& mapType) TITANIUM_NOEXCEPT
		{
			Titanium::Map::View::set_mapType(mapType);
			if (mapType__ == Titanium::Map::MAP_TYPE::HYBRID) {
				mapview__->Style = MapStyle::AerialWithRoads;
			} else if (mapType__ == Titanium::Map::MAP_TYPE::SATELLITE) {
				mapview__->Style = MapStyle::Aerial;
			} else if (mapType__ == Titanium::Map::MAP_TYPE::NORMAL) {
				mapview__->Style = MapStyle::Road;
			}
		}

		void View::set_region(const MapRegionType& region) TITANIUM_NOEXCEPT
		{
			Titanium::Map::View::set_region(region);
			BasicGeoposition location = {region.latitude, region.longitude};
			mapview__->Center = ref new Geopoint(location);
			zoom(region.zoom);

			// TODO : Add support for latitudeDelta and longitudeDelta.
			//        Just use zoomLevel for the time being
			//float dpi = Windows::Graphics::Display::DisplayProperties::LogicalDpi;
			//float scale = (dpi*39.37*156543.04*cos(region__.latitude)/(2^16));
		}

		void View::zoom(const uint32_t& zoom) TITANIUM_NOEXCEPT
		{
			mapview__->ZoomLevel = zoom;
		}

		void View::set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_bottom(bottom);
			TitaniumWindows::UI::ViewBase::setLayoutProperty(Titanium::LayoutEngine::ValueName::Bottom, bottom);
		}

		void View::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_height(height);
			TitaniumWindows::UI::ViewBase::setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, height);
		}

		void View::set_left(const std::string& left) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_left(left);
			TitaniumWindows::UI::ViewBase::setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, left);
		}

		void View::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_layout(layout);
			TitaniumWindows::UI::ViewBase::setLayout(layout);
		}

		void View::set_right(const std::string& right) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_right(right);
			TitaniumWindows::UI::ViewBase::setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, right);
		}

		void View::set_top(const std::string& top) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_top(top);
			TitaniumWindows::UI::ViewBase::setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, top);
		}

		void View::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_width(width);
			TitaniumWindows::UI::ViewBase::setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, width);
		}

	} // namespace Map
}  // namespace Titanium
