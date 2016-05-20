include(../../config.pri)

QT += core
QT -= gui

TARGET = rri
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    RRI-bin.cpp \
    argumentmanager.cpp \
    filemanager.cpp \
    streamset.cpp

unix:!macx: LIBS += -L$$DESTDIR -lrri-csv
INCLUDEPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-csv
DEPENDPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-csv

unix:!macx: LIBS += -L$$DESTDIR -lrri
INCLUDEPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core
DEPENDPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-core

unix:!macx: LIBS += -L$$DESTDIR -lrri-prv
INCLUDEPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-prv
DEPENDPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-prv

unix:!macx: LIBS += -L$$DESTDIR -lrri-profiling
INCLUDEPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-profiling
DEPENDPATH += $$PROJECT_ROOT_DIRECTORY/src/RRI-profiling

QMAKE_LFLAGS += '-Wl,-rpath,\'\$$ORIGIN/../lib\''

unix:!macx: LIBS += -llpaggreg
isEmpty( LPAGGREG_PATH ){
} else {
unix:!macx: LIBS +=-L$$LPAGGREG_PATH/lib
INCLUDEPATH += $$LPAGGREG_PATH/include
QMAKE_LFLAGS += -Wl,-rpath,$$LPAGGREG_PATH/lib
}

unix {
    target.path = $$PREFIX/bin
    INSTALLS += target
}

HEADERS += \
    argumentmanager.h \
    filemanager.h \
    streamset.h \
    bin_constants.h

