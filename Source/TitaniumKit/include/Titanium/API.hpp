/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_API_HPP_
#define _TITANIUM_API_HPP_

#include "Titanium/Module.hpp"

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class

	  @discussion This is the Titanium API Module.

	  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.API
	*/
	class TITANIUMKIT_EXPORT API : public Module, public JSExport<API>
	{
	public:
		/*!
		  @method

		  @abstract info( message ) : void

		  @discussion Logs messages with an 'info' severity-level.

		  @param message Message to log. Accepts an array on iOS
		  only. (String[]/String)

		  @result void
		*/
		virtual void info(const std::string& message) const TITANIUM_NOEXCEPT final;

		/*!
		  @method

		  @abstract warn( message ) : void

		  @discussion Logs messages with a 'warn' severity-level.

		  @param message Message to log. Accepts an array on iOS
		  only. (String[]/String)

		  @result void
		*/
		virtual void warn(const std::string& message) const TITANIUM_NOEXCEPT final;

		/*!
		  @method

		  @abstract error( message ) : void

		  @discussion Logs messages with an 'error' severity-level.

		  @param message Message to log. Accepts an array on iOS
		  only. (String[]/String)

		  @result void
		*/
		virtual void error(const std::string& message) const TITANIUM_NOEXCEPT final;

		/*!
		  @method

		  @abstract debug( message ) : void

		  @discussion Logs messages with a 'debug' severity-level.

		  @param message Message to log. Accepts an array on iOS
		  only. (String[]/String)

		  @result void
		*/
		virtual void debug(const std::string& message) const TITANIUM_NOEXCEPT final;

		/*!
		  @method

		  @abstract trace( message ) : void

		  @discussion Logs messages with a 'trace' severity-level.

		  @param message Message to log. Accepts an array on iOS
		  only. (String[]/String)

		  @result void
		 */
		virtual void trace(const std::string& message) const TITANIUM_NOEXCEPT final;

		/*!
		  @method

		  @abstract log( level, message ) : void

		  @discussion Logs messages with the specified severity-level.

		  @param level One of 'info', 'warn', 'error', 'debug' and
		  'trace'. If the value is not recognized, an info-level message
		  prefixed with the value is logged. (String)

		  @param message Message to log. Accepts an array on iOS
		  only. (String[]/String)

		  @result void
		*/
		virtual void log(const std::string& level, const std::string& message) const TITANIUM_NOEXCEPT final;

		API(const JSContext&) TITANIUM_NOEXCEPT;
		virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

		virtual ~API() TITANIUM_NOEXCEPT;  //= default;
		API(const API&) = default;
		API& operator=(const API&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		API(API&&) = default;
		API& operator=(API&&) = default;
#endif

		// TODO: The following functions can automatically be generated from
		// the YAML API docs.
		static void JSExportInitialize();
		JSValue js_info(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_warn(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_error(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_debug(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_trace(const std::vector<JSValue>& arguments, JSObject& this_object);
		JSValue js_log(const std::vector<JSValue>& arguments, JSObject& this_object);

	protected:
		virtual void log(const std::string& message) const TITANIUM_NOEXCEPT;

	private:
		enum class LogSeverityLevel {
			API_INFO,
			API_WARN,
			API_ERROR,
			API_DEBUG,
			API_TRACE
		};

		void log(LogSeverityLevel log_severity_level, const std::string& message) const TITANIUM_NOEXCEPT;

		static LogSeverityLevel ToLogLevel(const std::string& level);
	};

}  // namespace Titanium

#endif  // _TITANIUM_API_HPP_
