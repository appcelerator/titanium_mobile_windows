# TitaniumKit
# Author: Matt Langston <mlangston@appcelerator.com>
# Created: 2013.03.12
# 
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# 
# Licensed under the Apache License, Version 2.0 (the "License"); you
# may not use this software or any of it's contents except in
# compliance with the License. The full text of the license is in the
# file LICENSE.txt in the top-level directory of this project, or you
# may obtain a copy of the License at
# 
# http://www.apache.org/licenses/LICENSE-2.0

find_program(XCODEBUILD xcodebuild)
if ("${XCODEBUILD}" MATCHES "-NOTFOUND$")
  message(FATAL_ERROR "The xcodebuild program could not be found.")
endif()

find_program(XCODE-SELECT xcode-select)
if ("${XCODE-SELECT}" MATCHES "-NOTFOUND$")
  message(FATAL_ERROR "The xcode-select program could not be found.")
endif()

find_program(XCRUN xcrun)
if ("${XCRUN}" MATCHES "-NOTFOUND$")
  message(FATAL_ERROR "The xcrun program could not be found.")
endif()

# Sets VAR to the Xcode root directory of the given SDK (e.g. macosx)
# for the user's currently selected Xcode installation. The command
# "xcodebuild -showsdks" will list all available SDK's.
#
# Passing any of the values "macosx", "iphoneos" or "iphonesimulator"
# for sdk will use the latest installed version of that SDK, e.g. if
# "macosx10.8" is the latest installed version of OS X, then passing
# "macosx" will select "macosx10.8".
#
# $ xcodebuild -showsdks
# OS X SDKs:
# Mac OS X 10.7                 -sdk macosx10.7
# OS X 10.8                     -sdk macosx10.8
# 
# iOS SDKs:
# iOS 6.1                       -sdk iphoneos6.1
# 
# iOS Simulator SDKs:
# Simulator - iOS 6.1           -sdk iphonesimulator6.1
#
# $ xcodebuild -sdk macosx -version Path
# /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.8.sdk
function(find_xcode_sdkroot VAR sdk)
  execute_process(COMMAND ${XCODEBUILD} -sdk ${sdk} -version Path
    OUTPUT_VARIABLE XCODE_SDKROOT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  set("${VAR}" "${XCODE_SDKROOT}" PARENT_SCOPE)
endfunction()

# Set VAR to the Xcode Developer directory of the user's currently
# selected Xcode installation.
# 
# $ xcode-select -print-path
# /Applications/Xcode.app/Contents/Developer
function(find_xcode_developer_dir VAR)
  execute_process(COMMAND ${XCODE-SELECT} -print-path
    OUTPUT_VARIABLE XCODE_DEVELOPER_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  set("${VAR}" "${XCODE_DEVELOPER_DIR}" PARENT_SCOPE)
endfunction()

# Set VAR to the list of framework directories of the user's currently
# selected Xcode installation for the given SDK (e.g. macosx).  The
# command "xcodebuild -showsdks" will list all available SDK's.
#
# Passing any of the values "macosx", "iphoneos" or "iphonesimulator"
# for sdk will use the latest installed version of that SDK, e.g. if
# "macosx10.8" is the latest installed version of OS X, then passing
# "macosx" will select "macosx10.8".
function(find_xcode_framework_dirs VAR sdk)
  find_xcode_sdkroot(XCODE_SDKROOT ${sdk})
  find_xcode_developer_dir(XCODE_DEVELOPER_DIR)
  set(XCODE_FRAMEWORK_DIRS "${XCODE_SDKROOT}/System/Library/Frameworks" "${XCODE_DEVELOPER_DIR}/Library/Frameworks")
  list(REMOVE_DUPLICATES XCODE_FRAMEWORK_DIRS)
  set("${VAR}" ${XCODE_FRAMEWORK_DIRS} PARENT_SCOPE)
endfunction()

# Prepend the user-selected Xcode SDK framework directories (via
# xcode-select) for the given sdk (e.g. macosx) to
# CMAKE_SYSTEM_FRAMEWORK_PATH so that they are searched first.  The
# command "xcodebuild -showsdks" will list all available SDK's.
#
# Passing any of the values "macosx", "iphoneos" or "iphonesimulator"
# for sdk will use the latest installed version of that SDK, e.g. if
# "macosx10.8" is the latest installed version of OS X, then passing
# "macosx" will select "macosx10.8".
function(config_cmake_system_framework_path sdk)
  find_xcode_framework_dirs(XCODE_FRAMEWORK_DIRS ${sdk})
  list(INSERT CMAKE_SYSTEM_FRAMEWORK_PATH 0 ${XCODE_FRAMEWORK_DIRS})
  list(REMOVE_DUPLICATES CMAKE_SYSTEM_FRAMEWORK_PATH)
  # Make sure our caller can see the changes.
  set(CMAKE_SYSTEM_FRAMEWORK_PATH ${CMAKE_SYSTEM_FRAMEWORK_PATH} PARENT_SCOPE)
endfunction()

# ocunit_test(name libs srcs...)
#
# Creates a named OCUnit test target that depends on the given libs
# and is built from the given source files.
function(ocunit_test name libs)
  find_library(SenTestingKit SenTestingKit)
  if ("${SenTestingKit}" MATCHES "-NOTFOUND$")
    message(FATAL_ERROR "SenTestingKit.framework could not be found.")
  else()
    message(STATUS "SenTestingKit=${SenTestingKit}")
    # -- SenTestingKit=/Applications/Xcode.app/Contents/Developer/Library/Frameworks/SenTestingKit.framework
  endif()
  
  # The link fails because target_link_libraries isn't adding the -F
  # linker flag for the SenTestingKit Framework. According to the
  # CMake docs it should (see
  # http://www.cmake.org/cmake/help/v2.8.10/cmake.html#command:find_library):
  #
  #   If the library found is a framework, then VAR will be set to the
  #   full path to the framework <fullPath>/A.framework. When a full
  #   path to a framework is used as a library, CMake will use a
  #   -framework A, and a -F<fullPath> to link the framework to the
  #   target.
  # 
  # My workaround is to add it manually.
  get_filename_component(SenTestingKit_Frameworks_PATH ${SenTestingKit} PATH)
  add_library(${name} MODULE ${ARGN})
  target_link_libraries(${name}
    ${libs}
    "-F ${SenTestingKit_Frameworks_PATH}" # I shouldn't have to do this.
    ${SenTestingKit}
    )
  
  set(BUNDLE_EXTENSION "octest")
  set(BUNDLE_PATH "${CMAKE_CURRENT_BINARY_DIR}/${name}.${BUNDLE_EXTENSION}")
  set_target_properties(${name}
    PROPERTIES
    BUNDLE "true"
    BUNDLE_EXTENSION "${BUNDLE_EXTENSION}"
    # We attach the BUNDLE_PATH custom property to the target because
    # it is needed by otest. Interestingly there is no built-in CMake
    # target property that gives this path.
    BUNDLE_PATH "${BUNDLE_PATH}"
    )
  
  # Get the directory containing SenTestingKit.framework, which must
  # be added to the DYLD_FRAMEWORK_PATH environment variable in order
  # for otest to run.
  get_filename_component(DYLD_FRAMEWORK_PATH ${SenTestingKit} PATH)
  #message(STATUS "MDL: DYLD_FRAMEWORK_PATH=${DYLD_FRAMEWORK_PATH}")
  
  #DYLD_FRAMEWORK_PATH=$(xcode-select -print-path)/Library/Frameworks OBJC_DISABLE_GC=YES xcrun -log otest ./build.debug/test/FooTests.octest/
  set(OTEST_COMMAND xcrun -log otest ${BUNDLE_PATH})
  #message(STATUS "MDL: DYLD_FRAMEWORK_PATH=${DYLD_FRAMEWORK_PATH} OBJC_DISABLE_GC=YES ${OTEST_COMMAND}")
  add_test(NAME ${name} COMMAND ${OTEST_COMMAND})
  set_property(TEST ${name}
    PROPERTY
    ENVIRONMENT
    "OBJC_DISABLE_GC=YES"
    "DYLD_FRAMEWORK_PATH=${DYLD_FRAMEWORK_PATH}"
    )
endfunction()
