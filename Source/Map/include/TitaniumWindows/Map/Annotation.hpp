/**
 * Titanium.Map.Annotation for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_MAP_ANNOTATION_HPP_
#define _TITANIUMWINDOWS_MAP_ANNOTATION_HPP_

#include "TitaniumWindows_Map_EXPORT.h"
#include "Titanium/Map/Annotation.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"

namespace TitaniumWindows
{
	namespace Map
	{
		using namespace HAL;

		/*!
		  @class
 		  @discussion This is the Titanium.Map.Annotation implementation for Windows.
		*/
		class TITANIUMWINDOWS_MAP_EXPORT Annotation final : public Titanium::Map::Annotation, public JSExport<Annotation>
		{
		public:

			virtual void set_latitude(const double& latitude)   TITANIUM_NOEXCEPT override final;
			virtual void set_longitude(const double& longitude) TITANIUM_NOEXCEPT override final;
			virtual void set_pincolor(const Titanium::Map::ANNOTATION_COLOR& pincolor) TITANIUM_NOEXCEPT override final;
			virtual void set_title(const std::string& title)    TITANIUM_NOEXCEPT override final;

			void updateGeoLocation();

			Annotation(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Annotation();
			Annotation(const Annotation&)            = default;
			Annotation& operator=(const Annotation&) = default;
		#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Annotation(Annotation&&)                 = default;
			Annotation& operator=(Annotation&&)      = default;
		#endif

			static void JSExportInitialize();

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			Windows::UI::Xaml::Controls::Grid^ GetMapIcon() {
				return mapicon__;
			}
#endif
		protected:

		private:

#if defined(IS_WINDOWS_PHONE) || defined(IS_WINDOWS_10)
			Windows::UI::Xaml::Controls::Grid^ mapicon__ = { nullptr };

			Windows::UI::Xaml::Shapes::Line^ pin__ = { nullptr };
			Windows::UI::Xaml::Shapes::Ellipse^ icon__ = { nullptr };
			Windows::UI::Xaml::Controls::TextBlock^ text__ = { nullptr };
#endif
		};
	} // namespace Map
}  // namespace Titanium
#endif // _TITANIUMWINDOWS_MAP_ANNOTATION_HPP_
