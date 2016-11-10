TEMPLATE = app
QT+= quick

DESTDIR = bin
TARGET = pp

OBJECTS_DIR = tmp
MOC_DIR = tmp

SOURCES += \
    main.cpp \
    poc_utils.cpp \
    poc_qmlutils.cpp

HEADERS += \
    poc_utils.h \
    poc_qmlutils.h

OTHER_FILES += *.qml \
    qml/*.qml \
    plugin.sh \
    qml/*.js


qml.files +=\
      qml/*.qml \
      qml/*.js
plugin.files+= \
      plugin.sh

target.path += /home/pi/PianoPi
qml.path += /home/pi/PianoPi/qml
plugin.path+= /home/pi/PianoPi

INSTALLS += \
       target \
       qml \
       plugin
