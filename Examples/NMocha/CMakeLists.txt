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

set(SOURCE_analytics
  "src/Assets/analytics/featureEventPayload.json"
  )
source_group("analytics" FILES
  "src/Assets/analytics/featureEventPayload.json"
  )
set_property(SOURCE ${SOURCE_analytics} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_analytics} PROPERTY VS_DEPLOYMENT_LOCATION "analytics")
set(SOURCE_src_Assets
  ${CMAKE_CURRENT_BINARY_DIR}/${APP_MANIFEST_NAME}
  ${JavaScriptCore_LIBRARY_DIR}/Release/JavaScriptCore.dll
  ${JavaScriptCore_LIBRARY_DIR}/Release/WTF.dll
  "src/Assets/app.js"
  "src/Assets/console.test.js"
  "src/Assets/error.test.js"
  "src/Assets/global.test.js"
  "src/Assets/Logo.png"
  "src/Assets/require.test.js"
  "src/Assets/sample.mp3"
  "src/Assets/should.js"
  "src/Assets/SmallLogo.png"
  "src/Assets/SplashScreen.png"
  "src/Assets/StoreLogo.png"
  "src/Assets/string.test.js"
  "src/Assets/testDbResource.db"
  "src/Assets/ti-mocha.js"
  "src/Assets/ti.accelerometer.test.js"
  "src/Assets/ti.analytics.test.js"
  "src/Assets/ti.android.notificationmanager.test.js"
  "src/Assets/ti.android.service.interval.js"
  "src/Assets/ti.android.service.normal.js"
  "src/Assets/ti.android.service.test.js"
  "src/Assets/ti.android.test.js"
  "src/Assets/ti.api.test.js"
  "src/Assets/ti.app.ios.searchquery.test.js"
  "src/Assets/ti.app.ios.test.js"
  "src/Assets/ti.app.ios.useractivity.test.js"
  "src/Assets/ti.app.properties.test.js"
  "src/Assets/ti.app.test.js"
  "src/Assets/ti.app.windows.backgroundservice.test.js"
  "src/Assets/ti.blob.test.js"
  "src/Assets/ti.bootstrap.test.js"
  "src/Assets/ti.buffer.test.js"
  "src/Assets/ti.calendar.calendar.test.js"
  "src/Assets/ti.codec.test.js"
  "src/Assets/ti.contacts.group.test.js"
  "src/Assets/ti.contacts.person.test.js"
  "src/Assets/ti.contacts.test.js"
  "src/Assets/ti.database.test.js"
  "src/Assets/ti.filesystem.file.test.js"
  "src/Assets/ti.filesystem.filestream.test.js"
  "src/Assets/ti.filesystem.test.js"
  "src/Assets/ti.geolocation.test.js"
  "src/Assets/ti.gesture.test.js"
  "src/Assets/ti.locale.test.js"
  "src/Assets/ti.map.test.js"
  "src/Assets/ti.media.audioplayer.test.js"
  "src/Assets/ti.media.sound.test.js"
  "src/Assets/ti.media.test.js"
  "src/Assets/ti.media.videoplayer.test.js"
  "src/Assets/ti.network.cookie.test.js"
  "src/Assets/ti.network.httpclient.test.js"
  "src/Assets/ti.network.socket.tcp.test.js"
  "src/Assets/ti.network.socket.udp.test.js"
  "src/Assets/ti.network.test.js"
  "src/Assets/ti.platform.displaycaps.test.js"
  "src/Assets/ti.platform.test.js"
  "src/Assets/ti.proxy.test.js"
  "src/Assets/ti.require.test_test.js"
  "src/Assets/ti.stream.test.js"
  "src/Assets/ti.test.js"
  "src/Assets/ti.ui.2dmatrix.test.js"
  "src/Assets/ti.ui.activityindicator.test.js"
  "src/Assets/ti.ui.alertdialog.test.js"
  "src/Assets/ti.ui.android.drawerlayout.test.js"
  "src/Assets/ti.ui.attributedstring.test.js"
  "src/Assets/ti.ui.button.test.js"
  "src/Assets/ti.ui.constants.test.js"
  "src/Assets/ti.ui.emaildialog.test.js"
  "src/Assets/ti.ui.imageview.test.js"
  "src/Assets/ti.ui.ios.navigationwindow.test.js"
  "src/Assets/ti.ui.ios.previewcontext.test.js"
  "src/Assets/ti.ui.ios.test.js"
  "src/Assets/ti.ui.label.test.js"
  "src/Assets/ti.ui.layout.test.js"
  "src/Assets/ti.ui.listview.test.js"
  "src/Assets/ti.ui.maskedimage.test.js"
  "src/Assets/ti.ui.optiondialog.test.js"
  "src/Assets/ti.ui.picker.test.js"
  "src/Assets/ti.ui.progressbar.test.js"
  "src/Assets/ti.ui.scrollableview.test.js"
  "src/Assets/ti.ui.scrollview.test.js"
  "src/Assets/ti.ui.searchbar.test.js"
  "src/Assets/ti.ui.slider.test.js"
  "src/Assets/ti.ui.switch.test.js"
  "src/Assets/ti.ui.tab.test.js"
  "src/Assets/ti.ui.tabgroup.test.js"
  "src/Assets/ti.ui.tableview.test.js"
  "src/Assets/ti.ui.test.js"
  "src/Assets/ti.ui.textarea.test.js"
  "src/Assets/ti.ui.textfield.test.js"
  "src/Assets/ti.ui.toolbar.test.js"
  "src/Assets/ti.ui.view.test.js"
  "src/Assets/ti.ui.webview.test.html"
  "src/Assets/ti.ui.webview.test.js"
  "src/Assets/ti.ui.window.test.js"
  "src/Assets/ti.ui.windows.commandbar.test.js"
  "src/Assets/ti.utils.test.js"
  "src/Assets/ti.xml.test.js"
  "src/Assets/timers.test.js"
  )
