
set( PROJECT UdpClient )

project( ${PROJECT} )

set( BUILD_SHARED_LIBS TRUE )

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../../../bin )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../../../bin )

cmake_minimum_required(VERSION 2.8)
cmake_policy( SET CMP0012 NEW )

set( CMAKE_BUILD_TYPE Debug )
IF( ${BUILD_RELEASE} )
  set( CMAKE_BUILD_TYPE Release )
ENDIF( ${BUILD_RELEASE} )

######## для сборки ручками добавим путь к исходникам Qt  #####################
#set(CMAKE_PREFIX_PATH /home/user/Qt/5.12.1/gcc_64)

FIND_PACKAGE(Qt5Core REQUIRED)
FIND_PACKAGE(Qt5Network REQUIRED)

set(CMAKE_AUTOMOC ON)

if (CMAKE_COMPILER_IS_GNUCXX)
        message("Detected GCC compiler")
        add_definitions (-Wall)
else ()
        message ("Unknown compiler")
endif ()

set(    PROJECT_SRC
        ../main.cpp
        ../module_info.cpp
        ../module_udp_client.cpp
        ../udp_client.cpp
        ../module_info.h
        ../module_udp_client.h
        ../udp_client.h
    )

include_directories(
        ${QT_INCLUDES}
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/../
        ${CMAKE_CURRENT_BINARY_DIR}
    )

add_library( ${PROJECT} SHARED ${PROJECT_SRC} ${PROJECT_MOC_SRC} )

qt5_use_modules ( ${PROJECT} Core Network )

target_link_libraries (
        ${PROJECT}
        ${QT_CORE_LIBRARY}
        ${QT_NETWORK_LIBRARY}
    )

if( NOT WIN32 )
add_custom_target(
    ${PROJECT}_buildnumber ALL
    ${PROJECT_SOURCE_DIR}/../../../../../src/utils/buildnumber.sh ${PROJECT_SOURCE_DIR}/buildnumber
    )
add_dependencies( ${PROJECT} ${PROJECT}_buildnumber )
endif()

message("
Configuration module "${PROJECT_SOURCE_DIR}"
-------------
CMAKE_BUILD_TYPE        	= ${CMAKE_BUILD_TYPE}
CXXFLAGS                	= $ENV{CXXFLAGS}
CMAKE_CXX_FLAGS         	= ${CMAKE_CXX_FLAGS}
LDFLAGS                 	= $ENV{LDFLAGS}
CMAKE_EXE_LINKER_FLAGS  	= ${CMAKE_EXE_LINKER_FLAGS}
CMAKE_INSTALL_PREFIX    	= ${CMAKE_INSTALL_PREFIX}
CMAKE_SHARED_LINKER_FLAGS	= ${CMAKE_SHARED_LINKER_FLAGS}
")
