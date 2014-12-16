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

namespace TitaniumWindows {

  API::API(const JSContext& js_context) TITANIUM_NOEXCEPT
    : Titanium::API(js_context) {
    TITANIUM_LOG_DEBUG("API::ctor Initialize");
    connect();
  }

  API::API(const API& rhs, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT
    : Titanium::API(rhs, arguments) {
    TITANIUM_LOG_DEBUG("API::ctor CallAsConstructor");
  }

  void API::log(const std::string& message) const TITANIUM_NOEXCEPT{
    TITANIUM_LOG_DEBUG("API::log");

    // send message to Titanium CLI log relay
    if (tcp_socket_ != nullptr && tcp_writer_ != nullptr) {
      tcp_writer_->WriteString(TitaniumWindows::Utility::ConvertString(message) + "\n"); // Logger assumes \n for newlines!
      tcp_writer_->StoreAsync();
    } else {
      // TODO If the socket isn't connected yet, we should probably store the logs in a queue to get sent along
      std::clog << message << std::endl;
    }
  }

  void API::JSExportInitialize() {
    JSExport<API>::SetClassVersion(1);
    JSExport<API>::SetParent(JSExport<Titanium::API>::Class());
  }

  void API::connect() {
    using namespace TitaniumWindows::Utility;
    using namespace Windows::Storage;
    using namespace Windows::Networking;
    using namespace concurrency;
    // Get a handle on titanium_settings.ini file
    auto get_file_task = create_task(Windows::ApplicationModel::Package::Current->InstalledLocation->GetFileAsync("titanium_settings.ini"));
    
    // Read titanium_settings.ini file into String
    get_file_task.then([this](StorageFile^ storage_file)
    {
        return FileIO::ReadTextAsync(storage_file);
    })
    // Parse the ini, try to connect using settinsg found in INI
    .then([this](task<Platform::String^> antecedent)
    {
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
      Platform::String^ port = ConvertString(pt.get<std::string>("tcpPort"));
      Platform::String^ server_token = ConvertString(pt.get<std::string>("serverToken"));

      std::vector<std::string> hosts;
      std::string ip_address_list = pt.get<std::string>("ipAddressList");
      boost::algorithm::split(hosts, ip_address_list, boost::algorithm::is_any_of(","));

      for (auto ip_address : hosts) {
        TITANIUM_LOG_DEBUG("API::connect: Trying to connect to log server: ", ip_address, ":", ConvertString(port));
        
        try {
          // Connect to the tcp socket on log relay!
          tcp_socket_ = ref new Sockets::StreamSocket();
          tcp_socket_->Control->KeepAlive = true;

          // TODO Set timeout based on value from ini! We need to use a cancellation token somehow!

          Windows::Networking::HostName^ host = ref new HostName(ConvertString(ip_address));

          event connect_event;
          task<void>(tcp_socket_->ConnectAsync(host, port)).then([this, &connect_event](task<void> task) {
            try {
              task.get();
              tcp_writer_ = ref new Streams::DataWriter(tcp_socket_->OutputStream);
            }
            catch (Platform::COMException^ e) {
              // We need to try next IP! So lets log this and wipe the socket out
              TITANIUM_LOG_DEBUG(e->Message->Data());
              delete tcp_socket_;
              tcp_socket_ = nullptr;
            }
            connect_event.set();
          }, task_continuation_context::use_arbitrary());
          connect_event.wait();

          // we write the server token to see if this log relay is really the log relay we're looking for
          if (tcp_writer_ != nullptr) {
            log(ConvertString(server_token));
            break;
          }
        }
        catch (Platform::COMException^ e) {
          delete tcp_socket_;
          tcp_socket_ = nullptr;
          delete tcp_writer_;
          tcp_writer_ = nullptr;
          // try next ip!
          TITANIUM_LOG_DEBUG("API::connect: Trying to connect failed, trying next IP...");
        }
      }
    });
  }

}  // namespace TitaniumWindows
