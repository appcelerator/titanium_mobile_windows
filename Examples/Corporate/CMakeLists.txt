# The "NG" App.
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

project(CORPORATE)

set(CORPORATE_VERSION 0.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

get_filename_component(Titanium_SOURCE_DIR    ${PROJECT_SOURCE_DIR}/../../Source/Titanium    ABSOLUTE)
get_filename_component(Global_SOURCE_DIR      ${PROJECT_SOURCE_DIR}/../../Source/Global      ABSOLUTE)
get_filename_component(API_SOURCE_DIR         ${PROJECT_SOURCE_DIR}/../../Source/API         ABSOLUTE)
get_filename_component(UI_SOURCE_DIR          ${PROJECT_SOURCE_DIR}/../../Source/UI          ABSOLUTE)
get_filename_component(TitaniumKit_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../../Source/TitaniumKit ABSOLUTE)
get_filename_component(HAL_SOURCE_DIR         ${PROJECT_SOURCE_DIR}/../../Source/HAL         ABSOLUTE)

if(NOT TARGET TitaniumWindows)
  add_subdirectory(${Titanium_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Titanium EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_Global)
  add_subdirectory(${Global_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Global EXCLUDE_FROM_ALL)
endif()

if(NOT TARGET TitaniumWindows_API)
  add_subdirectory(${API_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/API EXCLUDE_FROM_ALL)
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
  src/Assets/app.js
  src/Assets/Default-568h@2x.png
  src/Assets/Default-Portrait.png
  src/Assets/Default@2x.png
  src/Assets/Icon-Small-50.png
  src/Assets/alloy.js
  src/Assets/appicon-72@2x.png
  src/Assets/iTunesArtwork
  src/Assets/Default-Landscape.png
  src/Assets/Default-Portrait@2x.png
  src/Assets/Icon-50.png
  src/Assets/Icon-Small.png
  src/Assets/appicon.png
  src/Assets/iTunesArtwork@2x
  src/Assets/Default-Landscape@2x.png
  src/Assets/Default.png
  src/Assets/Icon-50@2x.png
  src/Assets/Icon-Small@2x.png
  src/Assets/appicon-72.png
  src/Assets/appicon@2x.png
  src/Assets/utilities.js
  src/Assets/alloy/CFG.js
  src/Assets/alloy/backbone.js
  src/Assets/alloy/constants.js
  src/Assets/alloy/controllers/BaseController.js
  src/Assets/alloy/controllers/directory.js
  src/Assets/alloy/controllers/index.js
  src/Assets/alloy/controllers/profile.js
  src/Assets/alloy/models/Users.js
  src/Assets/alloy/styles/directory.js
  src/Assets/alloy/styles/index.js
  src/Assets/alloy/styles/profile.js
  src/Assets/alloy/sync/localStorage.js
  src/Assets/alloy/sync/properties.js
  src/Assets/alloy/sync/sql.js
  src/Assets/alloy/underscore.js
  src/Assets/alloy/widget.js
  src/Assets/alloy/widgets/net.hoyohoyo.iconiclabel/controllers/widget.js
  src/Assets/alloy/widgets/net.hoyohoyo.iconiclabel/styles/widget.js
  src/Assets/fonts/LigatureSymbols-2.11.ttf
  src/Assets/fonts/fontawesome-webfont.ttf
  src/Assets/fonts/icomoon.ttf
  src/Assets/images/profile-bkg.jpg
  src/Assets/net.hoyohoyo.iconiclabel/FontAwesome-deprecate.js
  src/Assets/net.hoyohoyo.iconiclabel/FontAwesome.js
  src/Assets/net.hoyohoyo.iconiclabel/IconicFont.js
  src/Assets/net.hoyohoyo.iconiclabel/LigatureSymbols-deprecate.js
  src/Assets/net.hoyohoyo.iconiclabel/LigatureSymbols.js
  src/Assets/net.hoyohoyo.iconiclabel/ti.ss-pika.js
  src/Assets/userData/data.json
  src/Assets/Logo.png
  src/Assets/SmallLogo.png
  src/Assets/SplashScreen.png
  src/Assets/StoreLogo.png
  )

set_property(SOURCE ${SOURCE_Assets} PROPERTY VS_DEPLOYMENT_CONTENT 1)

add_executable(${EXE_NAME} WIN32
  src/main.cpp
  src/OutputDebugStringBuf.hpp
  ${SOURCE_Assets}
)

set_target_properties(${EXE_NAME} PROPERTIES VS_WINRT_COMPONENT TRUE)
target_link_libraries(${EXE_NAME} TitaniumWindows)

target_include_directories(${EXE_NAME} PUBLIC
  $<TARGET_PROPERTY:TitaniumWindows,INTERFACE_INCLUDE_DIRECTORIES>
  )
