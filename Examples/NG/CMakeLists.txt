# The "NG" App.
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

project(NG)

set(NG_VERSION 0.1.0)

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

include_external_msproject(
    TitaniumWindows_Hyperloop ${PROJECT_SOURCE_DIR}/TitaniumWindows_Hyperloop/TitaniumWindows_Hyperloop.csproj
    TYPE FAE04EC0-301F-11D3-BF4B-00C04F79EFBC)

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

if(NOT TARGET TitaniumWindows_Native)
  get_filename_component(Native_SOURCE_DIR ${PROJECT_SOURCE_DIR}/Native ABSOLUTE)
  add_subdirectory(${Native_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/Native EXCLUDE_FROM_ALL)
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
  src/Assets/titanium_settings.ini
  src/Assets/app.js
  src/Assets/Logo.png
  src/Assets/SmallLogo.png
  src/Assets/SplashScreen.png
  src/Assets/SplashScreen480x800.png
  src/Assets/StoreLogo.png
  src/Assets/Square150x150Logo.png
  src/Assets/Square71x71Logo.png
  src/Assets/Square44x44Logo.png
  src/Assets/cricket.wav
  src/Assets/WebViewIndexPage.htm
  src/Assets/WebViewNextPage.htm
  src/Assets/sample.jpg
  src/Assets/require_test.js
  )

set_property(SOURCE ${SOURCE_Assets} PROPERTY VS_DEPLOYMENT_CONTENT 1)

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

set(SOURCE_Strings_en "src/Assets/Strings/en/Resources.resw")
source_group("Strings\\en" FILES "src/Assets/Strings/en/Resources.resw")

set(SOURCE_Strings_es "src/Assets/Strings/es/Resources.resw")
source_group("Strings\\es" FILES "src/Assets/Strings/es/Resources.resw")

file(GLOB_RECURSE COMMONJS_LEGACY_PACKAGE_DIRECTORY "modules/commonjs/commonjs.legacy.package/1.0.0/*.*")
set(SOURCE_commonjs_legacy_package ${COMMONJS_LEGACY_PACKAGE_DIRECTORY})
source_group("node_modules/commonjs.legacy.package" FILES ${COMMONJS_LEGACY_PACKAGE_DIRECTORY})
set_property(SOURCE ${SOURCE_commonjs_legacy_package} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.legacy.package")
set_property(SOURCE ${SOURCE_commonjs_legacy_package} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE WITH_INDEX_JS_DIRECTORY "src/Assets/with_index_js/*.*")
set(SOURCE_with_index_js ${WITH_INDEX_JS_DIRECTORY})
source_group("with_index_js" FILES ${WITH_INDEX_JS_DIRECTORY})
set_property(SOURCE ${SOURCE_with_index_js} PROPERTY VS_DEPLOYMENT_LOCATION "with_index_js")
set_property(SOURCE ${SOURCE_with_index_js} PROPERTY VS_DEPLOYMENT_CONTENT 1)

add_executable(${EXE_NAME} WIN32
  src/main.cpp
  include/OutputDebugStringBuf.hpp
  ${SOURCE_Assets}
  ${SOURCE_fonts}
  ${SOURCE_Strings_en}
  ${SOURCE_Strings_es}
  ${SOURCE_with_index_js}
  ${SOURCE_commonjs_legacy_package}
)

set_target_properties(${EXE_NAME} PROPERTIES VS_WINRT_COMPONENT TRUE)
target_link_libraries(${EXE_NAME} TitaniumWindows TitaniumWindows_Native)

target_include_directories(${EXE_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  $<TARGET_PROPERTY:TitaniumWindows,INTERFACE_INCLUDE_DIRECTORIES>
  $<TARGET_PROPERTY:TitaniumWindows_Native,INTERFACE_INCLUDE_DIRECTORIES>
  )
