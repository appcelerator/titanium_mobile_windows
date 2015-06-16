# The "Corporate Directory" App.
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

project(Corporate)

set(Corporate_VERSION 0.1.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

# Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

get_filename_component(Titanium_SOURCE_DIR      ${PROJECT_SOURCE_DIR}/../../Source/Titanium      ABSOLUTE)
get_filename_component(Global_SOURCE_DIR        ${PROJECT_SOURCE_DIR}/../../Source/Global        ABSOLUTE)
get_filename_component(Ti_SOURCE_DIR            ${PROJECT_SOURCE_DIR}/../../Source/Ti            ABSOLUTE)
get_filename_component(Sensors_SOURCE_DIR       ${PROJECT_SOURCE_DIR}/../../Source/Sensors       ABSOLUTE)
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
  "src/Assets/utilities.js"
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
      "src/Assets/alloy/controllers/annotation.js"
      "src/Assets/alloy/controllers/BaseController.js"
      "src/Assets/alloy/controllers/directory.js"
      "src/Assets/alloy/controllers/index.js"
      "src/Assets/alloy/controllers/loader.js"
      "src/Assets/alloy/controllers/profile.js"
  )
source_group("alloy/controllers" FILES 
      "src/Assets/alloy/controllers/annotation.js"
      "src/Assets/alloy/controllers/BaseController.js"
      "src/Assets/alloy/controllers/directory.js"
      "src/Assets/alloy/controllers/index.js"
      "src/Assets/alloy/controllers/loader.js"
      "src/Assets/alloy/controllers/profile.js"
  )
set_property(SOURCE ${SOURCE_alloy_controllers} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\controllers")
set_property(SOURCE ${SOURCE_alloy_controllers} PROPERTY VS_DEPLOYMENT_CONTENT 1)

#set(SOURCE_alloy_models
#      "src/Assets/alloy/models/Users.js"
#  )
#source_group("alloy/models" FILES 
#      "src/Assets/alloy/models/Users.js"
#  )
#set_property(SOURCE ${SOURCE_alloy_models} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\models")
#set_property(SOURCE ${SOURCE_alloy_models} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_styles
      "src/Assets/alloy/styles/annotation.js"
      "src/Assets/alloy/styles/directory.js"
      "src/Assets/alloy/styles/index.js"
      "src/Assets/alloy/styles/loader.js"
      "src/Assets/alloy/styles/profile.js"
  )
