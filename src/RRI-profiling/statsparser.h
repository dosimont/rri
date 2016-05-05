#ifndef STATSPARSER_H
#define STATSPARSER_H

#include <QMap>
#include <QString>
#include <QTextStream>
#include "stats.h"
#include "profiling_constants.h"
#include "rricsv.h"


class StatsParser
{
public:
    StatsParser();
    ~StatsParser();
    int buildStats(QTextStream* stream);
private:
    Stats* buildStats(QStringList stringList);
    QMap<QString, Stats*> statsMap;
};

#endif // STATSPARSER_H
