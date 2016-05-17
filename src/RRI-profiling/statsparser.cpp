#include "statsparser.h"

StatsParser::StatsParser()
{

}

StatsParser::~StatsParser()
{
    for (Stats* stats:statsMap.values()){
        delete stats;
    }
}

int StatsParser::buildStats(QTextStream *stream)
{
    RRICsv streamReader=RRICsv(stream);
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
    stats->setRegion(stringList[CSV_STATS_REGION]);
    stats->setGroup(stringList[CSV_STATS_GROUP]);
    stats->setTotalInstanceNumber(stringList[CSV_STATS_TOTAL_INS_NUMBER]);
    stats->setTotalSampleNumber(stringList[CSV_STATS_TOTAL_SAMPLE_NUMBER]);
    stats->setTotalMedian(stringList[CSV_STATS_TOTAL_MEDIAN]);
    stats->setTotalMad(stringList[CSV_STATS_TOTAL_MAD]);
    stats->setSigmaTimeFactor(stringList[CSV_STATS_SIGMA_FACTOR]);
    stats->setSelectionIntervalMin(stringList[CSV_STATS_SELECTION_INTERVAL_MIN]);
    stats->setSelectionIntervalMax(stringList[CSV_STATS_SELECTION_INTERVAL_MAX]);
    stats->setSelectedInstanceNumber(stringList[CSV_STATS_SELECTED_INS_NUMBER]);
    stats->setSelectedInstanceProportion(stringList[CSV_STATS_SELECTED_INS_PROPORTION]);
    stats->setSelectedInstanceMedian(stringList[CSV_STATS_SELECTED_INS_MEDIAN]);
    stats->setSelectedInstanceMad(stringList[CSV_STATS_SELECTED_INS_MAD]);
    return stats;
}

QMap<QString, Stats *> StatsParser::getStatsMap() const
{
    return statsMap;
}

void StatsParser::setStatsMap(const QMap<QString, Stats *> &value)
{
    statsMap = value;
}


