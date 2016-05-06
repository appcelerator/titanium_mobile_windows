/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DETAIL_TILOGGER_HPP_
#define _TITANIUM_DETAIL_TILOGGER_HPP_

#include "Titanium/detail/TiLoggerPolicyConsole.hpp"
#include "Titanium/detail/TiLoggerPolicyAPI.hpp"
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <mutex>
#include <memory>

namespace Titanium
{
	namespace detail
	{
		// The TiLogger infrastructure was inspired by this Dr. Dobbs article:
		//
		// A Lightweight Logger for C++
		// By Filip Janiszewski, January 31, 2013
		// http://www.drdobbs.com/cpp/a-lightweight-logger-for-c/240147505

		/*!
		  @class

		  @abstract The logging infrastructure used by the Titanium
		  library.

		  @discussion Here is an example of how to use the Titanium
		  logging facility:

		  TITANIUM_LOG_DEBUG("Before loop.");
		  for(short i = 0 ; i < 3 ; ++i)
		  {
			  TITANIUM_LOG_DEBUG("The value of 'i' is ", i , ". " , 3 - i - 1 , " more iterations left ");
		  }
		  TITANIUM_LOG_WARN("After loop.");
		  TITANIUM_LOG_ERROR("All good things come to an end.");
		*/

		enum class TITANIUMKIT_EXPORT TiLoggerSeverityType {
			Ti_TRACE,
			Ti_DEBUG,
			Ti_INFO,
			Ti_WARN,
			Ti_ERROR
		};

		template <typename TiLoggerPolicy>
		class TiLogger final
		{
		public:
			template <typename...Args>
			static std::shared_ptr<TiLogger<TiLoggerPolicy>> Instance(Args&&...args);

			TiLogger(const TiLogger&) = delete;
			TiLogger& operator=(const TiLogger&) = delete;

#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			TiLogger(TiLogger&&) = delete;
			TiLogger& operator=(TiLogger&&) = delete;
#endif

			template <TiLoggerSeverityType severity, typename... Args>
			void Print(Args... args);

		private:
			template <typename...Args>
			TiLogger(Args&&... args);

			~TiLogger() = default;

			// Core printing functionality.
			void PrintImpl();

			template <typename First, typename... Rest>
			void PrintImpl(First first_parameter, Rest... rest);

			// This struct only exists so that a custom deleter can be passed to
			// std::shared_ptr<TiLogger<T>> while keeping the TiLogger<T> destructor
			// private.
			struct deleter
			{
				void operator()(TiLogger* ptr)
				{
					delete ptr;
				}
			};

			std::shared_ptr<TiLoggerPolicy> ti_log_policy__;
			uint32_t log_line_number__{0};
			std::ostringstream log_stream__;
			std::mutex ti_logger_mutex__;
		};

		template <typename TiLoggerPolicy>
		template <typename...Args>
		TiLogger<TiLoggerPolicy>::TiLogger(Args&&...args)
		    : ti_log_policy__(std::make_shared<TiLoggerPolicy>(std::forward<Args>(args)...))
		{
		}

		template <typename TiLoggerPolicy>
		template <typename...Args>
		std::shared_ptr<TiLogger<TiLoggerPolicy>> TiLogger<TiLoggerPolicy>::Instance(Args&&...args)
		{
			static std::shared_ptr<TiLogger<TiLoggerPolicy>> instance;
			static std::once_flag of;
			std::call_once(of, [&args...] {
      instance = std::shared_ptr<TiLogger<TiLoggerPolicy>>(new TiLogger<TiLoggerPolicy>(std::forward<Args>(args)...), deleter{});
			});

			return instance;
		}

