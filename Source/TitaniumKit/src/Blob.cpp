/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Blob.hpp"
#include <type_traits>

namespace Titanium
{
	Blob::Blob(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
	    : Module(js_context)
	{
	}

	void Blob::construct(std::vector<unsigned char> data) TITANIUM_NOEXCEPT
	{
	}

	std::vector<unsigned char> Blob::getData() TITANIUM_NOEXCEPT
	{
		return std::vector<unsigned char>();
	}

	void Blob::JSExportInitialize()
	{
		JSExport<Blob>::SetClassVersion(1);
		JSExport<Blob>::SetParent(JSExport<Module>::Class());
		JSExport<Blob>::AddValueProperty("length", std::mem_fn(&Blob::js_get_length));
		JSExport<Blob>::AddValueProperty("file", std::mem_fn(&Blob::js_get_file));
		JSExport<Blob>::AddValueProperty("height", std::mem_fn(&Blob::js_get_height));
		JSExport<Blob>::AddValueProperty("mimeType", std::mem_fn(&Blob::js_get_mimeType));
		JSExport<Blob>::AddValueProperty("nativePath", std::mem_fn(&Blob::js_get_nativePath));
		JSExport<Blob>::AddValueProperty("size", std::mem_fn(&Blob::js_get_size));
		JSExport<Blob>::AddValueProperty("text", std::mem_fn(&Blob::js_get_text));
		JSExport<Blob>::AddValueProperty("width", std::mem_fn(&Blob::js_get_width));

		JSExport<Blob>::AddFunctionProperty("getLength", std::mem_fn(&Blob::js_getLength));
		JSExport<Blob>::AddFunctionProperty("getFile", std::mem_fn(&Blob::js_getFile));
		JSExport<Blob>::AddFunctionProperty("getHeight", std::mem_fn(&Blob::js_getHeight));
		JSExport<Blob>::AddFunctionProperty("getMimeType", std::mem_fn(&Blob::js_getMimeType));
		JSExport<Blob>::AddFunctionProperty("getNativePath", std::mem_fn(&Blob::js_getNativePath));
		JSExport<Blob>::AddFunctionProperty("getSize", std::mem_fn(&Blob::js_getSize));
		JSExport<Blob>::AddFunctionProperty("getText", std::mem_fn(&Blob::js_getText));
		JSExport<Blob>::AddFunctionProperty("getWidth", std::mem_fn(&Blob::js_getWidth));

		JSExport<Blob>::AddFunctionProperty("append", std::mem_fn(&Blob::js_append));
		JSExport<Blob>::AddFunctionProperty("toString", std::mem_fn(&Blob::js_toString));
	}

	unsigned Blob::get_length() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Blob::get_length: Unimplemented");
		return 0;
	}

	JSValue Blob::get_file() const TITANIUM_NOEXCEPT
	{
		JSValue Titanium_property = get_context().get_global_object().GetProperty("Titanium");
		TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
		JSObject Titanium = static_cast<JSObject>(Titanium_property);

		JSValue Filesystem_property = Titanium.GetProperty("Filesystem");
		TITANIUM_ASSERT(Filesystem_property.IsObject());  // precondition
		JSObject Filesystem = static_cast<JSObject>(Filesystem_property);

		JSValue File_property = Filesystem.GetProperty("File");
		TITANIUM_ASSERT(File_property.IsObject());  // precondition
		JSObject File = static_cast<JSObject>(File_property);

		return File.CallAsConstructor(get_nativePath());
	}

	unsigned Blob::get_height() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Blob::get_height: Unimplemented");
		return 0;
	}

	std::string Blob::get_mimeType() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Blob::get_mimeType: Unimplemented");
		return "";
	}

	std::string Blob::get_nativePath() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Blob::get_nativePath: Unimplemented");
		return "";
	}

	unsigned Blob::get_size() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Blob::get_size: Unimplemented");
		return 0;
	}

	std::string Blob::get_text() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Blob::get_text: Unimplemented");
		return "";
	}

	unsigned Blob::get_width() const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Blob::get_width: Unimplemented");
		return 0;
	}

	void Blob::append(std::shared_ptr<Blob>&) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_WARN("Blob::append: Unimplemented");
	}

	JSValue Blob::js_get_length() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(get_length());
	}

	JSValue Blob::js_get_file() const TITANIUM_NOEXCEPT
	{
		return get_file();
	}

	JSValue Blob::js_get_height() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(get_height());
	}

	JSValue Blob::js_get_mimeType() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateString(get_mimeType());
	}

	JSValue Blob::js_get_nativePath() const TITANIUM_NOEXCEPT
	{
		const auto path = get_nativePath();
		if (path.size() > 0) {
			return get_context().CreateString(path);
		} else {
			return get_context().CreateNull();
		}
	}

	JSValue Blob::js_get_size() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(get_size());
	}

	JSValue Blob::js_get_text() const TITANIUM_NOEXCEPT
	{
		const auto text = get_text();
		if (text.size() > 0) {
			return get_context().CreateString(text);
		} else {
			return get_context().CreateNull();
		}
	}

	JSValue Blob::js_get_width() const TITANIUM_NOEXCEPT
	{
		return get_context().CreateNumber(get_width());
	}

	JSValue Blob::js_append(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		if (arguments.size() < 1) {
			return get_context().CreateUndefined();
		}
		const auto _0 = arguments.at(0);
		if (!_0.IsObject()) {
			return get_context().CreateUndefined();
		}
		const JSObject blob = static_cast<JSObject>(_0);
		auto blob_ptr = blob.GetPrivate<Blob>();
		TITANIUM_ASSERT(blob_ptr);
		append(blob_ptr);

		return get_context().CreateUndefined();
	}

	JSValue Blob::js_getFile(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_file();
	}

	JSValue Blob::js_getHeight(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_height();
	}

	JSValue Blob::js_getLength(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_length();
	}

	JSValue Blob::js_getMimeType(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_mimeType();
	}

	JSValue Blob::js_getNativePath(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_nativePath();
	}

	JSValue Blob::js_getSize(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_size();
	}

	JSValue Blob::js_getText(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_text();
	}

	JSValue Blob::js_getWidth(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_width();
	}

	JSValue Blob::js_toString(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
	{
		return js_get_text();
	}

}  // namespace Titanium
