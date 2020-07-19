/**
 * LayoutEngine
 * Author: Russell W. McMahon
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "LayoutEngine/LayoutEngine.hpp"

#include <stdlib.h>
#include <string>

namespace Titanium
{
	namespace LayoutEngine
	{
		double PhysicalPixelsFactor = 1.0;

		enum ValueType _getValueType(const std::string& value)
		{
			if (value == "UI.SIZE") {
				return Size;
			} else if (value == "UI.FILL") {
				return Fill;
			} else if (value.empty() || value == "NONE" || value == "undefined") {
				return None;
			} else if (value.find("%") != std::string::npos) {
				return Percent;
			} else {
				return Fixed;
			}
		}

		double _computeValue(const std::string& value, enum ValueType valueType, double ppi, const std::string& defaultUnits)
		{
			std::string units;
			double parsedValue = 0;

			if (valueType == Percent) {
				return atof(value.c_str()) / 100;
			} else if (valueType == Fixed) {
				const auto value_size = value.size();
				const auto units2 = value_size > 2 ? value.substr(value_size - 2, 2) : value;
				const auto units3 = value_size > 3 ? value.substr(value_size - 3, 3) : value;
				if ((units2 == "mm") || (units2 == "cm")  ||
				    (units2 == "em") || (units2 == "pt")  ||
				    (units2 == "pc") || (units3 == "ppx") ||
				    (units2 == "in") || (units2 == "px")  ||
				    (units2 == "dp") || (units3 == "dip")) {
					if ((units3 == "dip") || (units3 == "ppx")) {
						units = units3;
						parsedValue = atof(value.substr(0, value_size - 3).c_str());
					} else {
						units = units2;
						parsedValue = atof(value.substr(0, value_size - 2).c_str());
					}
				} else {
					parsedValue = atof(value.c_str());
					units = defaultUnits;
				}

				if (units == "mm") { // 1 mm = 0.0393701 in, 1 in = 25.4 mm
					return (parsedValue / 25.4) * ppi; // px = (mm / 25.4) * px/in
				} else if (units == "cm") { // 1 cm = .393700787 in, 1 in = 2.54 cm
					return (parsedValue / 2.54) * ppi; // px = (cm / 2.54) * px/in
				} else if (units == "em" || units == "pt") { // 1 inch = 72 pt // FIXME em = font size for element
					return (parsedValue / 72.0) * ppi; // px = (pt / 72) * px/in
				} else if (units == "pc") { // pica, 1/6th inch. 1 pc = 12 pt
					return (parsedValue / 6.0) * ppi; // px = (pc / 6) * px/in
				} else if (units == "in") {
					return parsedValue * ppi; // px = inches * pixels/inch
				} else if (units == "px") {
					return parsedValue; // px is our base value
				} else if (units == "dp" || units == "dip") { 
					return (parsedValue * ppi) / 160.0; // px = device independent pixels * pixels/inch / 160, see https://www.google.com/design/spec/layout/units-measurements.html#units-measurements-designing-layouts-for-dp
				} else if (units == "ppx") {
					return parsedValue / PhysicalPixelsFactor;
				}
			}
			return 0;
		}

		double parseUnitValue(const std::string& value, enum ValueType valueType, double ppi, const std::string& defaultUnits)
		{
			return _computeValue(value, valueType, ppi, defaultUnits);
		}

		void populateLayoutProperties(struct InputProperty inputProperty, struct LayoutProperties* layoutProperties, double ppi, const std::string& defaultUnits)
		{
			switch (inputProperty.name) {
				case MinHeight:
					(*layoutProperties).minHeight.valueType = _getValueType(inputProperty.value);
					(*layoutProperties).minHeight.value = _computeValue(inputProperty.value,
					                                                    (*layoutProperties).minHeight.valueType, ppi, defaultUnits);
					break;
				case MinWidth:
					(*layoutProperties).minWidth.valueType = _getValueType(inputProperty.value);
					(*layoutProperties).minWidth.value = _computeValue(inputProperty.value,
					                                                   (*layoutProperties).minWidth.valueType, ppi, defaultUnits);
					break;
				case Width:
					(*layoutProperties).width.valueType = _getValueType(inputProperty.value);
					(*layoutProperties).width.value = _computeValue(inputProperty.value,
					                                                (*layoutProperties).width.valueType, ppi, defaultUnits);
					break;
				case Height:
					(*layoutProperties).height.valueType = _getValueType(inputProperty.value);
					(*layoutProperties).height.value = _computeValue(inputProperty.value,
					                                                 (*layoutProperties).height.valueType, ppi, defaultUnits);
					break;
				case Left:
					(*layoutProperties).left.valueType = _getValueType(inputProperty.value);
					(*layoutProperties).left.value = _computeValue(inputProperty.value,
					                                               (*layoutProperties).left.valueType, ppi, defaultUnits);
					break;
				case CenterX:
					(*layoutProperties).centerX.valueType = _getValueType(inputProperty.value);
					(*layoutProperties).centerX.value = _computeValue(inputProperty.value,
					                                                  (*layoutProperties).centerX.valueType, ppi, defaultUnits);
					break;
				case CenterY:
					(*layoutProperties).centerY.valueType = _getValueType(inputProperty.value);
					(*layoutProperties).centerY.value = _computeValue(inputProperty.value,
					                                                  (*layoutProperties).centerY.valueType, ppi, defaultUnits);
					break;
				case Right:
					(*layoutProperties).right.valueType = _getValueType(inputProperty.value);
					(*layoutProperties).right.value = _computeValue(inputProperty.value,
					                                                (*layoutProperties).right.valueType, ppi, defaultUnits);
					break;
				case Top:
					(*layoutProperties).top.valueType = _getValueType(inputProperty.value);
					(*layoutProperties).top.value = _computeValue(inputProperty.value,
					                                              (*layoutProperties).top.valueType, ppi, defaultUnits);
					break;
				case Bottom:
					(*layoutProperties).bottom.valueType = _getValueType(inputProperty.value);
					(*layoutProperties).bottom.value = _computeValue(inputProperty.value,
					                                                 (*layoutProperties).bottom.valueType, ppi, defaultUnits);
					break;
			}
		}

		void layoutPropertiesInitialize(struct LayoutProperties* layoutProperties)
		{
			(*layoutProperties).top.valueType = None;
			(*layoutProperties).bottom.valueType = None;
			(*layoutProperties).left.valueType = None;
			(*layoutProperties).right.valueType = None;
			(*layoutProperties).width.valueType = None;
			(*layoutProperties).minWidth.valueType = None;
			(*layoutProperties).height.valueType = None;
			(*layoutProperties).minHeight.valueType = None;
			(*layoutProperties).centerX.valueType = None;
			(*layoutProperties).centerY.valueType = None;
		}
	} // namespace LayoutEngine
} // namespace Titanium
