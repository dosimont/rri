include(config.pri)

TEMPLATE = subdirs

SUBDIRS += \
           RRI-core

RRI-core.subdir = src/RRI-core

equals(BUILD_UI, true){
SUBDIRS += RRI-ui
RRI-ui.subdir  = src/RRI-ui
RRI-ui.depends = RRI-core
}

equals(BUILD_BIN, true){
SUBDIRS += RRI-bin
RRI-bin.subdir  = src/RRI-bin
RRI-bin.depends = RRI-core
}
