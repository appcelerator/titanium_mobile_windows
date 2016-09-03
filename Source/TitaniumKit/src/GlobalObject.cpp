/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "Titanium/detail/TiUtil.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Module.hpp"
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
	std::uint32_t GlobalObject::require_nested_count__ = 0;

	GlobalObject::GlobalObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : JSExportObject(js_context)
		, currentDir__(COMMONJS_SEPARATOR__)
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
			TITANIUM_LOG_DEBUG("package.json exists");
			const auto content = readRequiredModule(parent, packageJSONFile);
			TITANIUM_LOG_DEBUG("Content: " + content);
			const auto result = parent.get_context().CreateValueFromJSON(content);
			if (result.IsObject()) {
				TITANIUM_LOG_DEBUG("Result from loading JSON is an object");
				const auto json = static_cast<JSObject>(result);
				auto mainValue = json.GetProperty("main");
				if (mainValue.IsString()) {
					TITANIUM_LOG_DEBUG("main: " + static_cast<std::string>(mainValue));
					const auto resolved = resolvePath(static_cast<std::string>(mainValue), path);
					return resolvePathAsFile(parent, resolved);
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
		std::string modulePath;
		std::string resolvedPath = path;
		// First look for "legacy" CommonJS module as node_modules/moduleId/moduleId.js
		modulePath = resolvePathAsFile(parent, "node_modules" + COMMONJS_SEPARATOR__ + resolvedPath + COMMONJS_SEPARATOR__ + resolvedPath);
		if (!modulePath.empty()) {
			return modulePath;
		}

		// Now try looking up the node_modules paths
		auto reqPaths = resolveRequirePaths(dirname);
		if (resolvedPath.find(COMMONJS_SEPARATOR__)!=0) {
			resolvedPath = COMMONJS_SEPARATOR__ + resolvedPath;
		}
		for (size_t i = 0, len = reqPaths.size(); i < len; i++) {
			auto newResolvedPath = reqPaths[i] + resolvedPath;
			modulePath = resolvePathAsFile(parent,newResolvedPath);
			if (!modulePath.empty()) {
				return modulePath;
			}
			modulePath = resolvePathAsDirectory(parent,newResolvedPath);
			if (!modulePath.empty()) {
				return modulePath;
			}
		}
		return modulePath;
	}

	std::string GlobalObject::requestResolveModule(const JSObject& parent, const std::string& moduleId, const std::string& dirname) TITANIUM_NOEXCEPT
	{
		// Create unique key for the dirname + moduleId, assuming moduleId does not contain whitespace.
		const auto modulePathCacheKey = dirname + " " + moduleId;
		const auto cached = module_path_cache__.find(modulePathCacheKey);
		if (cached != module_path_cache__.end()) {
			return cached->second;
		}

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

		module_path_cache__.emplace(modulePathCacheKey, modulePath);

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
		if (moduleId == "ti.map") {
			return true;
		}
		return false;
	}

	JSValue GlobalObject::requireBuiltinModule(const JSContext& js_context, const std::string& moduleId)
	{
		if (moduleId == "ti.map") {
			JSValue Titanium_property = js_context.get_global_object().GetProperty("Titanium");
			TITANIUM_ASSERT(Titanium_property.IsObject());  // precondition
			JSObject Titanium = static_cast<JSObject>(Titanium_property);

			JSValue Map_property = Titanium.GetProperty("Map");
			TITANIUM_ASSERT(Map_property.IsObject());  // precondition

			return Map_property;
		}

		return js_context.CreateUndefined();
	}

	JSValue GlobalObject::requireModule(const JSObject& parent, const std::string& moduleId, const bool& reload)
	{
		TITANIUM_GLOBALOBJECT_LOCK_GUARD;
		const auto js_context = parent.get_context();

		TITANIUM_LOG_DEBUG(std::string(require_nested_count__, '-') + " require(" + moduleId + ") from ", currentDir__);

		// check if we have special module such as ti.map
		if (requiredBuiltinModuleExists(js_context, moduleId)) {
			return requireBuiltinModule(js_context, moduleId);
		}

		// check if we have native module
		if (requiredNativeModuleExists(js_context, moduleId)) {
			return requireNativeModule(js_context, moduleId);
		}

		// FIXME We should be able to ask for the parent module's filename property to determine the dirname!
		// Parent here seems to _always_ be the global object.
		std::string dirname = currentDir__;

		auto module_path = requestResolveModule(parent, moduleId, dirname);
		if (module_path.empty() && moduleId.find(".") != 0 && moduleId.find("/") != 0) {
			// Fall back to assuming equivalent of "/" + moduleId (legacy behavior) if we don't already have a leading . or /
			module_path = requestResolveModule(parent, "/" + moduleId);
		}
		if (module_path.empty()) {
			detail::ThrowRuntimeError("require", "Could not load module " + moduleId);
		}

		// check if we have already loaded the module
		if (!reload && module_cache__.find(module_path) != module_cache__.end()) {
			return module_cache__.at(module_path);
		}

		// FIXME We need to create a new Module object where we set the filename and parent on it after resolving the filename
		// This should be what we use for parent object in sub-require() calls
		// Node basically hangs a special require and resolve function off each module object
		// the require call has references to the __dirname, __filename, parent, global, etc
		//JSObject module = js_context.CreateObject();

		const auto module_js = readRequiredModule(parent, module_path);

		if (module_js.empty()) {
			detail::ThrowRuntimeError("require", "Could not load module " + moduleId);
		}

		// Update currentDir__ pointer
		std::size_t found = module_path.rfind(COMMONJS_SEPARATOR__);
		if (found != std::string::npos) {
			currentDir__ = COMMONJS_SEPARATOR__ + module_path.substr(0, found); //  Take the dirname of this, not the full filename
		}
		else {
			currentDir__ = COMMONJS_SEPARATOR__;
		}

		try {
			JSValue result = js_context.CreateUndefined();
			if (boost::ends_with(module_path, ".json")){
				result = js_context.CreateValueFromJSON(module_js);
			} else if (js_context.JSCheckScriptSyntax(module_js, moduleId)) {
				//
				// app entry point should not be treated as "CommonJS module". It should expose every variables to children.
				//
				if (moduleId == "/app") {
					result = js_context.JSEvaluateScript(module_js, js_context.get_global_object());
				} else {
					const std::string require_module_js = "(function(global) { var exports={},__OXP=exports,module={'exports':exports},__dirname='" + currentDir__ + "';__filename='/"
						+ module_path + "';" + module_js + R"JS(
						if(module.exports !== __OXP){
							return module.exports;
						} else {
							return exports;
						}
					})(this);
					)JS";
					result = js_context.JSEvaluateScript(require_module_js, js_context.get_global_object(), module_path);
				}
			} else {
				currentDir__ = dirname; // Should ensure this gets reset on _EVERY_ code branch possible here. Would be nice if C++/CX had finally blocks
				detail::ThrowRuntimeError("require", "Could not load module "+moduleId);
			}
			currentDir__ = dirname; // Should ensure this gets reset on _EVERY_ code branch possible here. Would be nice if C++/CX had finally blocks
			if (!result.IsObject()) {
				TITANIUM_LOG_WARN("GlobalObject::require: module '", moduleId, "' replaced 'exports' with a non-object: ", to_string(result));
			}
			// cache it so that we can reuse it
			module_cache__.insert({module_path, result});
			return result;
		} catch (const std::exception& exception) {
			currentDir__ = dirname; // Should ensure this gets reset on _EVERY_ code branch possible here. Would be nice if C++/CX had finally blocks
			detail::ThrowRuntimeError("require", "Error while require("+moduleId+") "+static_cast<std::string>(exception.what()));
		} catch (...) {
			currentDir__ = dirname; // Should ensure this gets reset on _EVERY_ code branch possible here. Would be nice if C++/CX had finally blocks
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
		TITANIUM_ASSERT(function.IsFunction());
		TITANIUM_ASSERT(timer_callback_map__.find(timerId) == timer_callback_map__.end());
		timer_callback_map__.emplace(timerId, function);
	}

	void GlobalObject::UnregisterCallback(const unsigned& timerId) TITANIUM_NOEXCEPT
	{
		TITANIUM_ASSERT(timer_callback_map__.find(timerId) != timer_callback_map__.end());
		timer_callback_map__.erase(timerId);
	}

	void GlobalObject::InvokeCallback(const unsigned& timerId) TITANIUM_NOEXCEPT
	{
		TITANIUM_EXCEPTION_CATCH_START{
			const auto found = timer_callback_map__.find(timerId);
			TITANIUM_ASSERT(found != timer_callback_map__.end());
			auto callback = found->second;
			TITANIUM_ASSERT(callback.IsFunction());
			callback(get_context().get_global_object());
		} TITANIUM_EXCEPTION_CATCH_END
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

			TITANIUM_ASSERT(timer_callback_map__.find(timerId) != timer_callback_map__.end());
			timer_callback_map__.erase(timerId);
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
		ENSURE_STRING_AT_INDEX(moduleId, 0);

		const auto global_object = this_object.get_context().get_global_object();
		const auto global_ptr = global_object.GetPrivate<GlobalObject>();
		TITANIUM_ASSERT(global_ptr);

		require_nested_count__++;
		const auto module = global_ptr->requireModule(this_object, moduleId);
		require_nested_count__--;
		return module;
	}

	TITANIUM_FUNCTION(GlobalObject, setTimeout)
	{
		ENSURE_OBJECT_AT_INDEX(function, 0);
		ENSURE_OPTIONAL_UINT_AT_INDEX(delay, 1, 0);

		const auto chrono_delay = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(delay));

		const auto global_object = this_object.get_context().get_global_object();
		const auto global_ptr = global_object.GetPrivate<GlobalObject>();
		TITANIUM_ASSERT(global_ptr);

		return this_object.get_context().CreateNumber(global_ptr->setTimeout(std::move(function), chrono_delay));
	}

	TITANIUM_FUNCTION(GlobalObject, clearTimeout)
	{
		ENSURE_UINT_AT_INDEX(timerId, 0);

		const auto global_object = this_object.get_context().get_global_object();
		const auto global_ptr = global_object.GetPrivate<GlobalObject>();
		TITANIUM_ASSERT(global_ptr);

		global_ptr->clearTimeout(timerId);

		return this_object.get_context().CreateUndefined();
	}

	TITANIUM_FUNCTION(GlobalObject, setInterval)
	{
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
		ENSURE_UINT_AT_INDEX(timerId, 0);

		const auto global_object = this_object.get_context().get_global_object();
		const auto global_ptr = global_object.GetPrivate<GlobalObject>();
		TITANIUM_ASSERT(global_ptr);

		global_ptr->clearInterval(timerId);

		return this_object.get_context().CreateUndefined();
	}

}  // namespace Titanium
