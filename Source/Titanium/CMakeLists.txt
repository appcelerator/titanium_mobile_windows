# Titanium for Windows
#
# Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.
cmake_minimum_required(VERSION 3.0.0)

project(TitaniumWindows VERSION 0.1.0 LANGUAGES CXX)

option(TitaniumWindows_DISABLE_TESTS "Disable compiling the tests" OFF)

# necessary to provide <LIBRARY>_EXPORT.h downstream
set(CMAKE_INCLUDE_CURRENT_DIR ON)		
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(SOURCE_TitaniumWindows
  include/TitaniumWindows/TitaniumWindows.hpp
  src/TitaniumWindows.cpp
  src/Blob.cpp
  include/TitaniumWindows/Blob.hpp
  src/File.cpp
  include/TitaniumWindows/File.hpp
  include/TitaniumWindows/TitaniumApplicationCallback.hpp
)

# Turn on precompiled headers
include(precompiled_header)
enable_precompiled_headers(src/stdafx.h SOURCE_TitaniumWindows)

add_library(TitaniumWindows SHARED ${SOURCE_TitaniumWindows})

include(GenerateExportHeader)
generate_export_header(TitaniumWindows)
target_compile_definitions(TitaniumWindows PRIVATE TitaniumWindows_EXPORTS)

target_include_directories(TitaniumWindows
  PUBLIC 
      $<INSTALL_INTERFACE:include>    
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
      src
)

target_link_libraries(TitaniumWindows
  PUBLIC
    TitaniumKit
    TitaniumWindows_Utility
  PRIVATE
    TitaniumWindows_Global
    TitaniumWindows_Filesystem
    TitaniumWindows_Map
    TitaniumWindows_Media
    TitaniumWindows_Network
    TitaniumWindows_Sensors
    TitaniumWindows_Ti
    TitaniumWindows_UI
    LayoutEngine
)

set_target_properties(TitaniumWindows PROPERTIES VS_WINRT_COMPONENT TRUE)

# Silence this warning when linking the Debug configuration:
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
set_property(TARGET TitaniumWindows APPEND_STRING PROPERTY LINK_FLAGS_DEBUG "/OPT:NOREF /OPT:NOICF")

# Fix error C1128: number of sections exceeded object file format limit
set_property(TARGET TitaniumWindows APPEND_STRING PROPERTY COMPILE_FLAGS "/bigobj")

# Fix error C4996: 'std::_Copy_impl': Function call with parameters that may be unsafe (needed by boost::split)
set_property(TARGET TitaniumWindows APPEND_STRING PROPERTY COMPILE_FLAGS " -D_SCL_SECURE_NO_WARNINGS")

if (NOT TitaniumWindows_DISABLE_TESTS)
  add_subdirectory(test)
endif()


# Support find_package(TitaniumWindows 0.1 REQUIRED)

set_property(TARGET TitaniumWindows PROPERTY VERSION ${TitaniumWindows_VERSION})
set_property(TARGET TitaniumWindows PROPERTY SOVERSION 0)
set_property(TARGET TitaniumWindows PROPERTY INTERFACE_TitaniumWindows_MAJOR_VERSION 0)
set_property(TARGET TitaniumWindows APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING TitaniumWindows_MAJOR_VERSION
)

install(TARGETS TitaniumWindows
  EXPORT TitaniumWindows_Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

export(EXPORT TitaniumWindows_Targets
  FILE "${CMAKE_BINARY_DIR}/TitaniumWindows_Targets.cmake"
)

configure_file(cmake/TitaniumWindows_Config.cmake
  "${CMAKE_BINARY_DIR}/TitaniumWindows_Config.cmake"
  COPYONLY
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/TitaniumWindows_ConfigVersion.cmake"
  VERSION ${TitaniumWindows_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# Store the current build directory in the CMake user package registry
# so that find_package(TitaniumWindows) works.
export(PACKAGE TitaniumWindows)
