/**
 * Windows Native Wrapper for Windows.Foundation.AsyncActionCompletedHandler
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_FOUNDATION_ASYNCACTIONCOMPLETEDHANDLER_HPP_
#define _WINDOWS_FOUNDATION_ASYNCACTIONCOMPLETEDHANDLER_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Platform.Object.hpp"

namespace Titanium
{
	namespace Windows
	{
		namespace Foundation
		{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT AsyncActionCompletedHandler : public ::Titanium::Platform::Object, public JSExport<AsyncActionCompletedHandler>
		{

		public:

			TITANIUM_FUNCTION_DEF(Invoke);

			AsyncActionCompletedHandler(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~AsyncActionCompletedHandler() = default;
			AsyncActionCompletedHandler(const AsyncActionCompletedHandler&) = default;
			AsyncActionCompletedHandler& operator=(const AsyncActionCompletedHandler&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			AsyncActionCompletedHandler(AsyncActionCompletedHandler&&)                 = default;
			AsyncActionCompletedHandler& operator=(AsyncActionCompletedHandler&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::Foundation::AsyncActionCompletedHandler^ unwrapWindows_Foundation_AsyncActionCompletedHandler() const;
			void wrap(::Windows::Foundation::AsyncActionCompletedHandler^ object);

		private:
			::Windows::Foundation::AsyncActionCompletedHandler^ unwrap() const;

		};

		} // namespace Foundation
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_FOUNDATION_ASYNCACTIONCOMPLETEDHANDLER_HPP_
