/**
 * TitaniumKit OpenWindowParams
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_OPENWINDOWPARAMS_HPP_
#define _TITANIUM_UI_OPENWINDOWPARAMS_HPP_

#include "Titanium/detail/TiBase.hpp"
#include "Titanium/Module.hpp"

namespace Titanium
{
	namespace UI
	{
		using namespace HAL;

		/*!
		  @struct
		  @discussion This is the OpenWindowParams.
		  Extend this struct to implement platform-specific properties like animation style.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/OpenWindowParams
		*/
		class TITANIUMKIT_EXPORT OpenWindowParams : public Module, public JSExport<OpenWindowParams>
		{
		public:
			virtual bool get_animated() const TITANIUM_NOEXCEPT;
			virtual void set_animated(const bool&) TITANIUM_NOEXCEPT;

			virtual bool get_fullscreen() const TITANIUM_NOEXCEPT;
			virtual void set_fullscreen(const bool&) TITANIUM_NOEXCEPT;

			virtual bool get_modal() const TITANIUM_NOEXCEPT;
			virtual void set_modal(const bool&) TITANIUM_NOEXCEPT;

			virtual bool get_navBarHidden() const TITANIUM_NOEXCEPT;
			virtual void set_navBarHidden(const bool&) TITANIUM_NOEXCEPT;

			virtual std::string get_top() const TITANIUM_NOEXCEPT;
			virtual void set_top(const std::string&) TITANIUM_NOEXCEPT;

			virtual std::string get_left() const TITANIUM_NOEXCEPT;
			virtual void set_left(const std::string&) TITANIUM_NOEXCEPT;

			virtual std::string get_bottom() const TITANIUM_NOEXCEPT;
			virtual void set_bottom(const std::string&) TITANIUM_NOEXCEPT;

			virtual std::string get_right() const TITANIUM_NOEXCEPT;
			virtual void set_right(const std::string&) TITANIUM_NOEXCEPT;

			virtual std::string get_width() const TITANIUM_NOEXCEPT;
			virtual void set_width(const std::string&) TITANIUM_NOEXCEPT;

			virtual std::string get_height() const TITANIUM_NOEXCEPT;
			virtual void set_height(const std::string&) TITANIUM_NOEXCEPT;

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments);

			OpenWindowParams(const JSContext&) TITANIUM_NOEXCEPT;
			
			virtual ~OpenWindowParams() = default;
			OpenWindowParams(const OpenWindowParams&) = default;
			OpenWindowParams& operator=(const OpenWindowParams&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			OpenWindowParams(OpenWindowParams&&) = default;
			OpenWindowParams& operator=(OpenWindowParams&&) = default;
#endif
			
			static void JSExportInitialize();
		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			bool animated__     {true};
			bool fullscreen__   {false};
			bool modal__        {false};
			bool navBarHidden__ {false};

			std::string top__;
			std::string left__;
			std::string bottom__;
			std::string right__;
			std::string width__;
			std::string height__;
#pragma warning(pop)
		};
		
	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_OPENWINDOWPARAMS_HPP_
