/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_GLOBALOBJECT_HPP_
#define _TITANIUM_GLOBALOBJECT_HPP_

#include "Titanium/detail/TiBase.hpp"
#include <chrono>
#include <memory>
#include <unordered_map>
#include <atomic>

namespace Titanium
{
	using namespace HAL;

	/*!
	  @class

	  @discussion This is the Titanium GlobalObject that implements the
	  Titanium API documented at
	  http://docs.appcelerator.com/titanium/latest/#!/api/Global.

	  Every Titanium platform provides a Platform Delegate that this
	  class delegates to for platform-specific capabilities.
	*/
	class TITANIUMKIT_EXPORT GlobalObject : public JSExportObject, public JSExport<GlobalObject>
	{
	public:
		/*!
		  @method

		  @abstract require( moduleId ) : Object

		  @discussion Loads either a native Titanium module, or a CommonJS
		  module.

		  The require function takes a module identifier as its argument
		  and returns an object with references to the module's exported
		  symbols.

		  To load a native Titanium module, use its module ID.

		  To load a local CommonJS module, use the relative path to the
		  file, minus the .js extension. The file path is relative to the
		  location of the file calling require.

		  Note that the appropriate platform-specific Resources
		  subdirectory is merged into the main Resources directory at build
		  time. For example, suppose the following files exist.

		  Resources/app.js
		  Resources/ui/MainWindow.js
		  Resources/iphone/ui/TaskWindow.js
		  Resources/android/ui/TaskWindow.js

		  The appropriate TaskWindow.js file is moved into the Resources/ui
		  directory of the built application. To include both the
		  MainWindow module and the platform-specific TaskWindow module,
		  then this code may be used in the app.js file:

		  // load main window module from ui subdirectory
		  var mainWindow = require('ui/MainWindow');

		  // load platform-specific task window module
		  var taskWindow = require('ui/TaskWindow');


		  On the other hand, to include the TaskWindow module from the
		  Resources/ui/MainWindow.js file:

		  // load task window module
		  var taskWindow = require('TaskWindow');

		  For more information, see the Official CommonJS website about
		  CommonJS Modules/1.1 Specification.

		  @param moduleId : Native module ID, or local path to a JavaScript
		  file, minus the .js extension (String).

		  @result Exported exports object of the required module (Object).
		*/
		virtual JSValue requireModule(const JSObject& parent, const std::string& moduleId, const bool& reload = false) final;

