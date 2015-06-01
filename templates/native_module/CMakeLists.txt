# Titanium Windows Native Module - Global
#
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

project(TitaniumWindows_Global)

set(TitaniumWindows_Global_VERSION 0.1.0)

set(WINDOWS_SOURCE_DIR "<%- tisdkPath.replace(/\\/g,'/') %>/windows")

SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib" ".dll")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

option(TitaniumWindows_Global_DISABLE_TESTS "Disable compiling the tests" OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

get_filename_component(APPCELERATOR_CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ABSOLUTE)
list(INSERT CMAKE_MODULE_PATH 0 ${APPCELERATOR_CMAKE_MODULE_PATH})

set(Boost_USE_STATIC_LIBS ON )
set(Boost_USE_MULTITHREADED ON )
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.55.0 REQUIRED)

find_package(HAL REQUIRED)
find_package(TitaniumKit REQUIRED)
find_package(JavaScriptCore REQUIRED)
find_package(TitaniumWindows_Utility REQUIRED)

enable_testing()

set(SOURCE_Global
  include/TitaniumWindows/detail/GlobalBase.hpp
  include/TitaniumWindows/GlobalObject.hpp
  src/GlobalObject.cpp
  include/TitaniumWindows/NativeModuleLoader.hpp
  src/NativeModuleLoader.cpp
  )

source_group(TitaniumWindows\\Global FILES ${SOURCE_Global})

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(TitaniumWindows_Global SHARED
  ${SOURCE_Global}
  )

include(GenerateExportHeader)
generate_export_header(TitaniumWindows_Global)
target_compile_definitions(TitaniumWindows_Global PRIVATE TitaniumWindows_Global_EXPORTS)

target_include_directories(TitaniumWindows_Global PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  $<TARGET_PROPERTY:HAL,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumKit,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows_Utility,INTERFACE_INCLUDE_DIRECTORIES>
  ${JavaScriptCore_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  )

target_link_libraries(TitaniumWindows_Global
  ${Boost_LIBRARIES}
  HAL
  TitaniumKit
  TitaniumWindows_Utility
  )

set_target_properties(TitaniumWindows_Global PROPERTIES VS_WINRT_COMPONENT TRUE)

set_property(TARGET TitaniumWindows_Global APPEND_STRING PROPERTY LINK_FLAGS_DEBUG "/OPT:NOREF /OPT:NOICF")

if (NOT TitaniumWindows_Global_DISABLE_TESTS)
  add_subdirectory(test)
endif()

set_property(TARGET TitaniumWindows_Global PROPERTY VERSION ${TitaniumWindows_Global_VERSION})
set_property(TARGET TitaniumWindows_Global PROPERTY SOVERSION 0)
set_property(TARGET TitaniumWindows_Global PROPERTY INTERFACE_TitaniumWindows_Global_MAJOR_VERSION 0)
set_property(TARGET TitaniumWindows_Global APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING TitaniumWindows_Global_MAJOR_VERSION
  )

install(TARGETS TitaniumWindows_Global EXPORT TitaniumWindows_Global_Targets
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

set_target_properties(TitaniumWindows_Global PROPERTIES VS_WINRT_REFERENCES HAL)

export(PACKAGE TitaniumWindows_Global)