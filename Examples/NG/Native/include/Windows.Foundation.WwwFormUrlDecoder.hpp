/**
 * Windows Native Wrapper for Windows.Foundation.WwwFormUrlDecoder
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_FOUNDATION_WWWFORMURLDECODER_HPP_
#define _WINDOWS_FOUNDATION_WWWFORMURLDECODER_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT WwwFormUrlDecoder : public ::Titanium::Platform::Object, public JSExport<WwwFormUrlDecoder>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(Size);

			TITANIUM_FUNCTION_DEF(GetFirstValueByName);
			TITANIUM_FUNCTION_DEF(First);
			TITANIUM_FUNCTION_DEF(GetAt);
			TITANIUM_FUNCTION_DEF(IndexOf);
			TITANIUM_FUNCTION_DEF(GetMany);

			WwwFormUrlDecoder(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~WwwFormUrlDecoder() = default;
			WwwFormUrlDecoder(const WwwFormUrlDecoder&) = default;
			WwwFormUrlDecoder& operator=(const WwwFormUrlDecoder&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			WwwFormUrlDecoder(WwwFormUrlDecoder&&)                 = default;
			WwwFormUrlDecoder& operator=(WwwFormUrlDecoder&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::Foundation::WwwFormUrlDecoder^ unwrapWindows_Foundation_WwwFormUrlDecoder() const;
			void wrap(::Windows::Foundation::WwwFormUrlDecoder^ object);

		private:
			::Windows::Foundation::WwwFormUrlDecoder^ unwrap() const;

		};

		} // namespace Foundation
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_FOUNDATION_WWWFORMURLDECODER_HPP_
