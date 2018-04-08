QT += core
QT -= gui

CONFIG += c++11

TARGET = Communicator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

DISTFILES += \
    myID.txt

SOURCES += \
    src/main.cpp \
    src/communicate.c \
    src/communicator.cpp \
    src/driver.cpp \
    src/locate.cpp \
    src/runasrobot.cpp \
    src/runasHub.cpp \

HEADERS += \
    src/communicate.h \
    src/communicator.h \
    src/args.h \
    src/driver.h \
    src/locate.h \
    src/runasrobot.h \
    src/runasHub.h \

linux-g++* {
    CONFIG += link_pkgconfig
    PKGCONFIG += playerc++
    QMAKE_CXXFLAGS += -std=c++11
    LIBS += -L../../../../../usr/lib/ -lphidget21 \
}


INCLUDEPATH += ../../../../../../usr/local/include/player-3.1/libplayerc++/ \
               ../../../../../../usr/local/include/player-3.1
DEPENDPATH += ../../../../../../usr/local/include/player-3.1/libplayerc++ \
              ../../../../../../usr/local/include/player-3.1