		template <typename TiLoggerPolicy>
		template <TiLoggerSeverityType severity, typename... Args>
		void TiLogger<TiLoggerPolicy>::Print(Args... args)
		{
			std::lock_guard<std::mutex> lock(ti_logger_mutex__);

			// The Debug and Error severity strings (i.e. "DEBUG" and "ERROR")
			// are the longest of the three severity strings, and each is 5
			// characters long. Since we want all of the severity types to have
			// the same width on output, we set it to 5.
			log_stream__ << std::setw(5) << std::left;

			switch (severity) {
				case TiLoggerSeverityType::Ti_TRACE:
					log_stream__ << "[TRACE] ";
					break;
				case TiLoggerSeverityType::Ti_DEBUG:
					log_stream__ << "[DEBUG] ";
					break;
				case TiLoggerSeverityType::Ti_INFO:
					log_stream__ << "[INFO] ";
					break;
				case TiLoggerSeverityType::Ti_WARN:
					log_stream__ << "[WARN] ";
					break;
				case TiLoggerSeverityType::Ti_ERROR:
					log_stream__ << "[ERROR] ";
					break;
			};

			PrintImpl(args...);
		}

		template <typename TiLoggerPolicy>
		void TiLogger<TiLoggerPolicy>::PrintImpl()
		{
			ti_log_policy__->Write(log_stream__.str());
			log_stream__.str("");
		}

		template <typename TiLoggerPolicy>
		template <typename First, typename... Rest>
		void TiLogger<TiLoggerPolicy>::PrintImpl(First first_parameter, Rest... rest)
		{
			log_stream__ << first_parameter;
			PrintImpl(rest...);
		}

#ifdef TITANIUM_LOGGING_ENABLE

		// Logging to console
		using TiLogger_t    = TiLogger<TiLoggerPolicyConsole>;

		// Logging with Ti.API
		using TiAPILogger_t = TiLogger<TiLoggerPolicyAPI>;

#define TITANIUM_LOG_TRACE Titanium::detail::TiLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_TRACE>
#define TITANIUM_LOG_DEBUG Titanium::detail::TiLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_DEBUG>
#define TITANIUM_LOG_INFO Titanium::detail::TiLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_INFO>
#define TITANIUM_LOG_WARN Titanium::detail::TiLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_WARN>
#define TITANIUM_LOG_ERROR Titanium::detail::TiLogger_t::Instance()->Print<Titanium::detail::TiLoggerSeverityType::Ti_ERROR>
#define TITANIUM_API_LOG_TRACE Titanium::detail::TiAPILogger_t::Instance(get_context())->Print<Titanium::detail::TiLoggerSeverityType::Ti_TRACE>
#define TITANIUM_API_LOG_DEBUG Titanium::detail::TiAPILogger_t::Instance(get_context())->Print<Titanium::detail::TiLoggerSeverityType::Ti_DEBUG>
#define TITANIUM_API_LOG_INFO Titanium::detail::TiAPILogger_t::Instance(get_context())->Print<Titanium::detail::TiLoggerSeverityType::Ti_INFO>
#define TITANIUM_API_LOG_WARN Titanium::detail::TiAPILogger_t::Instance(get_context())->Print<Titanium::detail::TiLoggerSeverityType::Ti_WARN>
#define TITANIUM_API_LOG_ERROR Titanium::detail::TiAPILogger_t::Instance(get_context())->Print<Titanium::detail::TiLoggerSeverityType::Ti_ERROR>
#else
#define TITANIUM_LOG_TRACE(...)
#define TITANIUM_LOG_DEBUG(...)
#define TITANIUM_LOG_INFO(...)
#define TITANIUM_LOG_WARN(...)
#define TITANIUM_LOG_ERROR(...)
#define TITANIUM_API_LOG_TRACE(...)
#define TITANIUM_API_LOG_DEBUG(...)
#define TITANIUM_API_LOG_INFO(...)
#define TITANIUM_API_LOG_WARN(...)
#define TITANIUM_API_LOG_ERROR(...)
#endif
	} // namespace detail
}  // namespace Titanium

#endif  // _TITANIUM_DETAIL_TILOGGER_HPP_
