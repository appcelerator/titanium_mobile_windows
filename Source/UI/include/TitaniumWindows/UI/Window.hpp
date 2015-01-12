/**
 * Titanium.UI.Window for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UI_WINDOW_HPP_
#define _TITANIUMWINDOWS_UI_WINDOW_HPP_

#include "TitaniumWindows/UI/detail/UIBase.hpp"
#include "ViewBase.hpp"

namespace TitaniumWindows { namespace UI {

	using namespace HAL;

	/*!
		@class

		@discussion This is the Titanium.UI.Window implementation for
		Windows.
		*/
	class TITANIUMWINDOWS_UI_EXPORT Window final : public Titanium::UI::Window, public JSExport < Window >, public ViewBase {

	public:

		virtual void open(const JSObject& params, JSObject& this_object) const TITANIUM_NOEXCEPT override final;
		virtual void add(const JSObject& view, JSObject& this_object) TITANIUM_NOEXCEPT;

		Window(const JSContext& js_context)													TITANIUM_NOEXCEPT;
		Window(const Window&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

		virtual ~Window();

		Window(const Window&) = default;
		Window& operator=(const Window&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		Window(Window&&)								 = default;
		Window& operator=(Window&&)			= default;
#endif

		static void JSExportInitialize();

		virtual void hide(JSObject& this_object) TITANIUM_NOEXCEPT;
		virtual void show(JSObject& this_object) TITANIUM_NOEXCEPT;

		virtual bool setBackgroundColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
		virtual bool setTopArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
		virtual bool setLeftArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
		virtual bool setWidthArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
		virtual bool setHeightArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;
		virtual bool setLayoutArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT override final;

		virtual void onLayoutEngineCallback(Titanium::LayoutEngine::Rect rect, const std::string& name);
		virtual void onComponentSizeChange(const Titanium::LayoutEngine::Rect&);

	private:

		Windows::UI::Xaml::Controls::Canvas^ canvas__;
	};

}}	// namespace TitaniumWindows { namespace UI {

#endif // _TITANIUMWINDOWS_UI_WINDOW_HPP_
