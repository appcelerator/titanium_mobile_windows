# Titanium for Windows
#
# Copyright (c) 2014-2015 by Appcelerator, Inc. All Rights Reserved.
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

project(TitaniumWindows)

set(TitaniumWindows_VERSION 0.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

option(TitaniumWindows_DISABLE_TESTS "Disable compiling the tests" OFF)

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

get_filename_component(APPCELERATOR_CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake ABSOLUTE)

# Define helper functions and macros.
include(${APPCELERATOR_CMAKE_MODULE_PATH}/internal_utils.cmake)

# Defined in internal_utils.cmake.
config_compiler_and_linker()

# Allow "make test" to work.
enable_testing()

get_filename_component(Filesystem_SOURCE_DIR        ${PROJECT_SOURCE_DIR}/../Filesystem        ABSOLUTE)
get_filename_component(Global_SOURCE_DIR            ${PROJECT_SOURCE_DIR}/../Global            ABSOLUTE)
get_filename_component(HAL_SOURCE_DIR               ${PROJECT_SOURCE_DIR}/../HAL               ABSOLUTE)
get_filename_component(LayoutEngine_SOURCE_DIR      ${PROJECT_SOURCE_DIR}/../LayoutEngine      ABSOLUTE)
get_filename_component(Media_SOURCE_DIR             ${PROJECT_SOURCE_DIR}/../Media             ABSOLUTE)
get_filename_component(Network_SOURCE_DIR           ${PROJECT_SOURCE_DIR}/../Network           ABSOLUTE)
get_filename_component(Sensors_SOURCE_DIR           ${PROJECT_SOURCE_DIR}/../Sensors           ABSOLUTE)
get_filename_component(Ti_SOURCE_DIR                ${PROJECT_SOURCE_DIR}/../Ti                ABSOLUTE)
get_filename_component(TitaniumKit_SOURCE_DIR       ${PROJECT_SOURCE_DIR}/../TitaniumKit       ABSOLUTE)
get_filename_component(UI_SOURCE_DIR                ${PROJECT_SOURCE_DIR}/../UI                ABSOLUTE)
get_filename_component(Utility_SOURCE_DIR           ${PROJECT_SOURCE_DIR}/../Utility           ABSOLUTE)

add_subdirectory(${Filesystem_SOURCE_DIR}    ${CMAKE_CURRENT_BINARY_DIR}/Filesystem    EXCLUDE_FROM_ALL)
add_subdirectory(${Global_SOURCE_DIR}        ${CMAKE_CURRENT_BINARY_DIR}/Global        EXCLUDE_FROM_ALL)
if (NOT TARGET HAL)
  add_subdirectory(${HAL_SOURCE_DIR}         ${CMAKE_CURRENT_BINARY_DIR}/HAL           EXCLUDE_FROM_ALL)
endif()
if (NOT TARGET LayoutEngine)
  add_subdirectory(${LayoutEngine_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/LayoutEngine EXCLUDE_FROM_ALL)
endif()
add_subdirectory(${Media_SOURCE_DIR}         ${CMAKE_CURRENT_BINARY_DIR}/Media         EXCLUDE_FROM_ALL)
add_subdirectory(${Network_SOURCE_DIR}       ${CMAKE_CURRENT_BINARY_DIR}/Network       EXCLUDE_FROM_ALL)
add_subdirectory(${Sensors_SOURCE_DIR}       ${CMAKE_CURRENT_BINARY_DIR}/Sensors       EXCLUDE_FROM_ALL)
add_subdirectory(${Ti_SOURCE_DIR}            ${CMAKE_CURRENT_BINARY_DIR}/Ti            EXCLUDE_FROM_ALL)
if(NOT TARGET TitaniumKit)
  add_subdirectory(${TitaniumKit_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/TitaniumKit   EXCLUDE_FROM_ALL)
endif()
if (NOT TARGET TitaniumWindows_UI)
  add_subdirectory(${UI_SOURCE_DIR}            ${CMAKE_CURRENT_BINARY_DIR}/UI            EXCLUDE_FROM_ALL)
endif()
if(NOT TARGET TitaniumWindows_Utility)
  add_subdirectory(${Utility_SOURCE_DIR}     ${CMAKE_CURRENT_BINARY_DIR}/Utility       EXCLUDE_FROM_ALL)
endif()

set(SOURCE_TitaniumWindows
  include/TitaniumWindows/TitaniumWindows.hpp
  src/TitaniumWindows.cpp
  src/Blob.cpp
  include/TitaniumWindows/Blob.hpp
  src/File.cpp
  include/TitaniumWindows/File.hpp
  include/TitaniumWindows/detail/TitaniumWindowsBase.hpp
  include/TitaniumWindows/TitaniumApplicationCallback.hpp
)

add_library(TitaniumWindows SHARED ${SOURCE_TitaniumWindows})

include(GenerateExportHeader)
generate_export_header(TitaniumWindows)
target_compile_definitions(TitaniumWindows PRIVATE TitaniumWindows_EXPORTS)

target_link_libraries(TitaniumWindows
  TitaniumWindows_Filesystem
  TitaniumWindows_Global
  HAL
  LayoutEngine
  TitaniumWindows_Media
  TitaniumWindows_Network
  TitaniumWindows_Sensors
  TitaniumWindows_Ti
  TitaniumKit
  TitaniumWindows_UI
  TitaniumWindows_Utility
  )

target_include_directories(TitaniumWindows PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  $<TARGET_PROPERTY:TitaniumWindows_Filesystem,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows_Global,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:HAL,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:LayoutEngine,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows_Media,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows_Network,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows_Sensors,INTERFACE_INCLUDE_DIRECTORIES> 
  $<TARGET_PROPERTY:TitaniumWindows_Ti,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumKit,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows_UI,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows_Utility,INTERFACE_INCLUDE_DIRECTORIES>
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

install(TARGETS TitaniumWindows EXPORT TitaniumWindows_Targets
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
