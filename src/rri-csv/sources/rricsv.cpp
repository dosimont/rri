#include "rricsv.h"


RRICsv::RRICsv(QTextStream* stream):stream(stream), separator(CSV_DEFAULT_SEPARATOR), line("")
{

}

RRICsv::RRICsv():separator(CSV_DEFAULT_SEPARATOR), line("")
{

}

RRICsv::RRICsv(QTextStream* stream, QChar separator):
    stream(stream), separator(separator), line("")
{

}

RRICsv::RRICsv(QChar separator):separator(separator), line("")
{

}

QChar RRICsv::getSeparator() const
{
    return separator;
}

void RRICsv::setSeparator(const QChar &value)
{
    separator = value;
}

QStringList RRICsv::readline()
{
    line=stream->readLine();
    line=line.simplified();
    return line.split(separator);
}

bool RRICsv::isEnd()
{
    return (line.compare("")==0);
}

QTextStream *RRICsv::getStream() const
{
    return stream;
}

void RRICsv::setStream(QTextStream *value)
{
    stream = value;
}