set_property(SOURCE ${SOURCE_src_Assets} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set(SOURCE_bootstraps
  "src/Assets/bootstraps/simple.bootstrap.js"
  "src/Assets/bootstraps/ui.bootstrap.js"
  )
source_group("bootstraps" FILES
  "src/Assets/bootstraps/simple.bootstrap.js"
  "src/Assets/bootstraps/ui.bootstrap.js"
  )
set_property(SOURCE ${SOURCE_bootstraps} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_bootstraps} PROPERTY VS_DEPLOYMENT_LOCATION "bootstraps")
set(SOURCE_fixtures
  "src/Assets/fixtures/empty-double.js"
  "src/Assets/fixtures/empty-single.js"
  "src/Assets/fixtures/false.js"
  "src/Assets/fixtures/nan.js"
  "src/Assets/fixtures/null.js"
  "src/Assets/fixtures/undefined.js"
  "src/Assets/fixtures/zero.js"
  )
source_group("fixtures" FILES
  "src/Assets/fixtures/empty-double.js"
  "src/Assets/fixtures/empty-single.js"
  "src/Assets/fixtures/false.js"
  "src/Assets/fixtures/nan.js"
  "src/Assets/fixtures/null.js"
  "src/Assets/fixtures/undefined.js"
  "src/Assets/fixtures/zero.js"
  )
set_property(SOURCE ${SOURCE_fixtures} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_fixtures} PROPERTY VS_DEPLOYMENT_LOCATION "fixtures")
set(SOURCE_json_files
  "src/Assets/json_files/amber.json"
  )
source_group("json_files" FILES
  "src/Assets/json_files/amber.json"
  )
set_property(SOURCE ${SOURCE_json_files} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_json_files} PROPERTY VS_DEPLOYMENT_LOCATION "json_files")
set(SOURCE_node_modules_abbrev
  "src/Assets/node_modules/abbrev/abbrev.js"
  "src/Assets/node_modules/abbrev/CONTRIBUTING.md"
  "src/Assets/node_modules/abbrev/LICENSE"
  "src/Assets/node_modules/abbrev/package.json"
  "src/Assets/node_modules/abbrev/README.md"
  )
