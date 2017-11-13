# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.
cmake_minimum_required(VERSION 3.0.0)

if (${CMAKE_SYSTEM_VERSION} MATCHES "^10.0")
  set(PLATFORM win10)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsPhone")
  set(PLATFORM wp)
  add_definitions("-DPHONE")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore")
  set(PLATFORM store)
else()
  message(FATAL_ERROR "This app supports Store / Phone only.")
endif()

project(NMocha)

set(NMocha_VERSION 0.1.0)

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

file(GLOB_RECURSE ASSETS_DIRECTORY "src/Assets/*.*")

# Exclude i18n files, that's supposed to be used from CLI
file(GLOB_RECURSE I18N_FILES "src/Assets/i18n/*")
list(REMOVE_ITEM ASSETS_DIRECTORY ${I18N_FILES})

set(SOURCE_Assets
  ${CMAKE_CURRENT_BINARY_DIR}/${APP_MANIFEST_NAME}
  ${ASSETS_DIRECTORY}
  ${JavaScriptCore_LIBRARY_DIR}/Release/JavaScriptCore.dll
  ${JavaScriptCore_LIBRARY_DIR}/Release/WTF.dll
  )

set_property(SOURCE ${SOURCE_Assets} PROPERTY VS_DEPLOYMENT_CONTENT 1)


