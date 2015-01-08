/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Filesystem/Constants.hpp"
#include <unordered_map>
#include <mutex>

namespace Titanium {
namespace Filesystem {
std::string Constants::to_string(const MODE& modeName) TITANIUM_NOEXCEPT {
  static std::string unknown_string = "MODE::Unknown";
  static std::unordered_map<MODE, std::string> map;
  static std::once_flag of;
  std::call_once(of, []() {
      map[MODE::READ]   = "MODE_READ";
      map[MODE::WRITE]  = "MODE_WRITE";
      map[MODE::APPEND] = "MODE_EMAIL_APPEND";
  });

  std::string string = unknown_string;
  const auto position = map.find(modeName);
  if (position != map.end()) {
    string = position->second;
  }

  return string;
}

MODE Constants::to_MODE(const std::string& modeName) TITANIUM_NOEXCEPT {
  static std::unordered_map<std::string, MODE> map;
  static std::once_flag of;
  std::call_once(of, []() {
      map["MODE_READ"]   = MODE::READ;
      map["MODE_WRITE"]  = MODE::WRITE;
      map["MODE_APPEND"] = MODE::APPEND;
  });

  MODE mode = MODE::READ;
  const auto position = map.find(modeName);
  if (position != map.end()) {
    mode = position->second;
  } else {
    TITANIUM_LOG_WARN("Constants::to_MODE: Titanium::Filesystem::MODE with name '", modeName, "' does not exist");
  }

  return mode;
}

std::unordered_set<MODE> Constants::to_MODE(std::underlying_type<MODE>::type modes) TITANIUM_NOEXCEPT {
  std::unordered_set<MODE> mode_set;
  static_cast<void>((modes & (1 << 0)) && mode_set.emplace(MODE::READ).second);
  static_cast<void>((modes & (1 << 1)) && mode_set.emplace(MODE::WRITE).second);
  static_cast<void>((modes & (1 << 2)) && mode_set.emplace(MODE::APPEND).second);
  return mode_set;
}

std::underlying_type<MODE>::type Constants::to_underlying_type(const std::unordered_set<MODE>& mode_set) TITANIUM_NOEXCEPT {
  std::underlying_type<MODE>::type result = 0;
  for (auto mode : mode_set) {
    result |= static_cast<std::underlying_type<MODE>::type>(mode);
  }

  return result;
}

std::underlying_type<MODE>::type Constants::to_underlying_type(const MODE& mode) TITANIUM_NOEXCEPT {
  return static_cast<std::underlying_type<MODE>::type>(mode);
}
}
}  // namespace Titanium { namespace Filesystem {
