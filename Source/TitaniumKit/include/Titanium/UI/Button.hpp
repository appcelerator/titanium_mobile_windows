/**
 * TitaniumKit
 *
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_BUTTON_HPP_
#define _TITANIUM_UI_BUTTON_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Font.hpp"

namespace Titanium
{
	class Blob;

	namespace UI
	{
		using namespace HAL;

		/*!
		  @class

		  @discussion This is the Titanium UI Button.

		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.Button
		*/
		class TITANIUMKIT_EXPORT Button : public View, public JSExport<Button>
		{
		public:

			/*!
			  @method

			  @abstract color : String

			  @discussion Default button text color, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, color);

			/*!
			  @method

			  @abstract font : Font

			  @discussion Font to use for the button text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Font, font);

			/*!
			  @method

			  @abstract image : String/Titanium.Blob

			  @discussion Image to display on the button, specified as a local path, URL or a Blob.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, image);
			TITANIUM_PROPERTY_IMPL_DEF(std::shared_ptr<Titanium::Blob>, imageAsBlob);

			/*!
			  @method

			  @abstract textAlign : String/Number

			  @discussion Text alignment.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(TEXT_ALIGNMENT, textAlign);

			/*!
			@method

			@abstract title : String

			@discussion Key identifying a string from the locale file to use for the button title.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, titleid);

			/*!
			  @method

			  @abstract title : String

			  @discussion Button title.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, title);

			/*!
			  @method

			  @abstract verticalAlign : String/Number

			  @discussion Vertical text alignment, specified using one of the vertical alignment constants from Titanium.UI.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(TEXT_VERTICAL_ALIGNMENT, verticalAlign);

			Button(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~Button() TITANIUM_NOEXCEPT;  //= default;
			Button(const Button&) = default;
			Button& operator=(const Button&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Button(Button&&) = default;
			Button& operator=(Button&&) = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(color);
			TITANIUM_FUNCTION_DEF(setColor);
			TITANIUM_FUNCTION_DEF(getColor);

			TITANIUM_PROPERTY_DEF(font);
			TITANIUM_FUNCTION_DEF(setFont);
			TITANIUM_FUNCTION_DEF(getFont);

			TITANIUM_PROPERTY_DEF(image);
			TITANIUM_FUNCTION_DEF(setImage);
			TITANIUM_FUNCTION_DEF(getImage);

			TITANIUM_PROPERTY_DEF(textAlign);
			TITANIUM_FUNCTION_DEF(getTextAlign);
			TITANIUM_FUNCTION_DEF(setTextAlign);

			TITANIUM_PROPERTY_DEF(titleid);
			TITANIUM_FUNCTION_DEF(setTitleid);
			TITANIUM_FUNCTION_DEF(getTitleid);

			TITANIUM_PROPERTY_DEF(title);
			TITANIUM_FUNCTION_DEF(setTitle);
			TITANIUM_FUNCTION_DEF(getTitle);

			TITANIUM_PROPERTY_DEF(verticalAlign);
			TITANIUM_FUNCTION_DEF(getVerticalAlign);
			TITANIUM_FUNCTION_DEF(setVerticalAlign);

		private:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string color__;
			Font font__;
			std::string image__;
			std::shared_ptr<Titanium::Blob> imageAsBlob__;
			TEXT_ALIGNMENT textAlign__;
			std::string title__;
			std::string titleid__;
			TEXT_VERTICAL_ALIGNMENT verticalAlign__;
#pragma warning(pop)
		};
	} // namespace UI
}  // namespace Titanium

#endif  // _TITANIUM_UI_BUTTON_HPP_
