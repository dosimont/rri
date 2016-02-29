#include "streamset.h"

StreamSet::StreamSet()
{

}

StreamSet::~StreamSet()
{
    delete infoStream;
    delete qualityStream;
    delete partitionStream;
    delete routineStream;
    delete inputStream;
}

StreamSet::close()
{
    infoFile.close();
    qualityFile.close();
    partitionFile.close();
    routineFile.close();
    inputFile.close();
}

int StreamSet::setOutputStream(QTextStream *stream, QFile file, QString path)
{
    file(path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
       return 1;
    }
    stream=new QTextStream(&file);
    return 0;
}

int StreamSet::setInputStream(QString path)
{
    inputFile(path);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)){
       return 1;
    }
    inputStream=new QTextStream(&inputFile);
    return 0;
}

int StreamSet::setOuputStreams(QString path)
{
    setOutputStream(infoStream, infoFile, path+"/"+INFO_FILE);
    setOutputStream(qualityStream, qualityFile, path+"/"+QUALITY_FILE);
    setOutputStream(partitionStream, partitionFile, path+"/"+PARTITION_FILE);
    setOutputStream(routineStream, routineFile, path+"/"+ROUTINE_FILE);

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

QTextStream *StreamSet::getInputStream() const
{
    return inputStream;
}
