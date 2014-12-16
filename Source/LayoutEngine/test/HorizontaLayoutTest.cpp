/**
 * LayoutEngine
 * Author: Russell W. McMahon
 *
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "LayoutEngine/LayoutEngine.hpp"

#include "gtest/gtest.h"

TEST(HorizontalLayout, measure_horizontal_node) {
  struct Titanium::LayoutEngine::LayoutProperties layoutProperties;
  Titanium::LayoutEngine::layoutPropertiesInitialize(&layoutProperties);
  struct Titanium::LayoutEngine::Element* element = new Titanium::LayoutEngine::Element();
  Titanium::LayoutEngine::elementInitialize(element, Titanium::LayoutEngine::Horizontal);
  layoutProperties.width.value = 50;
  layoutProperties.width.valueType = Titanium::LayoutEngine::Fixed;
  layoutProperties.height.value = 20;
  layoutProperties.height.valueType = Titanium::LayoutEngine::Fixed;
  measureNodeForHorizontalLayout(layoutProperties, element);

  // top left rule
  EXPECT_EQ(0.0, (*element).layoutCoefficients.top.x1);
  EXPECT_EQ(0.5, (*element).layoutCoefficients.top.x2);
  EXPECT_EQ(-0.5, (*element).layoutCoefficients.top.x3);
  EXPECT_EQ(0.0, (*element).layoutCoefficients.top.x4);
}

TEST(HorizontalLayout, horizontal_layout) {
  struct  Titanium::LayoutEngine::LayoutProperties layoutProperties;
  Titanium::LayoutEngine::layoutPropertiesInitialize(&layoutProperties);
  struct  Titanium::LayoutEngine::Element* e1 = new  Titanium::LayoutEngine::Element();
  Titanium::LayoutEngine::elementInitialize(e1, Titanium::LayoutEngine::Horizontal); // Device - top level window
  // e2
  layoutProperties.width.value = 50;
  layoutProperties.width.valueType = Titanium::LayoutEngine::Fixed;
  layoutProperties.height.value = 20;
  layoutProperties.height.valueType = Titanium::LayoutEngine::Fixed;
  struct Titanium::LayoutEngine::Element* e2 = new Titanium::LayoutEngine::Element();
  Titanium::LayoutEngine::elementInitialize(e2, Titanium::LayoutEngine::Composite);
  Titanium::LayoutEngine::measureNodeForHorizontalLayout(layoutProperties, e2);
  // e3
  layoutProperties.width.value = 50;
  layoutProperties.width.valueType = Titanium::LayoutEngine::Fixed; 
  layoutProperties.height.value = 40;
  layoutProperties.height.valueType = Titanium::LayoutEngine::Fixed;
  struct Titanium::LayoutEngine::Element* e3 = new Titanium::LayoutEngine::Element();
  Titanium::LayoutEngine::elementInitialize(e3, Titanium::LayoutEngine::Composite);
  Titanium::LayoutEngine::measureNodeForHorizontalLayout(layoutProperties, e3);
  Titanium::LayoutEngine::addChildElement(e1, e2);
  Titanium::LayoutEngine::addChildElement(e1, e3);
  Titanium::LayoutEngine::doHorizontalLayout((*e1).children, 100, 100, false, false);

  ASSERT_DOUBLE_EQ(10.0, (*e2).measuredTop);
  ASSERT_DOUBLE_EQ(0.0, (*e2).measuredLeft);
  ASSERT_DOUBLE_EQ(50.0, (*e2).measuredWidth);
  ASSERT_DOUBLE_EQ(20.0, (*e2).measuredHeight);
  ASSERT_DOUBLE_EQ(0.0, (*e3).measuredTop);
  ASSERT_DOUBLE_EQ(50.0, (*e3).measuredLeft);
  ASSERT_DOUBLE_EQ(50.0, (*e3).measuredWidth);
  ASSERT_DOUBLE_EQ(40.0, (*e3).measuredHeight);
}
