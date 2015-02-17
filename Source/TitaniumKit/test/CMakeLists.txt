# TitaniumKit
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

# if(WIN32)
#   get_target_property(HAL_DLL_LOCATION HAL LOCATION)
#   file(COPY ${HAL_DLL_LOCATION} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# endif()

cxx_test(GlobalObjectTests . TitaniumKit_examples)
cxx_test(APITests          . TitaniumKit_examples)
cxx_test(ModuleTests       . TitaniumKit_examples)
cxx_test(UITests           . TitaniumKit_examples)
cxx_test(NativeViewTests   . TitaniumKit_examples)
cxx_test(NativeWindowTests . TitaniumKit_examples)
cxx_test(NativeButtonTests . TitaniumKit_examples)
cxx_test(NativePlatformTests . TitaniumKit_examples)
cxx_test(NativeAccelerometerTests . TitaniumKit_examples)
cxx_test(NativeGestureTests . TitaniumKit_examples)
cxx_test(NativeBlobTests . TitaniumKit_examples)
cxx_test(NativeFileTests . TitaniumKit_examples)
cxx_test(NativeTiTests   . TitaniumKit_examples)
cxx_test(NativeListViewTests   . TitaniumKit_examples)
cxx_test(NativeWebViewTests   . TitaniumKit_examples)
