/**
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef _TITANIUMWINDOWS_TITANIUMAPPLICATIONCALLBACK_HPP_
#define _TITANIUMWINDOWS_TITANIUMAPPLICATIONCALLBACK_HPP_

#include <cinttypes>

namespace TitaniumWindows
{
	// This should return pointer to JSObject (key-value) which consists of module name & preloaded JSObject
	public delegate std::intptr_t TitaniumModulePreloadHandler(std::intptr_t js_context_ref);

	// This should return collections of supported name module names such as Windows.Xaml.Controls.Button etc.
	public delegate Windows::Foundation::Collections::IVector<::Platform::String^>^ TitaniumModuleNamesHandler(std::intptr_t js_context_ref);

	// This will be called when native module with supported name is not loaded. Return pointer to JSValue as the result of require.
	public delegate std::intptr_t TitaniumModuleRequireHandler(std::intptr_t js_context_ref, ::Platform::String^ moduleId);

	public delegate std::intptr_t NativeUIElementUnwrapHandler(std::intptr_t js_context_ref, std::intptr_t js_object_ref);
}  // namespace TitaniumWindows

#endif  // _TITANIUMWINDOWS_TITANIUMAPPLICATIONCALLBACK_HPP_

