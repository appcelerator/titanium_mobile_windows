/**
* TitaniumKit Titanium.App.Properties
*
* Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/

#ifndef _TITANIUM_PROPERTIES_HPP_
#define _TITANIUM_PROPERTIES_HPP_

#include "Titanium/Module.hpp"
#include <boost/optional.hpp>

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
			virtual boost::optional<bool> getBool(const std::string& property, boost::optional<bool> defaultValue) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract getDouble
			  @discussion Returns the value of a property as a double (double-precision, floating point) data type.
			*/
			virtual boost::optional<double> getDouble(const std::string& property, boost::optional<double> defaultValue) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract getInt
			  @discussion Returns the value of a property as an integer data type.
			*/
			virtual boost::optional<double> getInt(const std::string& property, boost::optional<double> defaultValue) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract getList
			  @discussion Returns the value of a property as an array data type.
			*/
			virtual JSValue getList(const std::string& property, JSValue defaultValue) TITANIUM_NOEXCEPT final;
			/*!
			  @method
			  @abstract getObject
			  @discussion Returns the value of a property as an object.
			*/
			virtual JSValue getObject(const std::string& property, JSValue defaultValue) TITANIUM_NOEXCEPT final;
			/*!
			  @method
			  @abstract getString
			  @discussion Returns the value of a property as a string data type.
			*/
			virtual boost::optional<std::string> getString(const std::string& property, const boost::optional<std::string>& defaultValue) TITANIUM_NOEXCEPT;
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
			virtual std::vector<std::string> listProperties() TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract removeAllProperties
			  @discussion Removes all properties that have been set by the user on runtime, or does nothing otherwise.
			*/
			virtual void removeAllProperties() TITANIUM_NOEXCEPT;
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
			virtual void setBool(const std::string& property, bool value) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setDouble
			  @discussion Sets the value of a property as a double (double-precision, floating point) data type. The property will be created if it does not exist.
			*/
			virtual void setDouble(const std::string& property, double value) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setInt
			  @discussion Sets the value of a property as an integer data type. The property will be created if it does not exist.
			*/
			virtual void setInt(const std::string& property, int value) TITANIUM_NOEXCEPT;
			/*!
			  @method
			  @abstract setList
			  @discussion Sets the value of a property as an array data type. The property will be created if it does not exist.
			*/
			virtual void setList(const std::string& property, JSValue value) TITANIUM_NOEXCEPT final;
			/*!
			  @method
			  @abstract setObject
			  @discussion Sets the value of a property as an object data type. The property will be created if it does not exist.
			*/
			virtual void setObject(const std::string& property, JSValue value) TITANIUM_NOEXCEPT final;
			/*!
			  @method
			  @abstract setString
			  @discussion Sets the value of a property as a string data type. The property will be created if it does not exist.
			*/
			virtual void setString(const std::string& property, const std::string& value) TITANIUM_NOEXCEPT;


			virtual void loadAppProperties() TITANIUM_NOEXCEPT;
			TITANIUM_FUNCTION_DEF(_loadAppProperties);

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
			static JSObject GetStaticObject(const JSContext& js_context) TITANIUM_NOEXCEPT;

			TITANIUM_FUNCTION_DEF(getBool);
			TITANIUM_FUNCTION_DEF(getDouble);
			TITANIUM_FUNCTION_DEF(getInt);
			TITANIUM_FUNCTION_DEF(getList);
			TITANIUM_FUNCTION_DEF(getObject);
			TITANIUM_FUNCTION_DEF(getString);
			TITANIUM_FUNCTION_DEF(hasProperty);
			TITANIUM_FUNCTION_DEF(listProperties);
			TITANIUM_FUNCTION_DEF(removeAllProperties);
			TITANIUM_FUNCTION_DEF(removeProperty);
			TITANIUM_FUNCTION_DEF(setBool);
			TITANIUM_FUNCTION_DEF(setDouble);
			TITANIUM_FUNCTION_DEF(setInt);
			TITANIUM_FUNCTION_DEF(setList);
			TITANIUM_FUNCTION_DEF(setObject);
			TITANIUM_FUNCTION_DEF(setString);

		private:
			JSFunction stringify_function__;
			JSFunction createStringifyFunction(const JSContext& js_context) const TITANIUM_NOEXCEPT;
			JSObject app_properties__;

		};
	}
}
#endif // _TITANIUM_PROPERTIES_HPP_