# The KitchenSink Alloy App.
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

project(kitchensink-v2)

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
get_filename_component(Ti_CMAKE_MODULE_DIR      ${PROJECT_SOURCE_DIR}/../../Source/cmake         ABSOLUTE)

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

list(INSERT CMAKE_MODULE_PATH 0 ${Ti_CMAKE_MODULE_DIR})
find_package(JavaScriptCore REQUIRED)

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
  "src/Assets/appicon.png"
  "src/Assets/log.js"
  "src/Assets/Logo.png"
  "src/Assets/SmallLogo.png"
  "src/Assets/SplashScreen.png"
  "src/Assets/SplashScreen480x800.png"
  "src/Assets/Square150x150Logo.png"
  "src/Assets/Square24x24Logo.png"
  "src/Assets/Square44x44Logo.png"
  "src/Assets/Square71x71Logo.png"
  "src/Assets/StoreLogo.png"
  "src/Assets/titanium_settings.ini"
  "src/Assets/_app_info_.json"
  "src/Assets/_app_props_.json"
  ${JavaScriptCore_LIBRARY_DIR}/Release/JavaScriptCore.dll
  ${JavaScriptCore_LIBRARY_DIR}/Release/WTF.dll
  )
set_property(SOURCE ${SOURCE_Assets} PROPERTY VS_DEPLOYMENT_CONTENT 1)


set(SOURCE_alloy
      "src/Assets/alloy/backbone.js"
      "src/Assets/alloy/CFG.js"
      "src/Assets/alloy/constants.js"
      "src/Assets/alloy/moment.js"
      "src/Assets/alloy/underscore.js"
      "src/Assets/alloy/widget.js"
  )
source_group("alloy" FILES
      "src/Assets/alloy/backbone.js"
      "src/Assets/alloy/CFG.js"
      "src/Assets/alloy/constants.js"
      "src/Assets/alloy/moment.js"
      "src/Assets/alloy/underscore.js"
      "src/Assets/alloy/widget.js"
  )
set_property(SOURCE ${SOURCE_alloy} PROPERTY VS_DEPLOYMENT_LOCATION "alloy")
set_property(SOURCE ${SOURCE_alloy} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_controllers
      "src/Assets/alloy/controllers/BaseController.js"
      "src/Assets/alloy/controllers/index.js"
  )
source_group("alloy/controllers" FILES
      "src/Assets/alloy/controllers/BaseController.js"
      "src/Assets/alloy/controllers/index.js"
  )
