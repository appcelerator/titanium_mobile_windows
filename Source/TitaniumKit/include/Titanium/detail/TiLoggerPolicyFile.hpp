/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DETAIL_TILOGGERPOLICYFILE_HPP_
#define _TITANIUM_DETAIL_TILOGGERPOLICYFILE_HPP_

#include "Titanium/detail/TiLoggerPolicyInterface.hpp"
#include <fstream>

namespace Titanium { namespace detail {
  
  class TITANIUMKIT_EXPORT TiLoggerPolicyFile final : public TiLoggerPolicyInterface {
  public:
    
    TiLoggerPolicyFile(const std::string& name) {
      ofstream__.open(name, std::ios_base::binary | std::ios_base::out);
      if(!ofstream__.is_open() ) {
        throw(std::runtime_error("TiLoggerPolicyFile: Unable to open an output stream"));
      }
    }
    
    ~TiLoggerPolicyFile() {
      ofstream__.close();
    }
    
    TiLoggerPolicyFile()                                     = delete;
    TiLoggerPolicyFile(const TiLoggerPolicyFile&)            = default;
    TiLoggerPolicyFile& operator=(const TiLoggerPolicyFile&) = default;
    
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    TiLoggerPolicyFile(TiLoggerPolicyFile&&)                 = default;
    TiLoggerPolicyFile& operator=(TiLoggerPolicyFile&&)      = default;
#endif
    
    virtual void Write(const std::string& log_message) override final {
      ofstream__ << log_message << std::endl;
      }
      
    private:
      
    // Silence 4251 on Windows since private member variables do not
    // need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable: 4251)
      std::ofstream ofstream__;
#pragma warning(pop)
  };
      
}} // namespace Titanium { namespace detail {
      
#endif // _TITANIUM_DETAIL_TILOGGERPOLICYFILE_HPP_
