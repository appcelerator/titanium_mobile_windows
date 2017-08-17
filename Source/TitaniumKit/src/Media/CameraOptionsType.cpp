/**
 * TitaniumKit CameraOptionsType
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Media/CameraOptionsType.hpp"
#include "Titanium/UI/View.hpp"
#include "Titanium/UI/2DMatrix.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Media
	{
		using namespace HAL;

		CameraOptionsType create_empty_CameraOptionsType(const JSContext& js_context)
		{
			CameraOptionsType options {
				false,
				true,
				0,
				true,
				true,
				false,
				std::vector<MediaType>(),
				nullptr,
				nullptr,
				false,
				true,
				nullptr,
				std::chrono::milliseconds::min(),
				Quality::High,
				CameraOption::NotDetermined,
				create_empty_CameraOptionsTypeCallbacks(js_context)
			};
			return options;
		}

		CameraOptionsTypeCallbacks create_empty_CameraOptionsTypeCallbacks(const JSContext& js_context)
		{
			auto empty = js_context.CreateNull();
			CameraOptionsTypeCallbacks callbacks{
				empty,
				empty,
				empty
			};
			return callbacks;
		}

		CameraOptionsType js_to_CameraOptionsType(const JSObject& object)
		{
			std::vector<MediaType> mediaTypes;
			
			const auto js_types_property = object.GetProperty("mediaTypes");
			if (js_types_property.IsObject()) {
				const auto js_types = static_cast<JSObject>(js_types_property);
				if (js_types.IsArray()) {
					auto types = static_cast<std::vector<JSValue>>(static_cast<JSArray>(js_types));
					for (const auto v : types) {
						mediaTypes.push_back(static_cast<MediaType>(static_cast<std::uint32_t>(v)));
					}
				}
			}

			const auto js_overlay = object.GetProperty("overlay");
			ENSURE_MODULE_OBJECT(js_overlay, overlay, Titanium::UI::View)
			
			const auto js_popoverView = object.GetProperty("overlay");
			ENSURE_MODULE_OBJECT(js_popoverView, popoverView, Titanium::UI::View)
			
			const auto js_transform = object.GetProperty("transform");
			ENSURE_MODULE_OBJECT(js_transform, transform, Titanium::UI::TwoDMatrix)

			const auto js_whichCamera = object.GetProperty("whichCamera");
			auto whichCamera = CameraOption::NotDetermined;
			if (!js_whichCamera.IsUndefined()) {
				const auto value = static_cast<CameraOption>(static_cast<uint32_t>(js_whichCamera));
				if (value == CameraOption::Front || value == CameraOption::Rear) {
					whichCamera = value;
				}
			}
			
			const auto success_property = object.GetProperty("success");
			const auto onsuccess = [success_property](const CameraMediaItemType& item) {
				TITANIUM_EXCEPTION_CATCH_START {
					if (success_property.IsObject()) {
						auto func = static_cast<JSObject>(success_property);
						if (func.IsFunction()) {
							const std::vector<JSValue> args = {
								CameraMediaItemType_to_js(func.get_context(), item)
							};
							func(args, func);
						}
					}
				} TITANIUM_EXCEPTION_CATCH_END_CTX(success_property.get_context())
			};
			const auto cancel_property = object.GetProperty("cancel");
			const auto oncancel = [cancel_property](const ErrorResponse& e) {
				TITANIUM_EXCEPTION_CATCH_START {
					if (cancel_property.IsObject()) {
						auto func = static_cast<JSObject>(cancel_property);
						if (func.IsFunction()) {
							const std::vector<JSValue> args = {
								ErrorResponse_to_js(func.get_context(), e)
							};
							func(args, func);
						}
					}
				} TITANIUM_EXCEPTION_CATCH_END_CTX(cancel_property.get_context())
			};
			const auto error_property = object.GetProperty("error");
			const auto onerror = [error_property](const ErrorResponse& e) {
				TITANIUM_EXCEPTION_CATCH_START {
					if (error_property.IsObject()) {
						auto func = static_cast<JSObject>(error_property);
						if (func.IsFunction()) {
							const std::vector<JSValue> args = {
								ErrorResponse_to_js(func.get_context(), e)
							};
							func(args, func);
						}
					}
				} TITANIUM_EXCEPTION_CATCH_END_CTX(error_property.get_context())
			};

			CameraOptionsTypeCallbacks callbacks {
				cancel_property,
				error_property,
				success_property,
				oncancel,
				onerror,
				onsuccess,
			};
			
			CameraOptionsType config {
				JSOBJECT_GETPROPERTY(object, allowEditing, bool, false),
				JSOBJECT_GETPROPERTY(object, animated, bool, true),
				JSOBJECT_GETPROPERTY(object, arrowDirection, std::uint32_t, 0),
				JSOBJECT_GETPROPERTY(object, autohide, bool, true),
				JSOBJECT_GETPROPERTY(object, autorotate, bool, true),
				JSOBJECT_GETPROPERTY(object, isPopOver, bool, false),
				mediaTypes,
				overlay,
				popoverView,
				JSOBJECT_GETPROPERTY(object, saveToPhotoGallery, bool, false),
				JSOBJECT_GETPROPERTY(object, showControls, bool, true),
				transform,
				std::chrono::milliseconds::min(),
				Quality::High,
				whichCamera,
				callbacks
			};
			
			return config;
		};

		JSObject CameraOptionsType_to_js(const JSContext& js_context, const CameraOptionsType& config)
		{
			std::vector<JSValue> mediaTypes;
			for (const auto mediaType : config.mediaTypes) {
				mediaTypes.push_back(js_context.CreateNumber(static_cast<std::uint32_t>(mediaType)));
			}
			
			JSValue overlay = js_context.CreateNull();
			if (config.overlay != nullptr) {
				overlay = config.overlay->get_object();
			}
			
			JSValue popoverView = js_context.CreateNull();
			if (config.popoverView != nullptr) {
				popoverView = config.popoverView->get_object();
			}
			
			JSValue transform = js_context.CreateNull();
			if (config.transform != nullptr) {
				transform = config.transform->get_object();
			}
			
			auto object = js_context.CreateObject();
			object.SetProperty("allowEditing", js_context.CreateBoolean(config.allowEditing));
			object.SetProperty("animated", js_context.CreateBoolean(config.animated));
			object.SetProperty("arrowDirection", js_context.CreateNumber(config.arrowDirection));
			object.SetProperty("autohide", js_context.CreateBoolean(config.autohide));
			object.SetProperty("autorotate", js_context.CreateBoolean(config.autorotate));
			object.SetProperty("cancel",  config.callbacks.cancel);
			object.SetProperty("error",   config.callbacks.error);
			object.SetProperty("isPopOver", js_context.CreateBoolean(config.isPopOver));
			object.SetProperty("mediaTypes", js_context.CreateArray(mediaTypes));
			object.SetProperty("overlay", overlay);
			object.SetProperty("popoverView", popoverView);
			object.SetProperty("saveToPhotoGallery", js_context.CreateBoolean(config.saveToPhotoGallery));
			object.SetProperty("showControls", js_context.CreateBoolean(config.showControls));
			object.SetProperty("success", config.callbacks.success);
			object.SetProperty("videoMaximumDuration", js_context.CreateNumber(static_cast<double>(config.videoMaximumDuration.count())));
			object.SetProperty("whichCamera", js_context.CreateNumber(static_cast<std::uint32_t>(config.whichCamera)));
			object.SetProperty("videoQuality", js_context.CreateNumber(static_cast<std::uint32_t>(config.videoQuality)));
			return object;
		}
	} // namespace Media
} // namespace Titanium
