/**
 * TitaniumKit CameraOptionsType
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_MEDIA_CAMERAOPTIONSTYPE_HPP_
#define _TITANIUM_MEDIA_CAMERAOPTIONSTYPE_HPP_

#include "Titanium/detail/TiBase.hpp"
#include "Titanium/ErrorResponse.hpp"
#include "Titanium/Media/Constants.hpp"
#include "Titanium/Media/CameraMediaItemType.hpp"
#include <chrono>
#include <functional>

namespace Titanium
{
	namespace UI
	{
		class View;
		class TwoDMatrix;
	}

	namespace Media
	{
		using namespace HAL;

		struct CameraOptionsTypeCallbacks 
		{
			// need to keep these references to prevent from GC
			JSValue cancel;
			JSValue error;
			JSValue success;
			std::function<void(const ErrorResponse&)> oncancel;
			std::function<void(const ErrorResponse&)> onerror;
			std::function<void(const CameraMediaItemType&)> onsuccess;
		};

		/*!
		  @struct
		  @discussion Simple object for specifying options to showCamera.
		  This is an abstract type. Any object meeting this description can be used where this type is used.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/CameraOptionsType
		*/
		struct CameraOptionsType
		{
			bool allowEditing;
			bool animated;
			std::uint32_t arrowDirection;
			bool autohide;
			bool autorotate;
			bool isPopOver;
			std::vector<MediaType> mediaTypes;
			std::shared_ptr<Titanium::UI::View> overlay;
			std::shared_ptr<Titanium::UI::View> popoverView;
			bool saveToPhotoGallery;
			bool showControls;
			std::shared_ptr<Titanium::UI::TwoDMatrix> transform;
			std::chrono::milliseconds videoMaximumDuration;
			Quality videoQuality;
			CameraOption whichCamera;
			CameraOptionsTypeCallbacks callbacks;
		};
		
		TITANIUMKIT_EXPORT CameraOptionsType create_empty_CameraOptionsType(const JSContext& js_context);
		TITANIUMKIT_EXPORT CameraOptionsTypeCallbacks create_empty_CameraOptionsTypeCallbacks(const JSContext& js_context);
		TITANIUMKIT_EXPORT CameraOptionsType js_to_CameraOptionsType(const JSObject& object);
		TITANIUMKIT_EXPORT JSObject CameraOptionsType_to_js(const JSContext& js_context, const CameraOptionsType& config);
		
	} // namespace Media
} // namespace Titanium
#endif // _TITANIUM_MEDIA_CAMERAOPTIONSTYPE_HPP_