source_group("node_modules_abbrev" FILES
  "src/Assets/node_modules/abbrev/abbrev.js"
  "src/Assets/node_modules/abbrev/CONTRIBUTING.md"
  "src/Assets/node_modules/abbrev/LICENSE"
  "src/Assets/node_modules/abbrev/package.json"
  "src/Assets/node_modules/abbrev/README.md"
  )
set_property(SOURCE ${SOURCE_node_modules_abbrev} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_node_modules_abbrev} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\abbrev")
set(SOURCE_node_modules_bar
  "src/Assets/node_modules/bar/bar.js"
  "src/Assets/node_modules/bar/package.json"
  )
source_group("node_modules_bar" FILES
  "src/Assets/node_modules/bar/bar.js"
  "src/Assets/node_modules/bar/package.json"
  )
set_property(SOURCE ${SOURCE_node_modules_bar} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_node_modules_bar} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\bar")
set(SOURCE_node_modules_bar_node_modules_baz
  "src/Assets/node_modules/bar/node_modules/baz/index.js"
  )
source_group("node_modules_bar_node_modules_baz" FILES
  "src/Assets/node_modules/bar/node_modules/baz/index.js"
  )
set_property(SOURCE ${SOURCE_node_modules_bar_node_modules_baz} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_node_modules_bar_node_modules_baz} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\bar\\node_modules\\baz")
set(SOURCE_node_modules_baz
  "src/Assets/node_modules/baz/index.js"
  )
source_group("node_modules_baz" FILES
  "src/Assets/node_modules/baz/index.js"
  )
set_property(SOURCE ${SOURCE_node_modules_baz} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_node_modules_baz} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\baz")

set(SOURCE_node_modules_commonjs.index_js
  "src/Assets/node_modules/commonjs.index_js/index.js"
  "src/Assets/node_modules/commonjs.index_js/index.json"
  "src/Assets/node_modules/commonjs.index_js/manifest"
  )
source_group("node_modules_commonjs.index_js" FILES
  "src/Assets/node_modules/commonjs.index_js/index.js"
  "src/Assets/node_modules/commonjs.index_js/index.json"
  "src/Assets/node_modules/commonjs.index_js/manifest"
  )
set_property(SOURCE ${SOURCE_node_modules_commonjs.index_js} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_node_modules_commonjs.index_js} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.index_js")
set(SOURCE_node_modules_commonjs.index_json
  "src/Assets/node_modules/commonjs.index_json/index.json"
  "src/Assets/node_modules/commonjs.index_json/manifest"
  )
source_group("node_modules_commonjs.index_json" FILES
  "src/Assets/node_modules/commonjs.index_json/index.json"
  "src/Assets/node_modules/commonjs.index_json/manifest"
  )
set_property(SOURCE ${SOURCE_node_modules_commonjs.index_json} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_node_modules_commonjs.index_json} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.index_json")
set(SOURCE_node_modules_commonjs.legacy
  "src/Assets/node_modules/commonjs.legacy/commonjs.legacy.js"
  "src/Assets/node_modules/commonjs.legacy/manifest"
  )
source_group("node_modules_commonjs.legacy" FILES
  "src/Assets/node_modules/commonjs.legacy/commonjs.legacy.js"
  "src/Assets/node_modules/commonjs.legacy/manifest"
  )
set_property(SOURCE ${SOURCE_node_modules_commonjs.legacy} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_node_modules_commonjs.legacy} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.legacy")
set(SOURCE_node_modules_commonjs.legacy.index_js
  "src/Assets/node_modules/commonjs.legacy.index_js/commonjs.legacy.index_js.js"
  "src/Assets/node_modules/commonjs.legacy.index_js/index.js"
  "src/Assets/node_modules/commonjs.legacy.index_js/index.json"
  "src/Assets/node_modules/commonjs.legacy.index_js/manifest"
  )
