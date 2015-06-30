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

QMAKE_CXXFLAGS += -g

HEADERS += \
    diferencafinita.h
