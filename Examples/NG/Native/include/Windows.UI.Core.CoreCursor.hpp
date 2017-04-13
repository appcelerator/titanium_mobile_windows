/**
 * Windows Native Wrapper for Windows.UI.Core.CoreCursor
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _WINDOWS_UI_CORE_CORECURSOR_HPP_
#define _WINDOWS_UI_CORE_CORECURSOR_HPP_

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

		class TITANIUMWINDOWS_NATIVE_EXPORT CoreCursor : public ::Titanium::Platform::Object, public JSExport<CoreCursor>
		{

		public:
			TITANIUM_PROPERTY_READONLY_DEF(Id);
			TITANIUM_PROPERTY_READONLY_DEF(Type);


			CoreCursor(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~CoreCursor() = default;
			CoreCursor(const CoreCursor&) = default;
			CoreCursor& operator=(const CoreCursor&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			CoreCursor(CoreCursor&&)                 = default;
			CoreCursor& operator=(CoreCursor&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Windows::UI::Core::CoreCursor^ unwrapWindows_UI_Core_CoreCursor() const;
			void wrap(::Windows::UI::Core::CoreCursor^ object);

		private:
			::Windows::UI::Core::CoreCursor^ unwrap() const;

		};

			} // namespace Core
		} // namespace UI
	} // namespace Windows
} // namespace Titanium
#endif // _WINDOWS_UI_CORE_CORECURSOR_HPP_
