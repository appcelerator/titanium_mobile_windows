/**
 * TitaniumKit
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_APPLICATIONBUILDER_HPP_
#define _TITANIUM_APPLICATIONBUILDER_HPP_

#include "Titanium/Application.hpp"
#include <memory>

namespace Titanium
{
	using namespace HAL;

	class TITANIUMKIT_EXPORT ApplicationBuilder final
	{
	public:
		ApplicationBuilder(const JSContext& js_context) TITANIUM_NOEXCEPT;
		Application build();

		JSObject TiObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& TiObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject APIObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& APIObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject AppObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& AppObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject PropertiesObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& PropertiesObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject ViewObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& ViewObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject WindowObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& WindowObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject ButtonObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& ButtonObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject ImageViewObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& ImageViewObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject LabelObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& LabelObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject SliderObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& SliderObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject AlertDialogObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& AlertDialogObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject ScrollViewObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& ScrollViewObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject TextFieldObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& TextFieldObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject PlatformObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& PlatformObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject AccelerometerObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& AccelerometerObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject GestureObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& GestureObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject BlobObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& BlobObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject FileObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& FileObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject FilesystemObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& FilesystemObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject DatabaseObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& DatabaseObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject WebViewObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& WebViewObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject HTTPClientObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& HTTPClientObject(const JSObject&) TITANIUM_NOEXCEPT;

		JSObject NetworkObject() const TITANIUM_NOEXCEPT;
		ApplicationBuilder& NetworkObject(const JSObject&) TITANIUM_NOEXCEPT;

		virtual ~ApplicationBuilder() = default;
		ApplicationBuilder(const ApplicationBuilder&) = default;
		ApplicationBuilder& operator=(const ApplicationBuilder&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		ApplicationBuilder(ApplicationBuilder&&) = default;
		ApplicationBuilder& operator=(ApplicationBuilder&&) = default;
#endif

	private:
		friend class Application;

// Silence 4251 on Windows since private member variables do not
// need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable : 4251)
		JSContext js_context__;
		JSObject global_object__;
		JSObject ti__;
		JSObject api__;
		JSObject view__;
		JSObject properties__;
		JSObject app__;
		JSObject window__;
		JSObject button__;
		JSObject alertDialog__;
		JSObject imageview__;
		JSObject label__;
		JSObject slider__;
		JSObject scrollview__;
		JSObject textField__;
		JSObject platform__;
		JSObject accelerometer__;
		JSObject gesture__;
		JSObject blob__;
		JSObject file__;
		JSObject filesystem__;
		JSObject database__;
		JSObject webview__;
		JSObject httpclient__;
		JSObject network__;
		
#pragma warning(pop)
	};

}  // namespace Titanium

#endif  // _TITANIUM_APPLICATIONBUILDER_HPP_
