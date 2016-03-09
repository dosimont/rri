#include "streamset.h"

StreamSet::StreamSet()
{

}

StreamSet::~StreamSet()
{
    /*delete infoFile;
    delete qualityFile;
    delete partitionFile;
    delete routineFile;
    delete inputFile;*/
    delete infoStream;
    delete qualityStream;
    delete partitionStream;
    delete routineStream;
    delete inputStream;
}

void StreamSet::close()
{
}

int StreamSet::openFile(QFile *file, QString path)
{
    file = new QFile(path);
    if (!file->open(QIODevice::ReadWrite | QIODevice::Text)){
       return RETURN_ERR_INVALID_OUTPUT_STREAM;
    }
    return RETURN_OK;
}

int StreamSet::setInputStream(QString path)
{
    inputFile = new QFile(path);
    if (!inputFile->open(QIODevice::ReadOnly | QIODevice::Text)){
       return RETURN_ERR_INVALID_INPUT_STREAM;
    }
    inputStream=new QTextStream(inputFile);
    return RETURN_OK;
}

int StreamSet::setOuputStreams(QString path)
{
    int error;
    error=openFile(infoFile, path+"/"+INFO_FILE);
    if (error!=RETURN_OK){
        return error;
    }
    infoStream= new QTextStream(infoFile);
    error=openFile(qualityFile, path+"/"+QUALITY_FILE);
    if (error!=RETURN_OK){
        return error;
    }
    qualityStream= new QTextStream(qualityFile);
    error=openFile(partitionFile, path+"/"+PARTITION_FILE);
    if (error!=RETURN_OK){
        return error;
    }
    partitionStream= new QTextStream(partitionFile);
    error=openFile(routineFile, path+"/"+ROUTINE_FILE);
    routineStream= new QTextStream(routineFile);
    return error;
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