file(GLOB_RECURSE COMMONJS_INDEX_JS_DIRECTORY "modules/commonjs/commonjs.index_js/1.0.0/*.*")
set(SOURCE_commonjs_index_js ${COMMONJS_INDEX_JS_DIRECTORY})
source_group("node_modules/commonjs.index_js" FILES ${COMMONJS_INDEX_JS_DIRECTORY})
set_property(SOURCE ${SOURCE_commonjs_index_js} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.index_js")
set_property(SOURCE ${SOURCE_commonjs_index_js} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE COMMONJS_INDEX_JSON_DIRECTORY "modules/commonjs/commonjs.index_json/1.0.0/*.*")
set(SOURCE_commonjs_index_json ${COMMONJS_INDEX_JSON_DIRECTORY})
source_group("node_modules/commonjs.index_json" FILES ${COMMONJS_INDEX_JSON_DIRECTORY})
set_property(SOURCE ${SOURCE_commonjs_index_json} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.index_json")
set_property(SOURCE ${SOURCE_commonjs_index_json} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE COMMONJS_LEGACY_DIRECTORY "modules/commonjs/commonjs.legacy/1.0.0/*.*")
set(SOURCE_commonjs_legacy ${COMMONJS_LEGACY_DIRECTORY})
source_group("node_modules/commonjs.legacy" FILES ${COMMONJS_LEGACY_DIRECTORY})
set_property(SOURCE ${SOURCE_commonjs_legacy} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.legacy")
set_property(SOURCE ${SOURCE_commonjs_legacy} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE COMMONJS_LEGACY_INDEX_JS_DIRECTORY "modules/commonjs/commonjs.legacy.index_js/1.0.0/*.*")
set(SOURCE_commonjs_legacy_index_js ${COMMONJS_LEGACY_INDEX_JS_DIRECTORY})
source_group("node_modules/commonjs.legacy.index_js" FILES ${COMMONJS_LEGACY_INDEX_JS_DIRECTORY})
set_property(SOURCE ${SOURCE_commonjs_legacy_index_js} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.legacy.index_js")
set_property(SOURCE ${SOURCE_commonjs_legacy_index_js} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE COMMONJS_LEGACY_INDEX_JSON_DIRECTORY "modules/commonjs/commonjs.legacy.index_json/1.0.0/*.*")
set(SOURCE_commonjs_legacy_index_json ${COMMONJS_LEGACY_INDEX_JSON_DIRECTORY})
source_group("node_modules/commonjs.legacy.index_json" FILES ${COMMONJS_LEGACY_INDEX_JSON_DIRECTORY})
set_property(SOURCE ${SOURCE_commonjs_legacy_index_json} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.legacy.index_json")
set_property(SOURCE ${SOURCE_commonjs_legacy_index_json} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE COMMONJS_LEGACY_PACKAGE_DIRECTORY "modules/commonjs/commonjs.legacy.package/1.0.0/*.*")
set(SOURCE_commonjs_legacy_package ${COMMONJS_LEGACY_PACKAGE_DIRECTORY})
source_group("node_modules/commonjs.legacy.package" FILES ${COMMONJS_LEGACY_PACKAGE_DIRECTORY})
set_property(SOURCE ${SOURCE_commonjs_legacy_package} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.legacy.package")
set_property(SOURCE ${SOURCE_commonjs_legacy_package} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE COMMONJS_PACKAGE_DIRECTORY "modules/commonjs/commonjs.package/1.0.0/*.*")
set(SOURCE_commonjs_package ${COMMONJS_PACKAGE_DIRECTORY})
source_group("node_modules/commonjs.package" FILES ${COMMONJS_PACKAGE_DIRECTORY})
set_property(SOURCE ${SOURCE_commonjs_package} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.package")
set_property(SOURCE ${SOURCE_commonjs_package} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE NODE_MODULES_FOO "src/Assets/node_modules/foo/*.*")
set(SOURCE_node_modules_foo ${NODE_MODULES_FOO})
source_group("node_modules/foo" FILES ${NODE_MODULES_FOO})
set_property(SOURCE ${SOURCE_node_modules_foo} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\foo")
set_property(SOURCE ${SOURCE_node_modules_foo} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE NODE_MODULES_BAR "src/Assets/node_modules/bar/*.*")
set(SOURCE_node_modules_bar ${NODE_MODULES_BAR})
source_group("node_modules/bar" FILES ${NODE_MODULES_BAR})
set_property(SOURCE ${SOURCE_node_modules_bar} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\bar")
set_property(SOURCE ${SOURCE_node_modules_bar} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE NODE_MODULES_BAR_BAZ "src/Assets/node_modules/bar/node_modules/baz/*.*")
set(SOURCE_node_modules_bar_baz ${NODE_MODULES_BAR_BAZ})
source_group("node_modules/bar/node_modules/baz" FILES ${NODE_MODULES_BAR_BAZ})
set_property(SOURCE ${SOURCE_node_modules_bar_baz} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\bar\\node_modules\\baz")
set_property(SOURCE ${SOURCE_node_modules_bar_baz} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE NODE_MODULES_BAZ "src/Assets/node_modules/baz/*.*")
set(SOURCE_node_modules_baz ${NODE_MODULES_BAZ})
source_group("node_modules/baz" FILES ${NODE_MODULES_BAZ})
set_property(SOURCE ${SOURCE_node_modules_baz} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\baz")
set_property(SOURCE ${SOURCE_node_modules_baz} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE WITH_INDEX_JS_DIRECTORY "src/Assets/with_index_js/*.*")
set(SOURCE_with_index_js ${WITH_INDEX_JS_DIRECTORY})
source_group("with_index_js" FILES ${WITH_INDEX_JS_DIRECTORY})
set_property(SOURCE ${SOURCE_with_index_js} PROPERTY VS_DEPLOYMENT_LOCATION "with_index_js")
set_property(SOURCE ${SOURCE_with_index_js} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE WITH_INDEX_JSON_DIRECTORY "src/Assets/with_index_json/*.*")
set(SOURCE_with_index_json ${WITH_INDEX_JSON_DIRECTORY})
source_group("with_index_json" FILES ${WITH_INDEX_JSON_DIRECTORY})
set_property(SOURCE ${SOURCE_with_index_json} PROPERTY VS_DEPLOYMENT_LOCATION "with_index_json")
set_property(SOURCE ${SOURCE_with_index_json} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE WITH_PACKAGE_DIRECTORY "src/Assets/with_package/*.*")
set(SOURCE_with_package ${WITH_PACKAGE_DIRECTORY})
source_group("with_package" FILES ${WITH_PACKAGE_DIRECTORY})
set_property(SOURCE ${SOURCE_with_package} PROPERTY VS_DEPLOYMENT_LOCATION "with_package")
set_property(SOURCE ${SOURCE_with_package} PROPERTY VS_DEPLOYMENT_CONTENT 1)

file(GLOB_RECURSE UTILITIES_DIRECTORY "src/Assets/utilities/*.*")
set(SOURCE_utilities ${UTILITIES_DIRECTORY})
source_group("utilities" FILES ${UTILITIES_DIRECTORY})
set_property(SOURCE ${SOURCE_utilities} PROPERTY VS_DEPLOYMENT_LOCATION "utilities")
set_property(SOURCE ${SOURCE_utilities} PROPERTY VS_DEPLOYMENT_CONTENT 1)

set(SOURCE_Strings_en "src/Assets/Strings/en/Resources.resw")
source_group("Strings\\en" FILES "src/Assets/Strings/en/Resources.resw")

set(SOURCE_Strings_en_GB "src/Assets/Strings/en-GB/Resources.resw")
source_group("Strings\\en-GB" FILES "src/Assets/Strings/en-GB/Resources.resw")

set(SOURCE_Strings_ja "src/Assets/Strings/ja/Resources.resw")
source_group("Strings\\ja" FILES "src/Assets/Strings/ja/Resources.resw")

add_executable(${EXE_NAME} WIN32
  src/main.cpp
  include/OutputDebugStringBuf.hpp
  include/pch.h
  ${SOURCE_Assets}
  ${SOURCE_commonjs_index_js}
  ${SOURCE_commonjs_index_json}
  ${SOURCE_commonjs_legacy}
  ${SOURCE_commonjs_legacy_index_js}
  ${SOURCE_commonjs_legacy_index_json}
  ${SOURCE_commonjs_legacy_package}
  ${SOURCE_commonjs_package}
  ${SOURCE_with_index_js}
  ${SOURCE_with_index_json}
  ${SOURCE_with_package}
  ${SOURCE_node_modules_foo}
  ${SOURCE_node_modules_bar}
  ${SOURCE_node_modules_bar_baz}
  ${SOURCE_node_modules_baz}
  ${SOURCE_utilities}
  ${SOURCE_Strings_en}
  ${SOURCE_Strings_en_GB}
  ${SOURCE_Strings_ja}
)

set_target_properties(${EXE_NAME} PROPERTIES VS_WINRT_COMPONENT TRUE)
target_link_libraries(${EXE_NAME} TitaniumWindows)

target_include_directories(${EXE_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  $<TARGET_PROPERTY:TitaniumWindows,INTERFACE_INCLUDE_DIRECTORIES>
  )
