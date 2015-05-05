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

LIBS += -larmadillo
