#-------------------------------------------------
#
# Project created by QtCreator 2016-02-24T17:31:35
#
#-------------------------------------------------
include(../../config.pri)


QT       -= gui

TARGET = rri-prv
TEMPLATE = lib

DEFINES += RRIPRV_LIBRARY

SOURCES += rriprv.cpp

HEADERS += rriprv.h\
        rri-prv_global.h

unix:!macx: LIBS += -L$$DESTDIR -lrri
INCLUDEPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core
DEPENDPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core

unix:!macx: LIBS += -llpaggreg
isEmpty( LPAGGREG_PATH ){
} else {
unix:!macx: LIBS +=-L$$LPAGGREG_PATH/lib
INCLUDEPATH += $$LPAGGREG_PATH/include
}

QMAKE_RPATHDIR += $$INCLUDEPATH

unix {
    target.path = $$TARGET_PATH/lib
    header_files.files = $$HEADERS
    header_files.path = $$TARGET_PATH/include/$$TARGET
    INSTALLS += target \
                header_files
}
