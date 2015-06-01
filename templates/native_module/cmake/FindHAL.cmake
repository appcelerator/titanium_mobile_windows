# FindHAL
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

set(HAL_ARCH "x86")
if(CMAKE_GENERATOR MATCHES "^Visual Studio .+ ARM$")
  set(HAL_ARCH "arm")
endif()

# Taken and slightly modified from build's HAL_Targets.cmake file
# INTERFACE_INCLUDE_DIRECTORIES is modified to point to our pre-packaged include dir for module

# Create imported target HAL
add_library(HAL SHARED IMPORTED)

set_target_properties(HAL PROPERTIES
  COMPATIBLE_INTERFACE_STRING "HAL_MAJOR_VERSION"
  INTERFACE_INCLUDE_DIRECTORIES "${WINDOWS_SOURCE_DIR}/lib/HAL/include"
  INTERFACE_HAL_MAJOR_VERSION "0"
)

set_target_properties(HAL PROPERTIES
  IMPORTED_IMPLIB "${WINDOWS_SOURCE_DIR}/lib/HAL/${PLATFORM}/${HAL_ARCH}/HAL.lib"
  IMPORTED_LOCATION "${WINDOWS_SOURCE_DIR}/lib/HAL/${PLATFORM}/${HAL_ARCH}/HAL.dll"
  )
