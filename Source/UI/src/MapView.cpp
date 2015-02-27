/**
 * Titanium.UI.MapView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/MapView.hpp"
#include "Titanium/MapModule.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"

using namespace Windows::Devices::Geolocation;

namespace TitaniumWindows
{
	namespace UI
	{
		MapView::MapView(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::UI::MapView(js_context, arguments),
			mapview__(ref new MapControl())
		{
			TITANIUM_LOG_DEBUG("MapView::ctor Initialize");

			// Load initial arguments
			if (arguments.size() >= 1 && arguments[0].IsObject()) {
				auto arg = static_cast<JSObject>(arguments[0]);
				if (arg.HasProperty("mapType")) {
					auto prop = arg.GetProperty("mapType");
					TITANIUM_ASSERT(prop.IsNumber());
					mapType__ = Titanium::Map::Constants::to_MAP_TYPE(static_cast<std::underlying_type<Titanium::Map::MAP_TYPE>::type>(prop));
				}
				if (arg.HasProperty("region")) {
					auto prop = arg.GetProperty("region");
					TITANIUM_ASSERT(prop.IsObject());
					region__ = getMapRegionType(static_cast<JSObject>(prop));
				}
				if (arg.HasProperty("zoom")) {
					auto prop = arg.GetProperty("zoom");
					TITANIUM_ASSERT(prop.IsNumber());
					zoom__ = static_cast<uint32_t>(prop);
				}
			}
				
			// MapView loaded callback
			mapview__->Loaded += ref new Windows::UI::Xaml::RoutedEventHandler([this](Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^e) {
				setZoom(zoom__);
				setRegion();
				setMapType(mapType__);
			});

			// Set service token
			// TODO : Load this from app properties, windows_map_service_token?
			mapview__->MapServiceToken = "VrSrmXR8B5bgklWrs0CK_w";

			// Layout engine
			setDefaultHeight(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
			setDefaultWidth(Titanium::UI::Constants::to_string(Titanium::UI::LAYOUT::FILL));
			setComponent(mapview__);
		}

		MapView::~MapView()
		{
			mapview__ = nullptr;
		}

		void MapView::JSExportInitialize() 
		{
			JSExport<MapView>::SetClassVersion(1);
			JSExport<MapView>::SetParent(JSExport<Titanium::UI::MapView>::Class());
		}

		void MapView::setMapType(Titanium::Map::MAP_TYPE mapType) TITANIUM_NOEXCEPT {
			Titanium::UI::MapView::setMapType(mapType);
			if (mapType__ == Titanium::Map::MAP_TYPE::HYBRID) {
				mapview__->Style = MapStyle::AerialWithRoads;
			} else if (mapType__ == Titanium::Map::MAP_TYPE::SATELLITE) {
				mapview__->Style = MapStyle::Aerial;
			} else if (mapType__ == Titanium::Map::MAP_TYPE::NORMAL) {
				mapview__->Style = MapStyle::Road;
			}
		}

		void MapView::setRegion(JSObject& region) TITANIUM_NOEXCEPT {
			Titanium::UI::MapView::setRegion(region);
			BasicGeoposition location = {region__.latitude, region__.longitude};
			mapview__->Center = ref new Geopoint(location);

			// TODO : Add support for latitudeDelta and longitudeDelta.
			//        Just use zoomLevel for the time being
			//float dpi = Windows::Graphics::Display::DisplayProperties::LogicalDpi;
			//float scale = (dpi*39.37*156543.04*cos(region__.latitude)/(2^16));
		}

		void MapView::setRegion() TITANIUM_NOEXCEPT {
			BasicGeoposition location = {region__.latitude, region__.longitude};
			mapview__->Center = ref new Geopoint(location);

			// TODO : Add support for latitudeDelta and longitudeDelta.
			//        Just use zoomLevel for the time being
			//float dpi = Windows::Graphics::Display::DisplayProperties::LogicalDpi;
			//float scale = (dpi*39.37*156543.04*cos(region__.latitude)/(2^16));
		}

		void MapView::setZoom(int zoom) TITANIUM_NOEXCEPT {
			Titanium::UI::MapView::setZoom(zoom);
			mapview__->ZoomLevel = zoom;
		}

		void MapView::set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_bottom(bottom);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Bottom, bottom);
		}

		void MapView::set_height(const std::string& height) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_height(height);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Height, height);
		}

		void MapView::set_left(const std::string& left) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_left(left);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Left, left);
		}

		void MapView::set_layout(const std::string& layout) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_layout(layout);
			setLayout(layout);
		}

		void MapView::set_right(const std::string& right) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_right(right);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Right, right);
		}

		void MapView::set_top(const std::string& top) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_top(top);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Top, top);
		}

		void MapView::set_width(const std::string& width) TITANIUM_NOEXCEPT
		{
			Titanium::UI::View::set_width(width);
			setLayoutProperty(Titanium::LayoutEngine::ValueName::Width, width);
		}

	} // namespace UI
}  // namespace Titanium
