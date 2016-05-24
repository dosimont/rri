#Should not be modified

include(options.pri)

VERSION=0.0.13

PROJECT_ROOT_DIRECTORY=$$PWD
DESTDIR=$${PROJECT_ROOT_DIRECTORY}/generated_files
OBJECTS_DIR=build/obj
MOC_DIR=build/moc

greaterThan(QT_MAJOR_VERSION, 3) {
    greaterThan(QT_MAJOR_VERSION, 4) {
        message("Using QT 5...")
        CONFIG += c++11
    }else{
        DEFINES += RRI_QT4
        message("Using QT 4...")
        message("RRI-UI feature compilation has been disabled!")
        BUILD_UI=false
        QMAKE_CXXFLAGS += -std=c++0x
        QMAKE_CXXFLAGS += -std=gnu++0x
        QMAKE_CFLAGS += -std=c++0x
        QMAKE_CFLAGS += -std=gnu++0x
        QMAKE_LFLAGS += -std=c++0x
        QMAKE_LFLAGS += -std=gnu++0x
        QMAKE_CXXFLAGS_RELEASE -= -std=gnu++98
        QMAKE_CFLAGS_RELEASE -= -std=gnu++98
    }
}else{
error(You need at least QT4 or QT5 to compile this program)
}

isEmpty( PREFIX ){
    PREFIX=/usr/local/
    message("PREFIX not defined, using default location: $$PREFIX")
}else{
    message("PREFIX : $$PREFIX")
}
isEmpty( LPAGGREG_PATH ){
    message("LPAGGREG_PATH not defined, using LD_PATH")
}else{
    message("LPAGGREG_PATH: $$LPAGGREG_PATH")
}

