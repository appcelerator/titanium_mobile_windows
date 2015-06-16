/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "Titanium/detail/TiUtil.hpp"
#include <sstream>
#include <functional>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/join.hpp>

namespace Titanium
{
	using namespace Titanium::detail;

	const std::string GlobalObject::COMMONJS_SEPARATOR__{"/"};
	std::atomic<std::uint32_t> GlobalObject::timer_id_generator__;

	JSFunction GlobalObject::createRequireFunction(const JSContext& js_context) const TITANIUM_NOEXCEPT
	{
		return js_context.CreateFunction(R"JS(
      var exports={},__OXP=exports,module={'exports':exports};
      eval(module_js);
      if(module.exports !== __OXP){
          return module.exports;
      }
      return exports;
      )JS",
		  {"__filename", "module_js"});
	}

	GlobalObject::GlobalObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : JSExportObject(js_context),
	      require_function__(createRequireFunction(js_context)),
	      callback_map__(js_context.CreateObject())
	{
		TITANIUM_LOG_DEBUG("GlobalObject:: ctor ", this);
	}

	void GlobalObject::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) {
		HAL_LOG_DEBUG("GlobalObject:: postCallAsConstructor ", this);
	}

	GlobalObject::~GlobalObject() TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("GlobalObject:: dtor ", this);
	}

	static std::vector<std::string> slice(const std::vector<std::string>& list, const size_t& begin, const size_t& end=std::string::npos)
	{
		std::vector<std::string> newlist;
		for (size_t i = begin; i < end; i++) {
			newlist.push_back(list[i]);
		}
		return newlist;
	}

	std::vector<std::string> GlobalObject::resolveRequirePaths(const std::string& dirname) const TITANIUM_NOEXCEPT
	{
		std::vector<std::string> paths;
		if (dirname == COMMONJS_SEPARATOR__) {
			paths.push_back("node_modules");
		} else {
#pragma warning(push)
#pragma warning(disable:4996)
			std::vector<std::string> parts;
			boost::split(parts, dirname, boost::is_any_of(COMMONJS_SEPARATOR__));
#pragma warning(pop)
			for (size_t i = 0, len = parts.size(); i < len; i++) {
				auto p = slice(parts, 0, len-i);
				auto path =  boost::algorithm::join(p, COMMONJS_SEPARATOR__) + "/node_modules";
				std::vector<std::string>::iterator it = paths.begin();
				paths.insert(it, path);
			}
		}
		return paths;
	}

	std::string GlobalObject::resolvePath(const std::string& path, const std::string& basedir) const TITANIUM_NOEXCEPT
	{
		std::string dir = basedir.length() == 1 || basedir.rfind(COMMONJS_SEPARATOR__) == basedir.length() ? basedir : basedir + COMMONJS_SEPARATOR__;
		const bool resolvedAbsolute = path.find(COMMONJS_SEPARATOR__)==0;

#pragma warning(push)
#pragma warning(disable:4996)
		std::vector<std::string> parts;
		boost::split(parts, path, boost::is_any_of(COMMONJS_SEPARATOR__));
#pragma warning(pop)

		size_t up = 0;
		const bool allowAboveRoot = !resolvedAbsolute;
		std::vector<std::string> newparts;
		for (std::vector<std::string>::reverse_iterator rit = parts.rbegin(); rit != parts.rend(); rit++) {
			std::string last = *rit;
			if (last == "") {
				// skip
			} else if (last == ".") {
				// skip
			} else if (last == "..") {
				// skip
				up++;
			} else if (up) {
				// skip
				up--;
			} else {
				std::vector<std::string>::iterator it = newparts.begin();
				newparts.insert(it, last);
			}
		}
			
		if (allowAboveRoot) {
			for (; up--;) {
				std::vector<std::string>::iterator it = newparts.begin();
				newparts.insert(it, "..");
			}
		}
			
		std::string newpath =  boost::algorithm::join(newparts, COMMONJS_SEPARATOR__);
		return resolvedAbsolute ? newpath : dir + newpath;
	}

	std::string GlobalObject::resolvePathAsFile(const JSObject& parent, const std::string& path) const TITANIUM_NOEXCEPT
	{
		std::vector<std::string> checks;
		checks.push_back(path);
		checks.push_back(path+".js");
		checks.push_back(path+".json");
		
		for (std::vector<std::string>::iterator i = checks.begin(); i!=checks.end(); i++) {
			auto check = *i;
			if (requiredModuleExists(check)) {
				return check;
			}
		}
		return std::string();
	}

	std::string GlobalObject::resolvePathAsDirectory(const JSObject& parent, const std::string& path) const TITANIUM_NOEXCEPT
	{
		const auto packageJSONFile = path + "/package.json";
		if (requiredModuleExists(packageJSONFile)) {
				const auto content = readRequiredModule(parent, packageJSONFile);
				const auto result = parent.get_context().CreateValueFromJSON(content);
				if (result.IsObject()) {
					const auto json = static_cast<JSObject>(result);
					auto mainValue = json.GetProperty("main");
					if (mainValue.IsString()) {
						return resolvePathAsFile(parent, path+COMMONJS_SEPARATOR__+static_cast<std::string>(mainValue));
					}
				}
		}
		const auto indexFile = path + "/index.js";
		if (requiredModuleExists(indexFile)) {
			return indexFile;
		}
		const auto indexJSON = path + "/index.json";
		if (requiredModuleExists(indexJSON)) {
			return indexJSON;
		}
		return std::string();
	}

	std::string GlobalObject::resolvePathAsModule(const JSObject& parent, const std::string& path, const std::string& dirname) const TITANIUM_NOEXCEPT
	{
		auto reqPaths = resolveRequirePaths(dirname);
		std::string modulePath;
		std::string resolvedPath = path;
		if (resolvedPath.find(COMMONJS_SEPARATOR__)!=0) {
			resolvedPath = COMMONJS_SEPARATOR__ + resolvedPath;
		}
		for (size_t i = 0, len = reqPaths.size(); i < len; i++) {
			auto newResolvedPath = reqPaths[i] + resolvedPath;
			modulePath = resolvePathAsFile(parent,newResolvedPath);
			if (!modulePath.empty()) {
				break;
			}
			modulePath = resolvePathAsDirectory(parent,newResolvedPath);
			if (!modulePath.empty()) {
				break;
			}
		}
		return modulePath;
	}

	std::string GlobalObject::requestResolveModule(const JSObject& parent, const std::string& moduleId, const std::string& dirname) TITANIUM_NOEXCEPT
	{
		auto isNodeModule = false;
		std::string rawPath;

		if (moduleId.find(COMMONJS_SEPARATOR__)==0) {
			rawPath = moduleId;
		} else if (moduleId.find("../") == 0 || moduleId.find("./") == 0) {
			rawPath = dirname + (dirname == COMMONJS_SEPARATOR__ ? "" : COMMONJS_SEPARATOR__) + moduleId;
		} else {
			isNodeModule = true;
			rawPath = moduleId;
		}

		const auto resolvedPath = resolvePath(rawPath,dirname);
		std::string modulePath;

		if (isNodeModule) {
			modulePath = resolvePathAsModule(parent,resolvedPath,dirname);
		} else {
			// load as file or load as directory
			modulePath = resolvePathAsFile(parent,resolvedPath);
			if (modulePath.empty()) {
				modulePath = resolvePathAsDirectory(parent,resolvedPath);
			}
		}
		return modulePath;
	}

	bool GlobalObject::requiredNativeModuleExists(const JSContext& js_context, const std::string& moduleId) const TITANIUM_NOEXCEPT
	{
		return false;
	}

	JSValue GlobalObject::requireNativeModule(const JSContext& js_context, const std::string& moduleId)
	{
		return js_context.CreateUndefined();
	}

	bool GlobalObject::requiredBuiltinModuleExists(const JSContext& js_context, const std::string& moduleId) const TITANIUM_NOEXCEPT
	{
		return false;
	}

	JSValue GlobalObject::requireBuiltinModule(const JSContext& js_context, const std::string& moduleId)
	{
		return js_context.CreateUndefined();
	}

	JSValue GlobalObject::requireModule(const JSObject& parent, const std::string& moduleId)
	{
		TITANIUM_GLOBALOBJECT_LOCK_GUARD;

		const auto js_context = parent.get_context();

		// check if we have special module such as ti.map
		if (requiredBuiltinModuleExists(js_context, moduleId)) {
			return requireBuiltinModule(js_context, moduleId);
		}

		// check if we have native module
		if (requiredNativeModuleExists(js_context, moduleId)) {
			return requireNativeModule(js_context, moduleId);
		}

		auto module_path = requestResolveModule(parent, moduleId);
		if (module_path.empty()) {
			// Fall back to assuming equivalent of "/" + moduleId?
			module_path = requestResolveModule(parent, "/" + moduleId);
			if (module_path.empty()) {
				detail::ThrowRuntimeError("require", "Could not load module " + moduleId);
			}
		}

		// check if we have already loaded the module
		if (module_cache__.find(module_path) != module_cache__.end()) {
			return module_cache__.at(module_path);
		}

		const auto module_js = readRequiredModule(parent, module_path);

		if (module_js.empty()) {
			detail::ThrowRuntimeError("require", "Could not load module " + moduleId);
		}

		try {
			JSValue result = js_context.CreateUndefined();
			if (boost::ends_with(module_path, ".json")){
				result = js_context.CreateValueFromJSON(module_js);
			} else if (js_context.JSCheckScriptSyntax(module_js, moduleId)) {
				const std::vector<JSValue> args = { js_context.CreateString(moduleId), js_context.CreateString(module_js) };
				result = require_function__(args, js_context.get_global_object());
			} else {
				detail::ThrowRuntimeError("require", "Could not load module "+moduleId);
			}
			if (!result.IsObject()) {
				TITANIUM_LOG_WARN("GlobalObject::require: module '", moduleId, "' replaced 'exports' with a non-object: ", to_string(result));
			}
			// cache it so that we can reuse it
			module_cache__.insert({module_path, result});
			return result;
		} catch (const std::exception& exception) {
			detail::ThrowRuntimeError("require", "Error while require("+moduleId+") "+static_cast<std::string>(exception.what()));
		} catch (...) {
			detail::ThrowRuntimeError("require", "Unknown error while require("+moduleId+")");
		}
		return js_context.CreateUndefined();
	}

	unsigned GlobalObject::setTimeout(JSObject&& function, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT
	{
		const auto timerId = timer_id_generator__++;

		RegisterCallback(std::move(function), timerId);

		Callback_t callback = [this, timerId]() mutable {
			InvokeCallback(timerId);
			clearTimeout(timerId);
		};

		StartTimer(std::move(callback), timerId, delay);

		return timerId;
	}

	void GlobalObject::clearTimeout(const unsigned& timerId) TITANIUM_NOEXCEPT
	{
		StopTimer(timerId);
	}

	unsigned GlobalObject::setInterval(JSObject&& function, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT
	{
		const auto timerId = timer_id_generator__++;

		RegisterCallback(std::move(function), timerId);

		Callback_t callback = [this, timerId]() mutable {
			InvokeCallback(timerId);
		};

		StartTimer(std::move(callback), timerId, delay);

		return timerId;
	}

	void GlobalObject::clearInterval(const unsigned& timerId) TITANIUM_NOEXCEPT
	{
		StopTimer(timerId);
	}

	void GlobalObject::RegisterCallback(JSObject&& function, const unsigned& timerId) TITANIUM_NOEXCEPT
	{
		const std::string timerId_str = "callback_" + std::to_string(timerId);
		TITANIUM_ASSERT(function.IsFunction());
		TITANIUM_ASSERT(!callback_map__.HasProperty(timerId_str));
		callback_map__.SetProperty(timerId_str, function);
	}

	void GlobalObject::UnregisterCallback(const unsigned& timerId) TITANIUM_NOEXCEPT
	{
		const std::string timerId_str = "callback_" + std::to_string(timerId);
		TITANIUM_ASSERT(callback_map__.HasProperty(timerId_str));
		const bool callback_deleted = callback_map__.DeleteProperty(timerId_str);
		TITANIUM_ASSERT(callback_deleted);
	}

	void GlobalObject::InvokeCallback(const unsigned& timerId) TITANIUM_NOEXCEPT
	{
		const std::string timerId_str = "callback_" + std::to_string(timerId);
		TITANIUM_ASSERT(callback_map__.HasProperty(timerId_str));
		JSValue callback_property = callback_map__.GetProperty(timerId_str);
		TITANIUM_ASSERT(callback_property.IsObject());
		JSObject callback = static_cast<JSObject>(callback_property);
		TITANIUM_ASSERT(callback.IsFunction());
		callback(get_context().get_global_object());
	}

	void GlobalObject::StartTimer(Callback_t&& callback, const unsigned& timerId, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT
	{
		auto timer = CreateTimer(callback, delay);
		const auto timer_insert_result = timer_map__.emplace(timerId, timer);
		const bool timer_inserted = timer_insert_result.second;
		TITANIUM_ASSERT(timer_inserted);
		TITANIUM_LOG_DEBUG("GlobalObject::setInterval: starting timer for timerId ", timerId);
		timer->Start();
	}

	void GlobalObject::StopTimer(const unsigned& timerId) TITANIUM_NOEXCEPT
	{
		const auto timer_position = timer_map__.find(timerId);
		const bool timer_found = timer_position != timer_map__.end();
		if (timer_found) {
			TITANIUM_LOG_DEBUG("GlobalObject::clearInterval: timerId ", timerId, " cleared");
			auto timer_ptr = timer_position->second;
			timer_ptr->Stop();
			const auto number_of_elements_removed = timer_map__.erase(timerId);
			TITANIUM_ASSERT(number_of_elements_removed == 1);

			const std::string timerId_str = "callback_" + std::to_string(timerId);
			TITANIUM_ASSERT(callback_map__.HasProperty(timerId_str));
			const bool callback_deleted = callback_map__.DeleteProperty(timerId_str);
			TITANIUM_ASSERT(callback_deleted);
		} else {
			TITANIUM_LOG_WARN("GlobalObject::clearTimeout: timerId ", timerId, " is not registered");
		}
	}
  
	bool GlobalObject::requiredModuleExists(const std::string& path) const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_ERROR("GlobalObject::requiredModuleExists: Unimplemented");
		return false;
	}

	std::string GlobalObject::readRequiredModule(const JSObject& parent, const std::string& path) const
	{
		TITANIUM_LOG_ERROR("GlobalObject::readRequiredModule: Unimplemented");
		return "";
	}

	GlobalObject::Timer::Timer(Callback_t callback, const std::chrono::milliseconds& interval)
	    : interval__(interval)
	{
		TITANIUM_LOG_DEBUG("GlobalObject::Timer: interval = ", interval.count(), "ms");
	}

	std::chrono::milliseconds GlobalObject::Timer::get_interval() const TITANIUM_NOEXCEPT
	{
		return interval__;
	}

	class UnimplementedTimer final : public GlobalObject::Timer
	{
	public:
		UnimplementedTimer(GlobalObject::Callback_t callback, const std::chrono::milliseconds& interval)
		    : Timer(callback, interval)
		{
			TITANIUM_LOG_ERROR("GlobalObject::Timer: Unimplemented");
		}

		virtual ~UnimplementedTimer()
		{
		}

		virtual void Start() TITANIUM_NOEXCEPT override final
		{
			TITANIUM_LOG_ERROR("GlobalObject::Timer::Start: Unimplemented");
		}

		virtual void Stop() TITANIUM_NOEXCEPT override final
		{
			TITANIUM_LOG_ERROR("GlobalObject::Timer::Stop: Unimplemented");
		}
	};

	std::shared_ptr<GlobalObject::Timer> GlobalObject::CreateTimer(Callback_t callback, const std::chrono::milliseconds& interval) const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_ERROR("GlobalObject::CreateTimer: Unimplemented");
		return std::make_shared<UnimplementedTimer>(callback, interval);
	}

	// TODO: The following functions can automatically be generated from
	// the YAML API docs.

	void GlobalObject::JSExportInitialize()
	{
		TITANIUM_LOG_DEBUG("GlobalObject::JSExportInitialize");
		JSExport<GlobalObject>::SetClassVersion(1);
		JSExport<GlobalObject>::SetParent(JSExport<JSExportObject>::Class());
		
		TITANIUM_ADD_PROPERTY_READONLY(GlobalObject, global);
		TITANIUM_ADD_FUNCTION(GlobalObject, require);
		TITANIUM_ADD_FUNCTION(GlobalObject, setTimeout);
		TITANIUM_ADD_FUNCTION(GlobalObject, clearTimeout);
		TITANIUM_ADD_FUNCTION(GlobalObject, setInterval);
		TITANIUM_ADD_FUNCTION(GlobalObject, clearInterval);
	}

	TITANIUM_PROPERTY_GETTER(GlobalObject, global)
	{
		return get_context().JSEvaluateScript("this;");
	}

	TITANIUM_FUNCTION(GlobalObject, require)
	{
		// TODO: Validate these precondition checks (which could be
		// automaticaly generated) with the team.
		ENSURE_STRING_AT_INDEX(moduleId, 0);

		const auto global_object = this_object.get_context().get_global_object();
		const auto global_ptr = global_object.GetPrivate<GlobalObject>();
		TITANIUM_ASSERT(global_ptr);

		return global_ptr->requireModule(this_object, moduleId);
	}

	TITANIUM_FUNCTION(GlobalObject, setTimeout)
	{
		// TODO: Validate these precondition checks (which could be
		// automaticaly generated) with the team.
		ENSURE_OBJECT_AT_INDEX(function, 0);
		ENSURE_UINT_AT_INDEX(delay, 1);
		
		const auto chrono_delay = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(delay));

		const auto global_object = this_object.get_context().get_global_object();
		const auto global_ptr = global_object.GetPrivate<GlobalObject>();
		TITANIUM_ASSERT(global_ptr);

		return this_object.get_context().CreateNumber(global_ptr->setTimeout(std::move(function), chrono_delay));
	}

	TITANIUM_FUNCTION(GlobalObject, clearTimeout)
	{
		// TODO: Validate these precondition checks (which could be
		// automaticaly generated) with the team.
		ENSURE_UINT_AT_INDEX(timerId, 0);

		const auto global_object = this_object.get_context().get_global_object();
		const auto global_ptr = global_object.GetPrivate<GlobalObject>();
		TITANIUM_ASSERT(global_ptr);

		global_ptr->clearTimeout(timerId);

		return this_object.get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(GlobalObject, setInterval)
	{
		// TODO: Validate these precondition checks (which could be
		// automaticaly generated) with the team.
		
		ENSURE_OBJECT_AT_INDEX(function, 0);
		ENSURE_UINT_AT_INDEX(delay, 1);

		TITANIUM_ASSERT(function.IsFunction());
		const auto chrono_delay = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(delay));

		const auto global_object = this_object.get_context().get_global_object();
		const auto global_ptr = global_object.GetPrivate<GlobalObject>();
		TITANIUM_ASSERT(global_ptr);

		return this_object.get_context().CreateNumber(global_ptr->setInterval(std::move(function), chrono_delay));
	}

	TITANIUM_FUNCTION(GlobalObject, clearInterval)
	{
		// TODO: Validate these precondition checks (which could be
		// automaticaly generated) with the team.
		ENSURE_UINT_AT_INDEX(timerId, 0);

		const auto global_object = this_object.get_context().get_global_object();
		const auto global_ptr = global_object.GetPrivate<GlobalObject>();
		TITANIUM_ASSERT(global_ptr);

		global_ptr->clearInterval(timerId);

		return this_object.get_context().CreateUndefined();
	}

}  // namespace Titanium
