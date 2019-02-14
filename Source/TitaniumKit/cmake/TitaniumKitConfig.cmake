# TitaniumKit
#
# Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
# Licensed under the terms of the Apache Public License.
# Please see the LICENSE included with this distribution for details.

include(CMakeFindDependencyMacro)
find_dependency(HAL REQUIRED)
find_dependency(Boost 1.55 REQUIRED)

if(NOT TARGET TitaniumKit)
	include("${CMAKE_BINARY_DIR}/TitaniumKitTargets.cmake")
endif()