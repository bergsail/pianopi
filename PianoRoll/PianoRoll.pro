TEMPLATE = lib
CONFIG += plugin
QT += qml quick

DESTDIR = PianoRoll
TARGET  = pianorollplugin

OBJECTS_DIR = tmp
MOC_DIR = tmp

HEADERS += \
    roll.h \
    pianoroll.h \
    pianorollplugin.h \
    midifile.h

SOURCES += \
    roll.cpp \
    pianoroll.cpp \
    pianorollplugin.cpp \
    midifile.cpp

OTHER_FILES += \
    qmldir \
    appRoll.qml \
    pianorollplugin.qmlproject

LIBS += -L$$OUT_PWD/../jmidi/ -ljmidi
INCLUDEPATH += $$PWD/../jmidi
DEPENDPATH += $$PWD/../jmidi
PRE_TARGETDEPS += $$OUT_PWD/../jmidi/libjmidi.a

qml.files += appRoll.qml

pluginfiles.files += qmldir

qml.path += /home/pi/PianoPi
target.path += /home/pi/PianoPi \
             /home/pi/PianoPi/PianoRoll


pluginfiles.path +=/home/pi/PianoPi/PianoRoll

INSTALLS += target \
            qml \
            pluginfiles
