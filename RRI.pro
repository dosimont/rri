TEMPLATE = subdirs

SUBDIRS += \
           RRI-core \
           RRI-ui

 RRI-core.subdir = src/RRI-core
 RRI-ui.subdir  = src/RRI-ui

 RRI-ui.depends = RRI-core

include(config.pri)
