/**
 * LayoutEngine
 * Author: Russell W. McMahon
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "LayoutEngine/LayoutEngine.hpp"

namespace Titanium { namespace LayoutEngine {

bool isNaN(double value) {
  if (value != value)
    return true;
  else
    return false;
}

ComputedSize layoutNode(struct Element* element, double width, double height, bool isWidthSize, bool isHeightSize) {
  ComputedSize computedSize;

  switch ((*element).layoutType) {
    case Composite:
      computedSize = doCompositeLayout((*element).children, width, height, isWidthSize, isHeightSize);
      break;
    case Horizontal:
      computedSize = doHorizontalLayout((*element).children, width, height, isWidthSize, isHeightSize);
      break;
    case Vertical:
      computedSize = doVerticalLayout((*element).children, width, height, isWidthSize, isHeightSize);
      break;
  }

  return computedSize;
}

void measureNode(enum LayoutType type, struct LayoutProperties* properties, struct Element* element) {
  switch (type) {
    case Composite:
      measureNodeForCompositeLayout(*properties, element);
      break;
    case Horizontal:
      measureNodeForHorizontalLayout(*properties, element);
      break;
    case Vertical:
      measureNodeForVerticalLayout(*properties, element);
      break;
  }
}

}}  // namespace Titanium { namespace LayoutEngine {
