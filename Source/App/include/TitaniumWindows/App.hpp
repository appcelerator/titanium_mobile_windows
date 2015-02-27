/**
* Titanium.App for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_APP_HPP_
#define _TITANIUMWINDOWS_APP_HPP_

#include "TitaniumWindows/detail/AppBase.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class

	  @discussion This is the Titanium.AppModule implementation for Windows.
	*/
	class TITANIUMWINDOWS_APP_EXPORT AppModule final : public Titanium::AppModule, public JSExport<AppModule>{

	public:
		AppModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~AppModule() = default;
		AppModule(const AppModule&) = default;
		AppModule& operator=(const AppModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		AppModule(AppModule&&) = default;
		AppModule& operator=(AppModule&&) = default;
#endif

		static void JSExportInitialize();

	private:

		virtual bool accessibilityEnabled() const TITANIUM_NOEXCEPT;
		virtual bool proximityDetection() const TITANIUM_NOEXCEPT;
		virtual bool proximityState() const TITANIUM_NOEXCEPT;
		virtual std::string sessionId() const TITANIUM_NOEXCEPT;

		virtual JSValue fireSystemEvent(const std::string& eventName, JSValue param) TITANIUM_NOEXCEPT;
	};
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_APP_HPP_