source_group("alloy/styles" FILES 
      "src/Assets/alloy/styles/annotation.js"
      "src/Assets/alloy/styles/directory.js"
      "src/Assets/alloy/styles/index.js"
      "src/Assets/alloy/styles/loader.js"
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

set(SOURCE_fonts
      "src/Assets/fonts/icomoon.ttf"
      "src/Assets/fonts/icomoon.woff"
  )
source_group("fonts" FILES 
      "src/Assets/fonts/icomoon.ttf"
      "src/Assets/fonts/icomoon.woff"
  )
set_property(SOURCE ${SOURCE_fonts} PROPERTY VS_DEPLOYMENT_LOCATION "fonts")
set_property(SOURCE ${SOURCE_fonts} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_images_RocketFlight
      "src/Assets/images/RocketFlight/RocketFlight01.png"
      "src/Assets/images/RocketFlight/RocketFlight02.png"
      "src/Assets/images/RocketFlight/RocketFlight03.png"
      "src/Assets/images/RocketFlight/RocketFlight04.png"
      "src/Assets/images/RocketFlight/RocketFlight05.png"
      "src/Assets/images/RocketFlight/RocketFlight06.png"
      "src/Assets/images/RocketFlight/RocketFlight07.png"
      "src/Assets/images/RocketFlight/RocketFlight08.png"
      "src/Assets/images/RocketFlight/RocketFlight09.png"
      "src/Assets/images/RocketFlight/RocketFlight10.png"
      "src/Assets/images/RocketFlight/RocketFlight11.png"
      "src/Assets/images/RocketFlight/RocketFlight12.png"
      "src/Assets/images/RocketFlight/RocketFlight13.png"
      "src/Assets/images/RocketFlight/RocketFlight14.png"
      "src/Assets/images/RocketFlight/RocketFlight15.png"
      "src/Assets/images/RocketFlight/RocketFlight16.png"
      "src/Assets/images/RocketFlight/RocketFlight17.png"
      "src/Assets/images/RocketFlight/RocketFlight18.png"
      "src/Assets/images/RocketFlight/RocketFlight19.png"
      "src/Assets/images/RocketFlight/RocketFlight20.png"
      "src/Assets/images/RocketFlight/RocketFlight21.png"
      "src/Assets/images/RocketFlight/RocketFlight22.png"
      "src/Assets/images/RocketFlight/RocketFlight23.png"
      "src/Assets/images/RocketFlight/RocketFlight24.png"
      "src/Assets/images/RocketFlight/RocketFlight25.png"
  )
source_group("images/RocketFlight" FILES 
      "src/Assets/images/RocketFlight/RocketFlight01.png"
      "src/Assets/images/RocketFlight/RocketFlight02.png"
      "src/Assets/images/RocketFlight/RocketFlight03.png"
      "src/Assets/images/RocketFlight/RocketFlight04.png"
      "src/Assets/images/RocketFlight/RocketFlight05.png"
      "src/Assets/images/RocketFlight/RocketFlight06.png"
      "src/Assets/images/RocketFlight/RocketFlight07.png"
      "src/Assets/images/RocketFlight/RocketFlight08.png"
      "src/Assets/images/RocketFlight/RocketFlight09.png"
      "src/Assets/images/RocketFlight/RocketFlight10.png"
      "src/Assets/images/RocketFlight/RocketFlight11.png"
      "src/Assets/images/RocketFlight/RocketFlight12.png"
      "src/Assets/images/RocketFlight/RocketFlight13.png"
      "src/Assets/images/RocketFlight/RocketFlight14.png"
      "src/Assets/images/RocketFlight/RocketFlight15.png"
      "src/Assets/images/RocketFlight/RocketFlight16.png"
      "src/Assets/images/RocketFlight/RocketFlight17.png"
      "src/Assets/images/RocketFlight/RocketFlight18.png"
      "src/Assets/images/RocketFlight/RocketFlight19.png"
      "src/Assets/images/RocketFlight/RocketFlight20.png"
      "src/Assets/images/RocketFlight/RocketFlight21.png"
      "src/Assets/images/RocketFlight/RocketFlight22.png"
      "src/Assets/images/RocketFlight/RocketFlight23.png"
      "src/Assets/images/RocketFlight/RocketFlight24.png"
      "src/Assets/images/RocketFlight/RocketFlight25.png"
  )
set_property(SOURCE ${SOURCE_images_RocketFlight} PROPERTY VS_DEPLOYMENT_LOCATION "images\\RocketFlight")
set_property(SOURCE ${SOURCE_images_RocketFlight} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_images_RocketSmoke
      "src/Assets/images/RocketSmoke/RocketSmoke01.png"
      "src/Assets/images/RocketSmoke/RocketSmoke02.png"
      "src/Assets/images/RocketSmoke/RocketSmoke03.png"
      "src/Assets/images/RocketSmoke/RocketSmoke04.png"
      "src/Assets/images/RocketSmoke/RocketSmoke05.png"
      "src/Assets/images/RocketSmoke/RocketSmoke06.png"
      "src/Assets/images/RocketSmoke/RocketSmoke07.png"
      "src/Assets/images/RocketSmoke/RocketSmoke08.png"
      "src/Assets/images/RocketSmoke/RocketSmoke09.png"
      "src/Assets/images/RocketSmoke/RocketSmoke10.png"
      "src/Assets/images/RocketSmoke/RocketSmoke11.png"
      "src/Assets/images/RocketSmoke/RocketSmoke12.png"
      "src/Assets/images/RocketSmoke/RocketSmoke13.png"
      "src/Assets/images/RocketSmoke/RocketSmoke14.png"
      "src/Assets/images/RocketSmoke/RocketSmoke15.png"
      "src/Assets/images/RocketSmoke/RocketSmoke16.png"
      "src/Assets/images/RocketSmoke/RocketSmoke17.png"
      "src/Assets/images/RocketSmoke/RocketSmoke18.png"
      "src/Assets/images/RocketSmoke/RocketSmoke19.png"
      "src/Assets/images/RocketSmoke/RocketSmoke20.png"
      "src/Assets/images/RocketSmoke/RocketSmoke21.png"
      "src/Assets/images/RocketSmoke/RocketSmoke22.png"
      "src/Assets/images/RocketSmoke/RocketSmoke23.png"
      "src/Assets/images/RocketSmoke/RocketSmoke24.png"
      "src/Assets/images/RocketSmoke/RocketSmoke25.png"
      "src/Assets/images/RocketSmoke/RocketSmoke26.png"
      "src/Assets/images/RocketSmoke/RocketSmoke27.png"
      "src/Assets/images/RocketSmoke/RocketSmoke28.png"
      "src/Assets/images/RocketSmoke/RocketSmoke29.png"
      "src/Assets/images/RocketSmoke/RocketSmoke30.png"
      "src/Assets/images/RocketSmoke/RocketSmoke31.png"
      "src/Assets/images/RocketSmoke/RocketSmoke32.png"
      "src/Assets/images/RocketSmoke/RocketSmoke33.png"
      "src/Assets/images/RocketSmoke/RocketSmoke34.png"
      "src/Assets/images/RocketSmoke/RocketSmoke35.png"
      "src/Assets/images/RocketSmoke/RocketSmoke36.png"
      "src/Assets/images/RocketSmoke/RocketSmoke37.png"
  )
source_group("images/RocketSmoke" FILES 
      "src/Assets/images/RocketSmoke/RocketSmoke01.png"
      "src/Assets/images/RocketSmoke/RocketSmoke02.png"
      "src/Assets/images/RocketSmoke/RocketSmoke03.png"
      "src/Assets/images/RocketSmoke/RocketSmoke04.png"
      "src/Assets/images/RocketSmoke/RocketSmoke05.png"
      "src/Assets/images/RocketSmoke/RocketSmoke06.png"
      "src/Assets/images/RocketSmoke/RocketSmoke07.png"
      "src/Assets/images/RocketSmoke/RocketSmoke08.png"
      "src/Assets/images/RocketSmoke/RocketSmoke09.png"
      "src/Assets/images/RocketSmoke/RocketSmoke10.png"
      "src/Assets/images/RocketSmoke/RocketSmoke11.png"
      "src/Assets/images/RocketSmoke/RocketSmoke12.png"
      "src/Assets/images/RocketSmoke/RocketSmoke13.png"
      "src/Assets/images/RocketSmoke/RocketSmoke14.png"
      "src/Assets/images/RocketSmoke/RocketSmoke15.png"
      "src/Assets/images/RocketSmoke/RocketSmoke16.png"
      "src/Assets/images/RocketSmoke/RocketSmoke17.png"
      "src/Assets/images/RocketSmoke/RocketSmoke18.png"
      "src/Assets/images/RocketSmoke/RocketSmoke19.png"
      "src/Assets/images/RocketSmoke/RocketSmoke20.png"
      "src/Assets/images/RocketSmoke/RocketSmoke21.png"
      "src/Assets/images/RocketSmoke/RocketSmoke22.png"
      "src/Assets/images/RocketSmoke/RocketSmoke23.png"
      "src/Assets/images/RocketSmoke/RocketSmoke24.png"
      "src/Assets/images/RocketSmoke/RocketSmoke25.png"
      "src/Assets/images/RocketSmoke/RocketSmoke26.png"
      "src/Assets/images/RocketSmoke/RocketSmoke27.png"
      "src/Assets/images/RocketSmoke/RocketSmoke28.png"
      "src/Assets/images/RocketSmoke/RocketSmoke29.png"
      "src/Assets/images/RocketSmoke/RocketSmoke30.png"
      "src/Assets/images/RocketSmoke/RocketSmoke31.png"
      "src/Assets/images/RocketSmoke/RocketSmoke32.png"
      "src/Assets/images/RocketSmoke/RocketSmoke33.png"
      "src/Assets/images/RocketSmoke/RocketSmoke34.png"
      "src/Assets/images/RocketSmoke/RocketSmoke35.png"
      "src/Assets/images/RocketSmoke/RocketSmoke36.png"
      "src/Assets/images/RocketSmoke/RocketSmoke37.png"
  )
set_property(SOURCE ${SOURCE_images_RocketSmoke} PROPERTY VS_DEPLOYMENT_LOCATION "images\\RocketSmoke")
set_property(SOURCE ${SOURCE_images_RocketSmoke} PROPERTY VS_DEPLOYMENT_CONTENT 1)

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
    ${SOURCE_alloy_styles}
    ${SOURCE_alloy_sync}
    ${SOURCE_fonts}
    ${SOURCE_images_RocketFlight}
    ${SOURCE_images_RocketSmoke}
    ${SOURCE_userData}
)

set_target_properties(${EXE_NAME} PROPERTIES VS_WINRT_COMPONENT TRUE)
target_link_libraries(${EXE_NAME} TitaniumWindows)

target_include_directories(${EXE_NAME} PUBLIC
  $<TARGET_PROPERTY:TitaniumWindows,INTERFACE_INCLUDE_DIRECTORIES>
  )
