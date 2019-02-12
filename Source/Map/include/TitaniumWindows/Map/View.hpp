/**
 * Titanium.Map.View for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_MAP_VIEW_HPP_
#define _TITANIUMWINDOWS_MAP_VIEW_HPP_

#include "TitaniumWindows_Map_EXPORT.h"
#include "Titanium/Map/View.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

namespace TitaniumWindows
{
	namespace Map
	{
		using namespace HAL;

		class Annotation;

		using Annotation_shared_ptr_t = std::shared_ptr<Titanium::Map::Annotation>;

		/*!
		  @class View
		  @ingroup Titanium.Map.View
 		  @discussion This is the Titanium.Map.View implementation for Windows.
		*/
		class TITANIUMWINDOWS_MAP_EXPORT View final : public Titanium::Map::View, public JSExport<View>
		{
		public:
			TITANIUM_FUNCTION_UNIMPLEMENTED(addRoute);
			TITANIUM_FUNCTION_UNIMPLEMENTED(animateCamera);
			TITANIUM_FUNCTION_UNIMPLEMENTED(deselectAnnotation);
			TITANIUM_FUNCTION_UNIMPLEMENTED(removeRoute);
			TITANIUM_FUNCTION_UNIMPLEMENTED(selectAnnotation);
			TITANIUM_FUNCTION_UNIMPLEMENTED(setLocation);
			TITANIUM_FUNCTION_UNIMPLEMENTED(showAnnotations);
			TITANIUM_FUNCTION_UNIMPLEMENTED(snapshot);
			TITANIUM_FUNCTION_UNIMPLEMENTED(selectAnnotation);

			View(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~View();
			View(const View&)            = default;
			View& operator=(const View&) = default;
		#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			View(View&&)                 = default;
			View& operator=(View&&)      = default;
		#endif

			static void JSExportInitialize();

#pragma warning(push)
#pragma warning(disable : 4251)
			// Save current View in static variable, assuming we use only one MapControl at once.
			// Assuming it's right since that's the precondition we use static MapControl::SetLocation in Annotaiton.
			static std::shared_ptr<View> CurrentView__;
			static void HandleMapClick(const JSContext& js_context, const std::shared_ptr<View>& view, const double& latitude, const double& longitude, const std::shared_ptr<Annotation>& annotation) TITANIUM_NOEXCEPT;
#pragma warning(pop)

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			// properties
			virtual uint32_t get_maxZoomLevel() const TITANIUM_NOEXCEPT override final;
			virtual uint32_t get_minZoomLevel() const TITANIUM_NOEXCEPT override final;
			virtual void set_mapType(const Titanium::Map::MAP_TYPE& mapType) TITANIUM_NOEXCEPT override final;
			virtual void set_region(const Titanium::Map::MapRegionTypev2& region) TITANIUM_NOEXCEPT override final;
			virtual void set_showsBuildings(const bool& buildings) TITANIUM_NOEXCEPT;
			virtual void set_traffic(const bool& traffic) TITANIUM_NOEXCEPT;
			
			// methods
			virtual void addAnnotation(const Annotation_shared_ptr_t& annotation) TITANIUM_NOEXCEPT;
			virtual void removeAnnotation(const Annotation_shared_ptr_t& annotation) TITANIUM_NOEXCEPT;
			virtual void zoom(const uint32_t& zoom) TITANIUM_NOEXCEPT override final;

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
			virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
#endif
		private:

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			Windows::Foundation::EventRegistrationToken click_event__;
			Windows::UI::Xaml::Controls::Maps::MapControl^ mapview__ = { nullptr };
#endif
		};
	} // namespace Map
}  // namespace Titanium
#endif // _TITANIUMWINDOWS_MAP_VIEW_HPP_
