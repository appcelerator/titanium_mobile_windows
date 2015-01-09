/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_FILESYSTEM_CONSTANTS_HPP_
#define _TITANIUM_FILESYSTEM_CONSTANTS_HPP_

#include "Titanium/detail/TiBase.hpp"
#include <unordered_set>
#include <functional>

namespace Titanium
{
namespace Filesystem
{
enum class TITANIUMKIT_EXPORT MODE {
	READ = 1 << 0,
	WRITE = 1 << 1,
	APPEND = 1 << 2,
};
}
}  // namespace Titanium { namespace Filesystem {

// Provide a hash function so that a Titanium::Filesystem::MODE can be stored in an
// unordered container.
namespace std
{
using Titanium::Filesystem::MODE;
template <>
struct hash<MODE> {
	using argument_type = MODE;
	using result_type = std::size_t;
	using underlying_type = std::underlying_type<argument_type>::type;
	std::hash<underlying_type> hash_function = std::hash<underlying_type>();

	result_type operator()(const argument_type& property_attribute) const
	{
		return hash_function(static_cast<underlying_type>(property_attribute));
	}
};
}  // namespace std {

namespace Titanium
{
namespace Filesystem
{
class TITANIUMKIT_EXPORT Constants final
{
   public:
	static std::string to_string(const MODE&) TITANIUM_NOEXCEPT;
	static MODE to_MODE(const std::string& modeName) TITANIUM_NOEXCEPT;
	static std::unordered_set<MODE> to_MODE(std::underlying_type<MODE>::type) TITANIUM_NOEXCEPT;
	static std::underlying_type<MODE>::type to_underlying_type(const std::unordered_set<MODE>&) TITANIUM_NOEXCEPT;
	static std::underlying_type<MODE>::type to_underlying_type(const MODE&) TITANIUM_NOEXCEPT;
};
}
}  // namespace Titanium { namespace Filesystem {

#endif  // _TITANIUM_FILESYSTEM_CONSTANTS_HPP_
