include(config.pri)

TEMPLATE = subdirs

QMAKE_STRIP = echo

SUBDIRS += \
           RRI-csv \

RRI-csv.subdir = src/RRI-csv

SUBDIRS += RRI-core

RRI-core.subdir = src/RRI-core
RRI-core.depends = RRI-csv

SUBDIRS += RRI-prv
RRI-prv.subdir  = src/RRI-prv
RRI-prv.depends = RRI-csv
RRI-prv.depends += RRI-core

SUBDIRS += RRI-profiling
RRI-profiling.subdir  = src/RRI-profiling
RRI-profiling.depends = RRI-csv
RRI-profiling.depends += RRI-core

equals(BUILD_BIN, true){
SUBDIRS += RRI-bin
RRI-bin.subdir  = src/RRI-bin
RRI-bin.depends = RRI-csv
RRI-bin.depends += RRI-core
RRI-bin.depends += RRI-prv
RRI-bin.depends += RRI-profiling
}

equals(BUILD_GUI, true){
SUBDIRS += RRI-gui
RRI-gui.subdir  = src/RRI-gui
RRI-gui.depends = RRI-core
}

install_R-packages.commands =  R --slave --vanilla < $$PROJECT_ROOT_DIRECTORY/scripts/rri-install.R

target_scripts.files += $$PROJECT_ROOT_DIRECTORY/scripts/rri-visualize.R
target_scripts.files += $$PROJECT_ROOT_DIRECTORY/scripts/rri-profiling.R
target_scripts.files += $$PROJECT_ROOT_DIRECTORY/scripts/rri-auto
target_scripts.files += $$PROJECT_ROOT_DIRECTORY/scripts/rri-visualize
target_scripts.files += $$PROJECT_ROOT_DIRECTORY/scripts/rri-profiling
target_scripts.path = $$PREFIX/bin
INSTALLS += target_scripts

QMAKE_CLEAN += $$QMAKE_TARGET $$DESTDIR/*
QMAKE_EXTRA_TARGETS += install_R-packages
