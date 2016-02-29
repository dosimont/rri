#ifndef STREAMSET_H
#define STREAMSET_H

#include <QTextStream>
#include <QFile>

#include "bin_constants.h"

class StreamSet
{
public:
    StreamSet();
    ~StreamSet();

    void close();

    int setOuputStreams(QString path);

    QTextStream* setOutputStream(QFile *file, QString path);

    int setInputStream(QString path);

    QTextStream *getInfoStream() const;

    QTextStream *getQualityStream() const;

    QTextStream *getPartitionStream() const;

    QTextStream *getRoutineStream() const;

    QTextStream *getInputStream() const;

    QFile *getInputFile() const;

    QFile *getInfoFile() const;

    QFile *getQualityFile() const;

    QFile *getPartitionFile() const;

    QFile *getRoutineFile() const;

private:
    QTextStream* inputStream;
    QTextStream* infoStream;
    QTextStream* qualityStream;
    QTextStream* partitionStream;
    QTextStream* routineStream;
    QFile* inputFile;
    QFile* infoFile;
    QFile* qualityFile;
    QFile* partitionFile;
    QFile* routineFile;
};

#endif // STREAMSET_H
