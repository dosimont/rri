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

#include "eventtypeitem.h"
#ifndef PRVREGIONWRITER_H
#define PRVREGIONWRITER_H

#include <QString>
#include <QTextStream>
#include <QMap>
#include <QDebug>

#include "prvfilemanager.h"
#include "regionparser.h"
#include "eventtypeblock.h"
#include "prv_constants.h"
#include "rriroutineinfo.h"
#include "rricore.h"

class PrvRegionWriter
{
public:
    PrvRegionWriter();
    ~PrvRegionWriter();
    void setEventTypeBlockItems();
    void pushRRIRegionHeader();
    void pushRRIRegion(QString region, RRICore* core);
    void pushRRIEventTypeBlock();
    void parseRegions(QTextStream* regionStream);
    PrvFileManager *getInputPrvFile() const;
    void setInputPrvFile(PrvFileManager *value);
    PrvFileManager *getOutputPrvFile() const;
    void setOutputPrvFile(PrvFileManager *value);

protected:
    PrvFileManager* inputPrvFile;
    PrvFileManager* outputPrvFile;
    RegionParser* parser;
    QMap<QString, int> mapBaseName;
    EventTypeBlock* block;
    QMap<int,QString> routineValues;
    int routineValueCounter;


};

#endif // PRVREGIONWRITER_H
