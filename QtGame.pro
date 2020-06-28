#-------------------------------------------------
#
# Project created by QtCreator 2013-08-22T22:46:33
#
#-------------------------------------------------

QT       += core gui multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtGame
TEMPLATE = app


SOURCES += main.cpp\
    tower.cpp \
    waypoint.cpp \
    enemy.cpp \
    bullet.cpp \
    musicplayer.cpp \
    function.cpp \
    mainwidget.cpp \
    gamewidgeta.cpp \
    gamewidgetb.cpp \
    towerbase.cpp


HEADERS  +=  \
    tower.h \
    enemy.h \
    bullet.h \
    musicplayer.h \
    function.h \
    mainwidget.h \
    gamewidgeta.h \
    gamewidgetb.h \
    towerbase.h \
    turnpoint.h


FORMS    +=  \
    mainwidget.ui \
    gamewidgetb.ui

RESOURCES += \
    resource.qrc
