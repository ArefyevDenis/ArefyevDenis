QT       -= gui

TARGET = library_three
TEMPLATE = lib

#CONFIG += staticlib

DEFINES += LIB_THREE

SOURCES += \
    library_three.cpp


HEADERS += \
    library_three.h


## войдёт в makefile в неизменном виде следовательно пути будут отсчитываться от makefile
DESTDIR += ../lib

unix{
    CONFIG  += link_pkgconfig
    PKGCONFIG +=opencv
}
