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
    QMap<QString, Stats *> getStatsMap() const;
    void setStatsMap(const QMap<QString, Stats *> &value);

private:
    Stats* buildStats(QStringList stringList);
    QMap<QString, Stats*> statsMap;
};

#endif // STATSPARSER_H