		/*!
		  @method

		  @abstract setTimeout( function, delay ) : Number

		  @discussion Executes code or a function after a delay. Note that
		  although the timeout is not guaranteed to be exact, the delay
		  before the function is invoked will be no less than the specified
		  delay. Returns a unique timer identifier that can be passed to
		  clearTimeout to cancel this timer. For more information, see the
		  MDN website for setTimeout.

		  @param function Code or function to call (Function).

		  @param delay Time in milliseconds to wait before the function is
		  called (Number).

		  @result Unique timer identifier (Number).
		*/
		virtual unsigned setTimeout(JSObject&& function, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT final;

		/*!
		  @method

		  @abstract clearTimeout( timerId ) : void

		  @discussion Cancels a one-time timer.

		  @param timerId Unique timer identifier returned by setTimeout
		  (Number).

		  @result void
		*/
		virtual void clearTimeout(const unsigned& timerId) TITANIUM_NOEXCEPT final;

		/*!
		  @method

		  @abstract setInterval( function, delay ) : Number

		  @discussion Executes a function repeatedly with a fixed time
		  delay between each call to that function. Note that although the
		  interval is not guaranteed to be exact, the interval between
		  calls will be no less than the specified delay. Returns a unique
		  timer identifier that can be passed to clearInterval to cancel
		  this timer. For more information, see the MDN website for
		  setInterval.

		  @param function Function to call (Function).

		  @param delay Time in milliseconds to wait between calls to
		  function (Number).

		  @result Unique timer identifier (Number).
		*/
		virtual unsigned setInterval(JSObject&& function, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT final;

		/*!
		  @method

		  @abstract clearInterval( timerId ) : void

		  @discussion Cancels an interval timer.

		  @param timerId Unique timer identifier returned by setInterval
		  (Number).

		  @result void
		*/
		virtual void clearInterval(const unsigned& timerId) TITANIUM_NOEXCEPT final;

		GlobalObject(const JSContext&) TITANIUM_NOEXCEPT;
		virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

		virtual ~GlobalObject() TITANIUM_NOEXCEPT;  //= default;
		GlobalObject(const GlobalObject&) = default;
		GlobalObject& operator=(const GlobalObject&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		GlobalObject(GlobalObject&&) = default;
		GlobalObject& operator=(GlobalObject&&) = default;
#endif

		// TODO: The following functions can automatically be generated
		// from the YAML API docs.
		static void JSExportInitialize();
		
		TITANIUM_PROPERTY_READONLY_DEF(global);
		TITANIUM_FUNCTION_DEF(require);
		TITANIUM_FUNCTION_DEF(setTimeout);
		TITANIUM_FUNCTION_DEF(clearTimeout);
		TITANIUM_FUNCTION_DEF(setInterval);
		TITANIUM_FUNCTION_DEF(clearInterval);

		using Callback_t = std::function<void()>;

		/*!
		  @class

		  @discussion This is an abstract base class used in the
		  implemenations of setTimeout, clearTimeout, setInterval and
		  clearInterval that native platforms must provide implementations
		  for.
		*/
		class TITANIUMKIT_EXPORT Timer
		{
		public:
			/*!
			  @method

			  @abstract Create a Timer instance that repeatedly calls the
			  given callback at the given interval after the Start method is
			  called.

			  @param callback The function to call repeatedly at the given
			  interval after the Start method is called.

			  @param interval The interval to repeatedly call the given
			  function after the Start method is called.
			*/
			Timer(Callback_t callback, const std::chrono::milliseconds& interval);

			virtual ~Timer() = default;
			Timer(const Timer&) = default;
			Timer& operator=(const Timer&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Timer(Timer&&) = default;
			Timer& operator=(Timer&&) = default;
#endif

			/*!
			  @method

			  @abstract Start calling the callback repeatedly at the given
			  interval.

			  @result void
			*/
			virtual void Start() TITANIUM_NOEXCEPT = 0;

			/*!
			  @method

			  @abstract Stop calling the callback repeatedly at the given
			  interval.

			  @result void
			*/
			virtual void Stop() TITANIUM_NOEXCEPT = 0;

			/*!
			  @method

			  @abstract Return the interval that the Timer was constructed
			  with.

			  @result The interval that the Timer was constructed with.
			*/
			virtual std::chrono::milliseconds get_interval() const TITANIUM_NOEXCEPT final;

		private:
// Silence 4251 on Windows since private member variables do not
// need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable : 4251)
			std::chrono::milliseconds interval__;
#pragma warning(pop)
		};

	protected:
		// Silence 4251 on Windows since private member variables do not
		// need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable : 4251)
		static const std::string COMMONJS_SEPARATOR__;
		static std::uint32_t require_nested_count__;
#pragma warning(pop)

		virtual std::string requestResolveModule(const JSObject& parent, const std::string& moduleId, const std::string& dirname = COMMONJS_SEPARATOR__) TITANIUM_NOEXCEPT;
		virtual std::string resolvePath(const std::string& path, const std::string& dir = COMMONJS_SEPARATOR__) const TITANIUM_NOEXCEPT final;
		virtual std::string resolvePathAsModule(const JSObject& parent, const std::string& resolvedPath, const std::string& dirname) const TITANIUM_NOEXCEPT final;
		virtual std::string resolvePathAsDirectory(const JSObject& parent, const std::string& resolvedPath) const TITANIUM_NOEXCEPT final;
		virtual std::string resolvePathAsFile(const JSObject& parent, const std::string& resolvedPath) const TITANIUM_NOEXCEPT final;
		virtual std::vector<std::string> resolveRequirePaths(const std::string& dirname) const TITANIUM_NOEXCEPT final;
    
		// platform-dependent functions
		virtual bool requiredModuleExists(const std::string& path) const TITANIUM_NOEXCEPT;
		virtual std::string readRequiredModule(const JSObject& parent, const std::string& path) const;

		// special module such as ti.map
		virtual bool requiredBuiltinModuleExists(const JSContext& js_context, const std::string& moduleId) const TITANIUM_NOEXCEPT;
		virtual JSValue requireBuiltinModule(const JSContext& js_context, const std::string& moduleId);

		// native module
		virtual bool requiredNativeModuleExists(const JSContext& js_context, const std::string& moduleId) const TITANIUM_NOEXCEPT;
		virtual JSValue requireNativeModule(const JSContext& js_context, const std::string& moduleId);

		/*!
		  @method

		  @abstract Create a Timer instance that repeatedly calls the given
		  callback at the given interval after its Start method is
		  called. Native platforms must implementat this method in order
		  for setTimeout, clearTimeout, setInterval and clearInterval to
		  function correctly.

		  @param callback The function to call repeatedly at the given
		  interval after the Timer's Start method is called.

		  @param interval The interval to repeatedly call the given
		  function after the Timer's Start method is called.

		  @result A std::shared_ptr<Timer> instance that repeatedly calls
		  the given callback at the given interval after its Start method
		  is called.
		*/
		virtual std::shared_ptr<Timer> CreateTimer(Callback_t callback, const std::chrono::milliseconds& interval) const TITANIUM_NOEXCEPT;

	private:

		void RegisterCallback(JSObject&& function, const unsigned& timerId) TITANIUM_NOEXCEPT;
		void UnregisterCallback(const unsigned& timerId) TITANIUM_NOEXCEPT;
		void InvokeCallback(const unsigned& timerId) TITANIUM_NOEXCEPT;
		void StartTimer(Callback_t&& callback, const unsigned& timerId, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT;
		void StopTimer(const unsigned& timerId) TITANIUM_NOEXCEPT;

// Silence 4251 on Windows since private member variables do not
// need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable : 4251)
		std::unordered_map<std::string, std::string> module_path_cache__;
		std::unordered_map<std::string, JSValue> module_cache__;
		std::string currentDir__;
		std::unordered_map<unsigned, std::shared_ptr<Timer>> timer_map__;
		std::unordered_map<unsigned, JSObject> timer_callback_map__;

		static std::atomic<unsigned> timer_id_generator__;
#pragma warning(pop)

#undef TITANIUM_GLOBALOBJECT_LOCK_GUARD
#ifdef TITANIUM_THREAD_SAFE
		std::recursive_mutex mutex__;
#define TITANIUM_GLOBALOBJECT_LOCK_GUARD std::lock_guard<std::recursive_mutex> lock(mutex__)
#else
#define TITANIUM_GLOBALOBJECT_LOCK_GUARD
#endif  // TITANIUM_THREAD_SAFE
	};

}  // namespace Titanium

#endif  // _TITANIUM_GLOBALOBJECT_HPP_
