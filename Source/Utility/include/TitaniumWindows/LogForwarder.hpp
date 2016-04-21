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
#include <agents.h>

// 
// Logging macro for module debugging:
// TITANIUM_MODULE_LOG_INFO("value: " << value);
//
#define TITANIUM_MODULE_LOG(level, expr) \
	{ const auto message = static_cast<::std::ostringstream&>(std::ostringstream() << level << expr).str();  concurrency::asend(TitaniumWindows::LogForwarder::buffer__, message); }
#define TITANIUM_MODULE_LOG_TRACE(expr) TITANIUM_MODULE_LOG("[TRACE] ", expr)
#define TITANIUM_MODULE_LOG_DEBUG(expr) TITANIUM_MODULE_LOG("[DEBUG] ", expr)
#define TITANIUM_MODULE_LOG_INFO(expr)  TITANIUM_MODULE_LOG("[INFO] ",  expr)
#define TITANIUM_MODULE_LOG_WARN(expr)  TITANIUM_MODULE_LOG("[WARN] ",  expr)
#define TITANIUM_MODULE_LOG_ERROR(expr) TITANIUM_MODULE_LOG("[ERROR] ", expr)

// 
// Logging macro for background module debugging: 
// TITANIUM_MODULE_LOG_INFO_BACKGROUND("value: " << value);
//
#define TITANIUM_MODULE_LOG_BACKGROUND(level, expr) \
	{ const auto message = static_cast<::std::ostringstream&>(std::ostringstream() << level << expr).str(); const auto logger = std::make_shared<TitaniumWindows::LogForwarder>(); logger->logSync(message); }
#define TITANIUM_MODULE_LOG_TRACE_BACKGROUND(expr) TITANIUM_MODULE_LOG_BACKGROUND("[TRACE] ", expr)
#define TITANIUM_MODULE_LOG_DEBUG_BACKGROUND(expr) TITANIUM_MODULE_LOG_BACKGROUND("[DEBUG] ", expr)
#define TITANIUM_MODULE_LOG_INFO_BACKGROUND(expr)  TITANIUM_MODULE_LOG_BACKGROUND("[INFO] ",  expr)
#define TITANIUM_MODULE_LOG_WARN_BACKGROUND(expr)  TITANIUM_MODULE_LOG_BACKGROUND("[WARN] ",  expr)
#define TITANIUM_MODULE_LOG_ERROR_BACKGROUND(expr) TITANIUM_MODULE_LOG_BACKGROUND("[ERROR] ", expr)

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

}  // namespace TitaniumWindows


#endif  // _TITANIUMWINDOWS_LOGFORWARDER_HPP_
