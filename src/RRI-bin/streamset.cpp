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
    delete infoFile;
    delete qualityFile;
    delete partitionFile;
    delete routineFile;
    delete inputFile;
}

void StreamSet::close()
{
    /*infoFile->close();
    qualityFile->close();
    partitionFile->close();
    routineFile->close();
    inputFile->close();*/
}

QTextStream * StreamSet::setOutputStream(QFile *file, QString path)
{
    file = new QFile(path);
    if (!file->open(QIODevice::ReadWrite | QIODevice::Text)){
       return new QTextStream();
    }
    return new QTextStream(file);
}

int StreamSet::setInputStream(QString path)
{
    inputFile = new QFile(path);
    if (!inputFile->open(QIODevice::ReadOnly | QIODevice::Text)){
       return 1;
    }
    inputStream=new QTextStream(inputFile);
    return 0;
}

int StreamSet::setOuputStreams(QString path)
{
    infoStream=setOutputStream(infoFile, path+"/"+INFO_FILE);
    qualityStream=setOutputStream(qualityFile, path+"/"+QUALITY_FILE);
    partitionStream=setOutputStream(partitionFile, path+"/"+PARTITION_FILE);
    routineStream=setOutputStream(routineFile, path+"/"+ROUTINE_FILE);
    return 0;
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

QFile *StreamSet::getInputFile() const
{
    return inputFile;
}

QFile *StreamSet::getInfoFile() const
{
    return infoFile;
}

QFile *StreamSet::getQualityFile() const
{
    return qualityFile;
}

QFile *StreamSet::getPartitionFile() const
{
    return partitionFile;
}

QFile *StreamSet::getRoutineFile() const
{
    return routineFile;
}
