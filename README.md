# RRI

## Dependencies

- lpaggreg library - BSC version (sources available here: https://github.com/bsc-performance-tools/lpaggreg)
- qt, qt-devel
- qmake

## Get the sources

    $ git clone https://github.com/bsc-performance-tools/RRI.git

## Go into the directory

    $ cd RRI

## Compile

*You can edit `options.pri` to enable or disable the compilation of subsidiary functionalities*

    $ qmake-qt4
    $ make

## Install

    # make install

## Run

    # ./bin/RRI-bin file.callerdata
