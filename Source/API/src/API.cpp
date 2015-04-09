/**
* Titanium.API for Windows
*
* Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
* Licensed under the terms of the Apache Public License.
* Please see the LICENSE included with this distribution for details.
*/
#define _SCL_SECURE_NO_WARNINGS

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include "Titanium/detail/TiBase.hpp"
#include "TitaniumWindows/API.hpp"
#include "TitaniumWindows/Utility.hpp"

namespace TitaniumWindows
{

	concurrency::unbounded_buffer <std::string> API::buffer__;
	bool API::done__ { false };

	void log_forwarder::run()
	{
		using namespace Windows::Storage;
		using namespace concurrency;

		Windows::Storage::Streams::DataWriter^ writer = nullptr;
		auto tcp_socket = ref new Windows::Networking::Sockets::StreamSocket();
		try {
			concurrency::event read_event;
			// Get a handle on titanium_settings.ini file
			create_task(Windows::ApplicationModel::Package::Current->InstalledLocation->GetFileAsync("titanium_settings.ini"), task_continuation_context::use_arbitrary())
			.then([](StorageFile^ file) { // don't wrap in task, so next continuation handles any exception from file not existing
				return FileIO::ReadTextAsync(file);
			}, task_continuation_context::use_arbitrary())
			.then([&writer, &read_event, &tcp_socket](task<Platform::String^> task) {
				Platform::String^ content;
				try {
					content = task.get();
				}
				catch (...) {
					read_event.set();
					return; // file didn't exist (non-CLI run?) or we had trouble reading it. We'll log to std::clog.
				}

				std::stringstream ss(TitaniumWindows::Utility::ConvertString(content)); // put string into stream

				// Parse stream with INI parser
				boost::property_tree::ptree pt;
				boost::property_tree::ini_parser::read_ini(ss, pt);

				// Now pull out the ips/secret/port from the map
				auto port = std::make_shared<Platform::String^>(TitaniumWindows::Utility::ConvertString(pt.get<std::string>("tcpPort", "8666")));
				auto server_token = std::make_shared<Platform::String^>(TitaniumWindows::Utility::ConvertString(pt.get<std::string>("serverToken")));
				// timeout value
				std::chrono::milliseconds timeout((long long)pt.get<double>("logConnectionTimeout", 2000));
				std::chrono::duration<std::chrono::nanoseconds::rep, std::ratio_multiply<std::ratio<100>, std::nano>> timer_interval_ticks = timeout;
				Windows::Foundation::TimeSpan time_span;
				time_span.Duration = timer_interval_ticks.count();

				std::vector<std::string> hosts;
				std::string ip_address_list = pt.get<std::string>("ipAddressList", "127.0.0.1");
				boost::algorithm::split(hosts, ip_address_list, boost::algorithm::is_any_of(","));

				for (auto ip_address : hosts) {
					try {
						auto host = std::make_shared<Windows::Networking::HostName^>(ref new Windows::Networking::HostName(TitaniumWindows::Utility::ConvertString(ip_address)));
						// Create token to use to hold cencellation for tasks
						auto cancel_token_source = cancellation_token_source();
						// Now create a timer to fire cancellation on token after timeout
						Windows::System::Threading::ThreadPoolTimer::CreateTimer(ref new Windows::System::Threading::TimerElapsedHandler([cancel_token_source](Windows::System::Threading::ThreadPoolTimer^ timer) {
							cancel_token_source.cancel();
						}), time_span);

						concurrency::event connect_event;
						// emtpy task so we can set the context for connection
						create_task([]() {})
						// try to connect to host, use current thread, use token to cancel based on timeout
						.then([host, port, &tcp_socket]() {
							return tcp_socket->ConnectAsync(*host, *port);
						}, cancel_token_source.get_token(), concurrency::task_continuation_context::use_current())
						// get connection, attach writer to stream
						.then([&writer, &tcp_socket, &connect_event, server_token](concurrency::task<void> connectTask) {
							try {
								connectTask.get();
								writer = ref new Windows::Storage::Streams::DataWriter(tcp_socket->OutputStream);
								// we write the server token to see if this log relay is really the log relay we're looking for
								writer->WriteString(*server_token + "\n");  // Logger assumes \n for newlines!
								writer->StoreAsync();
							}
							catch (...) {} // TODO delete writer?
							connect_event.set();
						}, concurrency::task_continuation_context::use_current());
						connect_event.wait();

						if (writer != nullptr) { // did we get a connection? If so, don't try other IPs
							break;
						}
					}
					catch (...) {
						// try next ip!
						TITANIUM_LOG_DEBUG("API::connect: Trying to connect failed, trying next IP...");
					}
				}
				read_event.set();
			}, concurrency::task_continuation_context::use_current());
			read_event.wait();
		}
		catch (...) {
			TITANIUM_LOG_DEBUG("API::connect: will use console log...");
		}

		// Main logging loop
		try {
			std::string message;
			while (!API::done__) {
				message = concurrency::receive(API::buffer__); // wait for next message to log
				if (writer == nullptr) { // no TCP connection
					std::wclog << TitaniumWindows::Utility::ConvertUTF8String(message)->Data() << std::endl;
				} else { // forward over tcp socket
					writer->WriteString(TitaniumWindows::Utility::ConvertUTF8String(message) + "\n");  // Logger assumes \n for newlines!
					writer->StoreAsync();
				}
			}
		}
		catch (...) {
			TITANIUM_LOG_ERROR("API::connect: Error");
		}
		// TODO Clean up the socket and writer!
		done();
	}

	API::API(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::API(js_context) {
	}

	API::~API() TITANIUM_NOEXCEPT
	{
		done__ = true;
	}

	void API::log(const std::string& message) const TITANIUM_NOEXCEPT
	{
		concurrency::asend(buffer__, message);
	}

	void API::JSExportInitialize() {
		JSExport<API>::SetClassVersion(1);
		JSExport<API>::SetParent(JSExport<Titanium::API>::Class());
	}

	void API::postInitialize(JSObject& this_object) 
	{
		connect();
	}

	void API::connect() {
		done__ = false;
		reader__.start();
	}
}  // namespace TitaniumWindows
