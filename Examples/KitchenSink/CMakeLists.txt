# The "KitchenSink" App.
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

project(KitchenSink)

set(KitchenSink_VERSION 0.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

get_filename_component(Titanium_SOURCE_DIR      ${PROJECT_SOURCE_DIR}/../../Source/Titanium      ABSOLUTE)
get_filename_component(Global_SOURCE_DIR        ${PROJECT_SOURCE_DIR}/../../Source/Global        ABSOLUTE)
get_filename_component(Ti_SOURCE_DIR            ${PROJECT_SOURCE_DIR}/../../Source/Ti            ABSOLUTE)
get_filename_component(Sensors_SOURCE_DIR       ${PROJECT_SOURCE_DIR}/../../Source/Sensors       ABSOLUTE)
get_filename_component(Map_SOURCE_DIR           ${PROJECT_SOURCE_DIR}/../../Source/Map           ABSOLUTE)
get_filename_component(Media_SOURCE_DIR         ${PROJECT_SOURCE_DIR}/../../Source/Media         ABSOLUTE)
get_filename_component(Network_SOURCE_DIR       ${PROJECT_SOURCE_DIR}/../../Source/Network       ABSOLUTE)
get_filename_component(Filesystem_SOURCE_DIR    ${PROJECT_SOURCE_DIR}/../../Source/Filesystem    ABSOLUTE)
get_filename_component(Utility_SOURCE_DIR       ${PROJECT_SOURCE_DIR}/../../Source/Utility       ABSOLUTE)
get_filename_component(UI_SOURCE_DIR            ${PROJECT_SOURCE_DIR}/../../Source/UI            ABSOLUTE)
get_filename_component(TitaniumKit_SOURCE_DIR   ${PROJECT_SOURCE_DIR}/../../Source/TitaniumKit   ABSOLUTE)
get_filename_component(HAL_SOURCE_DIR           ${PROJECT_SOURCE_DIR}/../../Source/HAL           ABSOLUTE)

if(NOT TARGET TitaniumWindows)
  add_subdirectory(${Titanium_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Titanium EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_Global)
  add_subdirectory(${Global_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Global EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_Ti)
  add_subdirectory(${Ti_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Ti EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_Sensors)
  add_subdirectory(${Sensors_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Sensors EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_Map)
  add_subdirectory(${Map_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Map EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_Media)
  add_subdirectory(${Media_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Media EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_Network)
  add_subdirectory(${Network_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Network EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_Filesystem)
  add_subdirectory(${Filesystem_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Filesystem EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_Utility)
  add_subdirectory(${Utility_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Utility EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_UI)
  add_subdirectory(${UI_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/UI EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumKit)
  add_subdirectory(${TitaniumKit_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/TitaniumKit EXCLUDE_FROM_ALL)
endif()

if (NOT TARGET HAL)
  add_subdirectory(${HAL_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/HAL EXCLUDE_FROM_ALL)
endif()

# No user-servicable parts below this line.

# Variable naming the built executable.
set(EXE_NAME ${PROJECT_NAME})

# Variables required to generate the app manifest.
set(APP_MANIFEST_NAME Package.appxmanifest)
set(SHORT_NAME ${EXE_NAME})
set(PACKAGE_GUID "f0473be1-c557-4f98-a103-4ba9f453b5b0")

# Generate the app manifest.
configure_file(
  src/Package.${PLATFORM}.appxmanifest.in
  ${CMAKE_CURRENT_BINARY_DIR}/${APP_MANIFEST_NAME}
  @ONLY)

set(SOURCE_Assets
  ${CMAKE_CURRENT_BINARY_DIR}/${APP_MANIFEST_NAME}
  "src/Assets/app.js"
  "src/Assets/appicon-72.png"
  "src/Assets/appicon-72@2x.png"
  "src/Assets/appicon.png"
  "src/Assets/appicon@2x.png"
  "src/Assets/Default-568h@2x.png"
  "src/Assets/Default-Landscape.png"
  "src/Assets/Default-Landscape@2x.png"
  "src/Assets/Default-Portrait.png"
  "src/Assets/Default-Portrait@2x.png"
  "src/Assets/Default.png"
  "src/Assets/Default@2x.png"
  "src/Assets/Icon-50.png"
  "src/Assets/Icon-50@2x.png"
  "src/Assets/Icon-Small-50.png"
  "src/Assets/Icon-Small.png"
  "src/Assets/Icon-Small@2x.png"
  "src/Assets/Logo.png"
  "src/Assets/SmallLogo.png"
  "src/Assets/SplashScreen.png"
  "src/Assets/StoreLogo.png"
  )
set_property(SOURCE ${SOURCE_Assets} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_ui_common
      "src/Assets/ui/common/ApplicationTabGroup.js"
      "src/Assets/ui/common/MessageWindow.js"
  )
source_group("ui/common" FILES 
      "src/Assets/ui/common/ApplicationTabGroup.js"
      "src/Assets/ui/common/MessageWindow.js"
  )
set_property(SOURCE ${SOURCE_ui_common} PROPERTY VS_DEPLOYMENT_LOCATION "ui\\common")
set_property(SOURCE ${SOURCE_ui_common} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_ui_handheld_windows
      "src/Assets/ui/handheld/windows/ApplicationWindow.js"
  )
source_group("ui/handheld/windows" FILES 
      "src/Assets/ui/handheld/windows/ApplicationWindow.js"
  )
set_property(SOURCE ${SOURCE_ui_handheld_windows} PROPERTY VS_DEPLOYMENT_LOCATION "ui\\handheld\\windows")
set_property(SOURCE ${SOURCE_ui_handheld_windows} PROPERTY VS_DEPLOYMENT_CONTENT 1)

# Add all the files to the app
add_executable(${EXE_NAME} WIN32
  src/main.cpp
  src/OutputDebugStringBuf.hpp
  ${SOURCE_Assets}
  ${SOURCE_ui_common}
  ${SOURCE_ui_handheld_windows}
)

set_target_properties(${EXE_NAME} PROPERTIES VS_WINRT_COMPONENT TRUE)
target_link_libraries(${EXE_NAME} TitaniumWindows)

target_include_directories(${EXE_NAME} PUBLIC
  $<TARGET_PROPERTY:TitaniumWindows,INTERFACE_INCLUDE_DIRECTORIES>
  )
