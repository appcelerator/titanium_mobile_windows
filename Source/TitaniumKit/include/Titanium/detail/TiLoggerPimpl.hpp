/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DETAIL_TILOGGERPIMPL_HPP_
#define _TITANIUM_DETAIL_TILOGGERPIMPL_HPP_

#include "TitaniumKit_EXPORT.h"
#include <string>
#include <cstdint>

namespace Titanium {
  template<typename TiLoggerPolicy>
  class TiLogger;
}

namespace Titanium { namespace detail {
  
  class TITANIUMKIT_EXPORT TiLoggerPimpl final {
    
  public:
    
    TiLoggerPimpl()                                = delete;
    ~TiLoggerPimpl()                               = delete;
    TiLoggerPimpl(const TiLoggerPimpl&)            = delete;
    TiLoggerPimpl(TiLoggerPimpl&&)                 = delete;
    TiLoggerPimpl& operator=(const TiLoggerPimpl&) = delete;
    TiLoggerPimpl& operator=(TiLoggerPimpl&&)      = delete;
    
    static std::string GetLoglineHeader(uint32_t log_line_number);
  };
  
}} // namespace Titanium { namespace detail

#endif // _TITANIUM_DETAIL_TILOGGERPIMPL_HPP_
