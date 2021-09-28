QT       -= gui

TARGET = library_two
TEMPLATE = lib

#CONFIG += staticlib

DEFINES += LIB_TWO

SOURCES += \
    library_two.cpp


HEADERS += \
    library_two.h


## войдёт в makefile в неихменном виде следовательно пути будут отсчитываться от makefile
DESTDIR += ../lib

unix{
    CONFIG  += link_pkgconfig
    PKGCONFIG +=opencv
}
