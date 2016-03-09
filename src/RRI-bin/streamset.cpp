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

int StreamSet::setOutputStream(QFile *file, QString path, QTextStream *stream)
{
    file = new QFile(path);
    if (!file->open(QIODevice::ReadWrite | QIODevice::Text)){
       return RETURN_ERR_INVALID_OUTPUT_STREAM;
    }
    stream = new QTextStream(file);
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
    error=setOutputStream(infoFile, path+"/"+INFO_FILE, infoStream);
    if (error!=RETURN_OK){
        return error;
    }
    error=setOutputStream(qualityFile, path+"/"+QUALITY_FILE, qualityStream);
    if (error!=RETURN_OK){
        return error;
    }
    error=setOutputStream(partitionFile, path+"/"+PARTITION_FILE, partitionStream);
    if (error!=RETURN_OK){
        return error;
    }
    error=setOutputStream(routineFile, path+"/"+ROUTINE_FILE, routineStream);
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
