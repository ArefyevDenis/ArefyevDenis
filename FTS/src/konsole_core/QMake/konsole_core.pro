QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport charts

CONFIG += c++17

#TARGET = mmm
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

OBJECTS_DIR = $$PWD/../obj_dir

DESTDIR = $$PWD/../../../bin

INCLUDEPATH += $$PWD/../../modules/log

SOURCES += ../main.cpp \
        $$PWD/../konsole_core.cpp \
        $$PWD/../../core/*.cpp \
        $$PWD/../../utils/*.cpp \

HEADERS += \
        $$PWD/../konsole_core.h \
        $$PWD/../../core/*.h \
        $$PWD/../../utils/*.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = $$PWD/../../../bin #/opt/$${TARGET}/bin
!isEmpty(target.path){
 INSTALLS += target
 message(INSTALLS: $$target.path)
}

message(PWD: $$PWD)
message(OUT_PWD: $$OUT_PWD)
message(OBJECTS_DIR: $$OBJECTS_DIR)
message(DESTDIR: $$DESTDIR)

unix{
    LIBS += -ldl -lrt
    LIBS += -lboost_filesystem -lboost_system -lboost_thread -lstdc++fs -lquadmath
#    QMAKE_CFLAGS += -ffloat-store
#    QMAKE_CXXFLAGS += -ffloat-store
}
