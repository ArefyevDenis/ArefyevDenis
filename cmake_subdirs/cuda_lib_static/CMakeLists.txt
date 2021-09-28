cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

message("---------------------Cuda_lib_static-------------------------")

#find_package(CUDA 10.1 REQUIRED)
#message(STATUS "Found CUDA ${CUDA_VERSION_STRING} at ${CUDA_TOOLKIT_ROOT_DIR}")

#if (NOT CMAKE_CUDA_COMPILER)
#    set(CMAKE_CUDA_COMPILER /usr/local/cuda/bin/nvcc) #"${CMAKE_SOURCE_DIR}/<your CUDA relative path here>"
#    message("CUDA = " ${CMAKE_CUDA_COMPILER} )
#endif()

#if(NOT CMAKE_CUDA_DEVICE_LINK_EXECUTABLE)
#  set(CMAKE_CUDA_DEVICE_LINK_EXECUTABLE
#    "<CMAKE_CUDA_COMPILER> <FLAGS> <CMAKE_CUDA_LINK_FLAGS> ${CMAKE_CUDA_COMPILE_OPTIONS_PIC} -shared -dlink <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")
#endif()

project(Cuda_lib_static LANGUAGES CXX CUDA)

#include(CTest)



file(GLOB_RECURSE CPP_FILES src_inc/*.cpp src_inc/*.h)

file(GLOB_RECURSE CU_FILES cuda_cu/*.cu cuda_cu/*.h)

set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED TRUE)

include_directories( /usr/local/cuda/include/ )

add_library( Cuda_lib_static STATIC ${CPP_FILES} ${CU_FILES}  )

set_property(TARGET Cuda_lib_static PROPERTY CUDA_SEPARABLE_COMPILATION ON)

# Request that particles be built with -std=c++11
# As this is a public compile feature anything that links to particles
# will also build with -std=c++11
target_compile_features( Cuda_lib_static PUBLIC cxx_std_11 )


# We need to explicitly state that we need all CUDA files in the particle
# library to be built with -dc as the member functions could be called by
# other libraries and executables
set_target_properties( Cuda_lib_static PROPERTIES CUDA_SEPARABLE_COMPILATION ON )

#if(BUILD_TESTING)

#  add_executable(particle_test test.cu)

# set_target_properties(particle_test PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

#  target_link_libraries(particle_test PRIVATE particles)

#  add_test(NAME particles_10k COMMAND particle_test 10000 )
#  add_test(NAME particles_256k COMMAND particle_test 256000 )

#  if(APPLE)
#    # We need to add the default path to the driver (libcuda.dylib) as an rpath,
#    # so that the static cuda runtime can find it at runtime.
#    set_property(TARGET particle_test PROPERTY BUILD_RPATH ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
#  endif()
#endif()

message("CUDA_VERSION_MAJOR = " ${CUDA_VERSION_MAJOR} )
message("CUDA_VERSION_MINOR = " ${CUDA_VERSION_MINOR} )
message("CUDA_VERSION = " ${CUDA_VERSION} )
message("CUDA_VERSION_STRING = " ${CUDA_VERSION_STRING} )
message("CUDA_INCLUDE_DIRS = " ${CUDA_INCLUDE_DIRS} )
message("CUDA_LIBRARIES = " ${CUDA_LIBRARIES} )
message("CMAKE_CUDA_COMPILER = " ${CMAKE_CUDA_COMPILER} )
message("CMAKE_CUDA_LINK_FLAGS = " ${CMAKE_CUDA_LINK_FLAGS} )
message("OBJECTS = " ${OBJECTS} )
message("CMAKE_CUDA_DEVICE_LINK_EXECUTABLE = " ${CMAKE_CUDA_DEVICE_LINK_EXECUTABLE} )
message("CMAKE_CUDA_STANDARD = " ${CMAKE_CUDA_STANDARD} )
message("CMAKE_CUDA_STANDARD_REQUIRED = " ${CMAKE_CUDA_STANDARD_REQUIRED} )
message("CMAKE_CUDA_EXTENSIONS = " ${CMAKE_CUDA_EXTENSIONS} )
message("CUDA_SEPARABLE_COMPILATION = " ${CUDA_SEPARABLE_COMPILATION} )

message("---------------------Cuda_lib_static-------------------------")

#randomize.cpp
#randomize.h
#particle.cu
#particle.h
#v3.cu
#v3.h
