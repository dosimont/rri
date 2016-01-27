#-------------------------------------------------
#
# Project created by QtCreator 2016-01-26T16:06:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = RRI
TEMPLATE = app

INCLUDEPATH = .


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    csv.cpp \
    core.cpp \
    microscopicmodel.cpp \
    rrimodel.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    csv.h \
    core.h \
    constants.h \
    microscopicmodel.h \
    rrimodel.h

FORMS    += mainwindow.ui
