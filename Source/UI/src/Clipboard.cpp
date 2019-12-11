/**
 * Titanium.UI.Clipboard for Windows
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/UI/Clipboard.hpp"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"

#include <boost/algorithm/string.hpp>
#include <concrt.h>

#if WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
using Windows::ApplicationModel::DataTransfer::Clipboard;
using Windows::ApplicationModel::DataTransfer::StandardDataFormats;
using Windows::ApplicationModel::DataTransfer::DataPackage;
#endif

namespace TitaniumWindows
{
	namespace UI
	{
		Clipboard::Clipboard(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
			: Titanium::UI::Clipboard(js_context, arguments)
		{
		}

		void Clipboard::JSExportInitialize() {
			JSExport<Clipboard>::SetClassVersion(1);
			JSExport<Clipboard>::SetParent(JSExport<Titanium::UI::Clipboard>::Class());
		}

		void Clipboard::clearData(const std::string& type) TITANIUM_NOEXCEPT
		{
#if WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
			Windows::ApplicationModel::DataTransfer::Clipboard::Clear();
#endif
		}

		void Clipboard::clearText() TITANIUM_NOEXCEPT
		{
#if WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
			Windows::ApplicationModel::DataTransfer::Clipboard::Clear();
#endif
		}

		JSObject Clipboard::getData(const std::string& type) TITANIUM_NOEXCEPT
		{
#if WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
			auto content = ::Clipboard::GetContent();

			if (boost::starts_with(type, "text") && content->Contains(::StandardDataFormats::Text)) {
				return static_cast<JSObject>(get_context().CreateValueFromJSON(getText()));
			}
#endif	
			return get_context().CreateObject();
		}

		std::string Clipboard::getText() TITANIUM_NOEXCEPT
		{
#if WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
			auto content = ::Clipboard::GetContent();
			Platform::String^ buffer;
			concurrency::event event;

			auto task = concurrency::create_task(content->GetTextAsync()).then([&event, &buffer](concurrency::task<Platform::String^> text) {
				try {
					buffer = text.get();
				} catch (Platform::Exception^ e) {
					TITANIUM_LOG_WARN(TitaniumWindows::Utility::ConvertString(e->Message));
				} catch (...) {
					TITANIUM_LOG_WARN("Unknown error at Clipboard.text");
				}
				event.set();
			}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return Utility::ConvertString(buffer);
#else
			return "";
#endif
		}

		bool Clipboard::hasData(const std::string& type) TITANIUM_NOEXCEPT
		{
#if WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
			auto content = ::Clipboard::GetContent();
			return content->Contains(::StandardDataFormats::Text);
#else
			return false;
#endif
		}

		bool Clipboard::hasText() TITANIUM_NOEXCEPT
		{
#if WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
			auto content = ::Clipboard::GetContent();
			return content->Contains(::StandardDataFormats::Text);
#else
			return false;
#endif
		}

		void Clipboard::setData(const std::string& type, JSObject data) TITANIUM_NOEXCEPT
		{
#if WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
			auto json = static_cast<std::string>(static_cast<JSValue>(data).ToJSONString());
			setText(json);
#endif
		}

		void Clipboard::setText(const std::string& text) TITANIUM_NOEXCEPT
		{
#if WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
			::DataPackage^ content = ref new ::DataPackage();
			content->SetText(Utility::ConvertString(text));
			::Clipboard::SetContent(content);
#endif
		}

	}  // namespace UI
}  // namespace TitaniumWindows