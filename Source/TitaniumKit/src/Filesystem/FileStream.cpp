/**
 * Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#include "Titanium/Filesystem/FileStream.hpp"

namespace Titanium
{
	namespace Filesystem
	{
		FileStream::FileStream(const JSContext& js_context) TITANIUM_NOEXCEPT
		    : Module(js_context)
		{
		}

		void FileStream::JSExportInitialize()
		{
			JSExport<FileStream>::SetClassVersion(1);
			JSExport<FileStream>::SetParent(JSExport<Module>::Class());
		}

	} // namespace Filesystem
}  // namespace Titanium
