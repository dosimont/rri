#include "rristreamreader.h"

RRIStreamReader::RRIStreamReader(QTextStream stream):stream(stream), line("")
{

}

RRIStreamReader::RRIStreamReader():separator(CSV_RRI_SEPARATOR), line("")
{

}

RRIStreamReader::RRIStreamReader(QTextStream stream, QChar separator):
    stream(stream), separator(separator), line("")
{

}

RRIStreamReader::RRIStreamReader(QChar separator):separator(separator), line("")
{

}

QTextStream RRIStreamReader::getStream() const
{
    return stream;
}

void RRIStreamReader::setStream(const QTextStream &value)
{
    stream = value;
}

QChar RRIStreamReader::getSeparator() const
{
    return separator;
}

void RRIStreamReader::setSeparator(const QChar &value)
{
    separator = value;
}

QStringList RRIStreamReader::readline()
{
    line=stream.readLine();
    line=line.simplified();
    return line.split(separator);
}

bool RRIStreamReader::isEnd()
{
    return (line.compare("")==0);
}


