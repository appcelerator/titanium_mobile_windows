/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/detail/TiLoggerPimpl.hpp"

#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <limits>

namespace Titanium { namespace detail {
  
  inline
  std::string to_string(const std::chrono::system_clock::time_point& tp) {
    // Convert to system time.
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    
#pragma warning(push)
#pragma warning(disable: 4996) //4996 for _CRT_SECURE_NO_WARNINGS equivalent
    // Convert to calendar time.
    //std::string ts = std::ctime(&t);
    std::string ts = std::asctime(std::localtime(&t));
    //std::string ts = std::asctime(std::gmtime(&t));
#pragma warning(pop)
    
    // Strip trailing newline.
    ts.resize(ts.size() - 1);
    
    return ts;
  }
  
  std::string TiLoggerPimpl::GetLoglineHeader(uint32_t log_line_number) {
    std::ostringstream os;
    
    os.str("");
    os << std::setfill('0')
    << std::setw(std::numeric_limits<uint32_t>::digits10)
    << log_line_number
    << " <"
    << to_string(std::chrono::system_clock::now())
    //     <<" - "
    //     << std::setfill('0')
    //     << std::setw(std::numeric_limits<std::clock_t>::digits10)
    //     << std::clock()
    <<"> ";
    
    return os.str();
  }
  
}} // namespace Titanium { namespace detail {
