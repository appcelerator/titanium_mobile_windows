/**
 * Titanium.Utility for Windows
 * Author: Gary Mathews
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_UTILITY_HPP_
#define _TITANIUMWINDOWS_UTILITY_HPP_

#include <string>
#include <locale>
#include <codecvt>
#include <ppltasks.h>
#include <unordered_map>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include "HAL/HAL.hpp"

#define EPOCH_BIAS 116444736000000000 // Number of 100 nanosecond units from 1/1/1601 (windows epoch) to 1/1/1970 (unix epoch)

namespace TitaniumWindows
{
	namespace Utility
	{
		//
		// Run a task on the UI thread
		//
		template<class T> static void RunOnUIThread(T handler) {
			RunOnUIThread<T>(Windows::UI::Core::CoreDispatcherPriority::Normal, handler);
		}

		//
		// Run a task on the UI thread with a specified priority
		//
		template<class T> static void RunOnUIThread(Windows::UI::Core::CoreDispatcherPriority priority, T handler) {
			auto dispatcher = Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher;
			dispatcher->RunAsync(priority, ref new Windows::UI::Core::DispatchedHandler(handler));
		}

		//
		// Convert std::string into Platform::String^
		//
		static ::Platform::String^ ConvertString(const std::string& str)
		{
			return ref new ::Platform::String(std::wstring(str.begin(), str.end()).c_str());
		}

		//
		// Convert Platform::String^ into std::string
		//
		static std::string ConvertString(::Platform::String^ str)
		{
			return std::string(str->Begin(), str->End());
		}

		//
		// Convert UTF-8 std::string into Platform::String^
		//
		static ::Platform::String^ ConvertUTF8String(const std::string& str) 
		{
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
			return ref new ::Platform::String(converter.from_bytes(str).data());
		}

		//
		// Convert Platform::String^ into UTF-8 std::string
		//
		static std::string ConvertUTF8String(::Platform::String^ str)
		{
			std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
			return std::string(converter.to_bytes(str->Data()));
		}

		//
		// Convert unsigned char array into plain-text hex std::string
		//
		static std::string HexString(unsigned char* data, size_t length)
		{
			std::stringstream ss;
			for (size_t i=0;i<length;++i) {
			  ss << std::hex
				 << std::noshowbase
				 << std::setw(2)
				 << std::setfill('0')
				 << (uint32_t)data[i];
			}
			return ss.str();
		}

		static std::vector<std::uint8_t> GetContentFromBuffer(Windows::Storage::Streams::IBuffer^ buffer)
		{
			const auto reader = Windows::Storage::Streams::DataReader::FromBuffer(buffer);
			std::vector<std::uint8_t> data(reader->UnconsumedBufferLength);
			if (!data.empty()) {
				reader->ReadBytes(::Platform::ArrayReference<std::uint8_t>(&data[0], data.size()));
			}
			return data;
		}

		static std::vector<std::uint8_t> GetContentFromFile(Windows::Storage::StorageFile^ file)
		{
			std::vector<std::uint8_t> content;
			concurrency::event event;
			concurrency::task<Windows::Storage::Streams::IBuffer^>(Windows::Storage::FileIO::ReadBufferAsync(file)).then([&content, &event](concurrency::task<Windows::Storage::Streams::IBuffer ^ > task) {
					try {
						content = std::move(GetContentFromBuffer(task.get()));
					} catch (::Platform::COMException^ ex) {
						// TODO throw JavaScript Exception
					}
					event.set();
				},
				concurrency::task_continuation_context::use_arbitrary());
			event.wait();

			return content;
		}

		static const std::string MimeTypeForExtension(std::string& path)
		{
			const static std::unordered_map<std::string, const std::string> mimeTypeFromExtensionDict = {
				{"css", "text/css"},
				{"m4v", "video/x-m4v"}};

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

		static std::chrono::milliseconds GetMSecSinceEpoch(Windows::Foundation::DateTime d)
		{
			long long intervals = d.UniversalTime - EPOCH_BIAS; // this gives us number of 100 nanosecond intervals since unix epoch
			long long milliseconds = intervals / 10000; // convert 100 nanosecond intervals to milliseconds
			return std::chrono::milliseconds(milliseconds); // wrap in data type
		}

		static Windows::Foundation::DateTime GetDateTime(const HAL::JSValue& dateObject) 
		{
			Windows::Foundation::DateTime date;
			const auto intervals = static_cast<std::uint64_t>(static_cast<double>(dateObject)) * 10000;
			date.UniversalTime = intervals + EPOCH_BIAS;
			return date;
		}

	}  // namespace Utility
}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UTILITY_HPP_
