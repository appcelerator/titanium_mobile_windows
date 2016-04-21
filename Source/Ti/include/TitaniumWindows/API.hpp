/**
* Titanium.API for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_API_HPP_
#define _TITANIUMWINDOWS_API_HPP_

#include "Titanium/API.hpp"
#include "TitaniumWindows_Ti_EXPORT.h"
#include "TitaniumWindows/LogForwarder.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class API
	  @ingroup Titanium.API

	  @discussion This is the Titanium.API implementation for Windows.
	*/
	class TITANIUMWINDOWS_TI_EXPORT API final : public Titanium::API, public JSExport<API>
	{
	public:
		TITANIUM_FUNCTION_UNIMPLEMENTED(timestamp);

		virtual void postInitialize(JSObject& js_object) override;

		API(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~API() TITANIUM_NOEXCEPT;
		API(const API&) = default;
		API& operator=(const API&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		API(API&&) = default;
		API& operator=(API&&) = default;
#endif

		static void JSExportInitialize();

	protected:
#pragma warning(push)
#pragma warning(disable : 4251)
		virtual void log(const std::string& message) const TITANIUM_NOEXCEPT override final;
		std::shared_ptr<LogForwarder> logger__;
#pragma warning(pop)

	};
}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_API_HPP_
