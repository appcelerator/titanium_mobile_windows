/**
 * LayoutEngine
 * Author: Russell W. McMahon
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "LayoutEngine/LayoutEngine.hpp"

#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

namespace Titanium
{
	namespace LayoutEngine
	{
		void elementInitialize(struct Element* element, enum LayoutType layoutType)
		{
			(*element).layoutCoefficients.width.x1 = NAN;
			(*element).layoutCoefficients.width.x2 = NAN;
			(*element).layoutCoefficients.width.x3 = NAN;
			(*element).layoutCoefficients.minWidth.x1 = NAN;
			(*element).layoutCoefficients.minWidth.x2 = NAN;
			(*element).layoutCoefficients.minWidth.x3 = NAN;
			(*element).layoutCoefficients.sandboxWidth.x1 = NAN;
			(*element).layoutCoefficients.sandboxWidth.x2 = NAN;
			(*element).layoutCoefficients.sandboxWidth.x3 = NAN;
			(*element).layoutCoefficients.height.x1 = NAN;
			(*element).layoutCoefficients.height.x2 = NAN;
			(*element).layoutCoefficients.height.x3 = NAN;
			(*element).layoutCoefficients.minHeight.x1 = NAN;
			(*element).layoutCoefficients.minHeight.x2 = NAN;
			(*element).layoutCoefficients.minHeight.x3 = NAN;
			(*element).layoutCoefficients.sandboxHeight.x1 = NAN;
			(*element).layoutCoefficients.sandboxHeight.x2 = NAN;
			(*element).layoutCoefficients.sandboxHeight.x3 = NAN;
			(*element).layoutCoefficients.left.x1 = NAN;
			(*element).layoutCoefficients.left.x2 = NAN;
			(*element).layoutCoefficients.left.x3 = NAN;
			(*element).layoutCoefficients.top.x1 = NAN;
			(*element).layoutCoefficients.top.x2 = NAN;
			(*element).layoutCoefficients.top.x3 = NAN;
			(*element).layoutCoefficients.top.x4 = NAN;
			(*element).layoutType = layoutType;
			(*element).defaultRowAlignment = Center;
			(*element).defaultHorizontalAlignment = Center;
			(*element).defaultVerticalAlignment = Center;
		}

		void addChildElement(Element* parent, Element* child)
		{
			const auto it = std::find(parent->children.begin(), parent->children.end(), child);
			if (it == parent->children.end()) {
				parent->children.push_back(child);
			}
		}

		void removeChildElement(struct Element* parent, struct Element* child)
		{
			const auto it = std::find(parent->children.begin(), parent->children.end(), child);
			if (it != parent->children.end()) {
				parent->children.erase(it);
			}
		}

		void insertChildElementAt(Element* parent, Element* child, unsigned int index) 
		{
			const auto it = std::find(parent->children.begin(), parent->children.end(), child);
			if (it == parent->children.end()) {
				parent->children.insert(parent->children.begin() + index, child);
			}
		}
	} // namespace LayoutEngine
} // namespace Titanium
