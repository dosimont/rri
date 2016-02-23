#-------------------------------------------------
#
# Project created by QtCreator 2016-02-03T11:54:17
#
#-------------------------------------------------
include(../../config.pri)

QT       += core gui

QT += widgets printsupport

TARGET = RRI-gui
TEMPLATE = app


SOURCES +=\
        mainwindow.cpp \
    qcustomplot.cpp \
    RRI-gui.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h

FORMS    += mainwindow.ui

unix:!macx: LIBS += -L$$DESTDIR -lrri
INCLUDEPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core
DEPENDPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core

unix:!macx: LIBS += -llpaggreg
isEmpty(LPAGGREG_PATH){
} else {
unix:!macx: LIBS +=-L$$LPAGGREG_PATH/lib
INCLUDEPATH += $$LPAGGREG_PATH/include
}

unix {
    target.path = $$TARGET_PATH/bin
    INSTALLS += target
}
