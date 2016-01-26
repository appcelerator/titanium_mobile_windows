/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_APPLICATION_HPP_
#define _TITANIUM_APPLICATION_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium
{
	using namespace HAL;

	class TITANIUMKIT_EXPORT Application final
	{
	public:
		Application(const JSContext& js_context);

		JSValue Run(const std::string& app_js);

		JSContext get_context() const;

		Application() = delete;
		virtual ~Application() = default;
		Application(const Application&) = default;
		Application& operator=(const Application&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Application(Application&&) = default;
		Application& operator=(Application&&) = default;
#endif

	private:
		JSContext js_context__;
	};

}  // namespace Titanium

#endif  // _TITANIUM_APPLICATION_HPP_
