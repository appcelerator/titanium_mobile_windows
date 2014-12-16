/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DETAIL_HASHUTILITIES_HPP_
#define _TITANIUM_DETAIL_HASHUTILITIES_HPP_

#include <cstddef>
#include <functional>

namespace Titanium { namespace detail {

template<typename T>
struct hash;

// These utility hash functions taken from "The C++ Standard Library:
// A Tutorial and Reference (2nd Edition)" by Nicolai M. Josuttis,
// pages 364-365.

template <typename T>
inline
void hash_combine(std::size_t& seed, const T& value) {
  seed ^= std::hash<T>()(value) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

template <typename T>
inline
void hash_val(std::size_t& seed, const T& value) {
  hash_combine(seed, value);
}

template <typename T, typename... Types>
inline
void hash_val(std::size_t& seed, const T& value, const Types&... args) {
  hash_combine(seed, value);
  hash_val(seed, args...);
}

template <typename... Types>
inline
std::size_t hash_val(const Types&... args) {
  std::size_t seed = 0;
  hash_val(seed, args...);
  return seed;
}

}} // namespace Titanium { namespace detail {

#endif // _TITANIUM_DETAIL_HASHUTILITIES_HPP_
