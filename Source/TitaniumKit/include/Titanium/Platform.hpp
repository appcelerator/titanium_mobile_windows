/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_PLATFORM_HPP_
#define _TITANIUM_PLATFORM_HPP_

#include "Titanium/Module.hpp"

namespace Titanium {

	using namespace HAL;

	/*!
	 @class
	 @discussion This is the Titanium Platform Module.
	 See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Platform
	 */
	class TITANIUMKIT_EXPORT Platform : public Module, public JSExport < Platform > {

	public:

		virtual std::string osname() const TITANIUM_NOEXCEPT;
		virtual std::string createUUID() TITANIUM_NOEXCEPT;

		Platform(const JSContext& js_context)                       TITANIUM_NOEXCEPT;
		Platform(const Platform&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

		virtual ~Platform() = default;
		Platform(const Platform&) = default;
		Platform& operator=(const Platform&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Platform(Platform&&)                 = default;
		Platform& operator=(Platform&&)      = default;
#endif

		// TODO: The following functions can automatically be generated from
		// the YAML Platform docs.
		static void JSExportInitialize();

		virtual JSValue get_osname_ArgumentValidator() const TITANIUM_NOEXCEPT final;
		virtual JSValue createUUIDArgumentValidator(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT final;

	};

} // namespace Titanium

#endif // _TITANIUM_PLATFORM_HPP_
