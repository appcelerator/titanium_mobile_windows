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

#define NOMINMAX // disable min & max macro which is just evil

#include <string>
#include <locale>
#include <codecvt>
#include <ppltasks.h>
#include <unordered_map>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <cstdint>

#include "TitaniumWindows_Utility_EXPORT.h"
#include "Titanium/ErrorResponse.hpp"

#define EPOCH_BIAS 116444736000000000 // Number of 100 nanosecond units from 1/1/1601 (windows epoch) to 1/1/1970 (unix epoch)

namespace HAL 
{
	class JSContext;
	class JSValue;
}

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
		TITANIUMWINDOWS_UTILITY_EXPORT ::Platform::String^ ConvertString(const std::string& str);

		//
		// Convert Platform::String^ into std::string
		//
		TITANIUMWINDOWS_UTILITY_EXPORT std::string ConvertString(::Platform::String^ str);

		//
		// Convert UTF-8 std::string into Platform::String^
		//
		TITANIUMWINDOWS_UTILITY_EXPORT ::Platform::String^ ConvertUTF8String(const std::string& str);

		//
		// Convert Platform::String^ into UTF-8 std::string
		//
		TITANIUMWINDOWS_UTILITY_EXPORT std::string ConvertUTF8String(::Platform::String^ str);

		//
		// Convert UTF-8 std::string into wstring
		//
		TITANIUMWINDOWS_UTILITY_EXPORT std::wstring ConvertToUTF8WString(const std::string& str);

		//
		// Convert IVector<Platform::String^> into std::string, concatenated by ","
		//
		TITANIUMWINDOWS_UTILITY_EXPORT std::string ConvertString(Windows::Foundation::Collections::IVector<::Platform::String^>^ strs);

		//
		// Convert unsigned char array into plain-text hex std::string
		//
		TITANIUMWINDOWS_UTILITY_EXPORT std::string HexString(unsigned char* data, size_t length);

		//
		// Get Platform::Array from IBuffer
		//
		TITANIUMWINDOWS_UTILITY_EXPORT::Platform::Array<std::uint8_t, 1U>^ GetArrayFromBuffer(Windows::Storage::Streams::IBuffer^ buffer);

		//
		// Get binary content from IBuffer
		//
		TITANIUMWINDOWS_UTILITY_EXPORT std::vector<std::uint8_t> GetContentFromBuffer(Windows::Storage::Streams::IBuffer^ buffer);

		//
		// Get binary content from StorageFile
		//
		TITANIUMWINDOWS_UTILITY_EXPORT std::vector<std::uint8_t> GetContentFromFile(Windows::Storage::StorageFile^ file);

		//
		// Get MIME string from path
		//
		TITANIUMWINDOWS_UTILITY_EXPORT const std::string MimeTypeForExtension(const std::string& path);

		//
		// Get milliseconds since the epoch from DateTime
		//
		TITANIUMWINDOWS_UTILITY_EXPORT std::chrono::milliseconds GetMSecSinceEpoch(const Windows::Foundation::DateTime& d);

		//
		// Get milliseconds from TimeSpan. 
		// The value of a TimeSpan object is the number of ticks that equal the represented time interval.
		// A tick is equal to 100 nanoseconds, or one ten-millionth of a second
		//
		TITANIUMWINDOWS_UTILITY_EXPORT std::chrono::milliseconds GetMSec(const Windows::Foundation::TimeSpan& t);
		TITANIUMWINDOWS_UTILITY_EXPORT std::chrono::seconds GetSec(const Windows::Foundation::TimeSpan& t);
		TITANIUMWINDOWS_UTILITY_EXPORT std::chrono::minutes GetMinutes(const Windows::Foundation::TimeSpan& t);

		//
		// Get Uri from path
		//
		TITANIUMWINDOWS_UTILITY_EXPORT Windows::Foundation::Uri^ GetUriFromPath(const std::string& path);

		//
		// Get Uri from path for browser
		//
		TITANIUMWINDOWS_UTILITY_EXPORT Windows::Foundation::Uri^ GetWebUriFromPath(const std::string& path);

		//
		// Get error code from HRESULT error message
		//
		TITANIUMWINDOWS_UTILITY_EXPORT std::uint32_t GetHResultErrorCode(::Platform::String^ errorMessage, const std::uint32_t& defaultCode);

		//
		// Get DateTime from JavaScript Date object
		//
		TITANIUMWINDOWS_UTILITY_EXPORT Windows::Foundation::DateTime GetDateTime(const HAL::JSValue& dateObject);

		//
		// Get DateTime from std::chrono::system_clock::time_point
		//
		TITANIUMWINDOWS_UTILITY_EXPORT Windows::Foundation::DateTime GetDateTime(const std::chrono::system_clock::time_point& time);

		//
		// Get std::chrono::system_clock::time_point from DateTime
		//
		TITANIUMWINDOWS_UTILITY_EXPORT std::chrono::system_clock::time_point GetDateTime(const  Windows::Foundation::DateTime& time);

		//
		// Extract hours, minutes and seconds from time_point
		//
		TITANIUMWINDOWS_UTILITY_EXPORT Windows::Foundation::TimeSpan ExtractTime(const std::chrono::system_clock::time_point& time);
		TITANIUMWINDOWS_UTILITY_EXPORT std::chrono::system_clock::time_point ExtractTime(const std::chrono::system_clock::time_point& baset_date, const Windows::Foundation::TimeSpan& base_time);

		//
		// Add view onto current Window
		//
		TITANIUMWINDOWS_UTILITY_EXPORT void SetViewForCurrentWindow(Windows::UI::Xaml::FrameworkElement^ view, Windows::Foundation::EventRegistrationToken& token, const bool& visible, const bool& fullscreen);

		//
		// Add hidden view onto current Window
		//
		TITANIUMWINDOWS_UTILITY_EXPORT void SetHiddenViewForCurrentWindow(Windows::UI::Xaml::FrameworkElement^ view, Windows::Foundation::EventRegistrationToken& token);

		//
		// Remove view from current Window
		//
		TITANIUMWINDOWS_UTILITY_EXPORT void RemoveViewFromCurrentWindow(Windows::UI::Xaml::FrameworkElement^ view, std::function<void()> = nullptr);

		//
		// Construct Ti.Blob from given path
		//
		TITANIUMWINDOWS_UTILITY_EXPORT HAL::JSValue GetTiBlobForFile(const HAL::JSContext& js_context, const std::string& path);

		//
		// Create ErrorResponse from Exception
		//
		TITANIUMWINDOWS_UTILITY_EXPORT Titanium::ErrorResponse GetTiErrorResponse(::Platform::Exception^ e);

		TITANIUMWINDOWS_UTILITY_EXPORT Titanium::ErrorResponse GetTiErrorResponse(const std::string& message);

		//
		// Check if Titanium is running on Windws Phone
		//
		TITANIUMWINDOWS_UTILITY_EXPORT bool IsWindowsPhoneOrMobile();

	}  // namespace Utility
}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_UTILITY_HPP_
