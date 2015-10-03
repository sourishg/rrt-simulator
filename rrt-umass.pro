#-------------------------------------------------
#
# Project created by QtCreator 2015-10-02T22:08:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rrt-umass
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    renderarea.cpp \
    obstacles.cpp \
    rrt.cpp

HEADERS  += mainwindow.h \
    renderarea.h \
    obstacles.h \
    rrt.h \
    constants.h

FORMS    += mainwindow.ui
