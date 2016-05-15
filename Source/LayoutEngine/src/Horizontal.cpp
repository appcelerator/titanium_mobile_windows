/**
 * LayoutEngine
 * Author: Russell W. McMahon
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "LayoutEngine/LayoutEngine.hpp"

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <string.h>
#include <algorithm>

namespace Titanium
{
	namespace LayoutEngine
	{
		struct ComputedSize doHorizontalLayout(std::vector<struct Element*> children, double width, double height, bool isWidthSize, bool isHeightSize)
		{
			struct ComputedSize computedSize;
			struct Element* child;
			unsigned int i = 0;
			unsigned int j = 0;
			struct LayoutCoefficients layoutCoefficients;
			struct ThreeCoefficients widthLayoutCoefficients, heightLayoutCoefficients, sandboxWidthLayoutCoefficients,
			    sandboxHeightLayoutCoefficients, leftLayoutCoefficients, minWidthLayoutCoefficients, minHeightLayoutCoefficients;
			struct FourCoefficients topLayoutCoefficients;
			struct ComputedSize childSize;
			double measuredWidth = 0;
			double measuredHeight = 0;
			double measuredSandboxHeight = 0;
			double measuredSandboxWidth = 0;
			double measuredLeft = 0;
			double measuredTop = 0;
			std::string pixelUnits = "px";
			double runningHeight = 0;
			double runningWidth = 0;
			// ToDo Russ - remove hard coded c arrays
			std::vector<std::vector<Element*>> rows;
			std::vector<double> rowHeights;
			double rowHeight = 0;
			std::vector<struct Element*> deferredTopCalculations;
			double verticalAlignmentOffset = 0;
			unsigned int len = children.size();
			unsigned int rowLen = 0;
			unsigned int rowsLen = (len > 0) ? 1 : 0;
			bool percentageFix = false;

			// Calculate horizontal size and position for the children
			for (i = 0; i < len; i++) {
				child = children[i];
				(*child).measuredRunningWidth = runningWidth;

				layoutCoefficients = (*child).layoutCoefficients;
				widthLayoutCoefficients = layoutCoefficients.width;
				heightLayoutCoefficients = layoutCoefficients.height;
				sandboxWidthLayoutCoefficients = layoutCoefficients.sandboxWidth;
				leftLayoutCoefficients = layoutCoefficients.left;

				// For some reason, iOS and Android append 10% right padding to horizontal
				// views of width Ti.UI.SIZE when an element inside uses % padding this is
				// a workaround to offset the padding and keep parity with iOS and Android
				if (isWidthSize && !percentageFix && leftLayoutCoefficients.x1 > 0) {
					runningWidth -= 0.1* width;
					percentageFix = true;
				}

				// Pedro
				measuredWidth = widthLayoutCoefficients.x1 * width + widthLayoutCoefficients.x2 * (width - (isWidthSize ? 0 : runningWidth)) + widthLayoutCoefficients.x3;
				// measuredWidth = widthLayoutCoefficients.x1 * width + widthLayoutCoefficients.x2 * (width - runningWidth) + widthLayoutCoefficients.x3;

				measuredHeight = heightLayoutCoefficients.x2 == 0 ? heightLayoutCoefficients.x1 * height + heightLayoutCoefficients.x3 : NAN;

				if (isNaN(measuredWidth) || isNaN(heightLayoutCoefficients.x1)) {
					childSize = layoutNode(
					    child,
					    isNaN(measuredWidth) ? width : measuredWidth - (*child).borderLeftWidth - (*child).borderRightWidth,
					    isNaN(measuredHeight) ? height : measuredHeight - (*child).borderTopWidth - (*child).borderBottomWidth,
					    isNaN(measuredWidth),
					    isNaN(measuredHeight));

					isNaN(measuredWidth) && (measuredWidth = childSize.width + (*child).borderLeftWidth + (*child).borderRightWidth);
					isNaN(heightLayoutCoefficients.x1) && (measuredHeight = childSize.height + (*child).borderTopWidth + (*child).borderBottomWidth);

					(*child).childrenLaidOut = true;
					if (heightLayoutCoefficients.x2 != 0 && !isNaN(heightLayoutCoefficients.x2)) {
						std::clog << "Child of width SIZE and height FILL detected in a horizontal layout. Performance degradation may occur." << std::endl;
						(*child).childrenLaidOut = false;
					}
				} else {
					(*child).childrenLaidOut = false;
				}

				(*child).measuredWidth = measuredWidth;
				(*child).measuredHeight = measuredHeight;

				measuredSandboxWidth = (*child).measuredSandboxWidth = sandboxWidthLayoutCoefficients.x1 * width + sandboxWidthLayoutCoefficients.x2 + measuredWidth;

				measuredLeft = leftLayoutCoefficients.x1 * width + leftLayoutCoefficients.x2 + runningWidth;

				if (!isWidthSize && width > 0 && (int)(measuredSandboxWidth + runningWidth) > width) {
					rowsLen++;
					measuredLeft -= runningWidth;
					runningWidth = 0;
				}

				(*child).measuredLeft = measuredLeft;

				if (rowsLen >= rows.size()) {
					rows.push_back(std::vector<Element*>());
				}
				if (rowLen >= rows[rowsLen - 1].size()) {
					rows[rowsLen - 1].push_back(child);
				} else {
					rows[rowsLen - 1][rowLen] = child;
				}

				rowLen++;
				runningWidth += measuredSandboxWidth;
				runningWidth > computedSize.width&&(computedSize.width = runningWidth);
			}

			// Calculate vertical size and position for the children
			len = rows.size();
			for (i = 0; i < len; i++) {
				auto row = rows[i];
				rowLen = row.size();

				rowHeight = 0;
				for (j = 0; j < row.size(); j++) {
					auto child = row[j];
					layoutCoefficients = (*child).layoutCoefficients;
					topLayoutCoefficients = layoutCoefficients.top;
					heightLayoutCoefficients = layoutCoefficients.height;
					sandboxHeightLayoutCoefficients = layoutCoefficients.sandboxHeight;
					measuredHeight = (*child).measuredHeight;
					if (isNaN(measuredHeight)) {
						(*child).measuredHeight = measuredHeight = heightLayoutCoefficients.x1 *
						                                               height +
						                                           heightLayoutCoefficients.x2 * (height - runningHeight) + heightLayoutCoefficients.x3;
					}

					if (!(*child).childrenLaidOut) {
						measuredWidth = (*child).measuredWidth;
						(*child).childrenLaidOut = true;
						layoutNode(
						    child,
						    isNaN(measuredWidth) ? width : measuredWidth - (*child).borderLeftWidth - (*child).borderRightWidth,
						    isNaN(measuredHeight) ? height : measuredHeight - (*child).borderTopWidth - (*child).borderBottomWidth,
						    isNaN(measuredWidth),
						    isNaN(measuredHeight));
					}

					if (topLayoutCoefficients.x2 != 0) {
						deferredTopCalculations.push_back(child);
						measuredTop = runningHeight;  // Temporary for use in calculating row height
					} else {
						(*child).measuredTop = measuredTop = topLayoutCoefficients.x1 * height +
						                                     topLayoutCoefficients.x3 * measuredHeight + topLayoutCoefficients.x4 + runningHeight;
					}

					(*child).measuredSandboxHeight = measuredSandboxHeight = sandboxHeightLayoutCoefficients.x1 * height + sandboxHeightLayoutCoefficients.x2 + measuredHeight + measuredTop - runningHeight;
					rowHeight < measuredSandboxHeight&&(rowHeight = measuredSandboxHeight);
				}
				rowHeights.push_back(rowHeight);
				runningHeight += rowHeight;
			}

			// Second pass, if necessary, to determine the top values
			runningHeight = 0;
			len = rowsLen;
			for (i = 0; i < len; i++) {
				auto row = rows[i];
				rowLen = row.size();
				rowHeight = rowHeights[i];
				for (j = 0; j < rowLen; j++) {
					child = row[j];
					(*child).measuredRunningHeight = runningHeight;
					(*child).measuredRowHeight = rowHeight;

					if (std::find(deferredTopCalculations.begin(), deferredTopCalculations.end(), child) != deferredTopCalculations.end()) {
						measuredHeight = (*child).measuredHeight;
						topLayoutCoefficients = (*child).layoutCoefficients.top;
						(*child).measuredTop = topLayoutCoefficients.x1 * height + topLayoutCoefficients.x2 * rowHeight + topLayoutCoefficients.x3 * measuredHeight + topLayoutCoefficients.x4 + runningHeight;
					}
				}
				runningHeight += rowHeight;
			}

			computedSize.height = runningHeight;

			return computedSize;
		}

		static void setDefaultHorizontalWidthType(struct LayoutProperties layoutProperties, enum ValueType* measuredWidthType)
		{
			if (*measuredWidthType == None) {
				*measuredWidthType = layoutProperties.defaultWidthType;
			}
		}

		static void setDefaultHorizontalHeightType(struct LayoutProperties layoutProperties, enum ValueType* measuredHeightType)
		{
			if (*measuredHeightType == None) {
				*measuredHeightType = layoutProperties.defaultHeightType;
			}
		}

		void measureNodeForHorizontalLayout(struct LayoutProperties layoutProperties, struct Element* element)
		{
			enum ValueType widthType = layoutProperties.width.valueType;
			double widthValue = layoutProperties.width.value;
			enum ValueType heightType = layoutProperties.height.valueType;
			double heightValue = layoutProperties.height.value;
			enum ValueType leftType = layoutProperties.left.valueType;
			double leftValue = layoutProperties.left.value;
			enum ValueType topType = layoutProperties.top.valueType;
			double topValue = layoutProperties.top.value;
			enum ValueType centerXType = layoutProperties.centerX.valueType;
			double centerXValue = layoutProperties.centerX.value;
			enum ValueType centerYType = layoutProperties.centerY.valueType;
			double centerYValue = layoutProperties.centerY.value;
			enum ValueType rightType = layoutProperties.right.valueType;
			double rightValue = layoutProperties.right.value;
			enum ValueType bottomType = layoutProperties.bottom.valueType;
			double bottomValue = layoutProperties.bottom.value;
			enum ValueType minWidthType = layoutProperties.minWidth.valueType;
			double minWidthValue = layoutProperties.minWidth.value;
			enum ValueType minHeightType = layoutProperties.minHeight.valueType;
			double minHeightValue = layoutProperties.minHeight.value;

			setDefaultHorizontalWidthType(layoutProperties, &widthType);
			setDefaultHorizontalHeightType(layoutProperties, &heightType);

			double x1 = 0;
			double x2 = 0;
			double x3 = 0;
			double x4 = 0;

			// Width rule calculation
			if (widthType == Size) {
				if (leftType != None && rightType != None) {
					x2 = 1;
					leftType == Percent && (x1 -= leftValue);
					leftType == Fixed && (x3 -= leftValue);
					rightType == Percent && (x1 -= rightValue);
					rightType == Fixed && (x3 -= rightValue);
				} else {
					x1 = x2 = x3 = NAN;
				}
			} else if (widthType == Fill) {
				x2 = 1;
				leftType == Percent&&(x1 -= leftValue);
				leftType == Fixed&&(x3 -= leftValue);
				rightType == Percent&&(x1 -= rightValue);
				rightType == Fixed&&(x3 -= rightValue);
			} else if (widthType == Percent) {
				x1 = widthValue;
			} else if (widthType == Fixed) {
				x3 = widthValue;
			}
			(*element).layoutCoefficients.width.x1 = x1;
			(*element).layoutCoefficients.width.x2 = x2;
			(*element).layoutCoefficients.width.x3 = x3;

			// Sandbox width rule calculation
			x1 = x2 = 0;
			leftType == Percent&&(x1 = leftValue);
			leftType == Fixed&&(x2 = leftValue);
			rightType == Percent&&(x1 += rightValue);
			rightType == Fixed&&(x2 += rightValue);
			(*element).layoutCoefficients.sandboxWidth.x1 = x1;
			(*element).layoutCoefficients.sandboxWidth.x2 = x2;

			// Height rule calculation
			x1 = x2 = x3 = 0;
			if (heightType == Size) {
				x1 = x2 = x3 = NAN;
			} else if (heightType == Fill) {
				x2 = 1;
				topType == Percent&&(x1 = -topValue);
				topType == Fixed&&(x3 = -topValue);
			} else if (heightType == Percent) {
				x1 = heightValue;
			} else if (heightType == Fixed) {
				x3 = heightValue;
			}
			(*element).layoutCoefficients.height.x1 = x1;
			(*element).layoutCoefficients.height.x2 = x2;
			(*element).layoutCoefficients.height.x3 = x3;

			// Sandbox height rule calculation
			(*element).layoutCoefficients.sandboxHeight.x1 = bottomType == Percent ? bottomValue : 0;
			(*element).layoutCoefficients.sandboxHeight.x2 = bottomType == Fixed ? bottomValue : 0;

			// Left rule calculation
			(*element).layoutCoefficients.left.x1 = leftType == Percent ? leftValue : 0;
			(*element).layoutCoefficients.left.x2 = leftType == Fixed ? leftValue : 0;

			// Top rule calculation
			x1 = x2 = x3 = x4 = 0;
			if (topType == Percent) {
				x1 = topValue;
			} else if (topType == Fixed) {
				x4 = topValue;
			} else if (bottomType == Percent) {
				x1 = 1 - bottomValue;
				x3 = -1;
			} else if (bottomType == Fixed) {
				x1 = 1;
				x3 = -1;
				x4 = -bottomValue;
			} else {
				switch ((*element).defaultRowAlignment) {
					case Center:
						x2 = 0.5;
						x3 = -0.5;
						break;
					case End:
						x2 = 1;
						x3 = -1;
						break;
				}
			}
			(*element).layoutCoefficients.top.x1 = x1;
			(*element).layoutCoefficients.top.x2 = x2;
			(*element).layoutCoefficients.top.x3 = x3;
			(*element).layoutCoefficients.top.x4 = x4;
		}
	} // namespace LayoutEngine
} // namespace Titanium
