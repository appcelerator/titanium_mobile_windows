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


TEST(CompositeLayout, measure_composite_node_fill_properties) {
  struct Titanium::LayoutEngine::LayoutProperties layoutProperties;
  Titanium::LayoutEngine::layoutPropertiesInitialize(&layoutProperties);
  struct Titanium::LayoutEngine::Element* element = new Titanium::LayoutEngine::Element();
  Titanium::LayoutEngine::elementInitialize(element, Titanium::LayoutEngine::Composite);
  layoutProperties.width.valueType = Titanium::LayoutEngine::Fill;
  layoutProperties.width.value = NAN;
  layoutProperties.height.valueType = Titanium::LayoutEngine::Fill;
  layoutProperties.height.value = NAN;
  measureNodeForCompositeLayout(layoutProperties, element);
  // width height rule
  EXPECT_EQ(1.0, (*element).layoutCoefficients.width.x1);
  EXPECT_EQ(0.0, (*element).layoutCoefficients.width.x2);
  EXPECT_EQ(1.0, (*element).layoutCoefficients.height.x1);
  EXPECT_EQ(0.0, (*element).layoutCoefficients.height.x2);
  // min-width min-height rule
  EXPECT_EQ(true, Titanium::LayoutEngine::isNaN((*element).layoutCoefficients.minWidth.x1));
  EXPECT_EQ(true, Titanium::LayoutEngine::isNaN((*element).layoutCoefficients.minWidth.x2));
  EXPECT_EQ(true, Titanium::LayoutEngine::isNaN((*element).layoutCoefficients.minWidth.x3));
  EXPECT_EQ(true, Titanium::LayoutEngine::isNaN((*element).layoutCoefficients.minHeight.x1));
  EXPECT_EQ(true, Titanium::LayoutEngine::isNaN((*element).layoutCoefficients.minHeight.x2));
  EXPECT_EQ(true, Titanium::LayoutEngine::isNaN((*element).layoutCoefficients.minHeight.x3));
  // top left rule
  EXPECT_EQ(0.5, (*element).layoutCoefficients.top.x1);
  EXPECT_EQ(-0.5, (*element).layoutCoefficients.top.x2);
  EXPECT_EQ(0.5, (*element).layoutCoefficients.left.x1);
  EXPECT_EQ(-0.5, (*element).layoutCoefficients.left.x2);
}

TEST(CompositeLayout, measure_composite_node) {
  struct Titanium::LayoutEngine::LayoutProperties layoutProperties;
  layoutPropertiesInitialize(&layoutProperties);
  struct Titanium::LayoutEngine::Element* element = new Titanium::LayoutEngine::Element();
  Titanium::LayoutEngine::elementInitialize(element, Titanium::LayoutEngine::Composite);
  layoutProperties.width.valueType = Titanium::LayoutEngine::ValueType::Fixed; 
  layoutProperties.width.value = 100;
  layoutProperties.height.valueType = Titanium::LayoutEngine::ValueType::Fixed; 
  layoutProperties.height.value = 100;
  Titanium::LayoutEngine::measureNodeForCompositeLayout(layoutProperties, element);
  // width height rule
  EXPECT_EQ(0.0, (*element).layoutCoefficients.width.x1);
  EXPECT_EQ(100.0, (*element).layoutCoefficients.width.x2);
  EXPECT_EQ(0.0, (*element).layoutCoefficients.height.x1);
  EXPECT_EQ(100.0, (*element).layoutCoefficients.height.x2);
  // min-width min-height rule
  EXPECT_EQ(true, Titanium::LayoutEngine::isNaN((*element).layoutCoefficients.minWidth.x1));
  EXPECT_EQ(true, Titanium::LayoutEngine::isNaN((*element).layoutCoefficients.minWidth.x2));
  EXPECT_EQ(true, Titanium::LayoutEngine::isNaN((*element).layoutCoefficients.minWidth.x3));
  EXPECT_EQ(true, Titanium::LayoutEngine::isNaN((*element).layoutCoefficients.minHeight.x1));
  EXPECT_EQ(true, Titanium::LayoutEngine::isNaN((*element).layoutCoefficients.minHeight.x2));
  EXPECT_EQ(true, Titanium::LayoutEngine::isNaN((*element).layoutCoefficients.minHeight.x3));
  // top left rule
  EXPECT_EQ(0.5, (*element).layoutCoefficients.top.x1);
  EXPECT_EQ(-0.5, (*element).layoutCoefficients.top.x2);
  EXPECT_EQ(0.5, (*element).layoutCoefficients.left.x1);
  EXPECT_EQ(-0.5, (*element).layoutCoefficients.left.x2);
}
