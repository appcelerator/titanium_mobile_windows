# TitaniumKit
#
# Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.
cmake_minimum_required(VERSION 3.0.0)

project(TitaniumKit)

set(TitaniumKit_VERSION 0.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

option(TitaniumKit_DISABLE_TESTS "Disable compiling the tests" OFF)

# Define helper functions and macros.
include(${PROJECT_SOURCE_DIR}/cmake/internal_utils.cmake)

# Defined in internal_utils.cmake.
config_compiler_and_linker()
#config_cmake_system_framework_path(macosx)

# Allow "make test" to work.
enable_testing()

if (NOT TARGET HAL)
  get_filename_component(HAL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../HAL ABSOLUTE)
  add_subdirectory(${HAL_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/HAL EXCLUDE_FROM_ALL)
endif()

# find_package(HAL REQUIRED)

get_filename_component(APPCELERATOR_CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake ABSOLUTE)
list(INSERT CMAKE_MODULE_PATH 0 ${APPCELERATOR_CMAKE_MODULE_PATH})

# Convert analytics.js into a c string in an hpp that we can include
include(GenerateCPPHeaderFile)
generate_cpp_header_file(resource_analytics_js_hpp ${PROJECT_SOURCE_DIR}/src/analytics.js ${PROJECT_SOURCE_DIR}/include/Titanium/analytics_js.hpp)
generate_cpp_header_file(resource_listview_js_hpp ${PROJECT_SOURCE_DIR}/src/UI/listview.js ${PROJECT_SOURCE_DIR}/include/Titanium/UI/listview_js.hpp)
generate_cpp_header_file(resource_xml_dom_js_hpp ${PROJECT_SOURCE_DIR}/src/XML/dom.js ${PROJECT_SOURCE_DIR}/include/Titanium/XML/dom_js.hpp)
generate_cpp_header_file(resource_xml_dom_parser_js_hpp ${PROJECT_SOURCE_DIR}/src/XML/dom-parser.js ${PROJECT_SOURCE_DIR}/include/Titanium/XML/dom_parser_js.hpp)
generate_cpp_header_file(resource_xml_sax_js_hpp ${PROJECT_SOURCE_DIR}/src/XML/sax.js ${PROJECT_SOURCE_DIR}/include/Titanium/XML/sax_js.hpp)

set(Boost_USE_STATIC_LIBS ON )
set(Boost_USE_MULTITHREADED ON )
set(Boost_USE_STATIC_RUNTIME OFF)

# Travis only supports Boost 1.55, which is good enough for now.
find_package(Boost 1.55.0 REQUIRED)

set(SOURCE_TitaniumKit
  include/Titanium/Titanium.hpp
  include/Titanium/ApplicationBuilder.hpp
  src/ApplicationBuilder.cpp
  include/Titanium/Application.hpp
  src/Application.cpp
  include/Titanium/GlobalObject.hpp
  src/GlobalObject.cpp
  include/Titanium/Module.hpp
  src/Module.cpp
  include/Titanium/Gesture.hpp
  src/Gesture.cpp
  )

set(SOURCE_TitaniumKit_detail
  include/Titanium/detail/TiBase.hpp
  src/detail/TiBase.cpp
  include/Titanium/detail/HashUtilities.hpp
  include/Titanium/detail/TiUtil.hpp
  src/detail/TiUtil.cpp
  )

set(SOURCE_Ti
  include/Titanium/TiModule.hpp
  src/TiModule.cpp
  )

set(SOURCE_API
  include/Titanium/API.hpp
  src/API.cpp
  )

set(SOURCE_Database
  include/Titanium/DatabaseModule.hpp
  src/DatabaseModule.cpp
  include/Titanium/Database/DB.hpp
  src/Database/DB.cpp
  include/Titanium/Database/ResultSet.hpp
  src/Database/ResultSet.cpp
  include/Titanium/Database/Constants.hpp
  src/Database/Constants.cpp
  include/sqlite3.h
  src/sqlite3.c
  )

set(SOURCE_Platform
  include/Titanium/PlatformModule.hpp
  include/Titanium/Platform/DisplayCaps.hpp
  src/PlatformModule.cpp
  src/Platform/DisplayCaps.cpp
  )

set(SOURCE_Accelerometer
  include/Titanium/Accelerometer.hpp
  src/Accelerometer.cpp
  )

set(SOURCE_Gesture
  include/Titanium/Gesture.hpp
  src/Gesture.cpp
  )

set(SOURCE_Blob
  include/Titanium/Blob.hpp
  src/Blob.cpp
  )

set(SOURCE_Filesystem
  include/Titanium/FilesystemModule.hpp
  src/FilesystemModule.cpp
  include/Titanium/Filesystem/File.hpp
  src/Filesystem/File.cpp
  include/Titanium/Filesystem/Constants.hpp
  src/Filesystem/Constants.cpp
  )

set(SOURCE_Network
  include/Titanium/NetworkModule.hpp
  src/NetworkModule.cpp
  include/Titanium/Network/HTTPClient.hpp
  src/Network/HTTPClient.cpp
  include/Titanium/Network/Constants.hpp
  src/Network/Constants.cpp
  )

set(SOURCE_UI
  include/Titanium/UIModule.hpp
  src/UIModule.cpp
  include/Titanium/UI/Constants.hpp
  src/UI/Constants.cpp
  include/Titanium/UI/Point.hpp
  src/UI/Point.cpp
  include/Titanium/UI/Dimension.hpp
  src/UI/Dimension.cpp
  include/Titanium/UI/Font.hpp
  src/UI/Font.cpp
  include/Titanium/UI/Gradient.hpp
  src/UI/Gradient.cpp
  include/Titanium/UI/ImageView.hpp
  src/UI/ImageView.cpp
  include/Titanium/UI/View.hpp
  src/UI/View.cpp
  include/Titanium/UI/Window.hpp
  src/UI/Window.cpp
  include/Titanium/UI/Button.hpp
  src/UI/Button.cpp
  include/Titanium/UI/Label.hpp
  src/UI/Label.cpp
  include/Titanium/UI/Animation.hpp
  src/UI/Animation.cpp
  include/Titanium/UI/TextArea.hpp
  src/UI/Button.cpp
  include/Titanium/UI/TextField.hpp
  src/UI/TextField.cpp
  include/Titanium/UI/Picker.hpp
  src/UI/Picker.cpp
  include/Titanium/UI/WebView.hpp
  src/UI/WebView.cpp
  include/Titanium/UI/AlertDialog.hpp
  src/UI/AlertDialog.cpp
  include/Titanium/UI/ScrollView.hpp
  src/UI/ScrollView.cpp
  include/Titanium/UI/Slider.hpp
  src/UI/Slider.cpp
  include/Titanium/UI/ListViewAnimationProperties.hpp
  src/UI/ListViewAnimationProperties.cpp
  include/Titanium/UI/ListViewMarkerProps.hpp
  src/UI/ListViewMarkerProps.cpp
  include/Titanium/UI/ListView.hpp
  src/UI/ListView.cpp
  include/Titanium/UI/ListSection.hpp
  src/UI/ListSection.cpp
  include/Titanium/UI/listview_js.hpp
  include/Titanium/UI/EmailDialog.hpp
  src/UI/EmailDialog.cpp
  )

set(SOURCE_TiLogger_detail
  include/Titanium/detail/TiLogger.hpp
  include/Titanium/detail/TiLoggerPolicyInterface.hpp
  include/Titanium/detail/TiLoggerPolicyConsole.hpp
  include/Titanium/detail/TiLoggerPolicyFile.hpp
  include/Titanium/detail/TiLoggerPimpl.hpp
  src/detail/TiLoggerPimpl.cpp
  )

set(SOURCE_App
  include/Titanium/App.hpp
  src/App.cpp
)

set(SOURCE_Properties
  include/Titanium/App/Properties.hpp
  src/App/Properties.cpp
)

set(SOURCE_Analytics
  include/Titanium/Analytics.hpp
  include/Titanium/analytics_js.hpp
  src/Analytics.cpp
)

set(SOURCE_XML
  include/Titanium/XML.hpp
  include/Titanium/XML/dom_js.hpp
  include/Titanium/XML/dom_parser_js.hpp
  include/Titanium/XML/sax_js.hpp
  src/XML.cpp
)

set(SOURCE_Map
  include/Titanium/MapModule.hpp
  src/MapModule.cpp
  include/Titanium/Map/Constants.hpp
  src/Map/Constants.cpp
  include/Titanium/Map/View.hpp
  src/Map/View.cpp
)

source_group(TitaniumKit                   FILES ${SOURCE_TitaniumKit})
source_group(TitaniumKit\\detail           FILES ${SOURCE_TitaniumKit_detail})
source_group(TitaniumKit\\Ti               FILES ${SOURCE_Ti})
source_group(TitaniumKit\\API              FILES ${SOURCE_API})
source_group(TitaniumKit\\Database         FILES ${SOURCE_Database})
source_group(TitaniumKit\\Platform         FILES ${SOURCE_Platform})
source_group(TitaniumKit\\Accelerometer    FILES ${SOURCE_Accelerometer})
source_group(TitaniumKit\\Gesture          FILES ${SOURCE_Gesture})
source_group(TitaniumKit\\Blob             FILES ${SOURCE_Blob})
source_group(TitaniumKit\\Filesystem       FILES ${SOURCE_Filesystem})
source_group(TitaniumKit\\App              FILES ${SOURCE_App})
source_group(TitaniumKit\\App\\Properties  FILES ${SOURCE_Properties})
source_group(TitaniumKit\\Network          FILES ${SOURCE_Network})
source_group(TitaniumKit\\Analytics        FILES ${SOURCE_Analytics})
source_group(TitaniumKit\\XML              FILES ${SOURCE_XML})
source_group(TitaniumKit\\Map              FILES ${SOURCE_Map})
source_group(TitaniumKit\\UI               FILES ${SOURCE_UI})
source_group(TitaniumKit\\TiLogger\\detail FILES ${SOURCE_TiLogger_detail})

#set(CMAKE_CXX_VISIBILITY_PRESET hidden)
#set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(TitaniumKit SHARED
  ${SOURCE_TitaniumKit}
  ${SOURCE_TitaniumKit_detail}
  ${SOURCE_Ti}
  ${SOURCE_API}
  ${SOURCE_Database}
  ${SOURCE_Platform}
  ${SOURCE_Accelerometer}
  ${SOURCE_Gesture}
  ${SOURCE_Blob}
  ${SOURCE_Filesystem}
  ${SOURCE_App}
  ${SOURCE_Properties}
  ${SOURCE_Network}
  ${SOURCE_Analytics}
  ${SOURCE_XML}
  ${SOURCE_UI}
  ${SOURCE_Map}
  ${SOURCE_TiLogger_detail}
  )

add_dependencies(TitaniumKit resource_analytics_js_hpp)
add_dependencies(TitaniumKit resource_listview_js_hpp)
add_dependencies(TitaniumKit resource_xml_dom_js_hpp)
add_dependencies(TitaniumKit resource_xml_dom_parser_js_hpp)
add_dependencies(TitaniumKit resource_xml_sax_js_hpp)

include(GenerateExportHeader)
generate_export_header(TitaniumKit)
target_compile_definitions(TitaniumKit PRIVATE TitaniumKit_EXPORTS)
#target_compile_definitions(TitaniumKit PUBLIC TitaniumKit_STATIC_DEFINE)

# target_compile_definitions(TitaniumKit PUBLIC
#   $<TARGET_PROPERTY:HAL,INTERFACE_COMPILE_DEFINITIONS>
#   )

target_include_directories(TitaniumKit PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  $<TARGET_PROPERTY:HAL,INTERFACE_INCLUDE_DIRECTORIES>
  ${Boost_INCLUDE_DIRS}
  )

target_link_libraries(TitaniumKit
  HAL
  ${Boost_LIBRARIES}
  )

if (WIN32)
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
  set_property(TARGET TitaniumKit APPEND_STRING PROPERTY LINK_FLAGS_DEBUG "/OPT:NOREF /OPT:NOICF")
  
  # Fix error C1128: number of sections exceeded object file format limit
  set_property(TARGET TitaniumKit APPEND_STRING PROPERTY COMPILE_FLAGS "/bigobj")

  # Fix error C4996: 'std::_Copy_impl': Function call with parameters that may be unsafe (needed by boost::split)
  set_property(TARGET TitaniumKit APPEND_STRING PROPERTY COMPILE_FLAGS " -D_SCL_SECURE_NO_WARNINGS")
endif()

if (NOT TitaniumKit_DISABLE_TESTS)
  add_subdirectory(examples)
  add_subdirectory(test)
endif()

# When building sqlite3 for Windows Phone, set special flags!
# TODO Do the same for WindowsStore! This info is hard to find and lives in http://www.sqlite.org/cgi/src/artifact/fc6b0b233b5621f3
if(CMAKE_SYSTEM_NAME MATCHES "^Windows(Phone|Store)$")
  # For Store, we need /DWINAPI_FAMILY=WINAPI_FAMILY_APP but I think that's already done for us!
  set_source_files_properties(src/sqlite3.c PROPERTIES COMPILE_FLAGS "/DSQLITE_OS_WINRT=1 /DSQLITE_OMIT_LOAD_EXTENSION=1 /DSQLITE_WIN32_FILEMAPPING_API=1")
endif()

# Support find_package(TitaniumKit 0.1 REQUIRED)

set_property(TARGET TitaniumKit PROPERTY VERSION ${TitaniumKit_VERSION})
set_property(TARGET TitaniumKit PROPERTY SOVERSION 0)
set_property(TARGET TitaniumKit PROPERTY INTERFACE_TitaniumKit_MAJOR_VERSION 0)
set_property(TARGET TitaniumKit APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING TitaniumKit_MAJOR_VERSION
  )

install(TARGETS TitaniumKit EXPORT TitaniumKitTargets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  )

export(EXPORT TitaniumKitTargets
  FILE "${CMAKE_BINARY_DIR}/TitaniumKitTargets.cmake"
)

configure_file(cmake/TitaniumKitConfig.cmake
  "${CMAKE_BINARY_DIR}/TitaniumKitConfig.cmake"
  COPYONLY
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/TitaniumKitConfigVersion.cmake"
  VERSION ${TitaniumKit_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

# Store the current build directory in the CMake user package registry
# so that find_package(TitaniumKit) works.
export(PACKAGE TitaniumKit)
