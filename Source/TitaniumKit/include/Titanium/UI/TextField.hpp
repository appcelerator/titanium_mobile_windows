/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_TEXTFIELD_HPP_
#define _TITANIUM_UI_TEXTFIELD_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Constants.hpp"

namespace Titanium { namespace UI {
  
  using namespace HAL;
  
  /*!
   @class
   
   @discussion This is the Titanium.UI.TextField module.
   
   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.TextField
   */
  class TITANIUMKIT_EXPORT TextField : public View, public JSExport<TextField> {
    
  public:
    
    /*!
     @method
     
     @abstract borderStyle : Number

     @discussion Border style for the field.
     */
    virtual INPUT_BORDERSTYLE get_borderStyle() const                               TITANIUM_NOEXCEPT final;
    virtual void              set_borderStyle(const INPUT_BORDERSTYLE& borderStyle) TITANIUM_NOEXCEPT;
    
    /*!
     @method
     
     @abstract clearButtonMode : Number
     
     @discussion Determines when the clear button is displayed.
     */
    virtual INPUT_BUTTONMODE get_clearButtonMode() const                               TITANIUM_NOEXCEPT final;
    virtual void             set_clearButtonMode(const INPUT_BUTTONMODE& clearButtonMode) TITANIUM_NOEXCEPT;

    /*!
     @method
     
     @abstract leftButtonMode : Number
     
     @discussion Determines when to display the left button view.
     */
    virtual INPUT_BUTTONMODE get_leftButtonMode() const                                 TITANIUM_NOEXCEPT final;
    virtual void             set_leftButtonMode(const INPUT_BUTTONMODE& leftButtonMode) TITANIUM_NOEXCEPT;
    
    /*!
     @method
     
     @abstract rightButtonMode : Number
     
     @discussion Determines when to display the right button view.
     */
    virtual INPUT_BUTTONMODE get_rightButtonMode() const                                  TITANIUM_NOEXCEPT final;
    virtual void             set_rightButtonMode(const INPUT_BUTTONMODE& rightButtonMode) TITANIUM_NOEXCEPT;

    /*!
     @method
     
     @abstract keyboardType : Number
     
     @discussion Keyboard type to display when this text field is
     focused. When asking for a specific kind of user input, such as a
     phone number or email address, you should always specify the
     appropriate keyboard type.
     */
    virtual KEYBOARD get_keyboardType() const                       TITANIUM_NOEXCEPT final;
    virtual void     set_keyboardType(const KEYBOARD& keyboardType) TITANIUM_NOEXCEPT;

    /*!
     @method
     
     @abstract returnKeyType : Number
     
     @discussion Specifies the text to display on the keyboard Return key when this field is focused.
     */
    virtual RETURNKEY get_returnKeyType() const                         TITANIUM_NOEXCEPT final;
    virtual void      set_returnKeyType(const RETURNKEY& returnKeyType) TITANIUM_NOEXCEPT;

    /*!
     @method
     
     @abstract textAlign : String/Number
     
     @discussion Text alignment within this text field.
     */
    virtual TEXT_ALIGNMENT get_textAlign() const                          TITANIUM_NOEXCEPT final;
    virtual void           set_textAlign(const TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT;

    /*!
     @method
     
     @abstract autocapitalization : Number
     
     @discussion Determines how text is capitalized during typing.
     */
    virtual TEXT_AUTOCAPITALIZATION get_autoCapitalization() const                                            TITANIUM_NOEXCEPT final;
    virtual void                    set_autoCapitalization(const TEXT_AUTOCAPITALIZATION& autoCapitalization) TITANIUM_NOEXCEPT;

    /*!
     @method
     
     @abstract verticalAlign : Number/String
     
     @discussion Vertical alignment within this text field.
     */
    virtual TEXT_VERTICAL_ALIGNMENT get_verticalAlign() const                                       TITANIUM_NOEXCEPT final;
    virtual void                    set_verticalAlign(const TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT;

    TextField(const JSContext& js_context)                             TITANIUM_NOEXCEPT;
    TextField(const TextField&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;
    
    virtual ~TextField()                   = default;
    TextField(const TextField&)            = default;
    TextField& operator=(const TextField&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
    TextField(TextField&&)                 = default;
    TextField& operator=(TextField&&)      = default;
#endif
    
    // TODO: The following functions can automatically be generated
    // from the YAML API docs.
    static void JSExportInitialize();
    
    virtual JSValue getBorderStyleArgumentValidator() const                         TITANIUM_NOEXCEPT final;
    virtual bool    setBorderStyleArgumentValidator(const JSValue& argument)        TITANIUM_NOEXCEPT final;
    
    virtual JSValue getClearButtonModeArgumentValidator() const                     TITANIUM_NOEXCEPT final;
    virtual bool    setClearButtonModeArgumentValidator(const JSValue& argument)    TITANIUM_NOEXCEPT final;

    virtual JSValue getLeftButtonModeArgumentValidator() const                      TITANIUM_NOEXCEPT final;
    virtual bool    setLeftButtonModeArgumentValidator(const JSValue& argument)     TITANIUM_NOEXCEPT final;

    virtual JSValue getRightButtonModeArgumentValidator() const                     TITANIUM_NOEXCEPT final;
    virtual bool    setRightButtonModeArgumentValidator(const JSValue& argument)    TITANIUM_NOEXCEPT final;
    
    virtual JSValue getKeyboardTypeArgumentValidator() const                        TITANIUM_NOEXCEPT final;
    virtual bool    setKeyboardTypeArgumentValidator(const JSValue& argument)       TITANIUM_NOEXCEPT final;
    
    virtual JSValue getReturnKeyTypeArgumentValidator() const                       TITANIUM_NOEXCEPT final;
    virtual bool    setReturnKeyTypeArgumentValidator(const JSValue& argument)      TITANIUM_NOEXCEPT final;
    
    virtual JSValue getTextAlignArgumentValidator() const                           TITANIUM_NOEXCEPT final;
    virtual bool    setTextAlignArgumentValidator(const JSValue& argument)          TITANIUM_NOEXCEPT final;

    virtual JSValue getAutoCapitalizationArgumentValidator() const                  TITANIUM_NOEXCEPT final;
    virtual bool    setAutoCapitalizationArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;
    
    virtual JSValue getVerticalAlignArgumentValidator() const                       TITANIUM_NOEXCEPT final;
    virtual bool    setVerticalAlignArgumentValidator(const JSValue& argument)      TITANIUM_NOEXCEPT final;

  private:
    
    INPUT_BORDERSTYLE       borderStyle__;
    INPUT_BUTTONMODE        clearButtonMode__;
    INPUT_BUTTONMODE        leftButtonMode__;
    INPUT_BUTTONMODE        rightButtonMode__;
    KEYBOARD                keyboardType__;
    RETURNKEY               returnKeyType__;
    TEXT_ALIGNMENT          textAlign__;
    TEXT_AUTOCAPITALIZATION autoCapitalization__;
    TEXT_VERTICAL_ALIGNMENT verticalAlign__;
  };
}} // namespace Titanium { namespace UI {

#endif // _TITANIUM_UI_TEXTFIELD_HPP_
