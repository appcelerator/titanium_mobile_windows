/**
 * Titanium.Utility for Windows
 * Author: Gary Mathews
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "TitaniumWindows/Utility.hpp"
#include <boost/algorithm/string.hpp>
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/WindowsMacros.hpp"
#include <ctime>
#include <concrt.h>

namespace TitaniumWindows
{
	namespace Utility
	{

		//
		// Convert std::string into Platform::String^
		//
		::Platform::String^ ConvertString(const std::string& str) 
		{
			if (str.empty()) {
				return "";
			}
			return ref new ::Platform::String(std::wstring(str.begin(), str.end()).c_str());
		}

		//
		// Convert Platform::String^ into std::string
		//
		std::string ConvertString(::Platform::String^ str) 
		{
			if (str == nullptr || str->IsEmpty()) {
				return "";
			}
			return std::string(str->Begin(), str->End());
		}

		//
		// Convert UTF-8 std::string into Platform::String^
		//
		::Platform::String^ ConvertUTF8String(const std::string& str) 
		{
			if (str.empty()) {
				return "";
			}
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
			return ref new ::Platform::String(converter.from_bytes(str).data());
		}

		//
		// Convert UTF-8 std::string into wstring
		//
		std::wstring ConvertToUTF8WString(const std::string& str)
		{
			if (str.empty()) {
				return std::wstring();
			}
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
			return converter.from_bytes(str);
		}

		//
		// Convert Platform::String^ into UTF-8 std::string
		//
		std::string ConvertUTF8String(::Platform::String^ str) 
		{
			if (str == nullptr || str->IsEmpty()) {
				return "";
			}
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
			return std::string(converter.to_bytes(str->Data()));
		}

		std::string ConvertString(Windows::Foundation::Collections::IVector<::Platform::String^>^ strs) 
		{
			std::stringstream ss;
			for (std::size_t i = 0; i < strs->Size; i++) {
				ss << ConvertString(strs->GetAt(i));
				if (i < strs->Size - 1) {
					ss << ",";
				}
			}
			return ss.str();
		}

		//
		// Convert unsigned char array into plain-text hex std::string
		//
		std::string HexString(unsigned char* data, size_t length) 
		{
			std::stringstream ss;
			for (size_t i = 0; i<length; ++i) {
				ss << std::hex
					<< std::noshowbase
					<< std::setw(2)
					<< std::setfill('0')
					<< (uint32_t)data[i];
			}
			return ss.str();
		}

		::Platform::Array<std::uint8_t, 1U>^ GetArrayFromBuffer(Windows::Storage::Streams::IBuffer^ buffer)
		{
			::Platform::Array<std::uint8_t, 1U>^ array = ref new ::Platform::Array<std::uint8_t, 1U>(buffer->Length);
			Windows::Security::Cryptography::CryptographicBuffer::CopyToByteArray(buffer, &array);
			return array;
		}

		std::vector<std::uint8_t> GetContentFromBuffer(Windows::Storage::Streams::IBuffer^ buffer) 
		{
			if (buffer == nullptr) {
				return std::vector<std::uint8_t>();
			}
			const auto reader = Windows::Storage::Streams::DataReader::FromBuffer(buffer);
			std::vector<std::uint8_t> data(reader->UnconsumedBufferLength);
			if (!data.empty()) {
				reader->ReadBytes(::Platform::ArrayReference<std::uint8_t>(&data[0], data.size()));
			}
			return data;
		}

		std::vector<std::uint8_t> GetContentFromFile(Windows::Storage::StorageFile^ file) 
		{
			std::vector<std::uint8_t> content;
			concurrency::event event;
			concurrency::task<Windows::Storage::Streams::IBuffer^>(Windows::Storage::FileIO::ReadBufferAsync(file)).then([&content, &event](concurrency::task<Windows::Storage::Streams::IBuffer ^ > task) {
				try {
					content = std::move(GetContentFromBuffer(task.get()));
				} catch (::Platform::Exception^ ex) {
					TITANIUM_LOG_DEBUG(TitaniumWindows::Utility::ConvertString(ex->Message));
				} catch (...) {
					TITANIUM_LOG_DEBUG("Unknown error while GetContentFromFile");
				}
				event.set();
			},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return content;
		}

		const std::string MimeTypeForExtension(const std::string& path) 
		{
			const static std::unordered_map<std::string, const std::string> mimeTypeFromExtensionDict = {
				{ "css", "text/css" },
				{ "m4v", "video/x-m4v" } };

			const auto pos = path.find_last_of(".");
			if (pos != std::string::npos && path.size() > pos) {
				const auto ext = path.substr(pos + 1);
				const auto found = mimeTypeFromExtensionDict.find(ext);
				if (found != mimeTypeFromExtensionDict.end()) {
					return found->second;
				}
			}
			return "application/octet-stream";
		}

		std::chrono::milliseconds GetMSecSinceEpoch(const Windows::Foundation::DateTime& d) 
		{
			long long intervals = d.UniversalTime - EPOCH_BIAS; // this gives us number of 100 nanosecond intervals since unix epoch
			long long milliseconds = intervals / 10000; // convert 100 nanosecond intervals to milliseconds
			return std::chrono::milliseconds(milliseconds); // wrap in data type
		}

		std::chrono::milliseconds GetMSec(const Windows::Foundation::TimeSpan& t) 
		{
			return std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(t.Duration / 10000));
		}

		std::chrono::seconds GetSec(const Windows::Foundation::TimeSpan& t) 
		{
			return std::chrono::duration_cast<std::chrono::seconds>(GetMSec(t));
		}

		std::chrono::minutes GetMinutes(const Windows::Foundation::TimeSpan& t)
		{
			return std::chrono::duration_cast<std::chrono::minutes>(GetMSec(t));
		}

		Windows::Foundation::Uri^ GetUriFromPath(const std::string& path) 
		{
			std::string modified = path;

			// fix backslash
			boost::replace_all<std::string>(modified, "\\", "/");

			// if the path isn't an http/s URI already, fix URI to point to local files in app
			if (!boost::starts_with(modified, "http://") && !boost::starts_with(modified, "https://")) {

				// fix root folder path
				auto rootFolder = TitaniumWindows::Utility::ConvertString(Windows::ApplicationModel::Package::Current->InstalledLocation->Path);
				boost::replace_all<std::string>(rootFolder, "\\", "/");

				// Note that rootFolder does not end with "/", so we don't need to use ":///" here
				boost::replace_all<std::string>(modified, rootFolder, "ms-appx://");
				
				// fix local folder path
				auto localFolder = TitaniumWindows::Utility::ConvertString(Windows::Storage::ApplicationData::Current->LocalFolder->Path);
				boost::replace_all<std::string>(localFolder, "\\", "/");
				boost::replace_all<std::string>(modified, localFolder, "ms-appdata:///local");

				// fix relative path with application directory
				if (modified.find("://") == std::string::npos) {

					// always use absolute path
					if (!boost::starts_with(modified, "/")) {
						modified = "/" + modified;
					}

					modified = "ms-appx://" + modified;
				}

				// Fix invalid path separator in path "//" just in case since Windows can't handle this
				// This often happens when user concatenate path with filename manually
				auto scheme    = modified.substr(0, modified.find_first_of("://") + 3);
				auto pathInURL = modified.substr(scheme.size());

				boost::replace_all<std::string>(pathInURL, "//", "/");

				modified = scheme + pathInURL;
			}
			return ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertUTF8String(modified));
		}

		Windows::Foundation::Uri^ GetWebUriFromPath(const std::string& path)
		{
			std::string modified = path;

			// fix backslash
			boost::replace_all<std::string>(modified, "\\", "/");

			// if the path isn't an http/s URI already, fix URI to point to local files in app
			if (!boost::starts_with(modified, "http://") && !boost::starts_with(modified, "https://")) {
				// URIs must be absolute
				if (!boost::starts_with(modified, "/")) {
					modified = "/" + modified;
				}
				// use MS's in-app URL scheme for browser
				modified = "ms-appx-web://" + modified;
			}
			return ref new Windows::Foundation::Uri(TitaniumWindows::Utility::ConvertUTF8String(modified));
		}

		std::uint32_t GetHResultErrorCode(::Platform::String^ errorMessage, const std::uint32_t& defaultCode)
		{
			// Extract HRESULT error code from error message
			const auto message = TitaniumWindows::Utility::ConvertString(errorMessage);
			std::uint32_t codeAsInt = defaultCode;
			const std::string needle = "HRESULT - ";
			const auto codeStart = message.find(needle);
			if (codeStart != std::string::npos) {
				const auto code = message.substr(message.find(needle) + needle.size());
				codeAsInt = static_cast<std::uint32_t>(std::stoul(code, nullptr, 16));
			}
			return codeAsInt;
		}

		Windows::Foundation::DateTime GetDateTime(const HAL::JSValue& dateObject) 
		{
			Windows::Foundation::DateTime date;
			const auto intervals = static_cast<std::uint64_t>(static_cast<double>(dateObject)) * 10000;
			date.UniversalTime = intervals + EPOCH_BIAS;
			return date;
		}

		Windows::Foundation::DateTime GetDateTime(const std::chrono::system_clock::time_point& time)
		{
			Windows::Foundation::DateTime date;
			const auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(time.time_since_epoch()).count();
			const auto intervals = msec * 10000;
			date.UniversalTime = intervals + EPOCH_BIAS;
			return date;
		}

		std::chrono::system_clock::time_point GetDateTime(const Windows::Foundation::DateTime& date)
		{
			const auto msec = GetMSecSinceEpoch(date);
			return std::chrono::time_point<std::chrono::system_clock>(msec);
		}

		Windows::Foundation::TimeSpan ExtractTime(const std::chrono::system_clock::time_point& time)
		{
			Windows::Foundation::TimeSpan timeSpan;

			const auto tt = std::chrono::system_clock::to_time_t(time);
			tm local_tm;
			localtime_s(&local_tm, &tt);

			const std::uint64_t msec = ((local_tm.tm_hour * 60 * 60) + (local_tm.tm_min * 60) + local_tm.tm_sec) * 1000;
			timeSpan.Duration = msec * 10000; // 100-nanoseconds

			return timeSpan;
		}

		std::chrono::system_clock::time_point ExtractTime(const std::chrono::system_clock::time_point& base_date, const Windows::Foundation::TimeSpan& base_time)
		{
			const auto base_msec = std::chrono::duration_cast<std::chrono::milliseconds>(base_date.time_since_epoch()).count();
			const std::uint64_t base_date_msec = base_msec - GetMSec(ExtractTime(base_date)).count(); // base msec without time

			// new time by msec
			const auto time_msec = GetMSec(base_time).count();
			return std::chrono::time_point<std::chrono::system_clock>(std::chrono::milliseconds(static_cast<std::chrono::milliseconds::rep>(base_date_msec + time_msec)));
		}

		void RemoveViewFromCurrentWindow(Windows::UI::Xaml::FrameworkElement^ view, std::function<void()> callback)
		{
			const auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
			TITANIUM_ASSERT_AND_THROW(rootFrame->Content, "Could not get content from current Window");
			const auto removeUI = ref new Windows::UI::Core::DispatchedHandler([view, rootFrame, callback]() {
				if (rootFrame->Content) {
					const auto page = dynamic_cast<Windows::UI::Xaml::Controls::Page^>(rootFrame->Content);
					if (page && page->Content) {
						const auto content = static_cast<Windows::UI::Xaml::Controls::Panel^>(page->Content);
						if (content) {
							std::uint32_t index;
							if (content->Children->IndexOf(view, &index)) {
								content->Children->RemoveAt(index);
							} else {
								TITANIUM_LOG_WARN("Could not find view from current Window");
							}
						}
					}
					if (callback) {
						callback();
					}
				}
			});
			Windows::UI::Xaml::Window::Current->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, removeUI);
		}


		// Add hidden UI onto current Window
		void SetHiddenViewForCurrentWindow(Windows::UI::Xaml::FrameworkElement^ view, Windows::Foundation::EventRegistrationToken& token)
		{
			SetViewForCurrentWindow(view, token, false, false);
		}

		void SetViewForCurrentWindow(Windows::UI::Xaml::FrameworkElement^ view, Windows::Foundation::EventRegistrationToken& token, const bool& visible, const bool& fullscreen)
		{
			view->Visibility = visible ? Windows::UI::Xaml::Visibility::Visible : Windows::UI::Xaml::Visibility::Collapsed;
			const auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Windows::UI::Xaml::Window::Current->Content);
			const auto registerUI = ref new Windows::UI::Core::DispatchedHandler([view, rootFrame, fullscreen]() {
				if (rootFrame->Content) {
					const auto page = dynamic_cast<Windows::UI::Xaml::Controls::Page^>(rootFrame->Content);
					if (page && page->Content) {
						const auto content = static_cast<Windows::UI::Xaml::Controls::Panel^>(page->Content);
						if (content) {
							if (fullscreen) {
								const auto currentBounds = Windows::UI::Xaml::Window::Current->Bounds;
								view->Width = currentBounds.Width;
								view->Height = currentBounds.Height;
							}
							content->Children->Append(view);
						}
					}
				}
			});
			if (rootFrame->Content == nullptr) {
				// If there's no Window (Window.open() is not called) yet, wait for the first Window opened
				token = rootFrame->Navigated += ref new Windows::UI::Xaml::Navigation::NavigatedEventHandler([rootFrame, registerUI, &token](Platform::Object^ sender, Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) {
					rootFrame->Navigated -= token; // unregister current event, you just need to do this only once
					Windows::UI::Xaml::Window::Current->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, registerUI);
				});
			} else {
				// If there's a Window already, just attach to it
				Windows::UI::Xaml::Window::Current->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal, registerUI);
			}
		}

		HAL::JSValue GetTiBlobForFile(const HAL::JSContext& js_context, const std::string& path)
		{
			const std::string blob_read = R"(
			function blob_read(path) {
				var f = Ti.Filesystem.getFile(path);
				if (f.exists()) {
					return f.read();
				}
			}
			blob_read;
			)";

			// read file and get blob.
			auto object = js_context.CreateObject();
			auto blob_read_func = static_cast<HAL::JSObject>(js_context.JSEvaluateScript(blob_read, object));
			return blob_read_func({ js_context.CreateString(path) }, blob_read_func);
		}

		Titanium::ErrorResponse GetTiErrorResponse(const std::string& message)
		{
			Titanium::ErrorResponse response;
			response.success = false;
			response.code = -1; // default error code
			response.error = message;
			return response;
		}

		Titanium::ErrorResponse GetTiErrorResponse(::Platform::Exception^ e)
		{
			Titanium::ErrorResponse response;
			response.success = false;
			response.code  = e->HResult;
			response.error = TitaniumWindows::Utility::ConvertString(e->Message);
			return response;
		}

		bool IsWindowsPhoneOrMobile()
		{
#if defined(IS_WINDOWS_10)
			return IS_WINDOWS_MOBILE;
#elif defined(IS_WINDOWS_PHONE)
			return true;
#else
			return false;
#endif
		}
	}  // namespace Utility
}  // namespace TitaniumWindows