set_property(SOURCE ${SOURCE_alloy_controllers} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\controllers")
set_property(SOURCE ${SOURCE_alloy_controllers} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_controllers_console
      "src/Assets/alloy/controllers/console/index.js"
  )
source_group("alloy/controllers/console" FILES
      "src/Assets/alloy/controllers/console/index.js"
  )
set_property(SOURCE ${SOURCE_alloy_controllers_console} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\controllers\\console")
set_property(SOURCE ${SOURCE_alloy_controllers_console} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_controllers_controls
      "src/Assets/alloy/controllers/controls/activityindicator.js"
      "src/Assets/alloy/controllers/controls/alertdialog.js"
      "src/Assets/alloy/controllers/controls/index.js"
      "src/Assets/alloy/controllers/controls/label.js"
      "src/Assets/alloy/controllers/controls/optiondialog.js"
      "src/Assets/alloy/controllers/controls/picker.js"
      "src/Assets/alloy/controllers/controls/slider.js"
      "src/Assets/alloy/controllers/controls/stepper.js"
      "src/Assets/alloy/controllers/controls/switchcontrol.js"
      "src/Assets/alloy/controllers/controls/tabbedbar.js"
      "src/Assets/alloy/controllers/controls/textarea.js"
      "src/Assets/alloy/controllers/controls/textfield.js"
  )
source_group("alloy/controllers/controls" FILES
      "src/Assets/alloy/controllers/controls/activityindicator.js"
      "src/Assets/alloy/controllers/controls/alertdialog.js"
      "src/Assets/alloy/controllers/controls/index.js"
      "src/Assets/alloy/controllers/controls/label.js"
      "src/Assets/alloy/controllers/controls/optiondialog.js"
      "src/Assets/alloy/controllers/controls/picker.js"
      "src/Assets/alloy/controllers/controls/slider.js"
      "src/Assets/alloy/controllers/controls/stepper.js"
      "src/Assets/alloy/controllers/controls/switchcontrol.js"
      "src/Assets/alloy/controllers/controls/tabbedbar.js"
      "src/Assets/alloy/controllers/controls/textarea.js"
      "src/Assets/alloy/controllers/controls/textfield.js"
  )
set_property(SOURCE ${SOURCE_alloy_controllers_controls} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\controllers\\controls")
set_property(SOURCE ${SOURCE_alloy_controllers_controls} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_controllers_controls_views
      "src/Assets/alloy/controllers/controls/views/blurview.js"
      "src/Assets/alloy/controllers/controls/views/imageview.js"
      "src/Assets/alloy/controllers/controls/views/index.js"
      "src/Assets/alloy/controllers/controls/views/listview.js"
      "src/Assets/alloy/controllers/controls/views/scrollableview.js"
      "src/Assets/alloy/controllers/controls/views/scrollview.js"
      "src/Assets/alloy/controllers/controls/views/view.js"
      "src/Assets/alloy/controllers/controls/views/webview.js"
  )
source_group("alloy/controllers/controls/views" FILES
      "src/Assets/alloy/controllers/controls/views/blurview.js"
      "src/Assets/alloy/controllers/controls/views/imageview.js"
      "src/Assets/alloy/controllers/controls/views/index.js"
      "src/Assets/alloy/controllers/controls/views/listview.js"
      "src/Assets/alloy/controllers/controls/views/scrollableview.js"
      "src/Assets/alloy/controllers/controls/views/scrollview.js"
      "src/Assets/alloy/controllers/controls/views/view.js"
      "src/Assets/alloy/controllers/controls/views/webview.js"
  )
set_property(SOURCE ${SOURCE_alloy_controllers_controls_views} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\controllers\\controls\\views")
set_property(SOURCE ${SOURCE_alloy_controllers_controls_views} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_controllers_mashups
      "src/Assets/alloy/controllers/mashups/index.js"
      "src/Assets/alloy/controllers/mashups/twitter.js"
  )
source_group("alloy/controllers/mashups" FILES
      "src/Assets/alloy/controllers/mashups/index.js"
      "src/Assets/alloy/controllers/mashups/twitter.js"
  )
set_property(SOURCE ${SOURCE_alloy_controllers_mashups} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\controllers\\mashups")
set_property(SOURCE ${SOURCE_alloy_controllers_mashups} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_controllers_phone
      "src/Assets/alloy/controllers/phone/index.js"
      "src/Assets/alloy/controllers/phone/peekAndPop.js"
      "src/Assets/alloy/controllers/phone/shortcutItems.js"
      "src/Assets/alloy/controllers/phone/sound.js"
      "src/Assets/alloy/controllers/phone/soundLocal.js"
      "src/Assets/alloy/controllers/phone/soundRemote.js"
      "src/Assets/alloy/controllers/phone/soundRemoteStreaming.js"
  )
source_group("alloy/controllers/phone" FILES
      "src/Assets/alloy/controllers/phone/index.js"
      "src/Assets/alloy/controllers/phone/peekAndPop.js"
      "src/Assets/alloy/controllers/phone/shortcutItems.js"
      "src/Assets/alloy/controllers/phone/sound.js"
      "src/Assets/alloy/controllers/phone/soundLocal.js"
      "src/Assets/alloy/controllers/phone/soundRemote.js"
      "src/Assets/alloy/controllers/phone/soundRemoteStreaming.js"
  )
set_property(SOURCE ${SOURCE_alloy_controllers_phone} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\controllers\\phone")
set_property(SOURCE ${SOURCE_alloy_controllers_phone} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_controllers_platform
      "src/Assets/alloy/controllers/platform/index.js"
      "src/Assets/alloy/controllers/platform/network.js"
  )
source_group("alloy/controllers/platform" FILES
      "src/Assets/alloy/controllers/platform/index.js"
      "src/Assets/alloy/controllers/platform/network.js"
  )
set_property(SOURCE ${SOURCE_alloy_controllers_platform} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\controllers\\platform")
set_property(SOURCE ${SOURCE_alloy_controllers_platform} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_moment_lang
      "src/Assets/alloy/moment/lang/de-at.js"
      "src/Assets/alloy/moment/lang/de.js"
      "src/Assets/alloy/moment/lang/en-au.js"
      "src/Assets/alloy/moment/lang/en-ca.js"
      "src/Assets/alloy/moment/lang/en-gb.js"
  )
source_group("alloy/moment/lang" FILES
      "src/Assets/alloy/moment/lang/de-at.js"
      "src/Assets/alloy/moment/lang/de.js"
      "src/Assets/alloy/moment/lang/en-au.js"
      "src/Assets/alloy/moment/lang/en-ca.js"
      "src/Assets/alloy/moment/lang/en-gb.js"
  )
set_property(SOURCE ${SOURCE_alloy_moment_lang} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\moment\\lang")
set_property(SOURCE ${SOURCE_alloy_moment_lang} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_styles_console
      "src/Assets/alloy/styles/console/index.js"
  )
source_group("alloy/styles/console" FILES
      "src/Assets/alloy/styles/console/index.js"
  )
set_property(SOURCE ${SOURCE_alloy_styles_console} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\styles\\console")
set_property(SOURCE ${SOURCE_alloy_styles_console} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_styles_controls
      "src/Assets/alloy/styles/controls/activityindicator.js"
      "src/Assets/alloy/styles/controls/alertdialog.js"
      "src/Assets/alloy/styles/controls/index.js"
      "src/Assets/alloy/styles/controls/label.js"
      "src/Assets/alloy/styles/controls/optiondialog.js"
      "src/Assets/alloy/styles/controls/picker.js"
      "src/Assets/alloy/styles/controls/slider.js"
      "src/Assets/alloy/styles/controls/stepper.js"
      "src/Assets/alloy/styles/controls/switchcontrol.js"
      "src/Assets/alloy/styles/controls/tabbedbar.js"
      "src/Assets/alloy/styles/controls/textarea.js"
      "src/Assets/alloy/styles/controls/textfield.js"
  )
source_group("alloy/styles/controls" FILES
      "src/Assets/alloy/styles/controls/activityindicator.js"
      "src/Assets/alloy/styles/controls/alertdialog.js"
      "src/Assets/alloy/styles/controls/index.js"
      "src/Assets/alloy/styles/controls/label.js"
      "src/Assets/alloy/styles/controls/optiondialog.js"
      "src/Assets/alloy/styles/controls/picker.js"
      "src/Assets/alloy/styles/controls/slider.js"
      "src/Assets/alloy/styles/controls/stepper.js"
      "src/Assets/alloy/styles/controls/switchcontrol.js"
      "src/Assets/alloy/styles/controls/tabbedbar.js"
      "src/Assets/alloy/styles/controls/textarea.js"
      "src/Assets/alloy/styles/controls/textfield.js"
  )
set_property(SOURCE ${SOURCE_alloy_styles_controls} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\styles\\controls")
set_property(SOURCE ${SOURCE_alloy_styles_controls} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_styles_controls_views
      "src/Assets/alloy/styles/controls/views/blurview.js"
      "src/Assets/alloy/styles/controls/views/imageview.js"
      "src/Assets/alloy/styles/controls/views/index.js"
      "src/Assets/alloy/styles/controls/views/listview.js"
      "src/Assets/alloy/styles/controls/views/scrollableview.js"
      "src/Assets/alloy/styles/controls/views/scrollview.js"
      "src/Assets/alloy/styles/controls/views/view.js"
      "src/Assets/alloy/styles/controls/views/webview.js"
  )
source_group("alloy/styles/controls/views" FILES
      "src/Assets/alloy/styles/controls/views/blurview.js"
      "src/Assets/alloy/styles/controls/views/imageview.js"
      "src/Assets/alloy/styles/controls/views/index.js"
      "src/Assets/alloy/styles/controls/views/listview.js"
      "src/Assets/alloy/styles/controls/views/scrollableview.js"
      "src/Assets/alloy/styles/controls/views/scrollview.js"
      "src/Assets/alloy/styles/controls/views/view.js"
      "src/Assets/alloy/styles/controls/views/webview.js"
  )
set_property(SOURCE ${SOURCE_alloy_styles_controls_views} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\styles\\controls\\views")
set_property(SOURCE ${SOURCE_alloy_styles_controls_views} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_styles
      "src/Assets/alloy/styles/index.js"
  )
source_group("alloy/styles" FILES
      "src/Assets/alloy/styles/index.js"
  )
set_property(SOURCE ${SOURCE_alloy_styles} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\styles")
set_property(SOURCE ${SOURCE_alloy_styles} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_styles_mashups
      "src/Assets/alloy/styles/mashups/index.js"
      "src/Assets/alloy/styles/mashups/twitter.js"
  )
source_group("alloy/styles/mashups" FILES
      "src/Assets/alloy/styles/mashups/index.js"
      "src/Assets/alloy/styles/mashups/twitter.js"
  )
set_property(SOURCE ${SOURCE_alloy_styles_mashups} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\styles\\mashups")
set_property(SOURCE ${SOURCE_alloy_styles_mashups} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_styles_phone
      "src/Assets/alloy/styles/phone/index.js"
      "src/Assets/alloy/styles/phone/peekAndPop.js"
      "src/Assets/alloy/styles/phone/shortcutItems.js"
      "src/Assets/alloy/styles/phone/sound.js"
      "src/Assets/alloy/styles/phone/soundLocal.js"
      "src/Assets/alloy/styles/phone/soundRemote.js"
      "src/Assets/alloy/styles/phone/soundRemoteStreaming.js"
  )
source_group("alloy/styles/phone" FILES
      "src/Assets/alloy/styles/phone/index.js"
      "src/Assets/alloy/styles/phone/peekAndPop.js"
      "src/Assets/alloy/styles/phone/shortcutItems.js"
      "src/Assets/alloy/styles/phone/sound.js"
      "src/Assets/alloy/styles/phone/soundLocal.js"
      "src/Assets/alloy/styles/phone/soundRemote.js"
      "src/Assets/alloy/styles/phone/soundRemoteStreaming.js"
  )
set_property(SOURCE ${SOURCE_alloy_styles_phone} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\styles\\phone")
set_property(SOURCE ${SOURCE_alloy_styles_phone} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_alloy_styles_platform
      "src/Assets/alloy/styles/platform/index.js"
      "src/Assets/alloy/styles/platform/network.js"
  )
source_group("alloy/styles/platform" FILES
      "src/Assets/alloy/styles/platform/index.js"
      "src/Assets/alloy/styles/platform/network.js"
  )
set_property(SOURCE ${SOURCE_alloy_styles_platform} PROPERTY VS_DEPLOYMENT_LOCATION "alloy\\styles\\platform")
set_property(SOURCE ${SOURCE_alloy_styles_platform} PROPERTY VS_DEPLOYMENT_CONTENT 1)

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


set(SOURCE_images_icons
      "src/Assets/images/icons/console.png"
      "src/Assets/images/icons/console@2x.png"
      "src/Assets/images/icons/console@3x.png"
      "src/Assets/images/icons/controls.png"
      "src/Assets/images/icons/controls@2x.png"
      "src/Assets/images/icons/controls@3x.png"
      "src/Assets/images/icons/mashups.png"
      "src/Assets/images/icons/mashups@2x.png"
      "src/Assets/images/icons/mashups@3x.png"
      "src/Assets/images/icons/phone.png"
      "src/Assets/images/icons/phone@2x.png"
      "src/Assets/images/icons/phone@3x.png"
      "src/Assets/images/icons/shortcutItemIcon.png"
      "src/Assets/images/icons/shortcutItemIcon@2x.png"
      "src/Assets/images/icons/shortcutItemIcon@3x.png"
      "src/Assets/images/icons/tab.png"
      "src/Assets/images/icons/tab@2x.png"
      "src/Assets/images/icons/tab@3x.png"
  )
source_group("images/icons" FILES
      "src/Assets/images/icons/console.png"
      "src/Assets/images/icons/console@2x.png"
      "src/Assets/images/icons/console@3x.png"
      "src/Assets/images/icons/controls.png"
      "src/Assets/images/icons/controls@2x.png"
      "src/Assets/images/icons/controls@3x.png"
      "src/Assets/images/icons/mashups.png"
      "src/Assets/images/icons/mashups@2x.png"
      "src/Assets/images/icons/mashups@3x.png"
      "src/Assets/images/icons/phone.png"
      "src/Assets/images/icons/phone@2x.png"
      "src/Assets/images/icons/phone@3x.png"
      "src/Assets/images/icons/shortcutItemIcon.png"
      "src/Assets/images/icons/shortcutItemIcon@2x.png"
      "src/Assets/images/icons/shortcutItemIcon@3x.png"
      "src/Assets/images/icons/tab.png"
      "src/Assets/images/icons/tab@2x.png"
      "src/Assets/images/icons/tab@3x.png"
  )
set_property(SOURCE ${SOURCE_images_icons} PROPERTY VS_DEPLOYMENT_LOCATION "images\\icons")
set_property(SOURCE ${SOURCE_images_icons} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_images
      "src/Assets/images/titanium-logo.png"
  )
source_group("images" FILES
      "src/Assets/images/titanium-logo.png"
  )
set_property(SOURCE ${SOURCE_images} PROPERTY VS_DEPLOYMENT_LOCATION "images")
set_property(SOURCE ${SOURCE_images} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_sounds
      "src/Assets/sounds/cricket.wav"
  )
source_group("sounds" FILES
      "src/Assets/sounds/cricket.wav"
  )
set_property(SOURCE ${SOURCE_sounds} PROPERTY VS_DEPLOYMENT_LOCATION "sounds")
set_property(SOURCE ${SOURCE_sounds} PROPERTY VS_DEPLOYMENT_CONTENT 1)


# Add all the files to the app
add_executable(${EXE_NAME} WIN32
  src/main.cpp
  src/OutputDebugStringBuf.hpp
    ${SOURCE_Assets}
    ${SOURCE_alloy}
    ${SOURCE_alloy_controllers}
    ${SOURCE_alloy_controllers_console}
    ${SOURCE_alloy_controllers_controls}
    ${SOURCE_alloy_controllers_controls_views}
    ${SOURCE_alloy_controllers_mashups}
    ${SOURCE_alloy_controllers_phone}
    ${SOURCE_alloy_controllers_platform}
    ${SOURCE_alloy_moment_lang}
    ${SOURCE_alloy_styles_console}
    ${SOURCE_alloy_styles_controls}
    ${SOURCE_alloy_styles_controls_views}
    ${SOURCE_alloy_styles}
    ${SOURCE_alloy_styles_mashups}
    ${SOURCE_alloy_styles_phone}
    ${SOURCE_alloy_styles_platform}
    ${SOURCE_alloy_sync}
    ${SOURCE_images_icons}
    ${SOURCE_images}
    ${SOURCE_sounds}
)

set_target_properties(${EXE_NAME} PROPERTIES VS_WINRT_COMPONENT TRUE)
target_link_libraries(${EXE_NAME} TitaniumWindows)

target_include_directories(${EXE_NAME} PUBLIC
  $<TARGET_PROPERTY:TitaniumWindows,INTERFACE_INCLUDE_DIRECTORIES>
  )
