#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T10:55:45
#
#-------------------------------------------------
include(../../config.pri)

QT       -= gui

TARGET = rri-profiling
TEMPLATE = lib

DEFINES += RRIPROFILING_LIBRARY

SOURCES += \
    statsparser.cpp \
    stats.cpp \
    slopeparser.cpp \
    slope.cpp \
    routineprofile.cpp \
    rriprofiling.cpp

HEADERS +=\
        rri-profiling_global.h \
    profiling_constants.h \
    statsparser.h \
    stats.h \
    slopeparser.h \
    slope.h \
    routineprofile.h \
    rriprofiling.h

unix:!macx: LIBS += -L$$DESTDIR -lrri
INCLUDEPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core
DEPENDPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core

unix:!macx: LIBS += -L$$DESTDIR -lrri-csv
INCLUDEPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-csv
DEPENDPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-csv

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
