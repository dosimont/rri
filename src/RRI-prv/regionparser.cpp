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
    DummyStreamReader streamReader=new DummyStreamReader(stream);
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
    region->setTask(stringList[CSV_REGION_TASK);
    region->setThread(stringList[CSV_REGION_THREAD]);
    region->setStart(stringList[CSV_REGION_START]);
    region->setEnd(stringList[CSV_REGION_END]);
    return region;
}

QMap<QString, Region *> RegionParser::getRegionMap() const
{
    return regionMap;
}
