/**
 * Titanium.Analytics for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_ANALYTICS_HPP_
#define _TITANIUM_ANALYTICS_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{

	using namespace HAL;

	/*!
	  @class
	  @discussion This is the Titanium Analytics Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Analytics
	*/
	class TITANIUMKIT_EXPORT Analytics : public Module, public JSExport<Analytics>
	{

	public:

		Analytics(const JSContext&) TITANIUM_NOEXCEPT;
		virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

		virtual ~Analytics() = default;
		Analytics(const Analytics&) = default;
		Analytics& operator=(const Analytics&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Analytics(Analytics&&)                 = default;
		Analytics& operator=(Analytics&&)      = default;
#endif

		static void JSExportInitialize();
		static JSObject GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT;

		TITANIUM_PROPERTY_DEF(_receivedResponse);
		TITANIUM_PROPERTY_READONLY_DEF(lastEvent);
		TITANIUM_FUNCTION_DEF(_start);
		TITANIUM_FUNCTION_DEF(_startPostingEvents);
		TITANIUM_FUNCTION_DEF(featureEvent);
		TITANIUM_FUNCTION_DEF(navEvent);
		TITANIUM_FUNCTION_DEF(getLastEvent);
		TITANIUM_PROPERTY_DEF(optedOut);
		TITANIUM_FUNCTION_DEF(setOptedOut);
		TITANIUM_FUNCTION_DEF(getOptedOut);

		bool loadJS();

		JSObject getTiObject() {
			return ti_analytics__;
		}

	private:
		JSObject ti_analytics__;
	};

} // namespace Titanium
#endif // _TITANIUM_ANALYTICS_HPP_