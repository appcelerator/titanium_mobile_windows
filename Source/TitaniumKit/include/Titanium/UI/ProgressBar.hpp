/**
 * TitaniumKit Titanium.UI.ProgressBar
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_UI_PROGRESSBAR_HPP_
#define _TITANIUM_UI_PROGRESSBAR_HPP_

#include "Titanium/UI/Font.hpp"
#include "Titanium/UI/View.hpp"

namespace Titanium
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium ProgressBar Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.ProgressBar
		*/
		class TITANIUMKIT_EXPORT ProgressBar : public View, public JSExport<ProgressBar>
		{

		public:

			/*!
			  @property
			  @abstract backgroundColor
			  @discussion Background color of the view, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundColor);

			/*!
			  @property
			  @abstract backgroundDisabledColor
			  @discussion Disabled background color of the view, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, backgroundDisabledColor);

			/*!
			  @property
			  @abstract color
			  @discussion Color of the progress bar text, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, color);

			/*!
			  @property
			  @abstract font
			  @discussion Font for the progress bar text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Font, font);

			/*!
			  @property
			  @abstract max
			  @discussion Maximum value of the progress bar.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, max);

			/*!
			  @property
			  @abstract message
			  @discussion Progress bar text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, message);

			/*!
			  @property
			  @abstract min
			  @discussion Minimum value of the progress bar.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, min);

			/*!
			  @property
			  @abstract value
			  @discussion Current value of the progress bar.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(double, value);

			ProgressBar(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ProgressBar() = default;
			ProgressBar(const ProgressBar&) = default;
			ProgressBar& operator=(const ProgressBar&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ProgressBar(ProgressBar&&)                 = default;
			ProgressBar& operator=(ProgressBar&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(backgroundColor);
			TITANIUM_PROPERTY_DEF(backgroundDisabledColor);
			TITANIUM_PROPERTY_DEF(color);
			TITANIUM_PROPERTY_DEF(font);
			TITANIUM_PROPERTY_DEF(max);
			TITANIUM_PROPERTY_DEF(message);
			TITANIUM_PROPERTY_DEF(min);
			TITANIUM_PROPERTY_DEF(style);
			TITANIUM_PROPERTY_DEF(value);

			TITANIUM_FUNCTION_DEF(remove);
			TITANIUM_FUNCTION_DEF(add);
			TITANIUM_FUNCTION_DEF(getBackgroundColor);
			TITANIUM_FUNCTION_DEF(setBackgroundColor);
			TITANIUM_FUNCTION_DEF(getBackgroundDisabledColor);
			TITANIUM_FUNCTION_DEF(setBackgroundDisabledColor);
			TITANIUM_FUNCTION_DEF(getColor);
			TITANIUM_FUNCTION_DEF(setColor);
			TITANIUM_FUNCTION_DEF(getFont);
			TITANIUM_FUNCTION_DEF(setFont);
			TITANIUM_FUNCTION_DEF(getMax);
			TITANIUM_FUNCTION_DEF(setMax);
			TITANIUM_FUNCTION_DEF(getMessage);
			TITANIUM_FUNCTION_DEF(setMessage);
			TITANIUM_FUNCTION_DEF(getMin);
			TITANIUM_FUNCTION_DEF(setMin);
			TITANIUM_FUNCTION_DEF(getStyle);
			TITANIUM_FUNCTION_DEF(setStyle);
			TITANIUM_FUNCTION_DEF(getValue);
			TITANIUM_FUNCTION_DEF(setValue);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string backgroundColor__;
			std::string backgroundDisabledColor__;
			std::string color__;
			Font font__;
			double max__;
			std::string message__;
			double min__;
			double value__;
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_UI_PROGRESSBAR_HPP_