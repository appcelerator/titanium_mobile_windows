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
		enum ValueType _getValueType(const std::string& value)
		{
			if (value == "UI.SIZE") {
				return Size;
			} else if (value == "UI.FILL") {
				return Fill;
			} else if (value == "NONE") {
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
				if ((value.find("mm") != std::string::npos) || (value.find("cm") != std::string::npos) ||
				    (value.find("em") != std::string::npos) || (value.find("pt") != std::string::npos) ||
				    (value.find("pc") != std::string::npos) ||
				    (value.find("in") != std::string::npos) || (value.find("px") != std::string::npos) ||
				    (value.find("dp") != std::string::npos) || (value.find("dip") != std::string::npos)) {
					if ((value.find("dip") != std::string::npos)) {
						units = value.substr(value.size() - 3, 3);
						parsedValue = atof(value.substr(0, value.size() - 3).c_str());
					} else {
						units = value.substr(value.size() - 2, 2);
						parsedValue = atof(value.substr(0, value.size() - 2).c_str());
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
