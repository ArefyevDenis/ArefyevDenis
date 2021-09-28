QT += gui widgets

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug|release) {
#    QMAKE_CFLAGS    += -fsanitize=address
#    QMAKE_CXXFLAGS  += -fsanitize=address
#    LIBS += -lasan
    DEFINES += MDBG
    message(DDF: $$DEFINES)
    message(QMAKE_CXXFLAGS: $$QMAKE_CXXFLAGS)
} else {
#    DEFINES += NDBG
#    LIBS += -lasan
    message(RDF: $$DEFINES)
    message(QMAKE_CXXFLAGS: $$QMAKE_CXXFLAGS)
}

unix{

    DESTDIR         = $$OUT_PWD/bin
    MOC_DIR         = $$OUT_PWD/moc
    OBJECTS_DIR     = $$OUT_PWD/obj
    RCC_DIR         = $$OUT_PWD/rcc
    UI_DIR          = $$OUT_PWD/uic

    QMAKE_CLEAN += \
        Makefile \
        MOC_DIR/moc_* \
        OBJECTS_DIR/*.o \
        *.o

    #CONFIG  += link_pkgconfig
    #PKGCONFIG +=opencv4

}

SOURCES += \
        factory.cpp \
        file_create.cpp \
        file_fill.cpp \
        file_server.cpp \
        file_sort.cpp \
        keeper.cpp \
        main.cpp \
        parser_args.cpp \
        profiling.cpp \
        qqfile.cpp \
        test_factory.cpp

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

HEADERS += \
    dbg.h \
    factory.h \
    file_create.h \
    file_fill.h \
    file_server.h \
    file_sort.h \
    instance.h \
    keeper.h \
    parser_args.h \
    profiling.h \
    qqfile.h \
    test_factory.h
