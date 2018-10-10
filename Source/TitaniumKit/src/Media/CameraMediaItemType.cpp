/**
 * TitaniumKit CameraMediaItemType
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Media/CameraMediaItemType.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Media
	{
		using namespace HAL;

		JSObject CameraMediaItemType_to_js(const JSContext& js_context, const CameraMediaItemType& config)
		{
			// Lazy load blob object based on file name whenever possible.
			auto exportObj = js_context.CreateObject();
			auto object = static_cast<JSObject>(js_context.JSEvaluateScript(R"(
				var item = { get media() {
                    if (this._media_filename) {
						var file = Ti.Filesystem.getFile(this._media_filename);
						if (file.exists()) {
							return file.read();
						}
				    }
					return null;
				}};
				item;
			)", exportObj));
			object.SetProperty("code", js_context.CreateNumber(config.code));
			object.SetProperty("cropRect", Titanium::UI::Dimension_to_js(js_context, config.cropRect));
			object.SetProperty("error", js_context.CreateString(config.error));
			if (!config.media_filename.empty()) {
				object.SetProperty("_media_filename", js_context.CreateString(config.media_filename));
			}
			object.SetProperty("mediaType", js_context.CreateNumber(static_cast<std::uint32_t>(config.mediaType)));
			object.SetProperty("success", js_context.CreateBoolean(config.success));
			return object;
		}
	} // namespace Media
} // namespace Titanium
