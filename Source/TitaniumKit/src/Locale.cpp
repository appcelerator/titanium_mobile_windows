/**
 * Copyright (c) 2015-2016 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Locale.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <boost/algorithm/string.hpp>

namespace Titanium
{
	Locale::Locale(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Module(js_context, "Ti.Locale")
		, currentLanguage__("en")
		, currentCountry__("US")
		, currentLocale__("en-US")
	{
		TITANIUM_LOG_DEBUG("Locale:: ctor ", this);
	}

	TITANIUM_PROPERTY_READ(Locale, std::string, currentCountry)
	TITANIUM_PROPERTY_READ(Locale, std::string, currentLanguage)
	TITANIUM_PROPERTY_READ(Locale, std::string, currentLocale)

	std::string Locale::formatTelephoneNumber(const std::string& number) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Locale::formatTelephoneNumber: Unimplemented");
		return number;
	}

	std::string Locale::getCurrencyCode(const std::string& locale) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Locale::getCurrencyCode: Unimplemented");
		return "";
	}

	std::string Locale::getCurrencySymbol(const std::string& currencyCode) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Locale::getCurrencySymbol: Unimplemented");
		return "";
	}

	std::string Locale::getLocaleCurrencySymbol(const std::string& locale) TITANIUM_NOEXCEPT
	{
		return getCurrencySymbol(getCurrencyCode(locale));
	}

	boost::optional<std::string> Locale::getString(const std::string& key) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Locale::getString: Unimplemented");
		return boost::none;
	}

	void Locale::setLanguage(const std::string& language) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Locale::setLanguage: Unimplemented");
	}

	void Locale::JSExportInitialize()
	{
		JSExport<Locale>::SetClassVersion(1);
		JSExport<Locale>::SetParent(JSExport<Module>::Class());

		TITANIUM_ADD_PROPERTY_READONLY(Locale, currentCountry);
		TITANIUM_ADD_PROPERTY_READONLY(Locale, currentLanguage);
		TITANIUM_ADD_PROPERTY_READONLY(Locale, currentLocale);

		TITANIUM_ADD_FUNCTION(Locale, formatTelephoneNumber);
		TITANIUM_ADD_FUNCTION(Locale, getCurrencyCode);
		TITANIUM_ADD_FUNCTION(Locale, getCurrencySymbol);
		TITANIUM_ADD_FUNCTION(Locale, getLocaleCurrencySymbol);
		TITANIUM_ADD_FUNCTION(Locale, getCurrentCountry);
		TITANIUM_ADD_FUNCTION(Locale, getCurrentLanguage);
		TITANIUM_ADD_FUNCTION(Locale, getCurrentLocale);
		TITANIUM_ADD_FUNCTION(Locale, getString);
		TITANIUM_ADD_FUNCTION(Locale, setLanguage);
	}

	JSObject Locale::GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	{
		static JSObject cached = js_context.CreateObject();
		static std::once_flag of;
		std::call_once(of, [=] {
			JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
			JSObject Titanium = static_cast<JSObject>(Titanium_property);

			JSValue Object_property = Titanium.GetProperty("Locale");
			TITANIUM_ASSERT(Object_property.IsObject());  // precondition
			cached = static_cast<JSObject>(Object_property);
		});
		return cached;
	}

	boost::optional<std::string> Locale::GetString(const JSContext& js_context, const std::string& key) TITANIUM_NOEXCEPT
	{
		const auto L = GetStaticObject(js_context);
		return L.GetPrivate<Locale>()->getString(key);
	}

	//
	// Escape characters with backslash.
	// Based on iOS behavior, not all backslashes are converted.
	//
	std::string Locale::EscapeJSCharacters(const std::string& content) TITANIUM_NOEXCEPT
	{
		// new line characters
		auto replaced = boost::replace_all_copy(content, "\\n", "\n");
		boost::replace_all(replaced, "\\r", "\r");
		boost::replace_all(replaced, "\\f", "\f");
		boost::replace_all(replaced, "\\t", "\t");

		// backspace is ignored
		boost::replace_all(replaced, "\\b", "");

		//double backslash
		boost::replace_all(replaced, "\\\\", "\\");

		// just remove backslash from \" and \'
		boost::replace_all(replaced, "\\\"", "\"");
		boost::replace_all(replaced, "\\'", "'");

		// Just remove backslash from unicode strings like "\u20ac"
		boost::replace_all(replaced, "\\u", "u");

		return replaced;
	}

	TITANIUM_PROPERTY_GETTER(Locale, currentCountry)
	{
		return get_context().CreateString(get_currentCountry());
	}

	TITANIUM_PROPERTY_GETTER(Locale, currentLanguage)
	{
		return get_context().CreateString(get_currentLanguage());
	}

	TITANIUM_PROPERTY_GETTER(Locale, currentLocale)
	{
		return get_context().CreateString(get_currentLocale());
	}

	TITANIUM_FUNCTION(Locale, formatTelephoneNumber)
	{
		ENSURE_STRING_AT_INDEX(number, 0);
		const auto ctx = this_object.get_context();
		return ctx.CreateString(GetStaticObject(ctx).GetPrivate<Locale>()->formatTelephoneNumber(number));
	}

	TITANIUM_FUNCTION(Locale, getCurrencyCode)
	{
		ENSURE_STRING_AT_INDEX(locale, 0);
		const auto ctx = this_object.get_context();
		return ctx.CreateString(GetStaticObject(ctx).GetPrivate<Locale>()->getCurrencyCode(locale));
	}

	TITANIUM_FUNCTION(Locale, getCurrencySymbol)
	{
		ENSURE_STRING_AT_INDEX(code, 0);
		const auto ctx = this_object.get_context();
		return ctx.CreateString(GetStaticObject(ctx).GetPrivate<Locale>()->getCurrencySymbol(code));
	}

	TITANIUM_FUNCTION(Locale, getLocaleCurrencySymbol)
	{
		ENSURE_STRING_AT_INDEX(locale, 0);
		const auto ctx = this_object.get_context();
		return ctx.CreateString(GetStaticObject(ctx).GetPrivate<Locale>()->getLocaleCurrencySymbol(locale));
	}

	TITANIUM_FUNCTION(Locale, getString)
	{
		ENSURE_STRING_AT_INDEX(key, 0);
		const auto ctx = this_object.get_context();
		const auto value = GetStaticObject(ctx).GetPrivate<Locale>()->getString(key);
		if (value) {
			return ctx.CreateString(EscapeJSCharacters(*value));
		} else if (arguments.size() > 1 && arguments.at(1).IsString()){
			// If there's a hint and it is a string value, let's return it.
			return arguments.at(1);
		}
		// If there's no hint and no entry, getString should return key.
		return arguments.at(0);
	}

	TITANIUM_FUNCTION(Locale, setLanguage)
	{
		ENSURE_STRING_AT_INDEX(language, 0);
		const auto ctx = this_object.get_context();
		GetStaticObject(ctx).GetPrivate<Locale>()->setLanguage(language);
		return ctx.CreateUndefined();
	}

	TITANIUM_FUNCTION_AS_GETTER(Locale, getCurrentCountry, currentCountry)
	TITANIUM_FUNCTION_AS_GETTER(Locale, getCurrentLanguage, currentLanguage)
	TITANIUM_FUNCTION_AS_GETTER(Locale, getCurrentLocale, currentLocale)

}  // namespace Titanium
