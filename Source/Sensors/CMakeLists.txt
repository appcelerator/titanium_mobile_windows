# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.
cmake_minimum_required(VERSION 3.0.0)

project(TitaniumWindows_Sensors VERSION 0.1.0 LANGUAGES CXX)

option(TitaniumWindows_Sensors_DISABLE_TESTS "Disable compiling the tests" OFF)

# necessary to provide <LIBRARY>_EXPORT.h downstream
set(CMAKE_INCLUDE_CURRENT_DIR ON)		
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(SOURCE_Sensors
  include/TitaniumWindows/Accelerometer.hpp
  include/TitaniumWindows/Gesture.hpp
  include/TitaniumWindows/Geolocation.hpp
  include/TitaniumWindows/ShakeGestureHelper.hpp
  src/Accelerometer.cpp
  src/Gesture.cpp
  src/Geolocation.cpp
  src/ShakeGestureHelper.cpp
  src/TitaniumEntryPoint.cpp
)

source_group(Titanium\\Sensors FILES ${SOURCE_Sensors})

# Turn on precompiled headers
include(precompiled_header)
enable_precompiled_headers(src/stdafx.h SOURCE_Sensors)

add_library(TitaniumWindows_Sensors SHARED
  ${SOURCE_Sensors}
)

include(GenerateExportHeader)
generate_export_header(TitaniumWindows_Sensors)
target_compile_definitions(TitaniumWindows_Sensors PRIVATE TitaniumWindows_Sensors_EXPORTS)

target_include_directories(TitaniumWindows_Sensors
  PUBLIC 
      $<INSTALL_INTERFACE:include>    
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
      src
)

target_link_libraries(TitaniumWindows_Sensors
  PUBLIC
    TitaniumKit
  PRIVATE
    TitaniumWindows_Utility
)

set_target_properties(TitaniumWindows_Sensors PROPERTIES VS_WINRT_COMPONENT TRUE)

# Silence this warning when lnking the Debug configuration:
#
# "LINK : warning LNK4075: ignoring '/INCREMENTAL' due to '/OPT:ICF'
# specification ..."
#
# According to "/IGNORE (Ignore Specific Warnings)" (see
# http://msdn.microsoft.com/en-us/library/dn782850.aspx) some linker
# warnings cannot be ignored and LNK4075 is one of them. However,
# according to "/INCREMENTAL (Link Incrementally)" (see
# http://msdn.microsoft.com/en-us/library/4khtbfyf.aspx):
#
# "Most programs can be linked incrementally. However, some changes
# are too great, and some options are incompatible with incremental
# linking. LINK performs a full link if any of the following options
# are specified:
# ...
# /OPT:REF is selected
# /OPT:ICF is selected
# ..."
#
# And according to "/OPT (Optimizations)" (see
# http://msdn.microsoft.com/en-us/library/bxwfs976.aspx):
#
# "If /DEBUG is specified, the default for /OPT is NOREF, and all
# functions are preserved in the image."
#
# As well as:
#
# "... we do not recommend that you use /OPT:ICF in debug builds ..."
#
# Therefore we disable /OPT:REF and /OPT:ICF for the Debug
# configuration.
set_property(TARGET TitaniumWindows_Sensors APPEND_STRING PROPERTY LINK_FLAGS_DEBUG "/OPT:NOREF /OPT:NOICF")

# Fix error C4996: 'std::_Copy_impl': Function call with parameters that may be unsafe (needed by boost::split)
set_property(TARGET TitaniumWindows_Sensors APPEND_STRING PROPERTY COMPILE_FLAGS " -D_SCL_SECURE_NO_WARNINGS")

if (NOT TitaniumWindows_Sensors_DISABLE_TESTS)
  add_subdirectory(test)
endif()


# Support find_package(TitaniumWindows_Sensors 0.1 REQUIRED)

set_property(TARGET TitaniumWindows_Sensors PROPERTY VERSION ${TitaniumWindows_Sensors_VERSION})
set_property(TARGET TitaniumWindows_Sensors PROPERTY SOVERSION 0)
set_property(TARGET TitaniumWindows_Sensors PROPERTY INTERFACE_TitaniumWindows_Sensors_MAJOR_VERSION 0)
set_property(TARGET TitaniumWindows_Sensors APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING TitaniumWindows_Sensors_MAJOR_VERSION
)

install(TARGETS TitaniumWindows_Sensors
  EXPORT TitaniumWindows_Sensors_Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

export(EXPORT TitaniumWindows_Sensors_Targets
  FILE "${CMAKE_BINARY_DIR}/TitaniumWindows_Sensors_Targets.cmake"
)

configure_file(cmake/TitaniumWindows_Sensors_Config.cmake
  "${CMAKE_BINARY_DIR}/TitaniumWindows_Sensors_Config.cmake"
  COPYONLY
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/TitaniumWindows_Sensors_ConfigVersion.cmake"
  VERSION ${TitaniumWindows_Sensors_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# Store the current build directory in the CMake user package registry
# so that find_package(TitaniumWindows_Sensors) works.
export(PACKAGE TitaniumWindows_Sensors)
