#-------------------------------------------------
#
# Project created by QtCreator 2016-02-03T11:53:02
#
#-------------------------------------------------

QT       -= gui

TARGET = RRI-core
TEMPLATE = lib

DEFINES += CORE_LIBRARY

SOURCES += biqmap.cpp \
    csv.cpp \
    microscopicmodel.cpp \
    rrimodel.cpp \
    rriobject.cpp \
    rricore.cpp

HEADERS += biqmap.h \
    csv.h \
    microscopicmodel.h \
    rrimodel.h \
    rriobject.h \
    rricore.h \
    constants.h \
    rricore_global.h

unix {
    target.path = /usr/lib
    header_files.files = $$HEADERS
    header_files.path = usr/incude/$$TARGET
    INSTALLS += target \
                header_files
}
