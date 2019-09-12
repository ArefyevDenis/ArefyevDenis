cmake_minimum_required(VERSION 3.8)
CMAKE_POLICY( SET CMP0012 NEW )
message("---------------Start Cmake ---------------")

set(PROJECT Factory_connector)

project(${PROJECT} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#set(SOURCE_FILE "main.cpp")

#if(CMAKE_VERSION VERSION_LESS "3.7.0")
#    set(CMAKE_INCLUDE_CURRENT_DIR ON)
#endif()

find_package(OpenCV 4 REQUIRED)
find_package(Boost 1.58.0 REQUIRED COMPONENTS system regex filesystem thread)

# подключаем библиотеки Qt5
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})
#find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network)
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5SerialPort REQUIRED)

include_directories( ./
    mavlink
    modules
    network
    serial
    multi_thread
    ${QT_INCLUDES}
    #${CMAKE_CURRENT_BINARY_DIR}
    )

#set(SRC_CURENT  ./*.cpp ./*.h)
file(GLOB SRC_CURENT    ./*.cpp ./*.h)
file(GLOB SRC_MODULES   modules/*.cpp modules/*.h)
file(GLOB SRC_NETWORK   network/*.cpp network/*.h)
file(GLOB SRC_SERIAL    serial/*.cpp serial/*.h)
file(GLOB SRC_THREAD    multi_thread/*.cpp multi_thread/*.h)

#set(project_ui mainwindow.ui)
#wrap the ui file to a c++ header
#qt5_wrap_ui(ui_wrap ${project_ui})
#qt5_wrap_cpp(moc_sources
#    ${SRC_MODULES}
#    ${SRC_NETWORK}
#    ${SRC_SERIAL}
#    ${SRC_THREAD} )

add_executable(Factory_connector
    ${SRC_CURENT}
    ${SRC_MODULES}
    ${SRC_NETWORK}
    ${SRC_SERIAL}
    ${SRC_THREAD}
    #${moc_sources}
    #${CMAKE_CURRENT_BINARY_DIR}
    )

qt5_use_modules(${PROJECT} Core Gui Widgets Network SerialPort)

#qt5_add_big_resources()     #Compiles big binary resources into object code
#qt5_add_binary_resources()  #Создает файл RCC из списка файлов ресурсов Qt
#qt5_add_resources()         #Компилирует бинарные ресурсы в исходный код
#qt5_generate_moc()          #Вызывает moc для входного файла
#qt5_wrap_cpp ()             #Создает .moc файлы из источников

#add_custom_target(${PROJECT} ${PROJECT}_autogen ALL)

#add_dependencies(${PROJECT} ${PROJECT}_autogen )

# //----------------- поиск opencv ------------------//

if(OpenCV_FOUND)
    target_link_libraries(${PROJECT} ${OpenCV_LIBRARIES})
else()
    message(FATAL_ERROR " ------ No opencv found ----- ")
endif()

# //----------------- поиск boost ------------------//

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT} ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR " ------ No Boost found ----- ")
endif()

#  ----- Три варианта линковки -------
target_link_libraries(${PROJECT}
    ${QT_CORE_LIBRARY}
    #${QT_NETWORK_LIBRARY}
    )

#target_link_libraries(${PROJECT_NAME}
#    Qt5Core
#    Qt5Widgets
#    Qt5Gui
#    Qt5Network
#    Qt5SerialPort )

#target_link_libraries(${PROJECT_NAME}
#        Qt5::Core
#        Qt5::Widgets
#        Qt5::Gui
#        Qt5::Network
#        Qt5::SerialPort)

#set_property(TARGET ${PROJECT} PROPERTY AUTOMOC ON)

message("  PROJECT_MOC_SRC = "   ${PROJECT_MOC_SRC})
message("  Configure "${PROJECT}"
    ------------------------------------------------
    CMAKE_BUILD_TYPE            = ${CMAKE_BUILD_TYPE}
    CXXFLAGS                    = $ENV{CXXFLAGS}
    CMAKE_CXX_FLAGS             = ${CMAKE_CXX_FLAGS}
    LDFLAGS                     = $ENV{LDFLAGS}
    CMAKE_EXE_LINKER_FLAGS      = ${CMAKE_EXE_LINKER_FLAGS}
    CMAKE_INSTALL_PREFIX        = ${CMAKE_INSTALL_PREFIX}
    CMAKE_SHARED_LINKER_FLAGS   = ${CMAKE_SHARED_LINKER_FLAGS}
    QT_CORE_LIBRARY             = ${QT_CORE_LIBRARY}
    QT_NETWORK_LIBRARY          = ${QT_NETWORK_LIBRARY}
    ")

message("---------------Stop Cmake ---------------")
