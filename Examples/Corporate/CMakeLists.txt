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
  ${SQLite_LIBRARIES_DLL}
  "src/Assets/alloy.js"
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
  "src/Assets/iTunesArtwork"
  "src/Assets/iTunesArtwork@2x"
  "src/Assets/Logo.png"
  "src/Assets/SmallLogo.png"
  "src/Assets/SplashScreen.png"
  "src/Assets/StoreLogo.png"
  )
set_property(SOURCE ${SOURCE_Assets} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy
      "src/Assets/alloy/backbone.js"
      "src/Assets/alloy/CFG.js"
      "src/Assets/alloy/constants.js"
      "src/Assets/alloy/underscore.js"
      "src/Assets/alloy/widget.js"
  )
source_group("alloy" FILES 
      "src/Assets/alloy/backbone.js"
      "src/Assets/alloy/CFG.js"
      "src/Assets/alloy/constants.js"
      "src/Assets/alloy/underscore.js"
      "src/Assets/alloy/widget.js"
  )
set_property(SOURCE ${SOURCE_alloy} PROPERTY VS_DEPLOYMENT_LOCATION "alloy")
set_property(SOURCE ${SOURCE_alloy} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_controllers
      "src/Assets/alloy/controllers/BaseController.js"
      "src/Assets/alloy/controllers/directory.js"
      "src/Assets/alloy/controllers/index.js"
      "src/Assets/alloy/controllers/profile.js"
  )
source_group("alloy/controllers" FILES 
      "src/Assets/alloy/controllers/BaseController.js"
      "src/Assets/alloy/controllers/directory.js"
      "src/Assets/alloy/controllers/index.js"
      "src/Assets/alloy/controllers/profile.js"
  )
