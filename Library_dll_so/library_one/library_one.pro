QT       -= gui

TARGET = library_one
TEMPLATE = lib

#CONFIG += staticlib

DEFINES += LIB_ONE

SOURCES += \
    library_one.cpp


HEADERS += \
    library_one.h

## войдёт в makefile в неихменном виде следовательно пути будут отсчитываться от makefile
DESTDIR += ../lib

unix{
    CONFIG  += link_pkgconfig
    PKGCONFIG +=opencv
}
