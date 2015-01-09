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

	TiModule(const JSContext& js_context) TITANIUM_NOEXCEPT;
	TiModule(const TiModule&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

	virtual ~TiModule() = default;
	TiModule(const TiModule&) = default;
	TiModule& operator=(const TiModule&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
	TiModule(TiModule&&) = default;
	TiModule& operator=(TiModule&&) = default;
#endif

	static void JSExportInitialize();

	virtual JSValue get_version_ArgumentValidator() const TITANIUM_NOEXCEPT final;
	virtual JSValue getVersionArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
	virtual JSValue get_buildDate_ArgumentValidator() const TITANIUM_NOEXCEPT final;
	virtual JSValue getBuildDateArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
	virtual JSValue get_buildHash_ArgumentValidator() const TITANIUM_NOEXCEPT final;
	virtual JSValue getBuildHashArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
	virtual JSValue get_userAgent_ArgumentValidator() const TITANIUM_NOEXCEPT final;
	virtual bool set_userAgent_ArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT;
	virtual JSValue getUserAgentArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;
	virtual JSValue setUserAgentArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

	virtual JSValue createBufferArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT;

   private:
	JSValue userAgent__;
};

}  // namespace Titanium

#endif  // _TITANIUM_TIMODULE_HPP_
