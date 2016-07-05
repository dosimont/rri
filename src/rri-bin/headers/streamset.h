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

#ifndef STREAMSET_H
#define STREAMSET_H

#include <QTextStream>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include "bin_constants.h"

class StreamSet
{
public:
    StreamSet();
    ~StreamSet();

    void close();
    int setOuputStreams(QString path);
    int openFile(QFile* file, QString path);
    QTextStream *openStream(QFile* file, QString path);
    int setInputStream(QString path);
    QTextStream *getInfoStream() const;
    QTextStream *getQualityStream() const;
    QTextStream *getPartitionStream() const;
    QTextStream *getRoutineStream() const;
    QTextStream *getDetailStream() const;
    QTextStream *getInputStream() const;
    QFile *getInputFile() const;
    QFile *getInfoFile() const;
    QFile *getDetailFile() const;
    QFile *getQualityFile() const;
    QFile *getPartitionFile() const;
    QFile *getRoutineFile() const;


private:
    QTextStream* inputStream;
    QTextStream* infoStream;
    QTextStream* qualityStream;
    QTextStream* partitionStream;
    QTextStream* detailStream;
    QTextStream* routineStream;
    QFile* inputFile;
    QFile* infoFile;
    QFile* detailFile;
    QFile* qualityFile;
    QFile* partitionFile;
    QFile* routineFile;
};

#endif // STREAMSET_H
