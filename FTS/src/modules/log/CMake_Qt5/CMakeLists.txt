
project( log )

CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
CMAKE_POLICY( SET CMP0012 NEW )

set( CMAKE_BUILD_TYPE Debug )
IF( ${BUILD_RELEASE} )
  set( CMAKE_BUILD_TYPE Release )
ENDIF( ${BUILD_RELEASE} )

######## для сборки ручками добавим путь к исходникам Qt  #####################
#set(CMAKE_PREFIX_PATH /home/user/Qt/5.12.1/gcc_64)

find_package(Qt5Core REQUIRED)

set( Boost_USE_STATIC_LIBS OFF )
if (WIN32)
        set( BOOST_ROOT ${BOOST_LIBRARY_PATH} )
endif()
find_package( Boost COMPONENTS system )

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (CMAKE_COMPILER_IS_GNUCXX)
        message("Detected GCC compiler")
        add_definitions (-Wall)
else ()
        message ("Unknown compiler")
endif ()

if (WIN32)
    LINK_DIRECTORIES($ENV{BOOST_LIBRARY_PATH}stage/lib)
endif()

if (NOT ${BUILD_PATH} STREQUAL "")
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_PATH} )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_PATH} )
else ()
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${log_SOURCE_DIR}/../../../../bin  )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${log_SOURCE_DIR}/../../../../bin  )
endif()

add_subdirectory( ${log_SOURCE_DIR}/../extern_lib/log4qt/CMake_Qt5 ${CMAKE_CURRENT_BINARY_DIR}/log4qt )

include_directories( 
		${QT_INCLUDES} 
        ${log_SOURCE_DIR}/../
        ${log_SOURCE_DIR}/../../../utils
        ${log_SOURCE_DIR}/buildnumber
        ${log_SOURCE_DIR}/../extern_lib/log4qt/src
	)
	
#*** Совместимость с Windows - определяем переменную BOOST_LIBRARY_PATH в Системе ***#
if (WIN32)
	include_directories( $ENV{BOOST_LIBRARY_PATH} ) 
        include_directories( ${Boost_INCLUDE_DIRS} )
endif()
#***  ***#

if(WIN32)
    set ( log_SRC
                    ../main.cpp
                    ../module_info.cpp
                    ../proxy_logger.cpp
                    ../log_system.cpp
                    ../signalsbynewloggrabber.cpp
                    ../module.def
                    ${log_SOURCE_DIR}/../../../utils/libraries_info_setter.cpp
                    ../module_info.h
                    ../proxy_logger.h
                    ../log_system.h
                    ../signalsbynewloggrabber.h
                    ${log_SOURCE_DIR}/../../../utils/libraries_info_setter.h
            )
else()
    set ( log_SRC
                    ../main.cpp
                    ../module_info.cpp
                    ../proxy_logger.cpp
                    ../log_system.cpp
                    ../signalsbynewloggrabber.cpp
                    ${log_SOURCE_DIR}/../../../utils/libraries_info_setter.cpp
                    ../module_info.h
                    ../proxy_logger.h
                    ../log_system.h
                    ../signalsbynewloggrabber.h
                    ${log_SOURCE_DIR}/../../../utils/libraries_info_setter.h
            )
endif()

add_library( log SHARED ${log_SRC} )

qt5_use_modules( log Core )

if (CMAKE_COMPILER_IS_GNUCXX)
        target_link_libraries( log ${QT_CORE_LIBRARY} Log4Qt pthread )
endif()


message("
Configuration module "${log_SOURCE_DIR}"
-------------
CMAKE_BUILD_TYPE        = ${CMAKE_BUILD_TYPE}
CXXFLAGS                = $ENV{CXXFLAGS}
CMAKE_CXX_FLAGS         = ${CMAKE_CXX_FLAGS}
LDFLAGS                 = $ENV{LDFLAGS}
CMAKE_EXE_LINKER_FLAGS  = ${CMAKE_EXE_LINKER_FLAGS}
CMAKE_INSTALL_PREFIX    = ${CMAKE_INSTALL_PREFIX}
CMAKE_SHARED_LINKER_FLAGS	= ${CMAKE_SHARED_LINKER_FLAGS}
")
