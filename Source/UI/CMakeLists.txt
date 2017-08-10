# Titanium.UI for Windows
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
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

project(TitaniumWindows_UI)

set(TitaniumWindows_UI_VERSION 0.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

option(TitaniumWindows_UI_DISABLE_TESTS "Disable compiling the tests" OFF)

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

set(SOURCE_UI
  include/TitaniumWindows/UI/Clipboard.hpp
  src/Clipboard.cpp
  include/TitaniumWindows/UI/ActivityIndicator.hpp
  src/ActivityIndicator.cpp
  include/TitaniumWindows/UI/AlertDialog.hpp
  src/AlertDialog.cpp
  include/TitaniumWindows/UI/Button.hpp
  src/Button.cpp
  include/TitaniumWindows/UI/EmailDialog.hpp
  src/EmailDialog.cpp
  include/TitaniumWindows/UI/ImageView.hpp
  src/ImageView.cpp
  include/TitaniumWindows/UI/Label.hpp
  src/Label.cpp
  include/TitaniumWindows/UI/ListView.hpp
  src/ListView.cpp
  include/TitaniumWindows/UI/Notification.hpp
  src/Notification.cpp
  include/TitaniumWindows/UI/OptionDialog.hpp
  src/OptionDialog.cpp
  include/TitaniumWindows/UI/Picker.hpp
  src/Picker.cpp
  include/TitaniumWindows/UI/PickerColumn.hpp
  src/PickerColumn.cpp
  include/TitaniumWindows/UI/PickerRow.hpp
  src/PickerRow.cpp
  include/TitaniumWindows/UI/ProgressBar.hpp
  src/ProgressBar.cpp
  include/TitaniumWindows/UI/SearchBar.hpp
  src/SearchBar.cpp
  include/TitaniumWindows/UI/ScrollableView.hpp
  src/ScrollableView.cpp
  include/TitaniumWindows/UI/ScrollView.hpp
  src/ScrollView.cpp
  include/TitaniumWindows/UI/Slider.hpp
  src/Slider.cpp
  include/TitaniumWindows/UI/Switch.hpp
  src/Switch.cpp
  include/TitaniumWindows/UI/Tab.hpp
  src/Tab.cpp
  include/TitaniumWindows/UI/TabGroup.hpp
  src/TabGroup.cpp
  include/TitaniumWindows/UI/TableView.hpp
  src/TableView.cpp
  include/TitaniumWindows/UI/TableViewRow.hpp
  src/TableViewRow.cpp
  include/TitaniumWindows/UI/TextArea.hpp
  src/TextArea.cpp
  include/TitaniumWindows/UI/TextField.hpp
  src/TextField.cpp
  include/TitaniumWindows/UIModule.hpp
  src/UIModule.cpp
  include/TitaniumWindows/UI/View.hpp
  src/View.cpp
  include/TitaniumWindows/UI/WebView.hpp
  src/WebView.cpp
  include/TitaniumWindows/UI/Window.hpp
  src/Window.cpp
  include/TitaniumWindows/UI/WindowsViewLayoutDelegate.hpp
  src/WindowsViewLayoutDelegate.cpp
  include/TitaniumWindows/UI/UIElement.hpp
  src/UIElement.cpp
  src/TitaniumEntryPoint.cpp
  )

source_group(Titanium\\UI FILES ${SOURCE_UI})

set(SOURCE_UI_Windows
  include/TitaniumWindows/UI/WindowsModule.hpp
  src/WindowsModule.cpp
  include/TitaniumWindows/UI/Windows/CommandBar.hpp
  src/Windows/CommandBar.cpp
  include/TitaniumWindows/UI/Windows/AppBarButton.hpp
  src/Windows/AppBarButton.cpp
  include/TitaniumWindows/UI/Windows/AppBarToggleButton.hpp
  src/Windows/AppBarToggleButton.cpp
  include/TitaniumWindows/UI/Windows/AppBarSeparator.hpp
  src/Windows/AppBarSeparator.cpp
  include/TitaniumWindows/UI/Windows/SystemIcon.hpp
  src/Windows/SystemIcon.cpp
  include/TitaniumWindows/UI/Windows/ViewHelper.hpp
  src/Windows/ViewHelper.cpp
  include/TitaniumWindows/UI/Windows/ListViewScrollPosition.hpp
  src/Windows/ListViewScrollPosition.cpp
  )

source_group(Titanium\\UI\\Windows FILES ${SOURCE_UI_Windows})

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

add_library(TitaniumWindows_UI SHARED
  ${SOURCE_UI}
  ${SOURCE_UI_Windows}
  )

include(GenerateExportHeader)
generate_export_header(TitaniumWindows_UI)
target_compile_definitions(TitaniumWindows_UI PRIVATE TitaniumWindows_UI_EXPORTS)

target_include_directories(TitaniumWindows_UI PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  $<TARGET_PROPERTY:TitaniumKit,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows_Utility,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:LayoutEngine,INTERFACE_INCLUDE_DIRECTORIES>
  )

target_link_libraries(TitaniumWindows_UI
  TitaniumKit
  LayoutEngine
  TitaniumWindows_Utility
  )

set_target_properties(TitaniumWindows_UI PROPERTIES VS_WINRT_COMPONENT TRUE)

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
set_property(TARGET TitaniumWindows_UI APPEND_STRING PROPERTY LINK_FLAGS_DEBUG "/OPT:NOREF /OPT:NOICF")

# Fix error C4996: 'std::_Copy_impl': Function call with parameters that may be unsafe (needed by boost::split)
set_property(TARGET TitaniumWindows_UI APPEND_STRING PROPERTY COMPILE_FLAGS " -D_SCL_SECURE_NO_WARNINGS")

if (NOT TitaniumWindows_UI_DISABLE_TESTS)
  add_subdirectory(test)
endif()


# Support find_package(TitaniumWindows_UI 0.1 REQUIRED)

set_property(TARGET TitaniumWindows_UI PROPERTY VERSION ${TitaniumWindows_UI_VERSION})
set_property(TARGET TitaniumWindows_UI PROPERTY SOVERSION 0)
set_property(TARGET TitaniumWindows_UI PROPERTY INTERFACE_TitaniumWindows_UI_MAJOR_VERSION 0)
set_property(TARGET TitaniumWindows_UI APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING TitaniumWindows_UI_MAJOR_VERSION
  )

install(TARGETS TitaniumWindows_UI EXPORT TitaniumWindows_UI_Targets
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
  )

export(EXPORT TitaniumWindows_UI_Targets
  FILE "${CMAKE_BINARY_DIR}/TitaniumWindows_UI_Targets.cmake"
)

configure_file(cmake/TitaniumWindows_UI_Config.cmake
  "${CMAKE_BINARY_DIR}/TitaniumWindows_UI_Config.cmake"
  COPYONLY
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_BINARY_DIR}/TitaniumWindows_UI_ConfigVersion.cmake"
  VERSION ${TitaniumWindows_UI_VERSION}
  COMPATIBILITY AnyNewerVersion
  )

# Store the current build directory in the CMake user package registry
# so that find_package(TitaniumWindows_UI) works.
export(PACKAGE TitaniumWindows_UI)
