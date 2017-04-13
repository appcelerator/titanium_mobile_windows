/**
 * Windows Native Wrapper for Windows.UI.Core.CoreCursor
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Windows.UI.Core.CoreCursor.hpp"
#include "Titanium/detail/TiImpl.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Core
			{

		CoreCursor::CoreCursor(const JSContext& js_context) TITANIUM_NOEXCEPT
			: Titanium::Platform::Object(js_context)
		{
			TITANIUM_LOG_DEBUG("CoreCursor::ctor");
		}

		void CoreCursor::postCallAsConstructor(const JSContext& context, const std::vector<JSValue>& arguments)
		{
			TITANIUM_LOG_DEBUG("CoreCursor::postCallAsConstructor ", this);
			if (arguments.size() == 2) {
				auto _0 = arguments.at(0);
			TITANIUM_ASSERT_AND_THROW(_0.IsNumber(), "Expected Number");
			auto type = static_cast<::Windows::UI::Core::CoreCursorType>(static_cast<int32_t>(_0)); // TODO Look up enum in metadata to know what type it's value is? 
				auto _1 = arguments.at(1); 
			TITANIUM_ASSERT_AND_THROW(_1.IsNumber(), "Expected Number");
			auto id = static_cast<uint32_t>(_1);

				wrapped__ = ref new ::Windows::UI::Core::CoreCursor(type, id);
			}

		}

		::Windows::UI::Core::CoreCursor^ CoreCursor::unwrapWindows_UI_Core_CoreCursor() const
		{
			return dynamic_cast<::Windows::UI::Core::CoreCursor^>(wrapped__);
		}

		::Windows::UI::Core::CoreCursor^ CoreCursor::unwrap() const
		{
			return unwrapWindows_UI_Core_CoreCursor();
		}

		void CoreCursor::wrap(::Windows::UI::Core::CoreCursor^ object)
		{
			wrapped__ = object;
		}

		void CoreCursor::JSExportInitialize()
		{
			JSExport<CoreCursor>::SetClassVersion(1);
			JSExport<CoreCursor>::SetParent(JSExport<Titanium::Platform::Object>::Class());

			TITANIUM_ADD_PROPERTY_READONLY(CoreCursor, Id);
			TITANIUM_ADD_PROPERTY_READONLY(CoreCursor, Type);
		}

		TITANIUM_PROPERTY_GETTER(CoreCursor, Id)
		{
			auto value = unwrap()->Id;
			auto context = get_context();
 
			auto result = context.CreateNumber(value);

			return result;
		}

		TITANIUM_PROPERTY_GETTER(CoreCursor, Type)
		{
			auto value = unwrap()->Type;
			auto context = get_context();

			auto result = context.CreateNumber(static_cast<int32_t>(static_cast<int>(value))); // FIXME What if the enum isn't an int based one?!

			return result;
		}

			} // namespace Core
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
