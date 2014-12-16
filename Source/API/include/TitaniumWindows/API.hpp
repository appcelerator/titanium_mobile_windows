/**
 * Titanium.API for Windows
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_API_HPP_
#define _TITANIUMWINDOWS_API_HPP_

#include "TitaniumWindows/detail/APIBase.hpp"

namespace TitaniumWindows {

  using namespace HAL;

  /*!
    @class

    @discussion This is the Titanium.API implementation for Windows.
    */
  class TITANIUMWINDOWS_API_EXPORT API final : public Titanium::API, public JSExport < API > {

  public:

    API(const JSContext& js_context)                       TITANIUM_NOEXCEPT;
    API(const API&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

    virtual ~API()             = default;
    API(const API&)            = default;
    API& operator=(const API&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    API(API&&)                 = default;
    API& operator=(API&&)      = default;
#endif

    static void JSExportInitialize();

  protected:

    virtual void log(const std::string& message) const TITANIUM_NOEXCEPT override final;

  private:

    Windows::Networking::Sockets::StreamSocket^ tcp_socket_ { nullptr };
    Windows::Storage::Streams::DataWriter^ tcp_writer_ { nullptr };

    void connect();
  };

}  // namespace TitaniumWindows

#endif // _TITANIUMWINDOWS_API_HPP_
