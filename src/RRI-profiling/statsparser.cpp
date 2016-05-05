#include "statsparser.h"

StatsParser::StatsParser()
{

}

StatsParser::~StatsParser()
{
    for (Stats* stats:statsMap->values()){
        delete stats;
    }
}

int StatsParser::buildStats(QTextStream *stream)
{
    RRICsv streamReader=RRICsv(stream, ';');
    QStringList stringList;
    //header
    streamReader.readline();
    for (stringList=streamReader.readline();!streamReader.isEnd();stringList=streamReader.readline()){
        Stats* stats=buildStats(stringList);
        if (stats->getGroup().compare("Group_0")!=0){
            return RETURN_ERR_GROUP;
        }
        statsMap.insert(stats->getRegion(), stats);
    }
    return RETURN_OK;
}

Stats* StatsParser::buildStats(QStringList stringList)
{
    Stats* stats=new Stats();
}


