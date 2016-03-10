#ifndef STREAMSET_H
#define STREAMSET_H

#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include "bin_constants.h"

class StreamSet
{
public:
    StreamSet();
    ~StreamSet();

    void close();
    int setOuputStreams(QString path);
    int openFile(QFile* file, QString path);
    QTextStream *openStream(QFile* file, QString path);
    int setInputStream(QString path);
    QTextStream *getInfoStream() const;
    QTextStream *getQualityStream() const;
    QTextStream *getPartitionStream() const;
    QTextStream *getRoutineStream() const;
    QTextStream *getDetailStream() const;
    QTextStream *getInputStream() const;
    QFile *getInputFile() const;
    QFile *getInfoFile() const;
    QFile *getDetailFile() const;
    QFile *getQualityFile() const;
    QFile *getPartitionFile() const;
    QFile *getRoutineFile() const;


private:
    QTextStream* inputStream;
    QTextStream* infoStream;
    QTextStream* qualityStream;
    QTextStream* partitionStream;
    QTextStream* detailStream;
    QTextStream* routineStream;
    QFile* inputFile;
    QFile* infoFile;
    QFile* detailFile;
    QFile* qualityFile;
    QFile* partitionFile;
    QFile* routineFile;
};

#endif // STREAMSET_H
