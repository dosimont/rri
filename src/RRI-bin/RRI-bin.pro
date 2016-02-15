include(../../config.pri)

QT += core
QT -= gui

CONFIG += c++11

TARGET = RRI-bin
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

unix:!macx: LIBS += -llpaggreg

unix:!macx: LIBS += -L$$DESTDIR -lrri

INCLUDEPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core
DEPENDPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core

unix {
    target.path = /usr/local/bin
    INSTALLS += target
}
