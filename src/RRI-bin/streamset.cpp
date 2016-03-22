/*  RRI - Relevant Routine Identifier
*   Copyright (C) 2016  Damien Dosimont
*
*   This file is part of RRI.
*
*   RRI is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
    delete detailStream;
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

QTextStream* StreamSet::openStream(QFile *file, QString path)
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
       return RETURN_ERR_INVALID_INPUT_STREAM;
    }
    inputStream=new QTextStream(inputFile);
    return RETURN_OK;
}

int StreamSet::setOuputStreams(QString path)
{
    infoStream=openStream(infoFile, path+"/"+INFO_FILE);
    qualityStream=openStream(qualityFile, path+"/"+QUALITY_FILE);
    partitionStream=openStream(partitionFile, path+"/"+PARTITION_FILE);
    detailStream=openStream(detailFile, path+"/"+DETAIL_FILE);
    routineStream=openStream(routineFile, path+"/"+ROUTINE_FILE);
    return RETURN_OK;
    //TODO error management
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

QFile *StreamSet::getDetailFile() const
{
    return detailFile;
}

QTextStream *StreamSet::getDetailStream() const
{
    return detailStream;
}
