# Global for Windows
#
# Copyright (c) 2014-2019 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.
cmake_minimum_required(VERSION 3.0.0)

project(TitaniumWindows_Global VERSION 0.1.0 LANGUAGES CXX)

option(TitaniumWindows_Global_DISABLE_TESTS "Disable compiling the tests" OFF)

# necessary to provide <LIBRARY>_EXPORT.h downstream
set(CMAKE_INCLUDE_CURRENT_DIR ON)		
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(SOURCE_Global
  include/TitaniumWindows/GlobalObject.hpp
  src/GlobalObject.cpp
  include/TitaniumWindows/GlobalString.hpp
  src/GlobalString.cpp
  src/TitaniumEntryPoint.cpp
)
source_group(Titanium\\Global FILES ${SOURCE_Global})

# Turn on precompiled headers
include(precompiled_header)
enable_precompiled_headers(src/stdafx.h SOURCE_Global)
add_library(TitaniumWindows_Global SHARED
  ${SOURCE_Global}
)

include(GenerateExportHeader)
generate_export_header(TitaniumWindows_Global)
target_compile_definitions(TitaniumWindows_Global PRIVATE TitaniumWindows_Global_EXPORTS)

target_include_directories(TitaniumWindows_Global
  PUBLIC 
      $<INSTALL_INTERFACE:include>    
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
      src
)

target_link_libraries(TitaniumWindows_Global
  PUBLIC
    TitaniumKit
  PRIVATE
    TitaniumWindows_Utility
)

set_target_properties(TitaniumWindows_Global PROPERTIES VS_WINRT_COMPONENT TRUE)

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
set_property(TARGET TitaniumWindows_Global APPEND_STRING PROPERTY LINK_FLAGS_DEBUG "/OPT:NOREF /OPT:NOICF")

if (NOT TitaniumWindows_Global_DISABLE_TESTS)
  add_subdirectory(test)
endif()


# Support find_package(TitaniumWindows_Global 0.1 REQUIRED)

set_property(TARGET TitaniumWindows_Global PROPERTY VERSION ${TitaniumWindows_Global_VERSION})
set_property(TARGET TitaniumWindows_Global PROPERTY SOVERSION 0)
set_property(TARGET TitaniumWindows_Global PROPERTY INTERFACE_TitaniumWindows_Global_MAJOR_VERSION 0)
set_property(TARGET TitaniumWindows_Global APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING TitaniumWindows_Global_MAJOR_VERSION
)

install(TARGETS TitaniumWindows_Global
  EXPORT TitaniumWindows_Global_Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

export(EXPORT TitaniumWindows_Global_Targets
  FILE "${CMAKE_BINARY_DIR}/TitaniumWindows_Global_Targets.cmake"
)

configure_file(cmake/TitaniumWindows_Global_Config.cmake
  "${CMAKE_BINARY_DIR}/TitaniumWindows_Global_Config.cmake"
  COPYONLY
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/TitaniumWindows_Global_ConfigVersion.cmake"
  VERSION ${TitaniumWindows_Global_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# Store the current build directory in the CMake user package registry
# so that find_package(TitaniumWindows_Global) works.
export(PACKAGE TitaniumWindows_Global)
