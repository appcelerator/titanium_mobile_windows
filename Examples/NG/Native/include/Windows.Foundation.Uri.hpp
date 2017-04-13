/**
 * Windows Native Wrapper for Windows.Foundation.Uri
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_FOUNDATION_URI_HPP_
#define _WINDOWS_FOUNDATION_URI_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Platform.Object.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace Foundation
		{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT Uri : public ::Titanium::Platform::Object, public JSExport<Uri>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(AbsoluteUri);
			TITANIUM_PROPERTY_READONLY_DEF(DisplayUri);
			TITANIUM_PROPERTY_READONLY_DEF(Domain);
			TITANIUM_PROPERTY_READONLY_DEF(Extension);
			TITANIUM_PROPERTY_READONLY_DEF(Fragment);
			TITANIUM_PROPERTY_READONLY_DEF(Host);
			TITANIUM_PROPERTY_READONLY_DEF(Password);
			TITANIUM_PROPERTY_READONLY_DEF(Path);
			TITANIUM_PROPERTY_READONLY_DEF(Port);
			TITANIUM_PROPERTY_READONLY_DEF(Query);
			TITANIUM_PROPERTY_READONLY_DEF(QueryParsed);
			TITANIUM_PROPERTY_READONLY_DEF(RawUri);
			TITANIUM_PROPERTY_READONLY_DEF(SchemeName);
			TITANIUM_PROPERTY_READONLY_DEF(Suspicious);
			TITANIUM_PROPERTY_READONLY_DEF(UserName);
			TITANIUM_PROPERTY_READONLY_DEF(AbsoluteCanonicalUri);
			TITANIUM_PROPERTY_READONLY_DEF(DisplayIri);

			TITANIUM_FUNCTION_DEF(Equals);
			TITANIUM_FUNCTION_DEF(CombineUri);
			TITANIUM_FUNCTION_DEF(ToString);
			TITANIUM_FUNCTION_DEF(UnescapeComponent);
			TITANIUM_FUNCTION_DEF(EscapeComponent);

			Uri(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Uri() = default;
			Uri(const Uri&) = default;
			Uri& operator=(const Uri&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Uri(Uri&&)                 = default;
			Uri& operator=(Uri&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::Foundation::Uri^ unwrapWindows_Foundation_Uri() const;
			void wrap(::Windows::Foundation::Uri^ object);

		private:
			::Windows::Foundation::Uri^ unwrap() const;

		};

		} // namespace Foundation
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_FOUNDATION_URI_HPP_
