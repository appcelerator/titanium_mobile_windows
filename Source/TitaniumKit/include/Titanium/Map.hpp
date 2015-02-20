/**
 * Titanium.Map for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_MAP_HPP_
#define _TITANIUM_MAP_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
		@class
		@discussion This is the Titanium Map Module.
		See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.MapModule
	*/
	class TITANIUMKIT_EXPORT MapModule : public Module, public JSExport<MapModule>
	{

	public:

		enum class MapType {
			HYBRID,
			SATELITE,
			STANDARD
		};

		virtual JSValue MAPTYPE_HYBRID() const TITANIUM_NOEXCEPT;
		virtual JSValue MAPTYPE_SATELITE() const TITANIUM_NOEXCEPT;
		virtual JSValue MAPTYPE_STANDARD() const TITANIUM_NOEXCEPT;

		/*!
			@method
			@abstract createMapView
			@discussion Creates and returns an instance of <Titanium.Map.View>.
		*/
		virtual JSValue createView(JSValue parameters) TITANIUM_NOEXCEPT;

		/*!
			@method
			@abstract createAnnotation
			@discussion Creates and returns an instance of <Titanium.Map.Annotation>.
		*/
		virtual JSValue createAnnotation(JSValue parameters) TITANIUM_NOEXCEPT;

		MapModule(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;
		virtual ~MapModule() = default;
		MapModule(const MapModule&) = default;
		MapModule& operator=(const MapModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		MapModule(MapModule&&)                 = default;
		MapModule& operator=(MapModule&&)      = default;
#endif

		static void JSExportInitialize();

		virtual JSValue js_createView(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
		virtual JSValue js_createAnnotation(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)

#pragma warning(pop)
	};
} // namespace Titanium
#endif // _TITANIUM_MAP_HPP_