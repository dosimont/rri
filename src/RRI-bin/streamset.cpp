#include "streamset.h"

StreamSet::StreamSet()
{

}

StreamSet::close()
{
    infoStream->
}

int StreamSet::setStream(QTextStream *stream, QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
       return 1;
    }
    stream(&file);
    return 0;
}

int StreamSet::setStreams(QString input, QString path)
{
    QString qualityString = path +"/quality.csv";
    QFile qualityFile(qualityString);
    if (!qualityFile.open(QIODevice::ReadWrite | QIODevice::Text)){
       return 3;
    }
    qualityFile.close();
    QString p = path +"/partitions.csv";
    QFile pFile(p);
    if (!pFile.open(QIODevice::ReadWrite | QIODevice::Text)){
       return 3;
    }
    QString codelines = path +"/codelines.csv";
    QFile codelinesFile(codelines);
    if (!codelinesFile.open(QIODevice::ReadWrite | QIODevice::Text)){
       return 3;
    }
    QString info = path +"/info.csv";
    QFile infoFile(info);
    if (!infoFile.open(QIODevice::ReadWrite | QIODevice::Text)){
       return 3;
    }
    QTextStream inputStream(&inputFile);
    QTextStream qualityStream(&qualityFile);
    QTextStream pStream(&pFile);
    QTextStream codelinesStream(&codelinesFile);
    QTextStream infoStream(&infoFile);
}

QTextStream *StreamSet::getInfoStream() const
{
    return infoStream;
}

QTextStream *StreamSet::getQualityStream() const
{
    return qualityStream;
}

QTextStream *StreamSet::getPartitionStream() const
{
    return partitionStream;
}

QTextStream *StreamSet::getRoutineStream() const
{
    return routineStream;
}

QTextStream StreamSet::getInputStream() const
{
    return inputStream;
}

QTextStream StreamSet::getInfoStream() const
{
    return infoStream;
}

QTextStream StreamSet::getQualityStream() const
{
    return qualityStream;
}

QTextStream StreamSet::getPartitionStream() const
{
    return partitionStream;
}

QTextStream StreamSet::getRoutineStream() const
{
    return routineStream;
}
