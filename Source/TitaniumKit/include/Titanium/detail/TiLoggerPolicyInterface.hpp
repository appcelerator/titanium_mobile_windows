/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DETAIL_TILOGGERPOLICYINTERFACE_HPP_
#define _TITANIUM_DETAIL_TILOGGERPOLICYINTERFACE_HPP_

#include "TitaniumKit_EXPORT.h"
#include <string>

namespace Titanium
{
	namespace detail
	{
		class TITANIUMKIT_EXPORT TiLoggerPolicyInterface
		{
		public:
			TiLoggerPolicyInterface() = default;
			virtual ~TiLoggerPolicyInterface() = default;
			TiLoggerPolicyInterface(const TiLoggerPolicyInterface&) = default;
			TiLoggerPolicyInterface& operator=(const TiLoggerPolicyInterface&) = default;

#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TiLoggerPolicyInterface(TiLoggerPolicyInterface&&) = default;
			TiLoggerPolicyInterface& operator=(TiLoggerPolicyInterface&&) = default;
#endif

			virtual void Write(const std::string& log_message) = 0;
		};
	} // namespace detail
}  // namespace Titanium

#endif  // _TITANIUM_DETAIL_TILOGGERPOLICYINTERFACE_HPP_
