/**
* Titanium.App.Properties for Windows
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUM_PROPERTIES_HPP_
#define _TITANIUM_PROPERTIES_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	namespace App
	{
		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium Properties Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.App.Properties
		*/
		class TITANIUMKIT_EXPORT Properties : public Module, public JSExport<Properties> {

		public:

			/*!
			  @method
			  @abstract getBool
			  @discussion Returns the value of a property as a boolean data type.
			*/
			virtual bool getBool(const std::string& property, bool defaultValue) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract getDouble
			  @discussion Returns the value of a property as a double (double-precision, floating point) data type.
			*/
			virtual double getDouble(const std::string& property, double defaultValue) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract getInt
			  @discussion Returns the value of a property as an integer data type.
			*/
			virtual double getInt(const std::string& property, double defaultValue) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract getList
			  @discussion Returns the value of a property as an array data type.
			*/
			virtual JSValue getList(const std::string& property, JSValue defaultValue) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract getObject
			  @discussion Returns the value of a property as an object.
			*/
			virtual JSValue getObject(const std::string& property, JSValue defaultValue) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract getString
			  @discussion Returns the value of a property as a string data type.
			*/
			virtual std::string getString(const std::string& property, const std::string& defaultValue) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract hasProperty
			  @discussion Indicates whether a property exists.
			*/
			virtual bool hasProperty(const std::string& property) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract listProperties
			  @discussion Returns an array of property names.
			*/
			virtual JSValue listProperties() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract removeProperty
			  @discussion Removes a property if it exists, or does nothing otherwise.
			*/
			virtual void removeProperty(const std::string& property) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setBool
			  @discussion Sets the value of a property as a boolean data type. The property will be created if it does not exist.
			*/
			virtual JSValue setBool(const std::string& property, bool value) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setDouble
			  @discussion Sets the value of a property as a double (double-precision, floating point) data type. The property will be created if it does not exist.
			*/
			virtual JSValue setDouble(const std::string& property, double value) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setInt
			  @discussion Sets the value of a property as an integer data type. The property will be created if it does not exist.
			*/
			virtual JSValue setInt(const std::string& property, int value) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setList
			  @discussion Sets the value of a property as an array data type. The property will be created if it does not exist.
			*/
			virtual JSValue setList(const std::string& property, JSValue value) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setObject
			  @discussion Sets the value of a property as an object data type. The property will be created if it does not exist.
			*/
			virtual JSValue setObject(const std::string& property, JSValue value) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setString
			  @discussion Sets the value of a property as a string data type. The property will be created if it does not exist.
			*/
			virtual JSValue setString(const std::string& property, const std::string& value) TITANIUM_NOEXCEPT;

			Properties(const JSContext&) TITANIUM_NOEXCEPT;
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual ~Properties() = default;
			Properties(const Properties&) = default;
			Properties& operator=(const Properties&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Properties(Properties&&) = default;
			Properties& operator=(Properties&&) = default;
#endif

			static void JSExportInitialize();

			virtual JSValue js_getBool(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getDouble(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getInt(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getList(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getObject(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_getString(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_hasProperty(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_listProperties(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_removeProperty(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setBool(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setDouble(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setInt(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setList(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setObject(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;
			virtual JSValue js_setString(const std::vector<JSValue>&, JSObject&) TITANIUM_NOEXCEPT final;

		};
	}
}
#endif // _TITANIUM_PROPERTIES_HPP_