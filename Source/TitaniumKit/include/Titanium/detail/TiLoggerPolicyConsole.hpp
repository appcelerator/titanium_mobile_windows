/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DETAIL_TILOGGERPOLICYCONSOLE_HPP_
#define _TITANIUM_DETAIL_TILOGGERPOLICYCONSOLE_HPP_

#include "Titanium/detail/TiLoggerPolicyInterface.hpp"
#include <iostream>

namespace Titanium
{
	namespace detail
	{
		class TITANIUMKIT_EXPORT TiLoggerPolicyConsole final : public TiLoggerPolicyInterface
		{
		public:
			TiLoggerPolicyConsole()
			{
			}

			~TiLoggerPolicyConsole() = default;
			TiLoggerPolicyConsole(const TiLoggerPolicyConsole&) = default;
			TiLoggerPolicyConsole& operator=(const TiLoggerPolicyConsole&) = default;

#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TiLoggerPolicyConsole(TiLoggerPolicyConsole&&) = default;
			TiLoggerPolicyConsole& operator=(TiLoggerPolicyConsole&&) = default;
#endif

			virtual void Write(const std::string& log_message) override final
			{
				std::clog << log_message << std::endl;
			}
		};
	} // namespace detail
}  // namespace Titanium

#endif  // _TITANIUM_DETAIL_TILOGGERPOLICYCONSOLE_HPP_
