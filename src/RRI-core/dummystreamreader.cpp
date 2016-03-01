#include "dummystreamreader.h"

DummyStreamReader::DummyStreamReader(QTextStream* stream):stream(stream), separator(CSV_DEFAULT_SEPARATOR), line("")
{

}

DummyStreamReader::DummyStreamReader():separator(CSV_DEFAULT_SEPARATOR), line("")
{

}

DummyStreamReader::DummyStreamReader(QTextStream* stream, QChar separator):
    stream(stream), separator(separator), line("")
{

}

DummyStreamReader::DummyStreamReader(QChar separator):separator(separator), line("")
{

}

QChar DummyStreamReader::getSeparator() const
{
    return separator;
}

void DummyStreamReader::setSeparator(const QChar &value)
{
    separator = value;
}

QStringList DummyStreamReader::readline()
{
    line=stream->readLine();
    line=line.simplified();
    return line.split(separator);
}

bool DummyStreamReader::isEnd()
{
    return (line.compare("")==0);
}

QTextStream *DummyStreamReader::getStream() const
{
    return stream;
}

void DummyStreamReader::setStream(QTextStream *value)
{
    stream = value;
}


