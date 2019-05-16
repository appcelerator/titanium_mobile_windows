# LayoutEngine
# Author: Russell W. McMahon
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.
cmake_minimum_required(VERSION 3.0.0)

project(LayoutEngine VERSION 0.5.0 LANGUAGES CXX)

option(LayoutEngine_DISABLE_TESTS "Disable compiling the tests" OFF)

# necessary to provide <LIBRARY>_EXPORT.h downstream
set(CMAKE_INCLUDE_CURRENT_DIR ON)		
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

set(SOURCE_LayoutEngine
  include/LayoutEngine/LayoutEngine.hpp
  src/Common.cpp
  src/Composite.cpp
  src/Element.cpp
  src/Horizontal.cpp
  src/Node.cpp
  src/ParseProperty.cpp
  src/Vertical.cpp
)

source_group(LayoutEngine FILES ${SOURCE_LayoutEngine})

# Turn on precompiled headers
include(precompiled_header)
enable_precompiled_headers(src/stdafx.h SOURCE_LayoutEngine)

add_library(LayoutEngine STATIC
  ${SOURCE_LayoutEngine}
)

include(GenerateExportHeader)
generate_export_header(LayoutEngine)
target_compile_definitions(LayoutEngine PRIVATE LayoutEngine_EXPORTS)

target_include_directories(LayoutEngine
  PUBLIC 
      $<INSTALL_INTERFACE:include>    
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
      src
)

if (WIN32)
  # Silence this warning when lnking with the JavaScriptCore static
  # library:
  #
  # "warning LNK4099: PDB 'vc120.pdb' was not found with
  # 'JavaScriptCore-Debug.lib(...)' ...".
  # set_property(TARGET LayoutEngine APPEND PROPERTY LINK_FLAGS "/IGNORE:4099")
  
  # Silence this warning when lnking with the JavaScriptCore static
  # library for the i386 emulator:
  #
  # "JavaScriptCore-Debug.lib(JSStringRef.obj) : warning LNK4075:
  # ignoring '/EDITANDCONTINUE' due to '/SAFESEH' specification".
  #
  # According to "/IGNORE (Ignore Specific Warnings)" (see
  # http://msdn.microsoft.com/en-us/library/dn782850.aspx) some linker
  # warnings cannot be ignored and LNK4075 is one of them. However,
  # according to "/SAFESEH (Image has Safe Exception Handlers)" (see
  # http://msdn.microsoft.com/en-us/library/9a89h429.aspx):
  #
  # "/SAFESEH is only valid when linking for x86 targets."
  #
  # Therefore we test for the processor architecture we are targeting
  # and if its i386 (i.e. the emulator) then we pass /SAFESEH:NO to
  # the linker.
  # 
  # If target platform is Windows Phone/Store,
  # we should not disable SAFESEH otherwise Windows App Certification will fail.
  # 
  if (NOT CMAKE_SYSTEM_NAME MATCHES "^Windows(Phone|Store)$")
    include(${APPCELERATOR_CMAKE_MODULE_PATH}/TargetArch.cmake)
    target_architecture(target_architecture)
    if (${target_architecture} STREQUAL i386)
      set_property(TARGET HAL APPEND_STRING PROPERTY LINK_FLAGS " /SAFESEH:NO")
    endif()
  endif()

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
  set_property(TARGET LayoutEngine APPEND_STRING PROPERTY LINK_FLAGS_DEBUG "/OPT:NOREF /OPT:NOICF")
endif()

if (NOT LayoutEngine_DISABLE_TESTS)
  add_subdirectory(examples)
  add_subdirectory(test)
endif()

# Support find_package(LayoutEngine 0.5 REQUIRED)

set_property(TARGET LayoutEngine PROPERTY VERSION ${LayoutEngine_VERSION})
set_property(TARGET LayoutEngine PROPERTY SOVERSION 0)
set_property(TARGET LayoutEngine PROPERTY INTERFACE_LayoutEngine_MAJOR_VERSION 0)
set_property(TARGET LayoutEngine APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING LayoutEngine_MAJOR_VERSION
)

install(TARGETS LayoutEngine
  EXPORT LayoutEngineTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

export(EXPORT LayoutEngineTargets
  FILE "${CMAKE_BINARY_DIR}/LayoutEngineTargets.cmake"
)

configure_file(cmake/LayoutEngineConfig.cmake
  "${CMAKE_BINARY_DIR}/LayoutEngineConfig.cmake"
  COPYONLY
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/LayoutEngineConfigVersion.cmake"
  VERSION ${LayoutEngine_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# Store the current build directory in the CMake user package registry
# so that find_package(LayoutEngine) works.
export(PACKAGE LayoutEngine)

#[[
# TODO: Install files to external locations.

set(ConfigPackageLocation lib/cmake/LayoutEngine)
install(EXPORT LayoutEngineTargets
  DESTINATION ${ConfigPackageLocation}
)

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/LayoutEngineConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/LayoutEngineConfigVersion.cmake"
  DESTINATION ${ConfigPackageLocation}
  COMPONENT Devel
)
#]]
