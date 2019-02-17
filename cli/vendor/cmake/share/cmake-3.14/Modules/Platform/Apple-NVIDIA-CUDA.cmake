include(Platform/Darwin)

set(__IMPLICT_LINKS )
foreach(dir ${CMAKE_CUDA_HOST_IMPLICIT_LINK_DIRECTORIES})
  string(APPEND __IMPLICT_LINKS " -L\"${dir}\"")
endforeach()
foreach(lib ${CMAKE_CUDA_HOST_IMPLICIT_LINK_LIBRARIES})
  if(${lib} MATCHES "/")
    string(APPEND __IMPLICT_LINKS " \"${lib}\"")
  else()
    string(APPEND __IMPLICT_LINKS " -l${lib}")
  endif()
endforeach()

set(CMAKE_SHARED_LIBRARY_CREATE_CUDA_FLAGS "-shared -Wl,-headerpad_max_install_names")
set(CMAKE_SHARED_MODULE_CREATE_CUDA_FLAGS "-shared -Wl,-headerpad_max_install_names")

set(CMAKE_CUDA_CREATE_SHARED_LIBRARY "<CMAKE_CUDA_HOST_LINK_LAUNCHER> <CMAKE_SHARED_LIBRARY_CUDA_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CUDA_FLAGS> -o <TARGET> <SONAME_FLAG> <TARGET_INSTALLNAME_DIR><TARGET_SONAME> <OBJECTS> <LINK_LIBRARIES>${__IMPLICT_LINKS}")
set(CMAKE_CUDA_CREATE_SHARED_MODULE "<CMAKE_CUDA_HOST_LINK_LAUNCHER> <CMAKE_SHARED_LIBRARY_CUDA_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_CUDA_FLAGS> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>${__IMPLICT_LINKS}")
