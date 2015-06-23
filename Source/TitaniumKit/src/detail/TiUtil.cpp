/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiUtil.hpp"
#include "Titanium/detail/TiLogger.hpp"

#include <stdexcept>

namespace Titanium
{
	namespace detail
	{
		void ThrowLogicError(const std::string& internal_component_name, const std::string& message)
		{
			TITANIUM_LOG_ERROR(internal_component_name, ": ", message);
			throw std::logic_error(message);
		}

		void ThrowRuntimeError(const std::string& internal_component_name, const std::string& message)
		{
			TITANIUM_LOG_ERROR(internal_component_name, ": ", message);
			throw std::runtime_error(message);
		}

		void ThrowInvalidArgument(const std::string& internal_component_name, const std::string& message)
		{
			TITANIUM_LOG_ERROR(internal_component_name, ": ", message);
			throw std::invalid_argument(message);
		}
	} // namespace detail
}  // namespace Titanium
