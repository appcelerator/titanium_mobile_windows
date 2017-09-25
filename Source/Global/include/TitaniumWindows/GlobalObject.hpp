/**
 * Global for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_GLOBALOBJECT_HPP_
#define _TITANIUMWINDOWS_GLOBALOBJECT_HPP_

#include "TitaniumWindows_Global_EXPORT.h"
#include "Titanium/GlobalObject.hpp"

namespace TitaniumWindows
{
	using namespace HAL;

	/*!
	  @class GlobalObject
	  @ingroup Global

	  @discussion This is the Titanium GlobalObject implementation for
	  Windows.
	*/
	class TITANIUMWINDOWS_GLOBAL_EXPORT GlobalObject final : public Titanium::GlobalObject, public JSExport<GlobalObject>
	{
	public:

		GlobalObject(const JSContext&) TITANIUM_NOEXCEPT;

		virtual ~GlobalObject() = default;
		GlobalObject(const GlobalObject&) = default;
		GlobalObject& operator=(const GlobalObject&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
		GlobalObject(GlobalObject&&) = default;
		GlobalObject& operator=(GlobalObject&&) = default;
#endif

		virtual unsigned setTimeout(JSObject& function, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT override;
		virtual unsigned setInterval(JSObject& function, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT override;
		virtual void clearTimeout(const unsigned& timerId) TITANIUM_NOEXCEPT override;
		virtual void clearInterval(const unsigned& timerId) TITANIUM_NOEXCEPT override;

		static void JSExportInitialize();
		void setSeed(::Platform::String^ seed);
		virtual std::string readRequiredModule(const JSObject& parent, const std::string& path) const override final;
		virtual void registerNativeModuleRequireHook(const std::vector<std::string>& supported_module_names, const std::unordered_map<std::string, JSValue>& preloaded_modules, std::function<JSValue(const JSContext&, const std::string&)> requireCallback);

	protected:
#pragma warning(push)
#pragma warning(disable : 4251)
		// store supported module names and its loaded status
		std::unordered_map<std::string, bool> native_module_names__;

		// cache for native module
		std::unordered_map<std::string, JSValue> native_module_cache__;
		std::function<JSValue(const JSContext& js_context, const std::string&)> native_module_requireHook__;

		Windows::Foundation::Collections::IMap<unsigned, Windows::System::Threading::ThreadPoolTimer^>^ timer_dispatcher_map__;
		std::unordered_map<unsigned, JSObject> timer_callback_map__;
		static std::atomic<unsigned> timer_id_generator__;

#pragma warning(pop)

		// native module
		virtual bool requiredNativeModuleExists(const JSContext& js_context, const std::string& moduleId) const TITANIUM_NOEXCEPT override;
		virtual JSValue requireNativeModule(const JSContext& js_context, const std::string& moduleId) TITANIUM_NOEXCEPT override;

		virtual bool requiredModuleExists(const std::string& path) const TITANIUM_NOEXCEPT override final;

		unsigned invokeTimerCallback(JSObject& function, const std::chrono::milliseconds& delay, const bool isSetTimeout) TITANIUM_NOEXCEPT;

	private:
		::Platform::String^ seed__;
	};

}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_GLOBALOBJECT_HPP_
