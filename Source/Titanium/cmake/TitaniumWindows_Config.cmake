# Titanium for Windows
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

include(CMakeFindDependencyMacro)
find_dependency(TitaniumWindows_Global)
find_dependency(TitaniumWindows_API)
find_dependency(TitaniumWindows_UI)

include("${CMAKE_BINARY_DIR}/TitaniumWindows_Targets.cmake")
