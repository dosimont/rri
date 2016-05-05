#-------------------------------------------------
#
# Project created by QtCreator 2016-05-05T09:39:33
#
#-------------------------------------------------

QT       -= gui

TARGET = rri-csv
TEMPLATE = lib

DEFINES += RRICSV_LIBRARY

SOURCES += rricsv.cpp

HEADERS += rricsv.h\
        rri-csv_global.h \
    csv_constants.h


QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/../lib\''

unix {
    target.path = $$TARGET_PATH/lib
    header_files.files = $$HEADERS
    header_files.path = $$TARGET_PATH/include/$$TARGET
    INSTALLS += target \
                header_files
}
