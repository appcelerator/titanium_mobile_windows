#
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
#

# Defines functions and macros useful for building.
#
# Note:
#
# - The functions/macros defined in this file may depend on option()
#   definitions, and thus must be called *after* the options have been
#   defined.

# Defines the compiler/linker flags used to build.  You can tweak
# these definitions to suit your needs.  A variable's value is empty
# before it's explicitly assigned to.
macro(config_compiler_and_linker)
  
  if(APPLE)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    if(COMPILER_SUPPORTS_CXX11)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    else()
      message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
    
    CHECK_CXX_COMPILER_FLAG("-stdlib=libc++" COMPILER_SUPPORTS_LIBCXX)
    if(COMPILER_SUPPORTS_CXX11)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    else()
      message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
  endif()
  
  set(cxx_base_flags "${CMAKE_CXX_FLAGS}")
  set(cxx_default "${cxx_base_flags}")
endmacro()

# Defines the gtest & gtest_main libraries.  User tests should link
# with one of them.
function(cxx_library_with_type name type cxx_flags)
  # type can be either STATIC or SHARED to denote a static or shared
  # library.  ARGN refers to additional arguments after 'cxx_flags'.
  add_library(${name} ${type} ${ARGN})
  if (cxx_flags)
    set_target_properties(${name}
      PROPERTIES
      COMPILE_FLAGS "${cxx_flags}")
  endif()
endfunction()

########################################################################
#
# Helper functions for creating build targets.

function(cxx_shared_library name cxx_flags)
  cxx_library_with_type(${name} SHARED "${cxx_flags}" ${ARGN})
endfunction()

function(cxx_library name cxx_flags)
  cxx_library_with_type(${name} "" "${cxx_flags}" ${ARGN})
endfunction()

# cxx_executable_with_flags(name cxx_flags libs srcs...)
#
# Creates a named C++ executable that depends on the given libraries
# and is built from the given source files with the given compiler
# flags.
function(cxx_executable_with_flags name cxx_flags libs)
  add_executable(${name} ${ARGN})
  if (cxx_flags)
    set_target_properties(${name}
      PROPERTIES
      COMPILE_FLAGS "${cxx_flags}")
  endif()
  
  target_link_libraries(${name} ${libs})
  #   # To support mixing linking in static and dynamic libraries, link each
  #   # library in with an extra call to target_link_libraries.
  #   foreach (lib "${libs}")
  #     target_link_libraries(${name} ${lib})
  #   endforeach()
endfunction()

# cxx_executable(name dir lib srcs...)
#
# Creates a named target that depends on the given libs and is built
# from the given source files.  dir/name.cpp is implicitly included in
# the source file list.
function(cxx_executable name dir libs)
  cxx_executable_with_flags(
    ${name} "${cxx_default}" "${libs}" "${dir}/${name}.cpp" ${ARGN})
endfunction()

find_package(GTest REQUIRED)

# cxx_test_with_flags(name cxx_flags libs srcs...)
#
# Creates a named C++ test that depends on the given libs and is built
# from the given source files with the given compiler flags.
function(cxx_test_with_flags name cxx_flags libs)
  list(APPEND libs ${GTEST_BOTH_LIBRARIES})
  cxx_executable_with_flags(${name} "${cxx_flags}" "${libs}" ${ARGN})
  set_property(TARGET ${name}
    APPEND PROPERTY INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIRS}")
  add_test(${name} ${name})
endfunction()

# cxx_test(name libs srcs...)
#
# Creates a named test target that depends on the given libs and is
# built from the given source files.  Unlike cxx_test_with_flags,
# name.cpp is already implicitly included in the source file list.
function(cxx_test name dir libs)
  cxx_test_with_flags("${name}" "${cxx_default}" "${libs}"
    "${dir}/${name}.cpp" ${ARGN})
endfunction()

# Sets PYTHONINTERP_FOUND and PYTHON_EXECUTABLE.
find_package(PythonInterp)

# py_test(name)
#
# Creates a Python test with the given name whose main module is in
# test/name.py.  It does nothing if Python is not installed.
function(py_test name)
  # We are not supporting Python tests on Linux yet as they consider
  # all Linux environments to be google3 and try to use google3
  # features.
  if (PYTHONINTERP_FOUND)
    # ${CMAKE_BINARY_DIR} is known at configuration time, so we can
    # directly bind it from cmake. ${CTEST_CONFIGURATION_TYPE} is
    # known only at ctest runtime (by calling ctest -c
    # <Configuration>), so we have to escape $ to delay variable
    # substitution here.
    add_test(${name}
      ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/test/${name}.py
      --build_dir=${CMAKE_CURRENT_BINARY_DIR}/\${CTEST_CONFIGURATION_TYPE})
  endif()
endfunction()

# Print all defined properties of the given target (i.e. those without
# a value of -NOTFOUND).
function(print_target_properties TARGET_NAME)
  execute_process(COMMAND cmake --help-property-list
    OUTPUT_VARIABLE CMAKE_PROPERTY_LIST_TEXT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    )
  
  string(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST_TEXT}")
  #message(STATUS "*** ${CMAKE_PROPERTY_LIST} ***")
  
  foreach(PROPERTY ${CMAKE_PROPERTY_LIST})
    # We don't want properties like these:
    #
    # make version 2.8.9
    # COMPILE_DEFINITIONS_<CONFIG>
    # <CONFIG>_OUTPUT_NAME
    # VS_GLOBAL_<variable>
    # XCODE_ATTRIBUTE_<an-attribute>
    
    # This is how to do it using grep:
    # cmake --help-property-list | grep -v -E "(<.+>| )"
    if (NOT "${PROPERTY}" MATCHES "(<.+>| |LOCATION)")
      #message(STATUS "*** ${PROPERTY} ***")
      get_target_property(PROPERTY_VALUE ${TARGET_NAME} ${PROPERTY})
      
      if (NOT "${PROPERTY_VALUE}" MATCHES "-NOTFOUND")
		message(STATUS "*** ${PROPERTY} = ${PROPERTY_VALUE} ***")
      endif()
      
    endif()
  endforeach()
endfunction()

if(APPLE)
  include(${CMAKE_CURRENT_LIST_DIR}/internal_utils_xcode.cmake)
endif()

