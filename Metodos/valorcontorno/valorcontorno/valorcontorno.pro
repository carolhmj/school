#-------------------------------------------------
#
# Project created by QtCreator 2015-06-29T22:31:40
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = auto
CONFIG   += console
CONFIG   -= app_bundle
CONFIG   += c++11

TEMPLATE = app


SOURCES += main.cpp \
    diferencafinita.cpp

LIBS += -larmadillo

HEADERS += \
    diferencafinita.h

QMAKE_CXXFLAGS += -g

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib64/release/ -larmadillo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib64/debug/ -larmadillo
else:unix: LIBS += -L$$PWD/../../../../../../../usr/lib64/ -larmadillo

INCLUDEPATH += $$PWD/../../../../../../../usr/lib64
DEPENDPATH += $$PWD/../../../../../../../usr/lib64
