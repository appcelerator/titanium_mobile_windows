# Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.
cmake_minimum_required(VERSION 3.0.0)

if(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsPhone")
  set(PLATFORM wp)
  add_definitions("-DPHONE")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore")
  set(PLATFORM store)
else()
  message(FATAL_ERROR "This app supports Store / Phone only.")
endif()

project(TitaniumWindows_Media)

set(TitaniumWindows_Media_VERSION 0.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

option(TitaniumWindows_Media_DISABLE_TESTS "Disable compiling the tests" OFF)

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

get_filename_component(APPCELERATOR_CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake ABSOLUTE)

# Define helper functions and macros.
include(${APPCELERATOR_CMAKE_MODULE_PATH}/internal_utils.cmake)

# Defined in internal_utils.cmake.
config_compiler_and_linker()

# Allow "make test" to work.
enable_testing()

if(NOT TARGET TitaniumKit)
	get_filename_component(TitaniumKit_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../TitaniumKit ABSOLUTE)
	add_subdirectory(${TitaniumKit_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/TitaniumKit EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_Utility)
  get_filename_component(Utility_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../Utility ABSOLUTE)
  add_subdirectory(${Utility_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Utility EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_UI)
  get_filename_component(UI_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../UI ABSOLUTE)
  add_subdirectory(${UI_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/UI EXCLUDE_FROM_ALL)
endif()

set(SOURCE_Media
  include/TitaniumWindows/Media.hpp
  include/TitaniumWindows/Media/AudioBackground.hpp
  include/TitaniumWindows/Media/AudioPlayer.hpp
  include/TitaniumWindows/Media/AudioRecorder.hpp
  include/TitaniumWindows/Media/Item.hpp
  include/TitaniumWindows/Media/Sound.hpp
  include/TitaniumWindows/Media/MusicPlayer.hpp
  include/TitaniumWindows/Media/VideoPlayer.hpp
  src/Media.cpp
  src/Media/AudioBackground.cpp
  src/Media/AudioPlayer.cpp
  src/Media/AudioRecorder.cpp
  src/Media/Item.cpp
  src/Media/Sound.cpp
  src/Media/MusicPlayer.cpp
  src/Media/VideoPlayer.cpp
  src/TitaniumEntryPoint.cpp
  )

source_group(Titanium\\Media FILES ${SOURCE_Media})

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(TitaniumWindows_Media SHARED
  ${SOURCE_Media}
  )

include(GenerateExportHeader)
generate_export_header(TitaniumWindows_Media)
target_compile_definitions(TitaniumWindows_Media PRIVATE TitaniumWindows_Media_EXPORTS)

target_include_directories(TitaniumWindows_Media PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  $<TARGET_PROPERTY:TitaniumKit,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows_Utility,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows_UI,INTERFACE_INCLUDE_DIRECTORIES>
  )

target_link_libraries(TitaniumWindows_Media
  TitaniumKit
  TitaniumWindows_Utility
  TitaniumWindows_UI
  )

set_target_properties(TitaniumWindows_Media PROPERTIES VS_WINRT_COMPONENT TRUE)

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
set_property(TARGET TitaniumWindows_Media APPEND_STRING PROPERTY LINK_FLAGS_DEBUG "/OPT:NOREF /OPT:NOICF")

if (NOT TitaniumWindows_Media_DISABLE_TESTS)
  add_subdirectory(test)
endif()


# Support find_package(TitaniumWindows_Media 0.1 REQUIRED)

set_property(TARGET TitaniumWindows_Media PROPERTY VERSION ${TitaniumWindows_Media_VERSION})
set_property(TARGET TitaniumWindows_Media PROPERTY SOVERSION 0)
set_property(TARGET TitaniumWindows_Media PROPERTY INTERFACE_TitaniumWindows_Media_MAJOR_VERSION 0)
set_property(TARGET TitaniumWindows_Media APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING TitaniumWindows_Media_MAJOR_VERSION
  )

install(TARGETS TitaniumWindows_Media EXPORT TitaniumWindows_Media_Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  )

export(EXPORT TitaniumWindows_Media_Targets
  FILE "${CMAKE_BINARY_DIR}/TitaniumWindows_Media_Targets.cmake"
)

configure_file(cmake/TitaniumWindows_Media_Config.cmake
  "${CMAKE_BINARY_DIR}/TitaniumWindows_Media_Config.cmake"
  COPYONLY
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/TitaniumWindows_Media_ConfigVersion.cmake"
  VERSION ${TitaniumWindows_Media_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

# Store the current build directory in the CMake user package registry
# so that find_package(TitaniumWindows_Media) works.
export(PACKAGE TitaniumWindows_Media)
