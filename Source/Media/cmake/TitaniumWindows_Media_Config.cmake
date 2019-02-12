# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

include(CMakeFindDependencyMacro)
find_dependency(TitaniumKit REQUIRED)
find_dependency(TitaniumWindows_Utility REQUIRED)
find_dependency(TitaniumWindows_UI REQUIRED)

include("${CMAKE_BINARY_DIR}/TitaniumWindows_Media_Targets.cmake")
