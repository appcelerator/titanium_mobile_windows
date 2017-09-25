/**
 * Global for Windows
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/GlobalObject.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "Titanium/Module.hpp"
#include <ratio>
#include <sstream>
#include <concrt.h>
#include <collection.h>
#include <boost/algorithm/string.hpp>
#include "TitaniumWindows/Utility.hpp"
#include "TitaniumWindows/LogForwarder.hpp"

using Windows::Security::Cryptography::Core::SymmetricAlgorithmNames;
using Windows::Security::Cryptography::Core::SymmetricKeyAlgorithmProvider;
using Windows::Security::Cryptography::Core::CryptographicKey;
using Windows::Security::Cryptography::CryptographicBuffer;
using Windows::Security::Cryptography::BinaryStringEncoding;
using Windows::Storage::Streams::IBuffer;
using Windows::Security::Cryptography::Core::CryptographicEngine;
using Windows::Storage::Streams::DataReader;
using Windows::Storage::Streams::UnicodeEncoding;
using Windows::Storage::StorageFile;
using Windows::Storage::FileIO;
using concurrency::task_continuation_context;

namespace TitaniumWindows
{
	std::atomic<std::uint32_t> GlobalObject::timer_id_generator__;

	unsigned GlobalObject::setTimeout(JSObject& function, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT
	{
		return invokeTimerCallback(function, delay, true);
	}

	unsigned GlobalObject::setInterval(JSObject& function, const std::chrono::milliseconds& delay) TITANIUM_NOEXCEPT
	{
		return invokeTimerCallback(function, delay, false);
	}

	void GlobalObject::clearTimeout(const unsigned& timerId) TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("clearTimeout: ", timerId);

		const bool timer_found = timer_dispatcher_map__->HasKey(timerId);

		// dispatcher won't be found when interval equals zero
		if (timer_found) {
			timer_dispatcher_map__->Lookup(timerId)->Cancel();
			timer_dispatcher_map__->Remove(timerId);
		}

		if (timer_callback_map__.find(timerId) != timer_callback_map__.end()) {
			timer_callback_map__.erase(timerId);
		}
	}

	void GlobalObject::clearInterval(const unsigned& timerId) TITANIUM_NOEXCEPT
	{
		clearTimeout(timerId);
	}

	unsigned GlobalObject::invokeTimerCallback(JSObject& function, const std::chrono::milliseconds& delay, const bool isSetTimeout) TITANIUM_NOEXCEPT
	{
		const auto timerId = timer_id_generator__++;
		timer_callback_map__.emplace(timerId, function);

		std::function<void()> run = [this, timerId, delay, function, isSetTimeout]() {
			TitaniumWindows::Utility::RunOnUIThread(Windows::UI::Core::CoreDispatcherPriority::High, [this, timerId, delay, function, isSetTimeout]() {
				TITANIUM_EXCEPTION_CATCH_START{
					TITANIUM_LOG_DEBUG((isSetTimeout ? "setTimeout" : "setInterval"), ": id=", timerId, " delay=", delay.count());
					const auto found = timer_callback_map__.find(timerId);

					//
					// This could happen when setInterval/Timeout is cleared while waiting for invocation.
					// In that case we can just ignore the callback.
					//
					if (found == timer_callback_map__.end()) {
						TITANIUM_LOG_DEBUG("setInterval/Timeout is cleared while waiting for invocation: ", timerId);
						return;
					}

					auto callback = found->second;
					TITANIUM_ASSERT(callback.IsFunction());
					callback(get_context().get_global_object());

					if (isSetTimeout) {
						clearTimeout(timerId);
					}
				} TITANIUM_EXCEPTION_CATCH_END
			});
		};

		//
		// Invoke callback immediately when interval equals zero
		//
		if (delay.count() == 0) {
			run();
			return timerId;
		}

		// A Windows::Foundation::TimeSpan is a time period expressed in
		// 100-nanosecond units.
		//
		// Reference:
		// http://msdn.microsoft.com/en-us/library/windows/apps/windows.foundation.timespan
		std::chrono::duration<std::chrono::nanoseconds::rep, std::ratio_multiply<std::ratio<100>, std::nano>> timer_interval_ticks = delay;

		Windows::Foundation::TimeSpan time_span;
		time_span.Duration = timer_interval_ticks.count();
		auto dispatcher_timer = Windows::System::Threading::ThreadPoolTimer::CreatePeriodicTimer(
			ref new Windows::System::Threading::TimerElapsedHandler([run](Windows::System::Threading::ThreadPoolTimer ^timer) {
			run();
		}), time_span);

		timer_dispatcher_map__->Insert(timerId, dispatcher_timer);

		return timerId;
	}


	void GlobalObject::registerNativeModuleRequireHook(const std::vector<std::string>& native_module_names, const std::unordered_map<std::string, JSValue>& preloaded_modules, std::function<JSValue(const JSContext&, const std::string&)> requireHook)
	{
		// store supported native module names
		for (const auto v : native_module_names) {
			const auto insert_result = native_module_names__.emplace(v,  false);
			TITANIUM_ASSERT(insert_result.second);
		}

		// register preloaded modules
		for (const auto v : preloaded_modules) {
			const auto insert_result = native_module_cache__.emplace(v.first,  v.second);
			TITANIUM_ASSERT(insert_result.second);
			native_module_names__[v.first] = true; // mark it as loaded
		}

		// register require callback
		native_module_requireHook__ = requireHook;
	}

	bool GlobalObject::requiredNativeModuleExists(const JSContext& js_context, const std::string& moduleId) const TITANIUM_NOEXCEPT
	{
		return native_module_names__.find(moduleId) != native_module_names__.end();
	}

	JSValue GlobalObject::requireNativeModule(const JSContext& js_context, const std::string& moduleId) TITANIUM_NOEXCEPT
	{
		// if we already cached the module, just return the instance
		if (native_module_cache__.find(moduleId) != native_module_cache__.end()) {
			return native_module_cache__.at(moduleId);
		}

		TITANIUM_ASSERT(native_module_names__.find(moduleId) != native_module_names__.end());

		// mark it as loaded
		native_module_names__[moduleId] = true;

		// otherwise try to load dynamically
		return native_module_requireHook__(js_context, moduleId);
	}

	static Platform::String^ resolve(const std::string& path) 
	{
		const auto newpath = TitaniumWindows::Utility::ConvertUTF8String(boost::algorithm::replace_all_copy(boost::algorithm::replace_all_copy(path, "/", "\\"), "\\\\", "\\"));

		if (!boost::contains(path, ":")) {
			Windows::ApplicationModel::Package^ package = Windows::ApplicationModel::Package::Current;
			Windows::Storage::StorageFolder^ installed_location = package->InstalledLocation;
			Platform::String^ location = installed_location->Path;
			// If we are given a path that starts with a slash then the the returned
			// path will contain \\\\, on 8.1 this will throw an error when getting
			// the file in readRequiredModule
			if (path.find("/") == 0 || path.find("\\") == 0) {
				return location + newpath;
			}
			return location + "\\" + newpath;
		}
		return newpath;
	}

	bool GlobalObject::requiredModuleExists(const std::string& path) const TITANIUM_NOEXCEPT
	{
		auto module_path = resolve(path);
		TITANIUM_LOG_DEBUG("GlobalObject::requiredModuleExists: ", TitaniumWindows::Utility::ConvertUTF8String(module_path));

		bool exists = false;
		concurrency::event event;
		concurrency::task<Windows::Storage::StorageFile^>(Windows::Storage::StorageFile::GetFileFromPathAsync(module_path)).then([&exists, &event](concurrency::task<Windows::Storage::StorageFile^> task) {
			try {
				task.get();
				exists = true;
			} catch (...) {
				exists = false;
			}
			event.set();
		}, concurrency::task_continuation_context::use_arbitrary());
		event.wait();

		return exists;
	}

	void GlobalObject::setSeed(::Platform::String^ seed)
	{
		seed__ = seed;
	}

	std::string GlobalObject::readRequiredModule(const JSObject& parent, const std::string& path) const
	{
		auto module_path = resolve(path);
		TITANIUM_LOG_DEBUG("GlobalObject::loadRequiredModule: module_path = ", Utility::ConvertUTF8String(module_path));

		Platform::String^ content;
		bool hasError = false;
		concurrency::event event;

		if (seed__ == nullptr || seed__->IsEmpty()) {
			concurrency::task<StorageFile^>(StorageFile::GetFileFromPathAsync(module_path))
				.then([&content, &hasError, &event](concurrency::task<StorageFile^> task) {
					try {
						concurrency::task<Platform::String^>(FileIO::ReadTextAsync(task.get(), UnicodeEncoding::Utf8))
							.then([&content, &hasError, &event](concurrency::task<Platform::String^> task) {
								content = task.get();
								event.set();
							}, concurrency::task_continuation_context::use_arbitrary());
					} catch (...) {
						hasError = true;
						event.set();
					}
				}, concurrency::task_continuation_context::use_arbitrary());
			event.wait();
		} else {
			IBuffer^ file_buffer = nullptr;
			IBuffer^ iv_buffer = nullptr;
			bool encrypted = false;

			concurrency::task<StorageFile^>(
				// read file
				StorageFile::GetFileFromPathAsync(module_path))
				.then([](StorageFile^ file) {
					return FileIO::ReadBufferAsync(file);
				}, task_continuation_context::use_arbitrary())

				// set file buffer
				.then([&file_buffer, &module_path](IBuffer^ buffer) {
					file_buffer = buffer;
					return StorageFile::GetFileFromPathAsync(module_path + ".iv");
				}, task_continuation_context::use_arbitrary())

				// read IV file
				.then([&encrypted](StorageFile^ file) {
					encrypted = true;
					return FileIO::ReadBufferAsync(file);
				}, task_continuation_context::use_arbitrary())

				// set IV buffer
				.then([&iv_buffer, &encrypted, &file_buffer, &hasError, &event](concurrency::task<IBuffer^> task) {
					try {
						iv_buffer = task.get();
					} catch (...) {
						if (encrypted && !file_buffer) {
							hasError = true;
						}
					}
					event.set();
				}, task_continuation_context::use_arbitrary()
			);
			event.wait();

			// decrypt file
			if (!hasError && encrypted) {
				try {
					SymmetricKeyAlgorithmProvider^ provider = SymmetricKeyAlgorithmProvider::OpenAlgorithm(SymmetricAlgorithmNames::AesCbcPkcs7);
					CryptographicKey^ key = provider->CreateSymmetricKey(CryptographicBuffer::DecodeFromBase64String(seed__));
					IBuffer^ decrypted_buffer = CryptographicEngine::Decrypt(key, file_buffer, iv_buffer);
					content = CryptographicBuffer::ConvertBinaryToString(BinaryStringEncoding::Utf8, decrypted_buffer);
				} catch (Platform::Exception^ ex) {
					detail::ThrowRuntimeError("require", "Could not load module: module_path = " + TitaniumWindows::Utility::ConvertUTF8String(module_path) + ", message = " + TitaniumWindows::Utility::ConvertUTF8String(ex->Message));
					hasError = true;
				} catch (...) {
					detail::ThrowRuntimeError("require", "Could not load module: module_path = " + TitaniumWindows::Utility::ConvertUTF8String(module_path));
					hasError = true;
				}
			// not encrypted, return contents
			} else if (!encrypted && file_buffer) {
				content = CryptographicBuffer::ConvertBinaryToString(BinaryStringEncoding::Utf8, file_buffer);
			}
		}
		if (hasError) {
			detail::ThrowRuntimeError("require", "Could not load module: module_path = " + TitaniumWindows::Utility::ConvertUTF8String(module_path));
		}
		return TitaniumWindows::Utility::ConvertUTF8String(content);
	}

	GlobalObject::GlobalObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Titanium::GlobalObject(js_context),
		seed__(nullptr)
		, timer_dispatcher_map__(ref new Platform::Collections::Map<unsigned, Windows::System::Threading::ThreadPoolTimer^>())
	{
		TITANIUM_LOG_DEBUG("GlobalObject::ctor");
	}

	void GlobalObject::JSExportInitialize()
	{
		JSExport<GlobalObject>::SetClassVersion(1);
		JSExport<GlobalObject>::SetParent(JSExport<Titanium::GlobalObject>::Class());
	}

}  // namespace TitaniumWindows
