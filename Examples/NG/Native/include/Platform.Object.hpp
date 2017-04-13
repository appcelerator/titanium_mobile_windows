/**
 * Windows Native Wrapper for Platform.Object
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _PLATFORM_OBJECT_HPP_
#define _PLATFORM_OBJECT_HPP_

#include "TitaniumWindows_Native_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/Module.hpp"

namespace Titanium
{
	namespace Platform
	{


		using namespace HAL;

		class TITANIUMWINDOWS_NATIVE_EXPORT Object : public ::Titanium::Module, public JSExport<Object>
		{

		public:

			TITANIUM_FUNCTION_DEF(cast);

			Object(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Object() = default;
			Object(const Object&) = default;
			Object& operator=(const Object&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Object(Object&&)                 = default;
			Object& operator=(Object&&)      = default;
#endif

			static void JSExportInitialize();

			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			::Platform::Object^ unwrapPlatform_Object() const;
			void wrap(::Platform::Object^ object);

		protected:
			::Platform::Object^ wrapped__;

		private:
			::Platform::Object^ unwrap() const;

		};

	} // namespace Platform
} // namespace Titanium
#endif // _PLATFORM_OBJECT_HPP_
