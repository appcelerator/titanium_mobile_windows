# Titanium for Windows
#
# Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

include(CMakeFindDependencyMacro)
find_dependency(TitaniumWindows_Filesystem REQUIRED)
find_dependency(TitaniumWindows_Global REQUIRED)
find_dependency(LayoutEngine REQUIRED)
find_dependency(TitaniumWindows_Map REQUIRED)
find_dependency(TitaniumWindows_Media REQUIRED)
find_dependency(TitaniumWindows_Network REQUIRED)
find_dependency(TitaniumWindows_Sensors REQUIRED)
find_dependency(TitaniumWindows_Ti REQUIRED)
find_dependency(TitaniumKit REQUIRED)
find_dependency(TitaniumWindows_UI REQUIRED)
find_dependency(TitaniumWindows_Utility REQUIRED)

include("${CMAKE_BINARY_DIR}/TitaniumWindows_Targets.cmake")
