/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_BUTTON_HPP_
#define _TITANIUM_UI_BUTTON_HPP_

#include "Titanium/UI/View.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium UI Button.

		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.Button
		*/
		class TITANIUMKIT_EXPORT Button : public View, public JSExport<Button>
		{
		public:

			/*!
			  @method

			  @abstract title : String

			  @discussion Button title.
			*/
			virtual std::string get_title() const TITANIUM_NOEXCEPT final;
			virtual void set_title(const std::string& title) TITANIUM_NOEXCEPT;

			Button(const JSContext&, const std::vector<JSValue>& arguments = {}) TITANIUM_NOEXCEPT;

			virtual ~Button() TITANIUM_NOEXCEPT;  //= default;
			Button(const Button&) = default;
			Button& operator=(const Button&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Button(Button&&) = default;
			Button& operator=(Button&&) = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_get_title() const TITANIUM_NOEXCEPT final;
			virtual bool js_set_title(const JSValue& argument) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setTitle(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string title__;
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_BUTTON_HPP_
