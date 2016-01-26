/**
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/GlobalObject.hpp"
#include "Titanium/FilesystemModule.hpp"
#include "NativeFileExample.hpp"
#include "NativeFilesystemExample.hpp"
#include "gtest/gtest.h"

#define XCTAssertEqual ASSERT_EQ
#define XCTAssertNotEqual ASSERT_NE
#define XCTAssertTrue ASSERT_TRUE
#define XCTAssertFalse ASSERT_FALSE
#define XCTAssertNoThrow ASSERT_NO_THROW

using namespace Titanium;
using namespace HAL;

class FileTests : public testing::Test
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

TEST_F(FileTests, logging)
{
	JSContext js_context = js_context_group.CreateContext(JSExport<Titanium::GlobalObject>::Class());
	auto global_object = js_context.get_global_object();

	auto Filesystem = js_context.CreateObject(JSExport<Titanium::FilesystemModule>::Class());
	auto File = js_context.CreateObject(JSExport<NativeFileExample>::Class());

	Filesystem.SetProperty("File", File);
	global_object.SetProperty("Filesystem", Filesystem);

	XCTAssertTrue(Filesystem.HasProperty("createTempDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("createTempFile"));
	XCTAssertTrue(Filesystem.HasProperty("getFile"));
	XCTAssertTrue(Filesystem.HasProperty("isExternalStoragePresent"));
	XCTAssertTrue(Filesystem.HasProperty("openStream"));

	XCTAssertTrue(Filesystem.HasProperty("separator"));
	XCTAssertTrue(Filesystem.HasProperty("applicationCacheDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("applicationDataDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("applicationDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("applicationSupportDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("externalStorageDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("lineEnding"));
	XCTAssertTrue(Filesystem.HasProperty("resourcesDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("tempDirectory"));

	XCTAssertTrue(Filesystem.HasProperty("getSeparator"));
	XCTAssertTrue(Filesystem.HasProperty("getApplicationCacheDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("getApplicationDataDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("getApplicationDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("getApplicationSupportDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("getExternalStorageDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("getLineEnding"));
	XCTAssertTrue(Filesystem.HasProperty("getResourcesDirectory"));
	XCTAssertTrue(Filesystem.HasProperty("getTempDirectory"));

	auto json_result = js_context.JSEvaluateScript("JSON.stringify(Filesystem);");
	XCTAssertTrue(static_cast<std::string>(json_result).find("\"separator\":") != std::string::npos);

	auto File_ptr = File.GetPrivate<NativeFileExample>();
	XCTAssertNotEqual(nullptr, File_ptr);

	JSValue result = js_context.CreateNull();
	XCTAssertNoThrow(result = File.CallAsConstructor(js_context.CreateNull()));
	XCTAssertTrue(result.IsObject());

	JSObject file = static_cast<JSObject>(result);

	XCTAssertTrue(file.HasProperty("executable"));
	XCTAssertTrue(file.HasProperty("hidden"));
	XCTAssertTrue(file.HasProperty("name"));
	XCTAssertTrue(file.HasProperty("nativePath"));
	XCTAssertTrue(file.HasProperty("parent"));
	XCTAssertTrue(file.HasProperty("readonly"));
	XCTAssertTrue(file.HasProperty("remoteBackup"));
	XCTAssertTrue(file.HasProperty("size"));
	XCTAssertTrue(file.HasProperty("symbolicLink"));
	XCTAssertTrue(file.HasProperty("writable"));
	XCTAssertTrue(file.HasProperty("getExecutable"));
	XCTAssertTrue(file.HasProperty("getHidden"));
	XCTAssertTrue(file.HasProperty("getName"));
	XCTAssertTrue(file.HasProperty("getNativePath"));
	XCTAssertTrue(file.HasProperty("getParent"));
	XCTAssertTrue(file.HasProperty("getReadonly"));
	XCTAssertTrue(file.HasProperty("getRemoteBackup"));
	XCTAssertTrue(file.HasProperty("getSize"));
	XCTAssertTrue(file.HasProperty("getSymbolicLink"));
	XCTAssertTrue(file.HasProperty("getWritable"));
	XCTAssertTrue(file.HasProperty("append"));
	XCTAssertTrue(file.HasProperty("copy"));
	XCTAssertTrue(file.HasProperty("createDirectory"));
	XCTAssertTrue(file.HasProperty("createFile"));
	XCTAssertTrue(file.HasProperty("createTimestamp"));
	XCTAssertTrue(file.HasProperty("deleteDirectory"));
	XCTAssertTrue(file.HasProperty("deleteFile"));
	XCTAssertTrue(file.HasProperty("exists"));
	XCTAssertTrue(file.HasProperty("extension"));
	XCTAssertTrue(file.HasProperty("getDirectoryListing"));
	XCTAssertTrue(file.HasProperty("isDirectory"));
	XCTAssertTrue(file.HasProperty("isFile"));
	XCTAssertTrue(file.HasProperty("modificationTimestamp"));
	XCTAssertTrue(file.HasProperty("move"));
	XCTAssertTrue(file.HasProperty("open"));
	XCTAssertTrue(file.HasProperty("read"));
	XCTAssertTrue(file.HasProperty("rename"));
	XCTAssertTrue(file.HasProperty("resolve"));
	XCTAssertTrue(file.HasProperty("spaceAvailable"));
	XCTAssertTrue(file.HasProperty("write"));

	global_object.SetProperty("file", file);
	json_result = js_context.JSEvaluateScript("JSON.stringify(file);");
	XCTAssertTrue(static_cast<std::string>(json_result).find("\"symbolicLink\":") != std::string::npos);
}
