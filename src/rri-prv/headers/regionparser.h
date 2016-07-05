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

#ifndef REGIONPARSER_H
#define REGIONPARSER_H

#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QDebug>

#include "region.h"
#include "rricsv.h"
#include "prv_constants.h"

class RegionParser
{
public:
    RegionParser();
    ~RegionParser();
    void buildRegions(QTextStream* stream);
    QMap<QString, Region *> getRegionMap() const;

protected:
    Region* buildRegion(QStringList stringList);
    QMap<QString, Region*> regionMap;

};

#endif // REGIONPARSER_H
