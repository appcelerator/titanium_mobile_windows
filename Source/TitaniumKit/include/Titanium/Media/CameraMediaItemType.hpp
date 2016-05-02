/**
 * TitaniumKit CameraMediaItemType
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_MEDIA_CAMERAMEDIAITEMTYPE_HPP_
#define _TITANIUM_MEDIA_CAMERAMEDIAITEMTYPE_HPP_

#include "Titanium/detail/TiBase.hpp"
#include "Titanium/UI/Dimension.hpp"
#include "Titanium/Media/Constants.hpp"

namespace Titanium
{
	class Blob;

	namespace Media
	{
		using namespace HAL;

		/*!
		  @struct
		  @discussion A media object from the camera or photo gallery.
		  This is an abstract type. Any object meeting this description can be used where this type is used.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/CameraMediaItemType
		*/
		struct CameraMediaItemType
		{
			std::int32_t code { 0 };
			Titanium::UI::Dimension cropRect;
			std::string error;
			std::shared_ptr<Titanium::Blob> media;
			MediaType mediaType;
			bool success { true };

			// we don't want to instantiate Blob object when file exists. 
			// in that case we just hold file name, and create Blob object only on demand.
			std::string media_filename;
		};
		
		TITANIUMKIT_EXPORT JSObject CameraMediaItemType_to_js(const JSContext& js_context, const CameraMediaItemType& config);
		
	} // namespace Media
} // namespace Titanium
#endif // _TITANIUM_MEDIA_CAMERAMEDIAITEMTYPE_HPP_
