/**
 * Windows Native Wrapper for Windows.Foundation.Collections.IPropertySet
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_FOUNDATION_COLLECTIONS_IPROPERTYSET_HPP_
#define _WINDOWS_FOUNDATION_COLLECTIONS_IPROPERTYSET_HPP_

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
			namespace Collections
			{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT IPropertySet : public ::Titanium::Platform::Object, public JSExport<IPropertySet>
		{

		public:


			IPropertySet(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~IPropertySet() = default;
			IPropertySet(const IPropertySet&) = default;
			IPropertySet& operator=(const IPropertySet&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			IPropertySet(IPropertySet&&)                 = default;
			IPropertySet& operator=(IPropertySet&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::Foundation::Collections::IPropertySet^ unwrapWindows_Foundation_Collections_IPropertySet() const;
			void wrap(::Windows::Foundation::Collections::IPropertySet^ object);

		private:
			::Windows::Foundation::Collections::IPropertySet^ unwrap() const;

		};

			} // namespace Collections
		} // namespace Foundation
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_FOUNDATION_COLLECTIONS_IPROPERTYSET_HPP_
