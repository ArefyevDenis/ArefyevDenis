set ( PROJECT FTSKonsole )

project( ${PROJECT} )

CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
CMAKE_POLICY( SET CMP0012 NEW )

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../bin  )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../bin  )

set( CMAKE_BUILD_TYPE Debug )
IF( ${BUILD_RELEASE} )
  set( CMAKE_BUILD_TYPE Release )
ENDIF()

######## для сборки ручками добавим путь к исходникам Qt  #####################
#set(CMAKE_PREFIX_PATH /home/user/Qt/5.12.1/gcc_64)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)

set(CMAKE_AUTOMOC ON)

set( Boost_USE_STATIC_LIBS OFF )
if (WIN32)
        set( BOOST_ROOT ${BOOST_LIBRARY_PATH} )
endif()

find_package( Boost COMPONENTS thread date_time filesystem system )

include_directories(
    ${QT_INCLUDES}
    ../../core
    ../../utils
    #${CMAKE_CURRENT_BINARY_DIR}
    )
	
#*** Совместимость с Windows - определяем переменную BOOST_LIBRARY_PATH в Системе ***#
if (WIN32)
        include_directories( ${BOOST_LIBRARY_PATH} )
        include_directories( ${Boost_INCLUDE_DIRS} )
endif()
#***  ***#


#set (
#    PROJECT_MOC_HDRS
#    konsole_core.h
#    )

set (
    PROJECT_SRCS
    ../main.cpp
    ../konsole_core.cpp
    ../../core/module_installer.cpp
    ../../core/configs_pool.cpp
    ../../core/loggers_pool.cpp
    ../../core/settings.cpp
    ../../core/modules_grabber.cpp
    ../../core/cross_thread.cpp
    ../../core/ics_controller_handler.cpp
    ../../core/service_application_info.cpp
    ../../core/actions_pool.cpp
    ../../utils/export_interfaces_describer.cpp
    ../../utils/export_isc_parameter_describer.cpp
    ../../utils/widget_info_describer.cpp
    ../konsole_core.h
    ../../core/interface_struct.h
    ../../core/module_installer.h
    ../../core/configs_pool.h
    ../../core/loggers_pool.h
    ../../core/settings.h
    ../../core/modules_grabber.h
    ../../core/cross_thread.h
    ../../core/ics_controller_handler.h
    ../../core/service_application_info.h
    ../../core/actions_pool.h
    ../../utils/export_interfaces_describer.h
    ../../utils/export_isc_parameter_describer.h
    ../../utils/widget_info_describer.h
    ../../../include/factory/module_factory.h
    )

add_executable(
    ${PROJECT}
    ${PROJECT_SRCS}
    #${PROJECT_MOC_SRC}
    )

qt5_use_modules( ${PROJECT} Core Gui Widgets )

if (WIN32)
    target_link_libraries(
        ${PROJECT}
        ${QT_CORE_LIBRARY}
        ${Boost_LIBRARIES}
        )
else()
    target_link_libraries(
        ${PROJECT}
        dl
        ${QT_CORE_LIBRARY}
        ${Boost_LIBRARIES}
        )
endif()

message("
Configuration "${PROJECT}"
-------------
CMAKE_BUILD_TYPE            = ${CMAKE_BUILD_TYPE}
CXXFLAGS                    = $ENV{CXXFLAGS}
CMAKE_CXX_FLAGS             = ${CMAKE_CXX_FLAGS}
LDFLAGS                     = $ENV{LDFLAGS}
CMAKE_EXE_LINKER_FLAGS      = ${CMAKE_EXE_LINKER_FLAGS}
CMAKE_INSTALL_PREFIX        = ${CMAKE_INSTALL_PREFIX}
CMAKE_SHARED_LINKER_FLAGS   = ${CMAKE_SHARED_LINKER_FLAGS}
QT_CORE_LIBRARY             = ${QT_CORE_LIBRARY}
")
