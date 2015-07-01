#-------------------------------------------------
#
# Project created by QtCreator 2015-04-23T19:20:54
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
    autovalvec.cpp

HEADERS += \
    autovalvec.h

LIBS += -larmadillo -llapack -lblas

QMAKE_CXXFLAGS += -g

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib64/release/ -larmadillo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../../usr/lib64/debug/ -larmadillo
else:unix: LIBS += -L$$PWD/../../../../../../../usr/lib64/ -larmadillo

INCLUDEPATH += $$PWD/../../../../../../../usr/lib64
DEPENDPATH += $$PWD/../../../../../../../usr/lib64
