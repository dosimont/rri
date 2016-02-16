# RRI

## Dependencies

- lpaggreg library - BSC version (sources available here: https://github.com/bsc-performance-tools/lpaggreg)
- qt, qt-devel (version 5 -- do not compile with version 4)
- qmake

## Get the sources

    $ git clone https://github.com/bsc-performance-tools/RRI.git

## Go into the directory

    $ cd RRI

## Compile

*Edit* `options.pri` *to enable or disable the compilation of subsidiary functionalities and change the target directory and the dependency location*

    $ qmake-qt5
    $ make

## Install

    $ make install

## Run (command line program)

    # RRI-bin file.callerdata
