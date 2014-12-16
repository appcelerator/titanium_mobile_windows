/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DETAIL_TILOGGER_HPP_
#define _TITANIUM_DETAIL_TILOGGER_HPP_

#include "Titanium/detail/TiLoggerPimpl.hpp"
#include "Titanium/detail/TiLoggerPolicyConsole.hpp"
#include "Titanium/detail/TiLoggerPolicyFile.hpp"
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <mutex>

namespace Titanium { namespace detail {
  
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
    Ti_DEBUG,
    Ti_INFO,
    Ti_WARN,
    Ti_ERROR
  };
  
  template<typename TiLoggerPolicy>
  class TiLogger final {
    
  public:
    
    TiLogger(const std::string& name)
    : ti_log_policy__(name) {
    }
    
    TiLogger()                           = delete;
    ~TiLogger()                          = default;
    TiLogger(const TiLogger&)            = default;
    TiLogger& operator=(const TiLogger&) = default;
    
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    TiLogger(TiLogger&&)                 = default;
    TiLogger& operator=(TiLogger&&)      = default;
#endif
    
    template<TiLoggerSeverityType severity, typename...Args>
    void Print(Args...args);
    
  private:
    
    // Core printing functionality.
    void PrintImpl();
    
    template<typename First, typename...Rest>
    void PrintImpl(First first_parameter, Rest...rest);
    
    TiLoggerPolicy     ti_log_policy__;
    uint32_t           log_line_number__ { 0 };
    std::ostringstream log_stream__;
    std::mutex         ti_logger_mutex__;
  };
  
  template<typename TiLoggerPolicy>
  template<TiLoggerSeverityType severity, typename...Args>
  void TiLogger<TiLoggerPolicy>::Print(Args...args)  {
    std::lock_guard<std::mutex> lock(ti_logger_mutex__);
    
    // The Debug and Error severity strings (i.e. "DEBUG" and "ERROR")
    // are the longest of the three severity strings, and each is 5
    // characters long. Since we want all of the severity types to have
    // the same width on output, we set it to 5.
    log_stream__ << std::setw(5) << std::left;
    
    switch(severity) {
      case TiLoggerSeverityType::Ti_DEBUG:
        log_stream__ << "DEBUG: ";
        break;
      case TiLoggerSeverityType::Ti_INFO:
        log_stream__ << "INFO: ";
        break;
      case TiLoggerSeverityType::Ti_WARN:
        log_stream__ << "WARN: ";
        break;
      case TiLoggerSeverityType::Ti_ERROR:
        log_stream__ << "ERROR: ";
        break;
    };
    
    PrintImpl(args...);
  }
  
  template<typename TiLoggerPolicy>
  void TiLogger<TiLoggerPolicy>::PrintImpl() {
    ti_log_policy__.Write(TiLoggerPimpl::GetLoglineHeader(log_line_number__++) + log_stream__.str() + ".");
    log_stream__.str("");
  }
  
  template<typename TiLoggerPolicy>
  template<typename First, typename...Rest >
  void TiLogger<TiLoggerPolicy>::PrintImpl(First first_parameter, Rest...rest) {
    log_stream__ << first_parameter;
    PrintImpl(rest...);
  }
  
#ifdef TITANIUM_LOGGING_ENABLE
  
  // TODO: Add a more flexible way to specify the logging policy.
  
  //static TiLogger<TiLoggerPolicyFile>    ti_logger_instance("Titanium.log");
  static TiLogger<TiLoggerPolicyConsole> ti_logger_instance("Titanium.log");
  
#define TITANIUM_LOG_DEBUG Titanium::detail::ti_logger_instance.Print<Titanium::detail::TiLoggerSeverityType::Ti_DEBUG>
#define TITANIUM_LOG_INFO  Titanium::detail::ti_logger_instance.Print<Titanium::detail::TiLoggerSeverityType::Ti_INFO>
#define TITANIUM_LOG_WARN  Titanium::detail::ti_logger_instance.Print<Titanium::detail::TiLoggerSeverityType::Ti_WARN>
#define TITANIUM_LOG_ERROR Titanium::detail::ti_logger_instance.Print<Titanium::detail::TiLoggerSeverityType::Ti_ERROR>
#else
#define TITANIUM_LOG_DEBUG(...)
#define TITANIUM_LOG_INFO(...)
#define TITANIUM_LOG_WARN(...)
#define TITANIUM_LOG_ERROR(...)
#endif
  
}} // namespace Titanium { namespace detail {

#endif // _TITANIUM_DETAIL_TILOGGER_HPP_
