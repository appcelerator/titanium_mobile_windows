/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Titanium.hpp"
#include "NativeBlobExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE
#define XCTAssertNoThrow ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class BlobTests : public testing::Test
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

TEST_F(BlobTests, logging)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto global_object = js_context.get_global_object();

	XCTAssertFalse(global_object.HasProperty("Titanium"));
	auto Titanium = js_context.CreateObject();
	global_object.SetProperty("Titanium", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(global_object.HasProperty("Titanium"));

	// Make the alias "Ti" for the "Titanium" property.
	XCTAssertFalse(global_object.HasProperty("Ti"));
	global_object.SetProperty("Ti", Titanium, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(global_object.HasProperty("Ti"));

	XCTAssertFalse(Titanium.HasProperty("Blob"));
	auto Blob = js_context.CreateObject(JSExport<NativeBlobExample>::Class());
	Titanium.SetProperty("Blob", Blob, {JSPropertyAttribute::ReadOnly, JSPropertyAttribute::DontDelete});
	XCTAssertTrue(Titanium.HasProperty("Blob"));

	auto Blob_ptr = Blob.GetPrivate<NativeBlobExample>();
	XCTAssertNotEqual(nullptr, Blob_ptr);

	JSValue result = js_context.CreateNull();
	XCTAssertNoThrow(result = Blob.CallAsConstructor(js_context.CreateNull()));
	XCTAssertTrue(result.IsObject());

	JSObject blob = static_cast<JSObject>(result);
	XCTAssertTrue(blob.HasProperty("length"));
	// XCTAssertTrue(blob.HasProperty("file")); // This depends on Ti.Filesystme.File
	XCTAssertTrue(blob.HasProperty("height"));
	XCTAssertTrue(blob.HasProperty("mimeType"));
	XCTAssertTrue(blob.HasProperty("nativePath"));
	XCTAssertTrue(blob.HasProperty("size"));
	XCTAssertTrue(blob.HasProperty("text"));
	XCTAssertTrue(blob.HasProperty("width"));

	XCTAssertTrue(blob.HasProperty("getLength"));
	// XCTAssertTrue(blob.HasProperty("getFile")); // This depends on Ti.Filesystme.File
	XCTAssertTrue(blob.HasProperty("getHeight"));
	XCTAssertTrue(blob.HasProperty("getMimeType"));
	XCTAssertTrue(blob.HasProperty("getNativePath"));
	XCTAssertTrue(blob.HasProperty("getSize"));
	XCTAssertTrue(blob.HasProperty("getText"));
	XCTAssertTrue(blob.HasProperty("getWidth"));
	XCTAssertTrue(blob.HasProperty("append"));
	XCTAssertTrue(blob.HasProperty("toString"));
}
