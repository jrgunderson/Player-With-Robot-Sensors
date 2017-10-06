QT += core
QT -= gui

CONFIG += c++11

TARGET = Communicator
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    communicate.c \
    communicator.cpp \
    locate.cpp \
    driver.cpp

HEADERS += \
    communicate.h \
    communicator.h \ args.h \
    locate.h \
    driver.h

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
