/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/Button.hpp"

namespace Titanium
{
	namespace UI
	{
		Button::Button(const JSContext& js_context, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
		    : View(js_context),
		      title__(js_context.CreateString())
		{
			TITANIUM_LOG_DEBUG("Button:: ctor ", this);
		}

		Button::~Button() TITANIUM_NOEXCEPT
		{
			TITANIUM_LOG_DEBUG("Button:: dtor ", this);
		}

		std::string Button::get_title() const TITANIUM_NOEXCEPT
		{
			return title__;
		}

		void Button::set_title(const std::string& title) TITANIUM_NOEXCEPT
		{
			title__ = title;
		}

		void Button::JSExportInitialize()
		{
			JSExport<Button>::SetClassVersion(1);
			JSExport<Button>::SetParent(JSExport<View>::Class());
			
			JSExport<Button>::AddFunctionProperty("setTitle", std::mem_fn(&Button::js_setTitle));

			JSExport<Button>::AddValueProperty("title", std::mem_fn(&Button::js_get_title), std::mem_fn(&Button::js_set_title));
		}

		JSValue Button::js_get_title() const TITANIUM_NOEXCEPT
		{
			return get_context().CreateString(title__);
		}

		bool Button::js_set_title(const JSValue& argument) TITANIUM_NOEXCEPT
		{
			TITANIUM_ASSERT(argument.IsString());
			const std::string title = static_cast<std::string>(argument);
			TITANIUM_LOG_DEBUG("Button::js_set_title: title = ", title);
			set_title(title);
			return true;
		}

		JSValue Properties::js_setTitle(const std::vector<JSValue>& arguments, JSObject& this_object) TITANIUM_NOEXCEPT
		{
			if (arguments.empty()) {
				return get_context().CreateUndefined();

			} else {
				const auto _0 = arguments.at(0);
				js_set_title(_0);
			}

			return get_context().CreateUndefined();
		}
	} // namespace UI
}  // namespace Titanium
