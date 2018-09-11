/**
 * TitaniumKit ErrorResponse
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/ErrorResponse.hpp"

namespace Titanium
{
	using namespace HAL;

	ErrorResponse js_to_ErrorResponse(const JSObject& object)
	{
		ErrorResponse errorResponse;
		if (object.HasProperty("code")) {
			errorResponse.code = static_cast<std::int32_t>(object.GetProperty("code"));
		}
		if (object.HasProperty("error")) {
			errorResponse.error = static_cast<std::string>(object.GetProperty("error"));
		}
		if (object.HasProperty("success")) {
			errorResponse.success = static_cast<bool>(object.GetProperty("success"));
		}
		return errorResponse;
	};

	JSObject ErrorResponse_to_js(const JSContext& js_context, const ErrorResponse& errorResponse)
	{
		auto object = js_context.CreateObject();
		object.SetProperty("code",  js_context.CreateNumber(errorResponse.code));
		object.SetProperty("error", js_context.CreateString(errorResponse.error));
		object.SetProperty("success", js_context.CreateBoolean(errorResponse.success));
		return object;
	}
} // namespace Titanium