source_group("node_modules_commonjs.legacy.index_js" FILES
  "src/Assets/node_modules/commonjs.legacy.index_js/commonjs.legacy.index_js.js"
  "src/Assets/node_modules/commonjs.legacy.index_js/index.js"
  "src/Assets/node_modules/commonjs.legacy.index_js/index.json"
  "src/Assets/node_modules/commonjs.legacy.index_js/manifest"
  )
set_property(SOURCE ${SOURCE_node_modules_commonjs.legacy.index_js} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_node_modules_commonjs.legacy.index_js} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.legacy.index_js")
set(SOURCE_node_modules_commonjs.legacy.index_json
  "src/Assets/node_modules/commonjs.legacy.index_json/commonjs.legacy.index_json.js"
  "src/Assets/node_modules/commonjs.legacy.index_json/index.json"
  "src/Assets/node_modules/commonjs.legacy.index_json/manifest"
  )
source_group("node_modules_commonjs.legacy.index_json" FILES
  "src/Assets/node_modules/commonjs.legacy.index_json/commonjs.legacy.index_json.js"
  "src/Assets/node_modules/commonjs.legacy.index_json/index.json"
  "src/Assets/node_modules/commonjs.legacy.index_json/manifest"
  )
set_property(SOURCE ${SOURCE_node_modules_commonjs.legacy.index_json} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_node_modules_commonjs.legacy.index_json} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.legacy.index_json")
set(SOURCE_node_modules_commonjs.legacy.package
  "src/Assets/node_modules/commonjs.legacy.package/commonjs.legacy.package.js"
  "src/Assets/node_modules/commonjs.legacy.package/index.js"
  "src/Assets/node_modules/commonjs.legacy.package/index.json"
  "src/Assets/node_modules/commonjs.legacy.package/main.js"
  "src/Assets/node_modules/commonjs.legacy.package/manifest"
  "src/Assets/node_modules/commonjs.legacy.package/package.json"
  )
source_group("node_modules_commonjs.legacy.package" FILES
  "src/Assets/node_modules/commonjs.legacy.package/commonjs.legacy.package.js"
  "src/Assets/node_modules/commonjs.legacy.package/index.js"
  "src/Assets/node_modules/commonjs.legacy.package/index.json"
  "src/Assets/node_modules/commonjs.legacy.package/main.js"
  "src/Assets/node_modules/commonjs.legacy.package/manifest"
  "src/Assets/node_modules/commonjs.legacy.package/package.json"
  )
set_property(SOURCE ${SOURCE_node_modules_commonjs.legacy.package} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_node_modules_commonjs.legacy.package} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.legacy.package")
set(SOURCE_node_modules_commonjs.package
  "src/Assets/node_modules/commonjs.package/index.js"
  "src/Assets/node_modules/commonjs.package/index.json"
  "src/Assets/node_modules/commonjs.package/main.js"
  "src/Assets/node_modules/commonjs.package/manifest"
  "src/Assets/node_modules/commonjs.package/package.json"
  )
source_group("node_modules_commonjs.package" FILES
  "src/Assets/node_modules/commonjs.package/index.js"
  "src/Assets/node_modules/commonjs.package/index.json"
  "src/Assets/node_modules/commonjs.package/main.js"
  "src/Assets/node_modules/commonjs.package/manifest"
  "src/Assets/node_modules/commonjs.package/package.json"
  )
set_property(SOURCE ${SOURCE_node_modules_commonjs.package} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_node_modules_commonjs.package} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\commonjs.package")

set(SOURCE_node_modules_foo
  "src/Assets/node_modules/foo/index.js"
  "src/Assets/node_modules/foo/package.json"
  )
source_group("node_modules_foo" FILES
  "src/Assets/node_modules/foo/index.js"
  "src/Assets/node_modules/foo/package.json"
  )
set_property(SOURCE ${SOURCE_node_modules_foo} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_node_modules_foo} PROPERTY VS_DEPLOYMENT_LOCATION "node_modules\\foo")
set(SOURCE_Strings_en
  "src/Assets/Strings/en/Resources.resw"
  )
