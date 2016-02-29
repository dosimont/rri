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

    close();

    int setOuputStreams(QString path);

    int setOutputStream(QTextStream *stream, QFile file, QString path);

    int setInputStream(QString path);

    QTextStream *getInfoStream() const;

    QTextStream *getQualityStream() const;

    QTextStream *getPartitionStream() const;

    QTextStream *getRoutineStream() const;

    QTextStream *getInputStream() const;

private:
    QTextStream* inputStream;
    QTextStream* infoStream;
    QTextStream* qualityStream;
    QTextStream* partitionStream;
    QTextStream* routineStream;
    QTextStream inputFile;
    QTextStream infoFile;
    QTextStream qualityFile;
    QTextStream partitionFile;
    QTextStream routineFile;
};

#endif // STREAMSET_H
