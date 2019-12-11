include(Compiler/Clang)
__compiler_clang(CXX)

if(NOT "x${CMAKE_CXX_SIMULATE_ID}" STREQUAL "xMSVC")
  set(CMAKE_CXX_COMPILE_OPTIONS_VISIBILITY_INLINES_HIDDEN "-fvisibility-inlines-hidden")
endif()

if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.0)
  set(CMAKE_CXX98_STANDARD_COMPILE_OPTION "-std=c++98")
  set(CMAKE_CXX98_EXTENSION_COMPILE_OPTION "-std=gnu++98")

  set(CMAKE_CXX11_STANDARD_COMPILE_OPTION "-std=c++11")
  set(CMAKE_CXX11_EXTENSION_COMPILE_OPTION "-std=gnu++11")
endif()

if(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.1)
  set(CMAKE_CXX14_STANDARD_COMPILE_OPTION "-std=c++14")
  set(CMAKE_CXX14_EXTENSION_COMPILE_OPTION "-std=gnu++14")
elseif(NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.1)
  # AppleClang 5.0 knows this flag, but does not set a __cplusplus macro greater than 201103L
  set(CMAKE_CXX14_STANDARD_COMPILE_OPTION "-std=c++1y")
  set(CMAKE_CXX14_EXTENSION_COMPILE_OPTION "-std=gnu++1y")
endif()

if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 6.1)
  set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "-std=c++1z")
  set(CMAKE_CXX17_EXTENSION_COMPILE_OPTION "-std=gnu++1z")
endif()

__compiler_check_default_language_standard(CXX 4.0 98)
