# FindTitaniumWindows_Geolocation
#
# Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

set(TitaniumWindows_Geolocation_ARCH "x86")
if(CMAKE_GENERATOR MATCHES "^Visual Studio .+ ARM$")
  set(TitaniumWindows_Geolocation_ARCH "arm")
endif()

# Taken and slightly modified from build's TitaniumWindows_Geolocation_Targets.cmake file
# INTERFACE_INCLUDE_DIRECTORIES is modified to point to our pre-packaged include dir for module

# Create imported target TitaniumWindows_Geolocation
add_library(TitaniumWindows_Geolocation SHARED IMPORTED)

set_target_properties(TitaniumWindows_Geolocation PROPERTIES
  COMPATIBLE_INTERFACE_STRING "TitaniumWindows_Geolocation_MAJOR_VERSION"
  INTERFACE_INCLUDE_DIRECTORIES "${WINDOWS_SOURCE_DIR}/lib/TitaniumWindows_Geolocation/include;$<TARGET_PROPERTY:TitaniumKit,INTERFACE_INCLUDE_DIRECTORIES>;$<TARGET_PROPERTY:TitaniumWindows_Utility,INTERFACE_INCLUDE_DIRECTORIES>"
  INTERFACE_LINK_LIBRARIES "TitaniumKit;TitaniumWindows_Utility"
  INTERFACE_TitaniumWindows_Geolocation_MAJOR_VERSION "0"
)

set_target_properties(TitaniumWindows_Geolocation PROPERTIES
  IMPORTED_IMPLIB "${WINDOWS_SOURCE_DIR}/lib/TitaniumWindows_Geolocation/${TitaniumWindows_Geolocation_ARCH}/TitaniumWindows_Geolocation.lib"
  IMPORTED_LOCATION "${WINDOWS_SOURCE_DIR}/lib/TitaniumWindows_Geolocation/${TitaniumWindows_Geolocation_ARCH}/TitaniumWindows_Geolocation.dll"
  )
