#-------------------------------------------------
#
# Project created by QtCreator 2013-04-17T11:43:43
#
#-------------------------------------------------

QT       += widgets

#QT       -= gui

TARGET = qpixmapwidget
TEMPLATE = lib staticlib

SOURCES += \
    src/qpixmapwidget.cpp

HEADERS += \
    src/qpixmapwidget.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    qpixmapwidget.pri \
    LICENSE.LGPL
