QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport #charts

CONFIG += c++14

TARGET = Load_library
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app
TEMPLATE = app

DEFINES += PATH_OBJECT_FILE='"\\\"$$OUT_PWD\\\""'

SOURCES += main.cpp \
    dinamyc_load_library.cpp \
    din_load_lib.cpp

unix{
    LIBS += -ldl -lrt
    LIBS += -lboost_filesystem -lboost_system -lstdc++fs -lquadmath
    QMAKE_CFLAGS += -ffloat-store
    QMAKE_CXXFLAGS += -ffloat-store
}

HEADERS += \
    dinamyc_load_library.h \
    din_load_lib.h

