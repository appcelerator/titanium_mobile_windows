/**
 * TitaniumKit Titanium.Network.Cookie
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_COOKIE_HPP_
#define _TITANIUM_COOKIE_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	namespace Network
	{

		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium Cookie Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.Network.Cookie
		*/
		class TITANIUMKIT_EXPORT Cookie : public Module, public JSExport<Cookie>
		{

		public:

			/*!
			  @property
			  @abstract comment
			  @discussion The comment describing the purpose of this cookie
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, comment);

			/*!
			  @property
			  @abstract domain
			  @discussion The domain attribute of the cookie.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, domain);

			/*!
			  @property
			  @abstract expiryDate
			  @discussion The expiration Date of the cookie.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, expiryDate);

			/*!
			  @property
			  @abstract httponly
			  @discussion The httponly attribute of the cookie.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, httponly);

			/*!
			  @property
			  @abstract name
			  @discussion The name of the cookie.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, name);

			/*!
			  @property
			  @abstract originalUrl
			  @discussion The origual url attribute of the cookie.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, originalUrl);

			/*!
			  @property
			  @abstract path
			  @discussion The path attribute of the cookie.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, path);

			/*!
			  @property
			  @abstract secure
			  @discussion The secure attribute of the cookie.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(bool, secure);

			/*!
			  @property
			  @abstract value
			  @discussion The value of the cookie.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, value);

			/*!
			  @property
			  @abstract version
			  @discussion The version of the cookie specification to which this cookie conforms.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::uint32_t, version);

			/*!
			  @method
			  @abstract isValid
			  @discussion Returns true if the cookie is valid.
			*/
			virtual bool isValid() TITANIUM_NOEXCEPT;

			Cookie(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Cookie() = default;
			Cookie(const Cookie&) = default;
			Cookie& operator=(const Cookie&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Cookie(Cookie&&)                 = default;
			Cookie& operator=(Cookie&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(comment);
			TITANIUM_PROPERTY_DEF(domain);
			TITANIUM_PROPERTY_DEF(expiryDate);
			TITANIUM_PROPERTY_DEF(httponly);
			TITANIUM_PROPERTY_DEF(name);
			TITANIUM_PROPERTY_DEF(originalUrl);
			TITANIUM_PROPERTY_DEF(path);
			TITANIUM_PROPERTY_DEF(secure);
			TITANIUM_PROPERTY_DEF(value);
			TITANIUM_PROPERTY_DEF(version);

			TITANIUM_FUNCTION_DEF(isValid);
			TITANIUM_FUNCTION_DEF(getComment);
			TITANIUM_FUNCTION_DEF(setComment);
			TITANIUM_FUNCTION_DEF(getDomain);
			TITANIUM_FUNCTION_DEF(setDomain);
			TITANIUM_FUNCTION_DEF(getExpiryDate);
			TITANIUM_FUNCTION_DEF(setExpiryDate);
			TITANIUM_FUNCTION_DEF(getHttponly);
			TITANIUM_FUNCTION_DEF(setHttponly);
			TITANIUM_FUNCTION_DEF(getName);
			TITANIUM_FUNCTION_DEF(getOriginalUrl);
			TITANIUM_FUNCTION_DEF(setOriginalUrl);
			TITANIUM_FUNCTION_DEF(getPath);
			TITANIUM_FUNCTION_DEF(setPath);
			TITANIUM_FUNCTION_DEF(getSecure);
			TITANIUM_FUNCTION_DEF(setSecure);
			TITANIUM_FUNCTION_DEF(getValue);
			TITANIUM_FUNCTION_DEF(setValue);
			TITANIUM_FUNCTION_DEF(getVersion);
			TITANIUM_FUNCTION_DEF(setVersion);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string comment__;
			std::string domain__;
			std::string expiryDate__; // TODO: std::chrono::time_point (or some other "date"-like type)?
			bool httponly__;
			std::string name__;
			std::string originalUrl__;
			std::string path__;
			bool secure__;
			std::string value__;
			std::uint32_t version__;
#pragma warning(pop)
		};

	} // namespace Network
} // namespace Titanium
#endif // _TITANIUM_COOKIE_HPP_