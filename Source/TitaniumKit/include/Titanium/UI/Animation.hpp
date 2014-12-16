/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_ANIMATION_HPP_
#define _TITANIUM_UI_ANIMATION_HPP_

#include "Titanium/Module.hpp"
#include "Titanium/UI/Constants.hpp"

namespace Titanium { namespace UI {
  
  using namespace HAL;
  
  /*!
   @class
   
   @discussion This is the Titanium.UI.Animation module.
   
   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.Animation
   */
  class TITANIUMKIT_EXPORT Animation : public Module, public JSExport<Animation> {
    
  public:
    
    /*!
     @method
     
     @abstract curve property: Number
     
     @discussion Animation curve or easing function to apply to the
     animation.
     */
    virtual ANIMATION_CURVE get_curve() const                       TITANIUM_NOEXCEPT final;
    virtual void            set_curve(const ANIMATION_CURVE& curve) TITANIUM_NOEXCEPT;
    
    Animation(const JSContext& js_context)                             TITANIUM_NOEXCEPT;
    Animation(const Animation&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~Animation()                   = default;
    Animation(const Animation&)            = default;
    Animation& operator=(const Animation&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    Animation(Animation&&)                 = default;
    Animation& operator=(Animation&&)      = default;
#endif
    
    // TODO: The following functions can automatically be generated
    // from the YAML API docs.
    static void JSExportInitialize();
    
    virtual JSValue getCurveArgumentValidator() const                  TITANIUM_NOEXCEPT final;
    virtual bool    setCurveArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;
    
  private:
    
    ANIMATION_CURVE curve__;
  };
}} // namespace Titanium { namespace UI {

#endif // _TITANIUM_UI_ANIMATION_HPP_