set_property(SOURCE ${SOURCE_alloy_controllers} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\controllers")
set_property(SOURCE ${SOURCE_alloy_controllers} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_models
      "src/Assets/alloy/models/Users.js"
  )
source_group("alloy/models" FILES 
      "src/Assets/alloy/models/Users.js"
  )
set_property(SOURCE ${SOURCE_alloy_models} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\models")
set_property(SOURCE ${SOURCE_alloy_models} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_styles
      "src/Assets/alloy/styles/directory.js"
      "src/Assets/alloy/styles/index.js"
      "src/Assets/alloy/styles/profile.js"
  )
source_group("alloy/styles" FILES 
      "src/Assets/alloy/styles/directory.js"
      "src/Assets/alloy/styles/index.js"
      "src/Assets/alloy/styles/profile.js"
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

set(SOURCE_alloy_widgets_net.hoyohoyo.iconiclabel_controllers
      "src/Assets/alloy/widgets/net.hoyohoyo.iconiclabel/controllers/widget.js"
  )
source_group("alloy/widgets/net.hoyohoyo.iconiclabel/controllers" FILES 
      "src/Assets/alloy/widgets/net.hoyohoyo.iconiclabel/controllers/widget.js"
  )
set_property(SOURCE ${SOURCE_alloy_widgets_net.hoyohoyo.iconiclabel_controllers} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\widgets\\net.hoyohoyo.iconiclabel\\controllers")
set_property(SOURCE ${SOURCE_alloy_widgets_net.hoyohoyo.iconiclabel_controllers} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_widgets_net.hoyohoyo.iconiclabel_styles
      "src/Assets/alloy/widgets/net.hoyohoyo.iconiclabel/styles/widget.js"
  )
source_group("alloy/widgets/net.hoyohoyo.iconiclabel/styles" FILES 
      "src/Assets/alloy/widgets/net.hoyohoyo.iconiclabel/styles/widget.js"
  )
set_property(SOURCE ${SOURCE_alloy_widgets_net.hoyohoyo.iconiclabel_styles} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\widgets\\net.hoyohoyo.iconiclabel\\styles")
set_property(SOURCE ${SOURCE_alloy_widgets_net.hoyohoyo.iconiclabel_styles} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_fonts
      "src/Assets/fonts/fontawesome-webfont.ttf"
      "src/Assets/fonts/icomoon.ttf"
      "src/Assets/fonts/LigatureSymbols-2.11.ttf"
  )
source_group("fonts" FILES 
      "src/Assets/fonts/fontawesome-webfont.ttf"
      "src/Assets/fonts/icomoon.ttf"
      "src/Assets/fonts/LigatureSymbols-2.11.ttf"
  )
set_property(SOURCE ${SOURCE_fonts} PROPERTY VS_DEPLOYMENT_LOCATION "fonts")
set_property(SOURCE ${SOURCE_fonts} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_images
      "src/Assets/images/profile-bkg.jpg"
  )
source_group("images" FILES 
      "src/Assets/images/profile-bkg.jpg"
  )
set_property(SOURCE ${SOURCE_images} PROPERTY VS_DEPLOYMENT_LOCATION "images")
set_property(SOURCE ${SOURCE_images} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_net.hoyohoyo.iconiclabel
      "src/Assets/net.hoyohoyo.iconiclabel/FontAwesome-deprecate.js"
      "src/Assets/net.hoyohoyo.iconiclabel/FontAwesome.js"
      "src/Assets/net.hoyohoyo.iconiclabel/IconicFont.js"
      "src/Assets/net.hoyohoyo.iconiclabel/LigatureSymbols-deprecate.js"
      "src/Assets/net.hoyohoyo.iconiclabel/LigatureSymbols.js"
      "src/Assets/net.hoyohoyo.iconiclabel/ti.ss-pika.js"
  )
source_group("net.hoyohoyo.iconiclabel" FILES 
      "src/Assets/net.hoyohoyo.iconiclabel/FontAwesome-deprecate.js"
      "src/Assets/net.hoyohoyo.iconiclabel/FontAwesome.js"
      "src/Assets/net.hoyohoyo.iconiclabel/IconicFont.js"
      "src/Assets/net.hoyohoyo.iconiclabel/LigatureSymbols-deprecate.js"
      "src/Assets/net.hoyohoyo.iconiclabel/LigatureSymbols.js"
      "src/Assets/net.hoyohoyo.iconiclabel/ti.ss-pika.js"
  )
set_property(SOURCE ${SOURCE_net.hoyohoyo.iconiclabel} PROPERTY VS_DEPLOYMENT_LOCATION "net.hoyohoyo.iconiclabel")
set_property(SOURCE ${SOURCE_net.hoyohoyo.iconiclabel} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_userData
      "src/Assets/userData/data.json"
  )
source_group("userData" FILES 
      "src/Assets/userData/data.json"
  )
set_property(SOURCE ${SOURCE_userData} PROPERTY VS_DEPLOYMENT_LOCATION "userData")
set_property(SOURCE ${SOURCE_userData} PROPERTY VS_DEPLOYMENT_CONTENT 1)


# Add all the files to the app
add_executable(${EXE_NAME} WIN32
  src/main.cpp
  src/OutputDebugStringBuf.hpp
  ${SOURCE_Assets}
      ${SOURCE_alloy}
    ${SOURCE_alloy_controllers}
    ${SOURCE_alloy_models}
    ${SOURCE_alloy_styles}
    ${SOURCE_alloy_sync}
    ${SOURCE_alloy_widgets_net.hoyohoyo.iconiclabel_controllers}
    ${SOURCE_alloy_widgets_net.hoyohoyo.iconiclabel_styles}
    ${SOURCE_fonts}
    ${SOURCE_images}
    ${SOURCE_net.hoyohoyo.iconiclabel}
    ${SOURCE_userData}
)

set_target_properties(${EXE_NAME} PROPERTIES VS_WINRT_COMPONENT TRUE)
target_link_libraries(${EXE_NAME} TitaniumWindows)

target_include_directories(${EXE_NAME} PUBLIC
  $<TARGET_PROPERTY:TitaniumWindows,INTERFACE_INCLUDE_DIRECTORIES>
  )
