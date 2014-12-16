# LayoutEngine
# Author: Russell W. McMahon
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

set(SOURCE_Main
  Main.cpp
  )
add_executable(SimpleExample
  ${SOURCE_Main}
  )
target_link_libraries(SimpleExample LayoutEngine)

source_group(LayoutEngine\\Examples FILES
  ${SOURCE_Main}
  )