source_group("Strings\\en" FILES
  "src/Assets/Strings/en/Resources.resw"
  )
set(SOURCE_Strings_en-GB
  "src/Assets/Strings/en-GB/Resources.resw"
  )
source_group("Strings\\en-GB" FILES
  "src/Assets/Strings/en-GB/Resources.resw"
  )
set(SOURCE_Strings_en-US
  "src/Assets/Strings/en-US/Resources.resw"
  )
source_group("Strings\\en-US" FILES
  "src/Assets/Strings/en-US/Resources.resw"
  )
set(SOURCE_Strings_ja
  "src/Assets/Strings/ja/Resources.resw"
  )
source_group("Strings\\ja" FILES
  "src/Assets/Strings/ja/Resources.resw"
  )
set(SOURCE_ti.touchid
  "src/Assets/ti.touchid/example.js"
  )
source_group("ti.touchid" FILES
  "src/Assets/ti.touchid/example.js"
  )
set_property(SOURCE ${SOURCE_ti.touchid} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_ti.touchid} PROPERTY VS_DEPLOYMENT_LOCATION "ti.touchid")
set(SOURCE_txtFiles
  "src/Assets/txtFiles/decodedFile.txt"
  "src/Assets/txtFiles/empty.txt"
  "src/Assets/txtFiles/encodedFile.txt"
  "src/Assets/txtFiles/file.txt"
  "src/Assets/txtFiles/stream_test_in.txt"
  "src/Assets/txtFiles/stream_test_out.txt"
  "src/Assets/txtFiles/text.txt"
  )
source_group("txtFiles" FILES
  "src/Assets/txtFiles/decodedFile.txt"
  "src/Assets/txtFiles/empty.txt"
  "src/Assets/txtFiles/encodedFile.txt"
  "src/Assets/txtFiles/file.txt"
  "src/Assets/txtFiles/stream_test_in.txt"
  "src/Assets/txtFiles/stream_test_out.txt"
  "src/Assets/txtFiles/text.txt"
  )
set_property(SOURCE ${SOURCE_txtFiles} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_txtFiles} PROPERTY VS_DEPLOYMENT_LOCATION "txtFiles")
set(SOURCE_utilities
  "src/Assets/utilities/assertions.js"
  "src/Assets/utilities/mocha-filter.js"
  "src/Assets/utilities/utilities.js"
  )
source_group("utilities" FILES
  "src/Assets/utilities/assertions.js"
  "src/Assets/utilities/mocha-filter.js"
  "src/Assets/utilities/utilities.js"
  )
set_property(SOURCE ${SOURCE_utilities} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_utilities} PROPERTY VS_DEPLOYMENT_LOCATION "utilities")
set(SOURCE_with_index_js
  "src/Assets/with_index_js/index.js"
  "src/Assets/with_index_js/index.json"
  "src/Assets/with_index_js/sub1.js"
  "src/Assets/with_index_js/sub2.js"
  "src/Assets/with_index_js/sub3.js"
  )
source_group("with_index_js" FILES
  "src/Assets/with_index_js/index.js"
  "src/Assets/with_index_js/index.json"
  "src/Assets/with_index_js/sub1.js"
  "src/Assets/with_index_js/sub2.js"
  "src/Assets/with_index_js/sub3.js"
  )
set_property(SOURCE ${SOURCE_with_index_js} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_with_index_js} PROPERTY VS_DEPLOYMENT_LOCATION "with_index_js")
set(SOURCE_with_index_json
  "src/Assets/with_index_json/index.json"
  )
source_group("with_index_json" FILES
  "src/Assets/with_index_json/index.json"
  )
set_property(SOURCE ${SOURCE_with_index_json} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_with_index_json} PROPERTY VS_DEPLOYMENT_LOCATION "with_index_json")
set(SOURCE_with_package
  "src/Assets/with_package/index.js"
  "src/Assets/with_package/index.json"
  "src/Assets/with_package/main.js"
  "src/Assets/with_package/package.json"
  )
