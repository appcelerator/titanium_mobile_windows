/**
 * Log forwarder for Titanium CLI
 *
 * Copyright (c) 2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_LOGFORWARDER_HPP_
#define _TITANIUMWINDOWS_LOGFORWARDER_HPP_

#include "TitaniumWindows_Utility_EXPORT.h"
#include <string>
#include "Titanium/detail/TiLoggerPolicyInterface.hpp"
#include "Titanium/detail/TiLogger.hpp"
#include <agents.h>

namespace TitaniumWindows
{
	/*!
	  This is an agent that is meant to connect over TCP to the CLi and forward logs over the socket. If unable to make a connection,
	  or not running under CLI we will forward logs to std::clog.
	*/
	class log_forwarder : public concurrency::agent
	{
	public:
		explicit log_forwarder() {}

		// Retrieves any error that occurs during the life of the agent.
		bool get_error(std::exception& e)
		{
			return try_receive(_error, e);
		}

	protected:
		void run();

	private:
		concurrency::overwrite_buffer<std::exception> _error;
	};

	class TITANIUMWINDOWS_UTILITY_EXPORT LogForwarder final
	{
	public:
		static bool done__;

#pragma warning(push)
#pragma warning(disable : 4251)
		static concurrency::unbounded_buffer<std::string> buffer__; // Buffer used to store log messages that we haven't written yet
		log_forwarder reader__; // agent/thread that writes the actual log messages to CLI/debug
#pragma warning(pop)

		LogForwarder();
		virtual ~LogForwarder();

		void logSync(const std::string& message);
		void log(const std::string& message);
		void connect();
	};

	class TiLoggerPolicyAsyncLogRelay final : public Titanium::detail::TiLoggerPolicyInterface
	{
	public:
		TiLoggerPolicyAsyncLogRelay()
		{
		}

		~TiLoggerPolicyAsyncLogRelay() = default;
		TiLoggerPolicyAsyncLogRelay(const TiLoggerPolicyAsyncLogRelay&) = default;
		TiLoggerPolicyAsyncLogRelay& operator=(const TiLoggerPolicyAsyncLogRelay&) = default;

#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		TiLoggerPolicyAsyncLogRelay(TiLoggerPolicyAsyncLogRelay&&) = default;
		TiLoggerPolicyAsyncLogRelay& operator=(TiLoggerPolicyAsyncLogRelay&&) = default;
#endif

		virtual void Write(const std::string& log_message) override final
 		{
 			concurrency::asend(LogForwarder::buffer__, log_message);
		}
	};

	class TiLoggerPolicyAsyncBackgroundLogRelay final : public Titanium::detail::TiLoggerPolicyInterface
	{
	public:
		TiLoggerPolicyAsyncBackgroundLogRelay()
		{
		}

		~TiLoggerPolicyAsyncBackgroundLogRelay() = default;
		TiLoggerPolicyAsyncBackgroundLogRelay(const TiLoggerPolicyAsyncBackgroundLogRelay&) = default;
		TiLoggerPolicyAsyncBackgroundLogRelay& operator=(const TiLoggerPolicyAsyncBackgroundLogRelay&) = default;

#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		TiLoggerPolicyAsyncBackgroundLogRelay(TiLoggerPolicyAsyncBackgroundLogRelay&&) = default;
		TiLoggerPolicyAsyncBackgroundLogRelay& operator=(TiLoggerPolicyAsyncBackgroundLogRelay&&) = default;
#endif

		virtual void Write(const std::string& log_message) override final
 		{
			const auto logger = std::make_shared<LogForwarder>();
			logger->logSync(log_message);
		}
	};
}  // namespace TitaniumWindows

// 
// Logging macro for module debugging:
// TITANIUM_MODULE_LOG_INFO("value: ", value);
//
using TiLogRelayLogger_t = Titanium::detail::TiLogger<TitaniumWindows::TiLoggerPolicyAsyncLogRelay>;

#define TITANIUM_MODULE_LOG_TRACE TiLogRelayLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_TRACE>
#define TITANIUM_MODULE_LOG_DEBUG TiLogRelayLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_DEBUG>
#define TITANIUM_MODULE_LOG_INFO  TiLogRelayLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_INFO>
#define TITANIUM_MODULE_LOG_WARN  TiLogRelayLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_WARN>
#define TITANIUM_MODULE_LOG_ERROR TiLogRelayLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_ERROR>

// 
// Logging macro for background module debugging: 
// TITANIUM_MODULE_LOG_INFO_BACKGROUND("value: ", value);
//
using TiBackgroundLogRelayLogger_t = Titanium::detail::TiLogger<TitaniumWindows::TiLoggerPolicyAsyncBackgroundLogRelay>;
#define TITANIUM_MODULE_LOG_TRACE_BACKGROUND TiBackgroundLogRelayLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_TRACE>
#define TITANIUM_MODULE_LOG_DEBUG_BACKGROUND TiBackgroundLogRelayLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_DEBUG>
#define TITANIUM_MODULE_LOG_INFO_BACKGROUND  TiBackgroundLogRelayLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_INFO>
#define TITANIUM_MODULE_LOG_WARN_BACKGROUND  TiBackgroundLogRelayLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_WARN>
#define TITANIUM_MODULE_LOG_ERROR_BACKGROUND TiBackgroundLogRelayLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_ERROR>


#endif  // _TITANIUMWINDOWS_LOGFORWARDER_HPP_
