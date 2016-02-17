include(../../config.pri)

QT += core
QT -= gui

CONFIG += c++11

TARGET = RRI-bin
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    RRI-bin.cpp

unix:!macx: LIBS += -L$$DESTDIR -lrri
INCLUDEPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core
DEPENDPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core

unix:!macx: LIBS += -llpaggreg
isEmpty($$LPAGGREG_PATH){
} else {
unix:!macx: LIBS +=-L$$LPAGGREG_PATH/lib
INCLUDEPATH += $$LPAGGREG_PATH/include
}

unix {
    target.path = $$TARGET_PATH/bin
    INSTALLS += target
}

