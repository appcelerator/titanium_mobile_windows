# FindTitaniumKit
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

set(TitaniumKit_ARCH "x86")
if(CMAKE_GENERATOR MATCHES "^Visual Studio .+ ARM$")
  set(TitaniumKit_ARCH "arm")
endif()

# Taken and slightly modified from build's TitaniumKit_Targets.cmake file
# INTERFACE_INCLUDE_DIRECTORIES is modified to point to our pre-packaged include dir for module

# Create imported target TitaniumKit
add_library(TitaniumKit SHARED IMPORTED)

set_target_properties(TitaniumKit PROPERTIES
  COMPATIBLE_INTERFACE_STRING "TitaniumKit_MAJOR_VERSION"
  INTERFACE_INCLUDE_DIRECTORIES "${WINDOWS_SOURCE_DIR}/lib/TitaniumKit/include;$<TARGET_PROPERTY:HAL,INTERFACE_INCLUDE_DIRECTORIES>"
  INTERFACE_LINK_LIBRARIES "HAL"
  INTERFACE_TitaniumKit_MAJOR_VERSION "0"
)
set_target_properties(TitaniumKit PROPERTIES
  IMPORTED_IMPLIB "${WINDOWS_SOURCE_DIR}/lib/TitaniumKit/${PLATFORM}/${TitaniumKit_ARCH}/TitaniumKit.lib"
  IMPORTED_LOCATION "${WINDOWS_SOURCE_DIR}/lib/TitaniumKit/${PLATFORM}/${TitaniumKit_ARCH}/TitaniumKit.dll"
  )
