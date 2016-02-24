include(config.pri)

TEMPLATE = subdirs

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4) {
}else{
error(You need QT5 to compile this program)
}

SUBDIRS += \
           RRI-core

RRI-core.subdir = src/RRI-core

equals(BUILD_PRV, true){
SUBDIRS += RRI-prv
RRI-prv.subdir  = src/RRI-prv
RRI-prv.depends = RRI-core
}

equals(BUILD_BIN, true){
SUBDIRS += RRI-bin
RRI-bin.subdir  = src/RRI-bin
RRI-bin.depends = RRI-core
}

equals(BUILD_GUI, true){
SUBDIRS += RRI-gui
RRI-gui.subdir  = src/RRI-gui
RRI-gui.depends = RRI-core
}

QMAKE_CLEAN += $$QMAKE_TARGET $$DESTDIR/*
