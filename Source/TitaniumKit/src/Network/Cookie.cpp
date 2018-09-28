/**
 * TitaniumKit Titanium.Network.Cookie
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Network/Cookie.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Network
	{


		Cookie::Cookie(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Module(js_context, "Ti.Network.Cookie")
			, comment__("")
			, domain__("")
			, expiryDate__("")
			, httponly__(false)
			, name__("")
			, originalUrl__("")
			, path__("")
			, secure__(false)
			, value__("")
			, version__(1)
		{
		}

		TITANIUM_PROPERTY_READWRITE(Cookie, std::string, comment)
		TITANIUM_PROPERTY_READWRITE(Cookie, std::string, domain)
		TITANIUM_PROPERTY_READWRITE(Cookie, std::string, expiryDate)
		TITANIUM_PROPERTY_READWRITE(Cookie, bool, httponly)
		TITANIUM_PROPERTY_READWRITE(Cookie, std::string, originalUrl)
		TITANIUM_PROPERTY_READWRITE(Cookie, std::string, path)
		TITANIUM_PROPERTY_READWRITE(Cookie, bool, secure)
		TITANIUM_PROPERTY_READWRITE(Cookie, std::string, value)
		TITANIUM_PROPERTY_READWRITE(Cookie, std::uint32_t, version)
		TITANIUM_PROPERTY_READ(Cookie, std::string, name)
		// name property is creation-only
		void Cookie::set_name(const std::string& name) TITANIUM_NOEXCEPT
		{
			if (name__.empty()) {
				name__ = name;
			}
		}

		/*!
		  @method
		  @abstract isValid
		  @discussion Returns true if the cookie is valid.
		  For a cookie to be valid the minimum properties requiered are name, value, path and either domain or originalUrl
		*/
		bool Cookie::isValid() TITANIUM_NOEXCEPT
		{
			return !name__.empty() && !value__.empty() && !path__.empty() && (!domain__.empty() || !originalUrl__.empty());
		}

		void Cookie::JSExportInitialize()
		{
			JSExport<Cookie>::SetClassVersion(1);
			JSExport<Cookie>::SetParent(JSExport<Module>::Class());

			TITANIUM_ADD_PROPERTY(Cookie, comment);
			TITANIUM_ADD_PROPERTY(Cookie, domain);
			TITANIUM_ADD_PROPERTY(Cookie, expiryDate);
			TITANIUM_ADD_PROPERTY(Cookie, httponly);
			TITANIUM_ADD_PROPERTY(Cookie, name);
			TITANIUM_ADD_PROPERTY(Cookie, originalUrl);
			TITANIUM_ADD_PROPERTY(Cookie, path);
			TITANIUM_ADD_PROPERTY(Cookie, secure);
			TITANIUM_ADD_PROPERTY(Cookie, value);
			TITANIUM_ADD_PROPERTY(Cookie, version);

			TITANIUM_ADD_FUNCTION(Cookie, isValid);
			TITANIUM_ADD_FUNCTION(Cookie, getComment);
			TITANIUM_ADD_FUNCTION(Cookie, setComment);
			TITANIUM_ADD_FUNCTION(Cookie, getDomain);
			TITANIUM_ADD_FUNCTION(Cookie, setDomain);
			TITANIUM_ADD_FUNCTION(Cookie, getExpiryDate);
			TITANIUM_ADD_FUNCTION(Cookie, setExpiryDate);
			TITANIUM_ADD_FUNCTION(Cookie, getHttponly);
			TITANIUM_ADD_FUNCTION(Cookie, setHttponly);
			TITANIUM_ADD_FUNCTION(Cookie, getName);
			TITANIUM_ADD_FUNCTION(Cookie, getOriginalUrl);
			TITANIUM_ADD_FUNCTION(Cookie, setOriginalUrl);
			TITANIUM_ADD_FUNCTION(Cookie, getPath);
			TITANIUM_ADD_FUNCTION(Cookie, setPath);
			TITANIUM_ADD_FUNCTION(Cookie, getSecure);
			TITANIUM_ADD_FUNCTION(Cookie, setSecure);
			TITANIUM_ADD_FUNCTION(Cookie, getValue);
			TITANIUM_ADD_FUNCTION(Cookie, setValue);
			TITANIUM_ADD_FUNCTION(Cookie, getVersion);
			TITANIUM_ADD_FUNCTION(Cookie, setVersion);
		}

		TITANIUM_PROPERTY_GETTER_STRING(Cookie, comment)
		TITANIUM_PROPERTY_SETTER_STRING(Cookie, comment)
		TITANIUM_PROPERTY_GETTER_STRING(Cookie, domain)
		TITANIUM_PROPERTY_SETTER_STRING(Cookie, domain)
		TITANIUM_PROPERTY_GETTER_STRING(Cookie, expiryDate)
		TITANIUM_PROPERTY_SETTER_STRING(Cookie, expiryDate)

		TITANIUM_PROPERTY_GETTER_BOOL(Cookie, httponly)
		TITANIUM_PROPERTY_SETTER_BOOL(Cookie, httponly)

		TITANIUM_PROPERTY_GETTER_STRING(Cookie, name)
		TITANIUM_PROPERTY_SETTER_STRING(Cookie, name)
		TITANIUM_PROPERTY_GETTER_STRING(Cookie, originalUrl)
		TITANIUM_PROPERTY_SETTER_STRING(Cookie, originalUrl)

		TITANIUM_PROPERTY_GETTER_STRING(Cookie, path)
		TITANIUM_PROPERTY_SETTER_STRING(Cookie, path)

		TITANIUM_PROPERTY_GETTER_BOOL(Cookie, secure)
		TITANIUM_PROPERTY_SETTER_BOOL(Cookie, secure)

		TITANIUM_PROPERTY_GETTER_STRING(Cookie, value)
		TITANIUM_PROPERTY_SETTER_STRING(Cookie, value)

		TITANIUM_PROPERTY_GETTER_UINT(Cookie, version)
		TITANIUM_PROPERTY_SETTER_UINT(Cookie, version)

		TITANIUM_FUNCTION(Cookie, isValid)
		{
			return get_context().CreateBoolean(isValid());
		}

		TITANIUM_FUNCTION_AS_GETTER(Cookie, getComment, comment)
		TITANIUM_FUNCTION_AS_SETTER(Cookie, setComment, comment)
		TITANIUM_FUNCTION_AS_GETTER(Cookie, getDomain, domain)
		TITANIUM_FUNCTION_AS_SETTER(Cookie, setDomain, domain)
		TITANIUM_FUNCTION_AS_GETTER(Cookie, getExpiryDate, expiryDate)
		TITANIUM_FUNCTION_AS_SETTER(Cookie, setExpiryDate, expiryDate)
		TITANIUM_FUNCTION_AS_GETTER(Cookie, getHttponly, httponly)
		TITANIUM_FUNCTION_AS_SETTER(Cookie, setHttponly, httponly)
		TITANIUM_FUNCTION_AS_GETTER(Cookie, getName, name)
		TITANIUM_FUNCTION_AS_GETTER(Cookie, getOriginalUrl, originalUrl)
		TITANIUM_FUNCTION_AS_SETTER(Cookie, setOriginalUrl, originalUrl)
		TITANIUM_FUNCTION_AS_GETTER(Cookie, getPath, path)
		TITANIUM_FUNCTION_AS_SETTER(Cookie, setPath, path)
		TITANIUM_FUNCTION_AS_GETTER(Cookie, getSecure, secure)
		TITANIUM_FUNCTION_AS_SETTER(Cookie, setSecure, secure)
		TITANIUM_FUNCTION_AS_GETTER(Cookie, getValue, value)
		TITANIUM_FUNCTION_AS_SETTER(Cookie, setValue, value)
		TITANIUM_FUNCTION_AS_GETTER(Cookie, getVersion, version)
		TITANIUM_FUNCTION_AS_SETTER(Cookie, setVersion, version)

	} // namespace Network
} // namespace Titanium
