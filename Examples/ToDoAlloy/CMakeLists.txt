# The ToDO List Alloy App.
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.
cmake_minimum_required(VERSION 3.0.0)

if (${CMAKE_SYSTEM_VERSION} STREQUAL "10.0")
  set(PLATFORM win10)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsPhone")
  set(PLATFORM wp)
  add_definitions("-DPHONE")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore")
  set(PLATFORM store)
else()
  message(FATAL_ERROR "This app supports Store / Phone only.")
endif()

project(ToDoAlloy)

set(ToDoAlloy_VERSION 0.1.0)

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
set(PUBLISHER_ID "CN=appcelerator")
set(PUBLISHER_DISPLAY_NAME "Appcelerator")
set(PHONE_PRODUCT_ID "f0473be1-c557-4f98-a103-4ba9f453b5b0")
set(PHONE_PUBLISHER_ID "00000000-0000-0000-0000-000000000000")
set(VERSION "1.1.0.0")

# Generate the app manifest.
configure_file(
  src/Package.${PLATFORM}.appxmanifest.in
  ${CMAKE_CURRENT_BINARY_DIR}/${APP_MANIFEST_NAME}
  @ONLY)

set(SOURCE_Assets
  ${CMAKE_CURRENT_BINARY_DIR}/${APP_MANIFEST_NAME}
  "src/Assets/alloy.js"
  "src/Assets/app.js"
  "src/Assets/Logo.png"
  "src/Assets/SmallLogo.png"
  "src/Assets/SplashScreen.png"
  "src/Assets/SplashScreen.scale-240.png"
  "src/Assets/SplashScreen480x800.png"
  "src/Assets/Square44x44Logo.png"
  "src/Assets/Square71x71Logo.png"
  "src/Assets/Square150x150Logo.png"
  "src/Assets/StoreLogo.png"
  "src/Assets/ic_menu_add.png"
  "src/Assets/red_x.png"
  "src/Assets/tick_64.png"
  "src/Assets/tick_gray_64.png"
  "src/Assets/_app_info_.json"
  "src/Assets/_app_props_.json"
  )
set_property(SOURCE ${SOURCE_Assets} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy
      "src/Assets/alloy/backbone.js"
      "src/Assets/alloy/CFG.js"
      "src/Assets/alloy/constants.js"
      "src/Assets/alloy/underscore.js"
      "src/Assets/alloy/widget.js"
      "src/Assets/alloy/moment.js"
  )
source_group("alloy" FILES
      "src/Assets/alloy/backbone.js"
      "src/Assets/alloy/CFG.js"
      "src/Assets/alloy/constants.js"
      "src/Assets/alloy/underscore.js"
      "src/Assets/alloy/widget.js"
      "src/Assets/alloy/moment.js"
  )
set_property(SOURCE ${SOURCE_alloy} PROPERTY VS_DEPLOYMENT_LOCATION "alloy")
set_property(SOURCE ${SOURCE_alloy} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_controllers
      "src/Assets/alloy/controllers/BaseController.js"
      "src/Assets/alloy/controllers/index.js"
      "src/Assets/alloy/controllers/add.js"
      "src/Assets/alloy/controllers/row.js"
  )
source_group("alloy/controllers" FILES
      "src/Assets/alloy/controllers/BaseController.js"
      "src/Assets/alloy/controllers/index.js"
      "src/Assets/alloy/controllers/add.js"
      "src/Assets/alloy/controllers/row.js"
  )
set_property(SOURCE ${SOURCE_alloy_controllers} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\controllers")
set_property(SOURCE ${SOURCE_alloy_controllers} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_models
      "src/Assets/alloy/models/ToDo.js"
  )
source_group("alloy/models" FILES
      "src/Assets/alloy/models/ToDo.js"
  )
set_property(SOURCE ${SOURCE_alloy_models} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\models")
set_property(SOURCE ${SOURCE_alloy_models} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_styles
      "src/Assets/alloy/styles/index.js"
      "src/Assets/alloy/styles/add.js"
      "src/Assets/alloy/styles/row.js"
  )
source_group("alloy/styles" FILES
      "src/Assets/alloy/styles/index.js"
      "src/Assets/alloy/styles/add.js"
      "src/Assets/alloy/styles/row.js"
  )
set_property(SOURCE ${SOURCE_alloy_styles} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\styles")
set_property(SOURCE ${SOURCE_alloy_styles} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_sync
      "src/Assets/alloy/sync/localStorage.js"
      "src/Assets/alloy/sync/properties.js"
      "src/Assets/alloy/sync/sql.js"
  )
source_group("alloy/sync" FILES
      "src/Assets/alloy/sync/localStorage.js"
      "src/Assets/alloy/sync/properties.js"
      "src/Assets/alloy/sync/sql.js"
  )
set_property(SOURCE ${SOURCE_alloy_sync} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\sync")
set_property(SOURCE ${SOURCE_alloy_sync} PROPERTY VS_DEPLOYMENT_CONTENT 1)

# Add all the files to the app
add_executable(${EXE_NAME} WIN32
  src/main.cpp
  src/OutputDebugStringBuf.hpp
  ${SOURCE_Assets}
    ${SOURCE_alloy}
    ${SOURCE_alloy_controllers}
    ${SOURCE_alloy_styles}
    ${SOURCE_alloy_sync}
    ${SOURCE_alloy_models}
)

set_target_properties(${EXE_NAME} PROPERTIES VS_WINRT_COMPONENT TRUE)
target_link_libraries(${EXE_NAME} TitaniumWindows)

target_include_directories(${EXE_NAME} PUBLIC
  $<TARGET_PROPERTY:TitaniumWindows,INTERFACE_INCLUDE_DIRECTORIES>
  )
