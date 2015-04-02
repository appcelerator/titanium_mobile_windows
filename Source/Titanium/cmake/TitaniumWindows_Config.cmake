# Titanium for Windows
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

include(CMakeFindDependencyMacro)
find_dependency(TitaniumWindows_Accelerometer)
find_dependency(TitaniumWindows_API)
find_dependency(TitaniumWindows_App)
find_dependency(TitaniumWindows_Filesystem)
find_dependency(TitaniumWindows_Geolocation)
find_dependency(TitaniumWindows_Gesture)
find_dependency(TitaniumWindows_Global)
find_dependency(LayoutEngine)
find_dependency(TitaniumWindows_Map)
find_dependency(TitaniumWindows_Network)
find_dependency(TitaniumWindows_Platform)
find_dependency(TitaniumWindows_Ti)
find_dependency(TitaniumWindows_UI)
find_dependency(TitaniumWindows_Utility)
find_dependency(TitaniumWindows_Utils)

include("${CMAKE_BINARY_DIR}/TitaniumWindows_Targets.cmake")
