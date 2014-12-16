/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_TIUTIL_HPP_
#define _TITANIUM_TIUTIL_HPP_

#include "Titanium/detail/TiBase.hpp"

#include <string>

namespace Titanium { namespace detail {
  
  template<typename T, typename... Ts>
  std::unique_ptr<T> make_unique(Ts&&... params) {
    return std::unique_ptr<T>(new T(std::forward<Ts>(params)...));
  }
  
  using namespace HAL;

  // Log and throw a std::logic_error from an internal component.
  TITANIUMKIT_EXPORT void      ThrowLogicError(const std::string& internal_component_name, const std::string& message);
  TITANIUMKIT_EXPORT void    ThrowRuntimeError(const std::string& internal_component_name, const std::string& message);
  TITANIUMKIT_EXPORT void ThrowInvalidArgument(const std::string& internal_component_name, const std::string& message);
  
}} // namespace Titanium { namespace detail {

#endif // _TITANIUM_TIUTIL_HPP_
