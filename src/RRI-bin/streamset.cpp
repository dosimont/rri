#include "streamset.h"

StreamSet::StreamSet(): infoStream(new QTextStream()),
                        qualityStream(new QTextStream()),
                        partitionStream(new QTextStream()),
                        routineStream(new QTextStream())
{

}

StreamSet::~StreamSet()
{
    delete infoStream;
    delete qualityStream;
    delete partitionStream;
    delete routineStream;
}

StreamSet::close()
{
    infoFile.close();
    qualityFile.close();
    partitionFile.close();
    routineFile.close();
}

int StreamSet::setStream(QTextStream *stream, QFile file, QString path)
{
    file(path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)){
       return 1;
    }
    stream(&file);
    return 0;
}

int StreamSet::setStreams(QString path)
{
    setStream(infoStream, infoFile, path+"/"+INFO_FILE);
    setStream(qualityStream, qualityFile, path+"/"+QUALITY_FILE);
    setStream(partitionStream, partitionFile, path+"/"+PARTITION_FILE);
    setStream(routineStream, routineFile, path+"/"+ROUTINE_FILE);

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
