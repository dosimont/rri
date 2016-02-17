include(config.pri)

TEMPLATE = subdirs

SUBDIRS += \
           RRI-core

RRI-core.subdir = src/RRI-core

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

unix {
    target.path = $$TARGET_PATH/bin
    INSTALLS += $$PROJECT_ROOT_DIRECTORY/scripts/rri.R
    INSTALLS += $$PROJECT_ROOT_DIRECTORY/scripts/rri.sh
    INSTALLS += $$PROJECT_ROOT_DIRECTORY/scripts/rri
}

QMAKE_CLEAN += $$QMAKE_TARGET $$DESTDIR\*
