cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)

project(Shared_lib)

#include_directories( )
#find_package(OpenCV 3)

set(SOURCE_FILES "shared_lib.cpp")
set(HEADER_FILES "shared_lib.h")

#target_include_directories(Shared_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# We declare the project as a static library and add all the source code files to it.
add_library(Shared_lib SHARED ${HEADER_FILES} ${SOURCE_FILES})









#if(OpenCV_FOUND)
#    target_link_libraries(Lib_Optical_Flow_Clear ${OpenCV_LIBRARIES})
#else()
#    message(FATAL_ERROR "Subdirs No OpenCV found")
#endif()

