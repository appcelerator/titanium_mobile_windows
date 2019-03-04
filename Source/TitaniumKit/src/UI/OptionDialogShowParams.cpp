/**
 * TitaniumKit OptionDialogShowParams
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/UI/OptionDialogShowParams.hpp"
#include "Titanium/UI/View.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		OptionDialogShowParams js_to_OptionDialogShowParams(const JSObject& object)
		{
			OptionDialogShowParams dict;
			if (object.HasProperty("animated")) {
				dict.animated = static_cast<bool>(object.GetProperty("animated"));
			}
			if (object.HasProperty("rect")) {
				dict.rect = js_to_Dimension(static_cast<JSObject>(object.GetProperty("rect")));
			}
			if (object.HasProperty("view")) {
				dict.view = static_cast<JSObject>(object.GetProperty("view")).GetPrivate<Titanium::UI::View>();
			}
			return dict;
		};

		JSObject OptionDialogShowParams_to_js(const JSContext& js_context, const OptionDialogShowParams& dict)
		{
			auto object = js_context.CreateObject();
			object.SetProperty("animated", js_context.CreateBoolean(dict.animated));
			object.SetProperty("rect", Dimension_to_js(js_context, dict.rect));
			object.SetProperty("view", dict.view->get_object());
			return object;
		};
	} // namespace UI
} // namespace Titanium
