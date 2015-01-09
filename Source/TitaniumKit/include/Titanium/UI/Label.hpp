/**
 * TitaniumKit
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_LABEL_HPP_
#define _TITANIUM_UI_LABEL_HPP_

#include "Titanium/UI/Constants.hpp"
#include "Titanium/UI/View.hpp"

namespace Titanium
{
namespace UI
{
using namespace HAL;

/*!
   @class

   @discussion This is the Titanium UI Label.

   See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.Label
   */
class TITANIUMKIT_EXPORT Label : public View, public JSExport<Label>
{
   public:
	/*!
    @method

    @abstract color : String

    @discussion Color of the label text, as a color name or hex triplet.
    */
	virtual JSValue get_color() const TITANIUM_NOEXCEPT final;
	virtual void set_color(const JSValue& color) TITANIUM_NOEXCEPT;

	/*!
    @method

    @abstract font : Font

    @discussion Font to use for the label text.
    */
	virtual JSValue get_font() const TITANIUM_NOEXCEPT final;
	virtual void set_fontFamily(const JSValue& family) TITANIUM_NOEXCEPT;
	virtual void set_fontSize(const JSValue& size) TITANIUM_NOEXCEPT;
	virtual void set_fontStyle(const JSValue& style) TITANIUM_NOEXCEPT;
	virtual void set_fontWeight(const JSValue& weight) TITANIUM_NOEXCEPT;
	virtual void set_textStyle(const TEXT_STYLE& style) TITANIUM_NOEXCEPT;

	/*!
     @method

     @abstract text : String

     @discussion Label text.
    */
	virtual JSValue get_text() const TITANIUM_NOEXCEPT final;
	virtual void set_text(const JSValue& title) TITANIUM_NOEXCEPT;

	/*!
     @method

     @abstract textAlign : String/Number

     @discussion Text alignment.
    */
	virtual TEXT_ALIGNMENT get_textAlign() const TITANIUM_NOEXCEPT final;
	virtual void set_textAlign(const TEXT_ALIGNMENT& textAlign) TITANIUM_NOEXCEPT;

	/*!
    @method

    @abstract verticalAlign : String/Number

    @discussion Vertical text alignment, specified using one of the vertical alignment constants from Titanium.UI.
    */
	virtual TEXT_VERTICAL_ALIGNMENT get_verticalAlign() const TITANIUM_NOEXCEPT final;
	virtual void set_verticalAlign(const TEXT_VERTICAL_ALIGNMENT& verticalAlign) TITANIUM_NOEXCEPT;

	/*!
    @method

    @abstract wordWrap : Boolean

    @discussion Enable or disable word wrapping in the label.
    */
	virtual JSValue get_wordWrap() const TITANIUM_NOEXCEPT final;
	virtual void set_wordWrap(const JSValue& wordWrap) TITANIUM_NOEXCEPT;

	Label(const JSContext& js_context) TITANIUM_NOEXCEPT;
	Label(const Label&, const std::vector<JSValue>& arguments) TITANIUM_NOEXCEPT;

	virtual ~Label() = default;
	Label(const Label&) = default;
	Label& operator=(const Label&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
	Label(Label&&) = default;
	Label& operator=(Label&&) = default;
#endif

	// TODO: The following functions can automatically be generated
	// from the YAML API docs.
	static void JSExportInitialize();

	virtual JSValue getColorArgumentValidator() const TITANIUM_NOEXCEPT final;
	virtual bool setColorArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;

	virtual JSValue getFontArgumentValidator() const TITANIUM_NOEXCEPT final;
	virtual bool setFontArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;

	virtual JSValue getTextArgumentValidator() const TITANIUM_NOEXCEPT final;
	virtual bool setTextArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;

	virtual JSValue getTextAlignArgumentValidator() const TITANIUM_NOEXCEPT final;
	virtual bool setTextAlignArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;

	virtual JSValue getVerticalAlignArgumentValidator() const TITANIUM_NOEXCEPT final;
	virtual bool setVerticalAlignArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;

	virtual JSValue getWordWrapArgumentValidator() const TITANIUM_NOEXCEPT final;
	virtual bool setWordWrapArgumentValidator(const JSValue& argument) TITANIUM_NOEXCEPT final;

   private:
	JSValue color__;
	JSObject font__;
	JSValue text__;
	TEXT_ALIGNMENT textAlign__;
	TEXT_VERTICAL_ALIGNMENT verticalAlign__;
	JSValue wordWrap__;
};
}
}  // namespace Titanium { namespace UI {

#endif  // _TITANIUM_UI_LABEL_HPP_
