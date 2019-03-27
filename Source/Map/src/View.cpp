/**
 * Titanium.Map.View for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Map/View.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/Map/Annotation.hpp"
#include "TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp"
#include "TitaniumWindows/App/Properties.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
using namespace Windows::UI::Xaml::Controls::Maps;
#endif

namespace TitaniumWindows
{
	namespace Map
	{
		using namespace Windows::UI::Xaml;
		using namespace Windows::UI::Xaml::Controls;
		using namespace Windows::UI::Xaml::Input;

		std::shared_ptr<TitaniumWindows::Map::View> View::CurrentView__ { nullptr };

		View::View(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Map::View(js_context)
		{
			TITANIUM_LOG_DEBUG("View::ctor Initialize");
		}

		View::~View()
		{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			mapview__ = nullptr;
#endif
		}

		void View::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
			Titanium::Map::View::postCallAsConstructor(js_context, arguments);

			// Save current View in static variable, assuming we use only one MapControl at once.
			// Assuming it's right since that's the precondition we use static MapControl::SetLocation in Annotaiton.
			CurrentView__ = get_object().GetPrivate<View>();

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			mapview__ = ref new MapControl();

			// obtain mapservicetoken
			auto titanium_js = get_context().get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(titanium_js.IsObject());
			auto titanium_obj = static_cast<JSObject>(titanium_js);

			auto app_js = titanium_obj.GetProperty("App");
			TITANIUM_ASSERT(app_js.IsObject());
			auto app_obj = static_cast<JSObject>(app_js);

			auto properties_js = app_obj.GetProperty("Properties");
			TITANIUM_ASSERT(properties_js.IsObject());
			auto properties_obj = static_cast<JSObject>(properties_js);
			auto properties_ptr = properties_obj.GetPrivate<TitaniumWindows::App::Properties>();
			TITANIUM_ASSERT(properties_ptr);

			auto mapservicetoken = properties_ptr->getString("mapservicetoken");
			if (mapservicetoken) {
				// set mapservicetoken
				mapview__->MapServiceToken = TitaniumWindows::Utility::ConvertString(*mapservicetoken);
			}
			else {
				TITANIUM_LOG_ERROR("Ti.Map.View: Windows mapservicetoken must be defined in tiapp.xml property, none was found");
			}

			Titanium::Map::View::setLayoutDelegate<TitaniumWindows::UI::WindowsViewLayoutDelegate>();

			layoutDelegate__->set_defaultHeight(Titanium::UI::LAYOUT::FILL);
			layoutDelegate__->set_defaultWidth(Titanium::UI::LAYOUT::FILL);

			getViewLayoutDelegate<TitaniumWindows::UI::WindowsViewLayoutDelegate>()->setComponent(mapview__);

			zoom(12); // use a default zoom of 12 for Windows?
#endif
		}

		void View::JSExportInitialize()
		{
			JSExport<View>::SetClassVersion(1);
			JSExport<View>::SetParent(JSExport<Titanium::Map::View>::Class());
		}

		uint32_t View::get_maxZoomLevel() const TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			return static_cast<uint32_t>(mapview__->MaxZoomLevel); // should be 20
#else
			return 20;
#endif
		}

		uint32_t View::get_minZoomLevel() const TITANIUM_NOEXCEPT
		{
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			return static_cast<uint32_t>(mapview__->MinZoomLevel); // should be 1
#else
			return 1;
#endif
		}

		void View::set_mapType(const Titanium::Map::MAP_TYPE& mapType) TITANIUM_NOEXCEPT
		{
			Titanium::Map::View::set_mapType(mapType);
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			if (mapType == Titanium::Map::MAP_TYPE::HYBRID) {
				mapview__->Style = MapStyle::AerialWithRoads;
			} else if (mapType == Titanium::Map::MAP_TYPE::SATELLITE) {
				mapview__->Style = MapStyle::Aerial;
			} else if (mapType == Titanium::Map::MAP_TYPE::NORMAL) {
				mapview__->Style = MapStyle::Road;
			}
#endif
		}

		void View::set_region(const Titanium::Map::MapRegionTypev2& region) TITANIUM_NOEXCEPT
		{
			Titanium::Map::View::set_region(region);

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			using namespace Windows::Devices::Geolocation;

			// set center to supplied lat/long
			BasicGeoposition location = { region.latitude, region.longitude };
			auto gp = ref new Geopoint(location);
			mapview__->Center = gp;

			// If there are deltas, use them to set the view bounds
			if (region.latitudeDelta > 0 && region.longitudeDelta > 0) {
				BasicGeoposition top_left = { region.latitude - region.latitudeDelta, region.longitude - region.longitudeDelta };
				BasicGeoposition bottom_right = { region.latitude + region.latitudeDelta, region.longitude + region.longitudeDelta };

				auto bounds = ref new GeoboundingBox(bottom_right, top_left);
				mapview__->TrySetViewBoundsAsync(bounds, nullptr, get_animate() ? MapAnimationKind::Default : MapAnimationKind::None);
				mapview__->DesiredPitch = region.tilt;
			} else {
				// no deltas, use the long/lat and zoom to set view area/region
				if (region.zoom > 0) {
					mapview__->TrySetViewAsync(gp, static_cast<double>(region.zoom), nullptr, region.tilt, get_animate() ? MapAnimationKind::Default : MapAnimationKind::None);
				} else {
					mapview__->TrySetViewAsync(gp, nullptr, nullptr, region.tilt, get_animate() ? MapAnimationKind::Default : MapAnimationKind::None);
				}
			}
#endif
		}

		void View::set_showsBuildings(const bool& buildings) TITANIUM_NOEXCEPT
		{
			Titanium::Map::View::set_showsBuildings(buildings);
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			mapview__->LandmarksVisible = buildings;
#endif
		}

		void View::set_traffic(const bool& traffic) TITANIUM_NOEXCEPT
		{
			Titanium::Map::View::set_traffic(traffic);
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			mapview__->TrafficFlowVisible = traffic;
#endif
		}

		void View::addAnnotation(const Annotation_shared_ptr_t& annotation) TITANIUM_NOEXCEPT
		{
			Titanium::Map::View::addAnnotation(annotation);
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			auto native_annotation_ptr = annotation->get_object().GetPrivate<TitaniumWindows::Map::Annotation>();
			if (native_annotation_ptr != nullptr) {
				mapview__->Children->Append(native_annotation_ptr->GetMapIcon());
			}
#endif
		}

		void View::removeAnnotation(const Annotation_shared_ptr_t& annotation) TITANIUM_NOEXCEPT
		{
			Titanium::Map::View::removeAnnotation(annotation);

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			for (std::uint32_t i = 0; i < mapview__->Children->Size; i++) {
				auto element = mapview__->Children->GetAt(i);
				Windows::UI::Xaml::Controls::Grid^ icon = dynamic_cast<Windows::UI::Xaml::Controls::Grid^>(element);
				if (icon == nullptr) {
					continue; // not an annotation
				}
				// find annotation identified by title or a reference.
				auto annotation_ptr = annotation->get_object().GetPrivate<TitaniumWindows::Map::Annotation>()->GetMapIcon();
				if (icon == annotation_ptr) {
					//mapview__->MapElements->RemoveAt(i);
					mapview__->Children->RemoveAt(i);
					break;
				}
			}
#endif
		}

		void View::zoom(const uint32_t& zoom) TITANIUM_NOEXCEPT
		{
			Titanium::Map::View::zoom(zoom);
#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			if (zoom != 0) // no zoom specified in the region object?
			{
				// TODO Enforce min/max zoom levels?
				mapview__->ZoomLevel = zoom;
			}
#endif
		}

		void View::HandleMapClick(const JSContext& ctx, const std::shared_ptr<View>& view, const double& latitude, const double& longitude, const std::shared_ptr<Annotation>& annotation) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(view);

			JSObject  eventArgs = ctx.CreateObject();
			eventArgs.SetProperty("map", view->get_object());
			eventArgs.SetProperty("latitude", ctx.CreateNumber(latitude));
			eventArgs.SetProperty("longitude", ctx.CreateNumber(longitude));

			if (annotation) {
				eventArgs.SetProperty("clicksource", ctx.CreateString("pin"));
				eventArgs.SetProperty("annotation", annotation->get_object());
				eventArgs.SetProperty("title", ctx.CreateString(annotation->get_title()));
				eventArgs.SetProperty("subtitle", ctx.CreateString(annotation->get_subtitle()));
			} else {
				eventArgs.SetProperty("clicksource", ctx.CreateNull());
			}

			view->fireEvent("click", eventArgs);
		}

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
		void View::enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			getViewLayoutDelegate<TitaniumWindows::UI::WindowsViewLayoutDelegate>()->filterEvents({ "click" });
			Titanium::Map::View::enableEvent(event_name);
			if (event_name == "click") {
				click_event__ = mapview__->MapTapped += ref new Windows::Foundation::TypedEventHandler<MapControl^, MapInputEventArgs^>([this, event_name](MapControl^ sender, MapInputEventArgs^ e) {
					HandleMapClick(get_context(), get_object().GetPrivate<View>(), e->Location->Position.Latitude, e->Location->Position.Longitude, nullptr);
				});
			}
		}

		void View::disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT
		{
			Titanium::Map::View::disableEvent(event_name);
			if (event_name == "click") {
				mapview__->MapTapped -= click_event__;
			}
		}
#endif
	} // namespace Map
}  // namespace Titanium
