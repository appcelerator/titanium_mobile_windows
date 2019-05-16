/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_GEOLOCATION_CONSTANTS_HPP_
#define _TITANIUM_GEOLOCATION_CONSTANTS_HPP_

#include "Titanium/detail/TiBase.hpp"
#include <unordered_set>
#include <functional>

namespace Titanium
{
	namespace Geolocation
	{
		enum class TITANIUMKIT_EXPORT ACCURACY {
			BEST,
			BEST_FOR_NAVIGATION,
			HUNDRED_METERS,
			KILOMETER,
			NEAREST_TEN_METERS,
			THREE_KILOMETERS,
			HIGH,
			LOW
		};

		enum class TITANIUMKIT_EXPORT ACTIVITYTYPE {
			AUTOMOTIVE_NAVIGATION,
			FITNESS,
			OTHER,
			OTHER_NAVIGATION
		};

		enum class TITANIUMKIT_EXPORT AUTHORIZATION {
			ALWAYS,
			AUTHORIZED,
			DENIED,
			RESTRICTED,
			UNKNOWN,
			WHEN_IN_USE
		};

#ifdef ERROR
#pragma push_macro("ERROR")
#undef ERROR
#define _restore_ERROR_
#endif

		enum class TITANIUMKIT_EXPORT ERROR {
			DENIED,
			HEADING_FAILIURE,
			LOCATION_UNKNOWN,
			NETWORK,
			REGION_MONITORING_DELAYED,
			REGION_MONITORING_DENIED,
			REGION_MONITORING_FAILIURE,
			TIMEOUT,
		};

		enum class TITANIUMKIT_EXPORT PROVIDER {
			GPS,
			NETWORK,
			PASSIVE
		};

	} // namespace Geolocation
}  // namespace Titanium

// Provide a hash function so that a Titanium::Geolocation::ACCURACY can be stored in an
// unordered container.
namespace std
{
	using Titanium::Geolocation::ACCURACY;
	template <>
	struct hash<ACCURACY>
	{
		using argument_type = ACCURACY;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::Geolocation::ACTIVITYTYPE;
	template <>
	struct hash<ACTIVITYTYPE>
	{
		using argument_type = ACTIVITYTYPE;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	template <>
	struct hash<Titanium::Geolocation::AUTHORIZATION>
	{
		using argument_type = Titanium::Geolocation::AUTHORIZATION;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::Geolocation::ERROR;
	template <>
	struct hash<ERROR>
	{
		using argument_type = ERROR;
		using result_type = std::size_t;
		using underlying_type = std::underlying_type<argument_type>::type;
		std::hash<underlying_type> hash_function = std::hash<underlying_type>();

		result_type operator()(const argument_type& property_attribute) const
		{
			return hash_function(static_cast<underlying_type>(property_attribute));
		}
	};

	using Titanium::Geolocation::PROVIDER;
	template <>
	struct hash<PROVIDER>
	{
		using argument_type = PROVIDER;
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
	namespace Geolocation
	{
		class TITANIUMKIT_EXPORT Constants final
		{
		public:
			static std::string to_string(const ACCURACY&) TITANIUM_NOEXCEPT;
			static std::string to_string(const ACTIVITYTYPE&) TITANIUM_NOEXCEPT;
			static std::string to_string(const AUTHORIZATION&) TITANIUM_NOEXCEPT;
			static std::string to_string(const ERROR&) TITANIUM_NOEXCEPT;
			static std::string to_string(const PROVIDER&) TITANIUM_NOEXCEPT;
			
			static ACCURACY to_ACCURACY(const std::string& fieldTypeName) TITANIUM_NOEXCEPT;
			static ACTIVITYTYPE to_ACTIVITYTYPE(const std::string& fieldTypeName) TITANIUM_NOEXCEPT;
			static AUTHORIZATION to_AUTHORIZATION(const std::string& fieldTypeName) TITANIUM_NOEXCEPT;
			static ERROR to_ERROR(const std::string& fieldTypeName) TITANIUM_NOEXCEPT;
			static PROVIDER to_PROVIDER(const std::string& fieldTypeName) TITANIUM_NOEXCEPT;

			static ACCURACY to_ACCURACY(std::underlying_type<ACCURACY>::type) TITANIUM_NOEXCEPT;
			static ACTIVITYTYPE to_ACTIVITYTYPE(std::underlying_type<ACTIVITYTYPE>::type) TITANIUM_NOEXCEPT;
			static AUTHORIZATION to_AUTHORIZATION(std::underlying_type<AUTHORIZATION>::type) TITANIUM_NOEXCEPT;
			static ERROR to_ERROR(std::underlying_type<ERROR>::type) TITANIUM_NOEXCEPT;
			static PROVIDER to_PROVIDER(std::underlying_type<PROVIDER>::type) TITANIUM_NOEXCEPT;
			
			static std::underlying_type<ACCURACY>::type to_underlying_type(const ACCURACY&) TITANIUM_NOEXCEPT;
			static std::underlying_type<ACTIVITYTYPE>::type to_underlying_type(const ACTIVITYTYPE&) TITANIUM_NOEXCEPT;
			static std::underlying_type<AUTHORIZATION>::type to_underlying_type(const AUTHORIZATION&) TITANIUM_NOEXCEPT;
			static std::underlying_type<ERROR>::type to_underlying_type(const ERROR&) TITANIUM_NOEXCEPT;
			static std::underlying_type<PROVIDER>::type to_underlying_type(const PROVIDER&) TITANIUM_NOEXCEPT;
		};
	} // namespace Geolocation
}  // namespace Titanium

#ifdef _restore_ERROR_
#pragma pop_macro("ERROR")
#undef _restore_ERROR_
#endif

#endif  // _TITANIUM_GEOLOCATION_CONSTANTS_HPP_