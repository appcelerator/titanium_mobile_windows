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

TEST(ParserProperties, layout_initialization)
{
	struct Titanium::LayoutEngine::LayoutProperties layoutProperties;
	Titanium::LayoutEngine::layoutPropertiesInitialize(&layoutProperties);

	EXPECT_EQ((int)Titanium::LayoutEngine::None, (int)layoutProperties.top.valueType);
}

TEST(ParserProperties, populate_layout)
{
	struct Titanium::LayoutEngine::LayoutProperties layoutProperties;
	struct Titanium::LayoutEngine::InputProperty inputProperty;
	inputProperty.name = Titanium::LayoutEngine::Top;
	inputProperty.value = "99px";
	// 96 is the ppi
	Titanium::LayoutEngine::populateLayoutPoperties(inputProperty, &layoutProperties, 96);
	EXPECT_EQ(layoutProperties.top.value, (float)99.0);
}
