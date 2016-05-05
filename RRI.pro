include(config.pri)

TEMPLATE = subdirs

greaterThan(QT_MAJOR_VERSION, 4) {
}else{
error(You need QT5 to compile this program)
}

SUBDIRS += \
           RRI-csv

RRI-csv.subdir = src/RRI-csv

SUBDIRS += RRI-core

RRI-core.subdir = src/RRI-core
RRI-core.depends = RRI-csv

SUBDIRS += RRI-prv
RRI-prv.subdir  = src/RRI-prv
RRI-prv.depends = RRI-csv
RRI-prv.depends += RRI-core

equals(BUILD_BIN, true){
SUBDIRS += RRI-bin
RRI-bin.subdir  = src/RRI-bin
RRI-bin.depends = RRI-core
RRI-bin.depends += RRI-prv
}

equals(BUILD_GUI, true){
SUBDIRS += RRI-gui
RRI-gui.subdir  = src/RRI-gui
RRI-gui.depends = RRI-core
}

QMAKE_CLEAN += $$QMAKE_TARGET $$DESTDIR/*
