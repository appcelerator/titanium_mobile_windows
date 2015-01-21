/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/ApplicationBuilder.hpp"
#include "Titanium/TiModule.hpp"
#include "Titanium/API.hpp"
#include "Titanium/UIModule.hpp"
#include "Titanium/PlatformModule.hpp"
#include "Titanium/Accelerometer.hpp"
#include "Titanium/Gesture.hpp"
#include "Titanium/Blob.hpp"
#include "Titanium/FilesystemModule.hpp"
#include "Titanium/Filesystem/File.hpp"
#include "Titanium/XML.hpp"

namespace Titanium
{
	ApplicationBuilder::ApplicationBuilder(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : js_context__(js_context),
	      global_object__(js_context__.get_global_object()),
	      ti__(js_context__.CreateObject<Titanium::TiModule>()),
	      api__(js_context__.CreateObject<Titanium::API>()),
	      view__(js_context__.CreateObject<Titanium::UI::View>()),
	      window__(js_context__.CreateObject<Titanium::UI::Window>()),
	      button__(js_context__.CreateObject<Titanium::UI::Button>()),
	      imageview__(js_context__.CreateObject<Titanium::UI::ImageView>()),
	      label__(js_context__.CreateObject<Titanium::UI::Label>()),
	      scrollview__(js_context__.CreateObject<Titanium::UI::ScrollView>()),
	      platform__(js_context__.CreateObject<Titanium::PlatformModule>()),
	      accelerometer__(js_context__.CreateObject<Titanium::Accelerometer>()),
	      gesture__(js_context__.CreateObject<Titanium::Gesture>()),
	      blob__(js_context__.CreateObject<Titanium::Blob>()),
	      file__(js_context__.CreateObject<Titanium::Filesystem::File>()),
	      filesystem__(js_context__.CreateObject<Titanium::FilesystemModule>()),
	      xml__(js_context__.CreateObject<Titanium::XML>())
	{
	}

	Application ApplicationBuilder::build()
	{
		JSObject ui = js_context__.CreateObject<Titanium::UIModule>();
		ui.SetProperty("View", view__);
		ui.SetProperty("Window", window__);
		ui.SetProperty("Button", button__);
		ui.SetProperty("ImageView", imageview__);
		ui.SetProperty("Label", label__);
		ui.SetProperty("ScrollView", scrollview__);

		filesystem__.SetProperty("File", file__);

		JSObject titanium = ti__;
		global_object__.SetProperty("Titanium", titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		global_object__.SetProperty("Ti", titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});

		titanium.SetProperty("API", api__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("UI", ui, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Platform", platform__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Accelerometer", accelerometer__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Gesture", gesture__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Blob", blob__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("Filesystem", filesystem__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		titanium.SetProperty("XML", xml__, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
		JSString builtin_functions_script = R"js(
      console = {};
      console.log   = Ti.API.info;
      console.info  = Ti.API.info;
      console.warn  = Ti.API.warn;
      console.error = Ti.API.error;
    )js";

		js_context__.JSEvaluateScript(builtin_functions_script);

		return Application(*this);
	}

	JSObject ApplicationBuilder::TiObject() const TITANIUM_NOEXCEPT
	{
		return ti__;
	}

	ApplicationBuilder& ApplicationBuilder::TiObject(const JSObject& ti) TITANIUM_NOEXCEPT
	{
		ti__ = ti;
		return *this;
	}

	JSObject ApplicationBuilder::APIObject() const TITANIUM_NOEXCEPT
	{
		return api__;
	}

	ApplicationBuilder& ApplicationBuilder::APIObject(const JSObject& api) TITANIUM_NOEXCEPT
	{
		api__ = api;
		return *this;
	}

	JSObject ApplicationBuilder::ViewObject() const TITANIUM_NOEXCEPT
	{
		return view__;
	}

	ApplicationBuilder& ApplicationBuilder::ViewObject(const JSObject& view) TITANIUM_NOEXCEPT
	{
		view__ = view;
		return *this;
	}

	JSObject ApplicationBuilder::WindowObject() const TITANIUM_NOEXCEPT
	{
		return window__;
	}

	ApplicationBuilder& ApplicationBuilder::WindowObject(const JSObject& window) TITANIUM_NOEXCEPT
	{
		window__ = window;
		return *this;
	}

	JSObject ApplicationBuilder::ButtonObject() const TITANIUM_NOEXCEPT
	{
		return button__;
	}

	ApplicationBuilder& ApplicationBuilder::ButtonObject(const JSObject& button) TITANIUM_NOEXCEPT
	{
		button__ = button;
		return *this;
	}

	JSObject ApplicationBuilder::ImageViewObject() const TITANIUM_NOEXCEPT
	{
		return imageview__;
	}

	ApplicationBuilder& ApplicationBuilder::ImageViewObject(const JSObject& imageview) TITANIUM_NOEXCEPT
	{
		imageview__ = imageview;
		return *this;
	}

	JSObject ApplicationBuilder::LabelObject() const TITANIUM_NOEXCEPT
	{
		return label__;
	}

	ApplicationBuilder& ApplicationBuilder::LabelObject(const JSObject& label) TITANIUM_NOEXCEPT
	{
		label__ = label;
		return *this;
	}

	JSObject ApplicationBuilder::ScrollViewObject() const TITANIUM_NOEXCEPT
	{
		return scrollview__;
	}

	ApplicationBuilder& ApplicationBuilder::ScrollViewObject(const JSObject& view) TITANIUM_NOEXCEPT
	{
		scrollview__ = view;
		return *this;
	}

	JSObject ApplicationBuilder::PlatformObject() const TITANIUM_NOEXCEPT
	{
		return platform__;
	}

	ApplicationBuilder& ApplicationBuilder::PlatformObject(const JSObject& platform) TITANIUM_NOEXCEPT
	{
		platform__ = platform;
		return *this;
	}

	JSObject ApplicationBuilder::AccelerometerObject() const TITANIUM_NOEXCEPT
	{
		return accelerometer__;
	}

	ApplicationBuilder& ApplicationBuilder::AccelerometerObject(const JSObject& accelerometer) TITANIUM_NOEXCEPT
	{
		accelerometer__ = accelerometer;
		return *this;
	}

	JSObject ApplicationBuilder::GestureObject() const TITANIUM_NOEXCEPT
	{
		return gesture__;
	}

	ApplicationBuilder& ApplicationBuilder::GestureObject(const JSObject& gesture) TITANIUM_NOEXCEPT
	{
		gesture__ = gesture;
		return *this;
	}

	JSObject ApplicationBuilder::BlobObject() const TITANIUM_NOEXCEPT
	{
		return blob__;
	}

	ApplicationBuilder& ApplicationBuilder::BlobObject(const JSObject& blob) TITANIUM_NOEXCEPT
	{
		blob__ = blob;
		return *this;
	}

	JSObject ApplicationBuilder::FileObject() const TITANIUM_NOEXCEPT
	{
		return file__;
	}

	ApplicationBuilder& ApplicationBuilder::FileObject(const JSObject& file) TITANIUM_NOEXCEPT
	{
		file__ = file;
		return *this;
	}

	JSObject ApplicationBuilder::FilesystemObject() const TITANIUM_NOEXCEPT
	{
		return filesystem__;
	}
	ApplicationBuilder& ApplicationBuilder::FilesystemObject(const JSObject& filesystem) TITANIUM_NOEXCEPT
	{
		filesystem__ = filesystem;
		return *this;
	}

	JSObject ApplicationBuilder::XMLObject() const TITANIUM_NOEXCEPT
	{
		return xml__;
	}

	ApplicationBuilder& ApplicationBuilder::XMLObject(const JSObject& xml) TITANIUM_NOEXCEPT
	{
		xml__ = xml;
		return *this;
	}
}  // namespace Titanium {
