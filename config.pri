#Should not be modified

include(options.pri)

VERSION = 0.0.10

PROJECT_ROOT_DIRECTORY=$$PWD
DESTDIR=$${PROJECT_ROOT_DIRECTORY}/generated_files
OBJECTS_DIR=build/obj
MOC_DIR=build/moc

CONFIG += c++11
