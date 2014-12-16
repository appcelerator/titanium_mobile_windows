/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_DIMENSION_HPP_
#define _TITANIUM_UI_DIMENSION_HPP_

#include "Titanium/detail/TiBase.hpp"

namespace Titanium { namespace UI {
  
  using namespace HAL;
  
  /*!
   @class
   
   @discussion This is the Titanium Dimension.
   
   See http://docs.appcelerator.com/titanium/latest/#!/api/Dimension
   */
  class TITANIUMKIT_EXPORT Dimension final : public JSExportObject, public JSExport<Dimension> {
    
  public:
    
    virtual JSNumber get_height() const                 TITANIUM_NOEXCEPT final;
    virtual void     set_height(const JSNumber& height) TITANIUM_NOEXCEPT final;
    
    virtual JSNumber get_width() const                  TITANIUM_NOEXCEPT final;
    virtual void     set_width(const JSNumber& width)   TITANIUM_NOEXCEPT final;
    
    virtual JSNumber get_x() const                      TITANIUM_NOEXCEPT final;
    virtual void     set_x(const JSNumber& x)           TITANIUM_NOEXCEPT final;
    
    virtual JSNumber get_y() const                      TITANIUM_NOEXCEPT final;
    virtual void     set_y(const JSNumber& y)           TITANIUM_NOEXCEPT final;
    
    Dimension(const JSContext& js_context)                             TITANIUM_NOEXCEPT;
    Dimension(const Dimension&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~Dimension()                      = default;
    Dimension(const Dimension&)               = default;
    Dimension& operator=(const Dimension&)    = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    Dimension(Dimension&&)                    = default;
    Dimension& operator=(Dimension&&)         = default;
#endif
    
    // TODO: The following functions can automatically be generated
    // from the YAML API docs.
    static void JSExportInitialize();
    bool setHeightArgumentValidator(const JSValue& argument);
    bool setWidthArgumentValidator(const JSValue& argument);
    bool setXArgumentValidator(const JSValue& argument);
    bool setYArgumentValidator(const JSValue& argument);
    
  private:
    
    JSNumber height__;
    JSNumber width__;
    JSNumber x__;
    JSNumber y__;
    
  };
}} // namespace Titanium { namespace UI {

#endif // _TITANIUM_UI_DIMENSION_HPP_
