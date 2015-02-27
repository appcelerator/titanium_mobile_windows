/**
 * Titanium.UI.MapView for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_MAPVIEW_HPP_
#define _TITANIUMWINDOWS_UI_MAPVIEW_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "ViewBase.hpp"

using namespace Windows::UI::Xaml::Controls::Maps;
using namespace Windows::Services::Maps;

namespace TitaniumWindows
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class
 		  @discussion This is the Titanium.UI.MapView implementation for Windows.
		*/
#pragma warning(push)
#pragma warning(disable : 4275)
		class TITANIUMWINDOWS_UI_EXPORT MapView final : public Titanium::UI::MapView, public JSExport<MapView>, public ViewBase 
		{
#pragma warning(pop)
		public:
			MapView(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~MapView();
			MapView(const MapView&)            = default;
			MapView& operator=(const MapView&) = default;
		#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			MapView(MapView&&)                 = default;
			MapView& operator=(MapView&&)      = default;
		#endif

			static void JSExportInitialize();

			virtual void setRegion(JSObject& region) TITANIUM_NOEXCEPT;
			virtual void setRegion() TITANIUM_NOEXCEPT;
			virtual void setMapType(Titanium::Map::MAP_TYPE mapType) TITANIUM_NOEXCEPT;
			virtual void setZoom(int zoom) TITANIUM_NOEXCEPT;

			virtual void set_bottom(const std::string& bottom) TITANIUM_NOEXCEPT override final;
			virtual void set_height(const std::string& height) TITANIUM_NOEXCEPT override final;
			virtual void set_layout(const std::string& layout) TITANIUM_NOEXCEPT override final;
			virtual void set_left(const std::string& left) TITANIUM_NOEXCEPT override final;
			virtual void set_right(const std::string& right) TITANIUM_NOEXCEPT override final;
			virtual void set_top(const std::string& top) TITANIUM_NOEXCEPT override final;
			virtual void set_width(const std::string& width) TITANIUM_NOEXCEPT override final;

		protected:

		private:

			MapControl^ mapview__ = {nullptr};
		};
	} // namespace UI
}  // namespace Titanium
#endif // _TITANIUMWINDOWS_UI_MAPVIEW_HPP_
