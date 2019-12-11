include(Compiler/XLClang)
__compiler_xlclang(CXX)

if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 13.1.1)
  set(CMAKE_CXX98_STANDARD_COMPILE_OPTION  "")
  set(CMAKE_CXX98_EXTENSION_COMPILE_OPTION "")
  set(CMAKE_CXX11_STANDARD_COMPILE_OPTION  "-qlanglvl=extended0x")
  set(CMAKE_CXX11_EXTENSION_COMPILE_OPTION "-qlanglvl=extended0x")
  if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 13.1.2)
    set(CMAKE_CXX11_STANDARD_COMPILE_OPTION  "-std=c++11")
    set(CMAKE_CXX11_EXTENSION_COMPILE_OPTION "-std=gnu++11")
    set(CMAKE_CXX14_STANDARD_COMPILE_OPTION  "-std=c++1y")
    set(CMAKE_CXX14_EXTENSION_COMPILE_OPTION "-std=gnu++1y")
  endif ()
endif()

__compiler_check_default_language_standard(CXX 13.1.1 98)

set(CMAKE_CXX_COMPILE_OBJECT
  "<CMAKE_CXX_COMPILER> -x c++ <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT> -c <SOURCE>")
