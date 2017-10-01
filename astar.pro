#-------------------------------------------------
#
# Project created by QtCreator 2016-01-25T14:35:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = astar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    astar.cpp \
    graphicsviewdisplay.cpp \
    graphicsdisplayicon.cpp \
    pathitem.cpp

HEADERS  += mainwindow.h \
    astar.h \
    graphicsviewdisplay.h \
    graphicsdisplayicon.h \
    pathitem.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
