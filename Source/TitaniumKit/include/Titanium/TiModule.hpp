/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_TIMODULE_HPP_
#define _TITANIUM_TIMODULE_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class
	  @discussion This is the top-level Titanium Module.
	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium
	*/
	class TITANIUMKIT_EXPORT TiModule : public Module, public JSExport<TiModule>
	{
	public:
		virtual std::string version() const TITANIUM_NOEXCEPT;
		virtual std::string buildDate() const TITANIUM_NOEXCEPT;
		virtual std::string buildHash() const TITANIUM_NOEXCEPT;

		virtual void setUserAgent(const JSValue&) TITANIUM_NOEXCEPT final;

		TiModule(const JSContext&) TITANIUM_NOEXCEPT;
		virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

		virtual ~TiModule() = default;
		TiModule(const TiModule&) = default;
		TiModule& operator=(const TiModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		TiModule(TiModule&&) = default;
		TiModule& operator=(TiModule&&) = default;
#endif

		static void JSExportInitialize();

		virtual JSValue js_get_version() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getVersion(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_buildDate() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getBuildDate(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_buildHash() const TITANIUM_NOEXCEPT final;
		virtual JSValue js_getBuildHash(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
		virtual JSValue js_get_userAgent() const TITANIUM_NOEXCEPT final;
		virtual bool js_set_userAgent(const JSValue& argument) TITANIUM_NOEXCEPT;
		virtual JSValue js_getUserAgent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
		virtual JSValue js_setUserAgent(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

		virtual JSValue js_createBuffer(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

	private:
		JSValue userAgent__;
	};

}  // namespace Titanium

#endif  // _TITANIUM_TIMODULE_HPP_
