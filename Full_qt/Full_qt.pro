QT += gui core widgets network

TEMPLATE +=app

CONFIG += c++17 console
CONFIG -= app_bundle

QMAKE_CFLAGS    += -fsanitize=address,undefined
QMAKE_CXXFLAGS  += -fsanitize=address,undefined

unix: DEFINES += QMAKE_DATE=\\\"$$system( date "+%d.%m.%Y_%H:%M:%S" )\\\"
unix: DEFINES += QOUT_PWD=\\\"$$OUT_PWD\\\"
unix: DEFINES += QSRC_PWD=\\\"$$PWD\\\"
#unix: DEFINES += GIT_BRANCH=\\\"$$system( git rev-parse --abbrev-ref HEAD )\\\"
#unix: DEFINES += GIT_NAME=\\\"$$system( git log -1 --format=%an )\\\"
#unix: DEFINES += GIT_HASH=\\\"$$system( git log -1 --format=%h )\\\"
#unix: DEFINES += GIT_DATE=\\\"$$system( git log -1 --format=%cd )\\\"

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    $$PWD/derived/*.cpp \
    $$PWD/common/*.cpp \
    $$PWD/widgets/*.cpp \
    $$PWD/widgets/tab/*.cpp \
    $$PWD/dialog/*.cpp \
    $$PWD/network/*.cpp \
    $$PWD/handler_datagram/*.cpp \
    widgets/one/one_widget.cpp \
    gapplication.cpp \

HEADERS += \
    $$PWD/derived/*.h \
    $$PWD/common/*.h \
    $$PWD/widgets/*.h \
    $$PWD/widgets/tab/*.h \
    $$PWD/dialog/*.h \
    $$PWD/network/*.h \
    $$PWD/handler_datagram/*.h \
    widgets/one/one_widget.h \
    gapplication.h \

unix:{
    # разложим всё по полочкам и наведём порядок
    #DESTDIR     = $$OUT_PWD/bin
    MOC_DIR     = $$OUT_PWD/moc
    OBJECTS_DIR = $$OUT_PWD/obj
    RCC_DIR     = $$OUT_PWD/rcc
    UI_DIR      = $$OUT_PWD/uic

    QMAKE_CLEAN += Makefile \
    MOC_DIR/moc_*.o \
    OBJECTS_DIR/*.o

    LIBS += -lasan -lubsan
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
