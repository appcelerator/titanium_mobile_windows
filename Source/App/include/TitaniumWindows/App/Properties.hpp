/**
* Titanium.App.Properties for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUMWINDOWS_PROPERTIES_HPP_
#define _TITANIUMWINDOWS_PROPERTIES_HPP_

#include "TitaniumWindows/detail/AppBase.hpp"

using namespace Windows::Storage;
using namespace Windows::Foundation;

namespace TitaniumWindows
{
	namespace App
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium.App.Properties implementation for Windows.
		*/
		class TITANIUMWINDOWS_APP_EXPORT Properties final : public Titanium::App::Properties, public JSExport<Properties>{

		public:
			Properties(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Properties() = default;
			Properties(const Properties&) = default;
			Properties& operator=(const Properties&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Properties(Properties&&) = default;
			Properties& operator=(Properties&&) = default;
#endif

			static void JSExportInitialize();

		private:

			JSFunction stringify_function__;
			JSFunction createStringifyFunction(const JSContext& js_context) const TITANIUM_NOEXCEPT;

			virtual bool getBool(const std::string& property, bool default) TITANIUM_NOEXCEPT;
			virtual double getDouble(const std::string& property, double default) TITANIUM_NOEXCEPT;
			virtual double getInt(const std::string& property, double default) TITANIUM_NOEXCEPT;
			virtual JSValue getList(const std::string& property, JSValue default) TITANIUM_NOEXCEPT;
			virtual JSValue getObject(const std::string& property, JSValue default) TITANIUM_NOEXCEPT;
			virtual std::string getString(const std::string& property, const std::string& default) TITANIUM_NOEXCEPT;
			virtual bool hasProperty(const std::string& property) TITANIUM_NOEXCEPT;
			virtual JSValue listProperties() TITANIUM_NOEXCEPT;
			virtual void removeProperty(const std::string& property) TITANIUM_NOEXCEPT;
			virtual JSValue setBool(const std::string& property, bool value) TITANIUM_NOEXCEPT;
			virtual JSValue setDouble(const std::string& property, double value) TITANIUM_NOEXCEPT;
			virtual JSValue setInt(const std::string& property, int value) TITANIUM_NOEXCEPT;
			virtual JSValue setList(const std::string& property, JSValue value) TITANIUM_NOEXCEPT;
			virtual JSValue setObject(const std::string& property, JSValue value) TITANIUM_NOEXCEPT;
			virtual JSValue setString(const std::string& property, const std::string& value) TITANIUM_NOEXCEPT;

			ApplicationDataContainer^ local_settings_;

		};
	}
}  // namespace TitaniumWindows
#endif // _TITANIUMWINDOWS_PROPERTIES_HPP_