/**
 * Titanium.Map.View for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_MAP_VIEW_HPP_
#define _TITANIUMWINDOWS_MAP_VIEW_HPP_

#include "TitaniumWindows/UI/ViewBase.hpp"
#include "TitaniumWindows/Map/detail/MapBase.hpp"

using namespace Windows::UI::Xaml::Controls::Maps;
using namespace Windows::Services::Maps;

namespace TitaniumWindows
{
	namespace Map
	{
		using namespace HAL;

		/*!
		  @class
 		  @discussion This is the Titanium.Map.View implementation for Windows.
		*/
		class TITANIUMWINDOWS_MAP_EXPORT View final : public Titanium::Map::View, public JSExport<View>, public TitaniumWindows::UI::ViewBase 
		{
		public:
			View(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~View();
			View(const View&)            = default;
			View& operator=(const View&) = default;
		#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			View(View&&)                 = default;
			View& operator=(View&&)      = default;
		#endif

			static void JSExportInitialize();

			virtual uint32_t get_maxZoomLevel() const TITANIUM_NOEXCEPT override final;
			virtual uint32_t get_minZoomLevel() const TITANIUM_NOEXCEPT override final;

			virtual void set_region(const MapRegionType& region) TITANIUM_NOEXCEPT override final;
			virtual void set_mapType(const Titanium::Map::MAP_TYPE& mapType) TITANIUM_NOEXCEPT override final;
			virtual void zoom(const uint32_t& zoom) TITANIUM_NOEXCEPT override final;

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
	} // namespace Map
}  // namespace Titanium
#endif // _TITANIUMWINDOWS_MAP_VIEW_HPP_
