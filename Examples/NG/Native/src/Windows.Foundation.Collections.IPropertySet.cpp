/**
 * Windows Native Wrapper for Windows.Foundation.Collections.IPropertySet
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.Foundation.Collections.IPropertySet.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace Foundation
		{
			namespace Collections
			{

		IPropertySet::IPropertySet(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("IPropertySet::ctor");
		}

		void IPropertySet::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("IPropertySet::postCallAsConstructor ", this);

		}

		::Windows::Foundation::Collections::IPropertySet^ IPropertySet::unwrapWindows_Foundation_Collections_IPropertySet() const
		{
			return dynamic_cast<::Windows::Foundation::Collections::IPropertySet^>(wrapped__);
		}

		::Windows::Foundation::Collections::IPropertySet^ IPropertySet::unwrap() const
		{
			return unwrapWindows_Foundation_Collections_IPropertySet();
		}

		void IPropertySet::wrap(::Windows::Foundation::Collections::IPropertySet^ object)
		{
			wrapped__ = object;
		}

		void IPropertySet::JSExportInitialize()
		{
			JSExport<IPropertySet>::SetClassVersion(1);
			JSExport<IPropertySet>::SetParent(JSExport<Titanium::Platform::Object>::Class());

		}

			} // namespace Collections
		} // namespace Foundation
	} // namespace Windows
} // namespace Titanium
