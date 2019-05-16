# Titanium for Windows
#
# Copyright (c) 2019 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.
cmake_minimum_required(VERSION 3.5)
project(Windows VERSION 0.5.0 LANGUAGES CXX)

# Make sure that custom modules are found
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

# Define helper functions and macros.
include(internal_utils)

# Defined in internal_utils.cmake.
config_compiler_and_linker()

# Allow "make test" to work.
enable_testing() # needed on top-level CMakeLists.txt

##############################################
# Create target and set properties

if(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsPhone")
  set(PLATFORM wp)
  add_definitions("-DPHONE")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore")
  set(PLATFORM store)
else()
  message(FATAL_ERROR "This app supports Store / Phone only.")
endif()

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Use c++11+ globally
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_subdirectory(Filesystem)
add_subdirectory(Global)
add_subdirectory(HAL)
add_subdirectory(LayoutEngine)
add_subdirectory(Map)
add_subdirectory(Media)
add_subdirectory(Network)
add_subdirectory(Sensors)
add_subdirectory(Ti)
add_subdirectory(Titanium)
add_subdirectory(TitaniumKit)
add_subdirectory(UI)
add_subdirectory(Utility)