/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_APPLICATIONBUILDER_HPP_
#define _TITANIUM_APPLICATIONBUILDER_HPP_

#include "Titanium/Application.hpp"
#include <memory>

namespace Titanium {
  
  using namespace HAL;
  
  using JSClassPtr_t = std::shared_ptr<JSClass>;
  
  class TITANIUMKIT_EXPORT ApplicationBuilder final {
    
  public:

    ApplicationBuilder(const JSClassPtr_t& global_object_class_ptr) TITANIUM_NOEXCEPT;
    Application build();
    
    JSClassPtr_t        APIClass() const                 TITANIUM_NOEXCEPT;
    ApplicationBuilder& APIClass(const JSClassPtr_t&)    TITANIUM_NOEXCEPT;
    
    JSClassPtr_t        ViewClass() const                TITANIUM_NOEXCEPT;
    ApplicationBuilder& ViewClass(const JSClassPtr_t&)   TITANIUM_NOEXCEPT;
    
    JSClassPtr_t        WindowClass() const              TITANIUM_NOEXCEPT;
    ApplicationBuilder& WindowClass(const JSClassPtr_t&) TITANIUM_NOEXCEPT;
    
    JSClassPtr_t        ButtonClass() const              TITANIUM_NOEXCEPT;
    ApplicationBuilder& ButtonClass(const JSClassPtr_t&) TITANIUM_NOEXCEPT;
      
    JSClassPtr_t        PlatformClass() const                 TITANIUM_NOEXCEPT;
    ApplicationBuilder& PlatformClass(const JSClassPtr_t&)    TITANIUM_NOEXCEPT;
    
    JSClassPtr_t        AccelerometerClass() const              TITANIUM_NOEXCEPT;
    ApplicationBuilder& AccelerometerClass(const JSClassPtr_t&) TITANIUM_NOEXCEPT;
    
    JSClassPtr_t        GestureClass() const                 TITANIUM_NOEXCEPT;
    ApplicationBuilder& GestureClass(const JSClassPtr_t&)    TITANIUM_NOEXCEPT;
    
    JSClassPtr_t        BlobClass() const                 TITANIUM_NOEXCEPT;
    ApplicationBuilder& BlobClass(const JSClassPtr_t&)    TITANIUM_NOEXCEPT;
    
    JSClassPtr_t        FileClass() const                 TITANIUM_NOEXCEPT;
    ApplicationBuilder& FileClass(const JSClassPtr_t&)    TITANIUM_NOEXCEPT;

    JSClassPtr_t        FilesystemClass() const                 TITANIUM_NOEXCEPT;
    ApplicationBuilder& FilesystemClass(const JSClassPtr_t&)    TITANIUM_NOEXCEPT;

    virtual ~ApplicationBuilder() = default;
    ApplicationBuilder(const ApplicationBuilder&)            = default;
    ApplicationBuilder& operator=(const ApplicationBuilder&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    ApplicationBuilder(ApplicationBuilder&&)                 = default;
    ApplicationBuilder& operator=(ApplicationBuilder&&)      = default;
#endif
    
  private:
    
    friend class Application;
    
    // Silence 4251 on Windows since private member variables do not
    // need to be exported from a DLL.
#pragma warning(push)
#pragma warning(disable: 4251)
    JSClassPtr_t   global_object_class_ptr__ { nullptr };
    JSClassPtr_t   api_class_ptr__           { nullptr };
    JSClassPtr_t   view_class_ptr__          { nullptr };
    JSClassPtr_t   window_class_ptr__        { nullptr };
    JSClassPtr_t   button_class_ptr__        { nullptr };
    JSClassPtr_t   platform_class_ptr__      { nullptr };
    JSClassPtr_t   accelerometer_class_ptr__ { nullptr };
    JSClassPtr_t   gesture_class_ptr__       { nullptr };
    JSClassPtr_t   blob_class_ptr__          { nullptr };
    JSClassPtr_t   file_class_ptr__          { nullptr };
    JSClassPtr_t   filesystem_class_ptr__    { nullptr };

    JSContextGroup js_context_group__;
    JSContext      js_context__;
#pragma warning(pop)
};
  
} // namespace Titanium {

#endif // _TITANIUM_APPLICATIONBUILDER_HPP_
