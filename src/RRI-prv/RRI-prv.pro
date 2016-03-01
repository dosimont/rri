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

SOURCES += rriprv.cpp \
    prvfilemanager.cpp \
    eventtypeblock.cpp \
    eventtypeitem.cpp \
    eventtypevalue.cpp \
    regionparser.cpp \
    region.cpp \
    prvregionwriter.cpp

HEADERS += rriprv.h\
        rri-prv_global.h \
    prvfilemanager.h \
    prv_constants.h \
    eventtypeblock.h \
    eventtypeitem.h \
    eventtypevalue.h \
    regionparser.h \
    region.h \
    prvregionwriter.h

unix:!macx: LIBS += -L$$DESTDIR -lrri
INCLUDEPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core
DEPENDPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core

QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/../lib\''

unix:!macx: LIBS += -llpaggreg
isEmpty( LPAGGREG_PATH ){
} else {
unix:!macx: LIBS +=-L$$LPAGGREG_PATH/lib
INCLUDEPATH += $$LPAGGREG_PATH/include
QMAKE_LFLAGS += -Wl,-rpath,$$LPAGGREG_PATH/lib
}

unix {
    target.path = $$TARGET_PATH/lib
    header_files.files = $$HEADERS
    header_files.path = $$TARGET_PATH/include/$$TARGET
    INSTALLS += target \
                header_files
}
