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

    int setStreams(QString path);

    int setStream(QTextStream *stream, QFile file, QString path);

    QTextStream *getInfoStream() const;

    QTextStream *getQualityStream() const;

    QTextStream *getPartitionStream() const;

    QTextStream *getRoutineStream() const;

private:
    QTextStream* infoStream;
    QTextStream* qualityStream;
    QTextStream* partitionStream;
    QTextStream* routineStream;
    QTextStream infoFile;
    QTextStream qualityFile;
    QTextStream partitionFile;
    QTextStream routineFile;
};

#endif // STREAMSET_H
