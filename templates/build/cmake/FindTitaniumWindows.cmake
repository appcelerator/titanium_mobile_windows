# FindTitaniumWindows
# Author: Chris Williams
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

# Author: Chris Williams
# Created: 2014.12.02

if(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsPhone")
  set(PLATFORM phone)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore")
  set(PLATFORM store)
else()
  message(FATAL_ERROR "This app supports Store / Phone only.")
endif()

set(TitaniumWindows_ARCH "x86")
if(CMAKE_GENERATOR MATCHES "^Visual Studio .+ ARM$")
  set(TitaniumWindows_ARCH "arm")
endif()

# Taken and slightly modified from build's TitaniumWindows_Targets.cmake file
# INTERFACE_INCLUDE_DIRECTORIES is modified to point to our pre-packaged include dir for module

# Create imported target TitaniumWindows
add_library(TitaniumWindows SHARED IMPORTED)

set_target_properties(TitaniumWindows PROPERTIES
  COMPATIBLE_INTERFACE_STRING "TitaniumWindows_MAJOR_VERSION"
  INTERFACE_INCLUDE_DIRECTORIES "${WINDOWS_SOURCE_DIR}/lib/TitaniumWindows/include;$<TARGET_PROPERTY:TitaniumWindows_Filesystem,INTERFACE_INCLUDE_DIRECTORIES>;$<TARGET_PROPERTY:TitaniumWindows_Global,INTERFACE_INCLUDE_DIRECTORIES>;$<TARGET_PROPERTY:HAL,INTERFACE_INCLUDE_DIRECTORIES>;$<TARGET_PROPERTY:LayoutEngine,INTERFACE_INCLUDE_DIRECTORIES>;$<TARGET_PROPERTY:TitaniumWindows_Media,INTERFACE_INCLUDE_DIRECTORIES>;$<TARGET_PROPERTY:TitaniumWindows_Network,INTERFACE_INCLUDE_DIRECTORIES>;$<TARGET_PROPERTY:TitaniumWindows_Sensors,INTERFACE_INCLUDE_DIRECTORIES>;$<TARGET_PROPERTY:TitaniumWindows_Ti,INTERFACE_INCLUDE_DIRECTORIES>;$<TARGET_PROPERTY:TitaniumKit,INTERFACE_INCLUDE_DIRECTORIES>;$<TARGET_PROPERTY:TitaniumWindows_UI,INTERFACE_INCLUDE_DIRECTORIES>;$<TARGET_PROPERTY:TitaniumWindows_Utility,INTERFACE_INCLUDE_DIRECTORIES>"
  INTERFACE_LINK_LIBRARIES "TitaniumWindows_Filesystem;TitaniumWindows_Global;HAL;LayoutEngine;TitaniumWindows_Media;TitaniumWindows_Network;TitaniumWindows_Sensors;TitaniumWindows_Ti;TitaniumKit;TitaniumWindows_UI;TitaniumWindows_Utility"
  INTERFACE_TitaniumWindows_MAJOR_VERSION "0"
)
set_target_properties(TitaniumWindows PROPERTIES
  IMPORTED_IMPLIB "${WINDOWS_SOURCE_DIR}/lib/TitaniumWindows/${PLATFORM}/${TitaniumWindows_ARCH}/TitaniumWindows.lib"
  IMPORTED_LOCATION "${WINDOWS_SOURCE_DIR}/lib/TitaniumWindows/${PLATFORM}/${TitaniumWindows_ARCH}/TitaniumWindows.dll"
)
