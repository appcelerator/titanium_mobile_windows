/**
 * Windows Native Wrapper for Windows.Foundation.IWwwFormUrlDecoderEntry
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_FOUNDATION_IWWWFORMURLDECODERENTRY_HPP_
#define _WINDOWS_FOUNDATION_IWWWFORMURLDECODERENTRY_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT IWwwFormUrlDecoderEntry : public ::Titanium::Platform::Object, public JSExport<IWwwFormUrlDecoderEntry>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(Name);
			TITANIUM_PROPERTY_READONLY_DEF(Value);


			IWwwFormUrlDecoderEntry(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~IWwwFormUrlDecoderEntry() = default;
			IWwwFormUrlDecoderEntry(const IWwwFormUrlDecoderEntry&) = default;
			IWwwFormUrlDecoderEntry& operator=(const IWwwFormUrlDecoderEntry&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			IWwwFormUrlDecoderEntry(IWwwFormUrlDecoderEntry&&)                 = default;
			IWwwFormUrlDecoderEntry& operator=(IWwwFormUrlDecoderEntry&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::Foundation::IWwwFormUrlDecoderEntry^ unwrapWindows_Foundation_IWwwFormUrlDecoderEntry() const;
			void wrap(::Windows::Foundation::IWwwFormUrlDecoderEntry^ object);

		private:
			::Windows::Foundation::IWwwFormUrlDecoderEntry^ unwrap() const;

		};

		} // namespace Foundation
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_FOUNDATION_IWWWFORMURLDECODERENTRY_HPP_
