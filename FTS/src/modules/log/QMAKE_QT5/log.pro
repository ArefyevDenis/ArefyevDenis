QT       -= gui

TARGET = log
TEMPLATE = lib

INCLUDEPATH += $$PWD/../extern_lib/log4qt/src/
INCLUDEPATH += $$PWD/../../

#include($$PWD/../extern_lib/log4qt/src/Log4Qt.pri)

OBJECTS_DIR = $$PWD/../obj_dir
## войдёт в makefile в неихменном виде следовательно пути будут отсчитываться от makefile
DESTDIR = $$PWD/../../../../bin

INCLUDEPATH += ../CMake_Qt5

#CONFIG += staticlib
#DEFINES += LOG4QT_VERSION_STR='"1.0.0"'    #'"\\\"$$OUT_PWD\\\""'
DEFINES += LOG4QT_VERSION_STR='"\\\"1.0.0"\\\"'

SOURCES += \
    ../*.cpp

HEADERS += \
    ../*.h


unix{
   # SUBLIBS += $$PWD/../../../../bin
    LIBS += -L$$DESTDIR -lLog4Qt
}
