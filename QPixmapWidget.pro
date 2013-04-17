#-------------------------------------------------
#
# Project created by QtCreator 2013-04-17T11:43:43
#
#-------------------------------------------------

QT       += widgets

#QT       -= gui

TARGET = QPixmapWidget
TEMPLATE = lib

# choose between dll(shared) and staticlib(static)
CONFIG += dll
#CONFIG += staticlib
dll {
DEFINES += QPIXMAPWIDGET_LIBRARY
}
staticlib {
DEFINES += QPIXMAPWIDGET_STATIC
}

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
    QPixmapWidget.pri \
    LICENSE.LGPL
