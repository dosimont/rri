#ifndef RRIPROFILING_H
#define RRIPROFILING_H

#include "slopeparser.h"
#include "statsparser.h"
#include "routineprofile.h"
#include <QString>
#include <QTextStream>

class RRIProfiling
{
public:
    RRIProfiling();
    void parseSlope(QTextStream* stream);
    void parseStats(QTextStream* stream);
    void writeStream(QTextStream* stream);
    void stackRoutines(QString region, RRICore *core);
private:
    QMap<QString, RoutineProfile> routineProfiles;
    SlopeParser *slopeParser;
    StatsParser *statsParser;
};

#endif // RRIPROFILING_H
