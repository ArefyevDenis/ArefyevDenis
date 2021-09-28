cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)

project(Static_lib)

set(SOURCE_FILES "static_lib.cpp")
set(HEADER_FILES "static_lib.h")

# We declare the project as a static library and add all the source code files to it.
add_library(Static_lib STATIC ${HEADER_FILES} ${SOURCE_FILES})
