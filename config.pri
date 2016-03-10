include(options.pri)

#Should not be modified

VERSION = 0.0.5

PROJECT_ROOT_DIRECTORY=$$PWD
DESTDIR=$${PROJECT_ROOT_DIRECTORY}/generated_files
OBJECTS_DIR=build/obj
MOC_DIR=build/moc

CONFIG += c++11
