/**
 * Windows Native Wrapper for Windows.UI.Core.IdleDispatchedHandler
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_CORE_IDLEDISPATCHEDHANDLER_HPP_
#define _WINDOWS_UI_CORE_IDLEDISPATCHEDHANDLER_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT IdleDispatchedHandler : public ::Titanium::Platform::Object, public JSExport<IdleDispatchedHandler>
		{

		public:

			TITANIUM_FUNCTION_DEF(Invoke);

			IdleDispatchedHandler(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~IdleDispatchedHandler() = default;
			IdleDispatchedHandler(const IdleDispatchedHandler&) = default;
			IdleDispatchedHandler& operator=(const IdleDispatchedHandler&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			IdleDispatchedHandler(IdleDispatchedHandler&&)                 = default;
			IdleDispatchedHandler& operator=(IdleDispatchedHandler&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Core::IdleDispatchedHandler^ unwrapWindows_UI_Core_IdleDispatchedHandler() const;
			void wrap(::Windows::UI::Core::IdleDispatchedHandler^ object);

		private:
			::Windows::UI::Core::IdleDispatchedHandler^ unwrap() const;

		};

			} // namespace Core
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_CORE_IDLEDISPATCHEDHANDLER_HPP_
