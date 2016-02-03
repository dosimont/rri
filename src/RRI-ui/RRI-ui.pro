#-------------------------------------------------
#
# Project created by QtCreator 2016-02-03T11:54:17
#
#-------------------------------------------------
include(../../config.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = RRI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui

unix {
    target.path = /usr/local/bin
    INSTALLS += target
}
