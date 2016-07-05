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
#include "regionparser.h"

RegionParser::RegionParser()
{

}

RegionParser::~RegionParser()
{
    for (Region* region:regionMap.values()){
        delete region;
    }
}

void RegionParser::buildRegions(QTextStream* stream)
{
    RRICsv streamReader=RRICsv(stream, ';');
    QStringList stringList;
    //header
    streamReader.readline();
    for (stringList=streamReader.readline();!streamReader.isEnd();stringList=streamReader.readline()){
        Region* region=buildRegion(stringList);
        regionMap.insert(region->getName(), region);
    }
}

Region *RegionParser::buildRegion(QStringList stringList)
{
    Region* region=new Region();
    region->setName(stringList[CSV_REGION_NAME]);
    region->setApplication(stringList[CSV_REGION_APPL]);
    region->setTask(stringList[CSV_REGION_TASK]);
    region->setProcess(stringList[CSV_REGION_TASK]);
    region->setThread(stringList[CSV_REGION_THREAD]);
    region->setStart(stringList[CSV_REGION_START]);
    region->setEnd(stringList[CSV_REGION_END]);
    return region;
}

QMap<QString, Region *> RegionParser::getRegionMap() const
{
    return regionMap;
}
