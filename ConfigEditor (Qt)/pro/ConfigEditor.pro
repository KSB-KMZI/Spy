#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T22:39:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConfigEditor
TEMPLATE = app


SOURCES += main.cpp\
        confige.cpp \
    grabber.cpp \
    keylogger.cpp \
    screenshooter.cpp

HEADERS  += confige.h \
    grabber.h \
    keylogger.h \
    screenshooter.h

FORMS    += confige.ui \
    grabber.ui \
    keylogger.ui \
    screenshooter.ui
