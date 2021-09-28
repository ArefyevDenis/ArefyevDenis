cmake_minimum_required (VERSION 3.8)

message("---------------------Example_elf-------------------------")

project(Example_elf CXX CUDA)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES "main.cpp")

#file(GLOB_RECURSE SRC_FILES src_inc/*.cpp src_inc/*.h)

add_executable(Example_elf ${SOURCE_FILES} )

include_directories("../static_lib")
include_directories("../shared_lib")

include_directories("../cuda_lib_shared/cuda_cu")
include_directories("../cuda_lib_shared/src_inc")

include_directories("../cuda_lib_static/src_inc")
include_directories("../cuda_lib_static/cuda_cu")

target_link_libraries(Example_elf Static_lib)
target_link_libraries(Example_elf Shared_lib)

find_package(CUDA 10.1 REQUIRED)

if(CUDA_FOUND)
    message(STATUS "++++++++++++++++++++++ Found cuda ${CUDA_VERSION_STING} at ${CUDA_TOOLKIT_ROOT_DIR} ++++++++++++++++++++++++")
    target_link_libraries(Example_elf Cuda_lib_shared)
    target_link_libraries(Example_elf Cuda_lib_static)

else()
    message(FATAL_ERROR "<<<< No cuda found >>>>")
endif()


message("---------------------Example_elf-------------------------")

