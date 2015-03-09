/**
 * Titanium.API for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
#define _SCL_SECURE_NO_WARNINGS

#include "TitaniumWindows/API.hpp"
#include "TitaniumWindows/Utility.hpp"
#include "Titanium/detail/TiBase.hpp"
#include <iostream>
#include <ppltasks.h>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

namespace TitaniumWindows
{
	API::API(const JSContext& js_context) TITANIUM_NOEXCEPT
	    : Titanium::API(js_context),
		tcp_socket_(ref new Windows::Networking::Sockets::StreamSocket())
	{
		TITANIUM_LOG_DEBUG("API::ctor Initialize");
		tcp_socket_->Control->KeepAlive = true;
		connect();
	}

	void API::log(const std::string& message) const TITANIUM_NOEXCEPT
	{
		TITANIUM_LOG_DEBUG("API::log");

		// send message to Titanium CLI log relay
		if (tcp_writer_ != nullptr) {
			tcp_writer_->WriteString(TitaniumWindows::Utility::ConvertString(message) + "\n");  // Logger assumes \n for newlines!
			tcp_writer_->StoreAsync();
		} else {
			// TODO If the socket isn't connected yet, we should probably store the logs in a queue to get sent along
			std::clog << message << std::endl;
		}
	}

	void API::JSExportInitialize()
	{
		JSExport<API>::SetClassVersion(1);
		JSExport<API>::SetParent(JSExport<Titanium::API>::Class());
	}

	void API::connect()
	{
		using namespace TitaniumWindows::Utility;
		using namespace Windows::Storage;
		using namespace Windows::Networking;
		using namespace concurrency;
		// clang-format off
		// Get a handle on titanium_settings.ini file
		create_task(Windows::ApplicationModel::Package::Current->InstalledLocation->GetFileAsync("titanium_settings.ini"), task_continuation_context::use_arbitrary())
		// Read titanium_settings.ini file into String
		.then([](StorageFile^ storage_file) {
			return FileIO::ReadTextAsync(storage_file);
		}, task_continuation_context::use_arbitrary())
		// Parse the ini, try to connect using settings found in INI
		.then([this](task<Platform::String^> antecedent) {
			Platform::String^ content;
			try {
				content = antecedent.get();
			}
			catch (Platform::COMException^ e) {
				return; // there is no ini file, behave like it's empty
			}
			std::stringstream ss(ConvertString(content)); // put string into stream

			// Parse stream with INI parser
			boost::property_tree::ptree pt;
			boost::property_tree::ini_parser::read_ini(ss, pt);

			// Now pull out the ips/secret/port from the map
			auto port = std::make_shared<Platform::String^>(ConvertString(pt.get<std::string>("tcpPort")));
			auto server_token = std::make_shared<Platform::String^>(ConvertString(pt.get<std::string>("serverToken")));

			std::vector<std::string> hosts;
			std::string ip_address_list = pt.get<std::string>("ipAddressList");
			boost::algorithm::split(hosts, ip_address_list, boost::algorithm::is_any_of(","));

			for (auto ip_address : hosts) {
				TITANIUM_LOG_DEBUG("API::connect: Trying to connect to log server: ", ip_address, ":", ConvertString(*port));
				
				try {
					// Connect to the tcp socket on log relay!

					// TODO Set timeout based on value from ini! We need to use a cancellation token somehow!

					auto host = std::make_shared<Platform::String^>(ConvertString(ip_address));

					double d = static_cast<double>(2000);
					std::chrono::milliseconds timeout((long long)d);
					std::chrono::duration<std::chrono::nanoseconds::rep, std::ratio_multiply<std::ratio<100>, std::nano>> timer_interval_ticks = timeout;
					TITANIUM_LOG_DEBUG("Timer: ctor: timer_interval_ticks = ", timer_interval_ticks.count());

					auto cancellationTokenSource__ = cancellation_token_source();
					Windows::Foundation::TimeSpan time_span;
					time_span.Duration = timer_interval_ticks.count();
					auto dispatcher_timer__ = ref new Windows::UI::Xaml::DispatcherTimer();
					dispatcher_timer__->Interval = time_span;
					
					dispatcher_timer__->Tick += ref new Windows::Foundation::EventHandler<Platform::Object ^>([dispatcher_timer__, cancellationTokenSource__](Platform::Object ^ sender, Platform::Object ^ e) {
						cancellationTokenSource__.cancel();
						dispatcher_timer__->Stop();
					});
					if (tcp_writer_ != nullptr) {
						break;
					}
					dispatcher_timer__->Start();

					create_task([]() { return; }, task_continuation_context::use_current()).then([host, port, this]() { tcp_socket_->ConnectAsync(ref new HostName(*host), *port); }, cancellationTokenSource__.get_token(), task_continuation_context::use_current()).then([this, server_token](task<void> task) {
						try {
							task.get();
							auto writer = ref new Streams::DataWriter(tcp_socket_->OutputStream);
							// we write the server token to see if this log relay is really the log relay we're looking for
							writer->WriteString(*server_token + "\n");
							//writer->StoreAsync();
							tcp_writer_ = writer;
						}
						catch (Platform::COMException^ e) {
							// We need to try next IP! So lets log this and wipe the socket out
							TITANIUM_LOG_DEBUG(e->Message->Data());
						}
						catch (const task_canceled& e) {
							TITANIUM_LOG_DEBUG(e.what());
						}
						catch (const std::exception& e) {
							TITANIUM_LOG_DEBUG(e.what());
						}
						
					}, task_continuation_context::use_current());
					
					if (tcp_writer_ != nullptr) {
						break;
					}
				}
				catch (Platform::COMException^ e) {
					delete tcp_writer_;
					tcp_writer_ = nullptr;
					// try next ip!
					TITANIUM_LOG_DEBUG("API::connect: Trying to connect failed, trying next IP...");
				}
				catch (const std::exception& e) {
					TITANIUM_LOG_DEBUG(e.what());
				}
			}
		}, task_continuation_context::use_current());
		// clang-format on
	}
}  // namespace TitaniumWindows
