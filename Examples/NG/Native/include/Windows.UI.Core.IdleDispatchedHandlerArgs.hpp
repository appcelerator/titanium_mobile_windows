/**
 * Windows Native Wrapper for Windows.UI.Core.IdleDispatchedHandlerArgs
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_CORE_IDLEDISPATCHEDHANDLERARGS_HPP_
#define _WINDOWS_UI_CORE_IDLEDISPATCHEDHANDLERARGS_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Platform.Object.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace UI
		{
			namespace Core
			{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT IdleDispatchedHandlerArgs : public ::Titanium::Platform::Object, public JSExport<IdleDispatchedHandlerArgs>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(IsDispatcherIdle);


			IdleDispatchedHandlerArgs(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~IdleDispatchedHandlerArgs() = default;
			IdleDispatchedHandlerArgs(const IdleDispatchedHandlerArgs&) = default;
			IdleDispatchedHandlerArgs& operator=(const IdleDispatchedHandlerArgs&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			IdleDispatchedHandlerArgs(IdleDispatchedHandlerArgs&&)                 = default;
			IdleDispatchedHandlerArgs& operator=(IdleDispatchedHandlerArgs&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Core::IdleDispatchedHandlerArgs^ unwrapWindows_UI_Core_IdleDispatchedHandlerArgs() const;
			void wrap(::Windows::UI::Core::IdleDispatchedHandlerArgs^ object);

		private:
			::Windows::UI::Core::IdleDispatchedHandlerArgs^ unwrap() const;

		};

			} // namespace Core
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_CORE_IDLEDISPATCHEDHANDLERARGS_HPP_
