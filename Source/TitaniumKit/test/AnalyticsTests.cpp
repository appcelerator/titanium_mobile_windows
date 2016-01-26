/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "Titanium/Analytics.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE
#define XCTAssertNoThrow ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class AnalyticsTests : public testing::Test
{
protected:
	virtual void SetUp()
	{
	}

	virtual void TearDown()
	{
	}

	JSContextGroup js_context_group;
};

TEST_F(AnalyticsTests, BasicFeatures)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto Analytics = js_context.CreateObject(JSExport<Titanium::Analytics>::Class());

	XCTAssertTrue(Analytics.HasProperty("featureEvent"));
	XCTAssertTrue(Analytics.HasProperty("getLastEvent"));
	XCTAssertTrue(Analytics.HasProperty("navEvent"));
}
