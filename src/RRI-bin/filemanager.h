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

#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QVector>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include "argumentmanager.h"
#include "streamset.h"
#include "bin_constants.h"
#include "prvfilemanager.h"



class FileManager
{
public:
    FileManager(ArgumentManager* argumentManager);
    ~FileManager();
    QVector<QString> getIterationNames() const;
    ArgumentManager *getArgumentManager() const;
    QVector<QString> getCallerDataFileNames() const;
    QString getInputDir() const;
    QString getOutputDir() const;
    QVector<StreamSet *> getStreamSets() const;
    PrvFileManager *getInputPrvFiles() const;
    PrvFileManager *getOutputPrvFiles() const;
    QTextStream *getRegionStream() const;
    int init();

protected:
    int mkoutputDir();
    int set();
    QString inputDir;
    QString outputDir;
    QString regions;
    QFile* regionFile;
    QTextStream* regionStream;
    QVector<QString> callerDataFileNames;
    QVector<QString> iterationNames;
    QVector<StreamSet*> streamSets;
    PrvFileManager* inputPrvFiles;
    PrvFileManager* outputPrvFiles;
    ArgumentManager* argumentManager;
};

#endif // FILEMANAGER_H
