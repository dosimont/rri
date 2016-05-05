#include "slopeparser.h"

SlopeParser::SlopeParser()
{

}

SlopeParser::~SlopeParser()
{
    for (auto items:slopes->values()){
        for (Slope* slope:items->values()){
            delete slope;
        }
    }
}

int SlopeParser::buildSlopes(QTextStream *stream)
{
    RRICsv streamReader=RRICsv(stream);
    QStringList stringList;
    //header
    streamReader.readline();
    for (stringList=streamReader.readline();!streamReader.isEnd();stringList=streamReader.readline()){
        buildStats(stringList);
        if (stats->getGroup().compare("Group_0")!=0){
            return RETURN_ERR_GROUP;
        }
        statsMap.insert(stats->getRegion(), stats);
    }
    return RETURN_OK;
}

int SlopeParser::AddToSlope(QStringList stringList)
{
    if (stringList.size()<CSV_SLOPE_SIZE){
        return RETURN_ERR_CSVLINESIZE;
    }
    QString region=stringList[CSV_SLOPE_REGION];
    QString groupString=(stringList[CSV_SLOPE_GROUP]);
    int group=groupString.toInt();
    if (group!=0){
        return RETURN_ERR_GROUP;
    }
    QString counter=stringList[CSV_SLOPE_COUNTER];
    QString tsStr=stringList(CSV_SLOPE_TS);
    QString valueStr=stringList(CSV_SLOPE_VALUE);
    QString unknownStr=stringList(CSV_SLOPE_UNKNOWN);
    float ts=tsStr.toFloat();
    float value=valueStr.toFloat();
    float unknown=unknownStr.toFloat();
    if (slopes.contains(region)){
        if (!slopes[region].contains(counter)){
            Slope* slope=new Slope(region, counter);
            slopes[region].insert(counter, slope);
        }
    }else{
        slopes.insert(region, QMap<QString, Slope*>());
        Slope* slope=new Slope(region, counter);
        slopes[region].insert(counter, slope);
    }
    slopes[region][counter]->addPoint(ts, value, unknown);
    return RETURN_OK;
}
