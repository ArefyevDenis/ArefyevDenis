cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

message("---------------------Cuda_lib_shared-------------------------")

project(Cuda_lib_shared LANGUAGES CXX CUDA)

#include(CTest)

file(GLOB_RECURSE CPP_FILES src_inc/*.cpp src_inc/*.h)

file(GLOB_RECURSE CU_FILES cuda_cu/*.cu cuda_cu/*.h)

set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED TRUE)

include_directories( /usr/local/cuda/include/ )

add_library( Cuda_lib_shared SHARED ${CPP_FILES} ${CU_FILES}  )

set_property(TARGET Cuda_lib_shared PROPERTY CUDA_SEPARABLE_COMPILATION ON)

# Request that particles be built with -std=c++11
# As this is a public compile feature anything that links to particles
# will also build with -std=c++11
target_compile_features( Cuda_lib_shared PUBLIC cxx_std_11 )

# We need to explicitly state that we need all CUDA files in the particle
# library to be built with -dc as the member functions could be called by
# other libraries and executables
set_target_properties( Cuda_lib_shared PROPERTIES CUDA_SEPARABLE_COMPILATION ON )

message("---------------------Cuda_lib_shared-------------------------")
