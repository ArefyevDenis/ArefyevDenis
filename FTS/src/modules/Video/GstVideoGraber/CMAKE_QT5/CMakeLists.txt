
set( PROJECT GstVideoGraber )

project( ${PROJECT} )

set( BUILD_SHARED_LIBS TRUE )

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../../../bin )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../../../../../bin )

CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
CMAKE_POLICY( SET CMP0012 NEW )

set( CMAKE_BUILD_TYPE Debug )
IF( ${BUILD_RELEASE} )
   set( CMAKE_BUILD_TYPE Release )
ENDIF( ${BUILD_RELEASE} )

######## для сборки ручками добавим путь к исходникам Qt  #####################
#set(CMAKE_PREFIX_PATH /home/user/Qt/5.12.1/gcc_64)

find_package( Qt5Core REQUIRED )
find_package( Qt5Gui REQUIRED )

set(CMAKE_AUTOMOC ON)

if (CMAKE_COMPILER_IS_GNUCXX)
        message("Detected GCC compiler")
        add_definitions (-Wall)
else ()
        message ("Unknown compiler")
endif ()


if (WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
set( 	PROJECT_SRC
	../main.cpp
	../module_info.cpp
        ../module_GstVideoGraber.cpp
        ../GstVideoGraber.cpp
        ../module_info.h
        ../module_GstVideoGraber.h
        ../GstVideoGraber.h
        )
else()
set( 	PROJECT_SRC
        ../main.cpp
        ../module_info.cpp
        ../module_GstVideoGraber.cpp
        ../GstVideoGraber.cpp
        ../module_info.h
        ../module_GstVideoGraber.h
        ../GstVideoGraber.h
        )
endif()

include_directories(
	${QT_INCLUDES}
	${PROJECT_SOURCE_DIR}
	${PROJECT_SOURCE_DIR}/../
	${CMAKE_CURRENT_BINARY_DIR}
        /usr/include/gstreamer-1.0
        /usr/include/glib-2.0
	)
	
add_library( ${PROJECT} SHARED ${PROJECT_SRC} ${PROJECT_MOC_SRC} )

qt5_use_modules( ${PROJECT} Core Gui )

target_link_libraries(
	${PROJECT}
        ${QT_CORE_LIBRARY}
        ${QT_GUI_LIBRARY}
        gstreamer-1.0
        glib-2.0
        gobject-2.0
        gstapp-1.0
	)

if( NOT WIN32 )
add_custom_target( 
        ${PROJECT}_buildnumber ALL
        ${PROJECT_SOURCE_DIR}/../../../../../src/utils/buildnumber.sh ${PROJECT_SOURCE_DIR}/buildnumber
	)
add_dependencies( ${PROJECT} ${PROJECT}_buildnumber)
endif()

message(
"Configuration module "${PROJECT_SOURCE_DIR}"
-------------
CMAKE_BUILD_TYPE          = ${CMAKE_BUILD_TYPE}
CXXFLAGS                  = ${CXXFLAGS}
CMAKE_CXX_FLAGS           = ${CMAKE_CXX_FLAGS}
LDFLAGS                   = ${LDFLAGS}
CMAKE_EXE_LINKER_FLAGS    = ${CMAKE_EXE_LINKER_FLAGS}
CMAKE_INSTALL_PREFIX      = ${CMAKE_INSTALL_PREFIX}
CMAKE_SHARED_LINKER_FLAGS = ${CMAKE_SHARED_LINKER_FLAGS}
	")
