QT       += gui

TARGET = GstVideoSender
TEMPLATE = lib

INCLUDEPATH += /usr/include/gstreamer-1.0/
INCLUDEPATH += /usr/include/glib-2.0/
INCLUDEPATH += /usr/lib/x86_64-linux-gnu/glib-2.0/include/

OBJECTS_DIR = $$PWD/../obj_dir
## войдёт в makefile в неихменном виде следовательно пути будут отсчитываться от makefile
DESTDIR = $$PWD/../../../../../bin

INCLUDEPATH += ../CMAKE_QT5

SOURCES += \
    ../*.cpp

HEADERS += \
    ../*.h

unix{
    LIBS += -lgstreamer-1.0 -lgstbase-1.0 -lgstapp-1.0 #-L/usr/lib/x86_64-linux-gnu/
}