source_group("with_package" FILES
  "src/Assets/with_package/index.js"
  "src/Assets/with_package/index.json"
  "src/Assets/with_package/main.js"
  "src/Assets/with_package/package.json"
  )
set_property(SOURCE ${SOURCE_with_package} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_with_package} PROPERTY VS_DEPLOYMENT_LOCATION "with_package")
set(SOURCE_xml
  "src/Assets/xml/attrs.xml"
  "src/Assets/xml/cdata.xml"
  "src/Assets/xml/cdataEntities.xml"
  "src/Assets/xml/element.xml"
  "src/Assets/xml/elementNS.xml"
  "src/Assets/xml/mismatched_tag.xml"
  "src/Assets/xml/nodeCount.xml"
  "src/Assets/xml/nodes.xml"
  "src/Assets/xml/no_end.xml"
  "src/Assets/xml/no_toplevel.xml"
  "src/Assets/xml/soap.xml"
  "src/Assets/xml/with_dtd.xml"
  "src/Assets/xml/with_ns.xml"
  "src/Assets/xml/xpath.xml"
  )
source_group("xml" FILES
  "src/Assets/xml/attrs.xml"
  "src/Assets/xml/cdata.xml"
  "src/Assets/xml/cdataEntities.xml"
  "src/Assets/xml/element.xml"
  "src/Assets/xml/elementNS.xml"
  "src/Assets/xml/mismatched_tag.xml"
  "src/Assets/xml/nodeCount.xml"
  "src/Assets/xml/nodes.xml"
  "src/Assets/xml/no_end.xml"
  "src/Assets/xml/no_toplevel.xml"
  "src/Assets/xml/soap.xml"
  "src/Assets/xml/with_dtd.xml"
  "src/Assets/xml/with_ns.xml"
  "src/Assets/xml/xpath.xml"
  )
set_property(SOURCE ${SOURCE_xml} PROPERTY VS_DEPLOYMENT_CONTENT 1)
set_property(SOURCE ${SOURCE_xml} PROPERTY VS_DEPLOYMENT_LOCATION "xml")
add_executable(${EXE_NAME} WIN32
  src/main.cpp
  include/OutputDebugStringBuf.hpp
  include/pch.h
  ${SOURCE_analytics}
  ${SOURCE_src_Assets}
  ${SOURCE_bootstraps}
  ${SOURCE_fixtures}
  ${SOURCE_json_files}
  ${SOURCE_node_modules_abbrev}
  ${SOURCE_node_modules_bar}
  ${SOURCE_node_modules_bar_node_modules_baz}
  ${SOURCE_node_modules_baz}
  ${SOURCE_node_modules_commonjs.index_js}
  ${SOURCE_node_modules_commonjs.index_json}
  ${SOURCE_node_modules_commonjs.legacy}
  ${SOURCE_node_modules_commonjs.legacy.index_js}
  ${SOURCE_node_modules_commonjs.legacy.index_json}
  ${SOURCE_node_modules_commonjs.legacy.package}
  ${SOURCE_node_modules_commonjs.package}
  ${SOURCE_node_modules_foo}
  ${SOURCE_Strings_en}
  ${SOURCE_Strings_en-GB}
  ${SOURCE_Strings_en-US}
  ${SOURCE_Strings_ja}
  ${SOURCE_ti.touchid}
  ${SOURCE_txtFiles}
  ${SOURCE_utilities}
  ${SOURCE_with_index_js}
  ${SOURCE_with_index_json}
  ${SOURCE_with_package}
  ${SOURCE_xml}
)


set_target_properties(${EXE_NAME} PROPERTIES VS_WINRT_COMPONENT TRUE)
target_link_libraries(${EXE_NAME} TitaniumWindows)

target_include_directories(${EXE_NAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/include
  $<TARGET_PROPERTY:TitaniumWindows,INTERFACE_INCLUDE_DIRECTORIES>
  )
