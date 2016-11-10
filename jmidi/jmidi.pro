#-------------------------------------------------
#
# Project created by QtCreator 2013-12-12T09:29:54
#
#-------------------------------------------------

QT       -= gui

TARGET = jmidi
TEMPLATE = lib
CONFIG += staticlib

SOURCES += *.cpp

HEADERS += *.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

