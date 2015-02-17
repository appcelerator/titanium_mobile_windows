# TitaniumKit
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

# if(WIN32)
#   get_target_property(HAL_DLL_LOCATION HAL LOCATION)
#   file(COPY ${HAL_DLL_LOCATION} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
# endif()

set(SOURCE_examples
  NativeGlobalObjectExample.hpp
  NativeGlobalObjectExample.cpp
  NativeModuleExample.hpp
  NativeModuleExample.cpp
  NativeTiExample.hpp
  NativeTiExample.cpp
  NativeAPIExample.hpp
  NativeAPIExample.cpp
  NativeViewExample.hpp
  NativeViewExample.cpp
  NativeWindowExample.hpp
  NativeWindowExample.cpp
  NativeButtonExample.hpp
  NativeButtonExample.cpp
  NativeListViewExample.hpp
  NativeListViewExample.cpp
  NativePlatformExample.hpp
  NativePlatformExample.cpp
  NativePlatformDisplayCapsExample.hpp
  NativePlatformDisplayCapsExample.cpp
  NativeAccelerometerExample.hpp
  NativeAccelerometerExample.cpp
  NativeGestureExample.hpp
  NativeGestureExample.cpp
  NativeBlobExample.hpp
  NativeBlobExample.cpp
  NativeFilesystemExample.hpp
  NativeFilesystemExample.cpp
  NativeFileExample.hpp
  NativeFileExample.cpp
  NativeWebViewExample.hpp
  NativeWebViewExample.cpp
  )
add_library(TitaniumKit_examples
  ${SOURCE_examples}
  )
target_include_directories(TitaniumKit_examples INTERFACE
  ${PROJECT_SOURCE_DIR}/examples
  )
target_link_libraries(TitaniumKit_examples TitaniumKit)

set(SOURCE_Main
  Main.cpp
)
add_executable(Main
  ${SOURCE_Main}
  )
target_link_libraries(Main TitaniumKit_examples)

source_group(TitaniumKit\\Examples FILES
  ${SOURCE_examples}
  ${SOURCE_Main}
 )
