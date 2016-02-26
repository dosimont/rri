#-------------------------------------------------
#
# Project created by QtCreator 2016-02-03T11:53:02
#
#-------------------------------------------------
include(../../config.pri)

QT       -= gui

TARGET = rri
TEMPLATE = lib

DEFINES += CORE_LIBRARY

SOURCES += biqmap.cpp \
    microscopicmodel.cpp \
    rriobject.cpp \
    rricore.cpp \
    macroscopicmodel.cpp \
    omacroscopicmodel.cpp \
    parameters.cpp \
    part.cpp \
    redistributedmodel.cpp \
    rriredistributedmodel.cpp \
    rrimicroscopicmodel.cpp \
    rripart.cpp \
    rritimeslice.cpp \
    rriroutineinfo.cpp \
    rristreamreader.cpp

HEADERS += biqmap.h \
    microscopicmodel.h \
    rriobject.h \
    rricore.h \
    rricore_global.h \
    macroscopicmodel.h \
    omacroscopicmodel.h \
    parameters.h \
    part.h \
    debug.h \
    redistributedmodel.h \
    rrimicroscopicmodel.h \
    rriredistributedmodel.h \
    rripart.h \
    rritimeslice.h \
    rriroutineinfo.h \
    rristreamreader.h \
    core_constants.h

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
