# Titanium for Windows
#
# Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

include(CMakeFindDependencyMacro)
find_dependency(TitaniumWindows_Filesystem)
find_dependency(TitaniumWindows_Global)
find_dependency(HAL)
find_dependency(LayoutEngine)
find_dependency(TitaniumWindows_Media)
find_dependency(TitaniumWindows_Network)
find_dependency(TitaniumWindows_Sensors)
find_dependency(TitaniumWindows_Ti)
find_dependency(TitaniumKit)
find_dependency(TitaniumWindows_UI)
find_dependency(TitaniumWindows_Utility)

include("${CMAKE_BINARY_DIR}/TitaniumWindows_Targets.cmake")
