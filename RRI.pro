include(config.pri)
include(options.pri)

TEMPLATE = subdirs

SUBDIRS += \
           RRI-core

RRI-core.subdir = src/RRI-core

equals(BUILD_UI, true){
SUBDIRS += RRI-ui
RRI-ui.subdir  = src/RRI-ui
RRI-ui.depends = RRI-core
}
