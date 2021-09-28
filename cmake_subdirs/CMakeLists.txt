cmake_minimum_required (VERSION 3.8)

project(Example)

add_subdirectory (static_lib)
add_subdirectory (shared_lib)

find_package(CUDA REQUIRED)
if(CUDA_FOUND)
    message(STATUS "<<<<<<<<<< Found cuda ${CUDA_VERSION_STING} at ${CUDA_TOOLKIT_ROOT_DIR}>>>>>>>>>>>>>>>>>")
    add_subdirectory (cuda_lib_shared)
    add_subdirectory (cuda_lib_static)
else()
    message(FATAL_ERROR "<<<< No cuda found >>>>")
endif()

find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "<<<<<<<<<< 1 Found opencv ${OPENCV_VERSION} >>>>>>>>>>>>>>>>>")
    message(STATUS "<<<<<<<<<< 1 Found opencv ${OpenCV_INCLUDE_DIRS} >>>>>>>>>>>>>>>>>")
else()
    message(STATUS "<<<<<<<<<< NOT Found opencv >>>>>>>>>>>>>>>>>")
endif()

add_subdirectory (example_elf)

#target_link_libraries()
