/**
 * TitaniumKit Titanium.UI.ActivityIndicator
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUM_ACTIVITYINDICATOR_HPP_
#define _TITANIUM_ACTIVITYINDICATOR_HPP_

#include "Titanium/UI/View.hpp"
#include "Titanium/UI/Font.hpp"
#include "Titanium/UI/ActivityIndicatorStyle.hpp"

namespace Titanium
{
	namespace UI
	{

		using namespace HAL;

		/*!
		  @class
		  @discussion This is the Titanium ActivityIndicator Module.
		  See http://docs.appcelerator.com/titanium/latest/#!/api/Titanium.UI.ActivityIndicator
		*/
		class TITANIUMKIT_EXPORT ActivityIndicator : public View, public JSExport<ActivityIndicator>
		{

		public:

			/*!
			  @property
			  @abstract color
			  @discussion Color of the message text, as a color name or hex triplet.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, color);

			/*!
			  @property
			  @abstract font
			  @discussion Font used for the message text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(Font, font);

			/*!
			  @property
			  @abstract message
			  @discussion Message text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, message);

			/*!
			  @property
			  @abstract messageid
			  @discussion Key identifying a string in the locale file to use for the message text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, messageid);

			/*!
			  @property
			  @abstract style
			  @discussion The style for the activity indicator.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(ACTIVITY_INDICATOR_STYLE, style);

			/*!
			@property
			@abstract indicatorColor
			@discussion Color of the animated indicator.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, indicatorColor);

			/*!
			@property
			@abstract indicatorDiameter
			@discussion Diameter of the indicator. The diameter of the animated indicator, exclusive of any message text.
			*/
			TITANIUM_PROPERTY_IMPL_DEF(std::string, indicatorDiameter);

			ActivityIndicator(const JSContext&) TITANIUM_NOEXCEPT;

			virtual ~ActivityIndicator() = default;
			ActivityIndicator(const ActivityIndicator&) = default;
			ActivityIndicator& operator=(const ActivityIndicator&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			ActivityIndicator(ActivityIndicator&&)                 = default;
			ActivityIndicator& operator=(ActivityIndicator&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(color);
			TITANIUM_PROPERTY_DEF(font);
			TITANIUM_PROPERTY_DEF(message);
			TITANIUM_PROPERTY_DEF(messageid);
			TITANIUM_PROPERTY_DEF(style);
			TITANIUM_PROPERTY_DEF(indicatorColor);
			TITANIUM_PROPERTY_DEF(indicatorDiameter);

			TITANIUM_FUNCTION_DEF(getColor);
			TITANIUM_FUNCTION_DEF(setColor);
			TITANIUM_FUNCTION_DEF(getFont);
			TITANIUM_FUNCTION_DEF(setFont);
			TITANIUM_FUNCTION_DEF(getMessage);
			TITANIUM_FUNCTION_DEF(setMessage);
			TITANIUM_FUNCTION_DEF(getMessageid);
			TITANIUM_FUNCTION_DEF(setMessageid);
			TITANIUM_FUNCTION_DEF(getStyle);
			TITANIUM_FUNCTION_DEF(setStyle);
			TITANIUM_FUNCTION_DEF(getIndicatorColor);
			TITANIUM_FUNCTION_DEF(setIndicatorColor);
			TITANIUM_FUNCTION_DEF(getIndicatorDiameter);
			TITANIUM_FUNCTION_DEF(setIndicatorDiameter);

		protected:
#pragma warning(push)
#pragma warning(disable : 4251)
			std::string color__;
			Font font__;
			std::string message__;
			std::string messageid__;
			std::string indicatorColor__;
			std::string indicatorDiameter__;
			ACTIVITY_INDICATOR_STYLE style__;
#pragma warning(pop)
		};

	} // namespace UI
} // namespace Titanium
#endif // _TITANIUM_ACTIVITYINDICATOR_HPP_