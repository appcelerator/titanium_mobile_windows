/**
 * Global for Windows
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/GlobalObject.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include <ratio>
#include <sstream>
#include <concrt.h>
#include <boost/algorithm/string.hpp>
#include "TitaniumWindows/Utility.hpp"

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
	void GlobalObject::registerNativeModuleRequireHook(const std::vector<std::string>& native_module_names, const std::unordered_map<std::string, JSValue>& preloaded_modules, std::function<JSValue(const std::string&)> requireHook)
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
		// mark it as loaded
		native_module_names__[moduleId] = true;

		// otherwise try to load dynamically
		return native_module_requireHook__(moduleId);
	}

	static Platform::String^ resolve(const std::string& path) 
	{
		const auto newpath = TitaniumWindows::Utility::ConvertUTF8String(boost::algorithm::replace_all_copy(boost::algorithm::replace_all_copy(path, "/", "\\"), "\\\\", "\\"));

		if (!boost::contains(path, ":")) {
			Windows::ApplicationModel::Package^ package = Windows::ApplicationModel::Package::Current;
			Windows::Storage::StorageFolder^ installed_location = package->InstalledLocation;
			Platform::String^ location = installed_location->Path;

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
			} catch (Platform::Exception^ ex) {
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
					} catch (Platform::Exception^ ex) {
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
					} catch (Platform::Exception^ ex) {
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

#pragma warning(push)
#pragma warning(disable : 4251)
	class TITANIUMWINDOWS_GLOBAL_EXPORT Timer final : public Titanium::GlobalObject::Timer, public std::enable_shared_from_this<Timer>
	{
#pragma warning(pop)
	public:
		Timer(Titanium::GlobalObject::Callback_t callback, const std::chrono::milliseconds& _interval)
		    : Titanium::GlobalObject::Timer(callback, _interval), callback__(callback)
		{
			TITANIUM_LOG_DEBUG("Timer: ctor");

			std::chrono::milliseconds interval = _interval;
			// Avoid zero interval
			if (interval.count() == 0) {
				interval = std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(100));
			}

			// A Windows::Foundation::TimeSpan is a time period expressed in
			// 100-nanosecond units.
			//
			// Reference:
			// http://msdn.microsoft.com/en-us/library/windows/apps/windows.foundation.timespan
			std::chrono::duration<std::chrono::nanoseconds::rep, std::ratio_multiply<std::ratio<100>, std::nano>> timer_interval_ticks = interval;
			TITANIUM_LOG_DEBUG("Timer: ctor: timer_interval_ticks = ", timer_interval_ticks.count());

			Windows::Foundation::TimeSpan time_span;
			time_span.Duration = timer_interval_ticks.count();
			dispatcher_timer__ = ref new Windows::UI::Xaml::DispatcherTimer();
			dispatcher_timer__->Interval = time_span;
		}

		virtual ~Timer()
		{
			TITANIUM_LOG_DEBUG("Timer: dtor");
			if (dispatcher_timer__->IsEnabled) {
				dispatcher_timer__->Stop();
			}

			// TODO: what happens if start was never called? Is this an error?
			dispatcher_timer__->Tick -= event_registration_token__;
			dispatcher_timer__ = nullptr;
		}

		virtual void Start() TITANIUM_NOEXCEPT override final
		{
			TITANIUM_LOG_DEBUG("Timer::Start");
			std::call_once(dispatcher_timer_once_flag__, [this] {
				// Bring in the placeholders _1, _2, etc. for std::bind.
				using namespace std::placeholders;
				std::weak_ptr<Timer> weakThis(shared_from_this());
				auto callback = std::bind([](const std::weak_ptr<Timer>& weakThis, Platform::Object^ sender, Platform::Object^ event) {
						auto strong_ptr = weakThis.lock();
						if (strong_ptr) {
							strong_ptr->callback__();
						}
					},
					std::move(weakThis), _1, _2);
        
				this->event_registration_token__ = this->dispatcher_timer__->Tick += ref new Windows::Foundation::EventHandler<Platform::Object^>(callback);
			});

			if (!(dispatcher_timer__->IsEnabled)) {
				TITANIUM_LOG_DEBUG("Timer::Start: start timer ");
				dispatcher_timer__->Start();
			} else {
				TITANIUM_LOG_WARN("Timer::Start: start called while timer is already running");
			}
		}

		virtual void Stop() TITANIUM_NOEXCEPT override final
		{
			TITANIUM_LOG_DEBUG("Timer::Stop");
			if (dispatcher_timer__->IsEnabled) {
				TITANIUM_LOG_DEBUG("Timer::Stop: stop timer ");
				dispatcher_timer__->Stop();
			} else {
				TITANIUM_LOG_WARN("Timer::Stop: stop called while timer is not running");
			}
		}

	private:
#pragma warning(push)
#pragma warning(disable : 4251)
		Titanium::GlobalObject::Callback_t callback__;
		std::once_flag dispatcher_timer_once_flag__;
#pragma warning(pop)
		Windows::UI::Xaml::DispatcherTimer^ dispatcher_timer__;
		Windows::Foundation::EventRegistrationToken event_registration_token__;
	};

	std::shared_ptr<Titanium::GlobalObject::Timer> GlobalObject::CreateTimer(Titanium::GlobalObject::Callback_t callback, const std::chrono::milliseconds& interval) const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("Timer::CreateTimer");
		return std::make_shared<TitaniumWindows::Timer>(callback, interval);
	}
	GlobalObject::GlobalObject(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Titanium::GlobalObject(js_context),
		seed__(nullptr)
	{
		TITANIUM_LOG_DEBUG("GlobalObject::ctor");
	}

	void GlobalObject::JSExportInitialize()
	{
		JSExport<GlobalObject>::SetClassVersion(1);
		JSExport<GlobalObject>::SetParent(JSExport<Titanium::GlobalObject>::Class());
	}

}  // namespace TitaniumWindows
