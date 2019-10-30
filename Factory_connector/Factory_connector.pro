QT       += gui network serialport core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport charts

CONFIG += c++17
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/network   $$PWD/u_mof/include/ \

DEFINES += PATH_OUT_PWD='"\\\"$$OUT_PWD\\\""'
DEFINES += PATH_SRC_PWD='"\\\"$$PWD\\\""'

message(pwd     : $$PWD )
message(out_pwd : $$OUT_PWD )

SOURCES += \
        main.cpp \
    konsole_core.cpp \
    factory_morf.cpp \
    encapsulation_obj.cpp \
    configurate_obj.cpp \
    base_factory.cpp \  
    example_xml.cpp \
    logger.cpp \
    parsser_xml.cpp \
    activ_objects.cpp \
    factory_morf_new.cpp \
    $$PWD/modules/*.cpp \
    $$PWD/network/*.cpp \
    $$PWD/serial/*.cpp \
    $$PWD/u_mof/src/*.cpp \
    $$PWD/core_window/*.cpp \
    $$PWD/core_window/widgets/*.cpp

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

HEADERS += \
    konsole_core.h \
    factory_morf.h \
    encapsulation_obj.h \
    configurate_obj.h \
    base_factory.h \
    logger.h \
    parsser_xml.h \
    example_xml.h \
    activ_objects.h \
    factory_morf_new.h \
    $$PWD/modules/*.h \
    $$PWD/network/*.h \
    $$PWD/serial/*.h \
    $$PWD/u_mof/include/*.h \
    $$PWD/u_mof/include/umof/*.h \
    $$PWD/u_mof/include/umof/detail/*.h \
    $$PWD/core_window/*.h \
    $$PWD/core_window/widgets/*.h

unix{

    QMAKE_CLEAN += \
        Makefile \
        rmo \
        moc_* \
        *.o

    CONFIG  += link_pkgconfig
    PKGCONFIG +=opencv4
    LIBS += -lboost_filesystem -lboost_system -lstdc++fs
}

#    modules/qt_thread_mod.h
#    modules/server_mod.h \
#    modules/poll_mod.h \
#    modules/video_sender.h \
#    modules/optical_flow_mod.h \
#    modules/video_writer.h \
#    modules/video_consumer.h \
#    modules/modules.h \
#    modules/producer_stdout.h \
#    modules/video_producer.h \
#    modules/logger_mod.h \

#    modules/optical_flow_mod.cpp \
#    modules/video_writer.cpp \
#    modules/video_consumer.cpp \
#    modules/server_mod.cpp \
#    modules/poll_mod.cpp \
#    modules/producer_stdout.cpp \
#    modules/video_producer.cpp \
#    modules/logger_mod.cpp \
#    modules/modules.cpp \
#    modules/video_sender.cpp \
#    modules/qt_thread_mod.cpp \
