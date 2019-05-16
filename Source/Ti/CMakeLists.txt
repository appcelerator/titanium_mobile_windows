# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.
cmake_minimum_required(VERSION 3.0.0)

project(TitaniumWindows_Ti VERSION 0.1.0 LANGUAGES CXX)

option(TitaniumWindows_Ti_DISABLE_TESTS "Disable compiling the tests" OFF)

# necessary to provide <LIBRARY>_EXPORT.h downstream
set(CMAKE_INCLUDE_CURRENT_DIR ON)		
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

# Convert group.js into a c string in an hpp that we can include
include(GenerateCPPHeaderFile)
generate_cpp_header_file(resource_group_js_hpp ${PROJECT_SOURCE_DIR}/src/Contacts/group.js ${PROJECT_SOURCE_DIR}/include/TitaniumWindows/Contacts/group_js.hpp)

set(SOURCE_Ti
  include/TitaniumWindows/TiModule.hpp
  src/TiModule.cpp
  src/TitaniumEntryPoint.cpp
)

set(SOURCE_Codec
  include/TitaniumWindows/Codec.hpp
  src/Codec.cpp
)

set(SOURCE_API
  include/TitaniumWindows/API.hpp
  src/API.cpp
)

set(SOURCE_Locale
  include/TitaniumWindows/Locale.hpp
  src/Locale.cpp
)

set(SOURCE_App
  include/TitaniumWindows/App/Properties.hpp
  src/App/Properties.cpp
  include/TitaniumWindows/App.hpp
  include/TitaniumWindows/AppModule.hpp
  src/AppModule.cpp
  include/TitaniumWindows/App/WindowsModule.hpp
  src/App/WindowsModule.cpp
  include/TitaniumWindows/App/BackgroundService.hpp
  src/App/BackgroundService.cpp
  include/TitaniumWindows/App/BackgroundServiceTask.hpp
  src/App/BackgroundServiceTask.cpp
)

set(SOURCE_Platform
  include/TitaniumWindows/Platform.hpp
  include/TitaniumWindows/DisplayCaps.hpp
  src/Platform.cpp
  src/DisplayCaps.cpp
)

set(SOURCE_Contacts
  include/TitaniumWindows/Contacts.hpp
  include/TitaniumWindows/Contacts/group_js.hpp
  include/TitaniumWindows/Contacts/Group.hpp
  include/TitaniumWindows/Contacts/Person.hpp
  src/Contacts.cpp
  src/Contacts/Person.cpp
  src/Contacts/Group.cpp
  src/Contacts/group.js
)

set(SOURCE_Utils
  include/TitaniumWindows/Utils.hpp
  src/Utils.cpp
)

source_group(Titanium\\Ti FILES ${SOURCE_Ti})
source_group(Titanium\\Codec FILES ${SOURCE_Codec})
source_group(Titanium\\API FILES ${SOURCE_API})
source_group(Titanium\\App FILES ${SOURCE_App})
source_group(Titanium\\Locale FILES ${SOURCE_Locale})
source_group(Titanium\\Platform FILES ${SOURCE_Platform})
source_group(Titanium\\Contacts FILES ${SOURCE_Contacts})
source_group(Titanium\\Utils FILES ${SOURCE_Utils})

set(SOURCE_ALL
  ${SOURCE_Ti}
  ${SOURCE_Codec}
  ${SOURCE_API}
  ${SOURCE_App}
  ${SOURCE_Locale}
  ${SOURCE_Platform}
  ${SOURCE_Contacts}
  ${SOURCE_Utils}
)

# Turn on precompiled headers
include(precompiled_header)
enable_precompiled_headers(src/stdafx.h SOURCE_ALL)

add_library(TitaniumWindows_Ti SHARED
  ${SOURCE_ALL}
)

include(GenerateExportHeader)
generate_export_header(TitaniumWindows_Ti)
target_compile_definitions(TitaniumWindows_Ti PRIVATE TitaniumWindows_Ti_EXPORTS)

target_include_directories(TitaniumWindows_Ti
  PUBLIC 
      $<INSTALL_INTERFACE:include>    
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
      src
)

target_link_libraries(TitaniumWindows_Ti
  PUBLIC
    TitaniumKit
    TitaniumWindows_Utility
)

set_target_properties(TitaniumWindows_Ti PROPERTIES VS_WINRT_COMPONENT TRUE)

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
set_property(TARGET TitaniumWindows_Ti APPEND_STRING PROPERTY LINK_FLAGS_DEBUG "/OPT:NOREF /OPT:NOICF")

if (NOT TitaniumWindows_Ti_DISABLE_TESTS)
  add_subdirectory(test)
endif()


# Support find_package(TitaniumWindows_Ti 0.1 REQUIRED)

set_property(TARGET TitaniumWindows_Ti PROPERTY VERSION ${TitaniumWindows_Ti_VERSION})
set_property(TARGET TitaniumWindows_Ti PROPERTY SOVERSION 0)
set_property(TARGET TitaniumWindows_Ti PROPERTY INTERFACE_TitaniumWindows_Ti_MAJOR_VERSION 0)
set_property(TARGET TitaniumWindows_Ti APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING TitaniumWindows_Ti_MAJOR_VERSION
)

install(TARGETS TitaniumWindows_Ti
  EXPORT TitaniumWindows_Ti_Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

export(EXPORT TitaniumWindows_Ti_Targets
  FILE "${CMAKE_BINARY_DIR}/TitaniumWindows_Ti_Targets.cmake"
)

configure_file(cmake/TitaniumWindows_Ti_Config.cmake
  "${CMAKE_BINARY_DIR}/TitaniumWindows_Ti_Config.cmake"
  COPYONLY
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/TitaniumWindows_Ti_ConfigVersion.cmake"
  VERSION ${TitaniumWindows_Ti_VERSION}
  COMPATIBILITY AnyNewerVersion
)

# Store the current build directory in the CMake user package registry
# so that find_package(TitaniumWindows_Ti) works.
export(PACKAGE TitaniumWindows_Ti)
