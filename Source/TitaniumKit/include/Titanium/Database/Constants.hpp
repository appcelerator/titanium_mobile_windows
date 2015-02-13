/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_DATABASE_CONSTANTS_HPP_
#define _TITANIUM_DATABASE_CONSTANTS_HPP_

#include "Titanium/detail/TiBase.hpp"
#include <unordered_set>
#include <functional>

namespace Titanium
{
	namespace Database
	{
		enum class TITANIUMKIT_EXPORT FIELD_TYPE {
			DOUBLE,
			FLOAT,
			INT,
			STRING,
		};
	} // namespace Database
}  // namespace Titanium

// Provide a hash function so that a Titanium::Database::FIELD_TYPE can be stored in an
// unordered container.
namespace std
{
	using Titanium::Database::FIELD_TYPE;
	template <>
	struct hash<FIELD_TYPE>
	{
		using argument_type = FIELD_TYPE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};
}  // namespace std

namespace Titanium
{
	namespace Database
	{
		class TITANIUMKIT_EXPORT Constants final
		{
		public:
			static std::string to_string(const FIELD_TYPE&) TITANIUM_NOEXCEPT;
			static FIELD_TYPE to_FIELD_TYPE(const std::string& fieldTypeName) TITANIUM_NOEXCEPT;
			static FIELD_TYPE to_FIELD_TYPE(std::underlying_type<FIELD_TYPE>::type) TITANIUM_NOEXCEPT;
			static std::underlying_type<FIELD_TYPE>::type to_underlying_type(const FIELD_TYPE&) TITANIUM_NOEXCEPT;
		};
	} // namespace Database
}  // namespace Titanium

#endif  // _TITANIUM_DATABASE_CONSTANTS_HPP_
