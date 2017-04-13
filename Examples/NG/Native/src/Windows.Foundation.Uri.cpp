/**
 * Windows Native Wrapper for Windows.Foundation.Uri
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.Foundation.Uri.hpp"
#include "Windows.Foundation.WwwFormUrlDecoder.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace Foundation
		{

		Uri::Uri(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("Uri::ctor");
		}

		void Uri::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("Uri::postCallAsConstructor ", this);
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsString(), "Expected String");
			auto baseUri = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_0));
				auto _1 = arguments.at(1); 
			TITANIUM_ASSERT_AND_THROW(_1.IsString(), "Expected String");
			auto relativeUri = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_1));

				wrapped__ = ref new ::Windows::Foundation::Uri(baseUri, relativeUri);
			}
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsString(), "Expected String");
			auto uri = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_0));

				wrapped__ = ref new ::Windows::Foundation::Uri(uri);
			}

		}

		::Windows::Foundation::Uri^ Uri::unwrapWindows_Foundation_Uri() const
		{
			return dynamic_cast<::Windows::Foundation::Uri^>(wrapped__);
		}

		::Windows::Foundation::Uri^ Uri::unwrap() const
		{
			return unwrapWindows_Foundation_Uri();
		}

		void Uri::wrap(::Windows::Foundation::Uri^ object)
		{
			wrapped__ = object;
		}

		void Uri::JSExportInitialize()
		{
			JSExport<Uri>::SetClassVersion(1);
			JSExport<Uri>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(Uri, AbsoluteUri);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, DisplayUri);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, Domain);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, Extension);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, Fragment);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, Host);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, Password);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, Path);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, Port);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, Query);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, QueryParsed);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, RawUri);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, SchemeName);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, Suspicious);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, UserName);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, AbsoluteCanonicalUri);
			TITANIUM_ADD_PROPERTY_READONLY(Uri, DisplayIri);
			TITANIUM_ADD_FUNCTION(Uri, Equals);
			TITANIUM_ADD_FUNCTION(Uri, CombineUri);
			TITANIUM_ADD_FUNCTION(Uri, ToString);
			TITANIUM_ADD_FUNCTION(Uri, UnescapeComponent);
			TITANIUM_ADD_FUNCTION(Uri, EscapeComponent);
		}

		TITANIUM_PROPERTY_GETTER(Uri, AbsoluteUri)
		{
			auto value = unwrap()->AbsoluteUri;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, DisplayUri)
		{
			auto value = unwrap()->DisplayUri;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, Domain)
		{
			auto value = unwrap()->Domain;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, Extension)
		{
			auto value = unwrap()->Extension;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, Fragment)
		{
			auto value = unwrap()->Fragment;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, Host)
		{
			auto value = unwrap()->Host;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, Password)
		{
			auto value = unwrap()->Password;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, Path)
		{
			auto value = unwrap()->Path;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, Port)
		{
			auto value = unwrap()->Port;
			auto context = get_context();
 
			auto result = context.CreateNumber(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, Query)
		{
			auto value = unwrap()->Query;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, QueryParsed)
		{
			auto value = unwrap()->QueryParsed;
			auto context = get_context();

			auto result = context.CreateObject(JSExport<Windows::Foundation::WwwFormUrlDecoder>::Class());
			auto result_wrapper = result.GetPrivate<Windows::Foundation::WwwFormUrlDecoder>();
			result_wrapper->wrap(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, RawUri)
		{
			auto value = unwrap()->RawUri;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, SchemeName)
		{
			auto value = unwrap()->SchemeName;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, Suspicious)
		{
			auto value = unwrap()->Suspicious;
			auto context = get_context();
 
			auto result = context.CreateBoolean(value); 

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, UserName)
		{
			auto value = unwrap()->UserName;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, AbsoluteCanonicalUri)
		{
			auto value = unwrap()->AbsoluteCanonicalUri;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_PROPERTY_GETTER(Uri, DisplayIri)
		{
			auto value = unwrap()->DisplayIri;
			auto context = get_context();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(value));

			return result;
		}

		TITANIUM_FUNCTION(Uri, Equals)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsObject(), "Expected Object");
			auto object_pUri = static_cast<JSObject>(_0);
 
			auto wrapper_pUri = object_pUri.GetPrivate<Windows::Foundation::Uri>();
			// FIXME What if the type we want here is some parent class of the actual wrapper's class? I think we'll get nullptr here.
			// We need some way to know the underlying type the JSObject maps to, get that, then cast to the type we want...
			auto pUri = wrapper_pUri->unwrapWindows_Foundation_Uri();

				auto method_result = unwrap()->Equals(pUri);
 
			auto result = context.CreateBoolean(method_result); 

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Uri::Equals with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(Uri, CombineUri)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsString(), "Expected String");
			auto relativeUri = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_0));

				auto method_result = unwrap()->CombineUri(relativeUri);

			auto result = context.CreateObject(JSExport<Windows::Foundation::Uri>::Class());
			auto result_wrapper = result.GetPrivate<Windows::Foundation::Uri>();
			result_wrapper->wrap(method_result);

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Uri::CombineUri with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(Uri, ToString)
		{
			auto context = get_context();
			if (arguments.size() == 0) {
				auto method_result = unwrap()->ToString();
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(method_result));

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Uri::ToString with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(Uri, UnescapeComponent)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsString(), "Expected String");
			auto toUnescape = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_0));

				auto method_result = ::Windows::Foundation::Uri::UnescapeComponent(toUnescape);
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(method_result));

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Uri::UnescapeComponent with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		TITANIUM_FUNCTION(Uri, EscapeComponent)
		{
			auto context = get_context();
			if (arguments.size() == 1) {
				auto _0 = arguments.at(0); 
			TITANIUM_ASSERT_AND_THROW(_0.IsString(), "Expected String");
			auto toEscape = TitaniumWindows::Utility::ConvertUTF8String(static_cast<std::string>(_0));

				auto method_result = ::Windows::Foundation::Uri::EscapeComponent(toEscape);
 
			auto result = context.CreateString(TitaniumWindows::Utility::ConvertUTF8String(method_result));

				return result;
			}

			// Catch-all if no arg count matches!
			TITANIUM_LOG_DEBUG("No method signature matched Uri::EscapeComponent with # of args: ", arguments.size());
			return context.CreateUndefined(); 
		}

		} // namespace Foundation
	} // namespace Windows
} // namespace Titanium
