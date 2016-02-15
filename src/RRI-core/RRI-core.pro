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
    csv.cpp \
    microscopicmodel.cpp \
    rrimodel.cpp \
    rriobject.cpp \
    rricore.cpp \
    macroscopicmodel.cpp \
    omacroscopicmodel.cpp \
    parameters.cpp \
    part.cpp

HEADERS += biqmap.h \
    csv.h \
    microscopicmodel.h \
    rrimodel.h \
    rriobject.h \
    rricore.h \
    constants.h \
    rricore_global.h \
    macroscopicmodel.h \
    omacroscopicmodel.h \
    parameters.h \
    part.h \
    debug.h

unix {
    target.path = $$TARGET_PATH/lib
    header_files.files = $$HEADERS
    header_files.path = $$TARGET_PATH/include/$$TARGET
    INSTALLS += target \
                header_files
}


unix:!macx: LIBS += -L$$LPAGGREG_PATH/lib -llpaggreg
INCLUDEPATH += $$LPAGGREG_PATH/include

QMAKE_CLEAN += $(TARGET) $(QMAKE_TARGET)
