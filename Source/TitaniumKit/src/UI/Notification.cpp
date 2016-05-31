/**
 * TitaniumKit Titanium.UI.Notification
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Notification.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace UI
	{

		Notification::Notification(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: View(js_context, "Ti.UI.Notification"),
			message__(""),
			duration__(NOTIFICATION_DURATION::SHORT),
			xOffset__(0),
			yOffset__(0),
			horizontalMargin__(0),
			verticalMargin__(0)
		{
		}

		TITANIUM_PROPERTY_READWRITE(Notification, std::string, message)
		TITANIUM_PROPERTY_READWRITE(Notification, NOTIFICATION_DURATION, duration)
		TITANIUM_PROPERTY_READWRITE(Notification, int32_t, xOffset)
		TITANIUM_PROPERTY_READWRITE(Notification, int32_t, yOffset)
		TITANIUM_PROPERTY_READWRITE(Notification, double, horizontalMargin)
		TITANIUM_PROPERTY_READWRITE(Notification, double, verticalMargin)

		void Notification::show() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_WARN("Notification::show: Unimplemented");
		}

		void Notification::JSExportInitialize() {
			JSExport<Notification>::SetClassVersion(1);
			JSExport<Notification>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(Notification, message);
			TITANIUM_ADD_PROPERTY(Notification, duration);
			TITANIUM_ADD_PROPERTY(Notification, xOffset);
			TITANIUM_ADD_PROPERTY(Notification, yOffset);
			TITANIUM_ADD_PROPERTY(Notification, horizontalMargin);
			TITANIUM_ADD_PROPERTY(Notification, verticalMargin);

			TITANIUM_ADD_FUNCTION(Notification, show);
			TITANIUM_ADD_FUNCTION(Notification, getMessage);
			TITANIUM_ADD_FUNCTION(Notification, setMessage);
			TITANIUM_ADD_FUNCTION(Notification, getDuration);
			TITANIUM_ADD_FUNCTION(Notification, setDuration);
			TITANIUM_ADD_FUNCTION(Notification, getXOffset);
			TITANIUM_ADD_FUNCTION(Notification, setXOffset);
			TITANIUM_ADD_FUNCTION(Notification, getYOffset);
			TITANIUM_ADD_FUNCTION(Notification, setYOffset);
			TITANIUM_ADD_FUNCTION(Notification, getHorizontalMargin);
			TITANIUM_ADD_FUNCTION(Notification, setHorizontalMargin);
			TITANIUM_ADD_FUNCTION(Notification, getVerticalMargin);
			TITANIUM_ADD_FUNCTION(Notification, setVerticalMargin);
		}

		TITANIUM_PROPERTY_GETTER_STRING(Notification, message)
		TITANIUM_PROPERTY_SETTER_STRING(Notification, message)

		TITANIUM_PROPERTY_GETTER_ENUM(Notification, duration)
		TITANIUM_PROPERTY_SETTER_ENUM(Notification, duration, NOTIFICATION_DURATION)

		TITANIUM_PROPERTY_GETTER_INT(Notification, xOffset)
		TITANIUM_PROPERTY_SETTER_INT(Notification, xOffset)

		TITANIUM_PROPERTY_GETTER_INT(Notification, yOffset)
		TITANIUM_PROPERTY_SETTER_INT(Notification, yOffset)

		TITANIUM_PROPERTY_GETTER_DOUBLE(Notification, horizontalMargin)
		TITANIUM_PROPERTY_SETTER_DOUBLE(Notification, horizontalMargin)

		TITANIUM_PROPERTY_GETTER_DOUBLE(Notification, verticalMargin)
		TITANIUM_PROPERTY_SETTER_DOUBLE(Notification, verticalMargin)

		TITANIUM_FUNCTION(Notification, show)
		{
			show();
			return get_context().CreateUndefined();
		}
		TITANIUM_FUNCTION_AS_GETTER(Notification, getMessage, message)
		TITANIUM_FUNCTION_AS_SETTER(Notification, setMessage, message)

		TITANIUM_FUNCTION_AS_GETTER(Notification, getDuration, duration)
		TITANIUM_FUNCTION_AS_SETTER(Notification, setDuration, duration)

		TITANIUM_FUNCTION_AS_GETTER(Notification, getXOffset, xOffset)
		TITANIUM_FUNCTION_AS_SETTER(Notification, setXOffset, xOffset)

		TITANIUM_FUNCTION_AS_GETTER(Notification, getYOffset, yOffset)
		TITANIUM_FUNCTION_AS_SETTER(Notification, setYOffset, yOffset)

		TITANIUM_FUNCTION_AS_GETTER(Notification, getHorizontalMargin, horizontalMargin)
		TITANIUM_FUNCTION_AS_SETTER(Notification, setHorizontalMargin, horizontalMargin)

		TITANIUM_FUNCTION_AS_GETTER(Notification, getVerticalMargin, verticalMargin)
		TITANIUM_FUNCTION_AS_SETTER(Notification, setVerticalMargin, verticalMargin)

	} // namespace UI
} // namespace Titanium
