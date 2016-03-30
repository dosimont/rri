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

#ifndef PRVFILEMANAGER_H
#define PRVFILEMANAGER_H

#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>

#include "prv_constants.h"

class PrvFileManager
{
public:
    PrvFileManager();
    ~PrvFileManager();
    int initStreams(QString prvPath, QIODevice::OpenMode mode);
    QString getPrv() const;
    QString getPcf() const;
    QString getRow() const;
    QFile *getPrvFile() const;
    QFile *getPcfFile() const;
    QFile *getRowFile() const;
    QTextStream *getPrvStream() const;
    QTextStream *getPcfStream() const;
    QTextStream *getRowStream() const;
    static int copyTrace(QString prvInputPath, QString prvOutputPath);

protected:
    QString prv;
    QString pcf;
    QString row;
    QFile* prvFile;
    QFile* pcfFile;
    QFile* rowFile;
    QTextStream* prvStream;
    QTextStream* pcfStream;
    QTextStream* rowStream;
};

#endif // PRVFILEMANAGER_H
