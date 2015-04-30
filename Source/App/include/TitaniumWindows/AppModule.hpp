/**
* Titanium.App for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_APPMODULE_HPP_
#define _TITANIUMWINDOWS_APPMODULE_HPP_

#include "TitaniumWindows/detail/AppBase.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class AppModule

	  @discussion This is the Titanium.App implementation for Windows.
	*/
	class TITANIUMWINDOWS_APP_EXPORT AppModule final : public Titanium::AppModule, public JSExport<AppModule>
	{

	public:
		AppModule(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~AppModule() = default;
		AppModule(const AppModule&) = default;
		AppModule& operator=(const AppModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		AppModule(AppModule&&) = default;
		AppModule& operator=(AppModule&&) = default;
#endif

		virtual bool keyboardVisible() const TITANIUM_NOEXCEPT override;

		static void JSExportInitialize();

		virtual void enableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
		virtual void disableEvent(const std::string& event_name) TITANIUM_NOEXCEPT override;
	private:

		static JSObject RectToJS(const JSContext& js_context, const Windows::Foundation::Rect& rect);

		Windows::Foundation::EventRegistrationToken keyboardframe_showing_event__;
		Windows::Foundation::EventRegistrationToken keyboardframe_hiding_event__;

	private:
		bool keyboardVisible__ { false };
	};
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_APPMODULE_HPP_