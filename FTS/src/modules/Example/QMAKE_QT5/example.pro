QT       -= gui

TARGET = Example
TEMPLATE = lib

OBJECTS_DIR = $$PWD/../obj_dir
## войдёт в makefile в неихменном виде следовательно пути будут отсчитываться от makefile
DESTDIR = $$PWD/../../../../bin

INCLUDEPATH += ../CMAKE_QT5

#CONFIG += staticlib
#DEFINES += Example

SOURCES += \
    ../*.cpp

HEADERS += \
    ../*.h

unix{
#    CONFIG  += link_pkgconfig
#    PKGCONFIG +=opencv
}
