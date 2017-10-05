#-------------------------------------------------
#
# Project created by QtCreator 2014-01-24T16:15:53
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CS490HUB
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    taskallocator.cpp \
    optaskresp.cpp \
    oppartic.cpp \
    remotecontrol.cpp \
    bid.cpp \
    task.cpp \
    team.cpp \
    cameraview.cpp \
    taskalowindow.cpp \
    errorwindow.cpp \
    communicate.c \
    communicator.cpp \
    communicatorwrapper.cpp

HEADERS  += mainwindow.h \
    taskallocator.h \
    readerthread.h \
    optaskresp.h \
    oppartic.h \
    remotecontrol.h \
    bid.h \
    team.h \
    task.h \
    cameraview.h \
    taskalowindow.h \
    errorwindow.h \
    communicate.h \
    communicator.h \
    communicatorwrapper.h

FORMS    += mainwindow.ui \
    optaskresp.ui \
    oppartic.ui \
    remotecontrol.ui \
    cameraview.ui \
    taskalowindow.ui \
    errorwindow.ui

DISTFILES += \
    tasks.txt

RESOURCES +=

