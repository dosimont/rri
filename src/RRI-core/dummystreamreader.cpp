/*  RRI - Relevant Routine Identifier
*  Copyright (C) 2016  Damien Dosimont
*  
*  This file is part of RRI.
*  
*  RRI is free software: you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation, either version 3 of the License, or
*  (at your option) any later version.
*  
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*  
*  You should have received a copy of the GNU General Public License
*  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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


