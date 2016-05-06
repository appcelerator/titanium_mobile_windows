/**
 * TiLoggerPolicyAPI
 *
 * Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DETAIL_TILOGGERPOLICYAPI_HPP_
#define _TITANIUM_DETAIL_TILOGGERPOLICYAPI_HPP_

#include "Titanium/detail/TiLoggerPolicyInterface.hpp"
#include "HAL/HAL.hpp"
#include <iostream>

namespace Titanium
{
	class API;

	namespace detail
	{
		using namespace HAL;

		class TITANIUMKIT_EXPORT TiLoggerPolicyAPI final : public TiLoggerPolicyInterface
		{
		public:
			TiLoggerPolicyAPI(const JSContext& js_context);

			~TiLoggerPolicyAPI() = default;
			TiLoggerPolicyAPI(const TiLoggerPolicyAPI&) = default;
			TiLoggerPolicyAPI& operator=(const TiLoggerPolicyAPI&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TiLoggerPolicyAPI(TiLoggerPolicyAPI&&) = default;
			TiLoggerPolicyAPI& operator=(TiLoggerPolicyAPI&&) = default;
#endif

			virtual void Write(const std::string& message) override final;

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			JSContext js_context__;
			std::shared_ptr<Titanium::API> api__;
#pragma warning(pop)
		};

	} // namespace detail
}  // namespace Titanium

#endif  // _TITANIUM_DETAIL_TILOGGERPOLICYAPI_HPP_
